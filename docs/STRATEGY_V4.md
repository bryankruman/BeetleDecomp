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
matching C are preserved with `#line`. The current ledger has **714** assembly references:
**677** ordinary functions and **37** entrypoints, with **664,628** known instruction bytes
and no unknown sizes. The broader name audit still finds **290** address-named C definitions.
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
CPU threads, 8 GiB RAM, 48 GiB disk and no autostart. Existing guests and hypervisor packages
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

* **OC15 — Dormant GUI relocation-padding rejection.**
  The original GUI module declares a 2,392-byte RELA payload. Its COMM header declares 597 records, which consume 2,388 bytes, followed by exactly four zero bytes at the module end. The existing `moduleFileDisasm.scanRela` equality check requires `relaSize == relocCount * 4` and would reject that original padded payload. The audited extraction path has zero calls to `scanRela`, so this is dormant tool debt rather than a current GUI extraction blocker. No relocation bytes are discarded, rewritten or guessed, and no parser patch is included in the GUI integration.
  * **A (recommended):** Preserve the current extraction path and this evidence. If `scanRela` becomes active, add narrowly format-aware padding support with fixtures requiring the documented count, exact declared extent, zero padding and complete native relocation equality.
    *Impact:* Keeps the matching GUI integration independent of an unused parser change and makes a later parser activation auditable.
  * **B:** Leave the parser unchanged when activating it and diagnose the expected rejection then.
    *Impact:* Retains the confirmed rejection of this original padded module and delays the format check until a future tool change.

Evidence: `gui-dormant-relocation-parser-path-audit-2316.json` SHA-256 `4a8083903bab3b85bb01458f740732ac959c336066255d4d34ff0c8d10712afd`; `gui-observed-exports-complete-operand-proof-2324.json` SHA-256 `3bef5916f2d8ac4a43ec0bf186f52f1b990b964bc919c684b13442e9b8befaa7`. The original RELA header is at packed offset 28,568; the payload count and final four zero bytes are independently checked against the original packed module. Tool pins: `tools/moduleExtract.py` SHA-256 `7f5eaee16cb5abafd3bdd1e59e95c01eed81ea6074eb86f10dd73828c8d6560a`; `tools/moduleFileDisasm.py` SHA-256 `afc8ea3e55325a3da45b072138231ab26bb41adf52b566751e878df4004b960d`. Existing OC14 concerns the environment assignment boundary and does not cover this parser finding.


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


## Historical accepted checkpoint — 361 further readable functions

Rename the four rectangle input words as neutral first/second X/Y components and its display-list cursor local. Preserve original independent Y transformations, signed lower/upper checks, repeated GMGR callbacks, all seven display-list commands and every cursor reload/store. Original GEOM/GMGR initializers and providers establish the actual bindings without inferring units, ordered corners, positive dimensions or caller capacity/alias/lifetime guarantees. Keep original LIGHT5AC assembly and its reviewed provider/radius/weight/unknown-domain note; no rejected C, types or ABI are accepted. One older C cleanup, one pure note, no recovery or readonly ownership change. Exact whole-source inverse and executable logical coordinates, rectangle resume351 and LIGHT pragma logical20, are prewrite gates. Require complete original packed GEOM/Light, fresh original ROM, all frozen sources and uncertainty index before acceptance.

Totals: 361 further recoveries after the 225 upstream ordinary imports, plus 1331 existing C semantic cleanups. Current ledger: 839 assembly references = 796 ordinary + 43 entrypoints; 748,864 known remaining instruction bytes; zero unknown sizes; 301 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2178-older-rectangle-light-contracts-2178` and `accepted-older-rectangle-light-contracts-2178` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 361 further readable functions

Name the reciprocal matrix copy uvMat4CopyWithReciprocalAndLinearScale and the three sine/cosine construction uvMat4SetRotationFromThreeAngles. Preserve original interleaved reads/stores, f32 grouping, exact-zero callback suppression, shared-handle reloads, third-zero product assignments and both inherited no-op source scaffolds. Native FMTX/MATH initializers and complete providers establish the actual exports without inventing axis/angle conventions, nonzero divisors, finite ranges or valid caller aliases/storage/lifetimes. Two older cleanups, zero recoveries and no ABI/type/readonly changes. All global source/header/linker references and exact native aliases are inverted before writes, with original executable logical coordinates/resumes 695 and 1002 retained. Regenerate extraction before build so derived references use canonical names; require original packed FMTX and QUAT, fresh original ROM, frozen sources and uncertainty index before acceptance.

Totals: 361 further recoveries after the 225 upstream ordinary imports, plus 1333 existing C semantic cleanups. Current ledger: 839 assembly references = 796 ordinary + 43 entrypoints; 748,864 known remaining instruction bytes; zero unknown sizes; 299 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2187-older-matrix-parameters-contracts-2187` and `accepted-older-matrix-parameters-contracts-2187` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 362 further readable functions

Recover Motion12CF0 as motionUpdateModeGatedProperties. Preserve ordered double comparison, byte-mode store/narrowing and post-callback reload, dynamic record update, CARANIM/CAM tagged calls and final existing state helper. All 85 native words and 13 complete relocation records match as multisets; raw HI/LO enumeration differs and existing native order metadata remains unchanged. The promoted s32 snapshot reproduces zero-extended byte values; historical lexical local type/order remains unknown. Regenerate extraction before full build. Require original packed Motion, fresh original ROM, frozen source hashes and uncertainty index. Counts 362 recoveries/1333 existing cleanups; known remaining code 748524 bytes.

Totals: 362 further recoveries after the 225 upstream ordinary imports, plus 1333 existing C semantic cleanups. Current ledger: 838 assembly references = 795 ordinary + 43 entrypoints; 748,524 known remaining instruction bytes; zero unknown sizes; 299 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2206-motion-mode-property-recovery-2206` and `accepted-motion-mode-property-recovery-2206` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 362 further readable functions

Rename only matrix-wrapper parameters and locals; preserve by-value64-byte fixed matrices, low16flags, shared-matrix operation order and ignored rejection returns. Actual FMTX/IMTX initializers and complete providers establish bindings without assuming valid input ranges, indices/capacity, aliases/lifetimes, historical flags or error expectations. Keep TED selected-record refresh in original ASM; document observed index/read/default/callback behavior, unknown caller domains and unresolved instruction/readonly differences. Two older cleanups, zero recoveries and one pure note; no alias/ABI/type/readonly changes. Raw whole-source inverse and all executable logical coordinates pass before writes. Require both original packed modules, fresh original ROM,1031source hashes and uncertainty index before acceptance.

Totals: 362 further recoveries after the 225 upstream ordinary imports, plus 1335 existing C semantic cleanups. Current ledger: 838 assembly references = 795 ordinary + 43 entrypoints; 748,524 known remaining instruction bytes; zero unknown sizes; 299 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2210-older-matrix-forwarding-contracts-2210` and `accepted-older-matrix-forwarding-contracts-2210` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 363 further readable functions

Recover Motion12F38 as motionApplyPropertyAndRumbleSequence: preserve all 107 original instruction words and all 20 ordered object relocation records, six original serialized relocations and existing order rows. Preserve captured-context versus later context reload, native callback widths, three rumble merges, CAM/CAR tagged inputs and the DATA vector/PIECE handoff. Keep historical source types, IDs, units, module availability, allocation and lifetime unknowns explicit. Include only the reviewed pure PAUSE Continue/Joker native-contract note; its original ASM remains. All untouched executable and pragma logical coordinates are preserved. Regenerate extraction before full build. Require original packed Motion and PAUSE, fresh original ROM, all frozen source hashes, uncertainty index and complete worker ledger with exactly 837 ordered remaining identities and 748096 positive known bytes. No local missing-ASM sizes are used.

Totals: 363 further recoveries after the 225 upstream ordinary imports, plus 1335 existing C semantic cleanups. Current ledger: 837 assembly references = 794 ordinary + 43 entrypoints; 748,096 known remaining instruction bytes; zero unknown sizes; 299 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2223-motion-property-sequence-recovery-2223` and `accepted-motion-property-sequence-recovery-2223` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 363 further readable functions

Name one existing C function uvIntersectCopySignedMatrixRowVector and clarify only its parameter/local roles. Preserve signed low 16-bit selectors, negative-row negation, no-write selectors, interleaved component loads/stores and inherited FAKE scaffold. Keep unknown caller domains, spans, aliases/lifetimes and coordinate conventions explicit. Rename all source/header/linker references and add the exact native alias at 0x004020A0. Correct the FontMessage size comment to native 124-byte stride; separately document original source[49] truncation/count 50, terminator/font-pointer write overlap and unresolved input/caller/queue/consumer contracts without inventing a reachable bug. One older cleanup, zero recoveries, two pure notes; no ABI/types/operations/readonly ownership change. All six raw inverses, member selectors and executable logical coordinates pass before writes. Native sizes come only from the accepted worker after all 837 ordered identities match; local missing ASM sizes remain null. Regenerate extraction, then require all three original packed modules, fresh original ROM, 1031 source hashes, full ledger and uncertainty index before acceptance.

Totals: 363 further recoveries after the 225 upstream ordinary imports, plus 1336 existing C semantic cleanups. Current ledger: 837 assembly references = 794 ordinary + 43 entrypoints; 748,096 known remaining instruction bytes; zero unknown sizes; 298 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2230-older-intersection-font-contracts-2230` and `accepted-older-intersection-font-contracts-2230` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 363 further readable functions

Rename only existing scalar-helper parameters and locals using original matrix-translation, endpoint and extent inputs. Preserve raw dot-derived arithmetic, all f32 grouping/comparisons, early exits and repeated provider handle loads. Retain the address name while normalization, units, finite/degenerate input domains and geometric intent remain unresolved. Add pure notes before unchanged Motion 9734, Motion 3C04 and PAUSE 423C pragmas; preserve original logical coordinates and qualify original conversion/formatting/storage observations without claiming reachable faults. One older cleanup, zero recoveries, three pure notes; no aliases, public ABI, types, executable behavior or readonly ownership changes. Complete original instructions/full ordered records, exact whole-source inverses, member selectors and all executable coordinates pass before writes. Accepted worker sizes are used only after all 837 function identities/data/address names match; local missing sizes remain null. Fresh original packed INTERSECT/MOTION/PAUSE modules, fresh original ROM, 1031 frozen source hashes, complete ledger and uncertainty index are mandatory before acceptance.

Totals: 363 further recoveries after the 225 upstream ordinary imports, plus 1337 existing C semantic cleanups. Current ledger: 837 assembly references = 794 ordinary + 43 entrypoints; 748,096 known remaining instruction bytes; zero unknown sizes; 298 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2250-older-scalar-motion-pause-contracts-2250` and `accepted-older-scalar-motion-pause-contracts-2250` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 363 further readable functions

Add pure searchable native-contract, unresolved-storage and compiler-difference notes before unchanged Motion 39BC and MED 2920 assembly pragmas. Preserve all executable logical coordinates; neither readable draft is accepted and no recovery or cleanup credit is added. Fix moduleCompare DATA selection to use each file's DATA extent and text-plus-RO offset. The focused isolated-worker regression rejects the original DATA-start assertion and passes both corrected DATA boundaries and unchanged RODATA selection with unequal section lengths. Preserve every other tool expression. Full original packed MOTION/MED equality, a fresh four-job original-ROM build, all1031 frozen source hashes, full remaining ledger/data/address-name rows and regenerated uncertainty index remain mandatory. GUI upstream integration is still under independent original-native review.

Totals: 363 further recoveries after the 225 upstream ordinary imports, plus 1337 existing C semantic cleanups. Current ledger: 837 assembly references = 794 ordinary + 43 entrypoints; 748,096 known remaining instruction bytes; zero unknown sizes; 298 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2263-retained-contracts-and-data-tool-2263` and `accepted-retained-contracts-and-data-tool-2263` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 364 further readable functions

Recover GAME 0C08 as gameDrawProfilerLabelRows with twelve explicit original label/ID/y calls and fresh shared-provider loads. All424 instruction bytes and all50 full relocation records at their original sites agree; only ELF label/ID pair-group record order differs. Actual original MISC slotFC initialization and body establish consumed label/signed-ID/signed-y arguments and original label bytes, without inventing full historical declarations or scratch capacity. Document dependency, profiler-ID and callback lifetime uncertainty beside the source. Add a pure searchable note before unchanged Motion F54 assembly, preserving all executable logical coordinates and recording its952-byte/170-word mismatch, exact by-value vector dispatch evidence and unknown ownership/domains/units/lifetimes; no motion C/types/prototypes or motion recovery credit. Original full packed GAME/MOTION including native relocation order, fresh four-job original-ROM build, all1031 source hashes, full remaining/data/address-name ledger and uncertainty-index validation remain mandatory. GUI upstream integration remains under independent native review.

Totals: 364 further recoveries after the 225 upstream ordinary imports, plus 1337 existing C semantic cleanups. Current ledger: 836 assembly references = 793 ordinary + 43 entrypoints; 747,672 known remaining instruction bytes; zero unknown sizes; 298 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2278-game-profiler-and-motion-note-2278` and `accepted-game-profiler-and-motion-note-2278` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 366 further readable functions

Recover Motion 61FC and6478 as motionCallScalarHelperWithThreeTransforms and motionBuildBasisAndCallScalarHelper. All1256 instruction bytes and42 full ordered object relocation records match without trimming or metadata changes. Preserve actual shared matrix/vector storage, original temporary placement, ordered threshold/cross products, ignored zero-length normalization returns, separate original constants and signed16 conversions. Names state observed operations; physical purpose, domains, ownership, frames and historical declarations remain searchable RE_UNKNOWN contracts. Add a pure note before unchanged GAME1338 assembly documenting actual indexed-module/provider/shared-word effects and unresolved bounds, aliases and lifetimes. Its552/564-byte C drafts remain parked against560 native bytes; no GAME C/types/prototypes or recovery credit. Original packed GAME/MOTION including native order, a fresh four-job original-ROM build, all1031 source hashes, full remaining/data/address-name ledger and uncertainty index remain mandatory acceptance gates. Upstream GUI remains independently reviewed.

Totals: 366 further recoveries after the 225 upstream ordinary imports, plus 1337 existing C semantic cleanups. Current ledger: 834 assembly references = 791 ordinary + 43 entrypoints; 746,416 known remaining instruction bytes; zero unknown sizes; 298 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2316-motion-draw-pair-and-game-note-2316` and `accepted-motion-draw-pair-and-game-note-2316` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 367 further readable functions

Recover Selection1BF4 as selectionApplyLatchedMenuActionWords with grounded minimum12-byte node and MENU08 call views, leaving existing shared storage declarations unchanged. All272 instruction bytes and32full object records match bysite; only firstfour HI/LO pair-group emission order differs. Native order must remain exact through existing serialization metadata. Preserve two numeric action latches, fresh node reload, early return before byte-zero reset, signed unchecked table index and original store order. Searchable unknowns record complete declarations, ownership, table capacity/index domain, callback consumers and reset/dependency lifetimes; unchecked original paths are identified without claiming reachable player faults. Original packed Selection, fresh four-job original-ROM build, allsource hashes and complete remaining/data/address-name ledger and uncertainty index are required before acceptance. Existing compiler warnings elsewhere in Selection remain separate audit debt.

Totals: 367 further recoveries after the 225 upstream ordinary imports, plus 1337 existing C semantic cleanups. Current ledger: 833 assembly references = 790 ordinary + 43 entrypoints; 746,144 known remaining instruction bytes; zero unknown sizes; 298 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2321-selection-latched-action-2321` and `accepted-selection-latched-action-2321` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 395 further readable functions

Recover 28 original GUI instruction owners, including the reserved 1,176-byte initializer, as readable C covering 24,060 native bytes. Give the 27 ordinary functions observational semantic names and preserve canonical native linker aliases. Preserve every accepted signature/type/operation and logical code coordinate; six call-token spellings in three accepted bodies change only by the declared inverse. The warning-free isolated object proves all 83 extents, 6,490 nonrelocated words, all 597 native runtime relocation operands and 25 kernel jumps, all 192 readonly bytes and 32 data bytes. Accepted raw instructions are exact; 52 accepted raw ordered record arrays are exact and three use explicit name-identity inverses without rewriting raw records. Native 72-byte string storage supports the observed 30-byte reads. Caller domains, capacity, alias/writability, callback mutation/lifetimes and inherited compiler scaffolds remain explicit unknowns. Preserve the existing partial packing and normal extraction path; no parser change, generated-only patch, record deletion or byte normalization. OC15 separately records dormant exact four-byte padded-RELA rejection. Acceptance requires real normal extraction, exact native alias/import/pool bindings, original ordered 597 runtime records, all 30,968 packed bytes, repeated extraction determinism, fresh four-job original-ROM build, every frozen source hash, full remaining/data/address-name ledger and derived uncertainty index.

Totals: 395 further recoveries after the 225 upstream ordinary imports, plus 1337 existing C semantic cleanups. Current ledger: 805 assembly references = 763 ordinary + 42 entrypoints; 722,084 known remaining instruction bytes; zero unknown sizes; 299 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2344-gui-semantic-contracts-2344` and `accepted-gui-semantic-contracts-2344` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 395 further readable functions

Correct one older matching C wrapper from discarded void result to its observed f32 return; rename the canonical symbol to miscEvaluateVectorDotThroughClampedHelper at original0x00403CA4. Native FVEC18 result flows into BF0 and returned F0 is consumed by original Motion66E4. Historical declarations, normalized input guarantees and result units remain explicitly unknown. Exact whole-definition/source inverse, unchanged member selectors and physical/logical coordinates, all13 instructions/3ordered records and empty compiler logs are verified before writes. Existing canonical symbol/map references are renamed in place; do not add duplicate extraction aliases or apply the older2331 pure-comment fallback. Zero recoveries, one older cleanup; all remaining ASM/data/address-name counts and native sizes unchanged. Normal extraction, original packed MISC, fresh original-ROM build, all frozen manifest files, complete ledger and uncertainty index are mandatory before acceptance.

