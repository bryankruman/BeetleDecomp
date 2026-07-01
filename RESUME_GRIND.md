# BAR HUD/menu decomp grind — resume state (updated 2026-07-01, session 2)

## Toolchain: UP + byte-verified in WSL Ubuntu-24.04 (/home/brysl/projects/bar-decomp)
IDO 5.3+7.1, splat asm, daisybox, .venv, baserom. `source .venv/bin/activate && make -j6` -> sha e5ab4d22.

## Result so far: +80 HUD/menu functions banked (byte-exact, committed)
- HUD/menu unmatched: 448 -> 368 (~18%, well above the 7-10% agent baseline).
- Every bank DaisyBox-hash gated; full ROM rebuilds to sha e5ab4d22 after each wave.

## The multi-engine wave pipeline (scripts in tools/decomp_helpers/grind/ + recomp .grind/)
Run in parallel: WSL permuter (CPU) + cloud Sonnet/Opus agent waves (no contention). DEFER consolidates
until the permuter finishes (or kill a tapered permuter) to avoid CPU thrash.
1. gen_cards.py <max> <mods|ALL> <min> -> asm+m2c cards for a size band.
2. Sonnet seed wave (seed_wave2 workflow) -> byte-matching C seeds (export shims = unk<hexoffset>, unique struct names).
3. consolidate2.py -> robust header-aware DaisyBox-hash byte-gate/bank. (Filter output with grep can drop it;
   re-run without the filter if the banked line is missing.)
4. capture_builderr.py -> fix_wave (Sonnet, then escalate to fix_wave_opus with model:opus) -> re-consolidate.
5. permute_campaign.py <timeout> <concurrent> <jobs> -> imports each NOMATCH seed, permutes in parallel,
   saves score-0 wins to .grind/wins/. Integrate by copying wins -> seeds then consolidate2.
   NOTE: ~50% of permuter score-0 wins integrate (the win's match can depend on the flattened import
   context / instruction scheduling that doesn't transfer to the module build). The simpler wins bank.

## Yield by lever (empirical, this session)
- Sonnet seed wave (<=200): ~25% direct. Fix-loop (Sonnet, given exact compiler error): +24 recovered.
- 200-350 tranche: lower (~+12 with fix-loop). 350-500: ~+5. -> yield falls with function size.
- Permuter (300s): ~12 score-0 wins across pools, ~half integrate (banked ~6).
- Opus fix-loop on stubborn BUILDERR: fixes compiles but they mostly NOMATCH (byte-match still eludes).

## HARD TAIL (368 remaining) — the levers that still pay
- **Longer permuter budgets (600s+)** on the NOMATCH pool (nomatch.json) — compute-bound, cracks higher
  base scores. This is the main remaining matching lever.
- **Larger/untried functions** (>500 bytes) via gen_cards + seed wave — low but nonzero yield.
- **Per-function Opus + permuter** on specific high-value functions (e.g. the letterbox cam.c writers).
- **Phase B scribe**: the 80 banked functions already have typed structs + purpose comments; deep symbol
  naming (func_XXXX/D_XXXX -> semantic) + framework commenting is the remaining readability pass.

## Gotchas
- git-bash -> wsl.exe mangles inline $vars and heredoc backticks. Use literal paths / quoted heredocs / write files to /mnt/c and run by literal path.
- Consolidating WHILE a permuter runs works but thrashes 24 cores (both compile). Prefer: kill a tapered permuter, consolidate clean, relaunch permuter with a longer budget.
- Commits are local in the WSL clone; push + bump the recomp submodule pointer (lib/bar-decomp) when ready.
