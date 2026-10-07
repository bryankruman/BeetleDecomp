"""Exercise the actual Makefile filter with GNU make; exclude exactly one input."""
from pathlib import Path
import json
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
PREFIX = 'asm/us/data/modules/uvdyn_rom.rodata-prefix.s'


class MakeReadonlyInputsTests(unittest.TestCase):
    def filter_line(self):
        lines = (ROOT / 'Makefile').read_text(encoding='utf-8').splitlines()
        matches = [line for line in lines if line.startswith('S_FILES') and 'filter-out' in line and PREFIX in line]
        self.assertEqual(len(matches), 1)
        expected = 'S_FILES       := $(filter-out ' + PREFIX + ',$(S_FILES))'
        self.assertEqual(matches[0], expected)
        return matches[0]

    def evaluate(self, sources):
        with tempfile.TemporaryDirectory(prefix='readonly-make-inputs-') as tmp:
            path = Path(tmp) / 'fixture.mk'
            fixture = ('S_FILES := ' + ' '.join(sources) + '\n' + self.filter_line()
                       + '\nO_FILES := $(addprefix build/,$(S_FILES:.s=.o))\n'
                       + '.PHONY: report\nreport:\n'
                       + '\t@$(info SOURCES=$(S_FILES))\n\t@$(info OBJECTS=$(O_FILES))\n\t@:\n')
            path.write_bytes(fixture.encode())
            output = subprocess.check_output(['make', '--no-print-directory', '-f', str(path), 'report'], text=True)
            rows = dict(line.split('=', 1) for line in output.splitlines() if '=' in line)
            return rows['SOURCES'].split(), rows['OBJECTS'].split()

    def test_exact_filter_is_tied_to_validated_ownership_metadata(self):
        # The metadata helper's own witness/type validation is covered by its
        # extraction tests. This test binds the exact build exclusion to that
        # declared C-included path, so changing either alone fails the suite.
        layout = json.loads((ROOT / 'config/us/readonly_layout/uvdyn_rom.json').read_text(encoding='utf-8'))
        self.assertEqual(layout['prefix_assembly'], PREFIX)
        self.assertEqual(layout['source'], 'src/modules/uvdyn_rom.c')
        self.filter_line()

    def test_only_declared_prefix_and_its_standalone_object_are_removed(self):
        keep = ['asm/us/data/modules/uvdyn_rom.rodata.s',
                'asm/us/data/modules/other.rodata-prefix.s',
                'asm/us/data/modules/uvdyn_rom.data.s', 'asm/us/data/ordinary.s',
                'src/normal.s', 'asm/jp/data/modules/uvdyn_rom.rodata-prefix.s']
        sources, objects = self.evaluate([PREFIX] + keep)
        self.assertEqual(sources, keep)
        self.assertEqual(objects, ['build/' + name[:-2] + '.o' for name in keep])
        self.assertNotIn('build/' + PREFIX[:-2] + '.o', objects)

    def test_normal_sources_unchanged_when_prefix_absent(self):
        sources = ['asm/us/data/ordinary.s', 'src/normal.s']
        actual, objects = self.evaluate(sources)
        self.assertEqual(actual, sources)
        self.assertEqual(objects, ['build/asm/us/data/ordinary.o', 'build/src/normal.o'])


if __name__ == '__main__':
    unittest.main()