Totals: 395 further recoveries after the 225 upstream ordinary imports, plus 1338 existing C semantic cleanups. Current ledger: 805 assembly references = 763 ordinary + 42 entrypoints; 722,084 known remaining instruction bytes; zero unknown sizes; 299 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2348-misc-vector-dot-return-contract-2350` and `accepted-misc-vector-dot-return-contract-2350` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 396 further readable functions

Recover Selection03DC as selectionDrawCurrentMenuAndConditionalOverlay with all420 native bytes/105 instructions exact. Preserve all53 original and candidate ELF dictionaries; actual native serialization contains51 module records plus two separately resolved FONT kernel records. Existing native order metadata and all23 signed HI/LO pairs plus5 JAL targets are unchanged. Exact node snapshots immediately after each effectful helper preserve callback-sensitive reads. Add five reviewed scratch/older-caller notes and the separate15D4 parked-contract note; no note receives cleanup/recovery credit and no parked C draft, type view or readonly ownership is accepted. Prewrite whole-source/map inverses, exact semantic alias append removal and logical coordinates are verified. Existing compiler warnings remain tracked. Normal extraction must regenerate old-name ASM callers. Checked converter source is not proof of the running binary; full original packed Selection, fixed FONT instructions, fresh original ROM, all1034 frozen hashes, complete remaining/data/address-C ledger and uncertainty index are mandatory before guarded landing.

Totals: 396 further recoveries after the 225 upstream ordinary imports, plus 1338 existing C semantic cleanups. Current ledger: 804 assembly references = 762 ordinary + 42 entrypoints; 721,664 known remaining instruction bytes; zero unknown sizes; 299 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2376-selection-current-menu-contracts-2376` and `accepted-selection-current-menu-contracts-2376` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 396 further readable functions

One older104-byte C cleanup renames the stored word by actual BATTLE identity comparison and names its unused incoming argument without altering types/expressions or canonical symbol. Remove unsupported handle/phase claims. Retain original66E4/7C10/7FC0 assembly with precise original-provider contracts, searchable unresolved caller/allocation/domain/lifetime/storage evidence and honest complete trial mismatch facts. No trial views/prototypes/ABI/body or recovery credit. Whole-source inverse, ordered members and all original executable/pragma logical coordinates are verified before writes. Normal extraction, original packed Motion, fresh original ROM, all frozen manifest files, complete unchanged remaining ledger and uncertainty index remain mandatory.

Totals: 396 further recoveries after the 225 upstream ordinary imports, plus 1339 existing C semantic cleanups. Current ledger: 804 assembly references = 762 ordinary + 42 entrypoints; 721,664 known remaining instruction bytes; zero unknown sizes; 299 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2379-motion-older-identity-and-dispatch-notes-2379` and `accepted-motion-older-identity-and-dispatch-notes-2379` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 396 further readable functions

One older568-byte query routine cleanup gives seven local roles descriptive names, preserves vector member selectors, strict f32 comparisons, the inherited UV_OLD block, every interleaved component load/store and pointer/count reload, and final exact2.0f trailing trimming. Observational comments replace loose selection-sort wording; count/array/scalar caller contracts remain explicit unknowns. One separate pure cleanup comment stops asserting external override ownership merely because cleanup does not release that pointer; it adds no cleanup credit. Exact whole-source binding-aware inverse, all executable logical coordinates and complete142 words/14 ordered relocation records are independently checked before writes. No new recovery, canonical name, type, ABI, algorithm, allocation or readonly change. Existing unrelated pointer-view warnings remain unchanged. Normal extraction, original packed QUERY/fresh ROM, all frozen source hashes, complete unchanged remaining/address/data ledger and uncertainty index are required.

Totals: 396 further recoveries after the 225 upstream ordinary imports, plus 1340 existing C semantic cleanups. Current ledger: 804 assembly references = 762 ordinary + 42 entrypoints; 721,664 known remaining instruction bytes; zero unknown sizes; 299 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2386-older-query-parallel-array-contracts-2386` and `accepted-older-query-parallel-array-contracts-2386` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 396 further readable functions

Two existing-C SPRT cleanups name display-list cursor and output roles and replace inaccurate alpha-write wording with the actual alpha-comparison effect. Preserve exact macros, shared attribute rereads, command/global access order and final cursor publication. Complete120 words and14 ordered relocation records match; four compile logs are empty. Two zero-credit Selection103CC/Motion77A8 notes preserve original ASM and document observed contracts, declaration debt and exact remaining evidence. No failed C bodies, externs, types, prototypes, runtime, aliases or readonly changes are accepted. Three whole-source byte inverses and all normalized executable logical rows pass before writes. Normal extraction, three original packed modules, fresh original ROM, all frozen source hashes, complete unchanged remaining/address/data ledger and uncertainty index are mandatory.

Totals: 396 further recoveries after the 225 upstream ordinary imports, plus 1342 existing C semantic cleanups. Current ledger: 804 assembly references = 762 ordinary + 42 entrypoints; 721,664 known remaining instruction bytes; zero unknown sizes; 299 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2407-older-sprite-and-native-contract-notes-2407` and `accepted-older-sprite-and-native-contract-notes-2407` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 396 further readable functions

Two existing sprite routines,440-byte bitmap assignment and1028-byte property dispatch, gain descriptive local roles and precise unknown comments. One separate same-line FromBitmap TODO becomes an explicit copied texture-data extent/ownership/lifetime unknown; zero extra cleanup credit. Bitmap drops one unsupported pointer cast to match unchanged s32 ID declaration and original signed validation. Props preserves raw va_arg modes, all narrow stores and callback/member reread order; native32-bit FP inputs do not establish historical variadic declarations or caller packing. Both full object proofs total367words/14orderedrecords per side with empty compiler logs. Exact independent and combined whole-source inverses preserve all838 executable logical rows and every unrelated byte. Original native611/985-word target/provider audits are independent. Asset extent/validity, aliasing, ownership, lifetime, allocator success, negative-index caller domains and input-stream termination remain unknown. No recovery, canonical rename, public type, ABI, macro, algorithm or readonly change. Normal extraction, original SPRT/freshROM, frozen manifest, complete unchanged remaining/address/data ledger and index gates required.

Totals: 396 further recoveries after the 225 upstream ordinary imports, plus 1344 existing C semantic cleanups. Current ledger: 804 assembly references = 762 ordinary + 42 entrypoints; 721,664 known remaining instruction bytes; zero unknown sizes; 299 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2429-older-sprite-bitmap-and-properties-contracts-2429` and `accepted-older-sprite-bitmap-and-properties-contracts-2429` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 397 further readable functions

Recover selectionLatchMenuActionsWithRecordGuard with all276 native bytes/69 words exact. Preserve callback-sensitive node reloads, original latch-before-guard writes, the second action test and live DATA callback-word read. All28 complete ELF dictionaries agree by site; candidate emission and existing metadata exactly match actual native serialized records4200..4227. No metadata change or readonly migration is accepted. One zero-credit before-pragma note preserves the language-question ASM and both honest unmatched trials; no parked C, type or prototype is accepted. Prewrite source/map byte inverses, exact alias append removal and logical coordinates pass. Existing GCC pointer and IDO prototype warnings remain tracked. Normal extraction must regenerate original-name instruction/data ASM references. Checked converter source is not proof of its running binary: original full packed Selection, fresh original ROM, all1034 frozen hashes, complete remaining/data/address-C ledger and uncertainty index must pass before guarded landing.

Totals: 397 further recoveries after the 225 upstream ordinary imports, plus 1344 existing C semantic cleanups. Current ledger: 803 assembly references = 761 ordinary + 42 entrypoints; 721,388 known remaining instruction bytes; zero unknown sizes; 299 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2434-selection-record-guard-contracts-2434` and `accepted-selection-record-guard-contracts-2434` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 397 further readable functions

One existing 96-byte sprite wrapper gains three local/parameter role names and precise cursor backing/capacity/alias/lifetime unknowns. Preserve numeric mask 0xFFDF, embedded sprite offset, provider order and both external cursor assignments. Complete 24-word/one ordered-record object proof per side is exact with empty logs; original 24+856 native words and all 1+25 auxiliary annotations separately reviewed. Whole-source byte inverse and member-aware roles preserve all 838 executable logical rows and logical 208/220 coordinates. No recovery, public API/type/ABI/macro/readonly/ownership change. SPRT_PROP_FAST_COPY selector 10 naming remains separate unresolved public-header debt, requiring caller/reference audit. Original packed SPRT, fresh ROM, all source hashes, complete unchanged remaining/address/data ledger and uncertainty index gates required.

Totals: 397 further recoveries after the 225 upstream ordinary imports, plus 1345 existing C semantic cleanups. Current ledger: 803 assembly references = 761 ordinary + 42 entrypoints; 721,388 known remaining instruction bytes; zero unknown sizes; 299 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2446-older-sprite-display-list-contracts-2446` and `accepted-older-sprite-display-list-contracts-2446` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 397 further readable functions

Retain Battle6A4/9314 assembly with precise original settings/handle/query effects, unresolved caller/allocation/alias/lifetime contracts, the original uninitialized query-prefix quirk and complete failed-trial matching debt. No C/type/prototype/ABI/body/name or recovery/cleanup credit. Whole-source inverse, ordered members and all514 original logical rows/52 pragmas are exact. Original packed Battle, fresh original ROM, every frozen manifest file, complete unchanged worker ledger and uncertainty index remain mandatory.

Totals: 397 further recoveries after the 225 upstream ordinary imports, plus 1345 existing C semantic cleanups. Current ledger: 803 assembly references = 761 ordinary + 42 entrypoints; 721,388 known remaining instruction bytes; zero unknown sizes; 299 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2446-battle-small-pair-retained-contracts-2446` and `accepted-battle-small-pair-retained-contracts-2446` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 397 further readable functions

Two existing sprite routines gain six scoped local/parameter role names and precise unknown/quirk comments: preserve all repeated bitmap/count/pool reads, unchecked allocator-result use, raw count domain, module loading and slot publication order. Original texture data uncertainty remains untouched. Separate pure retained Selection controller note preserves original ASM with logical line 2014 restoration and zero credit. Separate same-line header note records unresolved SPRT_PROP_FAST_COPY selector 10 naming versus observed UVTX selection; expansion/API unchanged. Complete 158-word/45 ordered-record object proof per side is exact with empty logs; original 41+117 native words/all44 initializer annotations independently read. Source/header/Selection byte inverses, member-aware roles and all838 source logical rows pass. Historical declarations, caller ranges, allocation/module success, capacity, aliases and lifetimes remain unknown with resolving producer/caller paths. Two older cleanups, no recovery, new alias/type/ABI/macro/algorithm/readonly ownership change. Normal extraction, original packed SPRT/Selection and fresh ROM, all frozen hashes, complete unchanged 803 remaining/2 data/299 address-name dictionaries and uncertainty index gates mandatory.

Totals: 397 further recoveries after the 225 upstream ordinary imports, plus 1347 existing C semantic cleanups. Current ledger: 803 assembly references = 761 ordinary + 42 entrypoints; 721,388 known remaining instruction bytes; zero unknown sizes; 299 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2459-older-sprite-storage-pool-contracts-2459` and `accepted-older-sprite-storage-pool-contracts-2459` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 397 further readable functions

One existing sprite drawing routine gains eight scoped parameter/local names: input/state pointers, bitmap cursor/index, display-list cursor/start and X/Y scales. Two same-line RE_UNKNOWN comments preserve inherited backing/capacity/alias/numeric/shared-state uncertainties and duplicate IA combine-arm source intent. All types, macros, constants, repeated reads, conversion/branch/call order, duplicate arms, public ABI and readonly ownership retained. Complete856+856 instruction views and25+25 ordered five-field records independently read and exactly equal; both complete logs empty. Member-aware body/full-source inverses preserve all838 executable source rows; drawing body logical690..969. Native2438 context is inverted exactly through only accepted DisplayList/storage-pool changes; original packed bytes remain sole instruction proof. One older cleanup, no recovery/new alias/type/algorithm/ownership change. Normal extraction, original packed SPRT/freshROM/allsource hashes, complete unchanged803 remaining/2 data/299 address-name dictionaries and uncertainty index required.

Totals: 397 further recoveries after the 225 upstream ordinary imports, plus 1348 existing C semantic cleanups. Current ledger: 803 assembly references = 761 ordinary + 42 entrypoints; 721,388 known remaining instruction bytes; zero unknown sizes; 299 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2472-older-sprite-drawing-core-contracts-2472` and `accepted-older-sprite-drawing-core-contracts-2472` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 398 further readable functions

Recover Battle9910 as battlePlayRandomThreeSoundVariant: all324 body bytes/81 instructions and14 complete ordered records match. Preserve signed LCG-times-three truncation, distinct callback paths and returned scalar, handle at owner34 and exact three IDs. Keep searchable caller/handle/module/historical-type unknowns. Original object336 includes a separate12-byte zero tail of unproved historical purpose; full packed Battle must preserve it and TEXT39520. Add only a pure note beside unchanged5D34 assembly documenting captured count, original aliases/cursor/append reloads, helper quirks and both unmatched drafts; no5D34 C/types/prototypes/credit. Existing relocation ordering unchanged. Regenerate extraction after canonical alias. Mandatory fresh original packed module/ROM, full frozen manifest, positive complete worker ledger and uncertainty index gates.

Totals: 398 further recoveries after the 225 upstream ordinary imports, plus 1348 existing C semantic cleanups. Current ledger: 802 assembly references = 760 ordinary + 42 entrypoints; 721,064 known remaining instruction bytes; zero unknown sizes; 299 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2482-battle-three-sound-recovery-and-identifier-contract-2482` and `accepted-battle-three-sound-recovery-and-identifier-contract-2482` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 398 further readable functions

One existing sprite bitmap-command routine gains 27 scoped parameter/local names for endpoints, texture offsets/steps, clipped coordinates, command cursor, packed rectangle fields and split-load traversal. Four RE_UNKNOWN comments record capacity/backing/alias/lifetime, numeric/packed-field, split-data extent and cache invalidation evidence still needed. One qualified RE_ORIGINAL_QUIRK preserves native cache publication for unsupported size values without claiming reachable failure. Types, members, macros, strings, constants, repeated reads, branch/conversion/order, public ABI and readonly ownership retained. Complete1480+1480 accepted-reference/candidate instruction views and12+12 ordered five-field records exactly equal; both logs empty. All1480 original native words/117 initializer words and actual caller/macros independently read; four native/reference raw LO16 operands explicitly distinguished pending packed proof. Member-aware exact body/source/comment inverses preserve all838 executable source rows, bitmap body logical457..663 and resume664. One older cleanup, zero recoveries or aliases. Normal extraction, original packed SPRT/freshROM/1034 source hashes, complete unchanged accepted remaining/data/address dictionaries and index required.

Totals: 398 further recoveries after the 225 upstream ordinary imports, plus 1349 existing C semantic cleanups. Current ledger: 802 assembly references = 760 ordinary + 42 entrypoints; 721,064 known remaining instruction bytes; zero unknown sizes; 299 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2494-older-sprite-bitmap-drawing-contracts-2494` and `accepted-older-sprite-bitmap-drawing-contracts-2494` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 399 further readable functions

Recover selectionUpdateMenuActionAndPendingNodeChange with all496 original bytes and124 words exact. Preserve original state3/state4 reset asymmetry, positive-f32/NaN paths, fresh state and callback-sensitive node/record reloads, signed item callback index and deferred action/latch stores. One native-backed switch dispatch replaces the first unmatched if/else representation; no arbitrary shape search or storage forcing. The sole compatible extern f32 D_80025D70 is grounded by original LWC1/SUB.S and canonical kernel80025D70, with writer units/lifetime still unknown. All46 full ELF records agree by site; original module has42 serialized records after excluding four undefined-kernel pair records. Existing exact metadata restores all42 native records4066..4107; all19 HI/LO pairs and4 direct helper calls resolve to original targets. No metadata or readonly ownership change. Exact whole source/context/map inverses, alias append removal and logical coordinates pass before writes. Existing36 GCC pointer and18 IDO missing-prototype warnings outside target remain byte-identical. Normal extraction must regenerate all original-name assembly/data references. Checked converter source is not proof of running binary behavior: full original packedSelection, fresh original ROM, all1034 source hashes, complete remaining/data/address-C ledger and uncertainty index are mandatory before guarded landing.

Totals: 399 further recoveries after the 225 upstream ordinary imports, plus 1349 existing C semantic cleanups. Current ledger: 801 assembly references = 759 ordinary + 42 entrypoints; 720,568 known remaining instruction bytes; zero unknown sizes; 299 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2507-selection-pending-node-contracts-2507` and `accepted-selection-pending-node-contracts-2507` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 399 further readable functions

Name the existing pose-channel merge uvJanimMergeWeightedPoseChannels and consistently rename its export member, prototype, initializer, caller and linker references, adding the exact 0x00400434 semantic alias without changing binary ABI or shared types. Twenty scoped parameter/local names and seven same-line searchable comments preserve strict clamps, NaN bypass, consumed unmatched entries whose weights are not positive, live alias-sensitive reloads, channel-count resets and final low-byte publication. The vector channel at offset 0x08 stays physically neutral. Original pose producers, all direct/indirect callers, allocations and historical declarations are still needed for ID ordering/agreement, capacity, aliases/lifetimes, numeric/rotation domains and inherited unused locals. The zero-credit header comment corrects the nine observed export words to 0x24; no backing allocation guarantee is inferred. All 502+502 accepted-reference/candidate words and 2+2 complete ordered records agree with empty logs; final comments reverse to the exact compiled 2510 body. Full 1003 original target/provider/caller/initializer words plus two native kernel sqrt words reviewed, with the single raw native/reference LO16 operand distinguished pending original packing. Exact binding/member/global-token/header/alias/whole-source inverses preserve all 571 executable source rows and merge body logical 131..339/resume 340. One older cleanup, zero recoveries. Normal extraction, affected original packed modules, fresh original ROM, full frozen manifest, all 801 remaining and two data dictionaries unchanged, exact removal of only this address-named C row and uncertainty index required.

