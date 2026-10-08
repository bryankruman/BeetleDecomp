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
matching C are preserved with `#line`. The current ledger has **839** assembly references:
**796** ordinary functions and **43** entrypoints, with **748,864** known instruction bytes
and no unknown sizes. The broader name audit still finds **301** address-named C definitions.
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


## Historical accepted checkpoint — 300 further readable functions

Recover __entrypoint_func_uvmathInitializeExports (264 bytes). All nineteen ordered export offsets and targets are independently audited against original SW/LO16 pairs, then validated in the real translation unit with exact complete instruction and relocation equality. Replace the entire inactive draft/assembly conditional, removing bogus integer declarations for functions and using their active recovered signatures. Keep existing raw-address fields 0x38/0x48 for proven counter-fraction/angle-fold targets; mark their wider indirect-consumer contracts as RE_UNKNOWN with caller evidence needed. Preserve the reserved __entrypoint_func prefix required by the module packer. No math routines, constants or shared-header ABI are changed. Full packed-module, fresh original-ROM, manifest and uncertainty-index gates precede landing.

Totals: 300 further recoveries after the 225 upstream ordinary imports, plus 1023 existing C semantic cleanups. Current ledger: 900 assembly references = 842 ordinary + 58 entrypoints; 769,920 known remaining instruction bytes; zero unknown sizes; 374 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `817-math-ledger-correction` and `accepted-math-module-initializer-ledger-corrected` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 300 further readable functions

Clean fifteen existing active C functions: six main-image glyph/hex/address/stack-trace routines, four file-manager listing/lookup/texture-table routines, four allocator fill/coalesce/reset helpers and one module tag lookup. Each finalized original-symbol candidate matches the complete accepted ELF function and every relocation, while inverse token audits preserve all operations, declarations, old matching scaffolding and existing prototypes. Global renames preserve callers and linker metadata. Comments explicitly flag uncertain debug totals, preceding-base ownership versus containment, UVTP lifetime, active-thread stack-fill range, original FAKE source forms, buffer/caller bounds, fixed glyph text/trigger and opcode-heuristic limits; they specify producer/caller/layout evidence to resolve those contracts. Debug address display correctly subtracts both module base and export-table size before its second hexadecimal draw. No runtime changes or new recoveries are counted. Full original packed-module/ROM, manifest and uncertainty-index gates precede landing.

Totals: 300 further recoveries after the 225 upstream ordinary imports, plus 1038 existing C semantic cleanups. Current ledger: 900 assembly references = 842 ordinary + 58 entrypoints; 769,920 known remaining instruction bytes; zero unknown sizes; 359 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `826-kernel-assembly-aliases` and `accepted-older-kernel-debug-readable-alias-corrected` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.

The uncertainty index also recognizes bare kernel address names and address-only entrypoints. Focused lexical/stable-ID fixtures pass; all 6,549 existing records remain exactly unchanged, and 43 address-name groups covering 73 physical locations are added. Other categories are unchanged. This search coverage does not prove that every semantic assumption has been discovered.

The first full-build attempt (wave 823) correctly rejected an unresolved old kernel name in an unconverted assembly caller: `_uvMemFree` still references `func_80002B80`. The retry preserves all fifteen original kernel address aliases separately from descriptive C definitions, retaining assembly compatibility. The failed attempt is not accepted validation.


## Historical accepted checkpoint — 300 further readable functions

Clean thirteen active existing-C profiler/scheduler routines after complete instruction and relocation-target comparisons and inverse-token audits. Preserve all original declarations, argument types, interrupt bookkeeping, empty diagnostic branch, trace streams and ring operations, variadic request termination, and pause-state truncation. Descriptive names retain original-address aliases for remaining assembly callers. RE_UNKNOWN notes identify numeric state/pairing, input range, event/stream protocol, reset synchronization and interval warm-up evidence still needed. The trace selector remains secondaryStream because both audio and graphics events use it. Separately correct two reversed model-loader extern pointer types: original initialization loads LGHT into EE0 and FMTX into EE4, and original release uses EE0 light-release slot 0x2C. Both affected bodies remain assembly; no initializer recovery is claimed. Clarify the existing AI shared-word setter comment using original consumer evidence: nonzero bypasses the two magnitude bounds and selects adjustment 9 rather than 4.5; ownership/lifetime/other consumers remain explicitly unknown. No runtime behavior changes or further recoveries are counted.

Totals: 300 further recoveries after the 225 upstream ordinary imports, plus 1051 existing C semantic cleanups. Current ledger: 900 assembly references = 842 ordinary + 58 entrypoints; 769,920 known remaining instruction bytes; zero unknown sizes; 346 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `828-older-profiler-scheduler-readable` and `accepted-older-profiler-scheduler-readable` verify real translation-unit instructions/full relocations, 5 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 300 further readable functions

Historical audit correction: the GUI linked-record and race retained-address ownership uncertainties remain valid. The particle interpretation recorded at this checkpoint was wrong: the reviewed wrapper calls getter slot 0x18, whereas the double-consuming handlers examined here belong to setter slot 0x14. The instruction-exact proof remains valid, but the numeric-input interpretation and raw-properties name are superseded by the later actual-getter contract correction. That correction establishes two four-float output regions, an acquisition followed by property reads, and explicit unresolved failure reachability, lifetime and component meaning. Do not use this superseded interpretation as evidence for a source ABI or runtime defect.

Totals: 300 further recoveries after the 225 upstream ordinary imports, plus 1052 existing C semantic cleanups. Current ledger: 900 assembly references = 842 ordinary + 58 entrypoints; 769,920 known remaining instruction bytes; zero unknown sizes; 346 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `836-older-hidden-contract-unknowns` and `accepted-older-hidden-contract-unknowns` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 301 further readable functions

Recover the 72-byte UFO initializer as readable active C, preserving allocation-pointer registration, all three original callback addresses and store order. Its table is explicitly N64 address storage; original source-level table type and unresolved slot 0x08 callable contract remain RE_UNKNOWN, without inventing a callable prototype. Correct the existing 148-byte intersection helper after original packed-module disassembly proves its incoming A0 is unchanged through indirect slot 0x04. Original initialization imports TEXT into D_uvisect_rom_00408204, and the actual texture header/initializer/implementation establish u8 uvTextureGetLoadedFlag27(s32 textureId). Replace the guessed no-argument game-state prefix/member with that actual interface and explicit texture ID; rename the helper to uvIsectMatchesTextureByteOrIdList and its local to textureByte. Preserve tests for 0x0A/0x11/0x1D, registered-list scan, first-match and empty-list behavior. The actual byte-code/list policy and ownership remain explicitly unknown with caller/setter/metadata resolution paths. Both finalized real translation-unit functions match all original bytes and relocation targets. This resolves one prior source interpretation while retaining full original runtime behavior.

Totals: 301 further recoveries after the 225 upstream ordinary imports, plus 1053 existing C semantic cleanups. Current ledger: 899 assembly references = 842 ordinary + 57 entrypoints; 769,848 known remaining instruction bytes; zero unknown sizes; 346 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `843-ufo-texture-contracts` and `accepted-ufo-texture-contracts` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 303 further readable functions

Recover two original active routines as readable C: the 280-byte car-animation cheat-selected object matrix-row scaling and the 272-byte configured local-Z motion-vector transform/accumulation. For cheat bytes 4/5/6, select X/Y/Z row and original float constant, publish axis+1 before callbacks, scale all four row components including W, and reload the object handle before updating slot zero. Other cheats clear the shared byte and leave the matrix untouched. Preserve existing matrix/object exports and the established facing-object inhibit relationship, while scale units/labels and wider byte ownership remain RE_UNKNOWN with caller/asset resolution paths. In motion, preserve kind loads before and after the transform callback, exact matrix/vector offsets, ordered negative/positive tests, f32-to-f64 multiplication by 0.5 followed by f32 conversion, and in-place vector addition. Kind/marker/constant units and accumulated-vector role remain explicitly unknown with producer/caller resolution paths. Finalized source uses one canonical function comment rather than duplicate draft prose. Every instruction and relocation target matches the original 552 bytes; no source-shape scaffolding, fake padding or runtime guards are introduced.

Totals: 303 further recoveries after the 225 upstream ordinary imports, plus 1053 existing C semantic cleanups. Current ledger: 897 assembly references = 840 ordinary + 57 entrypoints; 769,296 known remaining instruction bytes; zero unknown sizes; 346 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `848-car-axis-motion-vector` and `accepted-car-axis-motion-vector` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 303 further readable functions

Correct five existing C contracts using original module bindings and actual target implementations. The particle wrapper calls getter slot 0x18, not setter slot 0x14: properties 0x1005 and 0x4026 write four floats through pointer varargs. Rename it caranimAcquireParticleEffectAndReadProperties and type both output regions as f32 pointers, preserving exact original instructions. Acquisition-failure reachability, output lifetime and component meanings remain explicit unknowns; the unchecked acquired handle remains an original quirk without a new reachable-defect claim. Correct the sprite STAT slot 0x58 member to the actual void uvGfxResetShadeCombineMode callback in both complete callers. Name both AI-editor callbacks by their actual invocation rather than guessed selection/update semantics. TDATA slot 0x14 is tdataRefreshSharedData(void); slot 0x30 is an empty target whose intended source argument contract remains unknown. Preserve their original call forms and flag the declaration discrepancies with resolution paths. Every complete function and relocation target matches. This supersedes the erroneous earlier particle setter interpretation while preserving the validity of its machine-code verification.

Totals: 303 further recoveries after the 225 upstream ordinary imports, plus 1058 existing C semantic cleanups. Current ledger: 897 assembly references = 840 ordinary + 57 entrypoints; 769,296 known remaining instruction bytes; zero unknown sizes; 346 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `860-older-export-getter-contracts` and `accepted-older-export-getter-contracts` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 304 further readable functions

Recover the 124-byte intersection query initializer with the actual f32 fourth argument, ordered direction/point copies through FVEC slot 0x1C and a 16-bit state clear. Keep word roles, coordinates, state lifecycle and complete record ownership explicitly unknown. Correct two older player callbacks using original MOTN bindings: slot 0x30 returns after storing incoming A0 into its argument home, so its intended source prototype remains RE_UNKNOWN rather than inferred from an empty C body; slot 0x34 calls motionUpdateSharedState(void). Preserve car-audio invocation, exact conditional dispatch and unknown shared-value meanings. Correct the editor PAUS slot 0x08 description to actual node-callback/menu/controller dispatch. The nested callback inherits incoming argument registers, so preserve the existing no-argument caller view and explicitly track intended callback inputs/results and field meanings. No guessed gameplay-mode, player-count, drawing or ownership semantics are introduced. The finalized complete functions total 456 original instruction bytes and match every byte and relocation target; one new recovery and three existing-C semantic cleanups are accepted.

Totals: 304 further recoveries after the 225 upstream ordinary imports, plus 1061 existing C semantic cleanups. Current ledger: 896 assembly references = 839 ordinary + 57 entrypoints; 769,172 known remaining instruction bytes; zero unknown sizes; 344 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `865-query-motion-pause-contracts` and `accepted-query-motion-pause-contracts` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 304 further readable functions

Apply focused audit improvements to 21 distinct older functions. Replace unsupported ownership/lifetime claims for linked records, scalar regions, indexed sound handles, GUI value sources, UVCT aliases and queued pointers with explicit RE_UNKNOWN questions and concrete original producer/consumer/release evidence needed. Mark replay-unit, terrain-normal coordinate-space and shared FMTX-origin uncertainties. Correct stale texture membership wording and the box-side algorithm name: it selects the minimum signed XY face margin, without an absolute-distance or containment check; inside-point validity remains unknown. Use actual UvIntersect_Exports and its s32-index/Vec3F-output triangle-normal signature in both terrain callers; existing u16 fields promote to identical argument bits. Rename the packed triangle helper to Normal and the two audio wrappers to managed-handle position/pitch and release operations. Correct six callback-registration comments: the zero third argument is no insert-before callback, not context. Correct a graphics state mask previously mislabeled a framebuffer address and identify fill-color setting. The animation registration comment records the original ignored failure/unwritten-output contract and caller/pool audit needed, without claiming reachable player impact or adding guards. All comment edits pass exact whole-function and lexical code-token checks; logical source lines are preserved. All five complete type/name candidates match 1064 original instruction bytes and every relocation target. This adds no new recovery and changes no runtime behavior.

Totals: 304 further recoveries after the 225 upstream ordinary imports, plus 1082 existing C semantic cleanups. Current ledger: 896 assembly references = 839 ordinary + 57 entrypoints; 769,172 known remaining instruction bytes; zero unknown sizes; 344 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `874-older-focused-uncertainty-audit` and `accepted-older-focused-uncertainty-audit` verify real translation-unit instructions/full relocations, 13 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 307 further readable functions

Recover three original routines as readable active C: the 316-byte AI target-position snap,164-byte packed terrain-tile translation query and92-byte packed-triangle texture metadata comparison. Preserve AI settings snapshots/overrides, the discarded dot callback, target position reloads across vector callbacks, squared product threshold, all three component copies and conditional phase transition. Settings roles, threshold units and phase labels remain RE_UNKNOWN. Preserve terrain output clearing, loaded-resource lookup, original unchecked tile selection and distinct table reads across output writes; coordinate convention and index bounds remain unknown. Resolve intersection TERR slot0x1C and TEXT slot0x04 through actual initializers/producers, retain low12/low16 masks and missing-texture zero-match behavior while marking metadata policy unknown. All 572 original instruction bytes and every relocation target match in finalized real translation units. The AI match came from a bounded four-worker declaration/lifetime search with actual N64 headers and original IDO compiler: moving forceSnap after the float declarations resolves its two stack-offset differences. No operation, arithmetic tree, padding, volatility or ABI changes are involved. Strategy refinement: use bounded natural-declaration/lifetime searches for grounded near-matches, explicitly enable stack-difference scoring even for the baseline, review resulting source, and require complete real-TU/all-target plus packed-module/full-ROM proof before acceptance; a zero search score is never acceptance by itself.

Totals: 307 further recoveries after the 225 upstream ordinary imports, plus 1082 existing C semantic cleanups. Current ledger: 893 assembly references = 836 ordinary + 57 entrypoints; 768,600 known remaining instruction bytes; zero unknown sizes; 344 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `886-ai-terrain-texture-readable` and `accepted-ai-terrain-texture-readable` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 308 further readable functions

Recover the 228-byte planar-record angle-response helper as readable active C. Use the proven original misc degree-folding and normalized-pair-angle exports, retain y > 0 ? y : -y for zero and NaN, ordered magnitude thresholds, zero early return, shared angle scale, response reload and original attenuation formula. Constant units/ranges and the response consumer meaning remain RE_UNKNOWN with original writer/caller resolution paths. The earlier two-word mismatch was only a magnitude spill/reload offset; reordering the two existing genuine float declarations produces every original instruction and relocation target in the real translation unit. No padding, new temporary, volatility, arithmetic reassociation, runtime guard or ABI change is introduced. Final source contains one canonical uncertainty-bearing function comment.

Totals: 308 further recoveries after the 225 upstream ordinary imports, plus 1082 existing C semantic cleanups. Current ledger: 892 assembly references = 835 ordinary + 57 entrypoints; 768,372 known remaining instruction bytes; zero unknown sizes; 344 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `894-motion-planar-readable` and `accepted-motion-planar-readable` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 309 further readable functions

Recover the 204-byte terrain endpoint-to-Z-plane helper with its original normalization call, floating expression order and sequential writes. Reordering its two genuine local declarations resolves the eight stack-offset differences; coordinate-space and nonzero-direction guarantees remain explicit unknowns. Correct nine older GUI/menu/scene functions using original initializer bindings and actual target instructions: typed address and signed-index GUI views, the now-resolved MISC104 bound-scalar-row contract, GUI C4 fixed-width text-copy semantics, and GAMEGUI24 debug-byte input gating. Rename the misleading selection-reset helper to gameGuiLoadPaletteThreeAndSelectDebugFont. Keep original bound-storage extents/types, historical caller typedefs and debug-byte state meanings unresolved with concrete resolution paths. All three menu candidates produce one identical full source transaction. Add nine precise older-code comment corrections: nullable AI shared-target validity, exact object flag mask, 30-byte selected-label buffer requirements, proven immediate sound-position copy, speech priority versus playback-value roles and original pending-flag consumption on failure, full-state explosion caller semantics, and terrain sentinel/index checks without unsupported caller-validation claims. Source tokens are unchanged for those nine comment patches, with logical line directives preserved where comments grow. All ten complete functions and resolved relocation targets match; full packed-module and ROM proof gates this checkpoint. The declaration-only search helpers passed positive/negative AST guard tests on the worker; the bounded dynamics search did not produce a complete match and no dynamics candidate is accepted.

Totals: 309 further recoveries after the 225 upstream ordinary imports, plus 1100 existing C semantic cleanups. Current ledger: 891 assembly references = 834 ordinary + 57 entrypoints; 768,168 known remaining instruction bytes; zero unknown sizes; 344 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `924-terrain-gui-contracts` and `accepted-terrain-gui-contracts` verify real translation-unit instructions/full relocations, 11 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 310 further readable functions

Recover the 356-byte shared-widget initializer as active readable C. Preserve the original settings-word snapshot and enable gate, lazy ugui/dled/font loading order, widget initialization/bounds and five property calls, palette/font selection and final debug-byte/word stores. Actual GUI target instructions establish pointer arguments and signed low-halfword property selectors; retain unresolved settings/property meanings, shared allocation and resource ownership with concrete writer/loader resolution paths. Correct the older race GUI prefix and prose: original GAMEGUI14 initializes shared resources, while GAMEGUI28 exports the debug-byte address and the used widget begins 16 bytes later. Preserve its original pre-callback address calculation and all attachments. Both complete functions and resolved relocation targets match. Add a searchable original-behavior marker beside the still-active intersection03054 assembly: original branch paths can read an unassigned stack fraction for unordered values or unequal positive inputs whose product becomes zero. Actual caller ranges and floating-point exception/underflow-mode reachability remain unknown; this records original instructions without asserting a player-visible defect or changing behavior. That marker preserves every source code token and logical line context. Full affected packed modules, original ROM and source/index proof gate acceptance.

Totals: 310 further recoveries after the 225 upstream ordinary imports, plus 1101 existing C semantic cleanups. Current ledger: 890 assembly references = 833 ordinary + 57 entrypoints; 767,812 known remaining instruction bytes; zero unknown sizes; 344 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `938-shared-gui-initializer` and `accepted-shared-gui-initializer` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 311 further readable functions

