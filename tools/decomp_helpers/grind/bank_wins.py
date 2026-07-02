#!/usr/bin/env python3
"""Bank the sweep-verified score-0 permuter wins: sequential accumulation with a
per-bank module-hash gate (keep iff pass, else revert that one), then full make +
ROM SHA gate, ledger touch, nomatch.json refresh, and a local git commit.
"""
import os, re, glob, subprocess, sys, json, csv

REPO = os.path.expanduser("~/projects/bar-decomp"); os.chdir(REPO)
GRIND = "/mnt/c/Users/Bryan/Projects/BeetleRecomp/.grind"
SHA = "e5ab4d226c08d22f68a2edcc48870203e67454b8"

TARGETS = [fn for fn, r in json.load(open(f"{GRIND}/sweep_results.json")).items() if r == "BANKABLE"]
print(f"banking {len(TARGETS)}: {TARGETS}")

st = subprocess.run("git status --porcelain", shell=True, capture_output=True, text=True).stdout.strip()
if st:
    print("TREE NOT CLEAN — aborting:\n" + st); sys.exit(1)

def find_def(lines, fn):
    for i, l in enumerate(lines):
        if re.search(r'\b%s\s*\(' % re.escape(fn), l) and not l.rstrip().endswith(";"):
            return i
    return None

def extract_def(text, fn):
    lines = text.split("\n"); di = find_def(lines, fn)
    if di is None: return None
    depth = 0; started = False
    for i in range(di, len(lines)):
        depth += lines[i].count("{") - lines[i].count("}")
        if "{" in lines[i]: started = True
        if started and depth == 0:
            return "\n".join(lines[di:i + 1])
    return None

def seed_preamble(fn):
    for p in (f"{GRIND}/seeds/{fn}.c", f"progress/seeds/{fn}.c", f"progress/wins/{fn}.c"):
        if os.path.exists(p):
            lines = open(p).read().split("\n"); di = find_def(lines, fn)
            if di is not None:
                return "\n".join(lines[:di]).strip()
    return ""

def win_body(fn):
    for o in sorted(glob.glob(f"nonmatchings/{fn}/output*")):
        try: s = int(open(f"{o}/score.txt").read().strip())
        except Exception: continue
        if s == 0:
            return extract_def(open(f"{o}/source.c").read(), fn)
    return None

def gate(mod):
    subprocess.run(["rm", "-f", f"build/bin/us/{mod}.o", f"build/src/modules/{mod}.o"],
                   stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    r = subprocess.run(f"make build/bin/us/{mod}.o 2>&1", shell=True, capture_output=True, text=True)
    return "Hash verification passed" in (r.stdout + r.stderr)

banked = []
for fn in sorted(TARGETS):
    mod = re.match(r'func_([a-z0-9_]+?)_[0-9A-Fa-f]{8}$', fn).group(1)
    SRC = f"src/modules/{mod}.c"
    orig = open(SRC).read()
    pragma = f'#pragma GLOBAL_ASM("asm/us/nonmatchings/modules/{mod}/{fn}.s")'
    if pragma not in orig:
        print(f"  {fn:42s} SKIP (pragma gone)"); continue
    body = win_body(fn)
    if not body:
        print(f"  {fn:42s} SKIP (no score-0 output)"); continue
    pre = seed_preamble(fn)
    hay = re.sub(r'#pragma GLOBAL_ASM\([^)]*\)', '', orig)
    keep = []
    if pre:
        units, buf, depth = [], [], 0
        for l in pre.split("\n"):
            s = l.strip()
            if not s or s.startswith("//"): continue
            buf.append(l); depth += l.count("{") - l.count("}")
            if depth <= 0 and s.endswith(";"):
                units.append("\n".join(buf)); buf = []; depth = 0
        for u in units:
            mm = re.search(r'}\s*(\w+)\s*;', u) or re.search(r'\b(D_\w+|g[A-Z]\w+|func_\w+)\b', u)
            key = mm.group(1) if mm else None
            if key and re.search(r'\b%s\b' % re.escape(key), hay):
                continue
            keep.append(u)
    cand = ("\n".join(keep) + "\n\n" if keep else "") + body
    open(SRC, "w").write(orig.replace(pragma, cand))
    if gate(mod):
        banked.append(fn)
        print(f"  {fn:42s} BANKED")
    else:
        open(SRC, "w").write(orig)
        print(f"  {fn:42s} REVERTED (accumulation conflict)")

if not banked:
    print("nothing banked"); sys.exit(0)

print("\nfull build + SHA gate ...")
subprocess.run("make -j6 >/dev/null 2>&1", shell=True)
sha = subprocess.run("sha1sum build/beetleadventurerac.us.z64", shell=True,
                     capture_output=True, text=True).stdout
if SHA not in sha:
    print(f"ROM SHA MISMATCH — reverting everything!\n{sha}")
    subprocess.run("git checkout -- src/modules", shell=True)
    sys.exit(1)
print(f"ROM OK {sha.split()[0]}")

# delete orphaned .s for banked fns (repo convention), touch ledger, refresh nomatch pool
for fn in banked:
    mod = re.match(r'func_([a-z0-9_]+?)_[0-9A-Fa-f]{8}$', fn).group(1)
    s = f"asm/us/nonmatchings/modules/{mod}/{fn}.s"
    if os.path.exists(s): subprocess.run(["git", "rm", "-q", "-f", s])

rows = list(csv.DictReader(open("progress/ledger.csv")))
for r in rows:
    if r["fn"] in banked: r["status"] = "banked"
w = csv.DictWriter(open("progress/ledger.csv", "w", newline=""), fieldnames=rows[0].keys())
w.writeheader(); w.writerows(rows)

pool = json.load(open(f"{GRIND}/nomatch.json"))
fresh = []
for fn in pool:
    m = re.match(r'func_([a-z0-9_]+?)_[0-9A-Fa-f]{8}$', fn)
    if not m: continue
    src = f"src/modules/{m.group(1)}.c"
    if os.path.exists(src) and f'/{fn}.s"' in open(src).read():
        fresh.append(fn)
json.dump(fresh, open(f"{GRIND}/nomatch.json", "w"))
print(f"nomatch.json refreshed: {len(pool)} -> {len(fresh)} (dropped already-banked/stale)")

subprocess.run("git add -A src/modules progress/ledger.csv", shell=True)
msg = ("bank %d permuter score-0 wins recovered by integration sweep (byte-exact, ROM OK)\n\n"
       "%s\n\nEach gated per-module (DaisyBox hash) with sequential accumulation, then full\n"
       "ROM rebuild verified sha e5ab4d22. Wins were sitting in nonmatchings/*/output*/ from\n"
       "earlier campaigns without ever being integration-tested.\n\n"
       "Co-Authored-By: Claude Fable 5 <noreply@anthropic.com>") % (len(banked), "\n".join(sorted(banked)))
open("/tmp/bankmsg.txt", "w").write(msg)
subprocess.run("git commit -q -F /tmp/bankmsg.txt", shell=True)
print(subprocess.run("git log --oneline -2", shell=True, capture_output=True, text=True).stdout)
print("BANKED:", " ".join(sorted(banked)))