Totals: 399 further recoveries after the 225 upstream ordinary imports, plus 1350 existing C semantic cleanups. Current ledger: 801 assembly references = 759 ordinary + 42 entrypoints; 720,568 known remaining instruction bytes; zero unknown sizes; 298 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2516-older-joint-animation-merge-contracts-2516` and `accepted-older-joint-animation-merge-contracts-2516` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 399 further readable functions

Pure comments only. Correct JANIM CopyPose capacity wording to its actual u16-member/u8-count gate, document native source flags/count publication after skipped optional copies, and close the ApplyPose offset0x08 vector use through native FMTX slot0x30 scaling. Allocation/extent, alias/lifetime, joint/caller and convention domains remain searchable unknowns. Preserve Battle5ADC/6954 original assembly with actual callbacks, live linked count/slot reads, optional-pointer argument and conditional output validity, precision/compiler debt and explicit source-domain unknowns; clarify the existing caller parameter without changing its type. Selection notes preserve Start-prompt scalar reset/NaN/reloads and shared-sprite render order, while replacing the arbitrary-depth restoration guarantee with the actual push/pop depth constraint and explicit sprite/resource/text/caller requirements. Full native target/provider/init and mismatched diagnostic reviews are frozen; no unaccepted C body/view/type/prototype, runtime fix, parser or metadata change enters the source. Five artifacts/eight exact comment hunks preserve every executable token, member, accepted C body, original ASM pragma and logical coordinate through standalone and combined whole-byte inverses. Zero recoveries and zero additional older cleanup credit, with already-treated JANIM functions explicitly classified. Require original packed JANIM/Battle/Selection, fresh successful four-job original ROM, all1034 frozen source hashes, all801 complete remaining dictionaries, two data dictionaries, all298 address-named C dictionaries unchanged and uncertainty index before guarded landing.

Totals: 399 further recoveries after the 225 upstream ordinary imports, plus 1350 existing C semantic cleanups. Current ledger: 801 assembly references = 759 ordinary + 42 entrypoints; 720,568 known remaining instruction bytes; zero unknown sizes; 298 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2535-joint-battle-selection-contract-notes-2535` and `accepted-joint-battle-selection-contract-notes-2535` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 399 further readable functions

Two genuinely untreated existing quaternion routines gain six scoped parameter/local names and four same-line searchable comments. All original floating arithmetic and associations, component order, local product staging, interleaved copy reads/stores, types, public symbols, shared header/maps and storage ownership remain unchanged. One grounded RE_ORIGINAL_QUIRK records the native scalar subtraction second.x*first.z without claiming a reachable bug; RE_UNKNOWN notes identify original formula/declaration, convention/normalization/input domains, extents/lifetimes and partial-overlap proof still needed. Full71+71 product and9+9 copy accepted-reference/candidate instructions and complete ordered1+1 product records/empty copy arrays agree; four complete compiler logs empty. Full122 original product/copy/initializer words and24 object annotations independently read. The native JAL0998 operand differs from unresolved reference JAL0 and remains subject to mandatory original packed proof. Exact binding/comment/source/member inverses preserve all202 executable source rows and physical lines; product logical159..167/resume168 and copy169..174/resume175. Three additional pure-comment hunks qualify the Battle retained palette context and preserve Selection setting routines as unchanged original ASM with failed drafts explicitly unaccepted. Each note has an exact standalone/combined inverse and preserves all code/pragma logical coordinates, types and ownership. Two older cleanups only, zero recoveries or aliases. Normal extraction, original packed QUAT/Battle/Selection/freshROM/1034 source hashes, complete unchanged801 remaining dictionaries/data2/address298 and fresh index required.

Totals: 399 further recoveries after the 225 upstream ordinary imports, plus 1352 existing C semantic cleanups. Current ledger: 801 assembly references = 759 ordinary + 42 entrypoints; 720,568 known remaining instruction bytes; zero unknown sizes; 298 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2555-older-quaternion-and-setting-contracts-2555` and `accepted-older-quaternion-and-setting-contracts-2555` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 400 further readable functions

Recover selectionUpdateSharedObjectMatrixAndArrows from the original336-byte body with exact84 instruction words and all21 ELF records equal by site. Preserve the copied24-byte local view, scalar decrement and single negative correction with NaN bypass, fresh matrix/provider/global/node reads, object call and local three-word arrow-renderer ABI. Minimum consumed views remain incomplete historical declarations; RE_UNKNOWN calls for original scalar/object/node/storage producers and caller/lifetime evidence. Existing13 native relocation rows preserve six signed address pairs and one original local JAL; eight kernel records resolve separately, actual532-byte callee identity is proven without inventing a module alias. Keep metadata/readonly/data untouched; append exactly one semantic alias and rename the one actual caller reference. Two older fixed-matrix routines gain scoped output/cursor roles and searchable comments, preserving exact sixteen packed identity stores and command/cursor publication order. All19+19 reference/candidate words and ordered0+2 records match; four logs empty. Raw native pop LO16 handle displacement16 versus unresolved reference0 remains explicit and subject to original packed proof. Six zero-credit comments qualify actual IMTX allocation/partial export views and four retained Battle original contracts; no parked C or prototype is accepted. Existing Selection warnings remain inherited and pinned. Exact body/source/context/map/member/coordinate inverses and alias suffix removal preserve all unrelated definitions and pragmas. One new recovery and two older cleanups; all800 remaining complete dictionaries equal the801 baseline minus only611C/336bytes; data2/address298 unchanged and only Selection per-source count decreases. Normal extraction, original packed Selection/IMTX/Battle, fresh original ROM, all1034 source hashes, complete worker ledger and fresh index remain mandatory.

Totals: 400 further recoveries after the 225 upstream ordinary imports, plus 1354 existing C semantic cleanups. Current ledger: 800 assembly references = 758 ordinary + 42 entrypoints; 720,232 known remaining instruction bytes; zero unknown sizes; 298 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2578-older-selection-fixed-matrix-battle-contracts-2578` and `accepted-older-selection-fixed-matrix-battle-contracts-2578` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 400 further readable functions

One existing DOBJ property setter gains three scoped local names and seven same-line contract notes. Complete151 instructions, all seven ordered relocations and two empty compiler logs match the accepted object. Original upper-only guard, selector narrowing, varargs promotions, word stores, shifts, null/error behavior, types and public names remain unchanged. Three concise pure notes describe original Selection release and Battle model-action/range-query behavior and identified unknowns, while preserving their original assembly. Failed C drafts receive no recovery credit. Original packed modules, fresh ROM,1034source pins, uncertainty index and complete unchanged800 remaining/data2/address298 dictionaries required before guarded landing.

Totals: 400 further recoveries after the 225 upstream ordinary imports, plus 1355 existing C semantic cleanups. Current ledger: 800 assembly references = 758 ordinary + 42 entrypoints; 720,232 known remaining instruction bytes; zero unknown sizes; 298 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2595-older-dobj-and-release-contracts-2595` and `accepted-older-dobj-and-release-contracts-2595` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 400 further readable functions

One existing DOBJ model transition gains nine scoped local roles and ten same-line contract comments. All164 instructions,16 ordered relocation records and two complete empty compiler logs match. Original pre-gate model read, missing-resource PANIC, historical FAKE no-op, separately captured old/new byte counts, unguarded allocation publication, repeated free of the captured old base, fresh pointer reads, NaN inequality, final halfword/byte stores and callback order remain unchanged. Searchable unknowns name the original caller, resource producer, allocator, lifetime and transform evidence still needed. Exact full-source/member/logical/physical inverse preserves1348 executable source rows; no public ABI, type, field, alias or ownership change. One older cleanup, zero recoveries. Normal extraction, original packed DOBJ, fresh full ROM,1034source pins, uncertainty index and complete unchanged800remaining/data2/address298 dictionaries required before guarded landing.

Totals: 400 further recoveries after the 225 upstream ordinary imports, plus 1356 existing C semantic cleanups. Current ledger: 800 assembly references = 758 ordinary + 42 entrypoints; 720,232 known remaining instruction bytes; zero unknown sizes; 298 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2622-older-dobj-model-contracts-2622` and `accepted-older-dobj-model-contracts-2622` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 400 further readable functions

One existing DOBJ property query gains three scoped local roles and six same-line comments. All56 instructions,4 ordered relocation records and two empty compiler logs match. Preserve the signed upper-only object gate, word consumption followed by signed-halfword selector narrowing, zero termination, unsupported-selector cursor behavior, per-case fresh output pointer and field reads, and four-byte stores including zero-extended model halfword. Five searchable unknown notes identify missing original caller, argument producer, allocator, output extent, alias and lifecycle evidence. Exact full-source/member/logical/physical inverse preserves1348 executable rows; no public ABI/type/member/ownership change. One older cleanup, zero recoveries. Normal extraction, original packed DOBJ, fresh full ROM,1034source pins, index and complete unchanged800remaining/data2/address298 dictionaries required before guarded landing.

Totals: 400 further recoveries after the 225 upstream ordinary imports, plus 1357 existing C semantic cleanups. Current ledger: 800 assembly references = 758 ordinary + 42 entrypoints; 720,232 known remaining instruction bytes; zero unknown sizes; 298 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2637-older-dobj-getter-contracts-2637` and `accepted-older-dobj-getter-contracts-2637` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 400 further readable functions

One existing DOBJ object slot creator gains a scoped index name and six same-line comments. All50 original instructions,8 ordered relocation records and two empty compiler logs match. Preserve signed count traversal, the first zero occupancy byte, publication before ordered partial reset with global-base reloads, the conditional signed ID-limit update, and fullwordFFFF failure return. Four searchable unknowns name settings/count validity, pool extents, allocation and field lifetime, release/reuse rules, aliases and displaced-buffer ownership. Exact full-source/member/logical/physical inverse preserves1348 executable rows. No field/type/ABI/algorithm change. One older cleanup, zero recoveries. Require normal extraction, original packed DOBJ, fresh fullROM,1034source pins, index and unchanged full800remaining/data2/address298 dictionaries before guarded landing.

Totals: 400 further recoveries after the 225 upstream ordinary imports, plus 1358 existing C semantic cleanups. Current ledger: 800 assembly references = 758 ordinary + 42 entrypoints; 720,232 known remaining instruction bytes; zero unknown sizes; 298 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2646-older-dobj-create-contracts-2646` and `accepted-older-dobj-create-contracts-2646` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 401 further readable functions

Recover one400-byte Selection function with all100 instructions exact. Preserve SND numeric flags, fresh MENU/node reads, asymmetric action7/action8 latches and original deferred callback stores; retain specific original-domain/lifetime/type unknowns. All38 complete object records agree by site and all19 pairs remain intact. Six UND kernel SND records resolve to80025C78; all32 internal serialized records and16 signed targets exactly match original4279..4310 using unchanged metadata. Add five zero-credit source notes: one parked arrow function, three parked Battle functions, and one Battle object-index declaration uncertainty. Exact whole source/context/map inverses and logical coordinates precede writes. No failed C/types, metadata/readonly ownership, ABI or gameplay changes. Existing36 pointer and18 prototype warnings remain byte-identical. Normal extraction must regenerate canonical name references. Full original packed Selection and Battle, fresh original ROM, all1034 source pins, complete remaining/data/address ledger and index are mandatory before landing; checked converter source is not proof of actual converter behavior.

Totals: 401 further recoveries after the 225 upstream ordinary imports, plus 1358 existing C semantic cleanups. Current ledger: 799 assembly references = 757 ordinary + 42 entrypoints; 719,832 known remaining instruction bytes; zero unknown sizes; 298 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2664-selection-latched-action-contracts-2664` and `accepted-selection-latched-action-contracts-2664` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 401 further readable functions

One genuinely untreated existing SORT initializer gains three scoped local role names and seven same-line comments with searchable RE_UNKNOWN flags. Full 142 accepted-reference and candidate instructions, all 53 complete ordered five-field relocation records and two empty compiler logs agree. All 1,110 original SORT/CHAN/CBCK/GMGR words and 396 auxiliary identity annotations were reviewed, including incoming export-base lifetimes and actual CHAN04, CBCK10 and GMGR10 bindings. Pinned original CHAN jump table subtracts one: property 13/index 12 reaches 588 and writes the configured count only for valid channel 0; invalid-channel prior output remains unchanged. Preserve settings zero defaults, signed count domains, captured allocation count versus live traversal bound, fresh capacity and group-base reloads, partial field writes, ignored callback registration status and historical FAKE conditional. Original settings extent, imports/storage/lifetime, allocation failure, aliases, remaining-field validity, channel setup and callback-list capacity/failure handling remain explicit unknowns with resolving evidence. Exact binding-aware body/full-source/member/physical/logical inverses preserve all 261 executable source rows; initializer logical 67..113 resumes 114. Reserved initializer identity, all public types/members/macros, source directives, other definitions, maps and readonly ownership unchanged. One older cleanup only, zero recoveries. Require normal extraction, original packed SORT, fresh full ROM, all 1,034 source manifest files, fresh index and complete unchanged 799 remaining dictionaries/719,832 known bytes/data 2/address 298 before guarded landing.

Totals: 401 further recoveries after the 225 upstream ordinary imports, plus 1359 existing C semantic cleanups. Current ledger: 799 assembly references = 757 ordinary + 42 entrypoints; 719,832 known remaining instruction bytes; zero unknown sizes; 298 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2672-older-sort-initializer-contracts-2672` and `accepted-older-sort-initializer-contracts-2672` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 401 further readable functions

Two genuinely untreated existing callback routines gain allocation-byte and entry-index local roles and four same-line comments. Two separately inverted six-line preceding docs remove a nonexistent constructor parameter and qualify slot traversal. Preserve signed capacity/arithmetic, captured allocation bytes, original align8 allocation then byte clear before capacity publication without a null-result gate, unchanged 32-bit callback forwarding, null-slot skips and capacity reload after actual callback calls. Caller ranges, allocator success, storage/ownership/lifetime, mutation and reentrancy remain searchable RE_UNKNOWN with resolving caller/provider evidence. Full81 original initializer/constructor/executor words and17 annotations, plus8/143/13 kernel allocation-wrapper/core/byte-clear words reviewed. Full20+20 and31+31 accepted-reference/candidate instructions, complete ordered2+2 and0+0 five-field records and four empty logs match. Native constructor J26 operands differ from unresolved object references and are subject to original packed proof. Exact scoped body, preceding-doc and whole-source/member/directive/physical inverses preserve all122 executable callback source rows; constructor logical37..46/resume47 and executor63..75/resume76. Two pure retained-ASM notes qualify Battle652C and Selection1A960; failed drafts/types remain unaccepted and all executable/pragma coordinates preserved. Two older cleanups only, zero recoveries, aliases, types or readonly changes. Require normal extraction, original packed CBCK/Battle/Selection, fresh original ROM, all1034 source pins, unchanged full799 remaining dictionaries/719832B/data2/address298 and fresh index before guarded landing.

Totals: 401 further recoveries after the 225 upstream ordinary imports, plus 1361 existing C semantic cleanups. Current ledger: 799 assembly references = 757 ordinary + 42 entrypoints; 719,832 known remaining instruction bytes; zero unknown sizes; 298 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2700-older-callback-and-query-contracts-2700` and `accepted-older-callback-and-query-contracts-2700` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 403 further readable functions

Recover original284B Selection choice flags and496B Battle kind sound processing with all195 instruction words and ordered10+6 complete object relocation records exact. Preserve callback-sensitive node/field reloads, unsupported-choice no-call behavior, direct unscaled random-fraction truncation and explicit kind1 no-op. Keep caller/type/physical-purpose/resource/lifetime contracts searchable. Add one independent zero-credit Battle7C58 ASM note; failed C/types/prototypes remain unaccepted. Battle minimal context removes only unused7C58 declarations from the matched trial context, with body identity proved. Scoped whole-source/context/reference/map inverses and logical-coordinate checks precede writes. Preserve every existing map byte and append only grounded semantic aliases; normal extraction must regenerate caller labels. Native Selection10 records use unchanged metadata and Battle six actual kernel imports yield zero native records. Selection GCC36 warnings unchanged; IDO prior18 plus one known incomplete-helper-call warning retained; Battle logs empty. Require complete original packed modules/serialized payloads, fresh original ROM, all1034 source pins, exact797 remaining dictionaries/data2/address298/per_source and uncertainty index before landing.

Totals: 403 further recoveries after the 225 upstream ordinary imports, plus 1361 existing C semantic cleanups. Current ledger: 797 assembly references = 755 ordinary + 42 entrypoints; 719,052 known remaining instruction bytes; zero unknown sizes; 298 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2720-selection-battle-choice-sound-contracts-2720` and `accepted-selection-battle-choice-sound-contracts-2720` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 403 further readable functions

Five genuinely untreated existing FVEC leaves gain component/input/output/local roles and concise observed-operation/caller-unknown comments. Preserve all types and public names, x/y/z read-store interleaving, f32 products/differences, left-associated length-squared dependency, Sub unused local and Distance live MATH slot4 read after direct Sub/length-squared calls. Caller storage/alias/lifetime/FP and historical MATH/kernel/local contracts remain searchable RE_UNKNOWN with resolving evidence in the review. Full263 original target/provider/initializer words and all auxiliary annotations reviewed; all58+58 reference/candidate instruction words, Distance4+4 complete ordered five-field records, other four0+0 records and all10 empty logs exact. Native Distance J26 words are module-relative while unresolved object references are zero; complete packed proof remains mandatory. Exact scoped and whole-source binding/comment inverses preserve every executable row, physical line, member selector, directive and unrelated definition. Five older cleanups only, zero recoveries/types/aliases/macros/readonly changes. Require normal extraction, original packed FVEC, fresh full original ROM, all1034 source pins, exact unchanged full797 remaining dictionaries/719052B/data2/address298 and fresh uncertainty index before guarded landing.