Recover the 240-byte Dynamics matrix-property getter as named C, retaining selectors, null-state behavior, five source matrices and the actual FMTX copy contract. The compiler owns only the original twenty-entry,80-byte switch table. Native ASM preserves the surrounding588-byte prefix and212-byte suffix; the unchanged9384-byte function hosts suffix layout only. Independent isolated checks prove all72224 resolved module instruction bytes and common relocation targets, all880 readonly bytes and all twenty table targets. Two real extraction runs produce identical prefix/host outputs and preserve accepted C byte-for-byte. New explicit metadata, original ASM witness, extraction hooks and tests reject changed inputs, other table users, invalid source ownership and unproved host migration. Generated semantic-name ASM copies are allowed only as independently validated, unreferenced original getter definitions. The completion ledger now distinguishes889 unfinished instruction functions from one validated retained-data pragma; the uncertainty index continues to show both code and data references. No function is hidden by this classification. Full packed Dynamics and fresh original ROM equality remain mandatory before landing. Clean six older audio/GUI names and parameters without changing instructions: managed handles versus emitter IDs, proven pitch/volume, exact twelve-byte compact-text transformation, selected value-widget state clear and published debug-byte getter. Seven additional guarded comment corrections expose retained callback-state lifetime/color bounds, orientation rank loss for Z-parallel directions, language-table prefix indexing, actual packed replay input versus scaled-byte blocks, unproved vector normalization/selector extent, and unknown motion-helper retention/modes. Preserve original behavior and distinguish potential reachability from confirmed gameplay defects. The GUI byte transform intentionally subtracts32 for every input>=97, including above z; caller domains remain unresolved. Remaining artificial AI/audio draft rewrites failed exact comparison and are excluded. All accepted source changes receive refreshed searchable uncertainty entries.

Totals: 311 further recoveries after the 225 upstream ordinary imports, plus 1114 existing C semantic cleanups. Current ledger: 889 assembly references = 832 ordinary + 57 entrypoints; 767,572 known remaining instruction bytes; zero unknown sizes; 341 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `986-native-dyn-older-contracts-fixed` and `accepted-native-dyn-older-contracts-fixed` verify real translation-unit instructions/full relocations, 8 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.

The first full-build attempt (`972-native-dyn-older-contracts`) failed because global assembly discovery also selected the readonly prefix already included by C. The retry excludes only the metadata-declared US prefix from standalone assembly inputs. Three GNU make fixtures verify that ordinary assembly, other prefixes and Japanese-version inputs remain selected. The failed wave remains recorded and is not evidence of a successful ROM build.


## Historical accepted checkpoint — 312 further readable functions

Recover the 392-byte terrain grid lookup as named C, preserving separately truncated coordinate differences and cell sizes before integer division, signed bounds, initial and failure output writes, and the original linear-index snapshot before alias-visible output stores. Reload the tile-array base for the second coordinate exactly as the original does. Grid units, valid nonzero truncated divisors and finite-coordinate caller guarantees remain explicitly unresolved with producer/caller investigation paths. Replace the older 108-byte AI helper reconstruction with focused state/export types, removing its artificial goto, comma expression and redundant alias. Original dependency initialization binds car animation; actual callback bodies and the original 31-entry selector table prove tags17/14/0, vector copies to animation3B8..3C0, double-promoted scalar to3A8 and termination. Preserve both callback dependency loads and nested animation-state pointer reload. Physical meanings, units, full allocation and lifecycle remain marked unknown. Clarify the older animation registry lookup: valid count and nonnull searched-prefix entries require writer/remover/caller proof; the constructor alone does not enforce these invariants. No reachable defect or behavior correction is claimed. Both complete recovered/cleaned function instruction streams and every relocation target match isolated original comparisons. Exclude unsuccessful animation and screen/record conversion drafts. Full affected packed modules, fresh original ROM, all source hashes and refreshed uncertainty index gate acceptance. The ledger reports unfinished instruction functions separately from one validated retained-data pragma.

Totals: 312 further recoveries after the 225 upstream ordinary imports, plus 1116 existing C semantic cleanups. Current ledger: 888 assembly references = 831 ordinary + 57 entrypoints; 767,180 known remaining instruction bytes; zero unknown sizes; 340 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `999-ai-terrain-typed-contracts` and `accepted-ai-terrain-typed-contracts` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 313 further readable functions

Recover the 96-byte filmroll module initializer as readable named C. Pass the original incoming table pointer to the existing file-allocation API, then register the five exact original callback addresses in order. The address-only storage view has five original 32-bit words; it does not invent a callable interface for unresolved callbacks. Original callback bodies establish observed argument consumption, and the separately recovered empty callback retains its identity. Preserve the reserved __entrypoint_func prefix before the descriptive initializer name, as required by module packing. Explicit unknown notes preserve callback-facing roles, intended historical declarations and loader/table lifetime with a loader/export-consumer resolution path. All original initializer instructions and relocation targets match the isolated real translation-unit comparison. Exclude still-unmatched profiler, file-reader, motion and intersection drafts. Complete original packed filmroll module, fresh original full ROM, source hashes and current uncertainty index gate acceptance. Unfinished instructions remain separate from one validated retained readonly-data pragma.

Totals: 313 further recoveries after the 225 upstream ordinary imports, plus 1116 existing C semantic cleanups. Current ledger: 887 assembly references = 831 ordinary + 56 entrypoints; 767,084 known remaining instruction bytes; zero unknown sizes; 340 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1013-filmroll-module-exports` and `accepted-filmroll-module-exports` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 314 further readable functions

Recover the 304-byte editor version-three reader as readable named C. Preserve file-backend loading, scene-dependent filename formatting, open mode and flags, negative-open exit, one-byte version read and mismatch close/return. Version three invokes the four original file helpers in order, closes the file and invokes both original refresh helpers. Retain the unused incoming word, actual backend reloads and raw refresh argument ABI. A bounded declaration-order correction of the existing filename/version/handle locals restores the original observed stack storage; no dummy operations, extra locals or padding were introduced. Explicit original-behavior marker records ignored read/close statuses and a version byte without fallback initialization. Failed-read reachability, complete file/helper contracts, readable filename sources and exact historical workspace extent remain unproved with original helper/data/caller investigation paths. Do not assert a reachable player defect or silently change parsing. Original instructions and all offset-aware relocation targets match; incidental relocation record emission order differs. Full packed original TED module, fresh full original ROM, source hashes and current uncertainty index gate acceptance. Other unmatched utility and animation drafts remain excluded. Instruction accounting continues to report validated retained readonly data separately.

Totals: 314 further recoveries after the 225 upstream ordinary imports, plus 1116 existing C semantic cleanups. Current ledger: 886 assembly references = 830 ordinary + 56 entrypoints; 766,780 known remaining instruction bytes; zero unknown sizes; 340 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1016-editor-version-three-reader` and `accepted-editor-version-three-reader` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 315 further readable functions

Recover the 400-byte animation particle acquisition routine as named readable C. Preserve negative-kind and failed-acquisition exits, original shared definition-word address and requested count ten, tagged integer properties and double-promoted scalar, four palette choices and final restart. Actual original PFX initializer and accepted target bodies establish acquisition/setup/property/restart signatures; original color-helper instructions prove two float palette inputs and four caller bytes. A normal switch with original physical case order11/13/10/14 recovers the observed compare dispatch; the initial if/else draft differed and was excluded. Preserve original nonnegative kinds beyond those palette choices and the count setter clamp. Explicit unknown notes keep gameplay kind meanings, scalar units and shared definition ownership unresolved with caller/asset evidence paths. No neighboring callback/getter comments are changed; this checked setter path is distinct from the older unchecked property-read wrapper. Every original function instruction and offset-aware relocation target matches; relocation record emission order is incidental. Complete original packed animation module, fresh original full ROM, all source hashes and current uncertainty index gate acceptance. The separate Dynamics two-table trial and unmatched drafts remain unaccepted.

Totals: 315 further recoveries after the 225 upstream ordinary imports, plus 1116 existing C semantic cleanups. Current ledger: 885 assembly references = 829 ordinary + 56 entrypoints; 766,380 known remaining instruction bytes; zero unknown sizes; 340 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1020-animation-particle-setup` and `accepted-animation-particle-setup` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 316 further readable functions

Recover the 312-byte track-data query matrix routine as named readable C. Initialize the matrix, obtain a four-byte group/index handle plus translation and vector outputs from the original helper, select the record, cross its vector at offset 0x18 with the helper vector, and copy the three basis rows and translation. Preserve captured pointer lifetime, raw three-word aggregate copies with sixteen-byte matrix row stride, three original translation copies and the unchecked lookup result. Correct the outer declaration to its observed returned record pointer. Original helper instructions establish four machine arguments and returned output address, but cannot distinguish historical explicit output-pointer spelling from a hidden aggregate-return convention; mark that uncertainty explicitly. Query meanings, physical units, basis validity and allocation/alias guarantees remain unresolved with helper/caller evidence paths. Actual existing matrix/vector exports supply consumed callback signatures. No adjacent comments are stale. All original function instructions and offset-aware relocation targets match; full original packed track-data module, fresh complete original ROM, every source hash and current uncertainty index gate acceptance. The separate Dynamics native two-table feasibility proof passes independently but is not accepted by this checkpoint; persistent extraction and full build remain pending.

Totals: 316 further recoveries after the 225 upstream ordinary imports, plus 1116 existing C semantic cleanups. Current ledger: 884 assembly references = 828 ordinary + 56 entrypoints; 766,068 known remaining instruction bytes; zero unknown sizes; 340 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1025-tdata-query-matrix` and `accepted-tdata-query-matrix` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 317 further readable functions

Recover the 396-byte track-data module initializer as readable C with all thirty original ordered callback address stores and the original allocation-pointer update. Use address storage without inventing callable signatures for unfinished exports; preserve empty/constant callbacks and the reserved entrypoint prefix. Correct an older animation wrapper comment that described both helpers as initialization phases despite the second helper also being called through AI updates; no code tokens or line counts change. Improve the uncertainty index with additive lexical function/type/global declaration context, keeping all previous Q identities, note text, locations and counts. Named-routine queries now find leading and inline uncertainty and original-quirk notes. Seventeen regressions cover physical line directives, fake declarations in strings/macros, nested notes, types/prototypes, unsupported declarators, trailing/detached notes, stable identities and deterministic outputs. Conservative lexical ownership remains a search aid and does not prove semantic ownership or discover hidden assumptions. Verify named track-data lookup, complete packed track-data and animation modules, fresh full ROM, every source hash and regenerated index before landing. Dynamics persistent extraction and unmatched drafts remain outside this checkpoint.

Totals: 317 further recoveries after the 225 upstream ordinary imports, plus 1117 existing C semantic cleanups. Current ledger: 883 assembly references = 828 ordinary + 55 entrypoints; 765,672 known remaining instruction bytes; zero unknown sizes; 340 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1033-uncertainty-owner-tdata-exports` and `accepted-uncertainty-owner-tdata-exports` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 318 further readable functions

Recover the 344-byte Dynamics scalar-property getter as named readable C. Preserve null/unsupported fallback, thirteen original selectors and observed scalar widths/conversions. Original switch block order restores exact instructions and compiler table targets; initial numeric-order draft failed and remains excluded. Property meanings/units, node ownership and distinction of fallback from stored negative values remain explicitly unknown with setter/caller/registry investigation paths. Extend retained-readonly metadata to an ordered list of compiler tables and following original ASM spans. Exact original witness hashes, table entry targets, alternating nonempty byte coverage, source owner/host order, unconditional unique C owners, host instruction boundaries and real-reference rejection protect regeneration. Preserve legacy single-table behavior, the same prefix path, Makefile exclusion and immutable original witness. Validate only exact old or new rendered prefix during migration; changed/executable prefix is rejected. Independent proof already established all 72224 resolved instruction bytes, common relocation targets, original compiler-resolved branch, all 880 readonly bytes and both table targets, with old matrix getter and both ASM hosts unchanged. Real extractor ran twice in an isolated project with identical C and outputs. Thirty-six unique tests exercise old/new layout and negative guards. Local generated input contains only a validated readonly prefix; code is not built locally. Complete original packed Dynamics module, fresh full ROM, all source hashes, meaningful layout tests and current uncertainty index gate acceptance. Report retained readonly data separately from unfinished instructions.

Totals: 318 further recoveries after the 225 upstream ordinary imports, plus 1117 existing C semantic cleanups. Current ledger: 882 assembly references = 827 ordinary + 55 entrypoints; 765,328 known remaining instruction bytes; zero unknown sizes; 340 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1036-native-dyn-scalar-property` and `accepted-native-dyn-scalar-property` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 324 further readable functions

Recover six original module initializers as named readable C: flag120bytes, display-list editor144bytes, trigger animation144bytes, lighting144bytes, screen148bytes and AI record136bytes. Preserve original allocation-pointer argument, all address store ordering, separate empty exports, shared-word/data addresses, original list resets and screen selection/color stores without resetting its exported submission-disable word. AI record initialization preserves the500-record limit, twelve-byte allocation multiplier, unchecked allocation result word and three helper calls in order. The helper original instructions prove a writable table address argument; its full table/consumer contract remains unfinished. Address storage deliberately avoids invented callable interfaces. Existing C prototypes are copied exactly; assembly-only labels are declared as opaque linker code addresses with explicit notes to replace declarations after implementation/caller proof. Unknown slot signatures, global-word meanings, export capacity/lifetime, pool ownership/reload and allocation-failure reachability remain inline with concrete resolution paths. Reserved entrypoint prefixes remain intact for packing. Every selected original instruction and offset-aware relocation target matches; incidental relocation-record ordering differs for the record initializer. Unmatched geometry and editor drafts are excluded. Full original packed modules for all six sources, fresh complete original ROM, all source hashes and regenerated named-routine uncertainty index gate acceptance.

Totals: 324 further recoveries after the 225 upstream ordinary imports, plus 1117 existing C semantic cleanups. Current ledger: 876 assembly references = 827 ordinary + 49 entrypoints; 764,492 known remaining instruction bytes; zero unknown sizes; 340 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1045-six-module-initializers` and `accepted-six-module-initializers` verify real translation-unit instructions/full relocations, 6 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 328 further readable functions

Recover scene180bytes, rain184bytes and environment172bytes initializers and GUI452byte text-list hit state. Scene preserves the early blend-slot store and shared data export. Rain registers the original addresses then calls validated sound slot0xCC to initialize its existing handle; full handle/storage/reload ownership remains unknown. Environment resets its original count and three list heads. Initializer storage remains raw address slots where full callback contracts are not yet proven; separate empty callbacks retain their identities. GUI uses the existing widget layout and resolves the observed signed-halfword matched-child field at0x16A. Preserve last-child matching, mutable signed count reloads and the equality gate before committing an index: negative or shrinking counts can leave the previous matched index, while state outside two clears it to minus one. Retain inclusive bounds, original byte/halfword conversions and actual seven-argument helper passing. Input roles, scalar units, valid count/child-pointer domain and broader widget lifetime remain explicit RE_UNKNOWN notes with original helper/caller evidence paths. The original unchecked mutable count is separately marked RE_ORIGINAL_QUIRK without inventing a reachable crash. No failed piece/spray/glare recovery enters this checkpoint. All selected instruction words and offset-aware relocation targets match. Full affected packed modules, fresh original complete ROM, complete source hashes and regenerated named-routine uncertainty index gate landing.

Totals: 328 further recoveries after the 225 upstream ordinary imports, plus 1117 existing C semantic cleanups. Current ledger: 872 assembly references = 826 ordinary + 46 entrypoints; 763,504 known remaining instruction bytes; zero unknown sizes; 340 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1054-module-exports-gui-hit-state` and `accepted-module-exports-gui-hit-state` verify real translation-unit instructions/full relocations, 4 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 330 further readable functions

Recover352byte filtered shared geometry scan and240byte menu-selector initializer. Geometry preserves0x78/4/4 record/word/filter strides,16-bit index wrap, shared bound reload after helper invocation, typed six-argument helper passing and original optional-output order3/5/4/6/7 even if output pointers alias. No results leave all outputs untouched. The source uses the naturally mutable shared bound; skipping a record has no writes/calls that could change that bound. All original instruction words and offset-aware relocation targets match after swapping only two existing scalar declarations. Menu selector preserves all17 callback address stores in their original interleaving and separate empty callback. In older C, two geometry setter parameter names now identify observed record/index/address roles; original four-s32 and s32/u16/u16/s32/s32 interfaces, executable tokens after inverse identifier mapping, widths, mode toggles, assignment order and physical line counts remain exact. Both setters retain concrete bounds/lifetime/ownership uncertainty notes. Correct the older glare claim of allocation: original graphics slot0x10 retrieves an existing callback-list host. Its entire executable source and physical lines remain unchanged. Full geometry result-buffer capacity/lifetime, vector coordinate space, raw-word meanings and remaining menu callback contracts stay explicit RE_UNKNOWN notes; the wrapping mutable scan remains a separately marked original quirk. Failed object-bank/camera/pause/replay/GUI/selection/skid drafts are excluded. All affected packed modules, fresh complete original ROM, full source manifest and regenerated uncertainty index gate acceptance.

Totals: 330 further recoveries after the 225 upstream ordinary imports, plus 1120 existing C semantic cleanups. Current ledger: 870 assembly references = 825 ordinary + 45 entrypoints; 762,912 known remaining instruction bytes; zero unknown sizes; 340 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1063-geometry-menu-older-contracts` and `accepted-geometry-menu-older-contracts` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 332 further readable functions

Recover296byte camera initializer and2032byte texture-viewer control construction. Camera preserves all14 original export addresses (12 callbacks and two shared-data addresses), shared scalar/count initialization, font and camera-module loads and actual one-argument profiler creation. Slot0x28 remains neutrally named because its historical matrix callback ABI is unresolved; missing forward declaration is copied exactly from the existing later definition without inventing a signature. The texture panel constructs seven controls whose purposes are proven by original labels: texture ID, U, V, red, green, blue and alpha. Preserve all original allocator/getter calls and signed-halfword conversions, global export-table reloads, fixed12/30byte text copies, flags2/0x11, f32 bounds/defaults and persistent scalar bindings. Raw callback address storage stays distinct from an unresolved callable interface. Unknown widget/label extents, pool lifecycle, callback signatures, empty texture inventory and exhaustion reachability remain inline RE_UNKNOWN notes with original provider/data/caller evidence paths. Original behavior is retained; no new guards or invented capacities enter the matching source. All original2032texture instructions match after reordering only existing local declarations, with no added operations or storage. Camera and texture instruction targets match exactly, regardless of incidental relocation-record order. Failed pause/replay/GUI/object-bank/sound drafts remain excluded. All affected packed modules, fresh complete original ROM, complete source hashes and regenerated uncertainty index gate landing.

Totals: 332 further recoveries after the 225 upstream ordinary imports, plus 1120 existing C semantic cleanups. Current ledger: 868 assembly references = 824 ordinary + 44 entrypoints; 760,584 known remaining instruction bytes; zero unknown sizes; 340 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1075-camera-texture-control-panel-final` and `accepted-camera-texture-control-panel-final` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 333 further readable functions

