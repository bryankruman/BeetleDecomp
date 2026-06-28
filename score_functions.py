#!/usr/bin/env python3
"""Rank unmatched (nonmatching) BAR functions by estimated decomp difficulty.
Local analysis tool — reads the disassembled .s stubs, scores them, prints the
easiest first plus aggregate stats. Does not modify the repo."""
import os, re, sys, json

ASM_ROOT = os.path.expanduser("~/projects/bar-decomp/asm/us/nonmatchings")

INSN_RE = re.compile(r"/\*\s*[0-9A-Fa-f]+\s+[0-9A-Fa-f]+\s+[0-9A-Fa-f]+\s*\*/\s*([a-z0-9.]+)")
SIZE_RE = re.compile(r",\s*0x([0-9A-Fa-f]+)")

FLOAT_HINTS = (".s", ".d", "lwc1", "swc1", "ldc1", "sdc1", "mtc1", "mfc1", "cvt", "c.")
BRANCH_HINTS = ("beq", "bne", "blez", "bgtz", "bltz", "bgez", "bc1t", "bc1f", "b ", "bnez", "beqz")

def analyze(path):
    insns, floats, calls, branches, loops = 0, 0, 0, 0, 0
    label_lines, branch_targets = [], []
    size = None
    with open(path, encoding="utf-8", errors="replace") as f:
        for i, line in enumerate(f):
            if size is None:
                m = SIZE_RE.search(line)
                if m and "glabel" not in line and "/*" not in line:
                    size = int(m.group(1), 16)
            if line.strip().startswith(".L"):
                label_lines.append(i)
            m = INSN_RE.search(line)
            if not m:
                continue
            insns += 1
            op = m.group(1)
            if any(h in line for h in FLOAT_HINTS):
                floats += 1
            if op in ("jal", "jalr"):
                calls += 1
            if any(line.split("*/",1)[-1].strip().startswith(b.strip()) for b in BRANCH_HINTS):
                branches += 1
            # crude loop detect: a backward branch target label appears before branch
    # crude loop heuristic: presence of any .L label that is referenced by a branch above it
    has_loop = branches > 0 and len(label_lines) > 0
    score = (insns
             + floats * 4          # float regalloc is the hardest to match
             + calls * 1.0
             + branches * 1.5
             + (8 if has_loop else 0)
             + (size or insns*4)/64.0)
    return dict(insns=insns, floats=floats, calls=calls, branches=branches,
                loop=has_loop, leaf=(calls == 0), size=size or 0, score=round(score,1))

rows = []
for root, _, files in os.walk(ASM_ROOT):
    for fn in files:
        if fn.endswith(".s"):
            p = os.path.join(root, fn)
            a = analyze(p)
            a["func"] = fn[:-2]
            a["rel"] = os.path.relpath(p, ASM_ROOT)
            rows.append(a)

data = [r for r in rows if r["func"].startswith("D_")]      # data/rodata symbols
rows = [r for r in rows if not r["func"].startswith("D_")]  # real code functions
rows.sort(key=lambda r: r["score"])
n = len(rows)
print(f"UNMATCHED CODE functions : {n}")
print(f"UNMATCHED DATA symbols   : {len(data)}  (data/rodata to type into C)\n")

# aggregate buckets (code only)
leaf_nofloat = [r for r in rows if r["leaf"] and r["floats"] == 0]
tiny = [r for r in rows if r["insns"] <= 12]
small = [r for r in rows if r["insns"] <= 30]
nofloat = [r for r in rows if r["floats"] == 0]
floaty = [r for r in rows if r["floats"] > 0]
big = [r for r in rows if r["insns"] >= 80]
print("=== code difficulty buckets ===")
print(f"leaf + no-float (easiest)      : {len(leaf_nofloat)}")
print(f"tiny (<=12 instructions)       : {len(tiny)}")
print(f"small (<=30 instructions)      : {len(small)}")
print(f"no floats at all               : {len(nofloat)}")
print(f"float-using (harder)           : {len(floaty)}")
print(f"large (>=80 instructions)      : {len(big)}")
import statistics
print(f"median instructions/func       : {statistics.median(r['insns'] for r in rows):.0f}")
print(f"total instructions (unmatched) : {sum(r['insns'] for r in rows):,}")

print("\n=== 25 EASIEST unmatched functions ===")
print(f"{'score':>6} {'insn':>4} {'flt':>3} {'call':>4} {'loop':>4}  function / file")
for r in rows[:25]:
    print(f"{r['score']:>6} {r['insns']:>4} {r['floats']:>3} {r['calls']:>4} "
          f"{('yes' if r['loop'] else '-'):>4}  {r['rel']}")

# dump full ranking for the loop to consume
with open(os.path.expanduser("~/projects/bar-decomp/score_functions.json"), "w") as f:
    json.dump(rows, f)
print("\n(full ranking written to score_functions.json)")
