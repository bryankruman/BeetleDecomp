"""Exercise the actual Makefile filter with GNU make; exclude exactly the declared inputs."""
from pathlib import Path
import json
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
PREFIX = 'asm/us/data/modules/uvdyn_rom.rodata-prefix.s'
TED_PREFIX = 'asm/us/data/modules/ted.rodata-prefix.s'
PFX_PREFIX = 'asm/us/data/modules/uvpfx_rom.rodata-prefix.s'
LIGHT_RODATA = 'asm/us/data/modules/light.rodata.s'
FILM_OWNERS = ['asm/us/data/modules/filmroll.rodata.s', 'asm/us/data/modules/filmroll.data.s', 'asm/us/data/modules/filmroll.bss.s']
DYN_TERMINAL = 'asm/us/data/modules/uvdyn_rom-secondary.rodata-island.s'


class MakeReadonlyInputsTests(unittest.TestCase):
    def filter_line(self):
        lines = (ROOT / 'Makefile').read_text(encoding='utf-8').splitlines()
        matches = [line for line in lines if line.startswith('S_FILES') and 'filter-out' in line and PREFIX in line]
        self.assertEqual(len(matches), 1)
        expected = 'S_FILES       := $(filter-out asm/us/data/modules/uvdyn_rom.rodata-prefix.s asm/us/data/modules/uvdyn_rom-secondary.rodata-island.s asm/us/data/modules/ted.rodata-prefix.s asm/us/data/modules/race.rodata-prefix.s asm/us/data/modules/race-floats.rodata-island.s asm/us/data/modules/misc.rodata-prefix.s asm/us/data/modules/misc.rodata-suffix.s asm/us/data/modules/misc.rodata-aliases.s asm/us/data/modules/uvpfx_rom.rodata-prefix.s asm/us/data/modules/light.rodata.s asm/us/data/modules/filmroll.rodata.s asm/us/data/modules/filmroll.data.s asm/us/data/modules/filmroll.bss.s,$(S_FILES))'
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
        self.assertEqual(layout['version'], 3)
        self.assertEqual(layout['terminal_c_literals']['obsolete_assembly'], DYN_TERMINAL)
        self.assertEqual(layout['terminal_c_literals']['end'] - layout['terminal_c_literals']['begin'], 44)
        ted = json.loads((ROOT / 'config/us/readonly_layout/ted.json').read_text(encoding='utf-8'))
        self.assertEqual(ted['prefix_assembly'], TED_PREFIX)
        self.assertEqual(ted['source'], 'src/modules/ted.c')
        misc = json.loads((ROOT / 'config/us/readonly_layout/misc.json').read_text(encoding='utf-8'))
        self.assertEqual([misc[key] for key in ('prefix_assembly', 'suffix_assembly', 'bridge_assembly')], ['asm/us/data/modules/misc.rodata-prefix.s', 'asm/us/data/modules/misc.rodata-suffix.s', 'asm/us/data/modules/misc.rodata-aliases.s'])
        pfx = json.loads((ROOT / 'config/us/readonly_layout/uvpfx_rom.json').read_text(encoding='utf-8'))
        self.assertEqual(pfx['version'], 6)
        self.assertEqual(pfx['prefix_assembly'], PFX_PREFIX)
        self.assertEqual(pfx['source'], 'src/modules/uvpfx_rom.c')
        # Whole LIGHT readonly ownership is a standard done_sections entry,
        # not a retained-fragment layout or a fictitious readonly_layout file.
        modules = (ROOT / 'config/us/modules.yaml').read_text(encoding='utf-8')
        marker = '  - name: light\n'
        self.assertEqual(modules.count(marker), 1)
        light = modules.split(marker, 1)[1].split('  - name:', 1)[0]
        self.assertEqual(light, '    done_sections:\n      - rodata\n')
        film = modules.split('  - name: filmroll\n', 1)[1].split('  - name:', 1)[0]
        self.assertEqual(film, '    done_sections:\n      - text\n      - data\n      - bss\n      - rodata\n')
        self.filter_line()

    def test_only_declared_prefix_and_its_standalone_object_are_removed(self):
        keep = ['asm/us/data/modules/uvdyn_rom.rodata.s',
                'asm/us/data/modules/other.rodata-prefix.s',
                'asm/us/data/modules/uvdyn_rom.data.s', 'asm/us/data/ordinary.s',
                'src/normal.s', 'asm/jp/data/modules/light.rodata.s', 'asm/jp/data/modules/uvdyn_rom.rodata-prefix.s',
                'asm/jp/data/modules/ted.rodata-prefix.s']
        sources, objects = self.evaluate([PREFIX, TED_PREFIX, 'asm/us/data/modules/race.rodata-prefix.s', 'asm/us/data/modules/race-floats.rodata-island.s'] + ['asm/us/data/modules/misc.rodata-prefix.s', 'asm/us/data/modules/misc.rodata-suffix.s', 'asm/us/data/modules/misc.rodata-aliases.s', PFX_PREFIX, LIGHT_RODATA] + FILM_OWNERS + [DYN_TERMINAL] + keep)
        self.assertEqual(sources, keep)
        self.assertEqual(objects, ['build/' + name[:-2] + '.o' for name in keep])
        self.assertNotIn('build/' + PREFIX[:-2] + '.o', objects)
        self.assertNotIn('build/' + TED_PREFIX[:-2] + '.o', objects)
        self.assertNotIn(LIGHT_RODATA, sources)
        self.assertNotIn('build/' + LIGHT_RODATA[:-2] + '.o', objects)


    def test_complete_light_rodata_excludes_only_its_stale_partial_object(self):
        lines = (ROOT / 'Makefile').read_text(encoding='utf-8').splitlines()
        matches = [line for line in lines if line.startswith('    $$(filter-out $(BUILD_DIR)/asm/us/data/modules/light.rodata.o $(BUILD_DIR)/asm/us/data/modules/filmroll.rodata.o,')]
        self.assertEqual(len(matches), 1)
        expected = '    $$(filter-out $(BUILD_DIR)/asm/us/data/modules/light.rodata.o $(BUILD_DIR)/asm/us/data/modules/filmroll.rodata.o,$$(addprefix $(BUILD_DIR)/,$$(addsuffix .o,$$(basename $$(wildcard $(MODULE_DATA_DIR)/$$*.rodata.s))))) \\'
        self.assertEqual(matches[0], expected)
        # Evaluate the actual secondary-expansion expression with both a stale
        # LIGHT object and another module's legitimate readonly object present.
        with tempfile.TemporaryDirectory(prefix='readonly-partial-inputs-') as tmp:
            root = Path(tmp)
            for module in ('light', 'other'):
                source = root / ('asm/us/data/modules/' + module + '.rodata.s')
                obj = root / ('build/asm/us/data/modules/' + module + '.rodata.o')
                source.parent.mkdir(parents=True, exist_ok=True)
                obj.parent.mkdir(parents=True, exist_ok=True)
                source.write_text('', encoding='utf-8')
                obj.write_bytes(b'')
            fixture = ('BUILD_DIR := build\nMODULE_DATA_DIR := asm/us/data/modules\n'
                       + '.SECONDEXPANSION:\nbuild/partial_%.o: \\\n'
                       + matches[0].rstrip().removesuffix(chr(92)) + '\n'
                       + '\t@$(info OBJECTS=$^)\n\t@:\n')
            path = root / 'fixture.mk'
            path.write_text(fixture, encoding='utf-8')
            for module, expected_objects in (('light', []), ('other', ['build/asm/us/data/modules/other.rodata.o'])):
                output = subprocess.check_output(['make', '--no-print-directory', '-f', str(path), 'build/partial_' + module + '.o'], cwd=root, text=True)
                rows = [line[len('OBJECTS='):] for line in output.splitlines() if line.startswith('OBJECTS=')]
                self.assertEqual(len(rows), 1)
                self.assertEqual(rows[0].split(), expected_objects)

    def test_whole_film_owners_exclude_only_their_stale_partial_objects(self):
        lines = (ROOT / 'Makefile').read_text(encoding='utf-8').splitlines()
        expected = {'rodata': '    $$(filter-out $(BUILD_DIR)/asm/us/data/modules/light.rodata.o $(BUILD_DIR)/asm/us/data/modules/filmroll.rodata.o,$$(addprefix $(BUILD_DIR)/,$$(addsuffix .o,$$(basename $$(wildcard $(MODULE_DATA_DIR)/$$*.rodata.s)))))', 'data': '    $$(filter-out $(BUILD_DIR)/asm/us/data/modules/filmroll.data.o,$$(addprefix $(BUILD_DIR)/,$$(addsuffix .o,$$(basename $$(wildcard $(MODULE_DATA_DIR)/$$*.data.s)))))', 'bss': '    $$(filter-out $(BUILD_DIR)/asm/us/data/modules/filmroll.bss.o,$$(addprefix $(BUILD_DIR)/,$$(addsuffix .o,$$(basename $$(wildcard $(MODULE_DATA_DIR)/$$*.bss.s)))))'}
        for section, line in expected.items():
            self.assertEqual(lines.count(line + ' ' + chr(92)), 1)
            with tempfile.TemporaryDirectory(prefix='film-owner-partial-') as tmp:
                root = Path(tmp)
                for module in ('filmroll', 'other'):
                    source = root / ('asm/us/data/modules/' + module + '.' + section + '.s')
                    obj = root / ('build/asm/us/data/modules/' + module + '.' + section + '.o')
                    source.parent.mkdir(parents=True, exist_ok=True)
                    obj.parent.mkdir(parents=True, exist_ok=True)
                    source.write_bytes(b'')
                    obj.write_bytes(b'')
                fixture = ('BUILD_DIR := build\nMODULE_DATA_DIR := asm/us/data/modules\n'
                           + '.SECONDEXPANSION:\nbuild/partial_%.o: ' + chr(92) + '\n'
                           + line + '\n\t@$(info OBJECTS=$^)\n\t@:\n')
                path = root / 'fixture.mk'
                path.write_text(fixture, encoding='utf-8')
                for module in ('filmroll', 'other'):
                    output = subprocess.check_output(['make', '--no-print-directory', '-f', str(path), 'build/partial_' + module + '.o'], cwd=root, text=True)
                    rows = [s[len('OBJECTS='):] for s in output.splitlines() if s.startswith('OBJECTS=')]
                    self.assertEqual(len(rows), 1)
                    self.assertEqual(rows[0].split(), [] if module == 'filmroll' else ['build/asm/us/data/modules/other.' + section + '.o'])

    def test_normal_sources_unchanged_when_prefix_absent(self):
        sources = ['asm/us/data/ordinary.s', 'src/normal.s']
        actual, objects = self.evaluate(sources)
        self.assertEqual(actual, sources)
        self.assertEqual(objects, ['build/asm/us/data/ordinary.o', 'build/src/normal.o'])


if __name__ == '__main__':
    unittest.main()