Recover the 476-byte game initializer with four original callback addresses and one shared-state address. Preserve their registration order, the initial -1 state word, all thirteen original profiler calls and ID destinations, pause and settings-scalar clears, the original short-circuit display-mask decision, unchecked frame-option table indexing, no-input startup helper call and terrain shared-word reset. The actual profiler definition establishes its single label argument; the seed extra argument is discarded as a decompiler error. The full original startup-helper body establishes no incoming argument consumption, while its complete purpose and any return contract remain unknown. Original terrain registry instructions and relocation labels identify slot 0x5C as the accepted uvTerraSetSharedWordBF0(s32) provider; no unproven terrain operation is named. Opaque address-only callback labels are stored without inventing callable signatures. Inline RE_UNKNOWN notes identify unresolved callback contracts, shared state/settings meanings, helper purpose, table bounds and lifecycle, and say which callers or consumers would resolve them. No checks or runtime fixes are added. Exact original instruction bytes and relocation targets gate inclusion; incidental relocation record order is not a semantic difference. All affected packed modules, a fresh full original ROM, complete source hashes and regenerated uncertainty index gate landing. Failed terrain/provider/consumer drafts remain excluded.

Totals: 333 further recoveries after the 225 upstream ordinary imports, plus 1120 existing C semantic cleanups. Current ledger: 867 assembly references = 824 ordinary + 43 entrypoints; 760,108 known remaining instruction bytes; zero unknown sizes; 340 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1082-game-startup-contracts` and `accepted-game-startup-contracts` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 334 further readable functions

Recover the 456-byte shared-record facing adjustment as uvIsectFlipRecordVectorTowardPoint. Preserve selector1/2/4/8 handling, packed terrain-texture rejection bits, short-circuit linked-record flag reads, original f32 displacement threshold, actual vector-length and dot providers, and ordered vector/scalar negation. Shared rejection control flow and meaningful length/dot result locals reproduce all original instruction bytes and relocation targets without artificial storage. Prefix types describe only observed fields; flag meanings, full record lifetime, coordinate units and scalar meaning remain explicit unknowns with constructor/caller resolution paths. Audit nine existing C functions: four MED wrappers, three geometry properties/scans, one results callback wrapper and one game unload helper. Remove unproved ownership, buffer registration/extent, vector/color and transition-state claims. Replace the three misleading MED names with conservative shared-address/property and scalar-triple names; rename the results wrapper resultsCallMenuCallbackWith100 from the proven original MENU binding while retaining unknown action and units. Existing scan return contracts and scalar meanings gain explicit searchable markers. All existing executable tokens remain identical after inverse identifier mapping, with original physical source line counts preserved for the older cleanup. No runtime behavior or checks change. Failed triangle, terrain, MED and splash drafts remain excluded and their diagnostics retain unresolved storage/contract limits. All affected packed modules, fresh original full ROM, complete source hashes and regenerated uncertainty index gate landing.

Totals: 334 further recoveries after the 225 upstream ordinary imports, plus 1129 existing C semantic cleanups. Current ledger: 866 assembly references = 823 ordinary + 43 entrypoints; 759,652 known remaining instruction bytes; zero unknown sizes; 339 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1090-facing-older-unknowns-fixed` and `accepted-facing-older-unknowns-fixed` verify real translation-unit instructions/full relocations, 4 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 335 further readable functions

Recover the 500-byte packed-triangle mean-vertex-byte routine with existing terrain/geometry/triangle/vertex types. Preserve sentinel/null returns, all index reads and three separate unsigned-byte integer averages and stores, including alias-sensitive component sequencing. Canonical bounded integer addends reproduce every original instruction word and relocation target; sums are at most765 and cannot overflow signed32-bit arithmetic. Vertex-byte encoding, valid asset indices and caller alias policy remain explicitly unknown; no RGB/normal role or new guard is invented. Audit seven existing C functions: six environmental sound/letter/cache wrappers and the AI editor refresh-callback registration. Original graphics initializer and full756-byte target independently establish slot0x3C as primitive RGB/alpha setting, including FA00 color packing and F700 fill color, so the existing letter color name stays and contradictory viewport/scissor prose is removed. Letter descriptor bounds, sound-region count/player dispatch order, unchecked cache accesses, producer count/capacity and invalid-index writes remain concrete searchable uncertainties with original producer/caller resolution paths. Rename AI editor registration after its actual registered track-data refresh callback, preserving channel property6, priority0xC8, all arguments and the adjacent unknown historical callback-word meanings. Existing executable tokens after inverse identifier mapping and physical source line counts remain identical. Extraction maps use current canonical function names; historical addresses remain in guarded review artifacts. Failed terrain triangle/static-object drafts stay excluded. All affected original packed modules, fresh original full ROM, complete source hashes and regenerated uncertainty index gate landing.

Totals: 335 further recoveries after the 225 upstream ordinary imports, plus 1136 existing C semantic cleanups. Current ledger: 865 assembly references = 822 ordinary + 43 entrypoints; 759,152 known remaining instruction bytes; zero unknown sizes; 339 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1095-terrain-older-utilities` and `accepted-terrain-older-utilities` verify real translation-unit instructions/full relocations, 5 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 336 further readable functions

Recover the 556-byte filmroll buffer-range swap with actual original sound and graphics export bindings and target argument consumption. Preserve initial unsigned cursor snapshot, direction choice, live target reloads, signed4480-byte movement, sound handle initialization/start/update/release, exact graphics begin/end/wait ordering, video buffer swaps and alternating black state, final visible state and phase-dependent framebuffer copy. The sound-volume getter call remains an independent statement; scaling its actual result in the start-call expression reproduces the two remaining original FP register words without adding storage or operations. All original instruction bytes and relocation targets match; incidental relocation record order does not change targets. Shared address-window extent/alignment, target mutation, wrap/termination guarantees, sound-handle lifetime and intended visual role remain explicit unknowns with producer/caller/consumer resolution paths. Sound storage and export prefixes expose only observed accesses, with historical complete source declarations unresolved. Correct two existing geometry names: their property argument equals one, while neither routine reads a record-kind discriminator. New names state the actual signed-word/float conversion; executable tokens after inverse identifier mapping, ABI, comments and physical source line counts remain unchanged. No bounds, clamp or runtime correction is added. Failed screen and initializer drafts remain outside accepted code. All affected original packed modules, fresh original complete ROM, full source hashes and regenerated uncertainty index gate landing.

Totals: 336 further recoveries after the 225 upstream ordinary imports, plus 1138 existing C semantic cleanups. Current ledger: 864 assembly references = 821 ordinary + 43 entrypoints; 758,596 known remaining instruction bytes; zero unknown sizes; 339 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1105-filmroll-property-names` and `accepted-filmroll-property-names` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 337 further readable functions

Recover the 492-byte filmroll buffer-range transition using original sound, graphics and scheduler provider contracts. Preserve unsigned cursor comparisons, live target reloads, signed 3,840-byte steps, every sound and graphics call, video-interface buffer swaps and waits, the original otherwise unused local phase toggle, final fresh target swap, framebuffer direction-one copy and suppression clear. All instruction bytes and relocation targets match. Valid buffer window, alignment, mutation, wrap and termination guarantees, visual purpose and complete historical storage declarations remain searchable unknowns with caller/producer resolution paths. Correct two older player comments without changing executable tokens or physical source lines: global sound-handle addresses do not establish allocation ownership or safe lifetime; arrow drawing applies local-Y displacement directly to the caller matrix and a graphics stack pop does not restore its translation row. Matrix coordinate units and caller reuse remain explicit unknowns. No runtime behavior is changed and failed terrain/initializer drafts remain excluded. Affected original packed modules, a fresh original complete ROM, complete source hashes and a regenerated uncertainty index gate landing.

Totals: 337 further recoveries after the 225 upstream ordinary imports, plus 1140 existing C semantic cleanups. Current ledger: 863 assembly references = 820 ordinary + 43 entrypoints; 758,104 known remaining instruction bytes; zero unknown sizes; 339 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1110-filmroll-player-contracts` and `accepted-filmroll-player-contracts` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 338 further readable functions

Recover the 424-byte terrain index-pair lookup. Preserve signed-16 differences and narrowing, mode-specific rejected adjacent pairs, one 64-entry wrap correction, and transposed lookup order. The actual original table is writable DATA with 4,096 unsigned halfwords between proven adjacent symbols; change only its access declaration to 64 by 64 without migrating or recreating data. Original incoming mode homing and low-byte consumption ground an observed u8 input view; a redundant explicit mask is removed and every original instruction and relocation target matches. The view does not assert the complete historical source prototype. Table value meanings, caller index domains and mode convention remain explicit unknowns with caller/table resolution paths. Audit older readable code with six comment corrections across five existing functions and one controller type; executable tokens and physical source lines remain identical. Recording conversion uses three local pair tables but passes two different globals to the proven original empty track-data callback; discarded conversion and empty-path purposes remain unknown. Animation transform promotion uses per-object part getter/setter model-scale conversions, not a matrix stack; valid second-part storage is an unresolved caller/model precondition, not a claimed reachable fault. Controller buttons represent the current held sample and edge helpers compare the previous sample. The raw-state setter updates normalized axes without changing the raw stick cache read by the raw getter. Two packed-color scaler comments no longer promise unconditional alpha preservation: original IA4 low intensity is shifted without a three-bit mask and can spill into the neighboring alpha. A positive finite byte 0x0E with scale two becomes 0x1C under the exact original operations, changing bit 0x10. Caller scale ranges and asset reachability remain unknown; original packing is retained without new clamps or a claim that original gameplay reaches the case. Specific RE_UNKNOWN and RE_ORIGINAL_QUIRK notes provide producer/caller resolution paths. All affected original packed modules, fresh original complete ROM, complete source hashes and regenerated uncertainty index gate acceptance. A separate retained-assembly segment helper now has a same-line searchable annotation: an overlapping vertical-input path reads an intercept stack word not written on that path. Original caller reachability and intended collinear behavior remain unresolved; no C initialization or runtime fix is invented. Failed terrain and filmroll drafts remain excluded.

Totals: 338 further recoveries after the 225 upstream ordinary imports, plus 1145 existing C semantic cleanups. Current ledger: 862 assembly references = 819 ordinary + 43 entrypoints; 757,680 known remaining instruction bytes; zero unknown sizes; 339 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1129-terrain-older-contracts` and `accepted-terrain-older-contracts` verify real translation-unit instructions/full relocations, 6 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 338 further readable functions

Fix a concrete uncertainty-search gap: the preserved vertical-segment stack-read note was indexed but searching its assembly-backed function name did not retrieve the note. Add conservative assembly declaration context for immediately leading comments beside real standalone GLOBAL_ASM pragmas. The context comes from the original assembly filename and does not assert runtime ownership or that a retained-data pragma is a function. Literal-masked source and continuation checks reject quoted, commented and continued-macro examples. Keep detached notes unowned, prevent trailing comments from borrowing later declarations, preserve physical source lines despite #line, and retain every existing search-group identity, category, evidence and source hash. Twenty-two regression tests cover existing C/type/global behavior plus original assembly names, retained data, false directive examples, detached/trailing notes and stable IDs. Both the explicit unknown and original quirk for func_misc_004019FC are now queryable by that symbol. No gameplay C, ASM, data or ABI changes. Validate the unchanged representative original MISC module, freshly relinked original complete ROM, complete source manifest and regenerated index before local landing. Full readable decompilation remains incomplete.

Totals: 338 further recoveries after the 225 upstream ordinary imports, plus 1145 existing C semantic cleanups. Current ledger: 862 assembly references = 819 ordinary + 43 entrypoints; 757,680 known remaining instruction bytes; zero unknown sizes; 339 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1140-assembly-note-index` and `accepted-assembly-note-index` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 339 further readable functions

Recover the 216-byte terrain sort-group initializer with the actual SORT export interface. Preserve group creation tags 80, 85, 110 and 115, exact output-global store order, and option tag one/value one on the first and third handles. All original instruction bytes and relocation targets match. Original TERR initialization directly calls this routine at 0x004002C0 just after importing SORT; that caller is proven. Both original option calls omit the zero terminator consumed by the actual variadic provider. On the valid-handle normal-return path, the first setter leaves a3 holding its group-table-global address; no intervening call or instruction changes a3 before the second setter, which consumes that nonzero unsupplied tag and subsequent words. Allocation/error paths, the first residual a3 value, following stack contents, live initialization conditions and observable impact remain explicitly unknown. Preserve the exact original calls and record RE_ORIGINAL_QUIRK plus concrete caller/runtime resolution paths before any separate recomp correction; do not invent a terminator or fixed-argument callback. The readable initializer name avoids guessing option semantics. Failed centered-span and bounds drafts remain unaccepted. Full original packed terrain module, fresh original complete ROM, complete source hashes and refreshed uncertainty index gate landing.

Totals: 339 further recoveries after the 225 upstream ordinary imports, plus 1145 existing C semantic cleanups. Current ledger: 861 assembly references = 818 ordinary + 43 entrypoints; 757,464 known remaining instruction bytes; zero unknown sizes; 339 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1146-terrain-sort-groups` and `accepted-terrain-sort-groups` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 339 further readable functions

Improve eleven existing matching C functions without recovering additional assembly. Seven GAMEGUI callbacks request the exact observed numeric game-state codes; no screen meaning is invented. Name the shared GAMEGUI word setter, indexed PLYR word getter and low-byte REPLAY setter after their actual accesses, preserve raw ABI widths, and flag unresolved meanings/index domains beside them. Name the SORT group allocator and its actual allocation/order/channel scratch locals. Its original scan stops at the first free group before checking later duplicates; retain and flag this partial uniqueness check while leaving caller guarantees, capacities and bit domains explicitly unresolved. Per-definition inverse identifier guards retain all executable tokens. All eleven complete candidate instruction bodies and relocation targets match. Canonical extraction names replace original address labels without duplicate aliases. Full original packed modules, fresh original complete ROM, source manifest and regenerated uncertainty index gate acceptance. The failed MISC quaternion draft remains outside the accepted sources.

Totals: 339 further recoveries after the 225 upstream ordinary imports, plus 1156 existing C semantic cleanups. Current ledger: 861 assembly references = 818 ordinary + 43 entrypoints; 757,464 known remaining instruction bytes; zero unknown sizes; 328 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1154-readable-names-sort` and `accepted-readable-names-sort` verify real translation-unit instructions/full relocations, 5 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 339 further readable functions

Audit six existing functions. Name three menu helpers after the proven Controller Pak deletion request on controller zero, retention of its signed-halfword selection, and indexed UVBT/sprite resource cleanup. Correct the old comment that described the file-deletion request merely as controller-selection teardown; the original wrapper ignores the provider result and clears three tracking words. Original provider bindings establish deletion, requested graphics waiting, shared texture-animation release and sprite state clearing. File-number mapping, nested-record validity, error/retry policy, indexed resource domains and sprite lifetimes remain explicit unknowns rather than new reachable-bug claims. Two quaternion comments now distinguish requirements from proven guarantees: whether callers supply a nonzero divisor and the physical frames/purpose of a cached fixed rotation require original caller/consumer evidence. A stale TED comment now identifies original PAUS export 0x08 and refers to the detailed unresolved callback notes. All executable expressions and raw ABIs remain unchanged. Five complete candidate bodies and relocation targets match exactly, and separate prose edits have identical code tokens and physical lines. Full affected original packed modules, fresh original complete ROM, complete source hashes and regenerated uncertainty index gate acceptance. New TED and terrain collector drafts remain unaccepted pending exact instruction matches.

Totals: 339 further recoveries after the 225 upstream ordinary imports, plus 1162 existing C semantic cleanups. Current ledger: 861 assembly references = 818 ordinary + 43 entrypoints; 757,464 known remaining instruction bytes; zero unknown sizes; 325 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1161-older-selection-quat` and `accepted-older-selection-quat` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 339 further readable functions

Improve fourteen existing C functions and preserve knowledge from seven unaccepted recoveries. Twelve sound/file functions receive 32 descriptive parameter/local identifiers, including real managed-slot, sound-name, routing-index and buffered-byte roles. The corrected FILEUX candidates preserve all original struct member names; independent ordered member-access guards reject the two superseded failed drafts. The shadow wrapper now labels its third argument as an optional input record rather than output storage, supported by original helper reads. Environment-sound notes distinguish required first/final player grouping and currently declared table extents from proven original caller guarantees. Sound initialization comments describe actual prefix/ID routing, remove unsupported development-intent/sample claims and retain the original repeated BATTLEEXPLODE1 checks as a quirk requiring evidence before correction. All thirteen modified complete C candidate bodies and relocation targets match exactly. Seven original assembly pragmas remain intact with searchable contract notes: MISC blend/adjusted quaternion domains and flag lifecycle, TED record/model/property conventions, MED backing-object extent, terrain height-provider write-before-filter behavior, static-matrix scale/marker requirements and containing-object radius/layout/query guarantees. Each note identifies original callers, producers or consumers needed to resolve uncertainty; none claims player reachability from unproven inputs or accepts a failed C draft. Comment edits retain executable tokens and physical lines where applicable; banked annotations preserve original logical source lines. Full affected original packed modules, fresh original complete ROM, complete source hashes and regenerated uncertainty index gate acceptance.

