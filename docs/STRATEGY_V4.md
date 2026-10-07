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
matching C are preserved with `#line`. The current ledger has **900** assembly references:
**842** ordinary functions and **58** entrypoints, with **769,920** known instruction bytes
and no unknown sizes. The broader name audit still finds **374** address-named C definitions.
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


## Historical accepted checkpoint — 167 further readable functions

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


## Historical accepted checkpoint — 169 further readable functions

Two original intersection value scans replace 160 instruction bytes. Five existing
C word/address/query helpers (68 instruction bytes) separately receive descriptive
parameters/names and purpose/contract comments. Totals: 169 further recoveries after
the 225 upstream ordinary imports, plus 62 existing C cleanups.

Current ledger: 1,031 assembly references = 970 ordinary + 61 entrypoints;
803,264 known remaining instruction bytes; zero unknown sizes; 1,299 address-named
C definitions remain. The two scans preserve their original 16-bit index updates,
early exit and lack of state writes. The export return-value contract is not yet
established: C exposes a void scan, while all original instructions and return-register
behavior remain identical. This belongs in the existing grouped caller-contract audit,
not a guessed success result or deletion of the original routine. Offset-named fields
and parameters with unknown meanings are explicitly documented semantic debt; the
address-name count does not claim a complete semantic audit.

The vector-output getter draft remains unaccepted (21 instructions off in the best
current 148-byte source-pointer layout). Its original guard permits index == count
and does not reject negative indices; preserve the matching contract pending caller
analysis. Two original empty property exports remain assembly, rather than inventing
signatures/argument-home stores to increase the recovered count.

All selected instruction words and full relocation records match in real translation
units. Frozen wave 302 and `accepted-intersection-scan-cluster` prove the original
packed intersection module, a successful fresh four-job build, original full USA ROM
SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The
mandatory receipt and ledger checks precede staging and commit. Full readable
decompilation remains incomplete.


## Historical accepted checkpoint — 175 further readable functions

Six original control helpers replace 428 instruction bytes: clear dynamic-object
flag bit 2 for a track callback, forward AI-editor selection parameters to track
data, select a battle palette primitive color, register a channel-six callback,
query replay flag bits, and set/activate a selection record. Genuine unused callback
arguments and unchecked original index/pointer contracts are retained. Unknown
track-data parameter meanings are explicit; names do not infer a new game mechanic.

Totals: 175 further recoveries after the 225 upstream ordinary imports, plus 62
existing C semantic cleanups. Current ledger: 1,025 assembly references = 964 ordinary
+ 61 entrypoints; 802,836 known remaining instruction bytes; zero unknown sizes;
1,299 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave 305 and `accepted-small-control-cluster` verify every selected real
translation-unit instruction/relocation, all six original packed modules, a
successful fresh four-job build, the original full USA ROM SHA-1
`e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. Mandatory
receipt/source/ledger checks run before staging and commit. Screen/piece iteration
and packed RGB extraction drafts remain isolated diagnostics, not accepted changes.


## Historical accepted checkpoint — 183 further readable functions

Eight original helpers replace 860 instruction bytes: race-mode/AI-preset/player-
count speech selection, spray activation, course vector/magnitude initialization,
trigger-animation object/sound cleanup, replay settings/random-seed reset, and
display-list-editor mapped-word lookup. Speech names are grounded in callers that
set AI/player counts and the original speech-volume-aware helper. Unsupported
options still do nothing. Preserve signed bounds, ignored callback arguments,
null handling, store order, and original floating comparisons including NaNs.

Replay words at 0x190/0x198 and spray fields C0/D1 retain explicit semantic debt.
The replay module's shared miscellaneous export is consistently declared opaque,
with the original consumer using its precise local typed view; complete module
comparison catches any collateral compiler effect. No layout padding or synthetic
argument was added to force a match. Selection property stack layout, AI recording
ratios and scene selection drafts remain unaccepted diagnostics.

Totals: 183 further recoveries after the 225 upstream ordinary imports, plus 62
existing C semantic cleanups. Current ledger: 1,017 assembly references = 956 ordinary
+ 61 entrypoints; 801,976 known remaining instruction bytes; zero unknown sizes;
1,299 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave 308 and `accepted-control-followups` verify all selected real translation-
unit instructions/relocations, six original packed modules, a successful fresh four-
job build, the original full USA ROM SHA-1
`e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory
receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 190 further readable functions

Seven original helpers replace 820 instruction bytes: conditional movement
correction, planar record-vector computation and four-record iteration, alternating
camera offset, terrain lowest-Z candidate selection, transient selection reset and
track selection forwarding. Preserve original signed parity, explicit 16-bit index
wrapping, floating expression order, zero-default threshold selection, unknown
offset-named field meanings, and unchecked original index/pointer contracts.

Totals: 190 further recoveries after the 225 upstream ordinary imports, plus 62
existing C semantic cleanups. Current ledger: 1,010 assembly references = 949 ordinary
+ 61 entrypoints; 801,156 known remaining instruction bytes; zero unknown sizes;
1,299 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave 312 and `accepted-motion-terrain-cluster` verify selected real translation-
unit instructions/relocations, five original packed modules, a successful fresh four-
job build, the original full USA ROM SHA-1
`e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory
receipt/source/ledger gate precedes staging and commit. Terrain matrix wrappers,
record allocation, AI recording ratios and editor property drafts remain unaccepted.

### Original flag removal hazard — unresolved caller contract

The original `func_flag_004004A4` loads the first node's next pointer before any
null check. If asked to remove that first node, it stores the current node back
into the head variable and then frees the requested node; it does not advance the
head to next. Thus a head-removal call appears to leave a dangling head, and an
empty-list call appears to dereference null. No direct assembly caller was found;
indirect export callers and any sentinel contract remain unproven. This is a
specific original-code hazard, not a newly introduced regression. The draft is
still isolated and unaccepted. Add both conditions to the existing grouped original
caller-contract audit. Do not silently change matching behavior or claim that lack
of direct callers establishes unreachability.

* **OC1 — Original flag-list removal hazard.**
  The original routine can leave the head pointing to a freed first node if that
  call is permitted. Actual indirect-call reachability remains unproven.
  * **A (recommended):** Complete export/sentinel caller analysis and preserve the
    original matching implementation; add a separate recomp correction only if
    a supported reachable call violates the required contract.
    *Impact:* avoids changing game behavior based on an unverified caller assumption.
  * **B:** Record the hazard and defer a runtime change until a reproducer exists.
    *Impact:* retains original behavior and leaves a documented potential crash path.


## Historical accepted checkpoint — 200 further readable functions

Ten original helpers replace 1,392 instruction bytes: environment volume-value
lookup, light-state initialization and record insertion, shared dual-emitter sound
scalar, tournament voice selection, guarded two-player setup, AI pool allocation
and linked-list removal, victory joint-animation advance, and terrain record-buffer
allocation. Original pool limits, list aliasing, floating expression order, gated
voice selection, opaque parameter meanings and unchecked contracts are preserved.
One existing spark helper comment is corrected: DOBJ export 0x10B4 clears flag
bits, so passing two clears bit two rather than setting a mode.

Totals: 200 further recoveries after the 225 upstream ordinary imports, plus 63
existing C semantic cleanups. Current ledger: 1,000 assembly references = 939 ordinary
+ 61 entrypoints; 799,764 known remaining instruction bytes; zero unknown sizes;
1,299 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave 317 and `accepted-effect-state-cluster` verify real translation-unit
instructions/full relocations, eight original packed modules, a fresh successful
four-job build, original full USA ROM SHA-1
`e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory
receipt/source/ledger gate precedes staging and commit. AI active-handle iteration,
car color application and spark-array reset scheduling remain isolated diagnostics.

### Original light-handle sentinel mismatch — unresolved caller contract

`lightInitializeState` stores the allocator result into a signed 16-bit handle,
reloads it with sign extension, and compares it against integer 65535. The allocator
`func_uvlight_rom_00400B64` returns -1 when its configured light capacity is reached.
Consequently the original initializer's comparison cannot reject that failure value:
it continues writing the scalar defaults while retaining handle -1. Whether a
supported caller can exhaust capacity, and whether later handle consumers safely
reject -1, still needs an indirect export/caller audit. This is an original-code
hazard, not a new decomp regression; the exact signed comparison is retained.

* **OC2 — Original light-handle failure check.**
  The original signed handle check does not catch allocator failure -1.
  * **A (recommended):** Finish the capacity and handle-consumer audit while
    preserving matching C; propose a separate recomp fix if a supported reachable
    sequence causes incorrect behavior.
    *Impact:* keeps binary fidelity and avoids changing behavior before caller evidence.
  * **B:** Defer a runtime correction until a capacity-exhaustion reproducer exists.
    *Impact:* leaves the potential failure path documented with original behavior intact.


## Historical accepted checkpoint — 205 further readable functions

Five original helpers replace 616 instruction bytes: a sound-triggered Yes/No pause menu, texture-axis parameter assignment, pending camera scene-record synchronization, spatial light-record insertion and selection-menu return-node preservation. Original selector defaults, linked menu order, pending-flag clearing, squared influence radius and unknown parameter meanings are retained. Names are grounded in original menu strings, scene exports and the spatial light consumer. Display-list color packing, track-data loading and static-object model replacement remain isolated unaccepted diagnostics.

Totals: 205 further recoveries after the 225 upstream ordinary imports, plus 63 existing C semantic cleanups. Current ledger: 995 assembly references = 934 ordinary + 61 entrypoints; 799,148 known remaining instruction bytes; zero unknown sizes; 1,299 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `322-state-asset-cluster` and `accepted-state-asset-cluster` verify real translation-unit instructions/full relocations, 5 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 213 further readable functions

Eight original helpers replace 1,228 instruction bytes: two per-screen visibility cache refreshes and their dispatcher, replay spatial-record insertion, spark object-transform update, indexed selection preset copying, object color/callback setup and effect-record attachment with matrix translation. Original signed cache values, lazy -1 refresh, countdown expiration, null/default cases, property callback arguments, blocked-record return and unchecked index contracts are retained. GUI pool reset drafts remain isolated unaccepted diagnostics.

### Original visibility-cache bounds — unresolved caller contract

The visibility dispatcher reads first[index], second[index] or third[index] before
refreshing a -1 cache. Both recovered screen refresh functions check the reported
screen count but still write the selected byte when an index is negative or beyond
that count. The records have four first/second slots. Thus these checks do not
protect record bounds; callers must supply a valid slot even for inactive screens.
The dispatcher is the observed direct caller. Indirect export caller bounds remain
unproven, so matching behavior is retained and this joins the original caller audit.

