# Build options can be changed by modifying the makefile or by building with 'make SETTING=value'.
# It is also possible to override the settings in Defaults in a file called .make_options as 'SETTING=value'.

-include .make_options

MAKEFLAGS += --no-builtin-rules --no-print-directory --halt-on-error

# Returns the path to the command $(1) if exists. Otherwise returns an empty string.
find-command = $(shell which $(1) 2>/dev/null)

#### Defaults ####

# If COMPARE is 1, check the output sha1 after building
COMPARE ?= 1
# If NON_MATCHING is 1, define the NON_MATCHING C flag when building
NON_MATCHING ?= 0
# if WERROR is 1, pass -Werror to CC_CHECK, so warnings would be treated as errors
WERROR ?= 0
# Keep .mdebug section in build
KEEP_MDEBUG ?= 0
# Check code syntax with host compiler
RUN_CC_CHECK ?= 1
CC_CHECK_COMP ?= gcc
# Dump build object files
OBJDUMP_BUILD ?= 0
# Number of threads to compress with
N_THREADS ?= 4
# If COMPILER is GCC, compile with GCC instead of IDO.
COMPILER ?= ido
# Whether to colorize build messages
COLOR ?= 1
# Whether to hide commands or not
VERBOSE ?= 0
# Command for printing messages during the make.
PRINT ?= printf

# Set prefix to mips binutils binaries (mips-linux-gnu-ld => 'mips-linux-gnu-') - Change at your own risk!
# Auto-detect prefix for MIPS toolchain
ifneq      ($(call find-command,mips-linux-gnu-ld),)
  MIPS_BINUTILS_PREFIX := mips-linux-gnu-
else ifneq ($(call find-command,mips64-linux-gnu-ld),)
  MIPS_BINUTILS_PREFIX := mips64-linux-gnu-
else ifneq ($(call find-command,mips64-elf-ld),)
  MIPS_BINUTILS_PREFIX := mips64-elf-
else
  $(error Unable to detect a suitable MIPS toolchain installed)
endif

VERSION ?= us
REV ?= rev0

BASEROM              := baserom.$(VERSION).z64
TARGET               := beetleadventurerac

### Output ###

BUILD_DIR := build
TOOLS	  := tools
PYTHON	  := python3
ROM       := $(BUILD_DIR)/$(TARGET).$(VERSION).z64
ELF       := $(BUILD_DIR)/$(TARGET).$(VERSION).elf
LD_MAP    := $(BUILD_DIR)/$(TARGET).$(VERSION).map
LD_SCRIPT := linker_scripts/$(VERSION)/$(TARGET).ld
KERNEL_LD_SCRIPT := linker_scripts/$(VERSION)/kernel.ld
KERNEL_LD_MAP := linker_scripts/$(VERSION)/kernel.map

#### Setup ####

# If gcc is used, define the NON_MATCHING flag respectively so the files that
# are safe to be used can avoid using GLOBAL_ASM which doesn't work with gcc.
ifeq ($(COMPILER),gcc)
  $(warning WARNING: GCC support is experimental. Use at your own risk.)
  CFLAGS += -DCOMPILER_GCC
  NON_MATCHING := 1
endif

# Detect compiler and set variables appropriately.
ifeq ($(COMPILER),gcc)
  CC       := $(MIPS_BINUTILS_PREFIX)gcc
else
ifeq ($(COMPILER),ido)
  CC       := $(TOOLS)/ido-static-recomp/$(DETECTED_OS)/7.1/cc
  CC_OLD   := $(TOOLS)/ido-static-recomp/$(DETECTED_OS)/5.3/cc
else
$(error Unsupported compiler. Please use either ido or gcc as the COMPILER variable.)
endif
endif

ifeq ($(COMPILER),gcc)
  OPTFLAGS := -Os
else
  OPTFLAGS := -O2
endif

ifeq ($(COMPILER),gcc)
  CFLAGS += -G 0 -ffast-math -fno-unsafe-math-optimizations -march=vr4300 -mfix4300 -mabi=32 -mno-abicalls -mdivide-breaks -fno-zero-initialized-in-bss -fno-toplevel-reorder -ffreestanding -fno-common -fno-merge-constants -mno-explicit-relocs -mno-split-addresses $(CHECK_WARNINGS) -funsigned-char
  MIPS_VERSION := -mips3
else
  # we support Microsoft extensions such as anonymous structs, which the compiler does support but warns for their usage. Surpress the warnings with -woff.
  CFLAGS += -G 0 -use_readonly_const -non_shared -fullwarn -verbose -Xcpluscomm $(IINC) -nostdinc -Wab,-r4300_mul -woff 649,838,712,516
  MIPS_VERSION := -mips2 -32
  WARNINGS := -fullwarn -verbose -woff 624,649,838,712,516,513,596,564,594,709,807
endif

ifeq ($(COMPILER),ido)
  # Have CC_CHECK pretend to be a MIPS compiler
  MIPS_BUILTIN_DEFS := -D_MIPS_ISA_MIPS2=2 -D_MIPS_ISA=_MIPS_ISA_MIPS2 -D_ABIO32=1 -D_MIPS_SIM=_ABIO32 -D_MIPS_SZINT=32 -D_MIPS_SZLONG=32 -D_MIPS_SZPTR=32
  CC_CHECK  = gcc -fno-builtin -fsyntax-only -funsigned-char -std=gnu90 -D_LANGUAGE_C -DNON_MATCHING $(MIPS_BUILTIN_DEFS) $(IINC) $(CHECK_WARNINGS)
  ifeq ($(shell getconf LONG_BIT), 32)
    # Work around memory allocation bug in QEMU
    export QEMU_GUEST_BASE := 1
  else
    # Ensure that gcc (warning check) treats the code as 32-bit
    CC_CHECK += -m32
  endif
else
  CC_CHECK  = @:
endif

BUILD_DEFINES ?=

# Version check
ifeq ($(VERSION),jp)
    BUILD_DEFINES   += -DVERSION_JP=1
endif

ifeq ($(VERSION),us)
    BUILD_DEFINES   += -DVERSION_US=1
endif

ifeq ($(VERSION),eu)
    BUILD_DEFINES   += -DVERSION_EU=1
	REV := rev0
endif

ifeq ($(VERSION),au)
	BUILD_DEFINES	+= -DVERSION_AU=1
	REV := rev0
endif

ifeq ($(VERSION),ln)
	BUILD_DEFINES	+= -DVERSION_LN=1
	REV := rev0
endif

ifeq ($(NON_MATCHING),1)
    BUILD_DEFINES   += -DNON_MATCHING -DAVOID_UB -DISPRINT
    CPPFLAGS += -DNON_MATCHING -DAVOID_UB
endif

MAKE = make
CPPFLAGS += -fno-dollars-in-identifiers -P
LDFLAGS  := --no-check-sections --accept-unknown-input-arch --emit-relocs
# Compatibility aliases for preserved local matches, separate from Splat names.
ifneq ($(wildcard linker_scripts/$(VERSION)/local_matching_aliases.ld),)
LDFLAGS += -T linker_scripts/$(VERSION)/local_matching_aliases.ld
endif

UNAME_S := $(shell uname -s)
UNAME_M := $(shell uname -m)
ifeq ($(OS),Windows_NT)
$(error Native Windows is currently unsupported for building this repository, use WSL instead c:)
else ifeq ($(UNAME_S),Linux)
    DETECTED_OS := linux
    #Detect aarch64 devices (Like Raspberry Pi OS 64-bit)
    #If it's found, then change the compiler to a version that can compile in 32 bit mode.
    ifeq ($(UNAME_M),aarch64)
        CC_CHECK_COMP := arm-linux-gnueabihf-gcc
    endif
