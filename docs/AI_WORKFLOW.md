# AI‑assisted matching workflow

The operational loop for decompiling functions with LLMs, with a **model‑tiered** write→review design.
Strategy/context lives in [`DECOMP_PLAN.md`](DECOMP_PLAN.md).

## Principle

Matching decompilation is uniquely safe for AI assistance because success is **objective**: the
compiled bytes either equal the target or they don't (`objdiff`/`asm-differ` score 0). So we let
cheap models do the high‑volume writing, gate every result on the byte‑exact diff, and use an
expensive model only for the hard tail and a quality audit. **No result merges without a verified
byte‑exact match — regardless of which model produced it.**

## The pipeline (per function)

```
score_functions.py  →  m2c (seed)  →  [WRITER MODEL]  →  compile  →  objdiff/diff.py
                                          ↑                               │ score 0?
                                          └──────── permuter ←── no ──────┤
                                                                          │ yes
                                                                  [REVIEW MODEL] → name/type → commit
```

1. **Select** — `python3 score_functions.py` → take the lowest‑score (easiest) unclaimed function.
2. **Seed** — run `m2c` on the target `.s` to get a first‑pass C approximation (include it in the
   writer prompt).
3. **Write** — writer model produces candidate C using the target asm + m2c seed + nearby context
   (headers, sibling functions, known structs).
4. **Compile & diff** — build just this object; score with `objdiff` (preferred, scriptable) or
   `./diff.py -mwo <Func>`.
5. **Permute** — if close but not 0, run `decomp-permuter` seeded with the model's code (this is where
   AI + permuter shines — empirically the biggest booster).
6. **Escalate or accept** — see thresholds below.
7. **Review** — review model audits the verified match (below).
8. **Name & type, verify, commit** — `scripts/check.sh --module <m>` then commit.

## Model tiers

| Tier | Models | Use for |
|---|---|---|
| **Writer (default)** | **Haiku 4.5**, **Sonnet 4.6** | leaf/tiny/small/no‑float functions — the high‑volume majority |
| **Writer (hard)** | **Opus 4.8+** | float‑using, large (≥80 insn), or anything the default tier fails |
| **Reviewer** | **Opus 4.8+** | audit every accepted match for correctness, types, readability |

Rationale: a mid‑tier model lands ~74% of functions in this exact pipeline (88% deterministic across
runs). Spend Opus where it pays: the ~26% hard tail and the review pass.

### Escalation thresholds (from empirical data)
- **Attempt budget:** ≤12 compile/diff attempts per function for the writer tier.
- **Early‑escalation rule:** if not matched by **attempt 3**, the odds of *that tier* ever matching
  drop to ~25%. So: not matched in 3 → hand to permuter; still failing → escalate Haiku→Sonnet→Opus.
- **Hard‑class shortcut:** route float‑using or ≥80‑instruction functions straight to Opus (skip the
  cheap tier) — the scorer flags these.
- **Park‑it rule:** if Opus + permuter fail after the budget, mark the function `// MATCH: parked`
  with notes and move on; revisit in Phase 3 with more context (siblings often unlock it).

## The review (audit) pass — what Opus checks

A byte‑match is necessary but not sufficient. The reviewer confirms:
- **Genuine match**, not a permuter artifact that hits bytes via nonsense (weird casts, dead vars,
  implausible control flow). If it "matches" but couldn't plausibly be the original source, flag it.
- **Types & signatures** are sensible (args, return, struct usage) and consistent with callers.
- **Names** — `func_*`/`D_*` replaced with meaningful identifiers; consistent with the `uv` engine
  conventions.
- **No collateral risk** — type/struct changes didn't silently rely on layout coincidences.
- Re‑runs `scripts/check.sh` to confirm still‑matching after any naming/typing edits.

## Running it in Claude Code (orchestration)

The loop maps cleanly onto subagents with per‑call model overrides:

- **Driver** (you/Opus): reads `score_functions.json`, dispatches a batch of N easy functions.
- **Writer subagents** (`model: haiku` or `sonnet`): one per function — given the `.s`, m2c seed, and
  context; they iterate compile→diff until score 0 or budget; return the matched C + final diff score.
- **Reviewer subagent** (`model: opus`): audits a completed batch's matches, returns approve/needs‑work
  per function.
- **Checkpoint:** after each batch, `scripts/check.sh --module <m>` (fast) then a full
  `scripts/check.sh` before committing the batch.

Batch the cheap writes, then do **one** review + **one** checkpoint per chunk — that's the efficient
cadence (don't full‑build per function).

### Guardrails
- The diff gate is mandatory and tier‑independent. CI/`check.sh` must show `…z64: OK`.
- Never commit a parked/non‑matching function as if it matched.
- Prefer readability; reject byte‑matches that are unreadable when a clean equivalent also matches.
- Keep commits small and per‑function/per‑module for easy bisection if a later change regresses.

## Tools referenced
- **m2c** — MIPS→C first pass (seed).
- **objdiff** — local object differ (scriptable, scoped) — preferred for automated scoring.
- **asm-differ** (`./diff.py`) — interactive diff, good for humans.
- **decomp-permuter** — randomized permutation search; strongest when seeded with AI output.
- **score_functions.py** — difficulty ranker / model‑tier router.
- **scripts/check.sh**, **tools/progress.py** — verification + progress.
