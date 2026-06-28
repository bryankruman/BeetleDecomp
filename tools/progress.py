#!/usr/bin/env python3
"""Decomp progress report for this fork.

Counts remaining (still-assembly) functions and data symbols from the disassembly,
groups them by module, and estimates overall matched %. The *remaining* counts are
exact; the matched % uses a heuristic count of C function definitions and is labelled
approximate. Run from anywhere.

Usage: python3 tools/progress.py [--top N] [--json]
"""
import os, re, sys, json, collections

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
ASM = os.path.join(ROOT, "asm", "us", "nonmatchings")
SRC = os.path.join(ROOT, "src")

top_n = 20
as_json = False
args = sys.argv[1:]
if "--top" in args:
    top_n = int(args[args.index("--top") + 1])
if "--json" in args:
    as_json = True

def module_of(relpath):
    # asm/us/nonmatchings/modules/<mod>/...  or  asm/us/nonmatchings/<seg>/...
    parts = relpath.split(os.sep)
    if parts and parts[0] == "modules" and len(parts) > 1:
        return parts[1]
    return parts[0] if parts else "(root)"

DATA_PREFIX = ("D_", "RO_STR", "jtbl_", "jpt_", "L8")  # data / rodata / jump tables

rem_code = collections.Counter()   # remaining functions per module
rem_data = collections.Counter()   # remaining data symbols per module
code_total = data_total = 0

if not os.path.isdir(ASM):
    print(f"error: no disassembly at {ASM} — run `make extract` first.", file=sys.stderr)
    sys.exit(2)

for root, _, files in os.walk(ASM):
    for fn in files:
        if not fn.endswith(".s"):
            continue
        rel = os.path.relpath(os.path.join(root, fn), ASM)
        mod = module_of(rel)
        if fn.startswith(DATA_PREFIX):
            rem_data[mod] += 1; data_total += 1
        else:
            rem_code[mod] += 1; code_total += 1

# Heuristic: matched C functions = function-definition-looking lines minus GLOBAL_ASM stubs.
matched = 0
global_asm = 0
func_def = re.compile(r"^[A-Za-z_][\w\s\*]*\b([A-Za-z_]\w*)\s*\([^;]*\)\s*\{?\s*$")
for root, _, files in os.walk(SRC):
    for fn in files:
        if not fn.endswith(".c"):
            continue
        with open(os.path.join(root, fn), encoding="utf-8", errors="replace") as f:
            for line in f:
                if "GLOBAL_ASM" in line:
                    global_asm += 1
                elif func_def.match(line) and "return" not in line and "=" not in line:
                    matched += 1

total_funcs = matched + code_total
pct = (100.0 * matched / total_funcs) if total_funcs else 0.0

if as_json:
    print(json.dumps(dict(matched_approx=matched, remaining_code=code_total,
                          remaining_data=data_total, pct_approx=round(pct, 1),
                          per_module_code=dict(rem_code), per_module_data=dict(rem_data))))
    sys.exit(0)

print("=" * 60)
print(" Beetle Adventure Racing decomp — progress")
print("=" * 60)
print(f"  matched functions (approx) : {matched}")
print(f"  remaining code functions   : {code_total}")
print(f"  remaining data symbols     : {data_total}")
print(f"  GLOBAL_ASM stubs in src     : {global_asm}")
print(f"  estimated completion        : {pct:.1f}%  (approx — function count)")
print()

done = sorted(m for m in rem_code if rem_code[m] == 0)  # (won't appear; modules vanish when done)
modules = sorted(set(list(rem_code) + list(rem_data)), key=lambda m: -rem_code[m])
print(f"  Top {top_n} modules by remaining functions:")
print(f"  {'module':<28}{'funcs':>7}{'data':>7}")
print("  " + "-" * 42)
for m in modules[:top_n]:
    print(f"  {m:<28}{rem_code[m]:>7}{rem_data[m]:>7}")
print()
print("  Tip: a module with few remaining functions is a good 'finish it off'")
print("  target — completing a module lets scripts/check.sh --module verify it fast.")