Totals: 403 further recoveries after the 225 upstream ordinary imports, plus 1366 existing C semantic cleanups. Current ledger: 797 assembly references = 755 ordinary + 42 entrypoints; 719,052 known remaining instruction bytes; zero unknown sizes; 298 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2738-older-fvec-leaf-contracts-2738` and `accepted-older-fvec-leaf-contracts-2738` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 404 further readable functions

Recover Battle4074 as battlePlayGatedIndexedSound with all 488 bytes/122 words exact, both empty compiler logs and full 48-record object relocation multisets exact. Actual candidate module-local enumeration equals all 32 original packed records and unchanged text order rows; reference object enumeration differs. Actual partial R/D/B identities and kernel gSndExports import, all HI/LO pairs and all six serializers are reviewed; reconstruct original ROM body from resolved object pairs. Preserve four distinct equal-bit coefficient symbols, four managed handle addresses, fresh callbacks, gate clears and unsupported-selector behavior, with specific caller/storage/rearming unknowns. Minimal context prunes only unused 425C declarations; canonical name changes only definition/prototype plus append-only address alias. Add one pure note retaining 425C ASM: one multiply operand-order mismatch, 38-record object multisets exact and 20 native local records already in original order; no C/types/prototype or credit. Preserve all untouched logical coordinates, pragmas, existing maps and relocation ordering. Normal extraction and complete original packed Battle/serialized payloads, fresh ROM, all frozen source pins, exact 796 remaining dictionaries/data2/address298/per_source and uncertainty index remain mandatory.

Totals: 404 further recoveries after the 225 upstream ordinary imports, plus 1366 existing C semantic cleanups. Current ledger: 796 assembly references = 754 ordinary + 42 entrypoints; 718,564 known remaining instruction bytes; zero unknown sizes; 298 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2753-battle-indexed-gate-and-random-contract-2753` and `accepted-battle-indexed-gate-and-random-contract-2753` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 404 further readable functions

Five genuinely untreated existing FVEC helpers gain destination/input roles and concise operation/RE_UNKNOWN comments. Preserve public names/types/macros, original x/y/z read-store interleaving and f32 arithmetic. Full112 initializer plus47 native leaf words reviewed; all47+47 reference/candidate words, all complete empty relocation arrays and10 empty compiler logs exact. Whole-source/member-aware scoped inverses preserve all308 executable FVEC rows and every physical line/directive/other definition. Four independently reviewed Selection retained-assembly comments contribute zero credit and preserve all executable tokens/member selectors/pragma coordinates through separate exact whole-source inverses. Five older cleanups only, zero recoveries/types/aliases/macros/readonly changes. Require normal extraction, original packed FVEC and Selection, fresh full original ROM, all1034 source pins, complete unchanged796 remaining dictionaries/718564B/data2/address298 and fresh uncertainty index before guarded landing.

Totals: 404 further recoveries after the 225 upstream ordinary imports, plus 1371 existing C semantic cleanups. Current ledger: 796 assembly references = 754 ordinary + 42 entrypoints; 718,564 known remaining instruction bytes; zero unknown sizes; 298 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2800-older-fvec-component-and-selection-contracts-2800` and `accepted-older-fvec-component-and-selection-contracts-2800` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 404 further readable functions

Five genuinely untreated existing FVEC negation/set/sum/dot helpers gain destination/input roles and concise operation/RE_UNKNOWN comments. Preserve public names/types/macros, original component read-store interleaving, scalar word forwarding and f32 arithmetic grouping. Full112 initializer plus41 native leaf words reviewed; all41+41 reference/candidate words, all complete empty relocation arrays and10 empty compiler logs exact. Whole-source/member-aware scoped inverses preserve all308 executable FVEC rows and every physical line/directive/other definition. Two independently reviewed Battle retained-assembly comments contribute zero credit and preserve all638 executable rows/member selectors/49 pragma coordinates and all1201 original non-#line row coordinates through a separate exact whole-source inverse. Five older cleanups only, zero recoveries/types/aliases/macros/readonly changes. Require normal extraction, original packed FVEC and Battle, fresh full original ROM, all1034 source pins, complete unchanged796 remaining dictionaries/718564B/data2/address298 and fresh uncertainty index before guarded landing.

Totals: 404 further recoveries after the 225 upstream ordinary imports, plus 1376 existing C semantic cleanups. Current ledger: 796 assembly references = 754 ordinary + 42 entrypoints; 718,564 known remaining instruction bytes; zero unknown sizes; 298 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2818-older-fvec-final-leaf-and-battle-contracts-2818` and `accepted-older-fvec-final-leaf-and-battle-contracts-2818` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 405 further readable functions

Recover the408-byte Selection bitmap/shared-text routine with all102 instruction words exact. Preserve stored sound options, first bitmap load, signed sprite allocation/cache, property9 and2/3 calls, signed half-dimension arithmetic, fresh callback-sensitive reloads, distinct original format and post-format shared-word branch. Keep specific unchecked-allocation, declaration, caller/index/string/overlap/ownership/lifetime unknowns. All46 ELF record dictionaries match by site; original reference tail pairs differ from candidate pairs, which exactly match all13 original native pairs. Nineteen UND kernel records resolve independently; existing27 native metadata rows reproduce exact original serialized order. Rename only the original MIPS_32 function-pointer metadata symbol at rom0x21094 consistently with the C definition; retain the original location, kind and resolved address. No text-sort metadata, header, readonly ownership, ABI or forced-body changes. Normal extraction must regenerate canonical references. Entire original packed Selection including RELA, fresh full original ROM, all source pins, complete previous remaining dictionaries minus only this408-byte target, unchanged data/address dictionaries, per-source counts and uncertainty index are mandatory before landing.

Totals: 405 further recoveries after the 225 upstream ordinary imports, plus 1376 existing C semantic cleanups. Current ledger: 795 assembly references = 753 ordinary + 42 entrypoints; 718,156 known remaining instruction bytes; zero unknown sizes; 298 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2842-selection-bitmap-shared-text-contracts-2842` and `accepted-selection-bitmap-shared-text-contracts-2842` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 406 further readable functions

Recover 969C as battleBlendLinkedMatrixDirection: all 412 bytes, 103 instructions and 11 ordered object relocation records match, with empty compiler logs. One named scalar product local resolves the first trial two-register mismatch; historical local type and order remain unknown. Native J26 record 739 and text order are unchanged. Actual three kernel imports, local 9838 identity and all six serializers are reviewed; reconstruct the original raw ROM words from the complete object records. Retain the matrix rejection output quirk and specific caller, allocation, handle, scalar and callback unknowns. Change only the canonical definition name and append its address alias; all other Battle functions remain unchanged. Normal extraction, full original packed Battle, fresh ROM, all frozen manifest pins, the complete remaining dictionary delta, data, address, per-source and uncertainty-index gates remain mandatory.

Totals: 406 further recoveries after the 225 upstream ordinary imports, plus 1376 existing C semantic cleanups. Current ledger: 794 assembly references = 752 ordinary + 42 entrypoints; 717,744 known remaining instruction bytes; zero unknown sizes; 298 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2855-battle-linked-matrix-readable-recovery-2855` and `accepted-battle-linked-matrix-readable-recovery-2855` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 407 further readable functions

Recover the448-byte measured-menu-label routine with all112 instructions exact. Select FONT11, preserve original measurement and callback-sensitive reload sequence, signed coordinate arithmetic, conditional color and shadow words, and final font-list generation. Preserve the observed measurement-before-MENU-scale-reset quirk and explicit unknown caller/text/font/queue/coordinate/provider-lifetime contracts. Two genuine width/height local declarations are reordered only after native scratch-home evidence; no storage is invented. All16 ELF dictionaries match by site; seven BSS HI/LO pairs match actual native association and signed targets. Existing14 metadata rows reproduce shipped serialization; the two undefined FONT kernel records independently resolve80025C00. No relocation metadata/header/readonly/ABI changes. Rename both declarations and all eight current C calls, append only grounded semantic symbol alias, and require normal extraction to regenerate original ASM callers. Entire original packed Selection including DATA/RELA, fresh original ROM, all1034 source pins, complete ordered remaining/data/address/per-source bridge minus only448-byte target and index checks are mandatory before acceptance.

Totals: 407 further recoveries after the 225 upstream ordinary imports, plus 1376 existing C semantic cleanups. Current ledger: 793 assembly references = 751 ordinary + 42 entrypoints; 717,296 known remaining instruction bytes; zero unknown sizes; 298 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2866-selection-measured-menu-label-contracts-2866` and `accepted-selection-measured-menu-label-contracts-2866` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 407 further readable functions

Three existing DOBJ hierarchy routines gain purpose comments, parameter/local roles and globally consistent names for a scalar-extent query, point-bounds test and segment query. Preserve all current ABI/types, member selectors, macros, callback sequencing, fresh node-array reloads, cached u8 traversal count, signed narrowing/depth loops, shared-word writes and inherited unused storage. RE_UNKNOWN notes identify resource/node/matrix extents and lifetimes, mask and shift domains, stack capacity/balance, callback aliases, units/FP and historical storage evidence still needed; RE_ORIGINAL_QUIRK marks repeated capacity calls, ignored sums and early returns without final pops. All3552 original target/provider/initializer/kernel words reviewed; all525+525 complete reference/candidate instructions and27+27 ordered five-field records agree with six empty logs. Native packed/reference JAL/BSS operand differences are explicitly proved separately, never normalized. Exact binding/comment/global-name and alias-suffix inverses preserve all1348 executable source coordinates; three overview/#line prefixes add six physical lines. Three older cleanups, zero recoveries. Normal extraction, original packed affected modules, fresh original ROM, all1034 source pins, full unchanged remaining/data/per-source dictionaries, exact removal of only these three address-named C rows and fresh uncertainty index remain mandatory before acceptance.

Totals: 407 further recoveries after the 225 upstream ordinary imports, plus 1379 existing C semantic cleanups. Current ledger: 793 assembly references = 751 ordinary + 42 entrypoints; 717,296 known remaining instruction bytes; zero unknown sizes; 295 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2866-older-dobj-hierarchy-contracts-2866` and `accepted-older-dobj-hierarchy-contracts-2866` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 409 further readable functions

Recover 85F8/8B70 as battleConfigureKindOneModelEffects and battleConfigureKindTwoModelEffects: 608+600 bytes, all 302 instructions and 24 ordered object records match, with four empty compiler logs. Preserve actual DOBJ/FMTX/SND/PFX reloads, the three-word matrix copy, ignored queries and rejected-output quirks, distinct readonly coefficient symbols and optional PFX failure. Native-evidenced 1.0f default promotions and genuine local declaration order resolve the first trial differences; historical declarations remain unknown. All eight native local relocation records, 740 existing order rows and six serializers remain unchanged. Caller, extent, ownership, module lifetime, scalar unit and flag unknowns remain explicit. Only the two canonical definitions and append-only aliases are renamed. Normal extraction, full original packed Battle, fresh ROM, all frozen manifest pins, exact remaining dictionary, data, address, per-source and index gates remain mandatory.

Totals: 409 further recoveries after the 225 upstream ordinary imports, plus 1379 existing C semantic cleanups. Current ledger: 791 assembly references = 749 ordinary + 42 entrypoints; 716,088 known remaining instruction bytes; zero unknown sizes; 295 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2902-battle-acquired-model-effects-recoveries-2902` and `accepted-battle-acquired-model-effects-recoveries-2902` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 409 further readable functions

Two existing DOBJ drawing routines gain purpose comments, parameter/local roles and globally consistent names for node-matrix-index traversal and a planar matrix override. Preserve all ABI/types, member selectors, macros, callback sequencing, cached values and fresh reloads, signed depth loops, state restoration and inherited unused storage. RE_UNKNOWN notes identify allocation and asset extents, lifetimes, callback aliases, mask/shift and FP domains, matrix-stack/graphics capacity and historical declaration evidence still needed. RE_ORIGINAL_QUIRK marks the early visibility return skipping the post-callback and fresh stateTable restoration after drawing. All2839 original target/provider/initializer/caller words reviewed, with137 additional terrain-context words kept separate. All597+597 complete reference/candidate instructions and31+31 ordered five-field records must agree with four complete empty logs. Native packed/reference JAL/BSS operand differences are explicitly proved separately, never normalized. Exact binding/comment/global-name and alias-suffix inverses preserve all1348 executable source coordinates; body logical ranges683..800 and802..908, two overview/#line prefixes add four physical lines. Two older cleanups, zero recoveries. Each old name has exactly three source references and two derived relocation-map references; normal extraction must regenerate the latter. Original packed affected modules, fresh original ROM, all1034 source pins, full unchanged791 remaining/data/per-source dictionaries, exact removal of only these two address-named C rows and fresh uncertainty index remain mandatory before acceptance.

Totals: 409 further recoveries after the 225 upstream ordinary imports, plus 1381 existing C semantic cleanups. Current ledger: 791 assembly references = 749 ordinary + 42 entrypoints; 716,088 known remaining instruction bytes; zero unknown sizes; 293 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2920-older-dobj-render-contracts-2920` and `accepted-older-dobj-render-contracts-2920` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 409 further readable functions

Two existing object queries gain purpose comments, scoped parameter/local roles, consistent function/export names and unchanged public field offsets/types. Preserve all arithmetic/macros, original unused storage, callbacks, cached/fresh reads, shared result writes and output publication. Canonical unknown notes identify caller/index/extent/FP domains, resource/storage lifetimes, aliasing and actual capacity evidence still needed. Canonical original quirks preserve writes before capacity checks, ignored normalization return before scalar computation, zero-result output retention, low-u16 point result, return-one/shared-count-zero point path and pointer publication before sorting. Full276+318 original target words,337 DOBJ initializer words,363 fresh and964 independently revalidated reused provider words reviewed with prior original point-hierarchy/kernel closure. Full594+594 reference/candidate words and38+33 ordered five-field ELF records must agree with four complete compiler logs; actual packed runtime relocation counts are not inferred from ELF. All1348 executable source rows and every header coordinate/type preserved by exact role/comment/global-token/member/suffix inverses; only two export member identifiers at50/54 change. Two older treatments, zero recoveries. Parent normal extraction, all affected original packed modules, fresh original ROM, all1034 source pins, complete unchanged791 remaining/data/per-source dictionaries, address293 minus exactly two rows, and fresh uncertainty index remain mandatory.

Totals: 409 further recoveries after the 225 upstream ordinary imports, plus 1383 existing C semantic cleanups. Current ledger: 791 assembly references = 749 ordinary + 42 entrypoints; 716,088 known remaining instruction bytes; zero unknown sizes; 291 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2950-older-dobj-query-contracts-2950` and `accepted-older-dobj-query-contracts-2950` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 409 further readable functions

One existing six-plane perspective matrix builder gains a purpose comment, destination/near/far parameter roles, and a consistent function/export/caller name. Preserve all float types, formula association, chained zeros, original stores and historical empty matching scaffold; caller clip-plane, FP, storage and historical-source evidence remain explicit RE_UNKNOWN debt. Full49 original native/reference/candidate words must be literally equal, with zero ordered ELF records and two complete empty compiler logs. Full1065 FMTX executable logical rows and all header/Channel/Environment coordinates remain exact under scoped roles/comments and global name/member inverses. Exactly one slot50 field and two caller member identifiers change; public offsets/types remain unchanged. Append one proven semantic alias; normal extraction must regenerate two derived references. One older treatment, zero recoveries. Parent normal extraction, three affected original packed modules, fresh original ROM, all1034 source pins, complete unchanged791 remaining/data/per-source dictionaries, address291 minus only1F74, and fresh uncertainty index remain mandatory.

Totals: 409 further recoveries after the 225 upstream ordinary imports, plus 1384 existing C semantic cleanups. Current ledger: 791 assembly references = 749 ordinary + 42 entrypoints; 716,088 known remaining instruction bytes; zero unknown sizes; 290 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2966-older-fmtx-perspective-contracts-2966` and `accepted-older-fmtx-perspective-contracts-2966` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 410 further readable functions

Recover the612-byte localized centered bitmap-menu initializer with all153 instructions exact. Preserve stored sound flags, fresh current-node and export reloads, original language-dependent asset sequences, signed dimension halves and unchecked allocation-result behavior with explicit unknown domains/lifetimes. All34 ELF dictionaries agree by site; existing seven text-sort rows reproduce the original native localJAL and three signed address pairs, while all27 undefined kernel records independently resolve original words and canonical maps. No body/type/header/readonly/text-sort change. Rename only the target definition and forward declaration, append one semantic symbol alias, and canonically rename one independently proved original DATA MIPS_32 reference. Normal extraction, entire original packed Selection including DATA/RELA, fresh original ROM, all1034 source pins, complete remaining/data/address/per-source bridge minus only612-byte target and uncertainty index are mandatory before acceptance.

Totals: 410 further recoveries after the 225 upstream ordinary imports, plus 1384 existing C semantic cleanups. Current ledger: 790 assembly references = 748 ordinary + 42 entrypoints; 715,476 known remaining instruction bytes; zero unknown sizes; 290 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2967-selection-localized-centered-bitmap-contracts-2967` and `accepted-selection-localized-centered-bitmap-contracts-2967` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 410 further readable functions

Five genuinely untreated existing FVEC scalar and predicate helpers gain vector/input roles and concise operation/RE_UNKNOWN comments. Preserve public names/types/macros, component load/evaluation order, (x product + y product) + z product, unsuffixed double-zero comparisons, f32-to-f64 promotion and short circuit, TRUE/FALSE results, and the live MATH slot04 reload after squared-length calls. Original caller storage/lifetimes, FP mode/traps and loader/kernel contracts remain explicitly unknown. Full296 original target/initializer/provider words and116 auxiliary annotations reviewed. All84+84 complete reference/candidate words, six complete ordered records and ten empty compiler logs agree; the two original internal J26 operands are separately resolved against actual ELF targets. Exact scoped binding/comment/full-source/member inverses preserve all308 executable logical rows, physical rows, directives and every other definition. Five older cleanups only, zero recoveries/aliases/types/ownership changes. Require normal extraction, original packed FVEC equality, fresh full original ROM, all1034 source pins, complete unchanged accepted-baseline remaining/data/address/per-source dictionaries and fresh uncertainty index before guarded landing.

Totals: 410 further recoveries after the 225 upstream ordinary imports, plus 1389 existing C semantic cleanups. Current ledger: 790 assembly references = 748 ordinary + 42 entrypoints; 715,476 known remaining instruction bytes; zero unknown sizes; 290 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2988-older-fvec-scalar-predicate-contracts-2988` and `accepted-older-fvec-scalar-predicate-contracts-2988` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 411 further readable functions

