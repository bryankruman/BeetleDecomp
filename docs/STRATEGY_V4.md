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
matching C are preserved with `#line`. The current ledger has **1,033** assembly references:
**972** ordinary functions and **61** entrypoints, with **803,424** known instruction bytes
and no unknown sizes. The broader name audit still finds **1,304** address-named C definitions.
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


## Historical accepted checkpoint through c9e39853

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

Historical ledger at c9e39853: 1,147 assembly references = 1,085 ordinary + 62 entrypoints;
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


## Historical accepted checkpoint through f5ea3a1a

Seventy-one further readable functions are accepted after the 225 upstream ordinary
imports. Since the 53-function checkpoint, `8ad897ee` adds the correctly promoted
variadic GUI field-0x62 setter. The complete target layout and field purpose remain
unknown; the prefix view does not claim an unsupported widget type.

Intersection commits `a7288caf`, `e5f923e2`, `3cd2a862` and `4ccc3075` add thirteen
functions: value/attribute access, pending-record insertion, lower-value record
replacement, indexed query pairs, unique-value insertion, matrix property access,
value/large record initialization and vector/scalar properties. The comparison value
at 0x2C is not assumed to be distance. The value record allocation is 0x348 bytes;
field offsets alone must not be mistaken for complete array capacities. The large
record is 0xF14 bytes and initializes forty links with stride 0x58. Explicit original
16-bit iteration matches without artificial stack padding. Vector property setting
uses a Vec3F by-value aggregate, preserving the original ABI without assuming that
separate named float parameters form a portable contiguous vector.

Commit `f5ea3a1a` adds four dynamic-object vector/callback helpers. Shared prefix views
cover observed vector/scalar fields and the parameter flag. The optional callback
is loaded once and receives the original 12-byte request (value, -1, zero, result 1),
then returns the callback's 16-bit result. No gameplay meaning is guessed for its
opaque request fields or vector/scalar parameters.

Historical ledger at f5ea3a1a: 1,129 assembly references = 1,067 ordinary + 62 entrypoints;
817,836 known remaining instruction bytes; zero unknown sizes; 1,360 address-named
C definitions still require semantic review. This remains partial decompilation.
All accepted waves pass exact real-translation-unit instructions/relocations,
original affected packed-module hashes, the complete USA ROM SHA-1
`e5ab4d226c08d22f68a2edcc48870203e67454b8` and all 1,013 local/worker source hashes.
Evidence under `/opt/beetle-campaign-20261006`: `accepted-gui-field62-props`,
`accepted-isect-record-helpers`, `accepted-isect-transform-allocation`,
`accepted-isect-large-record`, `accepted-isect-properties`, `accepted-dyn-vector-callbacks`.

Unaccepted near matches include paired-vector output (two stack-offset differences)
and value-registry removal (four instruction differences in its best readable form).
GUI reset/property-switch and earlier orientation/film trials remain diagnostic.
No inline assembly, dummy stack padding, success stubs or nonmatching candidates
were accepted. Continue coherent typed helper clusters and retain all three gates.

Original intersection routines include inclusive count/index bounds, missing negative
index checks, unchecked insertion/registry capacity and unchecked allocation results.
Matching recovery preserves and comments these behaviors. Whether gameplay callers
can violate their contracts is not established. Group their eventual recomp review
with the original GUI exhaustion hazard; do not blindly change return sentinels,
array capacities or allocation handling without tracing export callers.


## Historical accepted checkpoint — 100 further readable functions

Source checkpoint `acb1153965dca47b233d0830034830a233a0211d` contains one hundred
further readable, named and commented functions after the 225 upstream ordinary
assembly imports. Six existing C functions also received semantic/type cleanup;
these are counted separately and do not inflate the assembly recovery count.

Since the 71-function checkpoint, twenty-nine newly recovered dynamic-object helpers
cover linked/secondary collection membership, secondary companion-state copying,
node reset, relative transforms, one-time secondary updates, DOBJ handle propagation,
attachment membership, scalar/matrix properties, secondary registry removal, four
registry passes, collection creation and work-buffer allocation. Five existing callback
wrappers and one collection-update wrapper received grounded names, types and comments.
Unknown gameplay meanings remain explicit in field names and purpose comments.

