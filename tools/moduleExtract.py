#!/usr/bin/env python3

import yaml
import sys
import subprocess
from pathlib import Path
from tqdm import tqdm
import time
from moduleReadonlyLayout import prepare as prepare_readonly_layout, apply as apply_readonly_layout

MODULE_EXTRACT_VERSION = 0.2
PATCHED_MODULE_FILES_DIR = "patched_modules"

class Module:
    def __init__(self, name: str, done_sections=None, readonly_layout=None):
        self.name = name
        self.done_sections = done_sections or []
        self.readonly_layout = readonly_layout
        if readonly_layout is not None and "rodata" not in self.done_sections:
            raise ValueError("readonly_layout requires whole-object rodata ownership")

    def __repr__(self):
        return f"<Module name={self.name} Done sections={self.done_sections}>"
    

class Disassembler:
    def __init__(self):
        self.args = []
        self.cmd = [sys.executable, "tools/moduleFileDisasm.py"]

    def addArgs(self, arg: str):
        self.args.append(arg)

    def resetArgs(self):
        self.args = []

    def printArgs(self):
        print("Current args:", self.args)

    def execute(self):
        cmd = self.cmd + self.args
        subprocess.run(cmd, check=True, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)

def load_modules(path):
    with open(path) as f:
        data = yaml.safe_load(f)

    modules = []

    for entry in data["Modules"]:
        name = entry["name"]
        # read done_sections list if it exists
        done_sections = entry.get("done_sections", [])

        modules.append(Module(name, done_sections, entry.get("readonly_layout")))

    return modules

def main():
    disassembler = Disassembler()
    if len(sys.argv) < 2:
        print("Usage: module_extract.py modules.yaml")
        sys.exit(1)

    yaml_file = Path(sys.argv[1])

    modules = load_modules(yaml_file)

    print(f"Module extract {MODULE_EXTRACT_VERSION}");
    print("Modules found:", len(modules))

    # Reject ownership errors before extracting any module, not halfway through
    # a complete extraction run. Accepted readable C remains untouched.
    readonly_plans = {
        m.name: prepare_readonly_layout(Path.cwd(), m.readonly_layout, m.name,
            Path(PATCHED_MODULE_FILES_DIR) / (m.name + ".uvmo"))
        for m in modules if m.readonly_layout is not None
    }

    t = tqdm(range(len(modules)), colour="white", desc="Disassembling module files")
    processedModuleFilesCount = 0
    for m in modules:
        readonly_plan = readonly_plans.get(m.name)
        moduleLnkScriptFiles = "linker_scripts/us/module_files/"
        kernelLnkScriptFiles = "linker_scripts/us/"

        moduleSymAddrs = moduleLnkScriptFiles + m.name + "_symbol_addrs.txt"
        moduleRelAddrs = moduleLnkScriptFiles + m.name + "_reloc_addrs.txt"
        kernelSymAddrs = kernelLnkScriptFiles + "symbol_addrs.txt"

        if "data" in m.done_sections:
            disassembler.addArgs("--dont-split-data")
            
        if "bss" in m.done_sections:
            disassembler.addArgs("--dont-split-bss")

        if "rodata" in m.done_sections:
            disassembler.addArgs("--dont-split-rodata")

#        disassembler.addArgs("--asm-nm-label")
#        disassembler.addArgs("#")
        disassembler.addArgs("--Mfpr-names")
        disassembler.addArgs("o32")
        disassembler.addArgs("--asm-jtbl-label")
        disassembler.addArgs("glabel")
        disassembler.addArgs("--module-name")
        disassembler.addArgs(m.name)
        disassembler.addArgs("--create-c-file")
        disassembler.addArgs("--symbol-addrs")
        disassembler.addArgs(moduleSymAddrs)
        disassembler.addArgs("--reloc-addrs")
        disassembler.addArgs(moduleRelAddrs)
        disassembler.addArgs("--symbol-addrs")
        disassembler.addArgs(kernelSymAddrs)
        disassembler.addArgs("--no-use-fpccsr")
        disassembler.addArgs(PATCHED_MODULE_FILES_DIR + "/" + m.name + ".uvmo")
        
        #disassembler.printArgs()
        if not "text" in m.done_sections:
            disassembler.addArgs("--split-functions")
            disassembler.addArgs("asm/us/nonmatchings/modules/")

        disassembler.addArgs("asm/us/data/modules")
        disassembler.execute()
        if readonly_plan is not None:
            apply_readonly_layout(readonly_plan)
        disassembler.resetArgs()
        t.update(1)

if __name__ == "__main__":
    main()
    print("Done")