Recover075B8 as aiEvaluateScaledCurveWithClampedAdjustment. All352bytes/88instructions match the original reference;12object records have identical sites/targets, with one pair enumeration permutation across the two excluded gUvGrphExports imports. All10 original serialized native records and existing order rows remain unchanged. Preserve grouped input/amplitude scaling, post-callback memory reads, ordered clamps and specific caller/alias/allocation/divisor-domain unknowns. Original DATA coefficients remain memory reads. Existing compiler prototype warnings elsewhere in AI are preserved in the full proof, not waived. Normal extraction, original packed AI/fresh ROM, all frozen manifest files, full remaining dictionary/data/address/per-source/index gates are mandatory.

Totals: 411 further recoveries after the 225 upstream ordinary imports, plus 1389 existing C semantic cleanups. Current ledger: 789 assembly references = 747 ordinary + 42 entrypoints; 715,124 known remaining instruction bytes; zero unknown sizes; 290 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `2996-ai-scaled-curve-readable-recovery-2996` and `accepted-ai-scaled-curve-readable-recovery-2996` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 411 further readable functions

Three existing MODEL functions gain descriptive parameter/local roles and focused purpose/uncertainty comments. Two LOD query functions receive consistent semantic names in declarations, export members, callers and exact appended aliases; all public field offsets/types, historical compiler scaffolds, literals/macros, arithmetic/grouping, callbacks, live reloads and store order remain unchanged. Preserve conditional bounds/output initialization, signed narrow counters and returns, ignored normalization result, writes before the scalar triangle capacity check/decrement, and bounds/segment appends without capacity checks. Caller/asset/FP/storage/alias/lifetime domains remain explicit unknowns. Original1752 target words,175 initializer words and fresh746/provider-reused closure reviewed; complete1752 reference/draft words and202 ordered five-field ELF records plus six full compiler logs required. All1055 MODEL executable source rows and all caller/header coordinates preserved by full role/comment/global-member/alias-suffix inverses. Three older cleanups, zero recoveries. Normal extraction, all affected original packed MODEL/DOBJ modules, fresh original ROM, all1034 source pins, complete unchanged remaining/data/per-source dictionaries, exactly two address-name removals and fresh uncertainty index remain mandatory.

Totals: 411 further recoveries after the 225 upstream ordinary imports, plus 1392 existing C semantic cleanups. Current ledger: 789 assembly references = 747 ordinary + 42 entrypoints; 715,124 known remaining instruction bytes; zero unknown sizes; 288 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `3024-older-model-node-query-contracts-3024` and `accepted-older-model-node-query-contracts-3024` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 412 further readable functions

Recover3D08 as battleBuildAdjustmentControls:876bytes/all219instructions exact, two empty compiler logs and all50 complete object records equal by site and identity. Original42 local records/order rows353..394, actual25 section-relative/import identities and six serializer sources remain unchanged. Preserve owner capture before initializer, fresh export reloads, unchecked factory indices, distinct labels and nine bound controls sharing optional output storage. Full object/export extents, failure/input domains and callback/module lifetimes remain explicit unknowns. Timer4694 and all other Battle bodies/prototypes remain unchanged. Only the canonical prototype/definition and append-only address alias are renamed. Normal extraction, original packed Battle/fresh ROM/all frozen manifest pins, full remaining dictionaries/data/address/per-source and uncertainty-index gates remain mandatory.

Totals: 412 further recoveries after the 225 upstream ordinary imports, plus 1392 existing C semantic cleanups. Current ledger: 788 assembly references = 746 ordinary + 42 entrypoints; 714,248 known remaining instruction bytes; zero unknown sizes; 288 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `3042-battle-adjustment-controls-recovery-3042` and `accepted-battle-adjustment-controls-recovery-3042` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 412 further readable functions

Three genuinely untreated existing CHANNEL functions gain descriptive local/parameter roles, concise operation and uncertainty comments, and consistent canonical names across source, export members, header, three callers and exactly appended native aliases. Preserve all types/offsets/macros, grouped floating-point arithmetic, live reloads, stores and callbacks; retain the null-path absolute-word quirk, ignored callback/normalization results, unreachable i==5 and FAKE/unused-storage scaffolds. Historical struct/array bounds, capacities, allocation/null paths, callback ABI/lifetimes, aliases and FP domains remain searchable RE_UNKNOWN. Original360 target words/117 initializer words and strict provider closure reviewed; full360 reference/draft words,35 ordered five-field object records/native operand mappings and six empty full compiler logs required. Binding-aware whole-source inverses preserve all542 executable CHANNEL rows and every header/caller coordinate; exactly seven export member identifiers change. Three older cleanups, zero recoveries. Normal extraction, original packed CHANNEL/BILL/DOBJ/FX, fresh full original ROM, all1035 source pins, entire unchanged remaining/data/per-source dictionaries, address rows minus only these three and fresh uncertainty index are mandatory.

Totals: 412 further recoveries after the 225 upstream ordinary imports, plus 1395 existing C semantic cleanups. Current ledger: 788 assembly references = 746 ordinary + 42 entrypoints; 714,248 known remaining instruction bytes; zero unknown sizes; 285 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `3080-older-channel-allocation-vector-contracts-3080` and `accepted-older-channel-allocation-vector-contracts-3080` verify real translation-unit instructions/full relocations, 4 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 412 further readable functions

Clarify four existing Motion C functions with eight descriptive local/parameter bindings and original-contract comments: four state-relative planar record updates, selected graph evaluation, and pending Hot Lava/explosion speech attempts. Preserve every type, operation, explicit random-choice gate, callback reload, returned emitter store and pending clear. Focused record extent/lifetime, graph writers/knot/input domains, speech-setting index bounds, pending rearming, module availability, playback units and tuning purpose remain searchable RE_UNKNOWN. Complete original162 target words/20 native records, two direct helpers, six caller windows and actual graph/math/sound bindings were reviewed. Exact binding/comment whole-source inverse preserves all793 active code/declaration rows and63 pragma coordinates. Four older cleanups, zero recoveries. Require original packed Motion, fresh original ROM, all frozen manifest files, complete unchanged remaining/data/address/per-source dictionaries and uncertainty index.

Totals: 412 further recoveries after the 225 upstream ordinary imports, plus 1399 existing C semantic cleanups. Current ledger: 788 assembly references = 746 ordinary + 42 entrypoints; 714,248 known remaining instruction bytes; zero unknown sizes; 285 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `3094-older-motion-record-graph-voice-contracts-3094` and `accepted-older-motion-record-graph-voice-contracts-3094` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 412 further readable functions

Four genuinely untreated existing BILL routines gain descriptive local/parameter roles, concise purpose/uncertainty comments and two consistent canonical names across source, export member, header and exact appended native aliases. Preserve all types/offsets/macros, arithmetic grouping, read/store/callback order, compiler scaffolds and conditional output provenance. Preserve absent-texture coordinate provenance, coincident-endpoint first-result-only clearing, unordered distance comparisons and X/Z radius calculation. Two marker standardizations are comment-only bridges to the exact tested payload. Nine disjoint Selection notes retain original assembly without recovery or cleanup credit. Full1544 native/reference/candidate words,102 ordered complete object records/native operand mappings and eight empty full compiler logs required. Binding-aware whole-source inverses preserve all551 executable BILL rows and all Selection code/pragma coordinates. Four older cleanups, zero recoveries. Normal extraction, original packed BILL/Selection, fresh full original ROM, all1035 source pins, entire unchanged remaining/data/per-source dictionaries, address rows minus only DEC/10B8 and fresh uncertainty index are mandatory.

Totals: 412 further recoveries after the 225 upstream ordinary imports, plus 1403 existing C semantic cleanups. Current ledger: 788 assembly references = 746 ordinary + 42 entrypoints; 714,248 known remaining instruction bytes; zero unknown sizes; 283 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `3140-older-billboard-and-selection-contracts-3140` and `accepted-older-billboard-and-selection-contracts-3140` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 412 further readable functions

Clarify the existing CARAUDIO slot/matrix binding function with four local names and original-contract comments. Preserve all twelve inherited masks, types, expressions and write/load order; historical formal types, negative-index validity, object capacity and storage lifetimes remain RE_UNKNOWN. Add three zero-credit retained-ASM notes for indexed sound handles and the screen-matrix updater, including complete failed-trial facts and unresolved bounds, callback replacement and declaration contracts. The old-C cleanup matches all24 words/96 bytes and all four ordered object relocation records; two original native BSS records are separately pinned. Preserve all166 active logical rows and23 ASM pragmas. One older cleanup, zero recoveries; notes receive no semantic/readability credit. Full original CARAUDIO packed module, fresh original ROM, every frozen manifest file, complete unchanged remaining/data/address/per-source ledger and uncertainty-index checks are mandatory.

Totals: 412 further recoveries after the 225 upstream ordinary imports, plus 1404 existing C semantic cleanups. Current ledger: 788 assembly references = 746 ordinary + 42 entrypoints; 714,248 known remaining instruction bytes; zero unknown sizes; 283 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `3148-older-caraudio-bindings-and-retained-contracts-3148` and `accepted-older-caraudio-bindings-and-retained-contracts-3148` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 412 further readable functions

Clarify three existing Selection object-property/release routines and four graphics-manager initialization/frame routines with scoped local names and truthful original-contract comments. Preserve public symbols, headers, types, operations, masks, memory order, internal __sgi line reset, all executable logical coordinates, member selectors and ASM pragmas. Add zero-credit Selection object-setup retained-ASM and graphics-settings partial-view notes. All seven isolated bodies match 4596 bytes/1149 words and 497 ordered object relocation records; complete original-native nonrelocation/opcode/reference-site checks pass. Selection retains the same 36 GCC and 19 IDO diagnostic identities; graphics-manager logs are empty. Seven older cleanups, zero recoveries. Full original packed Selection/GMGR, fresh original ROM, all1035 frozen files, complete unchanged remaining/data/address/per-source ledger and uncertainty index remain mandatory before acceptance.

Totals: 412 further recoveries after the 225 upstream ordinary imports, plus 1411 existing C semantic cleanups. Current ledger: 788 assembly references = 746 ordinary + 42 entrypoints; 714,248 known remaining instruction bytes; zero unknown sizes; 283 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `3197-older-selection-graphics-manager-contracts-3197` and `accepted-older-selection-graphics-manager-contracts-3197` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 414 further readable functions

Recover two original TED selector-label routines (528 instruction bytes) with natural C and exact original readonly ownership: three real compiler tables, 788-byte retained prefix and 64-byte retained middle, with terminal table at the exact section end and no fabricated host. Clarify three existing ENV routines (9160 bytes) with scoped local roles and original-contract comments; add three zero-credit CARAUDIO retained-ASM notes. Extend only the two reviewed V3 terminal-layout functions and four pure tests. Preserve raw object-order differences in evidence; require exact original packed TED/ENV/CARAUDIO and a fresh original USA ROM after normal extraction and four-job build. Complete1035 frozen source hashes, exact788-minus2 remaining dictionaries, exact2 data entries with only proven TED44-byte ownership transfer, all283 address-name dictionaries, per-source counts and uncertainty index are mandatory. Two recoveries, three older cleanups; comments and tooling receive no code credit.

Totals: 414 further recoveries after the 225 upstream ordinary imports, plus 1414 existing C semantic cleanups. Current ledger: 786 assembly references = 744 ordinary + 42 entrypoints; 713,720 known remaining instruction bytes; zero unknown sizes; 283 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `3236-ted-environment-audio-contracts-3236` and `accepted-ted-environment-audio-contracts-3236` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 414 further readable functions

Clarify the existing UVCL texture HSV blend routine (6544 native bytes) with scoped local names and truthful original-contract comments; rename its prototype, sole C caller and definition to uvColorBlendTextureHsv with one exact appended original-address alias. Add two zero-credit CARAUDIO retained-ASM notes, preserving the three previously accepted notes. The complete1636 words and six ordered five-field ELF records match exactly, with all original native sites/extents and two empty compiler logs. One older cleanup, zero recoveries. No relocation metadata, readonly ownership, headers, types, runtime operations or ASM pragmas change. Normal extraction, fresh full original UVCL/CARAUDIO packed modules and USA ROM, all1035 files, entire786 remaining and2data dictionaries, exact283-minus-only-one address-name dictionaries, all per-source counts and index are required before acceptance.

Totals: 414 further recoveries after the 225 upstream ordinary imports, plus 1415 existing C semantic cleanups. Current ledger: 786 assembly references = 744 ordinary + 42 entrypoints; 713,720 known remaining instruction bytes; zero unknown sizes; 282 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `3264-older-color-audio-contracts-3264` and `accepted-older-color-audio-contracts-3264` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 415 further readable functions

Recover the 400-byte camera basis blend/rebuild function as camBlendAndRebuildBasisRows using the measured original vector layout, retaining the original third.z-from-scaled-third.y quirk and fresh FVEC calls. Clarify the existing 1276-byte graphics-state draw function with scoped local roles and a provider-grounded LIGHT comment; add two zero-credit retained CARAUDIO notes. Full 100+319 instruction words and 8+26 ordered five-field records match, with four empty compiler logs. Preserve all 1448 prior assessed body tokens literally. Normal extraction, fresh complete original CAM/GFXSTATE/CARAUDIO packed modules and USA ROM, all 1035 manifest files, entire prior 786-minus-only-CAM400 remaining dictionaries, all data2/address282/per-source dictionaries and index are mandatory before acceptance. No readonly or text-sort ownership changes.

Totals: 415 further recoveries after the 225 upstream ordinary imports, plus 1416 existing C semantic cleanups. Current ledger: 785 assembly references = 743 ordinary + 42 entrypoints; 713,320 known remaining instruction bytes; zero unknown sizes; 282 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `3312-camera-graphics-state-audio-contracts-3312` and `accepted-camera-graphics-state-audio-contracts-3312` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 415 further readable functions

Clarify the existing 912-byte graphics-state initializer and 1016-byte LookAt direction packer with scoped local roles and concise native-grounded unknowns. Preserve all export stores, allocation and callback order, historical empty-if scaffold, grouped floating-point evaluation, distinct zero-length fallbacks, upper-only limits, byte stores and public types. All 482 native/reference instruction words and 119 complete ordered five-field relocation records match, with four empty compiler logs. Preserve all 1450 previously assessed identities and all 26 prior GFX bodies literally; the two distinct intervals total 1928 bytes and earn no credit until accepted. Normal extraction, fresh full original GFXSTATE packed module and USA ROM, all 1035 source pins, entire785 remaining dictionaries/data2/address282/per-source equality and the uncertainty index remain mandatory.

Totals: 415 further recoveries after the 225 upstream ordinary imports, plus 1418 existing C semantic cleanups. Current ledger: 785 assembly references = 743 ordinary + 42 entrypoints; 713,320 known remaining instruction bytes; zero unknown sizes; 282 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `3346-older-graphics-state-init-clamp-contracts-3346` and `accepted-older-graphics-state-init-clamp-contracts-3346` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 416 further readable functions

Recover the original 912-byte MISC initializer with its reserved extraction identity. Preserve the allocation-pointer callback, all73 export-address stores in native order and exact32-bit address storage. The16 declarations repeat accepted definition signatures without claiming complete callable ABIs; all20 prior MISC assessed bodies and all1452 prior identity tokens remain literal. Complete228 words and147 ordered five-field object relocation records match, with both compiler logs empty. Remove only the exact MISC entrypoint assembly row:785 to784 references,42 to41 entrypoints, ordinary743 unchanged and713320 to712408 remaining bytes. Add only the newly defined reserved entrypoint to address-named C rows at original source order:282 to283. Both retained data rows and every other address/remaining/per-source dictionary follow the explicit projection. Normal extraction, fresh whole original MISC packed module and USA ROM, all1035 source pins and uncertainty-index validation remain mandatory.

Totals: 416 further recoveries after the 225 upstream ordinary imports, plus 1418 existing C semantic cleanups. Current ledger: 784 assembly references = 743 ordinary + 41 entrypoints; 712,408 known remaining instruction bytes; zero unknown sizes; 283 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `3374-misc-initializer-contracts-3374` and `accepted-misc-initializer-contracts-3374` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 417 further readable functions

Recover the776-byte CARANIM initializer with19 native-ordered export stores, resource loads, seven-word copy, four particle property pairs and original callback registration. Preserve the reserved identity; twelve declarations repeat accepted signatures, and4074 is a focused consumed-word view with historical ABI unknown. All194 instruction words and97 complete five-field relocation records match at unique sites; raw ELF emission order differs explicitly. The original71-entry native sort map and26 actual undefined imports are preserved without metadata edits; only inherited4CA0 IDO835 remains. Clarify the existing2108-byte UVCT parser with32 scoped roles and concise original-contract/unknown comments; all527 words and60 raw ordered records match with empty logs. Preserve all1453 prior assessed bodies literally and all83 unresolved entries; two nonoverlapping intervals total2884 bytes and earn credit only after acceptance. Remove only the CARANIM entrypoint row and add its reserved C identity at exact source order:784→783 ASM,41→40 entrypoints,743ordinary unchanged,712408→711632 remaining bytes,address283→284,data2 unchanged. Normal extraction,fresh whole original CARANIM and UVCT packed modules, full USA ROM,all1035 source pins,entire explicit ordered ledger and uncertainty index remain mandatory.