* **OC3 — Original visibility-cache indices.**
  Original cache reads and invalid-screen writes require caller-owned record bounds.
  * **A (recommended):** Audit indirect export callers for four-slot bounds and
    preserve matching C; propose a separate recomp fix if a reachable caller violates it.
    *Impact:* avoids altering original cache behavior without a supported failing path.
  * **B:** Defer a runtime correction until an out-of-range caller is reproduced.
    *Impact:* keeps fidelity while leaving the potential memory-access hazard documented.


Totals: 213 further recoveries after the 225 upstream ordinary imports, plus 63 existing C semantic cleanups. Current ledger: 987 assembly references = 926 ordinary + 61 entrypoints; 797,920 known remaining instruction bytes; zero unknown sizes; 1,299 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `326-visibility-replay-cluster` and `accepted-visibility-replay-cluster` verify real translation-unit instructions/full relocations, 6 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 216 further readable functions

Three original helpers replace 496 instruction bytes: track-editor frame/camera dispatch, three-table AI recording conversion and Controller Pak settings-block writing. Original mode/default dispatch, opaque value/ratio pairs, legacy count-only loops, file lookup and 1024-byte transfer semantics are preserved.

The existing Controller Pak write helper at 0x00401148 and its export type are
corrected from void to s32, explicitly returning osPfsReadWriteFile's SDK status.
The original selection caller checks that status against zero; the previous
recovered C declaration incorrectly discarded that contract. The matching module
proof covers both this existing helper and the newly recovered caller. This fixes
a decompilation type error while retaining the original game's transfer behavior.
It adds one existing C semantic cleanup. The original save/Controller Pak gameplay
tests remain separate from byte-for-byte source validation.

The five-way voice-selection draft has matching instruction words but unresolved
jump-table ownership/relocations, so it remains isolated. Race marker, audio local
layout and motion vector drafts also remain unaccepted. No invalid draft is landed.


Totals: 216 further recoveries after the 225 upstream ordinary imports, plus 64 existing C semantic cleanups. Current ledger: 984 assembly references = 923 ordinary + 61 entrypoints; 797,424 known remaining instruction bytes; zero unknown sizes; 1,299 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `331-editor-save-cluster` and `accepted-editor-save-cluster` verify real translation-unit instructions/full relocations, 4 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 222 further readable functions

Six original helpers replace 868 instruction bytes: eight-slot object-position visibility caching, GUI three-component source configuration, localized PLAYER 1 menu setup, menu entry preserving recognized origins, Controller Pak repair/timer/peripheral-state handling, and dynamic indexed range lengths. Localized label contents and original export implementations ground the names and types. The GUI component meanings remain explicitly opaque.

Original visibility-cache contract OC3 [Original visibility-cache indices] also covers the third eight-slot cache: invalid indices still write the indexed byte. Original bounds and behavior remain unchanged in this matching decompilation. The dynamic range helper likewise retains the already documented collection-index caller contract.

Allocation-loop ordering, spark-slot allocation and pause/results drafts remain isolated because they do not yet match. No padding-only locals or invalid drafts are accepted.


Totals: 222 further recoveries after the 225 upstream ordinary imports, plus 64 existing C semantic cleanups. Current ledger: 978 assembly references = 917 ordinary + 61 entrypoints; 796,556 known remaining instruction bytes; zero unknown sizes; 1,299 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `336-control-cache-cluster` and `accepted-control-cache-cluster` verify real translation-unit instructions/full relocations, 4 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 229 further readable functions

Seven original helpers replace 1352 instruction bytes: all-zero/all-nonzero menu-byte predicates, gated gated replay-flag menu input, rain clipping, display-list RGBA unpacking, saved sound-option application and gated voice playback. The original compiler expands the two small byte loops substantially; readable C retains those compact loops rather than copying generated unrolling.

Signed nonpositive lengths return true. Replay flag priority and record gating remain unchanged. Rain comparisons preserve touching boundaries, depth endpoints and unordered floating-point behavior. Speech playback still initializes its local handle even when the voice gate is zero, and speech-disabled calls leave the gate unchanged.

AI recording interpolation and splash/bubble dispatch drafts remain isolated pending exact instruction scheduling and register matches.


Totals: 229 further recoveries after the 225 upstream ordinary imports, plus 64 existing C semantic cleanups. Current ledger: 971 assembly references = 910 ordinary + 61 entrypoints; 795,204 known remaining instruction bytes; zero unknown sizes; 1,299 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `339-particle-menu-cluster` and `accepted-particle-menu-cluster` verify real translation-unit instructions/full relocations, 4 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 229 further readable functions

Twenty existing C helpers receive semantic function/parameter names and contract comments: controller button/raw/normalized state, Controller Pak identity/lookup/capacity queries, object flag operations and callback registration, graphics viewport/framebuffer/wait operations and lighting setup/slot allocation. Source/header/export/linker references are renamed consistently. No instruction behavior changes are introduced.

These functions were already recovered upstream and have no standalone assembly fallback files. The isolated comparison therefore compares their complete ELF symbols, including alignment, against the fresh accepted build object, with a source/object freshness guard. All twenty complete instruction/relocation comparisons pass. The final original packed-module/full-ROM proof remains mandatory. The initial assembly-boundary-only trial stopped on a missing upstream assembly file without changing integration; the explicit existing-C comparison resolves that tooling limitation.

The four object-flag helpers retain the already documented inclusive/missing-negative object-index contract. Caller reachability and actual allocated capacity still determine whether any runtime patch is needed.

An additional original light contract was exposed during naming review: func_uvlight_rom_0040167C permits sentinel -1 through its initial checks, then evaluates the referenced array entry's refCount. A call with -1 therefore reads before the light-record array. Reachability and whether the allocation provides a sentinel record are not proven. Matching source preserves the original behavior.

* **OC4 — Original light sentinel lookup.**
  The light selection helper reads refCount through index -1 before storing its sentinel. A caller/sentinel audit is required to establish whether that access is valid in the original allocation.
  * **A (recommended):** Audit sentinel callers and allocation layout, preserving the original bytes; add a separate recomp runtime fix only if the read is outside the allocation.
    *Impact:* avoids changing an original sentinel convention without evidence; keeps the potential invalid read visible.
  * **B:** Defer a runtime change until a debugger or sanitizer reproduces an invalid read.
    *Impact:* retains original compatibility but leaves the sentinel contract unresolved.


Totals: 229 further recoveries after the 225 upstream ordinary imports, plus 84 existing C semantic cleanups. Current ledger: 971 assembly references = 910 ordinary + 61 entrypoints; 795,204 known remaining instruction bytes; zero unknown sizes; 1,279 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `342-existing-interface-names` and `accepted-existing-interface-names` verify real translation-unit instructions/full relocations, 15 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 231 further readable functions

Two original helpers replace 516 instruction bytes: horizontal menu action selection and wrapped numeric menu-value editing. Replay axis zero and left/right flags share the original direction priority. Numeric editing reacts when the previous action is zero, wraps across the inclusive limits and caches every current action. Controller indices and ordered numeric limits remain original caller contracts.

The five other menu, AI, weather and victory drafts remain isolated because they do not yet reproduce the original instructions. No nonmatching draft is included.

The light sentinel audit additionally confirms that the light array allocation has exactly count times 0x34 bytes and no visible pointer bias or extra sentinel element. The refCount field is at 0x30, so index -1 in the original lookup reads four bytes before the allocation. Reachable callers of export 0x30 still require audit before a separate runtime correction; matching decompilation retains the original behavior.

Totals: 231 further recoveries after the 225 upstream ordinary imports, plus 84 existing C semantic cleanups. Current ledger: 969 assembly references = 908 ordinary + 61 entrypoints; 794,688 known remaining instruction bytes; zero unknown sizes; 1,279 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `346-menu-value-cluster` and `accepted-menu-value-cluster` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 231 further readable functions

Twenty-five existing C functions receive descriptive names, parameter names and contract comments. No assembly reference is removed by this naming-only checkpoint. Controller Pak writes document 32-byte buffer rounding; allocation retains the original void error interface. Rumble cleanup retains all four SDK stop requests. Light record selection documents the original minus-one sentinel read hazard. Graphics polling remains nonblocking. Math helpers retain comparison order, signed-zero behavior, unsigned random-state wrap and the original sine/cosine tangent ratio.

The viewport append guard is less than eleven while the declared array has ten elements. The matching implementation and guard are preserved. This is recorded as original viewport capacity hazard OC5 [Original viewport capacity]; a caller/cursor audit must establish whether index ten is reachable before a separate recomp fix. The existing light sentinel hazard remains pending its caller audit.

Totals: 231 further recoveries after the 225 upstream ordinary imports, plus 109 existing C semantic cleanups. Current ledger: 969 assembly references = 908 ordinary + 61 entrypoints; 794,688 known remaining instruction bytes; zero unknown sizes; 1,254 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `348-interface-contracts` and `accepted-interface-contracts` verify real translation-unit instructions/full relocations, 20 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 234 further readable functions

Three original helpers replace 568 instruction bytes: two track-editor record writers and GUI pool-34 text-row creation. Editor serialization emits each original one-byte header and 0x2C-byte records, reloading shared counts and bases after callbacks and retaining ignored write results. The GUI helper uses the verified allocate/get/text/attach/property export slots, copies twelve original text bytes and returns the row pointer. No new validation changes game behavior.

The earlier recovered miscLoadFileModule had a void C declaration despite original editor callers storing its return value as a module export table. Its declaration and definition now explicitly return uvLoadModule('filr'). The original 36-byte instruction stream and full relocation targets still match. This correction does not count as another newly recovered function. The ROM-backed filr write callback is originally inactive; these writers preserve that module interface and introduce no host-file side effects.

The other medium menu/editor candidates remain isolated pending exact scheduling, buffer-contract and stack-layout recovery.

Totals: 234 further recoveries after the 225 upstream ordinary imports, plus 109 existing C semantic cleanups. Current ledger: 966 assembly references = 905 ordinary + 61 entrypoints; 794,120 known remaining instruction bytes; zero unknown sizes; 1,254 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `355-editor-gui-contracts` and `accepted-editor-gui-contracts` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 238 further readable functions

Four original helpers replace 888 instruction bytes: signed 16-bit menu wrapping, AI Manhattan target distance with its 105-unit limit, car-animation orientation basis construction and variadic static-object flags. The distance helper retains positive-test absolute values, original addition order, strict threshold and missing-link behavior. Car orientation follows the verified vector helper output/input contract and preserves degenerate-vector behavior. Numeric menu steps narrow to the original signed 16-bit storage before comparisons.

