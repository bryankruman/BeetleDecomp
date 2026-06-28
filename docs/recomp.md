# Recompilation ELF (`build/recomp.elf`)

This documents the `make recomp` path: producing an ELF laid out for **static
recompilation** with [N64Recomp](https://github.com/N64Recomp/N64Recomp), consumed by the
**BeetleRecomp** PC port (https://github.com/bryankruman/BeetleRecomp).

> **Status: UNTESTED.** `tools/genRecompLd.py` and the `recomp:` rule were written without
> running a build (no `.venv`/ROM/toolchain at authoring time). Treat this as a first draft;
> the checklist at the bottom must be verified before relying on the output.

## Why a separate ELF

The matching build is unsuitable as N64Recomp input:

- `beetleadventurerac.us.elf` (`find_file_boundaries`) splits each module into many per-file
  blob sub-sections (`.UVBT_0`, `.UVAN_0`, …) — raw archived bytes, not relocatable code.
- `build/bin/us/<module>.o` is a single packed `.uvmo` binary blob (one `.data` section, no
  `.text`, no usable relocations).

N64Recomp needs **one relocatable section per module**, with real `.text`/`.rodata`/`.data`/
`.bss` and ELF MIPS relocations. Those live in **`build/partial_<module>.o`** (produced by
`ld -r`; relocations preserved by the `--emit-relocs` LDFLAG).

## How it works

`make recomp`:
1. runs `pre-partial-link` (builds `FORM0.o`, the partial module objects, and
   `kernel_link_scripts_syms.txt`, which supplies `main_VRAM`, `FORM0_ROM_START`,
   `MODULE_FILES_START`, `UVTS_25_ROM_END`, … to the link);
2. runs `tools/genRecompLd.py linker_scripts/us/beetleadventurerac.ld`, which
   - copies the base script up to `FORM0_VRAM_END` (base game + FORM0 region, exactly as
     the matching link), then
   - appends one `.<module>` output section per module pulling `build/partial_<module>.o`
     at a distinct nominal VRAM, with `__recomp_<module>_*` boundary symbols;
3. links `build/recomp.elf` with `recomp.ld` + the auto undefined-stub scripts +
   `kernel_link_scripts_syms.txt`.

`recomp.ld` is generated and git-ignored (like `kernel.ld`).

## Feeding it to BeetleRecomp

In the recomp repo:
- point `BeetleRecomp.toml` `elf_path` at this `build/recomp.elf`;
- list the `.<module>` section names in `overlays.us.txt` (regenerate with
  `scripts/gen-overlays.sh`).

## Testing checklist (when `.venv`/ROM/toolchain are available)

- [ ] `make recomp` completes and produces `build/recomp.elf`.
- [ ] No duplicate-symbol or overlapping-section errors from `ld`.
- [ ] `readelf -r build/partial_<module>.o` shows real `.text`/`.rodata`/`.data`/`.bss` and
      MIPS relocations, and they survive into `recomp.elf`.
- [ ] Confirm the `FORM0_VRAM_END` truncation keeps base + FORM0 and drops the per-file blob
      sections (no `.UVBT_0` etc. in `recomp.elf`).
- [ ] Decide distinct-VRAM (current) vs. all-at-`0x400000` `OVERLAY`, per what N64Recomp
      expects for relocatable sections.
- [ ] N64Recomp ingests `recomp.elf` and emits per-module relocations (LOOKUP_FUNC/RELOC_*).