Totals: 339 further recoveries after the 225 upstream ordinary imports, plus 1176 existing C semantic cleanups. Current ledger: 861 assembly references = 818 ordinary + 43 entrypoints; 757,464 known remaining instruction bytes; zero unknown sizes; 325 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1176-older-sound-shadow-notes` and `accepted-older-sound-shadow-notes` verify real translation-unit instructions/full relocations, 8 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 339 further readable functions

Improve fourteen active existing C routines: nine UV color/texture-animation functions with17 descriptive live identifiers, and five particle functions with10. Names distinguish loaded file IDs, vertices, byte/halfword storage elements, masked RGB components, animation/effect records, queried fog snapshots and graphics/update scalars without inventing physical units or one-index-one-texel semantics. Binding-aware inverse-token and independent ordered member-access guards preserve executable expressions, original member spellings, types, declaration order and physical lines. Existing alpha/range/format/animation-lifetime quirks and unused compiler storage remain verbatim; conditional/artificial drafts are excluded. All fourteen complete candidate bodies and relocation targets match exactly. The original TED entry-compaction assembly remains unaccepted as C, with a same-line searchable note covering selection/count invariants, backing capacities, record field roles and callback mutation/alias domains; original creators, writers and callback targets are the resolution path. Full affected original packed modules, fresh original complete ROM, complete source hashes and regenerated uncertainty index gate acceptance. Angular-threshold and model-selector drafts remain unaccepted.

Totals: 339 further recoveries after the 225 upstream ordinary imports, plus 1190 existing C semantic cleanups. Current ledger: 861 assembly references = 818 ordinary + 43 entrypoints; 757,464 known remaining instruction bytes; zero unknown sizes; 325 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1185-color-particle-notes` and `accepted-color-particle-notes` verify real translation-unit instructions/full relocations, 4 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 340 further readable functions

Recover the 240-byte terrain packed-angular threshold wrapper. A null table returns one; otherwise the exact original atan2 operand division, native bias/scale, 5.625 angular division and signed 16 index narrowing select the packed five-bit level. Preserve the separate 15.625 input-level quantization and signed 16 narrowing: levels at least 32 require packed 31, while lower levels use the original signed greater-or-equal predicate. A natural direct comparison expresses the original SLT/XORI boolean without an artificial compiler temporary; every original instruction and relocation target matches. Initialize the genuine default result before the null guard as in the original lifetime. Keep native constants/data ownership and the packed-reader full s32 index ABI unchanged. Inline unknowns identify table extent/angle wrap, sample frame/units and finite/nonzero conversion domains, with original table builders/callers as evidence needed before any clamp or normalization. The reader remains original assembly with a searchable note covering actual MSB-first five-bit extraction, signed quotient/remainder behavior and second-byte boundary guarantees; no failed reader C is accepted. One canonical descriptive extraction symbol replaces the old wrapper address name without duplicate aliases. Full original packed terrain module, fresh original complete ROM, complete source hashes and regenerated uncertainty index gate acceptance.

Totals: 340 further recoveries after the 225 upstream ordinary imports, plus 1190 existing C semantic cleanups. Current ledger: 860 assembly references = 817 ordinary + 43 entrypoints; 757,224 known remaining instruction bytes; zero unknown sizes; 325 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1190-terrain-angular-level` and `accepted-terrain-angular-level-clean` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 341 further readable functions

Recover the396-byte terrain projection/draw callback with all original instruction words and relocation offset/type/target/value/addend records; incidental ELF enumeration order differs. Preserve the original threshold<=comparisonValue skip, including unordered floating-point drawing, the refresh flag, six frustum words, variadic property-one matrix output and original callback ordering. Explicit uncertainties cover matrix validity, threshold/metric units, masks, queue bounds and resource lifetime. Existing draw-helper argument now says channel from original registered callers; the old channel-byte getter becomes uvTerraGetIndexedDrawByte because the proved producer uses a tile-pointer difference while public caller domains remain unresolved. Three matching bitmap/texture loader functions receive33 grounded live identifier names, with binding/member/source/line guards preserving raw layouts, scratch and unused storage. Three additional existing-C comment improvements establish the lazy4096-byte fallback allocation, original graphics-begin reset to0xFF, destructor exclusion, local cleanup behavior and adjacent alternating TEXT counter words. Initial scratch contents, callback insertion success, indirect aliases, C cross-array bounds and reload lifetimes remain explicit unknowns. Original packed-equal TEXT/GMGR/CBCK/UVTXLD providers and real same-section BSS layout ground these statements; kernel loader zeroing is labeled accepted-source context rather than original kernel-byte proof. Searchable original-ASM notes preserve unresolved MED preview/model-selection, terrain queued-tile and spray drawing contracts with concrete producer/caller/provider resolution paths. No rejected draft becomes accepted C; no reachable player bug is asserted. Totals add one recovery and eight existing-C readability/comment edits. Full six affected packed modules, a fresh original USA ROM, complete source hashes and regenerated uncertainty index gate landing.

Totals: 341 further recoveries after the 225 upstream ordinary imports, plus 1198 existing C semantic cleanups. Current ledger: 859 assembly references = 816 ordinary + 43 entrypoints; 756,828 known remaining instruction bytes; zero unknown sizes; 325 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1203-loader-projection-contracts` and `accepted-loader-projection-contracts` verify real translation-unit instructions/full relocations, 6 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 342 further readable functions

Recover the392-byte fog setter as uvGfxSetFogParameters, retaining the original controls, clamps, geometry-mode writes and display-list coefficients. Two placeholder readonly float arrays are removed so the compiler owns the native32767 and-32467 literals at their original offsets; the isolated entire13,160-byte STAT module equals the original, with no fake storage or new data pragma. The physical meaning/domain of normalized controls remains explicitly unknown. Name one older bitmap local storedImageWidth from its actual size calculation and all100 original assets, keeping raw fields/types/layout and all1464 instruction bytes/relocations unchanged. Add a guarded, read-only MIO0-backed original texture inventory, metadata-only evidence and16 meaningful decoder/bounds tests. All1432 original textures decode and fit the six-row storage (maximum four used); all100 original bitmaps have nonzero divisors, bounded storage arithmetic and matching cursor extent. These inventories do not promise validity for modified/dynamic inputs, allocator success or lifetime. Correct VATR slot0C to three fixed word arguments plus promoted variadic words from actual native A3 homing/consumption; its source-only draft remains inactive and original ASM retained. Preserve unresolved MED initializer and terrain bound-mask contracts beside original ASM and in the regenerated uncertainty index. Totals add one recovery and two older-C readability/comment edits. Full affected packed modules, a fresh original USA ROM, complete source hashes and current uncertainty index gate landing.

Totals: 342 further recoveries after the 225 upstream ordinary imports, plus 1200 existing C semantic cleanups. Current ledger: 858 assembly references = 815 ordinary + 43 entrypoints; 756,436 known remaining instruction bytes; zero unknown sizes; 324 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1223-fog-asset-contracts` and `accepted-fog-asset-contracts` verify real translation-unit instructions/full relocations, 10 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 342 further readable functions

Correct medUpdateCameraByMode to take and explicitly forward its original incoming node pointer to both ASM-backed update paths; all64 instruction bytes and full relocation records equal the original. Repair the earlier camera-initialization uncertainty note from actual original dispatcher008F0/0D18 consumption, retaining mode/frame/object-lifetime unknowns. The larger orbit draft remains unaccepted. Add equal-line kernel source/header notes from original ROM instructions: encoded-data flag0x2 retains the compressed wrapper/data while returning its inner tag and reporting the wrapper-advertised decoded length; the allocation uses that wrapper size and the actual MIO0 decoder independently reads its internal size. Caller validation and malformed-input reachability remain unresolved; no reachable player bug is asserted. Preserve original-ASM notes for terrain channel records and sort-group selection, two small no-op callbacks, CARANIM populated-prefix byte clearing and SCRN shared-word copy. Notes identify concrete producer/caller/ownership evidence needed; do not infer variadic ABI from argument homing or fixed array capacity from copied words. No rejected recovery is banked. Totals add three existing-C signature/comment cleanups and zero recoveries. Full affected packed modules, fresh original USA ROM, complete source hashes and regenerated uncertainty index gate landing.

Totals: 342 further recoveries after the 225 upstream ordinary imports, plus 1203 existing C semantic cleanups. Current ledger: 858 assembly references = 815 ordinary + 43 entrypoints; 756,436 known remaining instruction bytes; zero unknown sizes; 324 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1236-camera-original-contracts` and `accepted-camera-original-contracts` verify real translation-unit instructions/full relocations, 5 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 342 further readable functions

Clarify two older-C comments from actual original reader and UFIL instructions: uvFileCopy tests the resource header type, not its FORM0 lookup category, and compressed-block sizeOut reports the wrapper-advertised decoded length regardless of retaining encoded data. Remove the unsupported unused-format claim. Metadata-only evidence accounts for all2478 non-null original resources:2455 validated FORM inputs contain2011 GZIP/MIO0 wrappers with equal advertised/internal lengths and valid checked header offsets. All23 non-FORM UVRW spans remain explicit opaque resources; original table/module/caller bindings establish parser paths but do not prove runtime ID reachability or the raw logical format. No corruption/safety/unusedness inference or complete format/routing claim is made. Preserve unresolved MED texture redirect, shared scalar copying and promoted scalar forwarding plus terrain pointer ordering beside original ASM, with concrete caller/field/ownership resolution paths. Native terrain initializer prefixes and footer ownership remain unchanged. No failed C draft is accepted. Totals add two existing-C comment improvements and zero recoveries. Full affected packed modules, a fresh original USA ROM, all source hashes and regenerated uncertainty index gate landing.

Totals: 342 further recoveries after the 225 upstream ordinary imports, plus 1205 existing C semantic cleanups. Current ledger: 858 assembly references = 815 ordinary + 43 entrypoints; 756,436 known remaining instruction bytes; zero unknown sizes; 324 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1245-original-header-boundaries` and `accepted-original-header-boundaries` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 342 further readable functions

Improve four older C contracts: expose the existing material scalar side effect in caranimAdjustScalarAndGetMaterialOffset, name its parameters/locals precisely without changing the kind member, document that the material getter returns a module-table address without proving ownership, and ground registry lookup/counter comments in the original constructor and reader instructions. The material body retains all160 instruction bytes and every full relocation record. Independent inverse-token/member/physical-line guards and an exact wrapper-aware whole-source composition audit cover the combined patches and canonical rename. The constructor increments the counter even when all eight slots are full; this is marked RE_ORIGINAL_QUIRK, while caller bounds, allocation/lifetime and runtime reachability remain RE_UNKNOWN. The focused registry type is explicitly a partial view of a0x45C allocation, and the byte23C note records actual helper-call-latch writes/reads without guessing its role or reset cadence. Add precise RE_UNKNOWN original-assembly notes for the checked MED ten-case color-source mapping, terrain static-model two-lookup sequence and asymmetric intersection scalar-side outputs. No rejected C recovery is accepted and no player-visible defect is inferred from unknown reachability. Totals add four existing-C semantic/comment improvements and zero recoveries. Full affected original packed modules, a fresh original USA ROM, complete source hashes and a regenerated uncertainty index gate landing.

Totals: 342 further recoveries after the 225 upstream ordinary imports, plus 1209 existing C semantic cleanups. Current ledger: 858 assembly references = 815 ordinary + 43 entrypoints; 756,436 known remaining instruction bytes; zero unknown sizes; 324 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1259-material-registry-contracts` and `accepted-material-registry-contracts` verify real translation-unit instructions/full relocations, 4 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 342 further readable functions

Improve six older C functions/contracts without changing original game bytes. camCopyMatrixIntoRecordOffset1A8 explicitly forwards the original incoming A1 matrix pointer to actual FMTX slot0C, whose original provider copies sixteen ordered floats into camera offset0x1A8; correct the focused export/prototype and initializer address-field name/comment. Independent original wrapper/provider/initializer evidence and all48 instruction bytes/full relocations support the change, while matrix frame, layout and source lifetime/aliasing remain unknown. Name the two existing64-byte helpers medWriteFirstSharedRgbaCommand/medWriteSecondSharedRgbaCommand from actual DLED slot10 FA/FB packing, and replace obsolete registration/provider comments in those helpers and medRefreshMatchedControlText with original label-table/combiner-command behavior plus remaining bounds/storage/domain/lifetime unknowns. Name the existing8-byte unsigned getter uvIsectGetRecordByte10, preserving its signed-word return ABI and unresolved byte meaning. All184 selected instruction bytes and full relocation records match the original. Add precise original-ASM notes for two terrain view wrappers and the dynamics query input: direct flag8/1 reads and indirect flag2 forwarding can observe the adjacent word left unassigned before the first native query; the second query stores zero. Historical C initialization, complete helper paths, caller flags, selector bounds and reachable player impact remain explicitly unproven. No rejected recovery or inferred runtime correction is accepted. Totals add six existing-C semantic/comment improvements and zero recoveries. Full affected original packed modules, a fresh original USA ROM, complete source hashes and the regenerated uncertainty index gate landing.

Totals: 342 further recoveries after the 225 upstream ordinary imports, plus 1215 existing C semantic cleanups. Current ledger: 858 assembly references = 815 ordinary + 43 entrypoints; 756,436 known remaining instruction bytes; zero unknown sizes; 322 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1266-camera-dled-original-contracts` and `accepted-camera-dled-original-contracts` verify real translation-unit instructions/full relocations, 5 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 344 further readable functions

Recover uvIsectQueryMinimumValueRecord and uvIsectQueryInputVectorsIntoRecord as clean commented C, preserving all436 original instruction bytes and every complete relocation record. The aggregate retains query flag order2/8/1/4, strict88-byte minimum-record updates, the original1.1 threshold, ordered final<=1 test and output-prefix store order. Its two genuine local declarations are organized threshold-before-scratch, with no artificial padding or changed operations. The delegate initializes only output byte offsets0x00/0x04 and forwards the original vector order, raw input word0x18 and native-width words to helper0x401558. Reuse the established88-byte record layout, move its unchanged typedef before both functions, and mark the new input prefix/observed prototypes as incomplete historical views. Preserve helper fraction-assignment observations and unknown input domains, coordinate meaning, flag/context roles, aliasing, lifetime and reachable behavior. Improve six older C functions/contracts: carAudioPrependCommand now uses soundHandlingEnabled, soundId and volume from actual original CARAUDIO consumers and SND slot6C/84 provider instructions, preserving types/offsets and all112 original bytes/full relocations; five older DLED comments distinguish proven scanner/label/RGBA operations from unresolved target presence, command extents and ownership. Precise RE_UNKNOWN/RE_ORIGINAL_QUIRK notes remain beside three parked DLED codecs and the parked MED texture editor; no failed drafts are accepted. Totals add two recoveries and six existing-C semantic/comment improvements. Full affected original packed modules, a fresh original USA ROM, complete source hashes and the regenerated uncertainty index gate landing.

Totals: 344 further recoveries after the 225 upstream ordinary imports, plus 1221 existing C semantic cleanups. Current ledger: 856 assembly references = 813 ordinary + 43 entrypoints; 756,000 known remaining instruction bytes; zero unknown sizes; 322 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1274-audio-query-contracts` and `accepted-audio-query-contracts` verify real translation-unit instructions/full relocations, 4 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 344 further readable functions

Improve six existing C functions without accepting a new recovery: two intersection query users share a neutral word18 member because actual original helpers low-bit-test the word or conditionally dereference it; their complete436 instruction bytes and full relocation records remain exact, and all guarded context/body changes compose to the independently audited whole-source hash before the banker line wrapper. An older selected-light wrapper now exposes the actual LIGHT tagged variadic parser rather than a single fixed tag signature, retaining tag1 promoted scalar order and132 original bytes/full relocations. Two older64-byte RGBA wrappers use explicit native-width command-address and observed read-only binary32 channel pointer views, preserving all128 bytes/full relocations without guessing historical complete storage. The audio prepend comment records only the proven fresh caud-image BSS-head zeroing, retaining capacity, cached reset/freeing and opaque-value uncertainties. A precise note beside retained intersection01558 assembly records original object-byte access, strict minimum selection, raw helper-result retention and mixed word representation; historical scratch declaration/alignment and helper-output validity remain unknown. Failed drafts are excluded. Full affected modules, fresh original USA ROM, complete source hashes and the regenerated uncertainty index gate landing.

Totals: 344 further recoveries after the 225 upstream ordinary imports, plus 1227 existing C semantic cleanups. Current ledger: 856 assembly references = 813 ordinary + 43 entrypoints; 756,000 known remaining instruction bytes; zero unknown sizes; 322 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1286-neutral-parser-contracts` and `accepted-neutral-parser-contracts` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 344 further readable functions

Improve seven existing C functions while preserving all872 original instruction bytes and full relocation records. The older camera initializer now describes actual CAM20 as a tagged variadic parser; its original three aligned double arguments and tag sequence remain unchanged. Atomically type medReleaseStoredCameraChannel as a pointer to one stored native-width camera address and adjust its sole direct release caller; actual CAM08 consumes a signed-short channel, forwards it to UVCHAN20 and stores -1, while complete ownership/repeated-release validity remain unknown. Audio start uses preparedSlotId for the returned managed slot, distinguishing the separately supplied sound selector. Audio allocation uses sourceRecordAddress and handleSlotIndex from original consumer dereferences and stride8 handle table accesses; the original repeated halfword store, s32 ABI, operations and ordering remain. Name two existing intersection shared-scalar accessors from the actual ISCT80 provider and Dynamics original caller, retaining physical units/domains/protocol uncertainties. Preserve original assembly beside three parked drafts: MED environment selection, Dynamics node update/finalization and results positive-ratio scaling. Their searchable notes distinguish proven original operations and call contracts from unresolved historical source/storage declarations and remaining compiler differences; no failed draft is accepted. Full affected modules, fresh original USA ROM, complete source hashes and regenerated uncertainty index gate landing.

Totals: 344 further recoveries after the 225 upstream ordinary imports, plus 1234 existing C semantic cleanups. Current ledger: 856 assembly references = 813 ordinary + 43 entrypoints; 756,000 known remaining instruction bytes; zero unknown sizes; 320 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1298-camera-audio-scalar-contracts` and `accepted-camera-audio-scalar-contracts` verify real translation-unit instructions/full relocations, 5 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 344 further readable functions