The terrain property list ends only at property zero. Unknown properties continue scanning; property one assigns flags, two clears a supplied bit and three sets a supplied bit. The draft that returned for unknown properties was rejected before acceptance. Caller-owned termination, argument types and bit limits remain explicit original contracts. The related AI basis and byte-menu drafts remain isolated until their remaining stack/register differences are resolved.

Totals: 238 further recoveries after the 225 upstream ordinary imports, plus 109 existing C semantic cleanups. Current ledger: 962 assembly references = 901 ordinary + 61 entrypoints; 793,232 known remaining instruction bytes; zero unknown sizes; 1,254 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `361-basis-distance-cluster` and `accepted-basis-distance-cluster` verify real translation-unit instructions/full relocations, 4 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 238 further readable functions

Twenty-four existing C functions receive grounded names, parameters and contract comments: matrix linear-copy/composition, point/direction/XY/homogeneous transforms, axis/translation/angle accessors, float-to-fixed matrix push, four module cleanup interfaces and texture scratch access/allocation. The angle extractor loses two unused locals while retaining exact original machine code. The distinct second Y-axis getter remains a separate export. Matrix multiplication and square-sum ordering remain unchanged.

A perspective-frustum draft that removed an existing empty constant-false conditional changed the original compiler output and remains excluded. That existing cleanup debt is explicit; no nonmatching simplification or assembly substitute was accepted.

The inspected texture helper indexes D_uvtexture_rom_00400D14 with zero minus the toggled buffer index. Whether that negative index intentionally addresses an adjacent legacy state slot requires allocation/layout and caller audit; no runtime correction is justified from the expression alone.

Totals: 238 further recoveries after the 225 upstream ordinary imports, plus 133 existing C semantic cleanups. Current ledger: 962 assembly references = 901 ordinary + 61 entrypoints; 793,232 known remaining instruction bytes; zero unknown sizes; 1,230 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `365-matrix-interfaces` and `accepted-matrix-interfaces` verify real translation-unit instructions/full relocations, 10 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 241 further readable functions

Three original helpers replace 648 instruction bytes: byte-sized menu wrapping, pause-menu language cycling and 0x34-byte UFO state allocation. Menu increment narrows to a byte before testing the upper bound; decrement wraps only at the original minimum. Language cycling uses separate left/right latches and retains the three original language indices.

The UFO constructor clears its allocation, stores the opaque parameter and starting position, obtains camera state and runs optional track-data initialization/attachment. The attachment scalar is floating zero, established by the original float-register transfer into argument one. The position uses a genuine three-component structure assignment, reproducing the original integer bit copies without type-punning float pointers. Camera/state meanings not established by consumers remain explicitly opaque.

The related AI basis stack-layout and perspective-matrix cleanup drafts remain isolated.

Totals: 241 further recoveries after the 225 upstream ordinary imports, plus 133 existing C semantic cleanups. Current ledger: 959 assembly references = 898 ordinary + 61 entrypoints; 792,584 known remaining instruction bytes; zero unknown sizes; 1,230 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `372-menu-language-ufo` and `accepted-menu-language-ufo` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 244 further readable functions

Three original helpers replace 676 instruction bytes. Two motion routines form angular velocity crossed with a point offset plus linear velocity. One projects the result onto two record axes and clears output Z; the other selects one of two offsets in a 0x1C-byte record and transforms the result by matrix 0x5E8. Physical names describe the observed velocity formula without asserting units. Original selector index ownership remains with callers.

The rain helper allocates and prepends a kind-two 0x1C-byte command, converting fraction times 100 to the original unsigned count and retaining the original scalar slot order. The unsigned conversion is intentional and matches the original floating-point exception and conversion sequence. Opaque scalar meanings remain offset-based.

Nonmatching direction-state, rain rectangle and particle-density drafts remain isolated.

Totals: 244 further recoveries after the 225 upstream ordinary imports, plus 133 existing C semantic cleanups. Current ledger: 956 assembly references = 895 ordinary + 61 entrypoints; 791,908 known remaining instruction bytes; zero unknown sizes; 1,230 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `377-motion-rain-cluster` and `accepted-motion-rain-cluster` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 244 further readable functions

Thirty-two already recovered C helpers receive grounded function/parameter names and comments. Coverage includes rain command kinds and maximum/value updates, RGB/HSV vertex transforms, sorted callback registration/ordering, texture buffer state and loaded data, light direction/packed colors and object teardown/model/joint output. Source, header, export and linker references are renamed consistently. All original instructions and return contracts remain unchanged.

The callback sorter is documented precisely: it negates selected keys before restoring negative keys, preserves flag-controlled insertion order and caches its index order. Its original key-range assumptions remain a caller contract; this routine is not represented as a general stable signed-key sort. Callback append retains the original equality-only capacity check. Other index capacities retain their original documented ownership.

The texture helper retains the already documented negative buffer-index expression pending a contiguous-global layout audit. No claim that the adjacent-state access is invalid has been made. The original lighting sentinel issues and viewport capacity issue remain in the earlier contract-audit entries. No speculative runtime patch is introduced.

The original RGB/HSV conversion uses normalized hue, -1 for equal-channel hue and unsigned byte conversion without added clamping. Unflagged vertices cube all RGB factors in the RGB helper but only the value factor in the HSV helper. Comments retain those distinct behaviors.

Totals: 244 further recoveries after the 225 upstream ordinary imports, plus 165 existing C semantic cleanups. Current ledger: 956 assembly references = 895 ordinary + 61 entrypoints; 791,908 known remaining instruction bytes; zero unknown sizes; 1,198 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `379-rendering-rain-contracts` and `accepted-rendering-rain-contracts` verify real translation-unit instructions/full relocations, 9 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 248 further readable functions

Four original helpers replace 828 instruction bytes. Motion lookup clears output halfword 0xA when flagged state/lookup conditions hold. The first lookup result is retained across the optional AI query and its referenced-state callback takes one real argument; the generated extra argument was not used in the original instructions. Returned records preserve their original nonnull caller contract.

The battle vector registration helper supports two kinds. Kind zero indexes and increments the count at 0x2254; kind one indexes with shared word C2D8 while incrementing a distinct count at 0x2258. This original difference is explicit in the source rather than silently normalized. Tables retain caller-owned capacity.

The intersection setter writes one of two vectors in the original 0x1C-byte indexed region through the vector library. It retains the already documented inclusive limit and missing negative-index check. No speculative runtime index patch is introduced.

The AI editor now has an expanded concrete state view: four object words, four 0x20-byte record regions, count/mode, selected float, parameter and scalar. Its loop reloads shared count/mode after callbacks and its optional track-data update uses integer selection, integer parameter and floating scalar. Existing selection-forwarding offsets remain unchanged.

Near-matching spray rendering, battle effect dispatch and car-audio playback drafts remain isolated; no artificial stack padding or invented operations have been added.

Totals: 248 further recoveries after the 225 upstream ordinary imports, plus 165 existing C semantic cleanups. Current ledger: 952 assembly references = 891 ordinary + 61 entrypoints; 791,080 known remaining instruction bytes; zero unknown sizes; 1,198 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `392-lookup-editor-vector-cluster` and `accepted-lookup-editor-vector-cluster` verify real translation-unit instructions/full relocations, 4 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 251 further readable functions

Three original helpers replace 776 instruction bytes. Race GUI construction resets the game GUI, allocates an original pool-5C slot and obtains its pointer, copies the fixed 30-byte label through the original uppercase helper, attaches the node and forwards it to camera, optional AI and track modules. Export 0x70 is confirmed as uvGuiAllocatePool5CSlot and 0x74 as its slot lookup; it is not mislabeled as a kind query or a generic constructor. The original unchecked allocation convention remains unchanged.

Replay serialization uses the existing file-module interface and original version-two binary layout: one version byte, frame count, event byte count, frame-input bytes, four-byte frame values and event bytes. It retains the original filename format, work-area prefix and four-character scene suffix. The original 128-byte local filename region, version-byte placement and complete instruction stream match. Open failure skips writes, while write/close statuses remain ignored as in the original. This recovery introduces no operating-system file backend or new host file write behavior.

Screen submission selects the original 0x46-byte record, forwards fill color with alpha one, obtains screen width/height and appends the full-screen viewport. It conditionally submits base geometry based on selected halfword 0x4, then submits the selected record. A genuine cached-height local reproduces the original stack layout without artificial padding.

All three functions match original instruction bytes and relocation targets; complete packed-module and ROM verification follows before landing.

Totals: 251 further recoveries after the 225 upstream ordinary imports, plus 165 existing C semantic cleanups. Current ledger: 949 assembly references = 888 ordinary + 61 entrypoints; 790,304 known remaining instruction bytes; zero unknown sizes; 1,198 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `399-gui-replay-screen` and `accepted-gui-replay-screen` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 251 further readable functions

Thirty-one existing C helpers gain grounded function and parameter names and contract comments. Coverage includes callback registration, audio allocation/source/track state, animation material and localized-label lookup, motion copying/reset/update, replay flags/scalars/regions, race model/table interfaces, screen rectangles, record detachment and effect teardown. Source, header, export and linker references are renamed consistently.

The audio command constructor now uses a typed 28-byte command with kind, three opaque words, flag, scalar and next pointer. This readable exact match removes the former volatile padding, comma expression and XOR no-op. The separate audio matrix-binding helper still contains historical repeated masks; attempted clean replacements differ in six register instructions and are deliberately excluded pending a genuine matching layout/lifetime recovery.

Original behavior and caller contracts remain intact: replay flag edges compare any requested current bit against absence of any requested previous bit, motion reset preserves five vector regions and store order, language and source indices are not speculatively clamped, and callback-visible counts reload in their original sequence. No runtime behavior changes or new confirmed reachable bugs are claimed.

Totals: 251 further recoveries after the 225 upstream ordinary imports, plus 196 existing C semantic cleanups. Current ledger: 949 assembly references = 888 ordinary + 61 entrypoints; 790,304 known remaining instruction bytes; zero unknown sizes; 1,167 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `404-game-contracts` and `accepted-game-contracts` verify real translation-unit instructions/full relocations, 11 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 255 further readable functions

Four original functions become readable matching C, replacing 824 instruction bytes. The motion helper advances a ten-slot history only when its countdown is negative, copies three-component position and two state scalars plus shared field 0x7C, clears an overwritten marked slot, and updates optional track data with the original 100.0 parameter.

The track-data vector lookup establishes a genuine Vec3F struct return, including the original hidden output-pointer ABI. The routine converts its linear index to a group/index handle, returns record vector offset 0x0C, and preserves the original fallback vector when the record lookup is null. An explicit pointer-return alternative did not match and was excluded.

The editor save uses the existing file backend, original filename format, version-three header and four record writer calls. Open failure skips writes; original ignored write/close statuses remain documented. The material offset helper preserves kind-two/three offset 0.125, special-material offset 0.5 and scalar lower bound ten, the 0xFFF default index and caller-owned remaining material bounds.

