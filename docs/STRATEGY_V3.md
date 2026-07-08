# BAR Decomp — Strategy v3 + Code Quality Standard (2026-07-08)

Post-mortem of the moon1 (dev-worker CT 119) permuter campaign and the revised operating
strategy. Supplements `GRIND_PLAYBOOK.md` (the wave loop mechanics still apply); where they
disagree, this doc wins.

## 1. moon1 campaign post-mortem ("bignight", 2026-07-04 → 07-06, ~30h)

**Result: 26 gated wins + 13 transfer-fail zeros out of ~550 attempted (~5% banked, ~7% zeros).**
Sweep as of 2026-07-06: 35 BANKABLE win files in `.grind/wins/` — **still unbanked**.

What the log actually shows (dev-worker `~/permuter.log`):

1. **~430 of 550 functions (78%) were cut after the 600s round with high best scores.**
   These seeds were structurally wrong — the permuter mutates a close seed, it cannot invent
   control flow or struct bases. The night pool was mostly `m2c_seed_all` auto-seeds, a
   known-depleted source. **The user's hypothesis is confirmed: seed quality, not permuter
   budget, was the binding constraint.** More hours on the same pool ≈ zero marginal wins.
2. **13 functions found score-0 repeatedly but never banked (transfer fail).** Rounds 2–3
   burned most of their budget re-finding the *same* non-bankable zeros (e.g.
   `func_med_004052C8`, `func_cam_00402158` zero-looped dozens of times). These are ~13
   "free" matches lost to context drift between the permuter's frozen `base.c` and the live
   module — an infrastructure bug, not a search problem.
3. **No end-of-campaign banking.** Wins sat on disk 2+ days. Every campaign must end with
   `bank_wins.py` + a notification/artifact.

## 2. Strategy v3 — changes

### Immediate (before any new campaign)
- **Bank the 35 BANKABLE wins** (`bank_wins.py`, full ROM SHA gate, commit, push, bump
  recomp submodule).
- **Fix the transfer-fail class**: for each of the 13, re-import against the *current*
  module (fresh `import.py`), diff the frozen `base.c` context vs live module decls, and
  re-gate the existing zero. Root-cause the drift (usually extern/typedef divergence).
  Cap automatic re-hunts at **2 per function per campaign** — after that, park with the
  zero attached for a manual context fix.