Improve five existing C function contracts: the environment scalar-pair wrapper uses the observed variadic tagged parser and neutral ID/unit-scalar names, without asserting physical blend/rate meaning or that ID!=-1 proves validity; the original property3 provider may reject the first scalar. The environment query uses property-number/ordinal local names instead of unproved RGB/blend/rate roles, preserving every local type/declaration/argument and the intentional shared second-output address for tags2/3. Its original absent-file panic/null-store behavior is explicitly indexed without claiming reachable failure. Animation selection is named caranimSelectCameraLightBufferSlot from actual original UVLIGHT1C allocation, constructor state248 store, UVLIGHT20 selector and UVLIGHT0690 emitted buffer addresses; CAM30 remains an address-bearing indirection and camera-word/slot validity/lifetime stay unknown. Two stale pause summaries now state unresolved original MENU callback/layout/lifetime contracts while retaining accurate existing operation comments. All492 selected instruction bytes and complete relocation records remain exact. Retain original assembly with precise known-operation and RE_UNKNOWN notes for reviewed Dynamics ranked-vector scratch/record projection, pause selector/short-bank update and piece five-record traversal drafts. No failed draft/types are accepted. All affected original packed modules, a fresh original USA ROM, complete source hashes and regenerated uncertainty index gate landing.

Totals: 344 further recoveries after the 225 upstream ordinary imports, plus 1239 existing C semantic cleanups. Current ledger: 856 assembly references = 813 ordinary + 43 entrypoints; 756,000 known remaining instruction bytes; zero unknown sizes; 320 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1313-environment-light-contracts` and `accepted-environment-light-contracts` verify real translation-unit instructions/full relocations, 5 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 345 further readable functions

Recover uvDynGetNodeVectorProperty from the actual original vector-copy and direction-transform providers, preserving unsupported-selector no-store behavior and explicit unknown physical meanings/coordinate frames/alias/output domains. V3 ownership retains the exact original252+148+212 bytes around compiler-owned112+76+80 byte tables; adjacent compiler tables require no fictitious host or padding. Both existing owners and original assembly hosts remain exact. Clarify MED optional-target low-byte forwarding and PAUSE replay-byte zero-test from original GAME/module/provider bindings, retaining unresolved storage meaning/lifetime. Refine original label minus-one behavior using63 original relocation records and original native loader dispatch, while preserving integer return and unknown language/caller reachability. Preserve original assembly beside the unmatched selected-state property27 draft and original unassigned-stack vector-address return. Correct dormant scanRela DATA/RODATA site bases and include the final declared record with strict extent/count validation; its current CLI does not invoke this helper, so no existing build/runtime corruption is asserted. Gate acceptance on all focused tests, real repeated extraction, final named whole-module instruction/relocation proof, all affected original packed modules, fresh original ROM and complete source/index hashes.

Totals: 345 further recoveries after the 225 upstream ordinary imports, plus 1244 existing C semantic cleanups. Current ledger: 855 assembly references = 812 ordinary + 43 entrypoints; 755,564 known remaining instruction bytes; zero unknown sizes; 319 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1346-vector-readonly-contracts-fixed` and `accepted-vector-readonly-contracts-fixed` verify real translation-unit instructions/full relocations, 6 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 345 further readable functions

Name gameNoOpModuleCleanup using original GAME export registration and native UVMO disposal dispatch; preserve empty body, ABI, identity and unresolved broader ownership. Expose the existing ENVSND matching-only empty count condition as explicit unresolved source debt. Retain unmatched TED second-list producer/compactor and CARANIM particle-palette assembly with precise original provider, bounds, callback and lifetime notes. Refine the existing Dynamics endpoint-query note with conditional unwritten input-word consumers, full u16 indexing, original fallback scalar-store timing and local query-address lifetime uncertainty. No unmatched draft or speculative runtime correction is accepted; preserve all original executable logical coordinates and standalone assembly directives. Gate on exact cleanup instructions/relocations, five original packed modules, fresh full ROM and complete source/index hashes.

Totals: 345 further recoveries after the 225 upstream ordinary imports, plus 1246 existing C semantic cleanups. Current ledger: 855 assembly references = 812 ordinary + 43 entrypoints; 755,564 known remaining instruction bytes; zero unknown sizes; 318 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1362-endpoint-editor-uncertainties` and `accepted-endpoint-editor-uncertainties` verify real translation-unit instructions/full relocations, 5 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 345 further readable functions

Name camAssignEnvironmentFileWithOptionalCopy from actual environment export18/1C bindings and original provider bodies. Native camera A1 remains the incoming sourceFileId at the optional copy call; explicitly pass that second integer argument while preserving exact original instructions. Then assign the destination file to the signed-short camera slot, preserving reloads after the callback. Leave camera layout, caller domains, ownership and lifetimes unresolved. Retain unmatched TED selected-record loader and Dynamics attachment-query assembly with precise original input-bound, callback, failure-sentinel, query-state and return-count notes. The Dynamics low16 returned count is explicitly traced to its initialized word; no uninitialized-return claim is made. Gate on original packed modules, fresh complete ROM and complete source/index hashes.

Totals: 345 further recoveries after the 225 upstream ordinary imports, plus 1247 existing C semantic cleanups. Current ledger: 855 assembly references = 812 ordinary + 43 entrypoints; 755,564 known remaining instruction bytes; zero unknown sizes; 317 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1372-camera-query-contracts` and `accepted-camera-query-contracts` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 347 further readable functions

Recover uvPfxLoaderApplySharedResourceWord from actual original UPFX setter dispatch, raw40-entry readonly table and native word consumers. Snapshot one32-bit caller word, reload signed configured count and shared selector/base/export per setter, and preserve raw1008 UVTX-ID versus1013 TSEQ behavior. All748 instruction bytes and complete24-record relocation multisets match; relocation record order alone differs. Name camAccumulateScalarAndQueryProperty and camClearSharedRecordWord1EC, with readable local names, inverse executable-token proof and exact280 original bytes/ordered relocations; preserve ordered nonpositive/NaN negation and unused callback ABI. Keep TED indexed controller transform in original assembly with precise frame/scalar/index/callback uncertainty and actual FMTX24 no-op word-call contract. No unmatched draft or speculative runtime repair is accepted. Gate on all affected original packed modules, fresh complete ROM and complete source/index hashes. The PHDR header recovery preserves two-byte item-buffer allocation, short stores, single-float reciprocal, zero-only state default and kind-nine vector allocation. Consolidate both recovered routines onto one observed configuration view. Improve uncertainty lookup across complete #line directives while retaining blank-line, real-code, macro, trailing-comment and quoted-text boundaries. Index bounded generated new_var identifiers without matching strings, comments or longer names. All 31 indexing regressions pass; the old tool fails the new positive cases. Add the original-backed AI object/terrain query note with confirmed leaf flag-setter behavior and unresolved vector units, scene-byte domain and record action.

Totals: 347 further recoveries after the 225 upstream ordinary imports, plus 1249 existing C semantic cleanups. Current ledger: 853 assembly references = 810 ordinary + 43 entrypoints; 754,816 known remaining instruction bytes; zero unknown sizes; 315 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1379-particle-camera-readability` and `accepted-particle-camera-readability` verify real translation-unit instructions/full relocations, 4 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 347 further readable functions

Clarify three older generated C bodies with descriptive parameters and locals, four-space formatting and operation names, preserving all 368 original instruction bytes and full ordered relocation records. Name four older pause wrappers from actual native instruction spans, preserving track-byte truncation, state request, halfword writes and callback order. Existing uncertain byte roles, action meaning and provider contracts remain explicit. Correct the two track-copy comments to separate original machine store ordering from C statements and keep state fourteen numerical until dispatcher evidence is established. Add the particle dispatcher original block/count/publication and reader-lifetime evidence beside retained assembly, keeping unknown original asset/caller/storage guarantees searchable and preserving logical source coordinates. Add the original-backed counter/channel quad note beside retained battle assembly; its readable draft differs only in frame allocation and remains unaccepted without invented padding. No unmatched draft or speculative runtime repair is accepted. Mandatory affected packed-module, fresh complete ROM, source manifest and regenerated index gates apply.

Totals: 347 further recoveries after the 225 upstream ordinary imports, plus 1256 existing C semantic cleanups. Current ledger: 853 assembly references = 810 ordinary + 43 entrypoints; 754,816 known remaining instruction bytes; zero unknown sizes; 308 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1402-older-generated-local-contracts-fixed` and `accepted-older-generated-local-contracts-fixed` verify real translation-unit instructions/full relocations, 6 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.

Full-module validation rejected the expanded selection-loop formatting: two address-add instructions exchanged positions. Restore its exact frozen statement layout while retaining descriptive locals, operation names and explicit unknowns. The other five affected modules matched the original in the failed wave; require all six modules and a fresh complete ROM in this repair wave. Failed wave 1394 is retained for diagnosis.


## Historical accepted checkpoint — 347 further readable functions

Name envSndBindRegionTableAndInitializeHandles and tdataReturnZeroScalar using original complete instruction spans. Preserve count/table/global callback ordering, f32 square to signed truncation, the existing empty count test and unused declaration, source-line directives, and homed unused constant-return argument. All196 instruction bytes and complete ordered relocation records match. Document original intersection payload refresh and AI linked-record ordering/summary contracts, retaining unmatched assembly and explicit capacity, aliasing, coordinate, lifetime and historical-source gaps. Fix the generated stack-name heuristic to require a digit or uppercase hexadecimal suffix character: remove four demonstrated ordinary-word false positives while preserving every retained record and all128 observed stack names; fully lowercase alphabetic suffixes remain outside this documented heuristic. The34-test suite passes and the old tool fails exactly two new regressions. No unmatched draft or speculative runtime repair is accepted. Gate on all affected original packed modules, fresh complete ROM, full source manifest and current index.

Totals: 347 further recoveries after the 225 upstream ordinary imports, plus 1258 existing C semantic cleanups. Current ledger: 853 assembly references = 810 ordinary + 43 entrypoints; 754,816 known remaining instruction bytes; zero unknown sizes; 306 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1410-utility-uncertainty-contracts` and `accepted-utility-uncertainty-contracts` verify real translation-unit instructions/full relocations, 4 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 347 further readable functions

Clarify uvIOUpdate, uvControllerPakDeleteFile, uvControllerInitPak and uvControllerRumbleInit using complete original1524-byte instruction spans and full ordered relocation proof. Rename controller/file/result/previous-state locals without changing ABI, types, branches, ordering or numeric states. Preserve shared cached file identity rather than substituting the local metadata output. Record both-path return-one behavior as an original quirk; callback mutation, index guarantees, cache serialization and state lifecycles remain explicit unknowns. Correct DEVICE_ERROR state-four prose without equating it to no peripheral. Add the actual original ISCT44 parameter-bank provider, low16 input/index/end-table, modes and buffer-address contract beside the unmatched Dynamics range publisher; retain assembly and unresolved construction/capacity/lifetime/historical-source requirements. No compiler-shape permutation, unmatched draft or speculative runtime change is accepted. Both affected original packed modules, fresh full ROM, complete source hashes and regenerated index remain mandatory.

Totals: 347 further recoveries after the 225 upstream ordinary imports, plus 1262 existing C semantic cleanups. Current ledger: 853 assembly references = 810 ordinary + 43 entrypoints; 754,816 known remaining instruction bytes; zero unknown sizes; 306 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1420-controller-query-uncertainties` and `accepted-controller-query-uncertainties` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 347 further readable functions

Clarify two older rumble routines and the52-byte first-player sound-handle release wrapper using complete original964-byte instruction spans and full ordered relocation proof. Canonically name the producer rumbleMergeQuantizedPatternValues and replace generated arguments/locals while preserving ABI, self-stores, conversion and comparison order. Correct the old per-controller enable-word claim to the native byte operation and describe stop/reinitialization as requests because actual providers can return without acting. Timing units, level domains, caller bounds and lifecycle remain explicit unknowns. Add original Dynamics scalar setter and race pause-pass operation/provider/width contracts beside retained assembly, including the signed settings halfword at88 and actual player handle-release callback. Unmatched drafts remain diagnostics. No arbitrary source-shape search, unsupported readonly migration or guessed runtime change is accepted. All affected original packed modules, fresh full ROM, complete source hashes and regenerated uncertainty index remain mandatory.

Totals: 347 further recoveries after the 225 upstream ordinary imports, plus 1265 existing C semantic cleanups. Current ledger: 853 assembly references = 810 ordinary + 43 entrypoints; 754,816 known remaining instruction bytes; zero unknown sizes; 305 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1429-rumble-scalar-pause-contracts` and `accepted-rumble-scalar-pause-contracts` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 347 further readable functions

Improve names in twelve older engine functions using complete3780-byte instruction spans and full ordered relocation records. Matrix copy alias paths, exact arithmetic/order, Euler scratch reuse, full texture-state input bits, callback reloads, unused light count snapshot/argument and original scalar types remain unchanged. Actual allocation/free/index consumers ground light buffer-address names. Two audio comment corrections identify managed-handle forwarding and original unchecked source dereferences without claiming proven nonnull callers. Independently correct the recorder pair key member u32 to f32 based on original producer arithmetic, float-key comparison and native float bit-copy; retain identical8-byte pair/164-byte buffer layout and all active consumer bodies. The116-byte C converter still differs in five cursor-register instructions and remains original assembly; inline notes retain count/capacity/alias/units/NaN/discarded-purpose unknowns. No speculative runtime change, shape permutation or assembly recovery is accepted. All eight affected original packed modules, fresh full ROM, complete source manifest and regenerated index remain mandatory.

Totals: 347 further recoveries after the 225 upstream ordinary imports, plus 1277 existing C semantic cleanups. Current ledger: 853 assembly references = 810 ordinary + 43 entrypoints; 754,816 known remaining instruction bytes; zero unknown sizes; 305 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1446-engine-audio-recorder-contracts` and `accepted-engine-audio-recorder-contracts` verify real translation-unit instructions/full relocations, 8 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 348 further readable functions

Recover profgameCreateProfileCarControls as readable C after verifying all 364 original instruction bytes and the complete 16 relocation records including offsets, types, symbols, values and addends. Relocation serialization order differs; original packed-module and fresh full-ROM checks remain mandatory. Original GAMEGUI, GUI, MISC and CARA initializers and actual targets ground all eleven calls, the shared host snapshot, signed-low16 pool results, profile labels, flags 0x12, bounds 0..8 and optional output storage. Preserve unchecked allocation/attachment and bound value data; entry reachability, full label-readable windows, ownership and lifecycles remain explicit unknowns. Add precise Dynamics and battle contracts beside retained assembly, including exact-zero count gating, shared scalar reset/reloads, result narrowing, matrix/vector copies, original DIV.S/MUL.S modes, promoted-double comparison and callback-sensitive reloads. Both unmatched drafts remain isolated; no stack padding, compiler-shape search or speculative runtime fix is accepted. All three original packed modules, fresh full ROM, complete source manifest and regenerated uncertainty index remain required.

Totals: 348 further recoveries after the 225 upstream ordinary imports, plus 1277 existing C semantic cleanups. Current ledger: 852 assembly references = 809 ordinary + 43 entrypoints; 754,452 known remaining instruction bytes; zero unknown sizes; 305 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1457-profile-controls-contracts` and `accepted-profile-controls-contracts` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 348 further readable functions

Clean up two existing fixed-matrix C helpers after independently reviewing original packed instructions and their by-value ABI. Give the partial transpose a precise semantic name, rename its local addresses and document only the six off-diagonal integer/fractional entries copied in the upper3x3 area. Preserve the original unusual alias/copy-back tests and partial temporary initialization; caller reachability and intended usage remain unknown. Clarify that the full copy preserves interleaved source loads/destination stores rather than promising an immutable snapshot under native overlap. All352 instruction bytes and complete ordered relocation records match. Add five adjacent retained-assembly contracts for Dynamics terrain querying and query-result adjustment, Motion vector/phase updates, AI record selection/audio, and demo replay/camera updates. Mark original narrowing, unchecked counts/tail, ignored normalize result and ordered-negative sqrt behavior separately from unproven scalar units, frames, domains, ownership and aliasing. Unmatched drafts remain isolated with exact diagnostic receipts, without padding, forced registers or arbitrary shape searches. Regenerate and check the searchable uncertainty index; require all affected original packed modules, a fresh full ROM and complete source-manifest proof.

Totals: 348 further recoveries after the 225 upstream ordinary imports, plus 1279 existing C semantic cleanups. Current ledger: 852 assembly references = 809 ordinary + 43 entrypoints; 754,452 known remaining instruction bytes; zero unknown sizes; 304 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1482-matrix-query-uncertainties` and `accepted-matrix-query-uncertainties` verify real translation-unit instructions/full relocations, 5 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 349 further readable functions

Recover demoCreateReplayControlGroup as readable named C using actual GUI, MISC, GAMEGUI, REPLAY and AI provider contracts. All 460 original instruction bytes and all 22 complete relocation records agree, including offsets, types, symbols, values and addends; only serialization order of two value/label HI16/LO16 pairs differs. Preserve all 13 calls, the shared-host snapshot before initialization, signed-low16 pool indices, float-backed scalar rows with flags 0x11 and bounds 0..500, null output pointers, replay controls and optional original empty AI callback. Keep original unchecked allocation/attachment; full label-readable windows, bound-value units, caller lifecycle and native callback source ABI remain explicit unknowns. Add an adjacent graph-display contract beside retained Motion assembly. Its unmatched draft remains isolated: native multiply-by-unity is removed by the compiler, floating-point storage and instruction/relocation placement differ; no exceptional-float equivalence is assumed. Document two original editor text-selector paths that can pass unwritten scratch bytes when unsigned selectors exceed their handled domains. Caller reachability, historical scratch-object extent, backing-record bounds and callback mutation remain explicit unknowns; do not claim a reachable player bug or invent default text. Regenerate and check the uncertainty index. All three original packed modules, a fresh complete ROM and complete source-manifest proof remain mandatory.

Totals: 349 further recoveries after the 225 upstream ordinary imports, plus 1279 existing C semantic cleanups. Current ledger: 851 assembly references = 808 ordinary + 43 entrypoints; 753,992 known remaining instruction bytes; zero unknown sizes; 304 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1488-demo-replay-menu-contracts` and `accepted-demo-replay-menu-contracts` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 349 further readable functions

Clarify one older text-rendering function with proven primitive-color export, descriptor RGB components, byte index and object alpha names; descriptor extent, valid index and unused bytes stay explicit unknowns. All 84 original instruction bytes and full ordered relocation records agree. Add a native dynamics query/vector-offset contract beside retained assembly, preserving sentinel gates, narrowed results, callback order, range reset before zero return, original facing/cross/normalize aliases, exact 0.1f factor, and matrix-before-query vector updates. Keep physical frames/units, result semantics, allocation, callback effects and caller domains unresolved. Add a native vehicle scalar-response contract beside retained assembly, with actual ordered clamp provider and mixed single/double arithmetic documented. Both C recovery drafts remain unaccepted after instruction and full relocation mismatches; no universal exceptional-float equivalence is claimed and no trial-only types/prototypes are banked. Regenerate and check the uncertainty index. All three original packed modules, fresh complete ROM and complete source-manifest proof remain mandatory.

Totals: 349 further recoveries after the 225 upstream ordinary imports, plus 1280 existing C semantic cleanups. Current ledger: 851 assembly references = 808 ordinary + 43 entrypoints; 753,992 known remaining instruction bytes; zero unknown sizes; 304 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1500-letter-query-scalar-contracts` and `accepted-letter-query-scalar-contracts` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 350 further readable functions