Other ranking, pause, sound and record-writer drafts remain isolated because their instructions do not match. No approximate function is admitted and no new runtime behavior changes or confirmed reachable bugs are claimed.

Totals: 255 further recoveries after the 225 upstream ordinary imports, plus 196 existing C semantic cleanups. Current ledger: 945 assembly references = 884 ordinary + 61 entrypoints; 789,480 known remaining instruction bytes; zero unknown sizes; 1,167 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `417-history-editor-material` and `accepted-history-editor-material` verify real translation-unit instructions/full relocations, 4 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 257 further readable functions

Two original routines become readable matching C, replacing 388 instruction bytes. Static-object property queries use the existing stdarg convention: property one writes the flag word, property four writes the model ID, zero terminates and unknown properties return. Missing objects consume no output properties; callers retain original pointer and termination responsibilities.

The selection preview teardown resets four player slots, flushes graphics and texture animation, unloads terrain 0xB/environment zero, clears selection field 0x220 and resets terrain/environment bindings in the original call order. All symbol/export/linker references are renamed consistently.

Other menu option/sound, track-data iteration and AI scalar lifetime trials remain isolated because their original instructions do not match. An AI seed leading-float argument was explicitly tested against the real compiler and rejected; the actual callee overwrites that floating register from its third integer-register argument. No guessed calling convention is admitted. No runtime behavior change or new confirmed reachable bug is claimed.

Totals: 257 further recoveries after the 225 upstream ordinary imports, plus 196 existing C semantic cleanups. Current ledger: 943 assembly references = 882 ordinary + 61 entrypoints; 789,092 known remaining instruction bytes; zero unknown sizes; 1,167 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `429-terrain-preview` and `accepted-terrain-preview` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 260 further readable functions

Three original routines become readable matching C, replacing 740 instruction bytes. The editor environment query preserves its unused argument, five RGB triplets, two blend outputs with shared rate storage and one scalar; the original routine discards these results. The battle routine builds an identity matrix with an indexed translation, assigns object matrix slot zero, selects mode two and enables flag one.

Terrain tile rendering uses the actual two-matrix rebasing export, loads view matrix one, conditionally dispatches both geometry lists with the original 16-bit masks and counts, then pops the matrix. The first export reads the tile matrix from its second argument, which the initial machine-generated seed omitted. The recovered call uses the established matrix header and the real implementation, with full instruction equivalence. All symbol/export/linker references are renamed consistently.

Camera, demo, gameplay loops and battle HUD color lifetime trials remain isolated because their original instruction words do not match. No guessed extra argument, artificial padding or volatile workaround is accepted. No new confirmed reachable bug or runtime behavior change is claimed.

Totals: 260 further recoveries after the 225 upstream ordinary imports, plus 196 existing C semantic cleanups. Current ledger: 940 assembly references = 879 ordinary + 61 entrypoints; 788,352 known remaining instruction bytes; zero unknown sizes; 1,167 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `437-environment-battle` and `accepted-environment-battle` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 261 further readable functions

Forty-one existing C routines gain grounded function/parameter names and contract comments across demo graphics, track-data state and handles, car animation, editor camera/light/color/text state, scene model refresh, race status and skid/spray callbacks. The track-data window helper now declares its three actual output-handle pointers instead of integers while preserving its full machine code. A redundant editor if(1) block and an unused animation local are removed after exact comparisons. Existing packing, low-byte conversions, sentinel checks, callback sequencing and bounds responsibilities remain intact.

One additional assembly routine becomes readable C: selection text storage and bitmap/sprite teardown, replacing 168 instruction bytes. Its format export takes a genuine variadic three-argument call; the initial machine-generated fourth argument was an unset register and is excluded. Original packed-module comparison proves the complete call and relocation behavior. Source, header, export and linker references are renamed consistently.

Two more aggressive editor loop rewrites differ in instruction scheduling and remain isolated. Terrain/camera/gameplay lifetime experiments and pointer-registry removal remain unaccepted. The existing editor pointer-table scan still assumes valid nonnull entries; this caller contract is documented rather than speculatively altered. No new confirmed reachable bug or runtime behavior change is claimed.

Totals: 261 further recoveries after the 225 upstream ordinary imports, plus 237 existing C semantic cleanups. Current ledger: 939 assembly references = 878 ordinary + 61 entrypoints; 788,184 known remaining instruction bytes; zero unknown sizes; 1,126 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `445-editor-effect-contracts` and `accepted-editor-effect-contracts` verify real translation-unit instructions/full relocations, 10 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 263 further readable functions

Two original routines become readable matching C, replacing 384 instruction bytes. Controller Pak selection uses the configured company/game identity, finds the file, calls the real boolean settings-read helper, stores successful file/status state and preserves the three-second result timer and failure reset. The helper declaration now exposes its actual return value instead of void; the callee machine code establishes this return contract.

Battle state transfer clears the linked motion flag, copies the position aggregate and two scalars, stores shared time, reads the object matrix and passes its translation row to the original motion export before updating the battle node. Export mapping establishes the target as motion function 0x130E4; callee inspection confirms it reads only the first three incoming argument registers. The generated fourth argument was leftover state, not an input. All symbol/export/linker references are renamed consistently.

A separate motion angle-limit candidate still differs in register scheduling and remains isolated. No new confirmed reachable bug or runtime behavior change is claimed.

Totals: 263 further recoveries after the 225 upstream ordinary imports, plus 237 existing C semantic cleanups. Current ledger: 937 assembly references = 876 ordinary + 61 entrypoints; 787,800 known remaining instruction bytes; zero unknown sizes; 1,126 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `455-pak-battle-state` and `accepted-pak-battle-state` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 268 further readable functions

Five original routines become readable matching C, replacing 840 instruction bytes. Menu updates retain selection-change notification, preview positioning and one consecutive four-byte object handle per configured player. Intersection policy preserves unconditional acceptance in states 10, 17 and 29 and otherwise tests list membership without inventing meanings for those states. Both GUI attachment routines retain their two display-width callbacks, original signed division and upper/lower band coordinates. Terrain setup passes its actual incoming channel to property six, retrieves the callback list and preserves callback priorities 40, 45 and 100. The generated seed had omitted this incoming argument; original instructions establish the contract. All symbol/export/linker references are renamed consistently.

Other menu, scene and recorded-sample experiments remain isolated because they do not yet match. No new reachable original bug or runtime behavior change is claimed.

Totals: 268 further recoveries after the 225 upstream ordinary imports, plus 237 existing C semantic cleanups. Current ledger: 932 assembly references = 871 ordinary + 61 entrypoints; 786,960 known remaining instruction bytes; zero unknown sizes; 1,126 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `471-menu-callback-cluster` and `accepted-menu-callback-cluster` verify real translation-unit instructions/full relocations, 4 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 268 further readable functions

Twenty-six existing C routines receive descriptive function and parameter names and explicit contracts. The six object pools retain signed indices, exact strides and unchecked access. Rectangle setters retain signed 16-bit edge and extent conversion. Four 30-byte text copies document that the original transform subtracts 32 from every byte at least 97, including bytes above z, and does not scan for NUL. Display-data/palette loading preserves its sentinel and callback order. Value-widget configuration preserves its optional caller-owned source pointer, fallback and state transition rules. All symbol/export/linker references are renamed consistently.

The compact 12-byte text-copy cleanup remains isolated: removing its existing comma artifact changes stack layout. No substitute padding, no-op or behavior-changing workaround was accepted. No newly confirmed reachable original bug or runtime behavior change is claimed.

Totals: 268 further recoveries after the 225 upstream ordinary imports, plus 263 existing C semantic cleanups. Current ledger: 932 assembly references = 871 ordinary + 61 entrypoints; 786,960 known remaining instruction bytes; zero unknown sizes; 1,100 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `478-gui-contracts` and `accepted-gui-contracts` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 269 further readable functions

The six-slot scene handle lookup becomes readable matching C, replacing 156 instruction bytes. The loop preserves first-match ordering and returns zero for an absent handle, retaining the original ambiguity with slot zero. IDO emits the original peeled and unrolled loop.

Raw object comparison records one differing relocation-immediate word: the original assembly names D_scene_00402CFC, while C references D_scene_00402CF8 plus four. A separate read-only MIPS HI16/LO16 comparison resolves every relocation using the actual scene linker script, verifies all targets and all 156 final instruction bytes, and passes with resolved function SHA-256 688f9fbc55e1bebfcdd8f4ccc7b3b53d6d0bfc745822c166a4140c1e95f49536. Evidence is worker_scene_alias_479.py and scene-slot-lookup-relocation-receipt.json; the raw mismatch remains recorded rather than reclassified as a raw byte match. Full packed scene module and fresh original-ROM checks remain mandatory. All symbol/export/linker references are renamed consistently. No new reachable original bug or behavior change is claimed.

Totals: 269 further recoveries after the 225 upstream ordinary imports, plus 263 existing C semantic cleanups. Current ledger: 931 assembly references = 870 ordinary + 61 entrypoints; 786,804 known remaining instruction bytes; zero unknown sizes; 1,100 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `480-scene-slot-lookup` and `accepted-scene-slot-lookup` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 269 further readable functions

Ten existing C routines receive descriptive names, parameters and comments. Graph evaluation retains endpoint clamping and exact interpolation order; insertion/removal preserve point limits, shifting, returned selection and caller-owned neighbor validity. Inverse lookup preserves its branch choice, strict range comparisons and endpoint behavior. Dynamic accessors document null handling, inclusive/unchecked index behavior, 0x170-byte record stride, parallel stores and the original integer address representation. Font reset retains its alternating static gate. The graph count-only loop remains because removing it changes original instructions; an empty do/while artifact in the linked-record accessor was removed with exact code preserved. All symbol/export/linker references are renamed consistently.

OC6 [Original graph range validation]: the existing inverse-curve C function leaves its last range index uninitialized when unequal range edges select no point below the upper edge. This is an invalid-input hazard; live caller reachability is unproven. Recommendation A: audit and document caller range/curve invariants during the continuing decomp, then apply any reachable runtime fix separately in recomp so original-ROM matching stays meaningful. Impact: caller tracing cost, with no speculative behavior change in matching C. Alternative B: retain the documented precondition until a reproducer identifies an affected caller. Impact: lower immediate effort but leaves invalid-input behavior unresolved. Point insertion also requires valid selected neighbors; dynamic getters retain the previously documented inclusive and negative-index hazards. No new reachable original bug or runtime behavior change is claimed.