### Seeds are the product; the permuter is only the last mile
- **No function enters a worker campaign without a triaged base score < 400**
  (`_permbase.py` / campaign2's import scores). base>400 items go back to the seed stage,
  not the queue. This alone would have cut the moon1 pool from 550 to roughly the ~120
  that were ever plausible.
- **Seed quality ladder** (cheapest first):
  1. `gen_cards2.py --context` m2c seeds (module context = real types — validated).
  2. Sonnet seed wave with the module's *scribed* headers in the cards.
  3. Opus only for permuter-proven near-misses (plateau < ~150 over two long rounds),
     always with the permuter's best-output diff in the prompt.
- **Scribe feeds match rate** (proven): correct struct/prototype context changes codegen.
  Before re-seeding a module's tail, do its scribe pass (Section 3) — richer
  `include/*.h` → better m2c context → lower base scores → higher permuter yield.
  Module order: highest (remaining-functions × current-match%) first, i.e. mostly-matched
  modules with a stubborn tail.

### Worker (moon1 dev-worker) usage rules
- Queue = triaged base<400 pool only. Ladder 300s → 900s → 1800s; survivors halved per
  round by best score.
- Campaign script must finish with: `bank_wins.py` → `sweep_wins.py` → results pushed back
  to `.grind/sweep_results.json` → touch a `CAMPAIGN_DONE` marker so the next interactive
  session banks immediately.
- Re-hunt cap 2 (above). Log a per-round table of best scores (already present) — that
  table is the *input* to the next seed wave, not just a report.

### The loop, revised
```
scribe module (types → headers, gated)            [tokens, high leverage]
→ gen_cards2 with new context                     [free]
→ seed wave (Sonnet, style contract §3)           [tokens, cheap]
→ consolidate2 byte-gate → fix_wave               [cheap]
→ triage: base<400 → worker queue; else park      [free]
→ moon1 campaign (ladder, re-hunt cap, auto-bank) [compute, free]
→ bank + sweep + commit                           [required, same day]
→ scribe pass over newly banked fns               [tokens — see §3, now mandatory]
```

## 3. Code Quality Standard (mandatory, per-wave)

Match-first remains: phase-1 candidates may use placeholder style (`unk<hexoff>`,
`Node_<ADDR>`, raw casts) because the byte gate is the only thing that matters there.
**But a wave is not "done" until its banked functions pass the scribe checklist below.**
Readability debt no longer accumulates indefinitely — each wave commits (a) the matched
code and (b) the scribe pass for the *previous* wave, so the debt window is one wave.

### Naming
- **Functions**: keep `func_<mod>_<addr>` only until behavior is understood; then rename to
  `<Module>_<VerbNoun>` per the uv-engine conventions (e.g. `Pause_DrawMenuCursor`,
  `UvLight_SetAmbientColor`). Every rename recorded in `docs/SYMBOLS.md` (addr → name),
  applied repo-wide by script, full-ROM SHA per batch.
- **Globals**: `D_<addr>` → `g<PascalCase>` with a type (`gPauseMenuState`), or
  `s<PascalCase>` for module-static data.
- **Locals**: descriptive camelCase (`entryIndex`, `carSpeed`, `nodePtr`) — never `sp2C`,
  `temp_v0`, `phi_a1` in banked code. Loop indices `i/j/k` are fine.
- **Struct members**: named with purpose the moment the purpose is known; until then
  `unk<hexoffset>` (never invented guesses — a wrong name is worse than `unk30`).
- ASCII only (euc-jp asm-processor constraint).

### Types & structs
- Promote raw casts (`*(s32*)((u8*)p + 0x2C)`) to typed member access (`car->engineRpm`)
  during scribe. The cast form is a matching tool, not a final form.
- Structs live in `include/structs.h` (or a module header), one definition, members with
  `// purpose` comments and offset comments on non-obvious padding:
  ```c
  typedef struct CarState {
      /* 0x00 */ Vec3f position;
      /* 0x0C */ f32   speed;        // m/s, updated by Car_Integrate
      /* 0x10 */ s16   surfaceType;  // index into gSurfaceTable
      /* 0x12 */ u8    unk12[0x6];
  } CarState; // size 0x18
  ```
- Every struct/type edit is gated: module hash, plus full ROM SHA if the header is shared.

### Comments
- **Every non-trivial function gets a one-line purpose comment above the definition**;
  logic-heavy functions get intent comments on branches/loops ("skip ghost cars",
  "wrap angle into [-PI, PI)"). Comments say *why/what for*, never restate the C.
- Magic numbers get a comment or a named constant (`#define MAX_RACERS 8`).
- Comments are codegen-neutral (cpp strips them) — they batch freely under one hash check.

### Matching-fragility rule
- IDO -O2 is source-line-sensitive; permuter winners can depend on exact line layout.
  When integrating a permuter win, keep its statement-per-line layout and mark it:
  `/* MATCH-SENSITIVE: line layout affects IDO scheduling — verify hash after any edit */`
  Scribe passes may rename/comment inside such functions but must re-verify the module
  hash after every edit batch; never bulk-reformat.

### CRITICAL: IDO codegen is source-line-sensitive — comments are NOT free
Verified 2026-07-08 while scribing `uvchannel_rom`: adding **3 comment lines** at
the top of a fully-matching module (shifting all code down 3 lines, no code
change) **broke the module hash**. IDO -O2 register allocation / scheduling here
depends on physical source line numbers. Therefore:
- A scribe pass that adds comment lines above/among functions **must pin line
  numbers** or it will silently un-match. The technique that works: put a
  `#line <original-line>` directive immediately before each compiled function's
  definition, so its body keeps the original numbering regardless of comments
  added above it. (`tools/decomp_helpers/` — see the uvchannel_rom scribe commit.)
- Struct-member and end-of-line comments that add **zero** net lines are free.
- Always re-gate the module hash after a scribe edit (full ROM SHA if a shared
  header changed). Never assume "just comments" is safe on this codebase.

### Review gate (per wave)
Before commit, an Opus-tier review of the wave's scribed diff checks:
1. names are justified by behavior (no speculative naming),
2. no `temp_/phi_/sp<hex>` locals remain,
3. every function has a purpose comment,
4. struct members added to headers, not duplicated locally,
5. hash/SHA gates all green.

## 4. Where the % goes from here

1496 module pragmas remain (~62% pragma-matched). The mechanical/permuter-convergent pool
is spent; the residue is struct-bound logic + regalloc near-misses. The v3 bet: **scribe →
context → seeds → permuter** compounds, whereas raw worker-hours on stale seeds do not
(moon1 proved it). Measure each wave by (banked fns) / (token+wall cost) and by base-score
distribution shift of the module's tail — if scribing a module doesn't drop its tail's
base scores, deprioritize that module.
