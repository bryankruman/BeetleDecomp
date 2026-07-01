# BAR HUD/menu decomp grind — resume state (updated 2026-07-01)

## Toolchain: UP + byte-verified (see also memory decomp-toolchain-wsl)
- WSL Ubuntu-24.04, clone `/home/brysl/projects/bar-decomp` (ext4). IDO 5.3+7.1, splat asm (7346 .s),
  daisybox+genForm0, `.venv`, baserom. `source .venv/bin/activate && make -j6` -> `...z64: OK` (sha e5ab4d22).

## Session result: +57 HUD/menu functions banked (byte-exact, committed)
- Commits on top of 31adf69: wave1 (+21), wave1b (+10), wave2 (+2), wave3 fix-loop r1 (+18), r2 (+6).
- HUD/menu unmatched: 448 -> 391. ~13% of the backlog (above the 7-10% agent baseline; the fix-loop is why).
- Every bank is DaisyBox-hash gated; full ROM rebuilds to sha e5ab4d22 after each wave.

## The reusable wave pipeline (scripts preserved in tools/decomp_helpers/grind/)
Driven from Windows git-bash calling `wsl.exe -d Ubuntu-24.04`; staging on /mnt/c/.../BeetleRecomp/.grind.
1. **gen_cards.py <maxsize> <mods|ALL>** — ledger -> per-function cards (target asm + m2c seed), stage headers.
2. **Seed wave (Sonnet 4.6, parallel workflow)** — one writer per function -> clean byte-matching C seed.
   Seed prompt MUST cover: export-table shims (member = unk<hexoffset> from `lw $t9,0xNN($t7)`, NEVER an
   invented name; global names from global_exports.h), uniquely-named inferred structs (suffix the addr),
   declare everything (module only sees common.h).
3. **consolidate2.py** — robust byte-gate/bank: parses multi-line typedef blocks, dedups decls by name,
   STRIPS decls already in common.h's header closure (avoids gGameSettings-type conflicts), swaps pragma,
   builds module .o, keeps iff hash passes. Then full build + sha.
4. **capture_builderr.py** -> **fix_wave (Sonnet, parallel workflow)** -> consolidate2 again.
   Feeds each non-compiling seed its EXACT compiler errors; agents repair. Round1 fixed 44/80 (banked 18),
   round2 banked 6. Cheap, high-yield — re-run until BUILDERR converges.
5. **iso_test.py** — sanity: tests each seed vs a CLEAN module to separate 'bad seed' from 'accumulation'.

## What remains (the real tail)
- **~43 NOMATCH** (compile OK, wrong bytes) in `nomatch.json` = the PERMUTER pool. Next step: import each
  into tools/decomp-permuter (permuter_settings.toml compiler_type=ido) seeded with its consolidated C,
  600s budget, parallel; integrate wins. This is compute (not token) bound and cracks regalloc/scheduling.
- **~30 stubborn BUILDERR** — need Opus-tier rewrites or hand attention (odd struct layouts, unusual ABI).
- **Larger functions** (size >200): gen_cards was run at <=200. Re-run gen_cards with a higher cap for the
  next tranche (selection/battle/med bulk).
- **Phase B readability (scribe):** matched functions already carry typed structs + one-line purpose comments.
  The remaining readability work is deep SYMBOL naming (func_XXXX/D_XXXX -> semantic) + centralizing the
  export structs into headers + commenting the framework (uvgfxmgr/uvsprt/uvfont/uvchannel viewport-scissor).
  Naming/comments are matching-safe but must be full-build gated (asm still references some symbols by name).

## Gotchas
- git-bash -> wsl.exe mangles inline $vars and heredoc backticks. Use literal paths; write scripts to /mnt/c
  and run by literal path; use quoted heredocs (<<'PYEOF') with no backticks.
- Commit banked matches in the WSL clone; push + bump the recomp submodule pointer (lib/bar-decomp) when ready.