Totals: 269 further recoveries after the 225 upstream ordinary imports, plus 273 existing C semantic cleanups. Current ledger: 931 assembly references = 870 ordinary + 61 entrypoints; 786,804 known remaining instruction bytes; zero unknown sizes; 1,090 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `484-graph-dyn-contracts` and `accepted-graph-dyn-contracts` verify real translation-unit instructions/full relocations, 4 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 270 further readable functions

The selection preview rotation becomes readable matching C, replacing 304 instruction bytes. The original routine translates around the supplied X/Z and stored Y, applies the original shared-angle Z rotation and supplied-angle X rotation with their scale constants, translates back and copies the result to the second matrix. Current-object reloads between exported calls preserve possible callback changes. The third incoming word remains an explicit unused parameter without inventing its original meaning. All symbol/export/linker references are renamed consistently.

Piece-release and oldest-skid reuse experiments remain isolated because their register/stack/unrolling differences are unresolved. No newly confirmed reachable original bug or runtime behavior change is claimed. The earlier OC6 graph invalid-range caller audit remains open.

Totals: 270 further recoveries after the 225 upstream ordinary imports, plus 273 existing C semantic cleanups. Current ledger: 930 assembly references = 869 ordinary + 61 entrypoints; 786,500 known remaining instruction bytes; zero unknown sizes; 1,090 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `491-selection-preview-rotation` and `accepted-selection-preview-rotation` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 271 further readable functions

The GUI text-list drawing routine now has a behavior-based name and readable C. It preserves translucent state-1 rendering, state-2 child drawing, the two original color selections, and state/count reloads around exported callbacks. Child-array capacity remains the original caller contract. Replay and result-submission drafts remain isolated because their instruction differences have not passed the acceptance gates. No new reachable runtime bug is established.

Totals: 271 further recoveries after the 225 upstream ordinary imports, plus 273 existing C semantic cleanups. Current ledger: 929 assembly references = 868 ordinary + 61 entrypoints; 786,200 known remaining instruction bytes; zero unknown sizes; 1,090 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `497-gui-text-list` and `accepted-gui-text-list` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 271 further readable functions

Twenty-six existing matching C routines now have behavior-based names, descriptive parameters and grounded contract comments. Resource loading and cleanup explain allocation ownership, block formats and original valid-asset requirements. Quaternion code identifies trace/largest-diagonal conversion, coordinate adjustment, the angular derivative and hemisphere-aware normalized blending. Matrix code identifies model-view/projection loads, submission counters and the original adjacent-state lookup. HSV conversion preserves the six hue sectors and out-of-range unchanged-output behavior. All symbol, export and linker references are renamed consistently. No runtime behavior changes or newly proven reachable faults are claimed. Existing assembly experiments remain isolated.

Totals: 271 further recoveries after the 225 upstream ordinary imports, plus 299 existing C semantic cleanups. Current ledger: 929 assembly references = 868 ordinary + 61 entrypoints; 786,200 known remaining instruction bytes; zero unknown sizes; 1,064 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `511-resource-math-contracts` and `accepted-resource-math-contracts` verify real translation-unit instructions/full relocations, 12 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 271 further readable functions

Thirty-nine existing matching C routines gain behavior-based names, descriptive parameters and contract comments. Listener code covers position/secondary-vector/velocity access, clock-based history and nearest-listener maximum-axis distance. Rendering channels identify getter/setter varargs, viewport/projection parameters, boundary callbacks, view transforms, clip ratios and debug drawing. Effects identify callback registration, frame caches, activity/kind, textured-quad submission, lifetime and visibility queuing. Pose code identifies optional channel copying and application, temporary animation evaluation and joint-matrix output. Two artificial empty checks are removed from pose application with exact function bytes preserved. Frustum-test/rebuild and queued-effect fake-code removal drafts remain isolated because their instructions differ.

OC7 [Original IA4 color adjustment]: the existing upstream annotation in func_uvcolor_rom_00404C54 identifies an uninitialized floating value used for the second packed IA4 pixel (format two, size four). This is an original invalid-value hazard; affected caller reachability is unproven. Recommendation A: trace format/size callers and preserve original matching C, then fix a reachable runtime defect separately in recomp. Impact: targeted caller analysis without speculative changes to original-ROM matching. Alternative B: defer a runtime change until a reproducer establishes an affected asset/caller. Impact: lower immediate effort but leaves that branch unresolved. Resource-loader malformed-input assumptions and previously documented original hazards remain caller-audit debt; no newly proven reachable runtime fault is claimed.

Totals: 271 further recoveries after the 225 upstream ordinary imports, plus 338 existing C semantic cleanups. Current ledger: 929 assembly references = 868 ordinary + 61 entrypoints; 786,200 known remaining instruction bytes; zero unknown sizes; 1,025 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `517-channel-ear-effects-contracts` and `accepted-channel-ear-effects-contracts` verify real translation-unit instructions/full relocations, 16 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 272 further readable functions

Recover racePlayPendingSoundByKind as readable matching C. The routine consumes a pending cue for kinds zero through two, selects the original sound ID and shared sound level, and leaves the pending flag untouched for other kinds. Specific cue meanings are not guessed. Bubble lifetime and environment/light candidates remain isolated because their instructions differ. Previously documented original-code hazards remain unchanged; no new runtime defect is claimed.

Totals: 272 further recoveries after the 225 upstream ordinary imports, plus 338 existing C semantic cleanups. Current ledger: 928 assembly references = 867 ordinary + 61 entrypoints; 785,864 known remaining instruction bytes; zero unknown sizes; 1,025 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `534-race-pending-sound` and `accepted-race-pending-sound` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 272 further readable functions

Fifty-seven active matching C routines gain behavior-based names, descriptive arguments and contract comments. Audio emitters identify positions, explicit velocity, segment distance, normalized volume/pan/pitch/mix, playback requests/completion, bank loading, playing-voice enumeration and Doppler ratio. Billboard code identifies callback attachment, frame marks, sphere overlap/query and release. Particle code identifies inactive-slot acquisition, matrices, triangle texture coordinates, lifetime/update/drawing, restart and simulation resets. The random-table C draft remains disabled behind NEEDS_RODATA and is deliberately excluded: a comparison of an inactive definition only tests its existing assembly. The candidate-freezing helper now rejects existing-C drafts with a corresponding assembly pragma until active-source proof is provided. All selected C definitions are outside such draft branches.

OC8 [Original particle fallback index]: func_uvpfx_rom_00400398 can use its uninitialized fallback index if no matching definition exceeds the original age threshold and no matching inactive slot exists. The routine is left unchanged; a caller/assets guarantee may make that path unreachable. Recommendation A: trace effect-kind registration and callers before any separate recomp correction. Impact: preserves original-ROM matching and avoids inventing a runtime change without reachability evidence. Alternative B: defer a correction until an affected effect/reproducer is found. Impact: less immediate investigation, unresolved invalid-kind behavior. Previously documented original-code hazards remain unchanged.

Totals: 272 further recoveries after the 225 upstream ordinary imports, plus 395 existing C semantic cleanups. Current ledger: 928 assembly references = 867 ordinary + 61 entrypoints; 785,864 known remaining instruction bytes; zero unknown sizes; 968 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `546-emitter-billboard-particles` and `accepted-emitter-billboard-particles` verify real translation-unit instructions/full relocations, 9 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 273 further readable functions

Recover bubbleUpdateLifetimeAndTransform as clean typed matching C. Joint initialization of start and duration preserves the original IDO compiler schedule; no one-shot loop, padding or artificial statement is retained from the diagnostic search. Normalized age drives scale, threshold model replacement and fade alpha before submitting the translated matrix. The original positive-duration/object-ownership contract is unchanged.

Active-C audit correction: 590 previously accepted named routines were checked for simultaneous C definitions and assembly pragmas. One earlier font reset-gate name, uvFontAdvanceResetGate (original func_uvfont_rom_00400840), still resides in a NEEDS_DATA draft branch. Its descriptive assembly alias remains valid, but it must not count as an active C semantic cleanup. The cumulative existing-C cleanup count is reduced by one. Isolated active-C recovery attempts differ and remain unaccepted; the existing assembly reference was never removed. The trial-freezing helper now rejects such inactive-C comparisons unless the proposed replacement removes the entire draft/assembly conditional. Previously documented original-code hazards, including OC8 [Original particle fallback index], remain unchanged.

Totals: 273 further recoveries after the 225 upstream ordinary imports, plus 394 existing C semantic cleanups. Current ledger: 927 assembly references = 866 ordinary + 61 entrypoints; 785,524 known remaining instruction bytes; zero unknown sizes; 968 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `561-bubble-lifetime` and `accepted-bubble-lifetime` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 273 further readable functions

Ninety-nine active matching C routines gain behavior-based names, descriptive arguments and contract comments. Sound code identifies generation-stamped managed handles, replacement priority, playback/control, stored versus live parameters, metadata/sample rates, routing and suppression. Debug code identifies the 18 profiling timestamp slots, measured scheduler-event intervals, time bars, graphics counters, overlay dispatch, font selection and statistics forwarding. Geometry code identifies owned display-list lifetime, descriptor initialization, vertex-range overrides and mesh/grid submission; two loader callbacks remain explicitly reserved. All 99 individual real translation-unit comparisons matched complete original C symbols and relocation targets, and every selected definition was checked to be active rather than an assembly-backed draft. Original caller-owned bounds, deliberate fault paths and reserved entrypoints remain unchanged. Previously recorded original-code hazards and the one-font-draft progress correction remain in force; no new proven reachable runtime defect is claimed.

Totals: 273 further recoveries after the 225 upstream ordinary imports, plus 493 existing C semantic cleanups. Current ledger: 927 assembly references = 866 ordinary + 61 entrypoints; 785,524 known remaining instruction bytes; zero unknown sizes; 869 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `566-sound-debug-geometry-contracts` and `accepted-sound-debug-geometry-contracts` verify real translation-unit instructions/full relocations, 17 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 276 further readable functions

Recover three routines as clean typed matching C: motionAccumulateScaledBasisVectors, tdataApplyScalarRegions and triganimCreateTransformNode. The motion routine preserves weighted Z/X/Y sums and separate shared/per-component scaling without guessing physical units. Track-region processing preserves strict interior comparisons, overlapping callback applications, fresh data reads and the actual float argument ABI of the adjustment helper. Trigger-node creation preserves allocation/list order, two matrix copies, original model setup and mode-controlled object flags.