Recover tdataApplyFirstMatchingScalarLink from all380 exact original instruction bytes and seven complete ordered relocation records. Preserve the packed-handle snapshot before both getters, unsigned fraction and record scalar reloads, exact external normalization constant, conditional sample-pair snapshot, ordered difference/negation branches, strict tolerance/bounds tests and first-match target-minus-value request with optional-position word zero. Mark original unchecked record lookup separately from unknown allocation, valid-handle, alias/lifetime, acyclic-list, physical units and caller guarantees. Correct one older UFO allocator: original TDATA slot08 adjusts record state and slot10 resets record state; remove unsupported attachment/ownership wording while preserving all216 instruction bytes and complete ordered relocations. Keep unchecked allocation and unresolved state/position/camera contracts indexed. Document native dynamics stored-vector interpolation and matrix update beside retained assembly, including zero-mode helper scratch initialization before read, full halfword mode, original provider aliases and partial final3x3 copy. The720-byte draft remains unaccepted: all ordered relocations and call/branch positions match but45 stack immediates differ. Require genuine source evidence for further recovery. Regenerate/check the uncertainty index and require all affected packed modules, fresh full ROM and complete source hashes.

Totals: 350 further recoveries after the 225 upstream ordinary imports, plus 1281 existing C semantic cleanups. Current ledger: 850 assembly references = 807 ordinary + 43 entrypoints; 753,612 known remaining instruction bytes; zero unknown sizes; 304 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1506-tdata-scalar-link-contracts` and `accepted-tdata-scalar-link-contracts` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 351 further readable functions

Recover pausePlayPendingRandomSound from all384 exact original instruction bytes and all32 complete relocation records, including exact offsets, types, symbols, values and addends; only relocation serialization order differs. Preserve random-float truncation, separate casesD8/D9/DA, shared pending-word reads, volume getter before sound-table reload, priority7FFF, original pitch0.5 and unconditional postplay pending clear. Original playback failure is ignored; sound metadata, pending/RNG/handle lifetimes and storage extent remain unknown. Correct one older RESULTS function: original SND fifth scalar flows through emitter field68, computed field74 and alSndpSetPitch, while pan independently uses byte81/alSndpSetPan. Name only proven local playback/volume callbacks, preserve void ignored-result view and all332 bytes/14 ordered relocation records, and remove unsupported timer-unit claims. Correct the Emitter size comment only to native allocation/stride0x90. Document native sphere/query refresh, motion asymmetric vector gates and race record/replay gates beside retained ASM. Their clean drafts remain unmatched: dynamics480bytes/12stack words/full ordered relocations, motion812bytes/37words/full ordered relocations, race512bytes/95words/relocation differences. No padding/register forcing or hidden semantic fixes. Unknown enums, vector frames, units, bounds, ownership, alias/lifetime and caller guarantees remain explicit searchable notes. Require six affected original packed modules, fresh full ROM, all source hashes and regenerated uncertainty index.

Totals: 351 further recoveries after the 225 upstream ordinary imports, plus 1282 existing C semantic cleanups. Current ledger: 849 assembly references = 806 ordinary + 43 entrypoints; 753,228 known remaining instruction bytes; zero unknown sizes; 304 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1520-pause-audio-query-contracts` and `accepted-pause-audio-query-contracts` verify real translation-unit instructions/full relocations, 6 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 351 further readable functions

Clean seven older functions with792 exact original instruction bytes and38 complete ordered relocation records: linked PAUSE menu selection184, CARANIM handle lookup88, FVEC squared lengths40/28, and BATTLE flag helpers128/128/196. Correct falsely described owner refresh to actual MENU first-selected index, native fullword return narrowed by original SH16, and graphics wait only when requested. Preserve callback reloads and historical argument views. Correct public squared-length spellings through existing canonical aliases; do not add duplicate aliases. Identify DOBJ handles and actual set/clear flag callbacks without changing pointer storage or legacy extra arguments. Add adjacent native sphere-update, endpoint-pair, controller-presence selection and signed-motion notes: clean drafts remain unmatched and assembly retained. Explicit RE_UNKNOWN and RE_ORIGINAL_QUIRK separate unresolved units, domains, capacities, lifetimes and historical declarations from confirmed original asymmetric containment, unordered predicates and pending source-shape differences. No new reachable gameplay bug claimed. Require all affected original packed modules, fresh full ROM, complete source hashes and regenerated uncertainty index.

Totals: 351 further recoveries after the 225 upstream ordinary imports, plus 1289 existing C semantic cleanups. Current ledger: 849 assembly references = 806 ordinary + 43 entrypoints; 753,228 known remaining instruction bytes; zero unknown sizes; 304 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1544-selection-flag-uncertainties` and `accepted-selection-flag-uncertainties` verify real translation-unit instructions/full relocations, 6 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 351 further readable functions

Resolve one older REPLAY representation uncertainty: original A2 word is forwarded to actual FVEC04/uvVec3FSet third-float storage at offset8; use f32z jointly with the canonical setter to preserve bits without numeric conversion. Rename the fourth scalar without claiming physical radius. Preserve20-byte allocation, scalar square, list/store ordering, unchecked allocation and all120 exact original bytes/5 ordered relocation records. The historical formal declaration remains unproved because machine ABI alone is not unique. Fix uncertainty search ownership for one generated blank inside paired definition #line wrappers; reject ordinary detached notes, arbitrary directives, prototypes, assembly and mismatched filenames. All38 regressions pass and real-corpus audit adds21 unknown/six quirk function contexts while every group ID/evidence/location remains unchanged. Document retained MENU wrapped-search/latch contracts, Dynamics raw callback-word storage and child flag propagation, Motion bounded-response ordering, two unchecked CARAUDIO selector/slot guarantees and four model bounds/matrix-stack contracts. The Dynamics shared-base correction still differs by16 register-allocation words; retain original ASM. Its earlier252-byte candidate had a real extra ADDU, not alignment padding. Retain original unordered comparisons, rejected-push increments and unknown caller guarantees; no newly reachable gameplay bug claimed. Comment-only notes do not increase recovered/older-code counts. Require all affected original packed modules, fresh full ROM, complete source hashes and regenerated uncertainty index.

Totals: 351 further recoveries after the 225 upstream ordinary imports, plus 1290 existing C semantic cleanups. Current ledger: 849 assembly references = 806 ordinary + 43 entrypoints; 753,228 known remaining instruction bytes; zero unknown sizes; 304 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1558-replay-searchable-contracts` and `accepted-replay-searchable-contracts` verify real translation-unit instructions/full relocations, 6 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 351 further readable functions

Improve two existing model texture routines with descriptive parameters and loop variables. Member-aware binding replacement and ordered member-selector checks preserve the graphics-state table; reverse binding proof recovers complete original code. All664 instruction bytes and four complete ordered relocation records match. Replace unsupported caller-responsibility language with the actual unchecked output writes and an explicit unknown requiring caller/model-count evidence. Preserve both routines original executable logical coordinates despite expanded comments. Add adjacent native contracts for AI linked scalar-gap gating, Dynamics attachment scalar properties and pause latched menu actions. Keep the original pause entry-gate read before the negative sentinel test, saved action result, live menu reloads and unchecked callback index; caller reachability and historical callback prototypes remain unknown. Retain the original subtraction/negation, saved head/scalar, state/callback ordering, float-to-unsigned conversions, u16 list transitions, cached count/bound, ordered shifting and stale trailing pointer. Conversion repeats only when old kind is zero and the first narrowed result is not one; each conversion restores floating control state. Unmatched drafts remain isolated: AI differs in frame/register/load scheduling; sole grounded Dynamics shared-counter correction leaves52 register-only words, with all10 complete relocation records identical as a multiset. Neither assembly routine counts as recovered. Require all affected original packed modules, a fresh complete ROM build, complete source hashes and regenerated uncertainty index.

Totals: 351 further recoveries after the 225 upstream ordinary imports, plus 1292 existing C semantic cleanups. Current ledger: 849 assembly references = 806 ordinary + 43 entrypoints; 753,228 known remaining instruction bytes; zero unknown sizes; 304 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1584-model-texture-uncertainties` and `accepted-model-texture-uncertainties` verify real translation-unit instructions/full relocations, 4 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 351 further readable functions

Improve four existing readable routines without changing the original binary. The screen rectangle caller now declares the actual fullword provider contract while retaining signed-short source fields, coordinate order, eight-byte advances and live count reloads. The spark transform countdown preserves signed-negative availability/reset, acquisition value five, zero-inclusive transform update and post-callback decrement; cadence and state lifetime remain unknown. Filmroll names describe sampled integer writes and a shared-word increment without claiming position, activation or physical units. All532 instruction bytes and19 complete ordered relocation records match. Explicitly flag unresolved index, storage, alias and lifetime domains in five replay readers, replacing unsupported caller-ownership promises. Retain original Motion graph-response and deferred pause assembly with precise native behavior and resolution evidence beside each pragma. Their nonmatching C remains isolated: Motion984 versus1000 bytes and235 differing words, pause476 bytes and69 differing words, both with unequal complete relocation records. No new assembly recovery is counted. Full six-module, fresh complete ROM, complete source-hash and generated uncertainty-index gates are mandatory.

Totals: 351 further recoveries after the 225 upstream ordinary imports, plus 1296 existing C semantic cleanups. Current ledger: 849 assembly references = 806 ordinary + 43 entrypoints; 753,228 known remaining instruction bytes; zero unknown sizes; 304 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1602-screen-spark-unknowns` and `accepted-screen-spark-unknowns` verify real translation-unit instructions/full relocations, 6 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 351 further readable functions

Record precise original behavior and explicit resolution evidence beside three retained assembly functions. The Dynamics vector setter note separates established property writes/transforms from unknown property meanings, units and caller domains; its isolated readonly feasibility proof does not justify accepting three different stack homes. CARANIM records its actual SPARKS provider, four pointer slots, first-null acquisition and unconditional null-result store, with flag, vector and pointer-lifetime questions. PAUSE records signed node counts, twelve-byte descriptors, low-halfword selections and both callback-sensitive node reloads, with unknown historical layouts and valid domains. Independent complete-dump and relocation reviews rejected the C drafts. Only comments and line restoration are applied; every executable logical source coordinate and whole-source inverse is proved. No recovery or older-code cleanup is counted. Three original packed modules, a fresh full ROM, all source hashes and the generated uncertainty index remain mandatory.

Totals: 351 further recoveries after the 225 upstream ordinary imports, plus 1296 existing C semantic cleanups. Current ledger: 849 assembly references = 806 ordinary + 43 entrypoints; 753,228 known remaining instruction bytes; zero unknown sizes; 304 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1617-native-contract-unknowns` and `accepted-native-contract-unknowns` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 351 further readable functions

Make three previously unmarked caller-domain assumptions searchable in existing readable code. The AI lookup wraps its continuing index to sixteen bits while comparing it with a saved full signed count; record that original behavior separately from unknown allocation, count and termination domains. Its indexed getter similarly consumes a low-sixteen-bit index without establishing the count-backed allocation extent. The filename FourCC reader tests basename byte four before packing bytes zero through three; original producers and callers must establish readable storage, rather than assuming a valid-path guarantee. The original AI instruction review covers all196 bytes. No oversized-count reachability or player-visible bug is claimed. Only same-line comments change: all executable tokens, physical lines, logical coordinates and complete source inverses are proved. No recovery or older-code cleanup is counted. Both original packed modules, a fresh full ROM, all source hashes and the generated uncertainty index remain mandatory.

Totals: 351 further recoveries after the 225 upstream ordinary imports, plus 1296 existing C semantic cleanups. Current ledger: 849 assembly references = 806 ordinary + 43 entrypoints; 753,228 known remaining instruction bytes; zero unknown sizes; 304 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1624-lookup-path-unknowns` and `accepted-lookup-path-unknowns` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 352 further readable functions

Recover replayReadVersionTwoFile as readable named C with all336 original instruction bytes and all nine complete offset/type/symbol/value/addend relocation records equal; only serialization of intact HI/LO pairs differs. The original symbol separately includes eight bytes of proven alignment, while the actual C symbol is exactly336 bytes without trimming. Original GAME loader-return chains establish the shared MISC/SCENE dependencies, and original MISC/FILEROM/SCENE initializers and consumed instructions establish the actual file module, callbacks and scene data address. Preserve supplied file arguments, ignored read/close statuses, the uninitialized-before-read version byte, wrong-version close, count reloads after callbacks, low32-bit count scaling, exact block offsets and original ordering. Explicit unknown notes cover historical filename extent, complete state allocation/count domains, field/stream meanings, shared-state alias/lifetimes and no-write error reachability; no reachable bug is claimed. Natural128-byte scratch view matches original stack use and the paired writer, while the literal format establishes only42 required bytes. Require original packed REPLAY and all three providers, a fresh full ROM, every source hash and the generated uncertainty index.

Totals: 352 further recoveries after the 225 upstream ordinary imports, plus 1296 existing C semantic cleanups. Current ledger: 848 assembly references = 805 ordinary + 43 entrypoints; 752,892 known remaining instruction bytes; zero unknown sizes; 304 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1633-replay-version-two-reader` and `accepted-replay-version-two-reader` verify real translation-unit instructions/full relocations, 4 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 352 further readable functions

Improve five existing C routines with all684 instruction bytes and all20 complete ordered relocation records unchanged in isolated comparisons. Name the ROM file close export for its actual shared source-address clear, rather than an unsupported pending-flag interpretation; original open stores the loader result to that address and original reads use it as their source. Name the actual write-slot zero-return export while preserving the existing three u8 formal widths and flagging historical input/write contracts. Remove five genuinely unused sound declarations and name the used managed-slot local; all types, expressions, calls and source coordinates remain. Add searchable adjacent native-contract and matching-debt notes for the unaccepted ISCT3208 and AI5B4C drafts while keeping original ASM active. Replace the AI tail getter ownership promise with an explicit caller/teardown evidence requirement; original12-byte getter only returns the shared word. Do not count these three notes as recoveries or cleanup functions. Complete source inverse and every unaffected logical coordinate are checked before writes. No runtime fix, changed ABI or demonstrated player bug. Require all four original packed modules, a fresh original ROM, all source hashes and uncertainty index.

Totals: 352 further recoveries after the 225 upstream ordinary imports, plus 1301 existing C semantic cleanups. Current ledger: 848 assembly references = 805 ordinary + 43 entrypoints; 752,892 known remaining instruction bytes; zero unknown sizes; 303 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1650-older-file-sound-contracts` and `accepted-older-file-sound-contracts` verify real translation-unit instructions/full relocations, 4 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 352 further readable functions

Record54 focused older-code contract corrections and two additional native-contract/matching-debt notes, with searchable unknowns and the evidence needed to resolve them. Preserve established behavior and explicitly mark original scan-end writes, negative-only allocator-sentinel mismatch and terminal query-record initialization without claiming their player reachability. Correct the reversed dynamic-object conversion name: original QUAT provider reads matrices and writes quaternions; synchronize all nine identifiers in source, header, caller and maps. Represent original UVVL asset addresses as opaque testData pointers across all three VOLTEST wrappers, retaining original24-byte layout and helper ASM. Four older C cleanups preserve728 isolated instruction bytes and17 complete ordered relocation records; notes count as no recovery or cleanup function. Complete guarded definitions, full-source inverse and executable source coordinates are checked before writes. Retain unmatched intersection and AI assembly with adjacent contract/matching debt. No runtime fix or newly demonstrated player bug. Require every affected original packed module, fresh original ROM, all source hashes and index.

Totals: 352 further recoveries after the 225 upstream ordinary imports, plus 1305 existing C semantic cleanups. Current ledger: 848 assembly references = 805 ordinary + 43 entrypoints; 752,892 known remaining instruction bytes; zero unknown sizes; 303 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1681-contract-uncertainties` and `accepted-contract-uncertainties` verify real translation-unit instructions/full relocations, 27 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 352 further readable functions

Record 36 reviewed contract uncertainties across 20 older modules, correcting unsupported input, capacity, ownership and lifetime promises. Pak converters read every requested input byte even after the first zero; listener selection retains the nearest qualifying entry and earliest ties. Keep source-level graph initialization uncertainty distinct from a proved original runtime fault. Preserve the previously documented light sentinel behavior. Add one original-backed intersection assembly note: selected pointers are stored at native stack 0x8C+index*4, while compaction reads halfwords at 0x130; the first 1 through 41 sequential pointer stores do not reach that region, while the 42nd would overlap it. Scratch provenance, count domain, callback effects and actual caller reachability remain unresolved. No universally uninitialized-storage or player-visible bug claim and no runtime fix. Every note names the evidence required for resolution. No executable tokens, types, prototypes, names or behavior changed; whole-source inverse and all noncomment logical source coordinates are checked. These notes add no recovered functions or older-body cleanup count. Require all 21 affected original packed modules, fresh four-job original ROM, all frozen source hashes and the regenerated searchable uncertainty index before acceptance.

Totals: 352 further recoveries after the 225 upstream ordinary imports, plus 1305 existing C semantic cleanups. Current ledger: 848 assembly references = 805 ordinary + 43 entrypoints; 752,892 known remaining instruction bytes; zero unknown sizes; 303 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1689-remaining-contract-notes` and `accepted-remaining-contract-notes` verify real translation-unit instructions/full relocations, 21 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 353 further readable functions