else ifeq ($(UNAME_S),Darwin)
    DETECTED_OS := macos
    MAKE := gmake
    CPPFLAGS += -xc++
    CC_CHECK_COMP := clang
endif

# Support python venv's if one is installed.
PYTHON_VENV = .venv/bin/python3
ifneq "$(wildcard $(PYTHON_VENV) )" ""
  PYTHON = $(PYTHON_VENV)
endif

ifeq ($(VERBOSE),0)
  V := @
endif

ifeq ($(COLOR),1)
NO_COL  := \033[0m
RED     := \033[0;31m
RED2    := \033[1;31m
GREEN   := \033[0;32m
YELLOW  := \033[0;33m
BLUE    := \033[0;34m
PINK    := \033[0;35m
CYAN    := \033[0;36m
endif

# Common build print status function
define print
  @$(PRINT) "$(GREEN)$(1) $(YELLOW)$(2)$(GREEN) -> $(BLUE)$(3)$(NO_COL)\n"
endef

#### Tools ####
ifneq ($(shell type $(MIPS_BINUTILS_PREFIX)ld >/dev/null 2>/dev/null; echo $$?), 0)
$(error Unable to find $(MIPS_BINUTILS_PREFIX)ld. Please install or build MIPS binutils, commonly mips-linux-gnu. (or set MIPS_BINUTILS_PREFIX if your MIPS binutils install uses another prefix))
endif


### Compiler ###

IDO             := $(TOOLS)/ido-static-recomp/build/5.3/out/cc
AS              := $(MIPS_BINUTILS_PREFIX)as
LD              := $(MIPS_BINUTILS_PREFIX)ld
OBJCOPY         := $(MIPS_BINUTILS_PREFIX)objcopy
OBJDUMP         := $(MIPS_BINUTILS_PREFIX)objdump
ICONV           := iconv
ASM_PROC        := $(PYTHON) $(TOOLS)/asm-processor/build.py
TORCH           := $(TOOLS)/Torch/cmake-build-release/torch
CRC             := $(TOOLS)/n64crc $(BUILD_DIR)/$(TARGET).$(VERSION).z64

# Prefer clang as C preprocessor if installed on the system
ifneq (,$(call find-command,clang))
  CPP      := clang
  CPPFLAGS := -E -P -x c -Wno-multichar -Wno-trigraphs -Wmissing-prototypes -Wstrict-prototypes -D_LANGUAGE_ASSEMBLY
else
  CPP      := cpp
  CPPFLAGS := -P -Wno-trigraphs -Wmissing-prototypes -Wstrict-prototypes -D_LANGUAGE_ASSEMBLY
endif

ASM_PROC_FLAGS  := --input-enc=utf-8 --output-enc=euc-jp --convert-statics=global-with-filename --drop-mdebug-gptab
OBJCOPY_FLAGS := -O binary --pad-to=0x1000000 --gap-fill=0xFF

SPLAT           ?= $(PYTHON) $(TOOLS)/splat/split.py
SPLAT_YAML      ?= config/$(VERSION)/$(TARGET).$(VERSION).yaml

DAISYBOX		 := $(TOOLS)/daisybox/daisybox

COMPTOOL		:= $(TOOLS)/comptool.py
COMPTOOL_DIR	:= baserom
MIO0			:= $(TOOLS)/mio0


IINC := -I include -I .
IINC += -I include/libc -I include/2.0I -I include/2.0I/PR -I include -I bin

ifeq ($(KEEP_MDEBUG),0)
  RM_MDEBUG = $(OBJCOPY) --remove-section .mdebug $@
else
  RM_MDEBUG = @:
endif

# Check code syntax with host compiler
CHECK_WARNINGS := -Wall -Wextra -Wimplicit-fallthrough -Wno-multichar -Wno-unknown-pragmas -Wno-missing-braces -Wno-sign-compare -Wno-uninitialized -Wno-multichar
# Have CC_CHECK pretend to be a MIPS compiler
MIPS_BUILTIN_DEFS := -DMIPSEB -D_MIPS_FPSET=16 -D_MIPS_ISA=2 -D_ABIO32=1 -D_MIPS_SIM=_ABIO32 -D_MIPS_SZINT=32 -D_MIPS_SZPTR=32
ifneq ($(RUN_CC_CHECK),0)
#   The -MMD flags additionaly creates a .d file with the same name as the .o file.
    CHECK_WARNINGS    := -Wno-unused-variable -Wno-int-conversion -Wno-multichar
    CC_CHECK          := $(CC_CHECK_COMP)
    CC_CHECK_FLAGS    := -MMD -MP -fno-builtin -fsyntax-only -funsigned-char -fdiagnostics-color -std=gnu89 -DNON_MATCHING -DAVOID_UB -D_FINALROM -DCC_CHECK=1

    # Ensure that gcc treats the code as 32-bit
    ifeq ($(UNAME_M),aarch64)
        CC_CHECK_FLAGS += -march=armv7-a+fp
    else
        CC_CHECK_FLAGS += -m32
    endif
	ifneq ($(WERROR), 0)
        CHECK_WARNINGS += -Werror
    endif
else
    CC_CHECK          := @:
endif

ASFLAGS         := -march=vr4300 -32 -G0
COMMON_DEFINES  := -D_MIPS_SZLONG=32
GBI_DEFINES     := -DF3DEX_GBI_2
RELEASE_DEFINES := -DNDEBUG
AS_DEFINES      := -DMIPSEB -D_LANGUAGE_ASSEMBLY -D_ULTRA64
C_DEFINES       := -D_FINALROM -DCOMPILING_LIBULTRA -DTARGET_N64 -DSSSV -DWIN32 -DLANGUAGE_C -D_LANGUAGE_C -D_FINALROM ${RELEASE_DEFINES}
ENDIAN          := -EB

ICONV_FLAGS     := --from-code=UTF-8 --to-code=EUC-JP

GENFORM0 := tools/genForm0

# Use relocations and abi fpr names in the dump
OBJDUMP_FLAGS := --disassemble --reloc --disassemble-zeroes -Mreg-names=32 -Mno-aliases

ifneq ($(OBJDUMP_BUILD), 0)
    OBJDUMP_CMD = $(OBJDUMP) $(OBJDUMP_FLAGS) $@ > $(@:.o=.dump.s)
    OBJCOPY_BIN = $(OBJCOPY) -O binary $@ $@.bin
else
    OBJDUMP_CMD = @:
    OBJCOPY_BIN = @:
endif

# rom compression flags
COMPFLAGS := --threads $(N_THREADS)
ifeq ($(NON_MATCHING),0)
    COMPFLAGS += --matching
endif

#### Files ####

$(shell mkdir -p asm bin linker_scripts/$(VERSION)/auto)

SRC_DIRS      := $(shell find src -type d)
# Temporary, until we decide how we're gonna handle other versions
ifeq ($(VERSION), jp)
SRC_DIRS      := $(shell find srcjp -type d)
endif
ifeq ($(VERSION), eu)
SRC_DIRS      := $(shell find srceu -type d)
endif
ASM_DIRS      := $(shell find asm/$(VERSION) -type d -not -path "asm/$(VERSION)/nonmatchings/*")
BIN_DIRS      := $(shell find bin -type d)


C_FILES       := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
C_FILES       := $(filter-out %.inc.c,$(C_FILES))
S_FILES       := $(foreach dir,$(ASM_DIRS) $(SRC_DIRS),$(wildcard $(dir)/*.s))
# Native readonly data is included by its C GLOBAL_ASM, not a separate object.
# Keep these exact paths aligned with their config/us/readonly_layout/*.json;
# tools/tests/test_readonly_make_inputs.py checks that contract and normal ASM.
S_FILES       := $(filter-out asm/us/data/modules/uvdyn_rom.rodata-prefix.s asm/us/data/modules/ted.rodata-prefix.s asm/us/data/modules/race.rodata-prefix.s asm/us/data/modules/race-floats.rodata-island.s,$(S_FILES))
BIN_FILES     := $(foreach dir,$(BIN_DIRS),$(wildcard $(dir)/*.bin))
O_FILES       := $(foreach f,$(C_FILES:.c=.o),$(BUILD_DIR)/$f) \
                 $(foreach f,$(S_FILES:.s=.o),$(BUILD_DIR)/$f) \
                 $(foreach f,$(BIN_FILES:.bin=.o),$(BUILD_DIR)/$f)

MODULE_C_DIR      := $(firstword $(filter %/modules,$(SRC_DIRS)))
MODULE_DATA_DIR   := asm/$(VERSION)/data/modules
# Fully recovered modules can have no remaining .data/.bss assembly files.
# Discover every module from the actual C translation units, including those.
MODULE_NAMES := $(sort $(patsubst %.c,%,$(notdir $(filter $(MODULE_C_DIR)/%.c,$(C_FILES)))))
PARTIAL_MODULE_OBJS := $(addprefix $(BUILD_DIR)/partial_,$(addsuffix .o,$(MODULE_NAMES)))
BIN_MODULE_OBJS := $(addprefix $(BUILD_DIR)/bin/us/,$(addsuffix .o,$(MODULE_NAMES)))

FORM0_JSON := config/$(VERSION)/form0.json

ifeq ($(NON_MATCHING),1)
CONV_PARTIAL_MOD = $(PYTHON) $(TOOLS)/convPartialModule.py $< True
else
CONV_PARTIAL_MOD = $(PYTHON) $(TOOLS)/convPartialModule.py $< False
endif

# Automatic dependency files
DEP_FILES := $(O_FILES:.o=.d) \
             $(O_FILES:.o=.asmproc.d)

# create build directories
$(shell mkdir -p $(BUILD_DIR)/linker_scripts/$(VERSION) $(BUILD_DIR)/linker_scripts/$(VERSION)/auto $(foreach dir,$(SRC_DIRS) $(ASM_DIRS) $(BIN_DIRS),$(BUILD_DIR)/$(dir)))

ifeq ($(COMPILER),ido)

$(BUILD_DIR)/src/libultra/os/%.o: OPTFLAGS := -O1
$(BUILD_DIR)/src/libultra/os/osVirtualtoPhysical.o: OPTFLAGS := -O1
$(BUILD_DIR)/src/libultra/gu/%.o: OPTFLAGS := -O3
$(BUILD_DIR)/src/libultra/io/%.o: OPTFLAGS := -O1
$(BUILD_DIR)/src/libultra/audio/%.o: OPTFLAGS := -O3
$(BUILD_DIR)/src/libultra/libc/%.o: OPTFLAGS := -O1

# File exceptions
$(BUILD_DIR)/src/libultra/gu/lookathil.o: OPTFLAGS := -O2
$(BUILD_DIR)/src/libultra/os/osVirtualtoPhysical.o: OPTFLAGS := -O1
$(BUILD_DIR)/src/libultra/libc/sprintf.o: OPTFLAGS := -O1
$(BUILD_DIR)/src/libultra/libc/sprintf.o: MIPS_VERSION := -mips2

$(BUILD_DIR)/libultra/libc/xprintf.o: OPTFLAGS := -O1
$(BUILD_DIR)/libultra/libc/xprintf.o: MIPS_VERSION := -mips2

$(BUILD_DIR)/src/libultra/io/vimgr.o: OPTFLAGS := -O2
$(BUILD_DIR)/src/libultra/io/vimgr.o: MIPS_VERSION := -mips2

$(BUILD_DIR)/src/libultra/io/pfsinit.o: OPTFLAGS := -O2
$(BUILD_DIR)/src/libultra/io/pfsinit.o: MIPS_VERSION := -mips1

$(BUILD_DIR)/src/libultra/io/pfsisplug.o: OPTFLAGS := -O2
$(BUILD_DIR)/src/libultra/io/pfsisplug.o: MIPS_VERSION := -mips1

$(BUILD_DIR)/src/libultra/io/pfssearchfile.o: OPTFLAGS := -O2
$(BUILD_DIR)/src/libultra/io/pfssearchfile.o: MIPS_VERSION := -mips1

$(BUILD_DIR)/src/libultra/io/pfsfreeblocks.o: OPTFLAGS := -O2
$(BUILD_DIR)/src/libultra/io/pfsfreeblocks.o: MIPS_VERSION := -mips1

$(BUILD_DIR)/src/libultra/io/pfsreadwritefile.o: OPTFLAGS := -O2
$(BUILD_DIR)/src/libultra/io/pfsreadwritefile.o: MIPS_VERSION := -mips1

$(BUILD_DIR)/src/libultra/io/pfsallocatefile.o: OPTFLAGS := -O2
$(BUILD_DIR)/src/libultra/io/pfsallocatefile.o: MIPS_VERSION := -mips1

$(BUILD_DIR)/src/libultra/io/pfsdeletefile.o: OPTFLAGS := -O2
$(BUILD_DIR)/src/libultra/io/pfsdeletefile.o: MIPS_VERSION := -mips1

$(BUILD_DIR)/src/libultra/io/pfsnumfiles.o: OPTFLAGS := -O2
$(BUILD_DIR)/src/libultra/io/pfsnumfiles.o: MIPS_VERSION := -mips1

$(BUILD_DIR)/src/libultra/io/pfsfilestate.o: OPTFLAGS := -O2
$(BUILD_DIR)/src/libultra/io/pfsfilestate.o: MIPS_VERSION := -mips1

$(BUILD_DIR)/src/libultra/io/pfs.o: OPTFLAGS := -O2
$(BUILD_DIR)/src/libultra/io/pfs.o: MIPS_VERSION := -mips1

$(BUILD_DIR)/src/libultra/io/pfschecker.o: OPTFLAGS := -O2
$(BUILD_DIR)/src/libultra/io/pfschecker.o: MIPS_VERSION := -mips1

$(BUILD_DIR)/src/libultra/io/contramread.o: OPTFLAGS := -O2
$(BUILD_DIR)/src/libultra/io/contramread.o: MIPS_VERSION := -mips1

$(BUILD_DIR)/src/libultra/io/contramwrite.o: OPTFLAGS := -O2
$(BUILD_DIR)/src/libultra/io/contramwrite.o: MIPS_VERSION := -mips1

$(BUILD_DIR)/src/libultra/io/controller.o: OPTFLAGS := -O2
$(BUILD_DIR)/src/libultra/io/controller.o: MIPS_VERSION := -mips1

$(BUILD_DIR)/src/libultra/libc/ll.o: OPTFLAGS := -O1 -g0
$(BUILD_DIR)/src/libultra/libc/ll.o: MIPS_VERSION := -mips3 -32

# cc & asm-processor
CC := $(ASM_PROC) $(ASM_PROC_FLAGS) $(IDO) -- $(AS) $(ASFLAGS) --
$(BUILD_DIR)/src/libultra/gu/lookatref.o: CC := $(IDO)
$(BUILD_DIR)/src/libultra/gu/ortho.o: CC := $(IDO)
$(BUILD_DIR)/src/libultra/gu/translate.o: CC := $(IDO)
$(BUILD_DIR)/src/libultra/gu/perspective.o: CC := $(IDO)
$(BUILD_DIR)/src/libultra/gu/mtxutil.o: CC := $(IDO)
$(BUILD_DIR)/src/libultra/gu/cosf.o: CC := $(IDO)
$(BUILD_DIR)/src/libultra/audio/bnkf.o: CC := $(IDO)
$(BUILD_DIR)/src/libultra/libc/ll.o: CC := $(IDO)

else # GCC

endif

all: finalrom

toolchain:
	@$(MAKE) -s -C $(TOOLS)

dependencies: tools
	@make -C tools
	@$(PYTHON) -m pip install -r tools/splat/requirements.txt #Install the splat dependencies
	@pip install mapfile_parser # Temporary fix for mapfile_parser

torch:
	@$(MAKE) -s -C $(TOOLS) torch
	rm -f torch.hash.yml

init:
	@$(MAKE) clean
	@$(MAKE) extract -j $(N_THREADS)
	@$(MAKE) finalrom -j $(N_THREADS)

WR := \n

finalrom: $(ROM)
ifneq ($(COMPARE),0)
	@sha1sum --status -c $(TARGET).$(VERSION).sha1 && \
	$(PRINT) "$(BLUE)$(TARGET).$(VERSION).z64$(NO_COL): $(GREEN)OK$(NO_COL)$(YELLOW) $(WR)" || \
	$(PRINT) "$(BLUE)$(TARGET).$(VERSION).z64 $(RED)FAILED$(NO_COL)\n\
	$(RED)ROM BUILT FINE BUT IT DOESN'T MATCH THE ORIGINAL.$(NO_COL)\n"
	@sha1sum --status -c $(TARGET).$(VERSION).sha1
endif


#### Main Targets ###

extract:
	@$(RM) -r asm/$(VERSION) bin/$(VERSION)
	@echo "Extracting..."
	@$(SPLAT) $(SPLAT_YAML)
	@$(PYTHON) tools/patchModules.py
	@$(PYTHON) tools/moduleExtract.py config/$(VERSION)/modules.yaml

assets:
	@echo "Extracting assets from ROM..."
	@$(TORCH) code $(BASEROM)
	@$(TORCH) header $(BASEROM)
	@$(TORCH) modding export $(BASEROM)

mod:
	@$(TORCH) modding import code $(BASEROM)

clean:
	rm -f torch.hash.yml
	@git clean -fdx asm/$(VERSION)
	@git clean -fdx bin/$(VERSION)
	@git clean -fdx build/
	@git clean -fdx src/assets/
	@git clean -fdx include/assets/
	@git clean -fdx linker_scripts/$(VERSION)/*.ld

  # temporary, remove when we start decompiling other versions
	@git clean -fdx bin/

format:
	@$(PYTHON) $(TOOLS)/format.py -j $(N_THREADS)

checkformat:
	@$(TOOLS)/check_format.sh -j $(N_THREADS)

# asm-differ expected object files
expected:
	mkdir -p expected/build
	rm -rf expected/build/
	cp -r build/ expected/build/

context:
	@echo "Generating ctx.c ..."
	@$(PYTHON) ./$(TOOLS)/m2ctx $(filter-out $@, $(MAKECMDGOALS))

disasm:
	@$(RM) -r asm/$(VERSION) bin/$(VERSION)
	@echo "Extracting..."
	@$(SPLAT) $(SPLAT_YAML) --disassemble-all

#### Various Recipes ####
# Build a recompilation-friendly ELF for N64Recomp: one relocatable section per module.
# Pulls the relocatable build/partial_*.o objects (NOT the packed build/bin/us/*.o blobs)
# and generates recomp.ld via tools/genRecompLd.py. UNTESTED -- see docs/recomp.md.
recomp: $(O_FILES) $(LD_SCRIPT) $(PARTIAL_MODULE_OBJS) pre-partial-link
	@echo "Generating recomp linker script (one relocatable section per module)"
	$(V)$(PYTHON) tools/genRecompLd.py $(LD_SCRIPT)
	@echo "Building recomp ELF"
	$(V)$(LD) $(LDFLAGS) --allow-multiple-definition -T linker_scripts/us/recomp.ld -T linker_scripts/$(VERSION)/hw_syms.txt -T linker_scripts/$(VERSION)/auto/undefined_funcs_auto.ld  -T linker_scripts/$(VERSION)/auto/undefined_syms_auto.ld -T linker_scripts/$(VERSION)/kernel_link_scripts_syms.txt -Map $(LD_MAP) -o build/recomp.elf

# Final ROM
$(ROM): $(ELF)
	$(call print,ELF->ROM:,$<,$@)
	$(V)$(OBJCOPY) $(OBJCOPY_FLAGS) $< $@
	$(call print,Fixing ROM CRC:,$<,$@)
	@$(CRC)

# Link
$(ELF): $(O_FILES) $(LD_SCRIPT) $(BIN_MODULE_OBJS)
	$(V)$(LD) $(LDFLAGS) -T $(LD_SCRIPT) \
		-T linker_scripts/$(VERSION)/auto/undefined_funcs_auto.ld  -T linker_scripts/$(VERSION)/auto/undefined_syms_auto.ld -T linker_scripts/$(VERSION)/kernel_link_scripts_syms.txt \
		-Map $(LD_MAP) -o $@

pre-partial-link: $(O_FILES) $(PARTIAL_MODULE_OBJS) $(LD_SCRIPT)
	@echo "Running pre-partial link..."
	$(GENFORM0) $(FORM0_JSON)
	$(V)$(OBJCOPY) -I binary -O elf32-big build/FORM0.generated.uvft build/bin/us/FORM0.o
	$(V)$(PYTHON) tools/genKernelLd.py $(LD_SCRIPT)
	$(V)$(LD) $(LDFLAGS) -T $(KERNEL_LD_SCRIPT) \
		-T linker_scripts/$(VERSION)/auto/undefined_funcs_auto.ld  -T linker_scripts/$(VERSION)/auto/undefined_syms_auto.ld \
		-Map $(BUILD_DIR)/kernel.map -o $(BUILD_DIR)/kernel.elf
	$(V)$(PYTHON) tools/createKernelLinkSyms.py $(BUILD_DIR)/kernel.map  linker_scripts/$(VERSION)/kernel_link_scripts_syms.txt $(if $(wildcard linker_scripts/$(VERSION)/local_matching_aliases.ld),--aliases linker_scripts/$(VERSION)/local_matching_aliases.ld)
	$(V)$(PYTHON) tools/kernelMapJson.py $(BUILD_DIR)/kernel.map $(BUILD_DIR)/kernel.map.json

# Discover section inputs from current sources. Stale generated objects must not
# reintroduce sections whose ownership has moved into the C translation unit.
.SECONDEXPANSION:
$(BUILD_DIR)/partial_%.o: \
    $(BUILD_DIR)/$(MODULE_C_DIR)/%.o \
    $$(addprefix $(BUILD_DIR)/,$$(addsuffix .o,$$(basename $$(wildcard $(MODULE_DATA_DIR)/$$*.rodata.s)))) \
    $$(addprefix $(BUILD_DIR)/,$$(addsuffix .o,$$(basename $$(wildcard $(MODULE_DATA_DIR)/$$*.data.s)))) \
    $$(addprefix $(BUILD_DIR)/,$$(addsuffix .o,$$(basename $$(wildcard $(MODULE_DATA_DIR)/$$*.bss.s)))) \
    $$(wildcard linker_scripts/$(VERSION)/module_files/$$*_partial_aliases.ld)
	$(call print,PartialLinking:,$^,$@)
	$(LD) -r $(filter %.o,$^) $(foreach alias,$(filter %_partial_aliases.ld,$^),-T $(alias)) -Map $(@:.o=.map) -o $@

$(BUILD_DIR)/bin/us/%.o: $(BUILD_DIR)/partial_%.o pre-partial-link
	$(call print,ConvertModule:,$<,$@)
	$(CONV_PARTIAL_MOD)

# PreProcessor
$(BUILD_DIR)/%.ld: %.ld
	$(call print,PreProcessor:,$<,$@)
	$(V)$(CPP) $(CPPFLAGS) $(BUILD_DEFINES) $(IINC) $< > $@

# Binary
$(BUILD_DIR)/%.o: %.bin
	$(call print,Binary:,$<,$@)
	$(V)$(OBJCOPY) -I binary -O elf32-big $< $@

# Assembly
$(BUILD_DIR)/%.o: %.s
	$(call print,Assembling:,$<,$@)
	$(V)$(CPP) $(CPPFLAGS) $(BUILD_DEFINES) $(IINC) -I $(dir $*) $(COMMON_DEFINES) $(RELEASE_DEFINES) $(GBI_DEFINES) $(AS_DEFINES) $< | $(ICONV) $(ICONV_FLAGS) | $(AS) $(ASFLAGS) $(ENDIAN) $(IINC) -I $(dir $*) -o $@
	$(V)$(OBJDUMP_CMD)

# Exact VERSION_I SDK context for the forty-six byte-proven audio translation units.
SDK_AUDIO_SOURCES := src/libultra/audio/csplayer.c src/libultra/audio/cseq.c src/libultra/audio/seqplayer.c src/libultra/audio/reverb.c src/libultra/audio/load.c src/libultra/audio/env.c src/libultra/audio/auxbus.c src/libultra/audio/cents2ratio.c src/libultra/audio/copy.c src/libultra/audio/drvrnew.c src/libultra/audio/event.c src/libultra/audio/filter.c src/libultra/audio/heapalloc.c src/libultra/audio/heapinit.c src/libultra/audio/mainbus.c src/libultra/audio/resample.c src/libultra/audio/save.c src/libultra/audio/seq.c src/libultra/audio/sl.c src/libultra/audio/sndpallocate.c src/libultra/audio/sndpdeallocate.c src/libultra/audio/sndpdelete.c src/libultra/audio/sndpgetstate.c src/libultra/audio/sndplayer.c src/libultra/audio/sndpplay.c src/libultra/audio/sndpplayat.c src/libultra/audio/sndpsetfxmix.c src/libultra/audio/sndpsetpan.c src/libultra/audio/sndpsetpitch.c src/libultra/audio/sndpsetsound.c src/libultra/audio/sndpsetvol.c src/libultra/audio/sndpstop.c src/libultra/audio/synaddplayer.c src/libultra/audio/synallocfx.c src/libultra/audio/synallocvoice.c src/libultra/audio/synfreevoice.c src/libultra/audio/syngetfxref.c src/libultra/audio/synremoveplayer.c src/libultra/audio/synsetfxmix.c src/libultra/audio/synsetfxparam.c src/libultra/audio/synsetpan.c src/libultra/audio/synsetpitch.c src/libultra/audio/synsetvol.c src/libultra/audio/synstartvoice.c src/libultra/audio/synstartvoiceparam.c src/libultra/audio/synstopvoice.c
# Native-matched sequence-player unlink routine; retain the existing fixed audio recipe.
SDK_AUDIO_SOURCES += src/libultra/audio/seqpdelete.c
SDK_AUDIO_OBJECTS := $(addprefix $(BUILD_DIR)/,$(SDK_AUDIO_SOURCES:.c=.o))
SDK_AUDIO_CC := $(TOOLS)/ido-static-recomp/build/5.3/out/cc
SDK_AUDIO_FLAGS := -c -Wab,-r4300_mul -G 0 -nostdinc -Xcpluscomm -fullwarn -woff 516,649,838,712 -non_shared -mips2 -o32 -EB -O3 -D_MIPS_SZLONG=32 -DF3DEX_GBI -DBUILD_VERSION=VERSION_I -DBUILD_VERSION_STRING=\"2.0I\" -D_FINALROM -DNDEBUG -Iinclude/libultra-sdk -Iinclude/libultra-sdk/compiler/ido -Iinclude/libultra-sdk/PR -Iinclude/2.0I -Iinclude/2.0I/PR
SDK_AUDIO_HEADERS := include/2.0I/PR/gbi.h include/2.0I/PR/os_version.h include/libultra-sdk/PR/abi.h include/libultra-sdk/PR/libaudio.h include/libultra-sdk/PR/mbi.h include/libultra-sdk/PR/os.h include/libultra-sdk/PR/os_ai.h include/libultra-sdk/PR/os_cache.h include/libultra-sdk/PR/os_cont.h include/libultra-sdk/PR/os_convert.h include/libultra-sdk/PR/os_debug.h include/libultra-sdk/PR/os_eeprom.h include/libultra-sdk/PR/os_error.h include/libultra-sdk/PR/os_exception.h include/libultra-sdk/PR/os_flash.h include/libultra-sdk/PR/os_gbpak.h include/libultra-sdk/PR/os_gio.h include/libultra-sdk/PR/os_host.h include/libultra-sdk/PR/os_internal.h include/libultra-sdk/PR/os_internal_debug.h include/libultra-sdk/PR/os_internal_error.h include/libultra-sdk/PR/os_internal_exception.h include/libultra-sdk/PR/os_internal_gio.h include/libultra-sdk/PR/os_internal_host.h include/libultra-sdk/PR/os_internal_reg.h include/libultra-sdk/PR/os_internal_rsp.h include/libultra-sdk/PR/os_internal_si.h include/libultra-sdk/PR/os_internal_thread.h include/libultra-sdk/PR/os_internal_tlb.h include/libultra-sdk/PR/os_libc.h include/libultra-sdk/PR/os_message.h include/libultra-sdk/PR/os_motor.h include/libultra-sdk/PR/os_pfs.h include/libultra-sdk/PR/os_pi.h include/libultra-sdk/PR/os_rdp.h include/libultra-sdk/PR/os_reg.h include/libultra-sdk/PR/os_rsp.h include/libultra-sdk/PR/os_si.h include/libultra-sdk/PR/os_system.h include/libultra-sdk/PR/os_thread.h include/libultra-sdk/PR/os_time.h include/libultra-sdk/PR/os_tlb.h include/libultra-sdk/PR/os_vi.h include/libultra-sdk/PR/os_voice.h include/libultra-sdk/PR/ultraerror.h include/libultra-sdk/PR/ultratypes.h include/libultra-sdk/assert.h src/libultra/audio/cseq.h src/libultra/audio/cseqp.h src/libultra/audio/seqp.h include/libultra-sdk/PR/R4300.h include/libultra-sdk/compiler/ido/math.h include/libultra-sdk/compiler/ido/stdio.h src/libultra/audio/initfx.h src/libultra/audio/seq.h src/libultra/audio/synthInternals.h src/libultra/audio/sndp.h
$(SDK_AUDIO_OBJECTS): $(BUILD_DIR)/%.o: %.c $(SDK_AUDIO_HEADERS)
	$(V)mkdir -p $(@D)
	$(V)$(SDK_AUDIO_CC) $(SDK_AUDIO_FLAGS) -o $@ $<

# The declared RACE island is restored after IDO/asm-processor compilation.
$(BUILD_DIR)/src/modules/race.o: RACE_READONLY_LAYOUT := config/us/readonly_layout/race.json
$(BUILD_DIR)/src/modules/race.o: tools/reorderRaceReadonly.py tools/moduleReadonlyLayout.py config/us/readonly_layout/race.json

# C
$(BUILD_DIR)/%.o: %.c
	$(call print,Compiling:,$<,$@)
	$(V)$(CC_CHECK) $(CC_CHECK_FLAGS) $(IINC) -I $(dir $*) $(CHECK_WARNINGS) $(BUILD_DEFINES) $(COMMON_DEFINES) $(RELEASE_DEFINES) $(GBI_DEFINES) $(C_DEFINES) $(MIPS_BUILTIN_DEFS) -o $@ $<
	$(V)$(CC) -c $(CFLAGS) $(BUILD_DEFINES) $(IINC) $(WARNINGS) $(MIPS_VERSION) $(ENDIAN) $(COMMON_DEFINES) $(RELEASE_DEFINES) $(GBI_DEFINES) $(C_DEFINES) $(OPTFLAGS) -o $@ $<
#	Remove gptab sections if present
	-$(V)$(OBJCOPY) --remove-section .gptab.bss $@
	-$(V)$(OBJCOPY) --remove-section .gptab.data $@
	$(if $(RACE_READONLY_LAYOUT),$(V)$(PYTHON) tools/reorderRaceReadonly.py --root . --layout $(RACE_READONLY_LAYOUT) --object $@)
	$(V)$(OBJDUMP_CMD)
	$(V)$(RM_MDEBUG)

# Patch ll.o
build/src/libultra/libc/ll.o: src/libultra/libc/ll.c $(TOOLS)/set_o32abi_bit.py
	$(call print,Patching:,$<,$@)
	@$(CC_CHECK) $(CC_CHECK_FLAGS) $(IINC) -I $(dir $*) $(CHECK_WARNINGS) $(BUILD_DEFINES) $(COMMON_DEFINES) $(RELEASE_DEFINES) $(GBI_DEFINES) $(C_DEFINES) $(MIPS_BUILTIN_DEFS) -o $@ $<
	$(V)$(SDK_AUDIO_CC) $(SDK_LL_FLAGS) -o $@ $<
	$(V)$(PYTHON) $(TOOLS)/set_o32abi_bit.py $@
	$(V)$(OBJDUMP_CMD)
	$(V)$(RM_MDEBUG)

-include $(DEP_FILES)

# Print target for debugging
print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true

.PHONY: all finalrom clean init extract expected format checkformat assets context disasm toolchain

# Four additional stock VERSION_I units: IO uses O1; libc uses O3.
SDK_NONAUDIO_LIBC_SOURCES := src/libultra/libc/ldiv.c src/libultra/libc/sprintf.c src/libultra/libc/string.c
SDK_NONAUDIO_LIBC_OBJECTS := $(addprefix $(BUILD_DIR)/,$(SDK_NONAUDIO_LIBC_SOURCES:.c=.o))
SDK_NONAUDIO_HEADERS := include/libultra-sdk/PR/rcp.h include/libultra-sdk/compiler/ido/memory.h include/libultra-sdk/compiler/ido/stdarg.h include/libultra-sdk/compiler/ido/stdlib.h include/libultra-sdk/compiler/ido/string.h src/libultra/libc/xstdio.h
$(SDK_NONAUDIO_LIBC_OBJECTS): $(BUILD_DIR)/%.o: %.c $(SDK_AUDIO_HEADERS) $(SDK_NONAUDIO_HEADERS)
	$(V)mkdir -p $(dir $@)
	$(V)$(SDK_AUDIO_CC) $(SDK_AUDIO_FLAGS) -o $@ $<
$(BUILD_DIR)/src/libultra/io/ai.o: src/libultra/io/ai.c $(SDK_AUDIO_HEADERS) $(SDK_NONAUDIO_HEADERS)
	$(V)mkdir -p $(dir $@)
	$(V)$(SDK_AUDIO_CC) $(subst -O3,-O1,$(SDK_AUDIO_FLAGS)) -o $@ $<

# Stock VERSION_I controller status/query units; retained assembly owns their storage.
SDK_CONTROLLER_SOURCES := src/libultra/io/contquery.c src/libultra/io/contsetch.c
SDK_CONTROLLER_OBJECTS := $(addprefix $(BUILD_DIR)/,$(SDK_CONTROLLER_SOURCES:.c=.o))
SDK_CONTROLLER_HEADERS := include/2.0I/PR/os_version.h include/libultra-sdk/PR/R4300.h include/libultra-sdk/PR/os.h include/libultra-sdk/PR/os_ai.h include/libultra-sdk/PR/os_cache.h include/libultra-sdk/PR/os_cont.h include/libultra-sdk/PR/os_convert.h include/libultra-sdk/PR/os_debug.h include/libultra-sdk/PR/os_eeprom.h include/libultra-sdk/PR/os_error.h include/libultra-sdk/PR/os_exception.h include/libultra-sdk/PR/os_flash.h include/libultra-sdk/PR/os_gbpak.h include/libultra-sdk/PR/os_gio.h include/libultra-sdk/PR/os_host.h include/libultra-sdk/PR/os_internal.h include/libultra-sdk/PR/os_internal_debug.h include/libultra-sdk/PR/os_internal_error.h include/libultra-sdk/PR/os_internal_exception.h include/libultra-sdk/PR/os_internal_gio.h include/libultra-sdk/PR/os_internal_host.h include/libultra-sdk/PR/os_internal_reg.h include/libultra-sdk/PR/os_internal_rsp.h include/libultra-sdk/PR/os_internal_si.h include/libultra-sdk/PR/os_internal_thread.h include/libultra-sdk/PR/os_internal_tlb.h include/libultra-sdk/PR/os_libc.h include/libultra-sdk/PR/os_message.h include/libultra-sdk/PR/os_motor.h include/libultra-sdk/PR/os_pfs.h include/libultra-sdk/PR/os_pi.h include/libultra-sdk/PR/os_rdp.h include/libultra-sdk/PR/os_reg.h include/libultra-sdk/PR/os_rsp.h include/libultra-sdk/PR/os_si.h include/libultra-sdk/PR/os_system.h include/libultra-sdk/PR/os_thread.h include/libultra-sdk/PR/os_time.h include/libultra-sdk/PR/os_tlb.h include/libultra-sdk/PR/os_vi.h include/libultra-sdk/PR/os_voice.h include/libultra-sdk/PR/rcp.h include/libultra-sdk/PR/ultratypes.h include/libultra-sdk/PRinternal/controller.h include/libultra-sdk/PRinternal/macros.h include/libultra-sdk/PRinternal/siint.h
$(SDK_CONTROLLER_OBJECTS): $(BUILD_DIR)/%.o: %.c $(SDK_CONTROLLER_HEADERS)
	$(V)mkdir -p $(dir $@)
	$(V)$(SDK_AUDIO_CC) $(subst -O3,-O1,$(SDK_AUDIO_FLAGS)) -o $@ $<

# Original compact-sequence API units; exact VERSION_I/O3 native matches.
SDK_COMPACT_SEQUENCE_SOURCES := src/libultra/audio/cspgetchlvol.c src/libultra/audio/cspgetfxmix.c src/libultra/audio/cspgetpan.c src/libultra/audio/cspgetpriority.c src/libultra/audio/cspgetprogram.c src/libultra/audio/cspgetstate.c src/libultra/audio/cspgettempo.c src/libultra/audio/cspplay.c src/libultra/audio/cspsendmidi.c src/libultra/audio/cspsetbank.c src/libultra/audio/cspsetchlvol.c src/libultra/audio/cspsetfxmix.c src/libultra/audio/cspsetpan.c src/libultra/audio/cspsetpriority.c src/libultra/audio/cspsetprogram.c src/libultra/audio/cspsetseq.c src/libultra/audio/cspsettempo.c src/libultra/audio/cspsetvol.c src/libultra/audio/cspstop.c
SDK_COMPACT_SEQUENCE_OBJECTS := $(addprefix $(BUILD_DIR)/,$(SDK_COMPACT_SEQUENCE_SOURCES:.c=.o))
SDK_COMPACT_SEQUENCE_HEADERS := include/2.0I/PR/gbi.h include/libultra-sdk/PR/abi.h include/libultra-sdk/PR/libaudio.h include/libultra-sdk/PR/mbi.h include/libultra-sdk/PR/ultratypes.h src/libultra/audio/cseqp.h
$(SDK_COMPACT_SEQUENCE_OBJECTS): $(BUILD_DIR)/%.o: %.c $(SDK_COMPACT_SEQUENCE_HEADERS)
	$(V)mkdir -p $(dir $@)
	$(V)$(SDK_AUDIO_CC) $(SDK_AUDIO_FLAGS) -o $@ $<

# Stock LL special rule: retain the original O1/MIPS3/o32 recipe.
SDK_LL_FLAGS := $(subst -O3,-O1,$(subst -mips2,-mips3,$(subst -o32,-32,$(SDK_AUDIO_FLAGS))))

# Exact VERSION_I/O1 AI and PFS units; original storage stays assembly-owned.
SDK_RETAINED_STORAGE_SOURCES := src/libultra/io/aisetnextbuf.c src/libultra/io/pfsisplug.c
SDK_RETAINED_STORAGE_OBJECTS := $(addprefix $(BUILD_DIR)/,$(SDK_RETAINED_STORAGE_SOURCES:.c=.o))
SDK_RETAINED_STORAGE_HEADERS := include/2.0I/PR/os_version.h include/libultra-sdk/PR/R4300.h include/libultra-sdk/PR/os.h include/libultra-sdk/PR/os_ai.h include/libultra-sdk/PR/os_cache.h include/libultra-sdk/PR/os_cont.h include/libultra-sdk/PR/os_convert.h include/libultra-sdk/PR/os_debug.h include/libultra-sdk/PR/os_eeprom.h include/libultra-sdk/PR/os_error.h include/libultra-sdk/PR/os_exception.h include/libultra-sdk/PR/os_flash.h include/libultra-sdk/PR/os_gbpak.h include/libultra-sdk/PR/os_gio.h include/libultra-sdk/PR/os_host.h include/libultra-sdk/PR/os_internal.h include/libultra-sdk/PR/os_internal_debug.h include/libultra-sdk/PR/os_internal_error.h include/libultra-sdk/PR/os_internal_exception.h include/libultra-sdk/PR/os_internal_gio.h include/libultra-sdk/PR/os_internal_host.h include/libultra-sdk/PR/os_internal_reg.h include/libultra-sdk/PR/os_internal_rsp.h include/libultra-sdk/PR/os_internal_si.h include/libultra-sdk/PR/os_internal_thread.h include/libultra-sdk/PR/os_internal_tlb.h include/libultra-sdk/PR/os_libc.h include/libultra-sdk/PR/os_message.h include/libultra-sdk/PR/os_motor.h include/libultra-sdk/PR/os_pfs.h include/libultra-sdk/PR/os_pi.h include/libultra-sdk/PR/os_rdp.h include/libultra-sdk/PR/os_reg.h include/libultra-sdk/PR/os_rsp.h include/libultra-sdk/PR/os_si.h include/libultra-sdk/PR/os_system.h include/libultra-sdk/PR/os_thread.h include/libultra-sdk/PR/os_time.h include/libultra-sdk/PR/os_tlb.h include/libultra-sdk/PR/os_vi.h include/libultra-sdk/PR/os_voice.h include/libultra-sdk/PR/rcp.h include/libultra-sdk/PR/ultraerror.h include/libultra-sdk/PR/ultratypes.h include/libultra-sdk/PRinternal/controller.h include/libultra-sdk/PRinternal/macros.h include/libultra-sdk/PRinternal/osint.h include/libultra-sdk/PRinternal/siint.h
$(SDK_RETAINED_STORAGE_OBJECTS): $(BUILD_DIR)/%.o: %.c $(SDK_RETAINED_STORAGE_HEADERS)
	$(V)mkdir -p $(dir $@)
	$(V)$(SDK_AUDIO_CC) $(subst -O3,-O1,$(SDK_AUDIO_FLAGS)) -o $@ $<

# Two native-matched SDK kernel units; the tested VERSION_I/IDO5.3/O1 recipe.
SDK_THREAD_VTOP_SOURCES := src/libultra/os/stopthread.c src/libultra/os/osVirtualtoPhysical.c
SDK_THREAD_VTOP_OBJECTS := $(addprefix $(BUILD_DIR)/,$(SDK_THREAD_VTOP_SOURCES:.c=.o))
$(SDK_THREAD_VTOP_OBJECTS): $(BUILD_DIR)/%.o: %.c $(SDK_AUDIO_HEADERS) $(SDK_RETAINED_STORAGE_HEADERS)
	$(V)mkdir -p $(dir $@)
	$(V)$(SDK_AUDIO_CC) $(subst -O3,-O1,$(SDK_AUDIO_FLAGS)) -o $@ $<

# Three native-matched SDK units; retain the tested VERSION_I/IDO5.3/O1 recipe.
SDK_PRIORITY_TIME_YIELD_SOURCES := src/libultra/os/getthreadpri.c src/libultra/os/gettime.c src/libultra/os/yieldthread.c
SDK_PRIORITY_TIME_YIELD_OBJECTS := $(addprefix $(BUILD_DIR)/,$(SDK_PRIORITY_TIME_YIELD_SOURCES:.c=.o))
$(SDK_PRIORITY_TIME_YIELD_OBJECTS): $(BUILD_DIR)/%.o: %.c $(SDK_AUDIO_HEADERS) $(SDK_RETAINED_STORAGE_HEADERS)
	$(V)mkdir -p $(dir $@)
	$(V)$(SDK_AUDIO_CC) $(subst -O3,-O1,$(SDK_AUDIO_FLAGS)) -o $@ $<

# Eighteen native-matched SDK I/O and thread units; retain the fixed IDO5.3/O1 recipe.
SDK_IO_THREAD_SOURCES := src/libultra/io/spsetstat.c src/libultra/io/spsetpc.c src/libultra/io/sprawdma.c src/libultra/io/sp.c src/libultra/io/spgetstat.c src/libultra/io/sirawread.c src/libultra/io/sirawwrite.c src/libultra/io/vigetcurrcontext.c src/libultra/io/pigetcmdq.c src/libultra/os/resetglobalintmask.c src/libultra/os/setglobalintmask.c src/libultra/os/destroythread.c src/libultra/os/setthreadpri.c src/libultra/os/jammesg.c src/libultra/os/settimer.c src/libultra/io/aisetfreq.c src/libultra/io/pidma.c src/libultra/io/si.c
SDK_IO_THREAD_OBJECTS := $(addprefix $(BUILD_DIR)/,$(SDK_IO_THREAD_SOURCES:.c=.o))
$(SDK_IO_THREAD_OBJECTS): $(BUILD_DIR)/%.o: %.c $(SDK_AUDIO_HEADERS) $(SDK_RETAINED_STORAGE_HEADERS)
	$(V)mkdir -p $(dir $@)
	$(V)$(SDK_AUDIO_CC) $(subst -O3,-O1,$(SDK_AUDIO_FLAGS)) -o $@ $<

# Native-matched PI/SI access units; retain stock grouping, storage and fixed IDO5.3/O1.
SDK_ACCESS_SOURCES := src/libultra/io/piacs.c src/libultra/io/siacs.c
SDK_ACCESS_OBJECTS := $(addprefix $(BUILD_DIR)/,$(SDK_ACCESS_SOURCES:.c=.o))
$(SDK_ACCESS_OBJECTS): $(BUILD_DIR)/%.o: %.c $(SDK_AUDIO_HEADERS) $(SDK_RETAINED_STORAGE_HEADERS)
	$(V)mkdir -p $(dir $@)
	$(V)$(SDK_AUDIO_CC) $(subst -O3,-O1,$(SDK_AUDIO_FLAGS)) -o $@ $<

# Mixed timer unit: retain 140 bytes of initializer assembly before three matched C routines.
$(BUILD_DIR)/src/libultra/os/timerintr.o: src/libultra/os/timerintr.c $(SDK_AUDIO_HEADERS) $(SDK_RETAINED_STORAGE_HEADERS) tools/asm-processor/build.py tools/asm-processor/asm_processor.py asm/nonmatchings/libultra/os/timerintr/__osTimerServicesInit.s tools/asm-processor/prelude.inc
	$(V)mkdir -p $(dir $@)
	$(V)$(ASM_PROC) $(ASM_PROC_FLAGS) $(SDK_AUDIO_CC) -- $(AS) $(ASFLAGS) -- $(subst -O3,-O1,$(SDK_AUDIO_FLAGS)) -o $@ $<

# Native-matched PI raw I/O: fixed IDO O1 recipe, retained stock source coordinates.
$(BUILD_DIR)/src/libultra/io/pirawread.o: src/libultra/io/pirawread.c $(SDK_AUDIO_HEADERS) $(SDK_RETAINED_STORAGE_HEADERS) tools/asm-processor/build.py tools/asm-processor/asm_processor.py tools/asm-processor/prelude.inc
	$(V)mkdir -p $(dir $@)
	$(V)$(ASM_PROC) $(ASM_PROC_FLAGS) $(SDK_AUDIO_CC) -- $(AS) $(ASFLAGS) -- $(subst -O3,-O1,$(SDK_AUDIO_FLAGS)) -o $@ $<
$(BUILD_DIR)/src/libultra/io/pirawdma_pair.o: src/libultra/io/pirawdma_pair.c $(SDK_AUDIO_HEADERS) $(SDK_RETAINED_STORAGE_HEADERS) tools/asm-processor/build.py tools/asm-processor/asm_processor.py tools/asm-processor/prelude.inc
	$(V)mkdir -p $(dir $@)
	$(V)$(ASM_PROC) $(ASM_PROC_FLAGS) $(SDK_AUDIO_CC) -- $(AS) $(ASFLAGS) -- $(subst -O3,-O1,$(SDK_AUDIO_FLAGS)) -o $@ $<
$(BUILD_DIR)/src/libultra/io/epirawio.o: src/libultra/io/epirawio.c $(SDK_AUDIO_HEADERS) $(SDK_RETAINED_STORAGE_HEADERS) tools/asm-processor/build.py tools/asm-processor/asm_processor.py tools/asm-processor/prelude.inc
	$(V)mkdir -p $(dir $@)
	$(V)$(ASM_PROC) $(ASM_PROC_FLAGS) $(SDK_AUDIO_CC) -- $(AS) $(ASFLAGS) -- $(subst -O3,-O1,$(SDK_AUDIO_FLAGS)) -o $@ $<

# Controller-read group uses fixed IDO5.3 O2 with the original shared packet storage.
$(BUILD_DIR)/src/libultra/io/contreaddata.o: src/libultra/io/contreaddata.c $(SDK_AUDIO_HEADERS) $(SDK_CONTROLLER_HEADERS) tools/asm-processor/build.py tools/asm-processor/asm_processor.py tools/asm-processor/prelude.inc
	$(V)mkdir -p $(dir $@)
	$(V)$(ASM_PROC) $(ASM_PROC_FLAGS) $(SDK_AUDIO_CC) -- $(AS) $(ASFLAGS) -- $(subst -O3,-O2,$(SDK_AUDIO_FLAGS)) -o $@ $<

# Native-matched VI routines use the J-or-later branch with explicit per-unit optimization.
# Existing VI context and mode storage remains owned by the original assembly/data.
SDK_VI_J_FLAGS := $(subst -DBUILD_VERSION_STRING=\"2.0I\",-DBUILD_VERSION_STRING=\"2.0J\",$(subst -DBUILD_VERSION=VERSION_I,-DBUILD_VERSION=VERSION_J,$(SDK_AUDIO_FLAGS)))
$(BUILD_DIR)/src/libultra/io/vi.o: src/libultra/io/vi.c $(SDK_AUDIO_HEADERS) $(SDK_CONTROLLER_HEADERS) include/2.0I/PRinternal/viint.h tools/asm-processor/build.py tools/asm-processor/asm_processor.py tools/asm-processor/prelude.inc
	$(V)mkdir -p $(dir $@)
	$(V)$(ASM_PROC) $(ASM_PROC_FLAGS) $(SDK_AUDIO_CC) -- $(AS) $(ASFLAGS) -- $(subst -O3,-O1,$(SDK_VI_J_FLAGS)) -o $@ $<
$(BUILD_DIR)/src/libultra/io/viswapcontext.o: src/libultra/io/viswapcontext.c $(SDK_AUDIO_HEADERS) $(SDK_CONTROLLER_HEADERS) include/2.0I/PRinternal/viint.h tools/asm-processor/build.py tools/asm-processor/asm_processor.py tools/asm-processor/prelude.inc
	$(V)mkdir -p $(dir $@)
	$(V)$(ASM_PROC) $(ASM_PROC_FLAGS) $(SDK_AUDIO_CC) -- $(AS) $(ASFLAGS) -- $(subst -O3,-O2,$(SDK_VI_J_FLAGS)) -o $@ $<