OC9 [Original object failure check]: triganimCreateTransformNode tests the dynamic-object allocation result only for a negative value, whereas uvDobjCreate returns positive 0xFFFF when its pool is full. The original exhaustion path can therefore continue with an invalid object ID. This verified sentinel mismatch is preserved for matching; pool exhaustion at game callers has not been demonstrated. Recommendation A: audit trigger callers and object-pool demand, then fix a reachable exhaustion case separately in recomp. Impact: targeted investigation preserves matching and avoids speculative changes during source recovery. Alternative B: defer a runtime fix until a full-pool reproducer exists. Impact: less immediate effort, unresolved exhaustion behavior. Other previously recorded original hazards remain unchanged.

Totals: 276 further recoveries after the 225 upstream ordinary imports, plus 493 existing C semantic cleanups. Current ledger: 924 assembly references = 863 ordinary + 61 entrypoints; 784,428 known remaining instruction bytes; zero unknown sizes; 869 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `571-basis-regions-trigger-nodes` and `accepted-basis-regions-trigger-nodes` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 276 further readable functions

Name and document 67 active existing C routines across compressed-sequence audio, the audio manager, graphics state and model processing. MIDI wrappers now distinguish player state changes from immediate MIDI messages; voice-phase collectors describe their exclusive tail and output-capacity contracts. Audio-manager volume/output state, bounded effects parameters and callback lists receive concrete names. Graphics code describes texture bits, depth/culling commands, fog parameter storage, statistics buffers and cleanup. Model code names inclusive local bounds, transformed-point tests, threshold bands, matrix stack operations and texture-state visits. Original unchecked caller contracts and index behavior remain explicit; opaque fields retain offset-based names. Two conditional graphics C drafts are excluded and do not count as active cleanup. All previously recorded original hazards remain unchanged.

Totals: 276 further recoveries after the 225 upstream ordinary imports, plus 560 existing C semantic cleanups. Current ledger: 924 assembly references = 863 ordinary + 61 entrypoints; 784,428 known remaining instruction bytes; zero unknown sizes; 802 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `575-audio-graphics-model-contracts` and `accepted-audio-graphics-model-contracts` verify real translation-unit instructions/full relocations, 18 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 277 further readable functions

Recover replayFindDirectedSpatialRecord as typed matching C. Walk replay records in original order, compare squared displacement against each strict radius, normalize a positive-length displacement and apply the original mapped dot-product threshold. Successful lookup copies the direction and distance; failure returns null without writing outputs. Vector roles and threshold units remain deliberately unguessed. All previously recorded original hazards remain unchanged.

Totals: 277 further recoveries after the 225 upstream ordinary imports, plus 560 existing C semantic cleanups. Current ledger: 923 assembly references = 862 ordinary + 61 entrypoints; 784,012 known remaining instruction bytes; zero unknown sizes; 802 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `581-replay-directed-spatial-query` and `accepted-replay-directed-spatial-query` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 279 further readable functions

Recover sceneBlendEightWordRecord and motionApplyGatedModeResponse as typed matching C. Scene blending copies endpoint records outside the interpolation interval, blends seven floats and chooses the leading integer key with the original midpoint/zero-selector rules. Its field read order remains safe for the same aliases as the original. Motion response preserves enabled/input/field-magnitude gates, mode zero/two handling, exponential-style response updates, signed 0x988 bounds and all original NaN comparison paths. Physical units are unproven and no runtime tuning is introduced. All previously recorded original hazards remain unchanged.

Totals: 279 further recoveries after the 225 upstream ordinary imports, plus 560 existing C semantic cleanups. Current ledger: 921 assembly references = 860 ordinary + 61 entrypoints; 783,232 known remaining instruction bytes; zero unknown sizes; 802 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `592-scene-blend-mode-response` and `accepted-scene-blend-mode-response` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 280 further readable functions

Recover raceReleaseManagedSoundsAndClearBytes as matching C, preserving fourteen managed-handle releases and the four subsequent shared byte clears in exact order. Name and document 37 active existing C routines covering query-array ownership, caller-supplied overrides, hit-count addresses and secondary state; terrain/channel binding, packed triangle-vector/texture decoding and shared scalar values; and GUI row attachment, panel/text-list drawing and state setters. Do not infer array ownership, capacity checks or opaque field units absent from original code. All previously recorded original hazards remain unchanged.

Totals: 280 further recoveries after the 225 upstream ordinary imports, plus 597 existing C semantic cleanups. Current ledger: 920 assembly references = 859 ordinary + 61 entrypoints; 782,828 known remaining instruction bytes; zero unknown sizes; 765 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `601-race-query-terrain-gui-contracts` and `accepted-race-query-terrain-gui-contracts` verify real translation-unit instructions/full relocations, 6 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 281 further readable functions

Recover flagAdjustPositionByDistanceBands, preserving the two strict squared-radius gates, distinct displacement fractions and float operation order without inferring physical units or altering original edge cases. Clarify 46 active existing C functions: selection input wrapping, per-player transmission bytes, independently gated sound IDs, time composition and sprite deletion; shared matrix copies and axis storage; loader/intersection/texture-animation teardown; counter sampling, GUI audio/debug callbacks, primitive color and small dynamic/LED/intersection state contracts. Keep caller-owned bounds and original cleanup behavior unchanged. No new runtime defect is claimed.

Totals: 281 further recoveries after the 225 upstream ordinary imports, plus 643 existing C semantic cleanups. Current ledger: 919 assembly references = 858 ordinary + 61 entrypoints; 782,424 known remaining instruction bytes; zero unknown sizes; 719 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `616-flag-menu-resource-contracts` and `accepted-flag-menu-resource-contracts` verify real translation-unit instructions/full relocations, 17 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 284 further readable functions

Recover menuslctDrawSolidRectangle, menuslctDrawGradientRectangle and plyrDrawRedArrowWithShadow as matching readable C. The menu routines preserve fixed 320-by-240 orthographic setup, untextured flags, vertex order and state restoration; the player arrow preserves current-screen projection, supplied-matrix translation, red triangle and translucent offset shadow. Do not alter layout, rendering order or caller coordinates. No new runtime defect is claimed.

Totals: 284 further recoveries after the 225 upstream ordinary imports, plus 643 existing C semantic cleanups. Current ledger: 916 assembly references = 855 ordinary + 61 entrypoints; 780,432 known remaining instruction bytes; zero unknown sizes; 719 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `632-menu-rectangles-player-arrow` and `accepted-menu-rectangles-player-arrow` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 284 further readable functions

Name and document 35 active existing C routines covering item-module cleanup, powerup/result lookup fallbacks, sprite allocation, texture-animation ownership, intro sprites, ripple callback registration, guarded AI state, GUI state requests, query index pairs and graphics scalar overrides. Clarify player-count/tournament/language/AI-count selection callbacks without inventing labels for unproven IDs. Preserve display-list scanning and texture address patching exactly. Other previously recorded original hazards remain unchanged.

* **OC10 — Original display-list end test.**
  dleditFindOpcodeWithOriginalEndTest sign-extends each opcode byte but compares it with positive 0xDF (223). The original assembly and rebuilt object both contain this impossible end-marker comparison; a missing requested opcode can therefore scan beyond the list. The only direct named C caller is the texture-image patcher searching for 0xFD; indirect export callers and asset guarantees remain unproven.
  * **A (recommended):** Trace exported scanner/patcher callers and verify their display lists contain the requested opcode before any separate recomp correction.
    *Impact:* preserves original-ROM matching and scopes a runtime correction to a demonstrated reachable case.
  * **B:** Defer a runtime correction until a missing-opcode reproducer exists.
    *Impact:* avoids speculative asset assumptions but leaves the original malformed-list behavior unresolved.

Totals: 284 further recoveries after the 225 upstream ordinary imports, plus 678 existing C semantic cleanups. Current ledger: 916 assembly references = 855 ordinary + 61 entrypoints; 780,432 known remaining instruction bytes; zero unknown sizes; 684 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `635-item-menus-display-contracts` and `accepted-item-menus-display-contracts` verify real translation-unit instructions/full relocations, 21 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 286 further readable functions

Recover victoryPlayPendingSoundsByKind and medPackScaledSharedRgba. Preserve all four pending-sound branches, unlock voice gates, flag-clear order and final emitter IDs. Preserve each floating color calculation, unsigned conversion and low-byte packing without clamping or guessing exceptional conversion behavior. The original victory symbol includes twelve alignment bytes after its 876 instruction bytes; the source recovery removes 876 instruction bytes from the remaining ledger. Previously recorded original hazards, including OC10 [Original display-list end test], remain unchanged.

Totals: 286 further recoveries after the 225 upstream ordinary imports, plus 678 existing C semantic cleanups. Current ledger: 914 assembly references = 853 ordinary + 61 entrypoints; 778,892 known remaining instruction bytes; zero unknown sizes; 684 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `642-victory-audio-shared-rgba` and `accepted-victory-audio-shared-rgba` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 287 further readable functions

Recover uvDynSolveFactoredSystemInPlace, a zero-based factored linear-system solve that overwrites the right-hand side. Name row, column, pivot and first-nonzero state, explain the two substitution phases, and preserve the original nonzero-diagonal caller precondition. The inclusive forward-loop bound produces the exact original instruction sequence; no padding, artificial accesses or ABI changes are used. The unrelated AI response-band candidate failed instruction comparisons and remains outside accepted sources.

Totals: 287 further recoveries after the 225 upstream ordinary imports, plus 678 existing C semantic cleanups. Current ledger: 913 assembly references = 852 ordinary + 61 entrypoints; 778,280 known remaining instruction bytes; zero unknown sizes; 684 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `652-lu-back-substitution` and `accepted-lu-back-substitution` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 287 further readable functions

Clean up thirty active C option, resource, lookup and callback contracts. Cover music, sound-effect and speech volume options; stereo/mono application; menu mode selection; player transmission and horn sound selection; bounded scene/letter lookups; particle-loader dependencies/media; dynamics counters; camera channel release; flag callback attachment; AI scalar reset; GUI states five/six; one-shot replay transition; and the shared file pending flag. Offset-only fields retain honest unresolved meanings. No original validation or ownership behavior is changed, and no unrelated failed candidate is included.

Totals: 287 further recoveries after the 225 upstream ordinary imports, plus 708 existing C semantic cleanups. Current ledger: 913 assembly references = 852 ordinary + 61 entrypoints; 778,280 known remaining instruction bytes; zero unknown sizes; 654 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `660-options-lookups-channel-contracts` and `accepted-options-lookups-channel-contracts` verify real translation-unit instructions/full relocations, 15 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 288 further readable functions

Recover selectionDrawFilledRectangleOrSteppedBorder using explicit vertex-coordinate expressions and preserve all triangle/state operations. Clean up eighteen active C contracts for seven-segment LED drawing/color/position, pending pause sounds, replay toggle, environment drawing/properties, debug HUD dispatch, selection sprite state, weapon/powerup pools, dependency and sound-handle release, packed contour triangles, finished explosion handles and AI linked records. Removing an empty branch in the separate environment-sound initializer changed sixteen instructions, so that candidate is excluded entirely. No artificial padding, no-op branch or register-allocation workaround is introduced.