Totals: 417 further recoveries after the 225 upstream ordinary imports, plus 1419 existing C semantic cleanups. Current ledger: 783 assembly references = 743 ordinary + 40 entrypoints; 711,632 known remaining instruction bytes; zero unknown sizes; 284 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `3426-caranim-contour-contracts-3426` and `accepted-caranim-contour-contracts-3426` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 417 further readable functions

Clarify original scene release ordering, callback lifetimes, node lifecycle and property boundaries in sixteen existing C functions. All statements and logical coordinates stay literal; actual unchanged-source warning provenance, complete original words and raw ordered relocations are proved. Full packed modules and ROM remain mandatory.

Totals: 417 further recoveries after the 225 upstream ordinary imports, plus 1435 existing C semantic cleanups. Current ledger: 783 assembly references = 743 ordinary + 40 entrypoints; 711,632 known remaining instruction bytes; zero unknown sizes; 284 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `3496-selection-dynamics-literal-contracts-3496` and `accepted-selection-dynamics-literal-contracts-3496` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 418 further readable functions

Give nineteen existing AI, dynamics and animation-loader functions descriptive local roles and precise original-behavior comments. Recover the profile-game initializer with minimum observed views; preserve its two raw symbol/addend differences while requiring full original packed module and relocation equality. Keep canonical function names, public APIs, arithmetic and store ordering unchanged. Full normal packed modules, ROM, source manifest and complete ledger are mandatory.

Totals: 418 further recoveries after the 225 upstream ordinary imports, plus 1454 existing C semantic cleanups. Current ledger: 782 assembly references = 743 ordinary + 39 entrypoints; 710,904 known remaining instruction bytes; zero unknown sizes; 285 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `3560-engine-role-recovery-cohort-3560` and `accepted-engine-role-recovery-cohort-3560` verify real translation-unit instructions/full relocations, 4 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 418 further readable functions

Give twenty existing dynamics functions precise parameter and local roles and source comments describing original callback ordering, signed bounds, live reads and untouched outputs. Keep the current interfaces, field names, expressions and native instructions unchanged. Historical return use and unchecked domains remain explicitly unknown. Full normal module packing, original ROM, source manifest, index and unchanged complete ledger are required.

Totals: 418 further recoveries after the 225 upstream ordinary imports, plus 1474 existing C semantic cleanups. Current ledger: 782 assembly references = 743 ordinary + 39 entrypoints; 710,904 known remaining instruction bytes; zero unknown sizes; 285 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `3630-dynamics-node-boundary-contracts-3630` and `accepted-dynamics-node-boundary-contracts-3630` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 419 further readable functions

Recover the original128-byte node-property selector with its17-entry compiler-owned jump table; preserve its unassigned fallback quirk. Clarify44 existing-C contracts through scoped local roles and bounded uncertainty comments. All original readonly bytes, serialized module relocations, prior assessed code and final ROM must remain exact.

Totals: 419 further recoveries after the 225 upstream ordinary imports, plus 1518 existing C semantic cleanups. Current ledger: 781 assembly references = 742 ordinary + 39 entrypoints; 710,776 known remaining instruction bytes; zero unknown sizes; 285 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `3684-dynamics-property-and-native-contracts-3684` and `accepted-dynamics-property-and-native-contracts-3684` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 419 further readable functions

Name observed local roles and document original callback, drawing, cleanup and lookup behavior with explicit unresolved domains.

Totals: 419 further recoveries after the 225 upstream ordinary imports, plus 1531 existing C semantic cleanups. Current ledger: 781 assembly references = 742 ordinary + 39 entrypoints; 710,776 known remaining instruction bytes; zero unknown sizes; 285 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `3730-sprite-vehicle-native-contracts` and `accepted-sprite-vehicle-native-contracts-3730` verify real translation-unit instructions/full relocations, 7 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 419 further readable functions

Name observed local roles and document light setup, color-record selection, emitter allocation, property dispatch and voice-stop behavior with explicit unresolved domains.

Totals: 419 further recoveries after the 225 upstream ordinary imports, plus 1538 existing C semantic cleanups. Current ledger: 781 assembly references = 742 ordinary + 39 entrypoints; 710,776 known remaining instruction bytes; zero unknown sizes; 285 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `3800-light-emitter-native-contracts` and `accepted-light-emitter-native-contracts-3800` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 419 further readable functions

Name observed audio manager initialization, buffer setup, emitter playback and particle selection roles while preserving original operations and searchable ownership and layout unknowns.

Totals: 419 further recoveries after the 225 upstream ordinary imports, plus 1545 existing C semantic cleanups. Current ledger: 781 assembly references = 742 ordinary + 39 entrypoints; 710,776 known remaining instruction bytes; zero unknown sizes; 285 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `3874-audio-effects-native-contracts` and `accepted-audio-effects-native-contracts-3874` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 428 further readable functions

Recover nine original MISC functions as descriptive canonical definitions with exact original-symbol compatibility aliases. Preserve all 52 prior C bodies literally, all 13 remaining assembly functions and every existing relocation-map byte. Complete 4576-byte native comparison, 52 ordered five-field records and 18 empty compiler logs passed. The exact trial-to-final name and six blank-line whitespace inverse is explicit; normal extraction, fresh complete original packed MISC and entire relocation section, full original ROM, all 1036 final manifest files (exact prior 1035 plus one explicit absent-before linker input) and exact entire 781-minus-nine ledger projection remain mandatory. The dedicated misc_partial_aliases.ld input uses the existing ld-r/-T route; all nine old/canonical pairs must be defined at equal executable addresses in the final partial ELF. No readonly ownership changes.

Totals: 428 further recoveries after the 225 upstream ordinary imports, plus 1545 existing C semantic cleanups. Current ledger: 772 assembly references = 733 ordinary + 39 entrypoints; 706,200 known remaining instruction bytes; zero unknown sizes; 285 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `3952-misc-core-native-recoveries` and `accepted-misc-core-native-recoveries-3952` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 428 further readable functions

Name observed local roles and document controller sampling, stick normalization, pak repair, rumble state and ear allocation behavior while preserving native order, ABI and searchable unknowns.

Totals: 428 further recoveries after the 225 upstream ordinary imports, plus 1553 existing C semantic cleanups. Current ledger: 772 assembly references = 733 ordinary + 39 entrypoints; 706,200 known remaining instruction bytes; zero unknown sizes; 285 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `4018-controller-ear-native-contracts` and `accepted-controller-ear-native-contracts-4018` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 431 further readable functions

Recover planar segment projection, direction adjustment and scaled distance approach with descriptive local roles and canonical definitions. Preserve every prior C body literally through same-address aliases in the existing partial linker input. All916 native bytes,18 complete ordered five-field records and six empty compiler logs passed; the name/comment inverse and minimal declaration reduction are explicit. Fresh normal original packed MISC, complete relocation section, original ROM, all1036 manifest files and exact full ledger remain mandatory. No readonly ownership change.

Totals: 431 further recoveries after the 225 upstream ordinary imports, plus 1553 existing C semantic cleanups. Current ledger: 769 assembly references = 730 ordinary + 39 entrypoints; 705,284 known remaining instruction bytes; zero unknown sizes; 285 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `4040-misc-three-native-recoveries` and `accepted-misc-three-native-recoveries-4040` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 431 further readable functions

Name observed sequence, frame, file and parser roles and document update order, signed remainder, shared frame-table ownership and unresolved caller domains while preserving every operation and inherited ABI.

Totals: 431 further recoveries after the 225 upstream ordinary imports, plus 1571 existing C semantic cleanups. Current ledger: 769 assembly references = 730 ordinary + 39 entrypoints; 705,284 known remaining instruction bytes; zero unknown sizes; 285 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `4060-texture-sequence-native-contracts` and `accepted-texture-sequence-native-contracts-4060` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 431 further readable functions

Name observed bank, sequence and channel roles and document heap ownership, captured lengths, callback sampling order, conversion widths and inherited return-contract uncertainty while preserving every operation and ABI.

Totals: 431 further recoveries after the 225 upstream ordinary imports, plus 1591 existing C semantic cleanups. Current ledger: 769 assembly references = 730 ordinary + 39 entrypoints; 705,284 known remaining instruction bytes; zero unknown sizes; 285 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `4076-cmidi-runtime-native-contracts` and `accepted-cmidi-runtime-native-contracts-4076` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 431 further readable functions

Name observed timing-mask, coordinate and resource-total roles. Document formatting bounds, discarded calculations and inherited layout and return-contract uncertainty while preserving callback order, storage, ABI and executable coordinates.

Totals: 431 further recoveries after the 225 upstream ordinary imports, plus 1596 existing C semantic cleanups. Current ledger: 769 assembly references = 730 ordinary + 39 entrypoints; 705,284 known remaining instruction bytes; zero unknown sizes; 285 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `4158-debug-overlay-native-contracts` and `accepted-debug-overlay-native-contracts-4158` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 431 further readable functions

Explain observed channel scaling, graphics command packing, fill-cycle state and depth selection. Preserve every executable token, ABI and coordinate while recording inherited channel-domain and rectangle-order uncertainty.

Totals: 431 further recoveries after the 225 upstream ordinary imports, plus 1605 existing C semantic cleanups. Current ledger: 769 assembly references = 730 ordinary + 39 entrypoints; 705,284 known remaining instruction bytes; zero unknown sizes; 285 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `4222-gmgr-rendering-native-contracts` and `accepted-gmgr-rendering-native-contracts-4222` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 433 further readable functions

Recover two named terrain/profiler functions608B with complete unique-site five-field relocation equality and independently replayed original native operands. Preserve raw ELF emission-order differences explicitly. Document three existing angle helpers556B through same-line comments without changing any code tokens or logical coordinates. Preserve retained readonly storage, all prior callers, all prior aliases and all137 typed SDK records. Fresh original packed MISC/full relocation section, original ROM, all1147 files, exact full ledger and defined same-address aliases remain mandatory.

Totals: 433 further recoveries after the 225 upstream ordinary imports, plus 1608 existing C semantic cleanups. Current ledger: 767 assembly references = 728 ordinary + 39 entrypoints; 704,676 known remaining instruction bytes; zero unknown sizes; 285 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `4306-misc-terrain-profiler-angle-contracts` and `accepted-misc-terrain-profiler-angle-contracts-4306` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 433 further readable functions

Explain17 existing vector helpers992B through same-line opening comments. Preserve every code token, logical coordinate, caller, global name, type and expression. Bind all17 actual isolated trials to full original native hashes and ordered five-field relocation records; require empty compiler logs, unchanged retained storage, all1798 prior identities and83 unresolved records, all137 typed SDK rows, fresh original packed MISC/fullROM, all1147sourcefiles and exact unchanged full ledger.

Totals: 433 further recoveries after the 225 upstream ordinary imports, plus 1625 existing C semantic cleanups. Current ledger: 767 assembly references = 728 ordinary + 39 entrypoints; 704,676 known remaining instruction bytes; zero unknown sizes; 285 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `4396-misc-vector-contracts` and `accepted-misc-vector-contracts-4396` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 433 further readable functions

Reassess32 currently unassessed existing-C identities12536B through full original native, exact current compiler-reference instruction bytes, all ordered five-field relocation records and empty compiler logs. Correct three standalone purpose comments; retain every executable token and logical coordinate. Preserve all1815 prior assessments including137 typed SDK intervals, all83 historical unresolved records, assembly and readonly storage, export ABI, existing function names, all1147 sources and the complete remaining ledger. Two known misleading wrapper names remain explicitly queued for a validated alias transition; renaming is already authorized. Require fresh13-module packed/native and original fullROM acceptance before Git landing or new semantic credit.

Totals: 433 further recoveries after the 225 upstream ordinary imports, plus 1657 existing C semantic cleanups. Current ledger: 767 assembly references = 728 ordinary + 39 entrypoints; 704,676 known remaining instruction bytes; zero unknown sizes; 285 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `4444-historical-contract-reassessments` and `accepted-historical-contract-reassessments-4444` verify real translation-unit instructions/full relocations, 3 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 435 further readable functions

Recover the two pending track/player-message sound switches (1940 original instruction bytes). Preserve the full original 1584-byte readonly section as 1528 retained bytes and 56 compiler table bytes, all DATA/BSS and prior C definitions. A fresh normal packed-module and full-ROM proof remains mandatory; readonly storage receives no semantic credit.

Totals: 435 further recoveries after the 225 upstream ordinary imports, plus 1657 existing C semantic cleanups. Current ledger: 765 assembly references = 726 ordinary + 39 entrypoints; 702,736 known remaining instruction bytes; zero unknown sizes; 285 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `4468-race-sound-switch-islands` and `accepted-race-sound-switch-islands-4468` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 436 further readable functions

Recover the 1452-byte sphere candidate query with a descriptive name and explicit original count, association, exact-fill and scratch-ownership constraints. Preserve all 1849 assessed identities, 137 typed SDK intervals, 83 unresolved records, RACE retained-island ownership and all prior C caller tokens. Bind the actual 4436 exact instruction bytes and 31 ordered relocation records, with the sole unrelated inherited IDO835 warning recorded exactly. Require fresh whole original DYN/full ROM, full 1151-source manifest, exact whole-ledger removal and a defined same-section/same-address old-to-canonical ELF alias before landing.

Totals: 436 further recoveries after the 225 upstream ordinary imports, plus 1657 existing C semantic cleanups. Current ledger: 764 assembly references = 725 ordinary + 39 entrypoints; 701,284 known remaining instruction bytes; zero unknown sizes; 285 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `4500-dynamics-sphere-native-recovery` and `accepted-dynamics-sphere-native-recovery-4500` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 436 further readable functions

Review26 complete original existing-C functions7228B across object management, Selection menu/voice gates, sprite rendering and query sorting. Name two object initializer locals and document native-observed ordering, partial resets, selectors, unsupported-option behavior and callback sampling. Use readable wrapped standalone comments with exact logical-coordinate restoration for Selection, sprite and query. Preserve all1850 prior identities including137 typed SDK intervals, all83 historical records, every executable operation, inherited opaque ABI/storage views, existing names, all1151 source files and the complete remaining ledger. Require fresh four-module packed/native plus original fullROM acceptance before landing or semantic credit.

Totals: 436 further recoveries after the 225 upstream ordinary imports, plus 1683 existing C semantic cleanups. Current ledger: 764 assembly references = 725 ordinary + 39 entrypoints; 701,284 known remaining instruction bytes; zero unknown sizes; 285 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `4544-dobj-selection-utility-contracts` and `accepted-dobj-selection-utility-contracts-4544` verify real translation-unit instructions/full relocations, 4 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 436 further readable functions

Review6 complete original existing-C graphics functions1956B across dynamic geometry and billboard setup. Document native-observed capacity/default handling, allocation/dependency/callback order, exact vertex append widths and off-by-one admission, buffer flipping and polygon markers. Preserve duplicate uvVtx/uvVtxDup native behavior, inherited opaque layouts, allocation/domain/lifetime unknowns, and every executable token and logical coordinate. All1876 prior ordinary and typed identities,137 SDK intervals,83 historical rows and1151 source files remain literal. Require fresh two-module whole packed/native and full originalROM acceptance before semantic credit

Totals: 436 further recoveries after the 225 upstream ordinary imports, plus 1689 existing C semantic cleanups. Current ledger: 764 assembly references = 725 ordinary + 39 entrypoints; 701,284 known remaining instruction bytes; zero unknown sizes; 285 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `4588-graphics-lifecycle-contracts` and `accepted-graphics-lifecycle-contracts-4588` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 436 further readable functions

Review thirty complete original existing-C functions totaling 6264 B across screen geometry, color blending, model bounds, collision query adapters, cached tests, audio lifecycle and file I/O. Preserve every executable operation and inherited quirk while naming genuine locals and adding wrapped contracts with exact compiler coordinates. Preserve all 1882 prior ordinary and typed identities, all 137 SDK intervals, all 83 historical records and the complete remaining ledger. Require fresh twelve-module packed/native and full original ROM validation before landing or credit.

Totals: 436 further recoveries after the 225 upstream ordinary imports, plus 1719 existing C semantic cleanups. Current ledger: 764 assembly references = 725 ordinary + 39 entrypoints; 701,284 known remaining instruction bytes; zero unknown sizes; 285 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `4704-geometry-audio-utility-contracts` and `accepted-geometry-audio-utility-contracts-4704` verify real translation-unit instructions/full relocations, 12 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 436 further readable functions

Review27 complete existing-C functions/4268 native bytes across17 source owners. Preserve all executable operations, original quirks, native identity/extent bindings, full translation-unit tokens and logical coordinates. All27 actual scoped observations verify current reference records and native opcode/site associations. Keep23 equal and4 unequal original/current raw reference hashes explicit without inferred explanations. Preserve1915 prior assessments including140 typed SDK intervals, all83 historical attempts and the complete ordinary ledger. Fresh17module packed/native plus original full ROM/source/Git proofs remain required.

Totals: 436 further recoveries after the 225 upstream ordinary imports, plus 1746 existing C semantic cleanups. Current ledger: 764 assembly references = 725 ordinary + 39 entrypoints; 701,284 known remaining instruction bytes; zero unknown sizes; 285 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `4904-remaining-historical-nearby-contracts` and `accepted-remaining-historical-nearby-contracts-4904` verify real translation-unit instructions/full relocations, 17 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 437 further readable functions

