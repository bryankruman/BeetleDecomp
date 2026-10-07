# Beetle Adventure Racing: matching, readable C campaign

Research and source inspection: October 6, 2026. This extends STRATEGY_V3; completing
a ROM build alone does not mean the game has been decompiled.

## Outcome and acceptance

The goal is matching C for every original executable function, with justified function
names, descriptive locals, documented structures and short purpose comments. The original
USA ROM must remain byte identical. Assembly fallbacks, unresolved semantic names and
unreviewed generated C remain unfinished work. Do not replace an assembly function with
an inline assembly string, a byte array or a success-reporting stub to inflate progress.

Maintain three separate gates: exact machine code and relocations; integration/module
packing and full ROM bytes; readability and evidenced semantics. A low permuter score,
successful compilation, plausible pseudocode or a visually working PC recomp passes none
of those gates by itself.

## Current source and external progress

The authoritative source is `/home/brysl/projects/bar-decomp` in Ubuntu-24.04, rather than
the Windows staging directory or the recomp's older decomp submodule. The previous baseline
was `8deada2`. The reviewed [upstream decomp](https://github.com/synamaxmusic/bar-decomp)
integration through `e0112bf` is now committed, with the original baseline preserved on
`pre-verified-upstream-20261006`. Upstream history is retained. The original USA ROM SHA-1
`e5ab4d226c08d22f68a2edcc48870203e67454b8` and all 133 packed-module SHA-256 checks passed
in isolated pve CT 105. All 1,013 reviewed local source files matched the worker snapshot.
The integration recovered 225 ordinary assembly placeholders and repaired shared export
types, module discovery, explicit map parsing and validated kernel aliases. Strict linker
failures remain; no failed link is hidden with upstream's copy fallback.

Four further functions were implemented, named and commented, then passed their independent
packed-module checks and original full ROM check after symbol extraction:
`airecRunLegacyCountLoop`, `smackGetPlayerValue`, `miscVec2LengthSquared`, and
`uvIsectGetKindOnePayload`. Their names describe observed behavior without inventing an
unknown gameplay meaning. Commit `76a2c9b` records this wave. Source locations of existing
matching C are preserved with `#line`. The current ledger has **1,147** assembly references:
**1,085** ordinary functions and **62** entrypoints, with **819,608** known instruction bytes
and no unknown sizes. The broader name audit still finds **1,360** address-named C definitions.
This is not a completed decompilation or completed readability audit.

Two further accepted waves recover nine functions. Commit `06bf51c` implements
`miscVec2Length`, `miscVec2TransformInPlace`, `uvIsectCopyRecord`,
`uvTerraSetStaticObjectValue` and `uvTerraGetStaticObject`, and repairs the typed
model-ID/value getters. Commit `8c7f0f4` implements restart, continue, quit and
new-track pause confirmation callbacks; original callback-table and localized-text
references establish their purposes. Every wave passed extraction, all original
packed-module hashes and the original full ROM hash after names/comments were applied.
All 1,013 local source hashes agreed with the validated worker source before landing.
The authoritative and integration branches both contain these commits.

Commit `838a024` adds `envPrependRecord`, `uvIsectAppendUniqueValue`,
`aiFindActiveRecordByKey` and `uvIsectFindNearestBoxSide`. Commit `ff53b8e` adds
`motionUnloadModulesAndStopEmitters`, `caranimUnloadEffectModules`,
`uvIsectSetQueryParameterBank` and `track4SetEnvironmentTint`. Shared export types
are reused where available; opaque values retain bounded descriptions. Each wave
passed real-translation-unit instruction/relocation checks, original packed module
hashes and original full ROM SHA-1 after names/comments and extraction. All 1,013
local source hashes agreed with the worker before landing. Twenty-one additional
functions have been recovered after the upstream integration.

The context-assisted m2c experiment generated 412 unaccepted small-function seeds.
341 produced output, but the initial marker-only filter admitted invalid void-field
accesses and `M2C_ERROR` macros. The reported 147 marker-free outputs are therefore
not 147 compilable or accepted functions. Review assembly, repair actual types and
compile each candidate in its real translation unit. The accepted eight functions
above were individually repaired and reviewed through that process.



The latest upstream increment comprised nine commits beyond the first `695461f` snapshot,
227 commits absent from the original baseline. Its explosion module and dependencies were
integrated after preserving local matching C. Frozen input archives remain unchanged;
later guarded worker waves carry source corrections and retain before-change backups.

Read-only GitHub comparisons covered all default and feature branches of inspectredc,
gcsmith, Hodapp87, queueRAM and LLONSIT-glitch. None had commits ahead of upstream main.
This avoids spending time importing stale branches. [bar-notes](https://github.com/synamaxmusic/bar-notes)
documents UltraVision's FORM chunks and module/file directory. Its tentative addresses and
unknown fields remain hypotheses until confirmed against the ROM and parser. Asset viewers are supporting format evidence,
not additional matching game C. Recheck branches at a later campaign checkpoint, rather
than polling GitHub for every function. Keep author attribution and upstream provenance.
Upstream does not accept AI contributions: carry this AI-assisted work in Bryan's fork.

The upstream-linked [BAR-Recomp](https://github.com/synamaxmusic/bar-recomp) default branch
contains documentation/media and five commits, with no public matching-C source to import
in the inspected tree. Daniel's recomp renderer/input work supplies useful behavior and
format evidence, but static generated C is not an additional matching decomp implementation.

The old progress script excludes module entrypoints and estimates C definitions heuristically.
Use `tools/completion_ledger.py` to list all assembly references, include entrypoints, count
known remaining instruction bytes, and expose missing size data. No mixed-denominator
percentage should be reported. Its address-name scan is an audit queue, not proof that
other names/comments are good. Eventually cross-check the ledger against original function
boundaries in the linked objects and symbol maps.
The name audit now includes recovered entrypoints and permits meaningful `func_*`
names. Its isolated fixture covers direct/macro entrypoint definitions, a meaningful
function name, absent assembly and commented pragmas. The updated candidate has 1,360
address-named C definitions under that broader audit, not the earlier narrower count.

## Research that changes the workflow

[HELIOS](https://arxiv.org/html/2601.14598v2) provides control-flow and call-graph structure
alongside raw decompiler output, with compiler feedback. Its experiments include MIPS;
the high compilation rates do not establish exact N64/IDO binary matching. Apply the
structural context idea: describe basic blocks, branch successors and relevant callees
explicitly instead of asking a model to infer all of them from isolated text.

[AutoDecompiler](https://arxiv.org/html/2606.16162v2) uses repeated compilation, execution
and input/output feedback instead of a single generated answer. This supports separate
diagnostics for syntax, semantics and code generation, and retaining the best known
candidate. Its reported behavioral improvements do not prove matching BAR code.

[CHISEL](https://arxiv.org/html/2608.27981v1) combines compiler feedback, differential
fuzzing and remembered divergence. Its benchmark is 120 x86-64 functions with Gemma4,
not this MIPS game. Treat its false acceptance results as a reason to keep an independent
byte gate. Differential harnesses are useful for pure math, decompression and state update
functions when their dependencies can be controlled; they supplement exact matching.

[m2c's own documentation](https://github.com/matt-kempster/m2c) supports multiple context
inputs and explicit stack-layout declarations. Correct inferred stack types and layouts
before asking the model for another source form. Use the project's original compiler and
flags, not a host compiler's optimization assumptions.

[decomp-permuter](https://github.com/simonlindholm/decomp-permuter) is a last-mile search
tool. Its score can ignore stack differences. An output scoring zero must still compile
inside the real source module and pass all packed-module/ROM gates. Never bank a winner
by copying expanded context or accepting an isolated object alone.

The [OoT IDO 5.3 -O2 guide](https://github.com/n64decomp/oot/blob/master/docs/guides/-O2%20decompilation%20(for%20IDO%205.3).md)
orders work from data layout and control-flow blocks through scheduling to register allocation.
Use that order when a seed is structurally wrong; small source layout changes can affect IDO
scheduling, so a host compiler's output is not a substitute.

[N64 Decomp Workbench](https://github.com/akratch/n64-decomp-workbench) provides relocation-aware
full-translation-unit comparison, stale-build guards and bounded-search triage. Evaluate its
ordinary object comparison on BAR fixtures before adoption. Its instrumented optimizer profiles
accept one pinned IDO 5.3 source revision; BAR's compiler compatibility is not yet established.
Escalate a demonstrably improving plateau to pass traces rather than spending another identical
search budget. Keep the packed-module and ROM checks as the final authority.

## Model routing and prompt contract

The inspected [official GPT-6 guidance](https://developers.openai.com/api/docs/guides/latest-model)
lists Astra for the hardest reasoning, GPT-6.1 Sol for balanced complex work and Luna for
focused volume work. It supports reasoning with tools through Responses and advises
evaluating model choices on the actual workload. The following routing is a campaign
design inference, not an N64 benchmark result: Astra for shared type recovery, difficult
control flow and plateau diagnosis; Sol/GPT-6 for grounded candidate implementation and
readability edits. Compare accepted matching bytes per cost on representative BAR functions.

[Claude Fable 5.1](https://www.anthropic.com/claude-fable-and-mythos-5-1) is Anthropic's
generally available coding model. Its [official prompting guide](https://platform.claude.com/docs/en/build-with-claude/prompt-engineering/prompting-claude-fable-5-1)
recommends starting at high effort and measuring gains before raising it. Use Fable for the same
grounded source/type work and independent candidate review, then compare actual BAR acceptance
results with Astra and GPT-6. Its published agentic results do not establish N64/IDO matching.
If an API harness is later authorized, retain returned thinking blocks unchanged in their exact
conversation and batch independent tool results before advancing the loop. Ask for patches and
concise evidence notes, not private reasoning transcripts. Preserve campaign state through
compaction: source/compiler hashes, best candidates, failed attempts, acceptance logs and scope.

Build a held-out set spanning tiny wrappers, branches, loops, float-heavy code, indirect exports
and large state machines. Run every model with the same target, type context and CPU budget.
Measure real-module matches, accepted instruction bytes, clean-name/comment coverage, model
cost and compiler/search time separately. Disqualify fake matches and stale outputs. Route by
observed BAR results rather than vendor rankings, and retain unsuccessful attempts so no model
receives an easier target or repeated free hints.

Each function task packet contains: original assembly and address/size; exact IDO version,
flags and file-level compiler settings; relevant callers/callees and export-table slots;
bounded header/type context with known sizes/offsets; original constant and string references;
current candidate and compiler diagnostics; the actual instruction/relocation/stack diff;
previous attempts and the reason each failed; the allowed source file and acceptance commands.

Ask the model for a patch and an evidence note. Each proposed name records its evidence
(callsite, export table, string, SDK analogue or observed behavior) and confidence. Unknown
fields stay `unkXX` with known offsets until evidence supports a stronger name. Do not turn
an attractive guess into an authoritative API name. Require explicit coverage of signedness,
delay slots, endianness, float constants, aliasing, stack locals and callback prototypes.

Keep reusable compiler/type context before varying per-function diagnostics in prompts.
Cache the context by source/header/toolchain hashes; invalidate it when types change. Avoid
embedding whole repositories or ROM images in prompts. Do not create a model API bill or
copy API credentials to fleet machines merely to start the compiler campaign.

## Execution sequence

1. Verify baseline and resolved upstream candidate on the isolated pve worker, using identical
   original ROM and pinned Python/compiler inputs. If baseline fails, repair the worker/tool
   environment first. If only the candidate fails, localize to the first compile/module error.
   Only then update the authoritative branch and the recomp's decomp dependency.
2. Audit pre-existing zero-score wins and transfer failures against the updated symbols/types.
   Attach source, target object, compiler settings and hashes to each record. Reuse genuine
   matches before generating more seeds; discard a stale claim, never the original evidence.
3. Recover shared structures and export-table prototypes for a small dependency cluster.
   Prioritize loaders, memory/file utilities and engine types that reduce many downstream
   errors. Finish near-complete modules before attacking the largest racing/physics functions.
4. Generate m2c with current context, then reason from CFG and calls. Compile immediately.
   Wrong branch structure, return type, object layout or instruction family goes back to
   type/source repair. Do not spend permuter CPU on a structurally wrong candidate.
5. For near matches, use the existing V3 score gate (base under 400) and 300/900/1,800-second
   ladder on pve, with at most two re-hunts from a materially improved seed. Preserve failed
   zero outputs for transfer diagnosis. Stop on no progress and record the first discriminating
   diff instead of restarting identical searches.
6. Integrate one module at a time. Compile in its real translation unit, require that exact
   packed module's SHA-256, then require the original full ROM SHA-1 before banking a wave.
   Rebuild an affected module rather than trusting a previous log or swallowing checker errors.
7. Perform readability work in the same wave: one purpose comment, descriptive locals, shared
   types instead of opaque pointer arithmetic where supported, and justified semantic names.
   BAR's IDO output is sensitive to source line positions. Preserve original compiler locations
   with `#line` around changed definitions as documented in V3, and rerun the module/ROM gates
   after cosmetic changes. Do not assume comments are code-generation neutral.
8. Repeat until all executable assembly references are eliminated. Independently audit every
   function's name, purpose and structure, and validate original boundary coverage so missing
   declarations cannot masquerade as completion. Final success requires a fresh matching build,
   zero unfinished function records and completed readability review, including entrypoints.

## Compute and state protection

pve's approved isolated CT 105 is `beetle-worker`, 10.0.10.70, unprivileged, capped at four
CPU threads, 8 GiB RAM, 32 GiB disk and no autostart. Existing guests and hypervisor packages
are outside the campaign. All substantial builds and searches belong there. Skytech handles
source review and small single-file diagnostics. The private payload contains the user's
ROM solely for local fleet matching; do not commit it, generated assets, raw code snapshots
or credentials to public repositories.

The user approved the initial snapshot builds and, with the explicit `w1-a - W2` reply,
approved a scoped build exception for CT 105 under `/opt/beetle-campaign-20261006`,
`/opt/beetle-recomp-review-20261006` and `/opt/beetle-recomp-fix-20261006`. It covers frozen
retries, guarded source/tool transfers, isolated candidate trials, builds/hash checks and
bounded searches. It excludes package installation, resource/network/security changes,
guest restarts/deletion, other guests/hypervisor, publishing, paid APIs and credentials.
Keep four-thread/8-GiB limits, accepted-source hashes, backups and job logs. Stop and
diagnose unexpected errors before continuing within scope. The exception ends at task
completion or revocation and does not change NetworkOps rules for unrelated operations.

## Completion reporting

Report accepted ordinary functions, entrypoints, matching code bytes, readability debt and
full ROM gate separately. Record source/tool hashes and build result with each accepted wave.
"ROM matches" means the retained assembly and compiled C reproduce the original. "All code
complete" means every original executable function is recovered in reviewed, readable C.
Do not announce the latter while a source ledger, byte gate or semantic audit remains open.


## Accepted readable checkpoint through 2a354512

Thirty-three further functions are now accepted after the 225 upstream ordinary
function imports. Commit `c36d19e` adds nine named helpers for angle folding,
selection callbacks, victory/track cleanup, trigger transforms, texture panels and
motion voices. Commit `b671b243` adds `menuslctDrawBottomLabel` and
`uvFoldAngleRadians`. Commit `2a354512` adds `aiBuildOrthonormalBasisFromX`.
The matrix helper preserves translation and W values while constructing and
normalizing the three axes in the original cross-product order.

All accepted functions pass real-translation-unit instruction and relocation
comparison, original affected packed-module hashes and the complete USA ROM SHA-1
`e5ab4d226c08d22f68a2edcc48870203e67454b8` after names/comments and extraction.
All 1,013 source hashes agree with the worker before each landing. Proofs are in
`/opt/beetle-campaign-20261006/accepted-typed-readable`, `accepted-label-fold`
and `accepted-orientation-x`. The radians fold has 112 actual instruction bytes;
the ELF's extra four zero bytes are module alignment, independently preserved by
the packed-module and complete ROM checks rather than artificial padding in C.

Historical ledger at 2a354512: 1,167 assembly references = 1,105 ordinary + 62 entrypoints;
821,732 known remaining instruction bytes; zero unknown sizes; 1,360 address-named
C definitions still require semantic review. This is partial decompilation.

Typed export context v2 produced 404 tasks and 394 outputs. The 197 marker-free
outputs include invalid opaque-pointer field accesses and are not accepted C.
Real translation-unit diagnostics covered 180 ordinary seeds in two batches;
near matches remain diagnostic until independently repaired and ROM validated.
Repair shared types and ABI layouts before spending bounded permuter time.

Companion recomp integration is committed locally in `37d8993`. Full Linux and
Windows builds pass. A startup race was repaired by initializing the current and
next VI framebuffer before spawning worker threads, under the shared VI mutex.
Five repeated fresh boot captures pass; a 190-second audio-enabled driving run
reached 111 km/h, rendered pause and preserved the existing 32 KiB Pak hash.
Broader release gameplay gates remain open. No public push or paid API was used.


## Current accepted checkpoint through c9e39853

Fifty-three further readable functions are accepted after the 225 upstream ordinary
imports. Since the 33-function checkpoint, commits `3d4b9af`, `db46ec4`, `655354d`,
`10a45f2` and `38a10a9` recover fixed-position car sound initialization, editor record
and GUI reset, three radians helpers and seven editor selected-record scalar callbacks.
Commit `f64db103` corrects the incomplete tile struct tag and UVCT/UVTR size comments;
actual GCC/IDO ABI assertions and the original ROM validate the layouts. Unknown scalar
meanings stay explicitly unknown; no rotation/scale interpretation is guessed.

Commits `cefff225` and `c9e39853` recover seven GUI allocation/active-change helpers.
Their typed slot sizes and active fields come from original strides and load/store
offsets. Five original allocators return capacity and write one slot beyond the pool
on exhaustion; preserve and document this original behavior in matching C. The eight-slot
0x5C allocator instead returns -1 without writing when full. Callers are through module
exports; a direct-call search found no direct C/assembly calls and does not establish
reachability of exhaustion. Recomp mitigation requires a separate caller/export audit
and sentinel handling, not a blind allocator return change. The matching decompilation
must remain byte identical.

Current ledger: 1,147 assembly references = 1,085 ordinary + 62 entrypoints;
819,608 known remaining instruction bytes; zero unknown sizes; 1,360 address-named C
definitions still need semantic review. This remains partial decompilation.
Every accepted wave passes real-translation-unit instruction and relocation comparison,
original affected packed-module hashes, complete USA ROM SHA-1
`e5ab4d226c08d22f68a2edcc48870203e67454b8`, and 1,013 local/worker source hashes.
Proof directories include `accepted-audio-fixed-position`, `accepted-ted-record`,
`accepted-radian-helpers`, `accepted-asset-header`, `accepted-ted-gui-state`,
`accepted-ted-selected-scalars`, `accepted-gui-pool-allocation` and
`accepted-gui-bounded-callback` under `/opt/beetle-campaign-20261006`.

The function comparator now records the assembly's declared instruction boundary and
separates verified zero ELF alignment from instructions. It requires the instruction
count to equal that boundary and original alignment bytes to be zero. Full relocations,
packed modules and complete ROM remain mandatory; no artificial padding is added to C.
This distinguishes the editor GUI reset's 348 instruction bytes from eight alignment
bytes. Its record-reset caller now has the actual one-argument ABI and all 100 original
instruction bytes still match.

Unaccepted trials remain diagnostics: film transition copies, orientation Y and GUI
pool initialization loops. The isolated film-circle permuter search ended after its
300-second/four-worker bound: initial score 140, best 25, no exact match. The clean
existing permuter was copied at `ec2efeebb33e2b1de81e39fbf7cbe3cd97350472` with file
provenance, no new packages or network search sharing. No paid API run is claimed.
Continue shared-type recovery and compiler-guided clean loop repairs before new searches.