Totals: 288 further recoveries after the 225 upstream ordinary imports, plus 726 existing C semantic cleanups. Current ledger: 912 assembly references = 851 ordinary + 61 entrypoints; 776,708 known remaining instruction bytes; zero unknown sizes; 636 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `673-led-effects-pool-border` and `accepted-led-effects-pool-border` verify real translation-unit instructions/full relocations, 12 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 288 further readable functions

Review and integrate 143 active existing-C readability improvements prepared by three subagents: 35 engine and graphics contracts, ten battle callbacks, 21 sound and utility contracts, 27 SDK/controller/animation contracts and 50 menu and game callbacks. Names, parameter/local identifiers and comments describe observed behavior without inventing unknown units. Preserve original caller bounds and failure behavior; correct historical comments that misidentified sound suppression/initialization, channel rendering and object flags. Individual real translation-unit instruction/relocation comparisons passed before integration. Source-level sound-ramp target limits and Controller Pak punctuation arithmetic remain audit debt pending caller/provenance checks; no runtime correction is introduced into the matching branch.

Totals: 288 further recoveries after the 225 upstream ordinary imports, plus 869 existing C semantic cleanups. Current ledger: 912 assembly references = 851 ordinary + 61 entrypoints; 776,708 known remaining instruction bytes; zero unknown sizes; 493 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `678-older-engine-sdk-menu-contracts` and `accepted-older-engine-sdk-menu-contracts` verify real translation-unit instructions/full relocations, 48 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 289 further readable functions

Recover selectionAdjustLanguageAndReloadTextures as readable C with explicit language resource lists. A raw object difference uses gGameSettings plus currentLanguage offset 0x174 instead of D_80025E64. Independent worker_language_alias_688.py resolves every HI16/LO16/26 relocation against linker addresses and the freshly validated kernel ELF: all 1284 linked bytes and all targets agree. Keep the raw difference as evidence; packed-module/full-ROM proof remains mandatory.

### Preserved older-code contract audit debt

* **OC11 — Original synchronous volume ramp.**
  sndRaiseSoundVolumeWithImmediateRamp clamps each increment to one while looping until the supplied target is reached. Targets above one cannot terminate. Its accepted object and packed sound module match the original; a game-reachable invalid target is not established.
  * **A (recommended):** Trace indirect sound-export callers and valid target ranges before a separate recomp correction.
    *Impact:* Establishes player impact while preserving original matching behavior.
  * **B:** Defer correction until a concrete invalid-target reproduction.
    *Impact:* Leaves the exposed invalid-target contract unresolved.

* **OC12 — Original memory-card punctuation encoding.**
  uvControllerEncodePakNameCharacter uses the punctuation table byte plus 0x34 rather than its index. For example, exclamation encodes as 0x55, which the paired decoder maps to dash. Both accepted functions and the packed controller module match the original; actual BAR names and player impact remain under audit.
  * **A (recommended):** Trace actual game/extension name strings before considering a separate recomp correction.
    *Impact:* Distinguishes unused SDK behavior from damaged player-visible memory-card names.
  * **B:** Preserve the original mapping until an affected name is reproduced.
    *Impact:* Avoids an unsupported compatibility change while leaving punctuation round trips unresolved.

Totals: 289 further recoveries after the 225 upstream ordinary imports, plus 869 existing C semantic cleanups. Current ledger: 911 assembly references = 850 ordinary + 61 entrypoints; 775,424 known remaining instruction bytes; zero unknown sizes; 493 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `689-language-texture-switch` and `accepted-language-texture-switch` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 289 further readable functions

Integrate 51 further active existing-C readability improvements: 36 newly named functions and 15 public vector/matrix/callback helpers with clearer parameters and behavioral contracts. Mark unproven meanings with RE_UNKNOWN and preserved original anomalies with RE_ORIGINAL_QUIRK. Add tools/uncertainty_index.py and generated docs/UNCERTAINTIES.md plus docs/UNCERTAINTIES.json. The deterministic index supplies physical source lines, stable search-group IDs, source hashes, query mode and a mandatory freshness check after future source/doc waves. It covers recognizable unknown conventions and explicit comments, including inactive conditional drafts; it cannot discover assumptions that have not yet been identified. Padding is indexed as layout to preserve, not a code-removal task. A lexical fixture verifies that identifier-like text inside literals/comments is not miscounted, physical lines remain correct and conditional assembly is included.

The targeted Controller Pak caller audit found normal active-C game initialization uses BEETLE RACING and an empty extension. Four observed active menu lookup paths forward those values and do not exercise the punctuation mapping defect. Remaining assembly allocation callers and indirect name writes remain RE_UNKNOWN; OC12 [Original memory-card punctuation] stays audit debt with no demonstrated BAR player impact.

For every future source wave, regenerate the uncertainty index after source and strategy edits and run `python3 tools/uncertainty_index.py --check` before proof/landing. Use `--query NAME` to retrieve every indexed location. New comments must explain known observations, the remaining unknown and evidence needed to resolve it; do not substitute guessed field meanings. Full readable decompilation remains in progress.

Totals: 289 further recoveries after the 225 upstream ordinary imports, plus 920 existing C semantic cleanups. Current ledger: 911 assembly references = 850 ordinary + 61 entrypoints; 775,424 known remaining instruction bytes; zero unknown sizes; 457 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `698-older-code-uncertainty-index` and `accepted-older-code-uncertainty-index` verify real translation-unit instructions/full relocations, 21 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all 1,013 source hashes. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 290 further readable functions

Recover selectionApplyChosenLanguageAndReloadTextures as readable C. The assignment inside the comparison preserves the original unconditional signed-word language store, including unchanged choices, before deciding whether to replace thirteen texture resources. Keep post-asset shared-state reloads and return through the linked menu node. Explicit RE_UNKNOWN documents that the associated speed-option units remain unproven; no field or numeric language meaning is guessed.

Totals: 290 further recoveries after the 225 upstream ordinary imports, plus 920 existing C semantic cleanups. Current ledger: 910 assembly references = 849 ordinary + 61 entrypoints; 774,112 known remaining instruction bytes; zero unknown sizes; 457 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `711-chosen-language-menu` and `accepted-chosen-language-menu` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 290 further readable functions

Give 45 existing C routines meaningful names and contracts: fourteen intersection helpers, eight vertex-attribute helpers and twenty-three gameplay/menu support functions. Preserve original arithmetic, pointer aliasing, branch-dependent outputs, texture/resource filtering, Pak lookups, callback latching and voice/sound behavior. Document observed quirks without guessing missing gameplay meanings; RE_UNKNOWN and RE_ORIGINAL_QUIRK markers enter the regenerated searchable uncertainty index.

Totals: 290 further recoveries after the 225 upstream ordinary imports, plus 965 existing C semantic cleanups. Current ledger: 910 assembly references = 849 ordinary + 61 entrypoints; 774,112 known remaining instruction bytes; zero unknown sizes; 412 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `717-older-geometry-gameplay-contracts` and `accepted-older-geometry-gameplay-contracts` verify real translation-unit instructions/full relocations, 9 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 290 further readable functions

Clarify twenty existing public font, string and floating-matrix functions without changing their exported names. Explain glyph and message handling, length-first string comparison, permissive parsing and fixed two-digit float formatting, local transforms and matrix multiplication order. Preserve all machine behavior; explicitly mark uncertain caller ranges, buffer capacities and the rotation-only inverse prerequisite, alongside original helper quirks.

Totals: 290 further recoveries after the 225 upstream ordinary imports, plus 985 existing C semantic cleanups. Current ledger: 910 assembly references = 849 ordinary + 61 entrypoints; 774,112 known remaining instruction bytes; zero unknown sizes; 412 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `720-font-string-matrix-contracts` and `accepted-font-string-matrix-contracts` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 290 further readable functions

Correct fifteen misleading or overconfident older comments and rename gameGuiRegisterChannelSixCallback to gameGuiRegisterChannelCallback: six is the property selector applied to the supplied channel. Preserve all runtime behavior. Flag camera-scalar units, matrix coordinate space and language-label mappings as unproven. Document two previously unreviewed matrix conversion contracts using original-equivalent instructions and an active-C caller audit.

### Preserved older-code contract audit debt

* **OC13 — Original matrix conversion aliasing.**
  uvMat4CopyF2L selects temporary storage when source and destination are identical, then compares the changed pointer against the source, skipping copy-back under ordinary caller stack ownership. uvMat4CopyL2F uses a by-value fixed matrix and retains a redundant alias/copy-back path. Original-equivalent instruction dumps and packed-module equality establish that this is original behavior. All four observed active-C F2L callers use separate storage; remaining assembly and opaque export callers have not been fully audited. No player-visible failure is established.
  * **A (recommended):** Trace remaining assembly and indirect callers for actual same-storage conversion before a separate recomp correction.
    *Impact:* Preserves original matching behavior and avoids changing unused SDK edge cases without evidence.
  * **B:** Defer runtime correction until a same-storage game caller is reproduced.
    *Impact:* Leaves the confirmed aliasing contract unresolved while retaining original compatibility.

The uncertainty index now records a comment carrying both RE_UNKNOWN and RE_ORIGINAL_QUIRK under both categories. A focused fixture confirms both searchable categories, distinct deterministic IDs and the correct physical source location; neither marker hides the other.

Totals: 290 further recoveries after the 225 upstream ordinary imports, plus 987 existing C semantic cleanups. Current ledger: 910 assembly references = 849 ordinary + 61 entrypoints; 774,112 known remaining instruction bytes; zero unknown sizes; 412 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `724-comment-evidence-boundaries` and `accepted-comment-evidence-boundaries` verify real translation-unit instructions/full relocations, 6 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 292 further readable functions

Recover selectionAdjustTrackAndReloadPreviewSprites (1112 bytes) and flagDrawVisibleRegisteredRecords (356 bytes) as readable C. Preserve the three sprite assets, original UVBT unload/load/free/create order, automatic-draw flags, centering arithmetic and shared track-index reloads. Preserve the flag channel-position query, original bounds query, graphics-state mask operations and list traversal; explicit RE_UNKNOWN notes retain the unproven image roles, extent meanings and per-record helper behavior. Correct one older comment that described graphics waiting/shared-array release as flushing.

Totals: 292 further recoveries after the 225 upstream ordinary imports, plus 987 existing C semantic cleanups. Current ledger: 908 assembly references = 847 ordinary + 61 entrypoints; 772,644 known remaining instruction bytes; zero unknown sizes; 412 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `740-preview-visible-flags` and `accepted-preview-visible-flags` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 294 further readable functions

