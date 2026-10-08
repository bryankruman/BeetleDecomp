"""Exercise the actual partial-link Make rule in disposable fixtures.

Run with --makefile-source PATH to test a staged Makefile. Tests perform no
compilation or real linking. The linker stub records argument order and output
creation; the actual rule must include optional metadata as a dependency.
"""
import argparse
import json
import os
from pathlib import Path
import shlex
import subprocess
import sys
import tempfile
import time
import unittest

parser = argparse.ArgumentParser(add_help=False)
parser.add_argument('--makefile-source', type=Path, default=Path('Makefile'))
options, remaining = parser.parse_known_args()
source = options.makefile_source.read_text(encoding='utf-8')
start = source.index('$(BUILD_DIR)/partial_%.o:')
end = source.index('\n$(BUILD_DIR)/bin/us/%.o:', start)
RULE = source[start:end]


class PartialAliasMetadata(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(prefix='make-partial-alias-')
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.objects = ['build/src/modules/sample.o',
            'build/asm/us/data/modules/sample.rodata.o',
            'build/asm/us/data/modules/sample.data.o',
            'build/asm/us/data/modules/sample.bss.o']
        past = time.time() - 120
        for name in self.objects + ['asm/us/data/modules/sample.rodata.s',
            'asm/us/data/modules/sample.data.s', 'asm/us/data/modules/sample.bss.s']:
            path = self.root / name
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text('fixture\n', encoding='utf-8')
            os.utime(path, (past, past))
        self.alias = 'linker_scripts/us/module_files/sample_partial_aliases.ld'
        self.target = 'build/partial_sample.o'
        stub = self.root / 'link.py'
        stub.write_text('import json,sys\nfrom pathlib import Path\n'
            'p=Path("calls.json"); rows=json.loads(p.read_text()) if p.exists() else []\n'
            'rows.append(sys.argv[1:]);p.write_text(json.dumps(rows))\n'
            'Path(sys.argv[sys.argv.index("-o")+1]).write_bytes(b"linked")\n', encoding='utf-8')
        (self.root / 'Makefile').write_text('BUILD_DIR=build\nMODULE_C_DIR=src/modules\n'
            'MODULE_DATA_DIR=asm/us/data/modules\nVERSION=us\n'
            'LD=' + shlex.quote(sys.executable) + ' link.py\n'
            'print=\n.SECONDEXPANSION:\n' + RULE + '\n', encoding='utf-8')

    def make(self):
        result = subprocess.run(['make', self.target], cwd=self.root,
            capture_output=True, text=True, timeout=30)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        return json.loads((self.root / 'calls.json').read_text(encoding='utf-8'))

    def expected(self, aliases=False):
        return ['-r', *self.objects, *(['-T', self.alias] if aliases else []),
            '-Map', 'build/partial_sample.map', '-o', self.target]

    def add_alias(self):
        path = self.root / self.alias
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text('native_name = defined_owner + 0x1E;\n', encoding='utf-8')
        return path

    def test_absent_metadata_retains_original_object_order(self):
        self.assertEqual(self.make(), [self.expected()])
        self.assertEqual(self.make(), [self.expected()])

    def test_present_metadata_is_passed_once_and_not_as_object(self):
        self.add_alias()
        self.assertEqual(self.make(), [self.expected(aliases=True)])
        self.assertEqual(self.make(), [self.expected(aliases=True)])

    def test_metadata_change_triggers_relink_without_object_change(self):
        alias = self.add_alias()
        self.assertEqual(self.make(), [self.expected(aliases=True)])
        original_objects = {name: (self.root / name).read_bytes() for name in self.objects}
        alias.write_text('native_name = defined_owner + 0x20;\n', encoding='utf-8')
        # Force only the existing target older; no sleeps or future timestamps.
        old = alias.stat().st_mtime - 1
        os.utime(self.root / self.target, (old, old))
        self.assertEqual(self.make(), [self.expected(aliases=True)] * 2)
        self.assertEqual({name: (self.root / name).read_bytes() for name in self.objects}, original_objects)

    def test_new_metadata_triggers_relink_of_existing_target(self):
        self.assertEqual(self.make(), [self.expected()])
        alias = self.add_alias()
        old = alias.stat().st_mtime - 1
        os.utime(self.root / self.target, (old, old))
        self.assertEqual(self.make(), [self.expected(), self.expected(aliases=True)])


if __name__ == '__main__':
    unittest.main(argv=[sys.argv[0], *remaining])