The complete collection layout is grounded in the original 0xF7A4-byte allocation.
The word at 0x94 is a member count, not a kind field. The active-collection registry
is established by the original property-zero setter. Secondary state registry removal
does not free the state. Original independent 16-bit scan/shift indices, count reloads,
unsigned kind-to-float conversions, in-place matrix order and callback context words
are preserved. Callback context words have not been guessed to be pointers.

Historical ledger at acb11539: 1,100 assembly references = 1,038 ordinary + 62 entrypoints;
813,444 known remaining instruction bytes; zero unknown sizes; 1,354 address-named
C definitions still require semantic review. This remains partial decompilation.
Exact machine-code matching does not establish complete readable C while assembly
fallbacks remain. Completion still requires zero unresolved assembly fallbacks and
a complete names/types/comments audit, with the original ROM continuing to match.

Every accepted wave passed real-translation-unit instruction and relocation checks,
the affected original packed-module hash, original USA ROM SHA-1
`e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 local/worker source hashes
after naming, comments and symbol extraction. Evidence under the approved pve campaign
directory includes `accepted-dyn-associations`, `accepted-dyn-secondary-state`,
`accepted-dyn-reset-callbacks`, `accepted-dyn-matrix-helpers`,
`accepted-dyn-secondary-update`, `accepted-dyn-render-attachments`,
`accepted-dyn-secondary-cluster` and `accepted-dyn-collection-utilities`.
Failed independent trial contexts and extraction retries remain recorded; no failing
candidate was accepted and no success fallback or artificial stack padding was added.

Original attachment reassignment calls a helper that only scans old membership;
the old list is not modified. Original collection initialization omits allocation
failure/capacity checks and would overwrite work-buffer pointers if repeated.
Whether gameplay callers violate those contracts is not established. Preserve them
in matching decompilation and group their eventual caller/export audit with the
previous GUI exhaustion and intersection bounds/capacity findings. A runtime fix
requires demonstrated reachability and a separate recomp patch; no speculative
fidelity-changing source edit is accepted here.

Continue coherent clusters with shared evidenced types, then recover their larger
consumers. Near matches remain diagnostics: node vector accumulation still differs
in four stack-frame instructions; paired intersection vector output differs in two
stack offsets; the older intersection registry-removal candidate differs in four
instructions. Readable exact matches take precedence over unbounded syntactic search.


## Historical accepted checkpoint — 111 further readable functions

Executable checkpoint `9446e5e0509af0a5a4f4b42bc0f64f184a3507f7` contains 111 further
readable, named and commented functions after the 225 upstream ordinary assembly
imports. Eighteen existing C functions have separately counted semantic/type cleanup.
Since checkpoint 100, eleven new dynamic-object functions cover node companion-state
preparation, two indexed parameter outputs, an attachment callback, indexed collection
output, five registry lifecycle helpers and point-pair sphere construction. Twelve
existing helpers now have grounded names/types/comments for module cleanup, shared
scalar properties/address, node-registry initialization, linked collection/attachment
access, DOBJ handles, opaque word 0x2C and first parameter-bank count.

Historical ledger at 9446e5e0: 1,089 assembly references = 1,027 ordinary + 62 entrypoints;
811,304 known remaining instruction bytes; zero unknown sizes; 1,342 address-named
C definitions still need semantic review. Full readable decompilation remains incomplete.
Every accepted wave passes exact real-translation-unit instructions and relocation
records at their instruction offsets, original affected packed-module bytes, complete
USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 reviewed
local/worker source hashes after names/comments and extraction.

The collection destructor emits two independent HI/LO relocation pairs in a different
object-table order. Each pair remains intact and every offset/type/target/value/addend
record is identical. The final original packed module and complete ROM are byte-identical;
no comparator requirement or linker failure was suppressed to accept it.

Evidence under `/opt/beetle-campaign-20261006`: `accepted-dyn-node-prepare`,
`accepted-dyn-parameter-outputs`, `accepted-dyn-indexed-entry`,
`accepted-dyn-registry-lifecycle`, and `accepted-dyn-semantic-helpers`.
The four-byte collection output is retained as an opaque aggregate, not guessed to
be a floating-point value. Original parameter output payloads reload after callbacks.
Attachment construction allocates 0x270 bytes; secondary state allocates 0x1A8 bytes,
with two identity matrices and explicit scalar 0x134 clearing. Registry unregister
helpers do not free their states. Collection destruction makes no explicit work-buffer
frees; allocator ownership and actual caller lifecycle still require investigation.

The original attachment getter uses an inclusive count/index comparison and has no
negative-index check. Matching recovery preserves and comments that contract. Group
its eventual caller/export audit with previous GUI/intersection/attachment findings;
do not change sentinels, bounds or ownership based on unproven gameplay reachability.

Unaccepted bounded trials remain diagnostic: collection active-property setter has
register-allocation differences despite equal size; range length has three instruction
differences; point-pair containment has floating-point scheduling/spill differences.
No inferred float type, invented stack padding, unsupported API parameter, nonmatching
candidate or success stub was accepted. Continue coherent evidenced helper/consumer
clusters and separately reduce semantic debt in existing C.


## Historical accepted checkpoint — 118 further readable functions

Executable checkpoint `2b887ab9b469a3d306df85907a2d03b7b768ad26` contains 118 further
readable, named and commented recoveries after 225 upstream ordinary function imports.
Eighteen existing C semantic/type cleanups remain separately counted. Since checkpoint
111, seven new functions cover two callback-gated lower-positive record acceptors,
secondary vector output, node translation-vector update, node creation, secondary
vector input and attachment delta preparation/callback. All seven pass exact real-unit
instruction bytes and relocation records, original packed dynamic-module bytes,
complete USA ROM SHA-1 and 1,013 matching local/worker source hashes after naming.

Historical ledger at 2b887ab9b: 1,082 assembly references = 1,020 ordinary + 62 entrypoints;
809,412 known remaining instruction bytes; zero unknown sizes; 1,342 address-named
C definitions still need semantic review. Full readable decompilation is incomplete.

The record acceptors use the lowercase isct module's 88-byte copy, allow callback
rejection and reload the record value after callback mutation without rechecking
eligibility. Negative callback values bypass the attachment callback. Their scalar's
gameplay meaning remains opaque. The secondary setter's by-value vector ABI is also
confirmed by the recovered node creator's original call sequence. Strict near-zero
double comparisons retain the original NaN behavior. The attachment helper caches the
delta's length before normalization, then invokes its callback for every record kind.

Evidence: `accepted-dyn-candidate-consumers`, `accepted-dyn-translation-helper`,
`accepted-dyn-creation-setter-clean` and `accepted-dyn-attachment-update` under
`/opt/beetle-campaign-20261006`. Each wave has guarded source backups and build logs.

Two node matrix/vector property getters remain UNACCEPTED in trials 187/189. Their
instructions match after resolving four original local PC16 branches, every remaining
external relocation agrees and all 39 generated jump-table entries match. The raw
comparator was not weakened; separate strict switch-resolution evidence records those
object representations. Combined wave 190 failed because the still-included original
assembly rodata refers to replaced jump labels and duplicates compiler-generated
tables. Wave 191 restored both assembly functions/maps and accepted only the independent
translation helper; the original module/ROM pass again. Do not count the two drafts.
Recover and place the coherent rodata section before banking its switch consumers.

No fake padding, unsupported arguments, inline-assembly substitute or success stub was
accepted. Original unchecked allocation/capacity and getter contracts remain preserved;
the grouped caller/export audit must establish reachability before runtime changes.


## Historical accepted checkpoint — 124 further readable functions

Executable checkpoint `ce8e25abdcfdcf2a5e57cdc7b990600fc985153f` contains 124 further
readable, named and commented recoveries after 225 upstream ordinary function imports.
Twenty-one existing C semantic/type cleanups remain separately counted. Since checkpoint
118, six recoveries add attachment-vector refresh, indexed intersection query-bank
selection, collection-member sphere preparation, secondary model/LOD radius selection
and node/secondary matrix property setters. The six recoveries replace 1,876 original
instruction bytes. Three already-C collection/handle/scalar helpers were also named
and typed, with their 208 original instruction bytes independently verified.

Historical ledger at ce8e25ab: 1,076 assembly references = 1,014 ordinary + 62 entrypoints;
807,536 known remaining instruction bytes; zero unknown sizes; 1,339 address-named
C definitions still need semantic review. Full readable decompilation is incomplete.

All accepted functions pass exact real-translation-unit instruction bytes and complete
relocation targets at the same instruction offsets. Independent relocation-table order
may differ; no target/type/symbol-value/addend differences are allowed. Original packed
dynamic-module bytes, complete USA ROM SHA-1 and all 1,013 local/worker source hashes
pass after final naming and extraction. The original USA ROM SHA-1 remains
`e5ab4d226c08d22f68a2edcc48870203e67454b8`.

The attachment refresh copies each kind-zero child vector pair to adjacent attachment
vectors and copies the kind-one single vector; other kinds remain unchanged. The query
bank selector forwards an unchecked index and opaque halfword to the lowercase isct
export; it does not itself perform collision processing. Sphere preparation preserves
the original radius-history updates and ordered comparisons. Model/LOD selection uses
established UVMD asset layouts and the two original vector triplets, preserving the
ordered maximum and valid-model/index preconditions.

Node matrix properties 6/16/15 and secondary properties 3/4 retain transform-cache
updates, DOBJ propagation and strict double near-zero/NaN behavior. Redundant explicit
matrix pointer locals increased the IDO stack frame even when instructions otherwise
agreed. Direct typed matrix fields generated exactly the original frames and pointer
spills, with no artificial padding, unsupported arguments or inline assembly.

Evidence under `/opt/beetle-campaign-20261006`: `accepted-dyn-query-pair-helpers`,
`accepted-dyn-collection-spheres`, `accepted-dyn-secondary-semantic-group`, and
`accepted-dyn-matrix-property-setters`; guarded waves 203/205/211/218 retain backups
and build logs. The two jump-table property getter drafts from trials 187/189 remain
UNACCEPTED pending coherent rodata ownership/placement. Packed-handle resolver drafts
219/220/221 are also diagnostics, not counted recoveries. Original caller-contract
reachability and the broader recomp release gates remain active work.


## Historical accepted checkpoint — 128 further readable functions

Executable checkpoint `a9cf817ca4730886c7bc0978cbf474aadfe7672c` contains 128 further
readable, named and commented recoveries after 225 upstream ordinary imports.
Twenty-one existing C semantic/type cleanups remain separately counted. Four filerom
recoveries replace 404 original instruction bytes: filename extension selection,
four-character filename tags, the last-delimiter scanner, and module export setup.
One of the four is the reserved module loader entrypoint, not an ordinary function.

Historical ledger at a9cf817c: 1,072 assembly references = 1,011 ordinary + 61 entrypoints;
807,132 known remaining instruction bytes; zero unknown sizes; 1,340 address-named
C definitions still need semantic review. The reserved loader name contributes to
the last count. Full readable decompilation is incomplete.

The extension selector compares the original case-sensitive TED, AIPATH and REPLAY
strings; a missing period leaves the whole path for comparison. The filename tag
uses the four basename bytes preceding a period and preserves the original valid
storage precondition. The scanner returns the byte after the last matching non-NUL
delimiter, or the original pointer if no delimiter is found. Its indexed loop and
documented zero-XOR equality reproduce IDO's exact register/branch representation;
the compiler emits no XOR instruction. Export setup preserves all five original
callback slots, including the original inactive shutdown/write callbacks.

Exact real-module instructions and every relocation target at its original offset,
the original packed filerom module, complete USA ROM SHA-1 and all 1,013 local/worker
source hashes pass. The original ROM SHA-1 remains
`e5ab4d226c08d22f68a2edcc48870203e67454b8`.
Evidence under `/opt/beetle-campaign-20261006`: `accepted-filerom-filename-helpers`
and `accepted-filerom-scanner-entry`; guarded waves 235/240 preserve build logs and
backups. Sphere-merge, callback-installation, packed-handle resolver, file-open/read
and jump-table getter drafts remain unaccepted diagnostics. No near match is counted.


## Historical accepted checkpoint — 142 further readable functions

Executable checkpoint `b1dbc3c57587b494b9d03c4803fe085f6a33f2d0` contains 142 further
readable, named and commented recoveries after 225 upstream ordinary imports.
Twenty-nine existing C semantic/type cleanups remain separately counted. Since
checkpoint 128, fourteen new recoveries replace 1,180 original instruction bytes;
eight existing dynamic field/callback helpers separately received meaningful names,
typed layouts and comments, retaining all 196 original instruction bytes.

Historical ledger at b1dbc3c5: 1,058 assembly references = 997 ordinary + 61 entrypoints;
805,952 known remaining instruction bytes; zero unknown sizes; 1,332 address-named
C definitions still need semantic review. Full readable decompilation is incomplete.

Five recoveries cover track environment color, copying the motion matrix, registered
animation-state key lookup, current shadow-frame update and the eight-state shadow
allocator. The allocator returns null on exhaustion; animation lookup retains the
original 16-bit index. Nine further recoveries cover bubble color/emission scheduling,
spark reset/callback registration, rain initialization/texture loads, environment
volume-record insertion/lookup and track-data record lookup/backward handle iteration.
Track-data handles use two signed halfwords; original aggregate return and -1 boundary
behavior are preserved. Other bounds, ownership and opaque gameplay meanings are not
invented. Environment lookup intentionally cannot distinguish a zero record value
from no match. These are preserved original behaviors, not newly introduced fixes.

Every accepted instruction and relocation target matches in the real module. Original
packed modules, complete USA ROM SHA-1 and all 1,013 local/worker source hashes pass
after final semantic naming and extraction. Recorded zero instruction-alignment tails
are separate from function code, never counted as newly recovered instructions. ROM
SHA-1 remains `e5ab4d226c08d22f68a2edcc48870203e67454b8`.

Evidence under `/opt/beetle-campaign-20261006`: `accepted-dyn-existing-field-helpers`,
`accepted-small-module-cluster`, and `accepted-effect-data-cluster`; guarded waves
254/259/265 preserve backups/build logs. Sphere stack-layout searches 250/252 and
animation/font loop trials 255–258 produced no additional exact functions. Track-data
forward/linear handle and float-return drafts 261–263 remain unaccepted diagnostics.
The two switch-table getters still require coherent original/compiler rodata ownership.
No unsuccessful draft or retained assembly is included in the accepted recovery count.


## Historical accepted checkpoint — 154 further readable functions

Executable checkpoint `e63413ffd9e6938fa30da9cbff08faf6dbe91db1` contains 154 further
readable recoveries after the 225 upstream ordinary imports. Forty-two existing C
semantic/type cleanups are counted separately. Since checkpoint 142, twelve new
recoveries replace 1,044 original instruction bytes; thirteen existing C helpers
received typed parameters, descriptive locals/names and purpose comments while
retaining their 484 original instruction bytes.

Current ledger: 1,046 assembly references = 985 ordinary + 61 entrypoints;
804,908 known remaining instruction bytes; zero unknown sizes; 1,319 address-named
C definitions still need semantic review. Full readable decompilation remains incomplete.

The new recoveries cover track-data linear-index conversion, nullable vector-Z and
direction-angle lookup, two-component normalization, four-component scaled addition,
three-component interpolation, the original LCG, linear track-data value lookup,
motion graph selection, two AI-editor forwards and selection rotation offset.
Existing cleanups cover track-data total count, ten vector arithmetic/copy helpers,
shadow release and the LCG seed setter. The four-component helper is deliberately
not mislabeled as a three-component vector operation. AI-editor exports 0x1C/0x20
forward to the original no-op/zero-result track-data implementations; their ignored
callback contexts and argument-home stores are preserved, not manufactured for matching.

All accepted instruction words and relocation records match in real translation units.
Final named sources pass original packed-module hashes, the complete USA ROM SHA-1
`e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 local/worker source hashes.
Evidence under `/opt/beetle-campaign-20261006`: `accepted-tdata-accessors`,
`accepted-misc-vector-cleanup`, `accepted-normalize-shadow-release`, and
`accepted-leaf-math-cluster`; guarded waves 270/277/280/284 retain originals and logs.
Alignment-only zero tails are recorded separately from instruction bytes.