Recover gameGuiApplyDitherAndVideoSettings as named commented C, preserving all380 original instruction bytes and all17 complete ordered relocation records. Original graphics-manager/state providers establish the display-list cursor and shared-word callbacks; original eight dither-table words and SDK feature constants establish literal operations. Preserve three display-list commands, callback-dependent settings reloads and native video flag order. Flag unresolved selector domains, cursor capacity/lifetime, shared-word bit meaning and historical unused callback declaration. Record two parked original-assembly contracts: AI dynamic-vector/matrix synchronization and callback-sensitive scalar refresh, with unresolved shared four-formal declaration and three prepared native arguments; and intersection signed columns with low16 selector, alias-sensitive stores, default normalization quirk and unchanged original readonly ownership. Failed drafts remain isolated and do not count as recoveries. Notes preserve executable tokens and every logical source coordinate; complete inverse checked. Require all affected original packed modules plus graphics providers, fresh four-job original ROM, every frozen source hash and regenerated uncertainty index.

Totals: 353 further recoveries after the 225 upstream ordinary imports, plus 1305 existing C semantic cleanups. Current ledger: 847 assembly references = 804 ordinary + 43 entrypoints; 752,512 known remaining instruction bytes; zero unknown sizes; 303 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1713-video-settings-and-recovery-notes` and `accepted-video-settings-and-recovery-notes` verify real translation-unit instructions/full relocations, 5 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 353 further readable functions

Record three original-backed assembly recovery contracts and refine the known role of a vehicle registry helper. The results routine retains ordered five-entry insertion and four-read/four-write name copying with its distinct native endpoint. The intersection selector retains the original flag-query order, scalar-only early return, tie/unordered predicates and output store order. The vehicle helper snapshots the object position before lighting callbacks and reloads shadow-dependent state afterward. Original DOBJ rejection can leave the matrix output unwritten; caller reachability remains unproved and no runtime fix is claimed. All three readable drafts remain unaccepted because complete native instruction or relocation comparisons differ. Unknown units, producer declarations, capacities, alias domains and storage lifetimes remain explicit with resolution evidence. Preserve all executable tokens and logical coordinates with whole-source inverse proof. No recovery or older-body cleanup totals change. Require all three affected packed original modules, fresh four-job original ROM, all frozen source hashes and regenerated uncertainty index before acceptance.

Totals: 353 further recoveries after the 225 upstream ordinary imports, plus 1305 existing C semantic cleanups. Current ledger: 847 assembly references = 804 ordinary + 43 entrypoints; 752,512 known remaining instruction bytes; zero unknown sizes; 303 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1730-native-recovery-contract-notes` and `accepted-native-recovery-contract-notes` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 353 further readable functions

Record six original-backed uncertainty notes across editor records, intersection results, vehicle model state and graphics texture replacement. Editor creation and reading preserve the original full-word minus-one check against zeroextended FFFF exhaustion, ignored file status and success-only destination progress. The editor mode branch can forward locally unwritten scratch; allowed mode reachability and actual GUI consumption remain unknown. Intersection results retain input-normal/fraction semantics, full-word/low-byte result gates, live output words and distinct rejection count publication. Vehicle model state retains ordered floating-point factor behavior, callback reloads and nested unchecked model access. Correct the graphics comment: the replacement ID is ORed unmasked into retained high bits, so caller ID guarantees remain explicit. All four readable drafts remain unaccepted after full native instruction and relocation comparisons. No reachable runtime fault is asserted or changed. Preserve all executable tokens and logical coordinates with whole-source inverse proof; no recovery or older-body cleanup totals change. Require all four affected packed original modules, fresh four-job original ROM, frozen source hashes and regenerated uncertainty index before acceptance.

Totals: 353 further recoveries after the 225 upstream ordinary imports, plus 1305 existing C semantic cleanups. Current ledger: 847 assembly references = 804 ordinary + 43 entrypoints; 752,512 known remaining instruction bytes; zero unknown sizes; 303 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1754-observed-contract-notes` and `accepted-observed-contract-notes` verify real translation-unit instructions/full relocations, 4 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 353 further readable functions

Clarify the older contour block reader input, current common block and last parsed contour with unchanged188 instruction bytes and all six complete ordered relocation records. Keep duplicate-block, allocation and inherited parser-state questions explicit. Record original-backed terrain draw and vehicle constructor contracts beside retained assembly; unmatched readable drafts remain isolated. Preserve executable logical coordinates and whole-source inverses. These notes distinguish original observations from unresolved runtime reachability; no new reachable bug or behavior fix is claimed. Require all affected packed modules, fresh four-job original ROM, every frozen source hash and regenerated uncertainty index before acceptance.

Totals: 353 further recoveries after the 225 upstream ordinary imports, plus 1306 existing C semantic cleanups. Current ledger: 847 assembly references = 804 ordinary + 43 entrypoints; 752,512 known remaining instruction bytes; zero unknown sizes; 303 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1776-contour-readability-notes` and `accepted-contour-readability-notes` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 354 further readable functions

Recover gameGuiAddRaceAndBattleControls as readable commented C with exact 476 original bytes and 30 complete relocation records at identical offsets, types, targets, values and addends. Only intact HI/LO pair serialization differs. Bind original player and AI counts and debug control words, retain both raw action addresses, original export reloads and reused widget output. Flag pool exhaustion reachability, exact 30-byte label reads versus historical object extents, storage lifetimes and unresolved property dispatch. Minimal observed export prefixes preserve native slots; no complete ownership or historical type claim. Require original GAMEGUI, GUI and MISC packed modules, fresh four-job original ROM, all frozen source hashes and regenerated uncertainty index before acceptance.

Totals: 354 further recoveries after the 225 upstream ordinary imports, plus 1306 existing C semantic cleanups. Current ledger: 846 assembly references = 803 ordinary + 43 entrypoints; 752,036 known remaining instruction bytes; zero unknown sizes; 303 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1802-race-battle-controls` and `accepted-race-battle-controls` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 354 further readable functions

Record seven original-backed uncertainty follow-ups across terrain draw dispatch, the older channel-to-terrain accessors, vehicle selection and matrix projection, and track-data interpolation. Keep native getter rejection/output behavior, old-table snapshots versus callback reloads, precise floating expression association and output store order explicit. The terrain accessors use unchecked channel indices; property-13 allocation, channel ranges and table lifetime still need producer and caller evidence. All nonmatching C drafts stay isolated and original assembly remains active. The sole grounded returned-handle refinement produces exactly the same failed instruction and full-reference sequences; no further shape variants are accepted. These observations do not establish reachable game bugs. No recovery or older-body cleanup totals change. Preserve executable tokens and every logical source coordinate, prove whole-source inverses, then require all three packed original modules, fresh four-job original ROM, every frozen source hash and regenerated uncertainty index before acceptance.

Totals: 354 further recoveries after the 225 upstream ordinary imports, plus 1306 existing C semantic cleanups. Current ledger: 846 assembly references = 803 ordinary + 43 entrypoints; 752,036 known remaining instruction bytes; zero unknown sizes; 303 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1836-original-contract-followups` and `accepted-original-contract-followups` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 354 further readable functions

Record six original-backed contract and uncertainty notes beside retained terrain, lighting and vehicle assembly. Document triangle-buffer store-before-capacity and inner-only stopping, hierarchy depth traversal and the conditional signed-halfword result read without inventing a default. Record actual environment triples and tagged lighting consumption, vehicle registry prefix exits, nested texture replacement and callback reload timing. Complete original/provider/draft instruction and reference audits found no supported further operation or ABI correction after the single grounded vehicle count/initialization refinement. All failed C drafts, types and prototype edits stay isolated. These observations do not establish reachable player faults. Recovery and older-body cleanup totals remain unchanged. Preserve executable tokens and every logical source coordinate, prove whole-source inverses, then require all three original packed modules, a fresh four-job original ROM, every frozen source hash and the regenerated uncertainty index before acceptance.

Totals: 354 further recoveries after the 225 upstream ordinary imports, plus 1306 existing C semantic cleanups. Current ledger: 846 assembly references = 803 ordinary + 43 entrypoints; 752,036 known remaining instruction bytes; zero unknown sizes; 303 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1858-terrain-light-vehicle-contracts` and `accepted-terrain-light-vehicle-contracts` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 354 further readable functions

Record six original-backed contract and uncertainty notes beside retained terrain, editor and vehicle assembly. Document two-point and point-scalar model-node queries, grid output and callback ordering, editor selected-segment query input uncertainty, and vehicle model-transition argument, resource and state reload contracts. Complete original/provider/draft instruction and reference audits preserve unresolved compile and calling-convention debt without inventing defaults, types or player-fault claims. Failed C drafts and prototype/caller edits remain isolated. Recovery and older-body cleanup totals remain unchanged. Preserve executable tokens and every logical source coordinate, prove whole-source inverses, then require all three original packed modules, a fresh four-job original ROM, every frozen source hash and the regenerated uncertainty index before acceptance.

Totals: 354 further recoveries after the 225 upstream ordinary imports, plus 1306 existing C semantic cleanups. Current ledger: 846 assembly references = 803 ordinary + 43 entrypoints; 752,036 known remaining instruction bytes; zero unknown sizes; 303 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1884-terrain-editor-transition-contracts` and `accepted-terrain-editor-transition-contracts` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 354 further readable functions

Record three original-backed matrix contract notes. Correct unsupported categorical caller ownership in matrix submission to an explicit lifetime and flag-domain uncertainty. Document terrain temporary fixed-matrix snapshots, halfword stores, live hierarchy/state reloads, ignored push failure and final restoration. Document vehicle scalar and matrix controls, conditional captured context and subsequent owner reload, first-index-only gating and unresolved domains. Full original/provider/draft instruction and reference audits keep both nonmatching C drafts isolated; high-level review does not prove exact floating or invalid-input behavior. Recovery and older-body cleanup totals remain unchanged. Preserve executable tokens and every logical source coordinate, prove whole-source inverses, then require all three original packed modules, a fresh four-job original ROM, every frozen source hash and the regenerated uncertainty index before acceptance.

Totals: 354 further recoveries after the 225 upstream ordinary imports, plus 1306 existing C semantic cleanups. Current ledger: 846 assembly references = 803 ordinary + 43 entrypoints; 752,036 known remaining instruction bytes; zero unknown sizes; 303 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1896-matrix-lifetime-control-contracts` and `accepted-matrix-lifetime-control-contracts` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 354 further readable functions

Record five original-backed producer, lighting and loader uncertainty notes. Confirm the contour parser conditional pointer initialization and unconditional publication without assuming zero-model asset validity or caller dereferences. Record initial zero object masks, exported whole-word/bit mutability and the observed four-byte field writer without a shared-layout or reachability claim. Close the original lighting cache-provider registration/load/store binding and preserve its nonmatching readable draft: seven frame/argument offsets remain despite exact property homes and ordered references. Flag the kernel current COMM scratch view versus observed original payload-copy extent; historical scratch declarations and input domains remain unresolved. No defaults, layout, padding, prototypes or executable behavior change. Recovery and older-body cleanup totals remain unchanged. Preserve executable tokens and every logical source coordinate, prove whole-source inverses, then require all three affected original packed modules, a fresh four-job original full ROM including the kernel, every frozen source hash and the regenerated uncertainty index before acceptance.

Totals: 354 further recoveries after the 225 upstream ordinary imports, plus 1306 existing C semantic cleanups. Current ledger: 846 assembly references = 803 ordinary + 43 entrypoints; 752,036 known remaining instruction bytes; zero unknown sizes; 303 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1905-producer-light-loader-contracts` and `accepted-producer-light-loader-contracts` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 354 further readable functions

Clarify six older C functions with all1,664 instruction bytes and75 complete ordered relocation records unchanged. Name the actual object-matrix source and destination, object/model/part variables and the sort-group/texture-sequence cleanup iterators. Remove five unused generated declarations while preserving executable line positions and existing comments. Count only four substantive naming cleanups; the two declaration-only cleanups do not increase the semantic-cleanup total. Flag original matrix-copy-before-check behavior and unresolved bounds, scale, aliasing and coordinate-frame contracts beside the two matrix functions. Preserve public names, ABI, types, reloads, call/unload order and whole-source inverses. Require all three affected original packed modules, fresh four-job original full ROM, every frozen source hash and the regenerated uncertainty index before acceptance.

Totals: 354 further recoveries after the 225 upstream ordinary imports, plus 1310 existing C semantic cleanups. Current ledger: 846 assembly references = 803 ordinary + 43 entrypoints; 752,036 known remaining instruction bytes; zero unknown sizes; 303 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1915-older-matrix-sort-sequence` and `accepted-older-matrix-sort-sequence` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 354 further readable functions

Record the original paired particle-position update contract beside retained assembly. Flag unknown scalar/mode policy, caller selection/handle/storage validity, matrix-output validity and callback ownership/lifetimes. Document the unordered comparison path and genuine unused transformed-point copy; particle final-interval timing is distinguished from freeing. The readable draft remains isolated: all1056 original and1056 candidate bytes and all46 ordered references were independently reviewed, but48 instruction words differ in frame/local homes, registers and argument/store scheduling. No unsupported source variants are banked. Preserve executable tokens, every logical coordinate and whole-source inverse; recovery totals remain unchanged. Require the original packed vehicle-animation module, fresh four-job original full ROM, all frozen source hashes and the regenerated uncertainty index before acceptance.

Totals: 354 further recoveries after the 225 upstream ordinary imports, plus 1310 existing C semantic cleanups. Current ledger: 846 assembly references = 803 ordinary + 43 entrypoints; 752,036 known remaining instruction bytes; zero unknown sizes; 303 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1916-paired-particle-contract` and `accepted-paired-particle-contract` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 354 further readable functions

Record original text-list allocation, exact fixed-length label copy and property-word forwarding beside retained assembly. Flag historical parent/shared-word types, label/pool extents, occupancy, alias/lifetime and action-dispatch ABI unknowns. Preserve allocator exhaustion behavior without asserting reachable invalid access. The readable draft remains isolated: all592 original and592 candidate bytes and all60 complete references were independently reviewed; only two shared-action stack-home offsets differ. Complete relocation multisets and intact HI/LO pairs agree, serialization order differs. No extra storage or padding is introduced to force a match. Preserve executable tokens, logical coordinates and source inverse. Require original packed GUI module, fresh four-job original ROM, frozen source hashes and regenerated uncertainty index.

Totals: 354 further recoveries after the 225 upstream ordinary imports, plus 1310 existing C semantic cleanups. Current ledger: 846 assembly references = 803 ordinary + 43 entrypoints; 752,036 known remaining instruction bytes; zero unknown sizes; 303 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1924-state-action-text-row-contract` and `accepted-state-action-text-row-contract` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 354 further readable functions

Clarify four older allocator and FORM file-reader functions while preserving all1168 instruction bytes and34 complete ordered relocation records. Name actual request/alignment/free-list, file-slot, payload-output and saved-cursor roles. Retain the original unused reader declaration because removal changes the size-sink stack address. Document unresolved heap/header/accounting, file/chunk/lifetime and occurrence contracts. Add six reviewed uncertainty refinements covering the camera pointer cell, bounded animation scalars, bound control construction, controller menu actions, the shared raw callback word and scalar intersection selection. Keep nonmatching C diagnostics isolated and original assembly active. Preserve logical source coordinates and exact source inverses. Require all three affected packed modules, a fresh four-job original full ROM, every frozen source hash and regenerated uncertainty index before acceptance.

Totals: 354 further recoveries after the 225 upstream ordinary imports, plus 1314 existing C semantic cleanups. Current ledger: 846 assembly references = 803 ordinary + 43 entrypoints; 752,036 known remaining instruction bytes; zero unknown sizes; 303 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1945-older-readable-uncertainty-ledger` and `accepted-older-readable-uncertainty-ledger` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 354 further readable functions

Document three original contracts beside retained assembly: fixed-address allocator interval reservation, variadic animation property dispatch and transformed-axis intersection results. Identify unresolved caller domains, widths, units, extents, aliases, resource lifetimes, original edge behavior and historical storage. Preserve native callback/store ordering and retain nonmatching readable drafts as isolated diagnostics. No new C recovery or older C cleanup is counted. Preserve all executable tokens and logical source coordinates with exact whole-source inverse proofs. Require both affected original packed modules, a fresh four-job full original ROM, every frozen source hash and the regenerated uncertainty index before acceptance.

Totals: 354 further recoveries after the 225 upstream ordinary imports, plus 1314 existing C semantic cleanups. Current ledger: 846 assembly references = 803 ordinary + 43 entrypoints; 752,036 known remaining instruction bytes; zero unknown sizes; 303 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1966-reservation-property-axis-contracts` and `accepted-reservation-property-axis-contracts` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 355 further readable functions

Recover uvIsectCollectRequestedProviderLists as readable commented C. Preserve 1484 original instruction bytes and all 34 complete relocation records; only enumeration of intact HI/LO pairs differs. Preserve flag1/8/2 provider order, optional word/scalar/vector copies, full-word object sentinel, byte snapshot and restoration, nonpositive count accumulation and final publication order. Bind focused export views to actual original provider initializers. Flag shared-ID dependency, output initialization, caller domains, capacities, aliases, lifetimes and reentrancy beside code. No invented storage or complete historical prototype claims. Require original ISCT, TERR and DOBJ packed modules, fresh four-job original ROM, all frozen source hashes and regenerated uncertainty index before acceptance.

Totals: 355 further recoveries after the 225 upstream ordinary imports, plus 1314 existing C semantic cleanups. Current ledger: 845 assembly references = 802 ordinary + 43 entrypoints; 750,552 known remaining instruction bytes; zero unknown sizes; 303 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1982-collected-provider-lists` and `accepted-collected-provider-lists` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 355 further readable functions

Record original four-slot animation effects and particle record acquisition beside retained assembly, and correct the older activation comment. The sound flag requests setup on next acquisition; the enabled byte is a nonzero gate while C0 is compared with2. Flag unresolved descriptor/source domains, original uninitialized fallback/style storage, unchecked matrix/normalization behavior, deliberate output aliasing, callback mutation and record/sound lifetimes. Compiler-local layout differences remain isolated diagnostics. No new C recovery or substantive older C cleanup is counted. Preserve all executable tokens/logical coordinates and exact complete-source inverse. Require both original packed modules, fresh four-job original ROM, all frozen source hashes and uncertainty index.