Recover144-byte SPARKS four-slot reset and clarify eleven existing graphics functions3880B across eight source files. Preserve exact operations, live callback/base reads, function identities and genuine unknowns. All twelve actual native proofs bind1006 words and416 ordered records. SPARKS inherited991-byte warning is qualified by exact unchanged-source commands, diagnostics and outside-target coordinates; graphics source role/comment inverses use existing v3 proof. Nine graphics raw reference hashes equal originals and two differ explicitly with complete closed native/site association. Preserve1942 prior ordinary/typed assessments,140 SDK rows and83 historical attempts; require fresh full packed/native, original ROM, whole-ledger and Git/source proofs.

Totals: 437 further recoveries after the 225 upstream ordinary imports, plus 1757 existing C semantic cleanups. Current ledger: 763 assembly references = 724 ordinary + 39 entrypoints; 701,140 known remaining instruction bytes; zero unknown sizes; 286 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `5002-sparks-graphics-native-contracts` and `accepted-sparks-graphics-native-contracts-5002` verify real translation-unit instructions/full relocations, 8 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 438 further readable functions

Recover344-byte TRIGANIM dynamic-attachment function and clarify13 existing resource-loader functions2244B. TRIGANIM final TU is literal retained actual compile; closed undefined HI/LO pairs replay native operands while raw ELF record identity remains explicitly false. Preserve actual source/header/caller context and all1954 prior assessments,140 SDK intervals and83 historical attempts. Loader561 native words/76 current ordered records and native/reference association are exact; all13 original/current raw hashes equal. No readonly, aliases, ABI or storage migration. Require fresh entire original packed modules including complete RELA, full original ROM, whole-ledger and current Git/source proofs.

Totals: 438 further recoveries after the 225 upstream ordinary imports, plus 1770 existing C semantic cleanups. Current ledger: 762 assembly references = 723 ordinary + 39 entrypoints; 700,796 known remaining instruction bytes; zero unknown sizes; 287 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `5132-resource-loader-triganim-native-contracts` and `accepted-resource-loader-triganim-native-contracts-5132` verify real translation-unit instructions/full relocations, 7 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 438 further readable functions

Clarify ten existing functions5032B across nine UI/render owners with native-grounded local roles and wrapped readable contracts. Preserve inferred provider types, uninitialized FAKE float scaffold, exact count/allocation/query and resource-lifetime quirks. No ABI, expression, storage or global-name changes. Actual1258 native words, all complete current ordered records/site associations and warning/logical-coordinate proof required. Original terrain12B and TED8B tail padding excluded. Preserve every actual prior ordinary record,140 typed SDK intervals and83 historical attempts. Require fresh whole original packed/native, original ROM, whole-ledger and Git/source proofs.

Totals: 438 further recoveries after the 225 upstream ordinary imports, plus 1780 existing C semantic cleanups. Current ledger: 762 assembly references = 723 ordinary + 39 entrypoints; 700,796 known remaining instruction bytes; zero unknown sizes; 287 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `5154-larger-ui-render-native-contracts` and `accepted-larger-ui-render-native-contracts-5154` verify real translation-unit instructions/full relocations, 9 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 438 further readable functions

Clarify twelve existing functions3408B across eleven module/resource owners with native-grounded local roles and wrapped readable contracts. Preserve sparse initialization, provider assumptions, unchecked handle paths, callback ordering, uninitialized FAKE scaffold and original lifetime quirks. No ABI, expression, storage or global-name changes. Actual852 native words, complete current ordered records/site associations and warning/logical-coordinate proof required. All twelve original declared FUNC extents have zero padding. Preserve every actual prior ordinary record,140 typed SDK intervals and83 historical attempts. Require fresh whole original packed/native, original ROM, whole-ledger and Git/source proofs.

Totals: 438 further recoveries after the 225 upstream ordinary imports, plus 1792 existing C semantic cleanups. Current ledger: 762 assembly references = 723 ordinary + 39 entrypoints; 700,796 known remaining instruction bytes; zero unknown sizes; 287 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `5274-followon-lifecycle-native-contracts` and `accepted-followon-lifecycle-native-contracts-5274` verify real translation-unit instructions/full relocations, 11 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 440 further readable functions

Recover CAM/GLARE assembly functions888B and clarify43 existing initializer/spatial functions5244B across18sources. Preserve actual recovery translation units after exact comment-marker inverse and all prior executable bodies,2009 assessments including159 typed SDK intervals and83 historical attempts. Ordinary43 candidate/baseline/native/site/order proofs are actual and independently replayed. Recovery raw ordered ELF inequality remains explicit: CAM closes six UND ADDIU records, one UND LW pair and one original module-relative J26; GLARE closes twelve literal global records plus six original-packed-order local records and retained DATA/RO windows. No alias, ABI, readonly ownership or storage changes. Fresh entire original packed modules/ordered RELA, all133 module original proof, original ROM, source manifest, complete ledger and actual Git carry mandatory.

Totals: 440 further recoveries after the 225 upstream ordinary imports, plus 1835 existing C semantic cleanups. Current ledger: 760 assembly references = 721 ordinary + 39 entrypoints; 699,908 known remaining instruction bytes; zero unknown sizes; 289 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `5704-initializer-spatial-glare-camera-contracts` and `accepted-initializer-spatial-glare-camera-contracts-5704` verify real translation-unit instructions/full relocations, 18 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 440 further readable functions

Clarify40 existing Selection menu functions2896B with complete native-grounded contracts. Preserve exact literal function bodies, callback/export ordering, unchecked menu/array accesses, handle widths, resources and existing compiler scaffolding. Require actual40 candidate plus1 baseline trials, complete current ordered records and native reference-site associations, scoped warnings and logical-coordinate proof. Preserve every actual2054 prior identity,159 typed SDK rows and83 historical attempts. No new recovery, ABI, names, aliases or storage. Fresh full packed/native/original ROM/full ledger/current Git source proof mandatory.

Totals: 440 further recoveries after the 225 upstream ordinary imports, plus 1875 existing C semantic cleanups. Current ledger: 760 assembly references = 721 ordinary + 39 entrypoints; 699,908 known remaining instruction bytes; zero unknown sizes; 289 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `5644-selection-menu-native-contracts` and `accepted-selection-menu-native-contracts-5644` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 440 further readable functions

Clarify80 existing lifecycle/resource/UI functions6816B across35 sources. Preserve literal executable definitions, original ABI/types, native quirks, callbacks, state-store order and precise remaining unknowns; restore proved MENU and TED/AIPATH/REPLAY facts. Actual80 candidate/36 baseline trials and native/ordered-record/site/warning/whole-TU-coordinate observations required. Preserve2104 prior assessments,169 typed SDK records and83 historical attempts; fresh full packed modules/ROM/full ledger/Git proofs remain mandatory.

Totals: 440 further recoveries after the 225 upstream ordinary imports, plus 1955 existing C semantic cleanups. Current ledger: 760 assembly references = 721 ordinary + 39 entrypoints; 699,908 known remaining instruction bytes; zero unknown sizes; 289 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `6442-lifecycle-ui-native-contracts` and `accepted-lifecycle-ui-native-contracts-6442` verify real translation-unit instructions/full relocations, 35 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 440 further readable functions

Clarify31 existing kernel file/module/resource functions5284B across exactly3 source paths. Preserve literal bodies, ABI/types, allocation ownership and known native quirks. Actual31 candidate/3 baseline trials and complete native/ordered-record/site/warning/whole-TU-coordinate observations required. Preserve2184 prior assessments,169 typed SDK records and83 historical attempts. All133 original packed modules, full original ROM and complete literal ledger remain mandatory.

Totals: 440 further recoveries after the 225 upstream ordinary imports, plus 1986 existing C semantic cleanups. Current ledger: 760 assembly references = 721 ordinary + 39 entrypoints; 699,908 known remaining instruction bytes; zero unknown sizes; 289 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `6572-kernel-resource-native-contracts` and `accepted-kernel-resource-native-contracts-6572` verify real translation-unit instructions/full relocations, 133 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 441 further readable functions

Recover the exact440-byte PIECE function as pieceCreateDynamicReplacementAndUpdateSourceModel. Preserve its original signed count branch, source scalar and matrix operations, provider ABI, explicit ownership/argument unknowns and existing source tokens. Bind the actual6160 compiler trial,6488/6548 complete native and seven ordered records with both logs empty. Add only the module-local legacy compatibility alias; the current Makefile already discovers it. Require fresh1178-source/full133/whole original PIECE/full ROM/exact ledger/Git proof and6596 canonical globalFUNC440 plus defined same-section legacy alias proof before landing. Preserve all2215 prior assessments,169 typed SDK rows and83 historical attempts.

Totals: 441 further recoveries after the 225 upstream ordinary imports, plus 1986 existing C semantic cleanups. Current ledger: 759 assembly references = 720 ordinary + 39 entrypoints; 699,468 known remaining instruction bytes; zero unknown sizes; 289 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `6606-piece-named-recovery` and `accepted-piece-named-recovery-6606` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 441 further readable functions

Clarify29 existing kernel scheduler/startup functions4564B across exactly2 source paths. Preserve literal bodies, ABI/types, allocation ownership and known native quirks. Actual29 candidate/2 baseline trials and complete native/ordered-record/site/warning/whole-TU-coordinate observations required. Preserve2220 prior assessments,173 typed SDK records and83 historical attempts. All133 original packed modules, full original ROM and complete literal ledger remain mandatory.

Totals: 441 further recoveries after the 225 upstream ordinary imports, plus 2015 existing C semantic cleanups. Current ledger: 759 assembly references = 720 ordinary + 39 entrypoints; 699,468 known remaining instruction bytes; zero unknown sizes; 289 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `7010-kernel-scheduler-native-contracts` and `accepted-kernel-scheduler-native-contracts-7010` verify real translation-unit instructions/full relocations, 133 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 441 further readable functions

Clarify62 existing ordinary module contracts2132B across24 sources; preserve literal bodies, ABI, logical coordinates,173 typed SDK rows and83 historical attempts. Require actual62 candidate/24 baseline trials, warning/native/ordered-record/site observations and fresh full133 packed modules/original ROM/full ledger/Git proof. Original12 tail bytes remain excluded; no recovery credit.

Totals: 441 further recoveries after the 225 upstream ordinary imports, plus 2077 existing C semantic cleanups. Current ledger: 759 assembly references = 720 ordinary + 39 entrypoints; 699,468 known remaining instruction bytes; zero unknown sizes; 289 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `8300-remaining-module-native-contracts` and `accepted-remaining-module-native-contracts-8300` verify real translation-unit instructions/full relocations, 133 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 441 further readable functions

Clarify44 existing kernel contracts7900B across24 sources; preserve complete literal bodies, ABI, logical coordinates,173 typed SDK rows and83 historical attempts. Require actual44 candidate/24 baseline trials, warning/native/complete ordered-record/site observations and fresh full133 original packed modules/original ROM/full ledger/Git proof. Preserve26 historical local-metadata holds separately from original positive global FUNC boundaries. No recovery credit.

Totals: 441 further recoveries after the 225 upstream ordinary imports, plus 2121 existing C semantic cleanups. Current ledger: 759 assembly references = 720 ordinary + 39 entrypoints; 699,468 known remaining instruction bytes; zero unknown sizes; 289 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `8820-kernel-remaining44-native-contracts` and `accepted-kernel-remaining44-native-contracts-8820` verify real translation-unit instructions/full relocations, 133 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 444 further readable functions

Recover three original AI functions1212B as aiCheckBasisUnitLengthsAndHandedness, aiPublishDynamicMatrixAndVectorProperties and aiAdjustAndPublishDynamicVectorPair. Preserve original FP/call order, zero-address failure, selective coordinate restoration, caller-scoped provider views and explicit ownership/domain unknowns. Bind actual matched trials with34 ordered records, five literal inherited835 warnings and exact definition-name/source inverses. Add only three relative compatibility assignments in one module alias file; existing Makefile discovers it. Require fresh1182-source/full133/all-original-packed-RELA/ROM/full-ledger/native and canonical/legacy ELF boundary proofs before landing. Preserve every actual prior assessment,173 typed SDK rows and83 historical attempts.

Totals: 444 further recoveries after the 225 upstream ordinary imports, plus 2121 existing C semantic cleanups. Current ledger: 756 assembly references = 717 ordinary + 39 entrypoints; 698,256 known remaining instruction bytes; zero unknown sizes; 289 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `9262-ai-three-named` and `accepted-ai-three-named-9262` verify real translation-unit instructions/full relocations, 133 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 445 further readable functions

Recover aiAccumulateWeightedCallbackResult312B with exact native instructions and six complete unique relocation sites. Preserve the explicit raw record-order inequality and fixed permutation [0,1,2,3,5,4], original DATA/BSS records and five literal inherited835 warnings. Append one relative compatibility assignment to the existing AI alias file; preserve the three accepted AI bodies and aliases. Require fresh1182-source/full133/original packed RELA/ROM/full-ledger/Git and canonical/legacy ELF native boundaries before acceptance.

Totals: 445 further recoveries after the 225 upstream ordinary imports, plus 2121 existing C semantic cleanups. Current ledger: 755 assembly references = 716 ordinary + 39 entrypoints; 697,944 known remaining instruction bytes; zero unknown sizes; 289 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `9380-ai-weighted` and `accepted-ai-weighted-9380` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 447 further readable functions

Recover smackAdvanceObjectMotion436B and smackSetVelocityAndRandomizeSpin652B with exact original native instructions and47 complete unique five-field relocation sites. Preserve both explicit raw ordered-record inequalities and their fixed permutations, original storage records, empty compiler logs, exact matched-body definition-name inverses, provider/header ABI and original quirks. Add only two relative compatibility assignments in one absent module alias file; preserve every prior assessed body and source coordinate. Require fresh1183-source/full133/original packed RELA/ROM/full-ledger/Git and both canonical/legacy ELF boundaries before acceptance. Preserve173 typed SDK rows and83 historical attempts.

Totals: 447 further recoveries after the 225 upstream ordinary imports, plus 2121 existing C semantic cleanups. Current ledger: 753 assembly references = 714 ordinary + 39 entrypoints; 696,856 known remaining instruction bytes; zero unknown sizes; 289 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `9488-smack-motion-pair` and `accepted-smack-motion-pair-9488` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 447 further readable functions

Assess the existing108-byte UVSTRING entrypoint with its real typed MODULE_ENTRY_POINT invocation and literal executable body. Preserve all13 complete ordered relocation records and actual four empty compiler logs, provider ABI, callback stores and source coordinates. Clarify only the loader export-table registration and six callback publication contract; storage and callback lifetime remain caller unknowns. No recovered C, ABI, storage, alias, readonly or denominator change. Require normal all133 original packed/native/ROM,1183 complete sources, full ledger/current Git and carry checks; preserve173 SDK rows and83 historical attempts.

Totals: 447 further recoveries after the 225 upstream ordinary imports, plus 2122 existing C semantic cleanups. Current ledger: 753 assembly references = 714 ordinary + 39 entrypoints; 696,856 known remaining instruction bytes; zero unknown sizes; 289 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `9660-uvstring-macro-entrypoint-contract` and `accepted-uvstring-entrypoint-native-contracts-9660` verify real translation-unit instructions/full relocations, 133 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 448 further readable functions

Recover raceUpdateCountdownVoicesAndLabel564B with all native words and61 closed unique relocation sites; retain explicit unequal raw ELF relocation order and41 ordered original packed sites. Add one absent relative compatibility alias. Apply only the proved zero-credit PLYR typedef/comment correction to raceCreateModuleGui, with exact whole-source/body inverse and actual canonical body/token hashes. All other prior code tokens stay literal. Require fresh1184-source/full133/original790RELA/ROM/full-ledger/Git and both canonical/legacy ELF boundaries; preserve173 typed SDK rows and83 historical attempts.

Totals: 448 further recoveries after the 225 upstream ordinary imports, plus 2122 existing C semantic cleanups. Current ledger: 752 assembly references = 713 ordinary + 39 entrypoints; 696,292 known remaining instruction bytes; zero unknown sizes; 289 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `9892-race-countdown-named` and `accepted-race-countdown-named-9892` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 449 further readable functions

Recover plyrUpdateTimedAudioAndObjectState452B with all113 native words,35 closed unique relocation sites and17 literal ordered packed sites. Retain explicit unequal raw ELF order and all three inherited835 warnings qualified against the actual accepted baseline. Add one absent relative compatibility alias. All prior source tokens and logical coordinates remain literal. Require fresh1187-source/full133/original552RELA/ROM/full-ledger/Git and both canonical/legacy ELF boundaries; preserve175 typed SDK rows and83 historical attempts.

Totals: 449 further recoveries after the 225 upstream ordinary imports, plus 2122 existing C semantic cleanups. Current ledger: 751 assembly references = 712 ordinary + 39 entrypoints; 695,840 known remaining instruction bytes; zero unknown sizes; 289 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `10424-plyr-timed-audio-named` and `accepted-plyr-timed-audio-named-10424` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 453 further readable functions

Recover four MODEL/PFX functions:3064 readable native bytes across91 fixed relocation sites. Preserve unequal raw order, original DATA/BSS/RO storage, all eight existing C definitions and202 typed SDK rows/83 historical attempts. Two four-byte original positive-FUNC tails remain uncredited; full3072 positive bytes, complete CODE/RELA, canonical/legacy ELF boundaries, all133 modules/1212 sources and ROM must independently match after normal build.

Totals: 453 further recoveries after the 225 upstream ordinary imports, plus 2122 existing C semantic cleanups. Current ledger: 747 assembly references = 708 ordinary + 39 entrypoints; 692,776 known remaining instruction bytes; zero unknown sizes; 289 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `11774-upstream-loader-four` and `accepted-upstream-loader-four-11774` verify real translation-unit instructions/full relocations, 2 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 454 further readable functions

Recover victoryCreateCameraAnimationDebugControls:952 native bytes and40 exact fixed relocation sites. Preserve original raw order inequality, original RO/DATA/BSS ownership and210 typed SDK rows/83 failed histories. Require fresh complete952/CODE/RELA/aliases/all133/1218-source/ROM/Git proof.