Unaccepted diagnostics include the shared direction-angle helper (six register
differences in the nearest 220-byte draft), bubble/shadow startup scheduling and
the previously recorded sphere, callback, packed-handle and switch-table packaging
work. A duplicate header include caused one isolated candidate-context assertion;
the corrected frozen trial used a unique anchor, and accepted source/ROM never
changed from that failed diagnostic. Preparation now checks context counts before
new candidate transfers.

Track-data float lookup has only an upper-bound check in the original code; negative
index reachability remains unproven and belongs in the grouped original caller-contract
audit. Matching source retains that contract. No speculative runtime fix is introduced.


## Historical accepted checkpoint — 158 further readable functions

The geometry wave was initially committed without successful full validation in
`9e80606f0e932d69c7d98587ba33f8bc4ac7ee0f`. Its commit message incorrectly claimed
module/ROM success. A declaration-editing regex had replaced the dot-product /
inverse-cosine call inside `func_misc_00403CA4` with a declaration. Corrective commit
`a641cf7181d654ac4cfb151cc0803aa9ad082b24` restores the original call and passes a
fresh successful build, original packed misc module SHA-256
`5860afcbb240b66074f15fa58e11822aba8e36fa8d3b541e8194349014aef0ec`, original USA ROM
SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes.
The initial failed build left a stale matching ROM, which was explicitly rejected
as evidence. Retained failed wave 290 and correction wave 291 preserve the history.