Recover uvGfxGetPreviousBufferCounter (348 bytes) and miscCreateGuiBoundScalarRow (388 bytes). C now owns the complete 64-byte graphics readonly section: two double-precision0.1 objects, two single-precision fog limits, nine original switch targets and four zero alignment bytes. IDO5.3 places readonly aggregate constants correctly under the existing compiler options, so one-element arrays preserve each original label, size and bits. An independent ELF relocation proof resolves the raw table-base symbol/addend difference; all348 linked instruction bytes and all64 readonly bytes agree. The GUI routine preserves signed-short widget allocation results, flag-two integer conversion versus raw float reads, callbacks and fixed-width labels. RE_UNKNOWN comments retain unproven counter abbreviations, kind bits and physical units. Full readable decompilation remains incomplete.

Totals: 294 further recoveries after the 225 upstream ordinary imports, plus 987 existing C semantic cleanups. Current ledger: 906 assembly references = 845 ordinary + 61 entrypoints; 771,908 known remaining instruction bytes; zero unknown sizes; 411 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `769-module-section-prerequisites` and `accepted-graphics-statistics-gui-scalar-source-filter` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.

The first build attempt in wave762 failed on duplicate graphics constants because partial linking discovered a stale generated .rodata.o after its assembly source disappeared. No acceptance receipt or commit was made from that failed build. Module section prerequisites now derive from current assembly sources, so stale objects cannot reintroduce C-owned readonly/data/BSS sections, and missing current objects remain explicit make prerequisites. The replacement wave retains the failed build log and validates the stale-object transition with the complete original modules and ROM.

The initial source-filter correction in wave766 also failed before acceptance: GNU make expanded the percent characters inside patsubst as pattern-rule stems, leaving assembly source paths in the link command. The corrected prerequisite expression uses basename/addsuffix/addprefix without percent characters. A GNU make fixture verifies existing section sources map to object prerequisites, missing current objects are scheduled, and stale objects without sources are excluded. Failed wave766 logs remain retained.


## Historical accepted checkpoint — 294 further readable functions

Review131 original empty C functions. Twenty receive evidence-supported names:16 generic module-unload cleanup slots, two controller peripheral hooks, the missing-track-data fallback and the fileux host-buffer hook. Another111 retain their current address-based names and receive RE_UNKNOWN comments identifying their unresolved purpose/caller/export roles. No unknown role is invented and no function body, signature or distinct identity changes. All131 isolated real translation-unit comparisons preserve complete original instructions and relocation targets. Only20 functions count toward existing-C semantic cleanup totals; the111 comment-only annotations are uncertainty coverage, not semantic naming completion.

Totals: 294 further recoveries after the 225 upstream ordinary imports, plus 1007 existing C semantic cleanups. Current ledger: 906 assembly references = 845 ordinary + 61 entrypoints; 771,908 known remaining instruction bytes; zero unknown sizes; 391 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `776-older-noop-uncertainties` and `accepted-older-noop-uncertainties` verify real translation-unit instructions/full relocations, 63 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 294 further readable functions

Review35 older nonempty C functions: name16 previously address-named environment/loader/game wrappers, correct one already-reviewed pause helper to pauseOpenConfirmationWithCancelSoundSuppressed, and retain18 neutral names with explicit uncertainty comments. Preserve all types, expressions, field names and control flow; only grounded function/local names and comments change. All35 isolated real translation-unit comparisons reproduce complete original function instructions and relocation targets. The pause helper suppression call does not play sound. Only the16 newly named functions count toward unique existing-C semantic cleanup totals; the corrected prior name and18 uncertainty annotations do not inflate completion. Record the original environment slot boundary as audit debt, preserving original checks in the matching decomp.

The uncertainty index additionally recognizes unresolved Unk-prefixed type names and plain pad/padding/prefix/gap storage fields. Focused deterministic fixtures verify literal/comment masking, physical source locations despite #line, independent unknown/quirk markers, stable existing records and IDs, and negative substring cases. The collector implementation is unchanged; only naming patterns and the type category are extended. Known gaps are searchable, but the index does not prove all hidden assumptions have been discovered.

## Original-code audit debt

* **OC14 — Environment assignment boundary.**
  Environment initialization allocates and initializes exactly count table entries. The exported assignment and getter accept slot equal to count and negative slots, which address storage outside that stated allocation. No outside-module named C caller or player-visible failure was found; remaining assembly and indirect export callers are untraced. Matching decompilation preserves these original checks.
  * **A (recommended):** Trace export and assembly callers to establish the valid slot contract, then consider a separate recomp guard requiring 0 <= slot < count while retaining existing invalid-value return/no-write behavior.
    *Impact:* Requires caller tracing and keeps speculative runtime changes out of the matching decompilation.
  * **B:** Wait for a reproducible invalid-slot call before changing runtime behavior.
    *Impact:* Avoids speculative fixes but retains the confirmed unchecked boundary.


Totals: 294 further recoveries after the 225 upstream ordinary imports, plus 1023 existing C semantic cleanups. Current ledger: 906 assembly references = 845 ordinary + 61 entrypoints; 771,908 known remaining instruction bytes; zero unknown sizes; 375 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `782-older-nonempty-uncertainties` and `accepted-older-nonempty-uncertainties` verify real translation-unit instructions/full relocations, 13 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 296 further readable functions

Recover selectionUpdateFourSlotStatesAndPivot (328 bytes) and aiUpdateExplosionEffectAndRestoreDelay (460 bytes). The selection switch preserves choices zero/one/two, four indexed state calls and repeated shared-menu reads around input and dirty-flag updates. The AI routine preserves original effect/audio calls and store order, the same-call positive-to-minus-one phase transition, object bit-one clear/restore and the original !(remaining > 0) expiry including NaNs. Explicit RE_UNKNOWN comments retain unproven menu labels, helper contracts, effect parameter and property meanings, field meanings and scalar units. Both finalized real translation-unit candidates match every original instruction word and relocation target; relocation-list ordering alone differs for AI. No uncertain semantics are promoted to facts.

Totals: 296 further recoveries after the 225 upstream ordinary imports, plus 1023 existing C semantic cleanups. Current ledger: 904 assembly references = 843 ordinary + 61 entrypoints; 771,120 known remaining instruction bytes; zero unknown sizes; 375 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `789-menu-ai-effects` and `accepted-menu-ai-effects` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 298 further readable functions

Recover __entrypoint_func_gameGuiInitializeModuleExports (168 bytes) and __entrypoint_func_letterInitializeModuleAndObjectPool (320 bytes). Preserve the GUI eleven-word export-address initialization and the letter three proven callback contracts, four model/four texture load order and twenty 36-byte record prefixes. Original N64 32-bit byte-address arithmetic preserves pool reloads and operand order; the existing shared pool remains a pointer. Unknown GUI callback signatures are stored as explicitly labeled address words, without invented callable prototypes. Comments retain unknown asset roles, remaining fields, ownership and original unchecked allocation. Extend offset-field indexing to opaque hexadecimal names and separately index explicitly unused identifiers as review aids, without asserting missing implementation. Focused fixtures preserve literal/comment masking, physical source locations, deterministic existing IDs/records, inactive branches and independent unknown/quirk markers. Both complete real translation-unit instruction and relocation comparisons pass.

Totals: 298 further recoveries after the 225 upstream ordinary imports, plus 1023 existing C semantic cleanups. Current ledger: 902 assembly references = 843 ordinary + 59 entrypoints; 770,632 known remaining instruction bytes; zero unknown sizes; 375 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `798-module-initializers-entry-prefix` and `accepted-module-initializers-uncertainties` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


The first frozen initializer build (795-module-initializers-uncertainties) failed in module packing: `setCommEntryPointOffset` requires an STT_FUNC symbol beginning with `__entrypoint_func`. The initial descriptive names removed that required prefix. No failed build or stale ROM was accepted. The corrected readable names retain `__entrypoint_func_` before their descriptive suffix; the existing packer is unchanged. The new frozen 798-module-initializers-entry-prefix build must pass every original packed-module/ROM/source/index gate before acceptance. Original isolated function bytes already matched.


## Historical accepted checkpoint — 299 further readable functions

Recover aiSnapshotAndUpdateDecisionState (448 bytes), preserving transform/vector snapshots, the original camera-result word contract, timer load after the Manhattan-distance helper, positive-only decrement, ordered NaN-sensitive thresholds, shared link-counter effects and terminal dispatch order. RE_UNKNOWN notes identify units, phase ownership, dispatch roles and the valid-link-node precondition, with caller/callee evidence needed to settle them. Apply twelve token-identical older-comment corrections across utility, vehicle and engine modules: remove unsupported randomized-field roles and camera ownership; mark the legacy editor argument contract, shared AI index lifetime, basis input constraints, one-sample history scheduling, model dependency/block ownership, texture fallback lifetime and particle raw-word ownership. Correct the battle clear-bit description and replace the disproven environment wrong-target warning with its verified lookup-builder identity. These comments add no semantic cleanup counts and do not change original behavior. Finalized AI candidate matches all 448 original instruction bytes and relocation targets. All affected packed modules, original full ROM and complete manifest/index gates must pass before landing.

Totals: 299 further recoveries after the 225 upstream ordinary imports, plus 1023 existing C semantic cleanups. Current ledger: 901 assembly references = 842 ordinary + 59 entrypoints; 770,184 known remaining instruction bytes; zero unknown sizes; 375 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `811-ai-snapshot-older-unknowns` and `accepted-ai-snapshot-older-unknowns` verify real translation-unit instructions/full relocations, 11 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Current accepted checkpoint — 300 further readable functions

Recover __entrypoint_func_uvmathInitializeExports (264 bytes). All nineteen ordered export offsets and targets are independently audited against original SW/LO16 pairs, then validated in the real translation unit with exact complete instruction and relocation equality. Replace the entire inactive draft/assembly conditional, removing bogus integer declarations for functions and using their active recovered signatures. Keep existing raw-address fields 0x38/0x48 for proven counter-fraction/angle-fold targets; mark their wider indirect-consumer contracts as RE_UNKNOWN with caller evidence needed. Preserve the reserved __entrypoint_func prefix required by the module packer. No math routines, constants or shared-header ABI are changed. Full packed-module, fresh original-ROM, manifest and uncertainty-index gates precede landing.

Totals: 300 further recoveries after the 225 upstream ordinary imports, plus 1023 existing C semantic cleanups. Current ledger: 900 assembly references = 842 ordinary + 58 entrypoints; 769,920 known remaining instruction bytes; zero unknown sizes; 374 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `817-math-ledger-correction` and `accepted-math-module-initializer-ledger-corrected` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.
