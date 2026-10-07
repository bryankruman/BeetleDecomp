# Matching and recomp dependency validation — October 6, 2026

Historical initial checkpoint (superseded by the current ledger below):
The upstream integration through e0112bf retains upstream history, and four further
readable utility functions are committed in 76a2c9b. This is partial decompilation:
1,196 assembly references (62 entrypoints), 825,380 instruction bytes and 1,362
address-named C definitions remain. Zero unknown assembly sizes are recorded.

All 133 packed module SHA-256 checks and original USA ROM SHA-1
e5ab4d226c08d22f68a2edcc48870203e67454b8 passed in isolated pve container 105.
The four utility modules and ROM passed again after semantic naming and extraction.
All 1,013 accepted local source files matched the worker before each landing.
Evidence is under /opt/beetle-campaign-20261006/accepted-union and
accepted-readable-small-functions. Private input archives remain frozen.

The recomp linker generator now discovers modules from src/modules/*.c, matching
the Makefile. Fully recovered cbars and expl had no remaining assembly data/BSS
and were incorrectly omitted by the previous discovery. Missing partial objects
now fail explicitly. The generated linker script remains ignored and is removed
from Git tracking; source generation is authoritative. The check wrapper defaults
to four jobs, keeping worker builds within the approved resource bound.

The corrected 133-module recomp ELF SHA-256 is
07b1fdf9853f11d56ec59c1099a722db9794b965d81c909656ef3fee8d057a79.
The original matching ROM still passes. In the companion recomp, main/patch code
generation, strict original-instruction fixups, MIPS patch linking and the full
Linux Release application link pass with this ELF. Actual cartridge-read and
ELF fixup regressions pass. Evidence: /opt/beetle-recomp-review-20261006/
cartridge-read-validation. This does not establish Windows or gameplay correctness.

The Windows staging records verified-union-landed.json, readable-small-landed.json
and accepted source manifests retain local provenance. Do not publish private ROMs,
ELFs, raw archives or SDK files. No paid model/API benchmark is claimed.


## Accepted readable waves through ff53b8e

Twenty-one additional functions after upstream integration are committed with
behavior-based names and purpose comments. Commits: `76a2c9b`, `06bf51c`,
`8c7f0f4`, `838a024`, `ff53b8e`. The build repair/research checkpoint is `1d920940`.
Every function wave passes original packed module hashes and full USA ROM SHA-1
`e5ab4d226c08d22f68a2edcc48870203e67454b8` after extraction and readability edits.
All 1,013 local source hashes agree with each validated worker snapshot before landing.

Historical ledger at ff53b8e: 1,179 assembly references = 1,117 ordinary + 62 entrypoints;
823,828 known remaining instruction bytes, zero unknown sizes, 1,360 address-named
C definitions. The game is not fully decompiled or fully audited for readability.
Proofs reside under `/opt/beetle-campaign-20261006/accepted-grounded-utilities`,
`accepted-pause-confirmations`, `accepted-context-utilities` and `accepted-module-cleanup`.
Guarded source waves preserve originals and plan hashes. Generated m2c seeds and
failed candidates remain unaccepted diagnostic material, never progress claims.

The companion recomp passes main/patch generation, strict fixups, full Linux and
Windows links. Runtime tests cover fresh launch, original Pak creation, cached-ROM
and existing-Pak reload, expanded 16:9 driving and pause over 190 seconds. Broader
course/results/multiplayer/audio-quality/physical-rumble gates remain open.


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


## Current accepted checkpoint — 100 further readable functions

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

Current ledger: 1,100 assembly references = 1,038 ordinary + 62 entrypoints;
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