Four recoveries since checkpoint 154 replace 664 original instruction bytes:
two-component scaled reflection, in-place three-component matrix transformation,
matrix direction-angle extraction, and nonlinear vector approach preserving its
original magnitude. Fifteen existing C helpers receive separate cleanup (1,960
instruction bytes): clamp/flag transition/busy wait/inverse cosine/tangent, scalar
proportional and linear approach, proportional vector approach, transform translation,
spherical-coordinate forwards/conversion, translation/rotation construction, and
file-ROM module load/unload. Totals are 158 further recoveries after the 225 upstream
ordinary imports, plus 57 existing C cleanups.

Current ledger: 1,042 assembly references = 981 ordinary + 61 entrypoints;
804,244 known remaining instruction bytes; zero unknown sizes; 1,304 address-named
C definitions still need semantic review. Full readable decompilation is incomplete.

Every newly selected function matches original instruction words and complete
relocation records in its actual translation unit. The final combined source passes
packed-module/full-ROM checks and every tracked source hash. The landing script now
requires a worker PASS receipt tied to the complete source manifest and a successful
fresh build before staging or committing. Missing, failed, wrong-manifest and changed-
source proofs are rejected by regression checks. Candidate preparation and banking
reject declaration edits that target call statements; the known failed replacement
is covered by a regression check. Future campaign landings use `guarded_land_wave.py`.

