# Matching and recomp dependency validation — October 6, 2026

The upstream integration through e0112bf retains upstream history, and four further
readable utility functions are committed in 76a2c9b. This is partial decompilation:
1,196 assembly references (62 entrypoints), 825,380 instruction bytes and 1,362
address-named C definitions remain. Zero unknown assembly sizes are recorded.

All 133 packed module SHA-256 checks and original USA ROM SHA-1
e5ab4d226c08d22f68a2edcc48870203e67454b8 passed in isolated pve container 105.
The four utility modules and ROM passed again after semantic naming and extraction.
All 1,013 accepted local source files matched the worker before each landing.
Evidence is under /opt/beetle-campaign-20261006/accepted-union and
accepted-readable-small-functions. Private input archives remain frozen.

The recomp linker generator now discovers modules from src/modules/*.c, matching
the Makefile. Fully recovered cbars and expl had no remaining assembly data/BSS
and were incorrectly omitted by the previous discovery. Missing partial objects
now fail explicitly. The generated linker script remains ignored and is removed
from Git tracking; source generation is authoritative. The check wrapper defaults
to four jobs, keeping worker builds within the approved resource bound.

The corrected 133-module recomp ELF SHA-256 is
07b1fdf9853f11d56ec59c1099a722db9794b965d81c909656ef3fee8d057a79.
The original matching ROM still passes. In the companion recomp, main/patch code
generation, strict original-instruction fixups, MIPS patch linking and the full
Linux Release application link pass with this ELF. Actual cartridge-read and
ELF fixup regressions pass. Evidence: /opt/beetle-recomp-review-20261006/
cartridge-read-validation. This does not establish Windows or gameplay correctness.

The Windows staging records verified-union-landed.json, readable-small-landed.json
and accepted source manifests retain local provenance. Do not publish private ROMs,
ELFs, raw archives or SDK files. No paid model/API benchmark is claimed.