Totals: 454 further recoveries after the 225 upstream ordinary imports, plus 2122 existing C semantic cleanups. Current ledger: 747 assembly references = 708 ordinary + 39 entrypoints; 691,964 known remaining instruction bytes; zero unknown sizes; 289 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `12856-victory-debug-controls` and `accepted-victory-debug-controls-12856` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Historical accepted checkpoint — 455 further readable functions

Recover sprayAppendStripPoint:692 positive native bytes and10 exact ordered relocation sites. Preserve original RO/DATA/BSS ownership and213 typed SDK rows/2196 ordinary rows/83 failed histories. Require fresh complete692/CODE/RELA/aliases/all133/1220-source/ROM/Git proof.

Totals: 455 further recoveries after the 225 upstream ordinary imports, plus 2122 existing C semantic cleanups. Current ledger: 746 assembly references = 707 ordinary + 39 entrypoints; 691,272 known remaining instruction bytes; zero unknown sizes; 289 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `spray-strip-13756` and `accepted-spray-strip-13756` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.


## Current accepted checkpoint — 456 further readable functions

Recover ufogameBuildCameraDebugPanel:560 readable bytes,564 positive native bytes and14 exact ordered relocation sites. Preserve original RO/DATA/BSS ownership and219 typed SDK rows/2197 ordinary rows/83 failed histories. Require fresh complete564/CODE/RELA/aliases/all133/1225-source/ROM/Git proof;4 trailing zero bytes remain uncredited.

Totals: 456 further recoveries after the 225 upstream ordinary imports, plus 2122 existing C semantic cleanups. Current ledger: 745 assembly references = 706 ordinary + 39 entrypoints; 690,712 known remaining instruction bytes; zero unknown sizes; 289 address-named C definitions remain. Full readable decompilation is incomplete.

Frozen wave `ufogame-camera-panel-14856` and `accepted-ufogame-camera-panel-14856` verify real translation-unit instructions/full relocations, 1 original packed modules, a fresh successful four-job build, original full USA ROM SHA-1 `e5ab4d226c08d22f68a2edcc48870203e67454b8`, and all source hashes in the frozen manifest. The mandatory receipt/source/ledger gate precedes staging and commit.

The recovered `osAiGetLength` source reads the raw 32-bit AI length register.
Its original positive function covers 12 bytes; the remaining four bytes of
the 16-byte source interval are unclassified and uncredited. The existing
recompiled runtime audio substitution remains unchanged.

The recovered legacy `__osGetActiveQueue` source returns the existing pointer
word at `D_80020A54`; it does not substitute the standard active-queue global.
Only the original positive 12-byte function contributes semantic credit.
The candidate has four zero bytes outside its function; those bytes remain
uncredited, and the original outside-function extent is unmeasured. The
existing 12-byte data owner and its trailing eight bytes remain intact.

The PI domain timing snapshot is recovered as `snapshotPiDomainTiming`, with
the original `func_8000730C` identity retained by an exact linker alias.
The mixed unit keeps the 380-byte PI manager in assembly before the
116-byte C helper; the complete normal object must remain 496 bytes.
Only the helper contributes new semantic credit. Its eight volatile
hardware reads update five bytes in each existing 120-byte raw owner;
the remaining 115 bytes and nominal SDK type provenance remain unknown.
The isolated candidate's twelve extra alignment bytes do not enter
the mixed owner or receive credit. Three approved older comment files
preserve all twenty executable bodies and logical coordinates.

The disk interrupt unit retains its 1,408-byte interrupt routine in assembly
and recovers two C helpers, `kernelDiskResetBufferManagerAndNotify` (180 bytes)
and `kernelDiskPostPiEvent` (188 bytes). The helpers use project-internal
external names for real assembly callers; original C linkage and private
storage ownership remain marked RE_UNKNOWN. Exact linker aliases preserve
the original function identities. The separate disk initializer remains
assembly. Four older-code purpose-comment updates preserve all 47 existing
function bodies and logical coordinates. Normal compilation uses existing
2.0I fallback headers only for this unit; no shared SDK ABI or include order
changes. The 1,776-byte object, all 47 relocations, native instructions,
all 133 packed modules and the full original ROM remain acceptance gates.

Three display-list editor routines (704 instruction bytes) now have explicit
RGBA/combiner purpose names and selector fields. Seven earlier routines keep
their literal bodies and logical source coordinates. Original truncation,
aliasing/evaluation-order quirks and unresolved caller/value domains remain
searchable in comments. The complete original module and its three storage
owners remain mandatory normal/native equality gates.

The motor controller unit recovers three original routines (976 instruction bytes)
with the verified J packet layout and a per-file IDO5.3/O2 rule. The reusable
four-controller packet array remains in its existing 256-byte assembly owner.
The motor helper has a genuine compiler function boundary; raw aliases retain
the original identities. The unchanged 5,088-byte assembly suffix is preserved
separately and earns no new C coverage. Full native relocations, all packed
modules and original-ROM equality remain required before accepting this source.


## October 17 strategy: reuse verified recoveries and measured evidence

Prioritize evidenced public recoveries and independent dependency clusters.
The selective terrain sphere-query recovery comes from
[c3e54b43f9fcec4b875c60f01f3befb8613615a9](https://github.com/synamaxmusic/bar-decomp/commit/c3e54b43f9fcec4b875c60f01f3befb8613615a9),
reviewed at upstream
[f5d130b6064cd8ed98b0178bc7617969875f7bc5](https://github.com/synamaxmusic/bar-decomp/commit/f5d130b6064cd8ed98b0178bc7617969875f7bc5).
Retain LLONSIT-glitch's commit authorship and PR141's inspectredc attribution.
Use narrow consumed layout views instead of replacing shared headers, preserving
the 37 older terrain bodies and every backing storage owner. The imported
public expression needed one original-assembly-grounded correction: compare
the left-associated squared-distance sum directly with squared radius rather
than subtracting and comparing with zero. The original ordered comparison and
arithmetic grouping are preserved; the finite-input contract remains unknown.

Read actual instruction, caller, callee and layout evidence before changing a
parked draft. An equivalent branch, declaration or register guess is not a
reason for another compiler trial. Keep independent recoveries moving while
retaining unsuccessful attempts and their precise holds. Use meaningful names,
concise purpose comments and local RE_UNKNOWN/RE_ORIGINAL_QUIRK notes without
inventing capacities, ownership or callback guarantees.

Reuse the shared data-driven fixed-O2 worker, bounded compressed binding and
strict validation algorithms. In terrain trial67942 the compiler command took
0.414 seconds within a 14.131-second guarded worker command. These measurements
do not establish a CPU speedup or completion ETA; source reasoning, evidence
reuse and avoiding repeated setup deserve priority over more compiler trials.
Root serializes validation and guarded commits while independent source work
and review proceed in parallel.

Borrow focused caller/callee queries, dependency clustering, authenticated
evidence reuse and complete-task measurement from
[Reverse Engineer Anything](https://github.com/morluto/rea).
Its documented MIPS32r2 and limited legacy MIPS32 admission does not establish
support for BAR's MIPS III image (ELF flags0x20001101) or exact IDO matching.
No package installation, paid API or private binary upload is implied.

Exact raw instructions alone earn no acceptance. Preserve every relocation
record and provider association, including natural emission-order differences;
require the normal partial link and packing, all 133 original module hashes,
full original-ROM equality, full native Recomp validation, refreshed readability
and uncertainty indexes, and guarded Git landing before credit. Runtime input
and gameplay qualification remain a separate campaign gate.


## FILMROLL disk copy: source recovery pending full validation

The 236-byte disk-copy function is a selective derivative of
[synamaxmusic/bar-decomp PR 138](https://github.com/synamaxmusic/bar-decomp/pull/138),
reviewed at public revision
[0b45277b8e4608b93561a150e331e182fc1a0224](https://github.com/synamaxmusic/bar-decomp/commit/0b45277b8e4608b93561a150e331e182fc1a0224).
Retain that public provenance and the existing AGPL-3.0-or-later notice.
The natural pair of for-loops uses six local variables. This is a meaningful
source-form change from the older drafts that cached the radius, used byte
offsets and used guarded do-loops. Keep the established signed-halfword
copies, first-coordinate-times-320 indexing, clipping tests and live
trailing-word reloads. Coordinate meaning, valid radius and overflow domains,
complete buffer ownership and capacity, and possible record overlap remain
explicit unknowns. The six older FILMROLL bodies and all backing storage
owners stay literal.

One bounded compilation with fixed O2 optimization matched all 236 raw
instruction bytes and the complete target native/provider replay. The whole
2464-byte object TEXT is literal. The measured emission order of the two-record
relocation block, section and string indexes, REGINFO descriptor and raw-export
association require their separate original evidence. Preserve those records
and all strict diagnostic flags; do not sort relocations or repair ELF metadata
to make them appear equal. The new raw-to-canonical linker alias receives zero
extra credit. Require its genuine zero-size FUNC association at 0x634, the normal
partial link, every original packed module and the full original ROM, complete
current native/SDK/carry validation and guarded Git landing before accepting
the 236 bytes. The alias adds one tracked path: the manifest grows from 1256 to
1257 files only after guarded absence and preimage checks. Runtime and gameplay
qualification remain an independent, unfinished campaign requirement.


## CARANIM COPY76: inline registry-copy recovery pending full validation

Recover only the 76-byte registry-copy function. The first two-body diagnostic
matched its own words and four ordered relocations but appended the function
after the old module body, moving its position. Isolating COPY at its original
source slot restored the exact 24724 position: all 76 raw bytes, all four ordered
relocations and the strict native/provider replay matched. Keep the separate
CLEAR callback as its original 56-byte assembly function; its 52-byte C attempt
remains an unaccepted retained diagnostic, not another shape-search candidate.
All 19 previously accepted CARANIM source bodies and their logical coordinates
remain literal.

The copy loop reloads the live count after each destination store and returns
the final live value. Do not snapshot that count or invent a destination bound.
The constructor can increment the count when all eight registry slots are full;
retain this original quirk and the explicit unknown destination capacity,
aliasing, state ownership, lifetime and callback-mutation domains.

The inline diagnostic also has an identical 25,040-byte whole TEXT section.
Its 881 relocation records retain a measured four-record COPY block move and
two entrypoint raw-export HI16/LO16 provider-role transitions. Preserve every
record, multiplicity and actual emission order, together with all false strict
metadata flags. Section/string/table indexes and the REGINFO descriptor remain
explicit measured differences; do not sort records or repair the object.

The canonical symbol-map append and a new raw-to-canonical linker alias are
reversible source changes and add no bytes of credit. Require fresh alias-path
absence/preimage checks, a genuine zero-size raw FUNC at the canonical 0x6094
address, the named normal compile/partial link, all 133 original packed modules
and full original-ROM equality, complete native/SDK/carry checks and guarded
Git landing before accepting 76 bytes. Preserve every earlier failed attempt
and its retained artifacts. Runtime/gameplay qualification remains separate.


## LIGHT1004: complete property dispatch and whole readonly ownership

Recover the original property dispatcher at 0x120 with the reviewed natural
tagged-argument loop. Explicit case zero shares the existing default return;
the five-entry original dispatch table establishes this source constraint.
Keep the unchanged 944 C body. Its 1,004-byte function retains three resolved
PC16 branch words in place of the original relocation records. Offline proof
945 replays every instruction against the original native window using the
four actual candidate relocations; none of the old strict diagnostic flags
is relabelled as a normal or runtime acceptance result.

The C switch owns the complete original 32-byte readonly section: five words
of table entries followed by twelve literal zero bytes. Those zero bytes have
no recovered historical padding purpose and add no instruction-byte credit.
Use standard whole-rodata ownership. Retain the old assembly as an unused
witness, exclude it from S_FILES, and exclude its stale object from the partial
link's independent wildcard input. The fixture covers both input paths.

Preserve all five older LIGHT bodies and their logical coordinates. Leave the
original raw code-address declaration and initializer untouched. The actual
standalone raw symbol is GLOBAL OBJECT, undefined and size zero. The new
raw-to-canonical linker assignment must be measured in the genuine partial;
do not invent a FUNC type, a table-label alias or a metadata exemption.
Require complete original module equality, all 133 original modules, full ROM,
native geometry/content/carry/SDK checks and guarded Git landing before adding
1,004 bytes. Registry bounds, property meaning, non-finite conversion behavior
and callback lifetimes remain explicit source uncertainties.


## FILMROLL904: complete transition source and section ownership

Prepare the original 264-byte buffer-pair setup and 640-byte disk-transition
loop as readable C, preserving the public source attribution already recorded
in this file. The complete FILM translation unit owns its original 16 readonly
bytes, 16 data bytes and 208-byte uninitialized storage extent. Raw linker
aliases for the two recovered functions add no instruction-byte credit.

Preserve the original floating multiplication order in the two older functions.
The alternating-black transition evaluates its volume-scale callback directly
at the observed call site. These two explicit older body/token changes require
their exact native-window proofs; do not claim all seven older bodies literal.
All seven older native identities remain mandatory. Callback order, live count
reloads, framebuffer address comparisons and the 180-by-ten traversal remain
visible in the source. Buffer ownership, live count range, record lifetime,
overflow/nonfinite domains and the unused storage meanings remain RE_UNKNOWN.

Whole-section ownership suppresses FILM assembly generation after make extract
clears asm/us. Preserve all fifteen former assembly consumers in immutable
pre-extract backups, including the three migrated scalar fragments and seven
older function witnesses. Exclude all three stale storage objects from the
normal partial link. Derive physical consumer membership and backup totals from
the exact inventories; a source ownership setting alone proves neither count.

The detached all-nine-function native replay is evidence for normal integration,
not acceptance. Keep its strict diagnostic false flags and complete relocation
association/order evidence. Require genuine current provider rows, raw alias
metadata, normal four-ELF/storage checks, all 133 original modules and full ROM,
FULL/native/carry/SDK validation and guarded Git before adding 904 bytes.
Runtime/gameplay qualification remains separate and pending.

The DYN secondary-address source preserves the original unwritten-result paths. The terminal 44-byte readonly tail is naturally C-owned by the secondary matrix setter, with no instruction credit. Isolated linking and packing reproduced all 79,840 original module bytes exactly; normal, FULL, native and full-ROM validation remain required.


## CAM528 follow-state source proposal

The natural follow-state source reproduces all132 raw target instructions at
0x1B2C and the complete18448-byte CAM TEXT section in the isolated diagnostic.
All13 accepted CAM bodies, code tokens and logical coordinates remain literal.
The legacy target ordered-REL flag remains false: two independent profiler
triples have a different record emission order. Whole-object record ordering
also moves the20-record target block and leaves one raw caller unresolved
until the explicit raw-to-canonical partial-link assignment is observed.
No record sorting, object rewrite, compiler forcing or diagnostic retag is used.

This source-stage proposal adds zero accepted instruction bytes. Its528-byte
identity remains conditional on genuine named normal TU/partial/native facts,
all133 original packed modules, complete original ROM, FULL/whole allocated
Recomp and prior native intervals, carry qualification and guarded Git landing.
Unknown field meanings, callback lifetimes, aliasing and non-finite comparison
domains stay explicit in the source and generated uncertainty index.


## SMACK impact672 source proposal

This detached proposal recovers the model-impact dispatch at CODE0x38C.
The six accepted SMACK bodies, tokens and logical coordinates remain literal;
the 0x1240 helper declaration states its captured float/vector consumed ABI.
The pool updater252 and static attachment312 remain assembly. The existing
0xE00 and0xFB4 aliases are preserved and the impact raw/canonical alias is
added separately. No owner-storage or Makefile change is proposed.

The current14-row original reference is qualified independently. Matching of
this exact672-only source is not qualified by this source bank. Its672 bytes
remain proposed with zero accepted credit until actual named normal TU/partial
facts, all168 native words, all six prior intervals, complete allocated storage,
all133 packed modules, the full original ROM, FULL/native carry and guarded Git
landing qualify. Retained older diagnostic false flags are not normalized.

Descriptor/controller domains, callback mutation and alias/lifetime guarantees,
float/gate units and return-code meanings stay explicit RE_UNKNOWN obligations.
Original ordered comparisons, reloads and unchecked behaviors remain intact.


## Terrain grid-mask source proposal

The readable segment-and-bounds mask helper at CODE 0xBD38 reproduces all
143 original instructions, its three ordered relocations, and the complete
54096-byte terrain TEXT section in the isolated diagnostic. All38 accepted
terrain bodies, code tokens and logical coordinates remain literal. The five
original raw-name callers still require genuine partial-link alias and native
qualification. Legacy native and prior metadata flags remain unchanged.

This source-stage proposal adds zero accepted instruction bytes. The572-byte
identity requires genuine normal TU/partial/provider metadata, complete native
replay, all133 packed modules, original ROM equality, FULL validation, semantic
carry qualification and guarded Git landing. B26C remains assembly. Unknown
field meanings and original out-of-range/grid callback quirks remain searchable
in source comments and the generated uncertainty index.


## PFX284 PI and readonly-owner source-stage proposal

The indexed initializer retains the measured PI literal at readonly offset436.
A detached replay of all71 native words passes using genuine original providers;
the legacy isolated raw/ordered-REL/storage flags remain false and native status
UNMEASURED. The real remaining0242C ASM host retains the authentic72-byte tail
at offset440 with phase8. The unchanged getter owns212 bytes, C PI owns4, and
the retained prefix224 plus tail72 completes512 bytes with106 readonly records.

The ledger above is the prospective source-bank projection, not accepted credit.
Accepted audited instruction/readable bytes remain587392 of1270016;
587676 is conditional on accepting this284-byte identity. This bank adds zero
accepted instruction bytes. The identity requires
actual normal TU/partial/provider/native qualification, all20 prior native
windows, complete allocated storage, all133 packed modules and original ROM,
FULL/native/carry and guarded Git before acceptance. RE_UNKNOWN and
RE_ORIGINAL_QUIRK contracts remain searchable in the regenerated source index.