Proofs: `/opt/beetle-campaign-20261006/accepted-geometry-corrected` and
`accepted-math-continuation`; frozen source waves 291 and 295. The inverse-sine,
approximate arctangent and nonlinear scalar drafts remain unaccepted; the vector
helper forwards to the original scalar assembly. No runtime behavior is approximated.


## Current accepted checkpoint — 167 further readable functions

Nine new matching recoveries replace 820 instruction bytes after checkpoint 158:
AI transformed-bounds containment in either order, eligible list rank, active record
field-0x9C lookup, car-audio emitter properties/scalar forwarding, complete indexed
module-reference unloading, track-editor record-pool reset, volume-test byte-slot
reset, battle/motion/Hot Lava update, and race parallel-flag marking.

Recovered layouts are grounded in the original offsets and access widths: the AI
indexed record has a 0x1E8 stride, s32 value at 0x9C and s16 activation at 0xB4;
the linked rank record follows next at 0x0C and source at 0x14, whose actor exclusion
byte is at 0x1D. The track-editor pool contains 80 pointers from offset 0x28, count
at 0x168 and selected index at 0x16A. Volume-test records preserve their 4+4+8 signed
byte arrays and next pointer at 0x14. Opaque ranges are actual inferred layout,
not invented stack padding. Names do not claim meanings for unexplained fields.

The bounds helper deliberately retains the original nine-point containment test;
it is not replaced with a different complete box-intersection algorithm. Rank counts
eligible predecessors while always accepting a found target. Indexed module unload
retains its original caller-owned index contract. Record reset preserves ownership
and does not invent frees. The ignored motion callback context and original argument
home store remain intact. The sound implementation owns scalar clamping.

Totals: 167 further readable recoveries after the 225 upstream ordinary imports;
57 existing C cleanups, counted separately. Current ledger: 1,033 assembly references
= 972 ordinary + 61 entrypoints; 803,424 known remaining instruction bytes; zero
unknown sizes; 1,304 address-named C definitions still require semantic review.
Full readable decompilation remains incomplete.

All nine instruction streams and full relocation records match in real translation
units. Independent relocation-record ordering differs for the race helper, while
offset/type/symbol/value/addend records are identical. AI/game alignment-only tails
(4/8 bytes) are separately recorded. Final named sources pass each original packed
module, a fresh successful four-job build, the original complete USA ROM SHA-1
`e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. Frozen
wave 298 and proof `accepted-callback-record-cluster` retain logs and originals;
the mandatory worker receipt gate precedes Git staging and commit.