Totals: 355 further recoveries after the 225 upstream ordinary imports, plus 1314 existing C semantic cleanups. Current ledger: 845 assembly references = 802 ordinary + 43 entrypoints; 750,552 known remaining instruction bytes; zero unknown sizes; 303 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1991-particle-lifetime-contracts` and `accepted-particle-lifetime-contracts` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 356 further readable functions

Recover tedCreateTaskEditorGroupsAndDispatchSelector as readable commented C using the actual original GAME→GAMEGUI→GUI loader bindings, signed-low16 pool indices, shared pointer stores/reloads and original dispatch order. Preserve all480 resolved original instruction bytes and the original928-byte readonly section using the unchanged validated V1 ownership framework:788 retained prefix bytes,32 compiler switch-table bytes and108 retained suffix bytes attached to the real1716-byte following assembly routine. The original PC16 branch resolves to the same native destination; table ownership differs from raw isolated object records and is not described as serialization-only. Preserve all eight original RELA-backed table targets. Keep exact pool/title/selector/alias/lifecycle unknowns explicit. Full acceptance requires actual repeated extraction with identical generated outputs, original TED/GUI/GAMEGUI packed modules, a fresh four-job original full-ROM build, all frozen source hashes and the regenerated uncertainty index. No padding, manual table masking, invented host or C body shape change.

Totals: 356 further recoveries after the 225 upstream ordinary imports, plus 1314 existing C semantic cleanups. Current ledger: 844 assembly references = 801 ordinary + 43 entrypoints; 750,072 known remaining instruction bytes; zero unknown sizes; 303 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `1993-ted-native-readonly-groups` and `accepted-ted-native-readonly-groups` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 356 further readable functions

Document original pending query refresh, filtered model selection and mode-dependent scalar blending beside their retained assembly. Flag conditional unassigned storage, callback-dependent object flag restoration, cached flag-4 reuse, low-16-bit retry/iteration, unchecked capacities and divisor domains. Compiler frame, register and relocation differences remain isolated diagnostics; no draft types or bodies are accepted. Preserve every executable token and logical coordinate, exact complete-source inverse, original packed modules and a fresh original ROM build. No C recovery or older C cleanup count is added; require all frozen source hashes and uncertainty index.

Totals: 356 further recoveries after the 225 upstream ordinary imports, plus 1314 existing C semantic cleanups. Current ledger: 844 assembly references = 801 ordinary + 43 entrypoints; 750,072 known remaining instruction bytes; zero unknown sizes; 303 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2012-query-and-motion-contracts` and `accepted-query-and-motion-contracts` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 356 further readable functions

Clarify three older kernel functions without changing their public names, types, expressions, layout or behavior. Name the actual source/destination byte cursors, transfer alignment, integer-read scratch and clock contributions. Preserve all 1,056 instruction bytes and complete ordered relocation records. Replace speculative device-fault prose with the actual original stores to addresses 1 and 2; flag the equality-only leading-count subtraction, signed high-word byte promotion and unresolved caller/device/overlap/calibration domains. Attach the reviewed selector-reset contract and original 30-byte label-copy uncertainty before retained TED assembly. Keep its nonmatching C draft isolated and do not count an assembly recovery. Preserve complete source inverses and every executable logical source coordinate. Require original packed TED, a fresh full kernel/ROM build, all frozen sources and uncertainty-index freshness before acceptance.

Totals: 356 further recoveries after the 225 upstream ordinary imports, plus 1317 existing C semantic cleanups. Current ledger: 844 assembly references = 801 ordinary + 43 entrypoints; 750,072 known remaining instruction bytes; zero unknown sizes; 303 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2024-older-memory-clock-contracts` and `accepted-older-memory-clock-contracts` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 356 further readable functions

Clarify one existing texture-animation variadic property function. Rename generated parameter/local roles and expose uvTexAnimSetTaggedProperties consistently in its source, public export member, initializer references and linker metadata. Preserve all 764 original instruction bytes, all four complete ordered relocation records, the existing 48-byte readonly section and seven native tag targets. Keep the original pointer-typed selector read and public variadic ABI, ordered floating comparisons, double-to-float conversions, byte truncation and write sequence; flag historical selector type, record/argument domains, coordinate units and caller termination as unresolved. The module already owns text/data/rodata/bss in C, so extraction and readonly ownership configuration stay unchanged. Require fresh extraction, original packed module equality, full original ROM, complete frozen source hashes and regenerated uncertainty index before acceptance.

Totals: 356 further recoveries after the 225 upstream ordinary imports, plus 1318 existing C semantic cleanups. Current ledger: 844 assembly references = 801 ordinary + 43 entrypoints; 750,072 known remaining instruction bytes; zero unknown sizes; 302 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2030-texanim-tagged-readability` and `accepted-texanim-tagged-readability` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 356 further readable functions

Clarify the two older system-property setter/getter functions while preserving all 136 original instruction bytes and four complete ordered relocation records. Name actual property IDs and the argument cursor; correct the misleading value/array-limit comment without changing the signed upper-ID check, zero sentinel, unchecked lower/getter indexing, backing-array count, pointer return or variadic word ABI. Keep caller domains, stored value kinds, object extents and lifetimes explicit. Add four reviewed original-contract notes beside retained RACE, Motion, intersection and AI assembly: player-gate summaries, curve/scalar output pairs, plane/box-edge selection and vector/graph response. Preserve actual quirks and unresolved floating, initialization, alias, bounds and historical-storage evidence; do not bank failed C drafts or count recoveries. Preserve whole-source inverses and every executable logical coordinate. Require all affected packed modules, a fresh original kernel/ROM, every frozen source hash and uncertainty-index freshness.

Totals: 356 further recoveries after the 225 upstream ordinary imports, plus 1320 existing C semantic cleanups. Current ledger: 844 assembly references = 801 ordinary + 43 entrypoints; 750,072 known remaining instruction bytes; zero unknown sizes; 302 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2037-system-property-native-contracts` and `accepted-system-property-native-contracts` verify real translation-unit instructions/full relocations, 4 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 356 further readable functions

Add five reviewed native-contract and uncertainty notes beside retained original assembly: particle COMMON setup, the Dynamics secondary selector, Motion acquisition callbacks and two task-editor record/query routines. Record observed callback order, mutable count and pointer reloads, original count/sentinel/read-status behavior, unresolved stack provenance, field meanings, storage and lifetimes, with evidence needed to resolve each. Keep unmatched readable reconstructions outside accepted source; document complete trial differences without invented local padding or initialized defaults. Preserve whole-source byte inverses and every executable logical coordinate. Counts remain 356 recoveries and 1320 older cleanups. Require all four affected original packed modules, a fresh full original ROM, every frozen source hash and uncertainty-index freshness.

Totals: 356 further recoveries after the 225 upstream ordinary imports, plus 1320 existing C semantic cleanups. Current ledger: 844 assembly references = 801 ordinary + 43 entrypoints; 750,072 known remaining instruction bytes; zero unknown sizes; 302 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2062-native-contract-notes-2062` and `accepted-native-contract-notes-2062` verify real translation-unit instructions/full relocations, 4 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 356 further readable functions

Add two reviewed original-assembly contract notes for Motion sample queries and the task-editor second record loader, plus a precise correction of a prior false DATA section claim to Global values. Record actual operation order, count/sentinel/read-status behavior and unresolved storage, alias, callback, resource and lifetime contracts. Preserve every executable logical coordinate and whole-source byte inverse. Unmatched readable C stays diagnostic. Counts remain 356 recoveries and 1320 older cleanups. Require both affected packed original modules, a fresh full original ROM, all 1031 frozen source hashes and uncertainty-index freshness before acceptance.

Totals: 356 further recoveries after the 225 upstream ordinary imports, plus 1320 existing C semantic cleanups. Current ledger: 844 assembly references = 801 ordinary + 43 entrypoints; 750,072 known remaining instruction bytes; zero unknown sizes; 302 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2086-native-query-record-notes-2086` and `accepted-native-query-record-notes-2086` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 356 further readable functions

Add two reviewed original-assembly contract notes for car-audio material classification and model COMM parsing. Preserve original material-code priority and duplicate tests, observed parser storage and header-copy behavior, provider word consumption and unresolved caller, count, capacity, allocation, alias and resource lifetimes. Leave failed C drafts outside accepted source. Preserve every executable logical coordinate and exact source inverse. Counts stay 356 recoveries and 1320 older cleanups. Require both packed original modules, a fresh original ROM, all 1031 frozen source hashes and uncertainty-index freshness before acceptance.

Totals: 356 further recoveries after the 225 upstream ordinary imports, plus 1320 existing C semantic cleanups. Current ledger: 844 assembly references = 801 ordinary + 43 entrypoints; 750,072 known remaining instruction bytes; zero unknown sizes; 302 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2093-native-audio-model-contract-notes-2093` and `accepted-native-audio-model-contract-notes-2093` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 357 further readable functions

Recover pauseCycleByteOnNewHorizontalAction from the actual original MENU callback and loader chain, preserving unsigned byte loads, signed full-word bounds, low-byte writes and the common action-word store. Preserve all eight complete relocation records and prove native serialization through existing unchanged offset-order metadata. Name genuine parameter/local roles in uvFxProps and uvFxModel while retaining all 1128 instruction bytes, complete ordered records, physical source widths, selectors, NaN-sensitive comparisons and modification-on-failure behavior. Preserve exact source inverses and existing FX logical coordinates. Require full original PAUSE/MENUSLCT/UVFX packed equality, a fresh full original ROM, all frozen source hashes and uncertainty-index freshness before acceptance. No padding, guessed layouts, source-shape variants or readonly ownership changes.

Totals: 357 further recoveries after the 225 upstream ordinary imports, plus 1322 existing C semantic cleanups. Current ledger: 843 assembly references = 800 ordinary + 43 entrypoints; 749,896 known remaining instruction bytes; zero unknown sizes; 302 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2100-pause-fx-readable-contracts-2100` and `accepted-pause-fx-readable-contracts-2100` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 357 further readable functions

Clarify three existing texture functions, including the descriptive uvTextureApplyPackedState name and its current references. Preserve low-12-bit IDs, first-record read before the later null gate, the original OR-with-0x40000 combine behavior, palette and alpha state, two cache stores, repeated output-head reloads and ordered variadic outputs. Preserve exactly 1728 instruction bytes and all 44 ordered relocation records. Add one root-reviewed original-assembly AI contract note without accepting the nonmatching draft. Explicitly invert only the existing bank helper normalization of the one four-space blank line after uvTextureGetProps va_start. Preserve every executable logical source coordinate, exact whole-source inverses and the exact known semantic alias append. Counts357 recoveries/1325 older cleanups; no new ASM recovery. Require full original packed AI/UVTEXTURE modules, fresh original ROM, all frozen source hashes and uncertainty-index freshness before acceptance.

Totals: 357 further recoveries after the 225 upstream ordinary imports, plus 1325 existing C semantic cleanups. Current ledger: 843 assembly references = 800 ordinary + 43 entrypoints; 749,896 known remaining instruction bytes; zero unknown sizes; 301 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2108-texture-ai-readable-contracts-2108` and `accepted-texture-ai-readable-contracts-2108` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 358 further readable functions

Recover Motion11BB4 as motionQueryHasNonExcludedKind using original lowercase isct and scen loader bindings and actual query/texture provider instructions. Ground the 88-byte result span in original copier4200 rather than unused stack space. Preserve signed scene byte promotion, second callback provider/global reloads, kind reclassification and u16 return flag. One reversal of the two real local declarations matches every original instruction; historical lexical declaration order remains unknown. Object relocation enumeration swaps two complete kernel-global HI/LO pairs, but all eight full records/sites match, actual native target serialized RELA and existing order metadata are empty in this range, and no packaging metadata is changed. Require full original packed Motion equality, fresh original ROM, all frozen source hashes and uncertainty-index freshness before acceptance. Counts358 recoveries/1325 existing cleanups; remaining known code749720bytes.

Totals: 358 further recoveries after the 225 upstream ordinary imports, plus 1325 existing C semantic cleanups. Current ledger: 842 assembly references = 799 ordinary + 43 entrypoints; 749,720 known remaining instruction bytes; zero unknown sizes; 301 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2115-motion-collision-readable-recovery-2115` and `accepted-motion-collision-readable-recovery-2115` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 358 further readable functions

Clarify dynamic geometry descriptor storage, display-list heads, polygon range and batching roles. Preserve raw forwarded words, minimum-count rejection, original descriptor initialization, vertex commands, repeated cursor reloads and original range overrides. Preserve all 860 instruction bytes and 34 complete ordered relocation records. Correct the inaccurate callback-export type label and document original signed vertex append limit/count behavior without a repair or reachable-overrun claim. Retain inherited outer prefix/pad roles as unknown and preserve all executable logical source coordinates, including explicit resumes181/196/397. Count two new older C cleanups, with the grid already counted in historical562. No new recovery, storage/ABI changes or readonly migration. Require original packed modules, fresh original ROM, all frozen sources and uncertainty-index freshness before acceptance.

Totals: 358 further recoveries after the 225 upstream ordinary imports, plus 1327 existing C semantic cleanups. Current ledger: 842 assembly references = 799 ordinary + 43 entrypoints; 749,720 known remaining instruction bytes; zero unknown sizes; 301 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2129-older-geometry-readable-contracts-2129` and `accepted-older-geometry-readable-contracts-2129` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 358 further readable functions

Clarify original banked and wide-grid dimension, closure, vertex cursor and command-index roles. Preserve every expression, declaration type/order, unused local, inherited pad, backslash continuation and display-list reload. Keep the original full-word dimension comparison, signed-halfword and byte narrowing, full-valued extra row-pair input and signed modulo/index behavior. Two new older C cleanups; no new recovery or type/readonly changes. Add three separately approved pure native-ASM notes for audio handle matching and Scene row/weather callback contracts. Preserve whole-source byte inverse and all executable logical coordinates, with grid resumes208/299. Require original packed GEOM/Audio/Scene modules, fresh original ROM, all frozen sources and uncertainty-index freshness before acceptance.

Totals: 358 further recoveries after the 225 upstream ordinary imports, plus 1329 existing C semantic cleanups. Current ledger: 842 assembly references = 799 ordinary + 43 entrypoints; 749,720 known remaining instruction bytes; zero unknown sizes; 301 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2140-older-grid-readable-contracts-2140` and `accepted-older-grid-readable-contracts-2140` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 359 further readable functions

Recover Battle4580 as battleCollectModelVertexHandlesAndScaledZ from original VATR and SND bindings and actual native providers. Preserve double promotion consumed as 32-bit tuples, selected signed third-coordinate division by 100, query saturation and all callback/global/count reloads. One reversal of two genuine locals reproduces all 69 original instructions. All six full object records match; the two local pairs exchange enumeration order but existing four native serialized site-order rows already specify the original order. Regenerate extraction before the full build so ASM callers use the canonical name. No packaging metadata edits. Require complete original packed Battle equality, fresh original ROM, frozen source hashes and current uncertainty index before acceptance. Counts359 recoveries/1329 existing cleanups; remaining known code749444 bytes.

Totals: 359 further recoveries after the 225 upstream ordinary imports, plus 1329 existing C semantic cleanups. Current ledger: 841 assembly references = 798 ordinary + 43 entrypoints; 749,444 known remaining instruction bytes; zero unknown sizes; 301 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2146-battle-vertex-readable-recovery-2146` and `accepted-battle-vertex-readable-recovery-2146` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 359 further readable functions

Clarify original triangle-strip batching, retained two-vertex overlap, phased signed-halfword batch count and triangle order alternation across batches. Preserve every body operation, type/order and cursor/descriptor access. Replace the incorrectly attributed graphics-manager export-pointer declaration at native1754 with the observed Gfx buffer-base view; actual GMGR imports remain at1758. Preserve the raw settings word and original cast/allocation/free behavior, with historical source type and caller-supplied capacity/lifetime explicitly unresolved. Keep the approved SceneCB8 original assembly and precise native provider/unknown-domain note. One older cleanup, one declaration correction(count0), one pure note; no recovery, public ABI, layout or readonly migration. Preserve raw inverse and executable logical coordinates with strip resume136. Require complete original packed GEOM/Scene, fresh original ROM, all frozen sources and uncertainty index before acceptance.

Totals: 359 further recoveries after the 225 upstream ordinary imports, plus 1330 existing C semantic cleanups. Current ledger: 841 assembly references = 798 ordinary + 43 entrypoints; 749,444 known remaining instruction bytes; zero unknown sizes; 301 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2156-older-geometry-strip-buffer-contracts-2156` and `accepted-older-geometry-strip-buffer-contracts-2156` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 361 further readable functions

Recover Battle4438 as battleInitializeNodeAndCollectVertexHandles and Battle6804 as battleResetNodePlaySoundAndClearObjectFlags. The original node initializer resets observed fields and both sound handles, clears thirty words, calls the accepted vertex collector, then reloads the current model. The sound reset preserves shared save/count/scalar effects, matrix query, returned sound volume, sound request and flag clears. All 145 original instructions and complete ordered object records match. Keep focused layouts neutral and searchable RE_UNKNOWN caller/allocation/alias/lifetime notes. Existing relocation metadata stays unchanged; regenerate extraction before build so original ASM references use canonical names. Require complete original packed Battle equality, fresh original ROM, frozen source hashes and uncertainty index before acceptance. Counts361 recoveries/1330 existing cleanups; remaining known code748864 bytes.

Totals: 361 further recoveries after the 225 upstream ordinary imports, plus 1330 existing C semantic cleanups. Current ledger: 839 assembly references = 796 ordinary + 43 entrypoints; 748,864 known remaining instruction bytes; zero unknown sizes; 301 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2168-battle-reset-initializer-recoveries-2168` and `accepted-battle-reset-initializer-recoveries-2168` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Current accepted checkpoint — 361 further readable functions

Rename the four rectangle input words as neutral first/second X/Y components and its display-list cursor local. Preserve original independent Y transformations, signed lower/upper checks, repeated GMGR callbacks, all seven display-list commands and every cursor reload/store. Original GEOM/GMGR initializers and providers establish the actual bindings without inferring units, ordered corners, positive dimensions or caller capacity/alias/lifetime guarantees. Keep original LIGHT5AC assembly and its reviewed provider/radius/weight/unknown-domain note; no rejected C, types or ABI are accepted. One older C cleanup, one pure note, no recovery or readonly ownership change. Exact whole-source inverse and executable logical coordinates, rectangle resume351 and LIGHT pragma logical20, are prewrite gates. Require complete original packed GEOM/Light, fresh original ROM, all frozen sources and uncertainty index before acceptance.

Totals: 361 further recoveries after the 225 upstream ordinary imports, plus 1331 existing C semantic cleanups. Current ledger: 839 assembly references = 796 ordinary + 43 entrypoints; 748,864 known remaining instruction bytes; zero unknown sizes; 301 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2178-older-rectangle-light-contracts-2178` and `accepted-older-rectangle-light-contracts-2178` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.
