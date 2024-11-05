MAKEFLAGS += --no-builtin-rules
SHELL=/bin/bash
BASH_ENV=~/.ez80-clang
BASH_ENV=version.sh

# Define directories
SRC_DIR := src
LIB_DIR := lib

# Define the assembler and archiver
AS := ez80-as
AR := ez80-ar
CLANG := ez80-clang

# Define the assembler flags
ASFLAGS := -march=ez80+full
CFLAGS  := -ffunction-sections -fdata-sections -nostdinc -Wall -Wextra -Wunreachable-code -Werror -mllvm -z80-print-zero-offset -S -Oz



# $1 -> library name & directory name
# $2 -> optional ASFLAGS
define build_lib =
$(1)_LIB_FILE := $(LIB_DIR)/lib$(1).a

all: $$($(1)_LIB_FILE)

$(1)_DIR := $$(SRC_DIR)/$(1)
$(1)_ASM_FILES := $$(wildcard $$($(1)_DIR)/*.asm)
$(1)_C_FILES := $$(wildcard $$($(1)_DIR)/*.c)
$(1)_S_FILES := $$($(1)_C_FILES:.c=.s)
$(1)_O_FILES := $$($(1)_C_FILES:.c=.o) $$($(1)_ASM_FILES:.asm=.o)

$$($(1)_DIR)/%.s: $$($(1)_DIR)/%.c
	@$(CLANG) $(CFLAGS) $$< -o $$@

# Rule to compile .c files to .s files
$$($(1)_DIR)/%.s: $$($(1)_DIR)/%.c
	@$(CLANG) $(CFLAGS) $$< -o $$@

# Rule to compile .asm files to .o files
$$($(1)_DIR)/%.o: $$($(1)_DIR)/%.s
	@$(AS) $(ASFLAGS) $(2) $$< -o $$@

# Rule to compile .asm files to .o files
$$($(1)_DIR)/%.o: $$($(1)_DIR)/%.asm
	@$(AS) $(ASFLAGS) $(2) $$< -o $$@

# Rule to create the library file
$$($(1)_LIB_FILE): $$($(1)_O_FILES)
	@mkdir -p $(LIB_DIR)
	@$(AR) rcs $$@ $$^

.SECONDARY: $$($(1)_S_FILES)

$(1)_clean:
	@rm -f $$($(1)_O_FILES) $$($(1)_LIB_FILE) $$($(1)_S_FILES)

clean: $(1)_clean

endef

$(eval $(call build_lib,ez80))
$(eval $(call build_lib,crt))
$(eval $(call build_lib,libc))
$(eval $(call build_lib,cpm))
$(eval $(call build_lib,v99x8-hdmi,--defsym ENABLE_DELAY=0))
$(eval $(call build_lib,v99x8-standard,--defsym ENABLE_DELAY=1))

.PHONY: all clean

V99X8_DIR := $(SRC_DIR)/v99x8
V99X8_ASM_FILES := $(wildcard $(V99X8_DIR)/*.asm)
V99X8_C_FILES := $(wildcard $(V99X8_DIR)/*.c)

V99X8_HDMI_DIR := $(SRC_DIR)/v99x8-hdmi
V99X8_HDMI_ASM_FILES := $(patsubst $(V99X8_DIR)/%.asm, $(V99X8_HDMI_DIR)/%.asm, $(V99X8_ASM_FILES))
V99X8_HDMI_C_FILES := $(patsubst $(V99X8_DIR)/%.c, $(V99X8_HDMI_DIR)/%.c, $(V99X8_C_FILES))
V99X8_HDMI_S_FILES := $(V99X8_HDMI_C_FILES:.c=.s)
V99X8_HDMI_O_FILES := $(V99X8_HDMI_ASM_FILES:.asm=.o) $(V99X8_HDMI_C_FILES:.asm=.o)
$(V99X8_HDMI_DIR)/%.asm: $(V99X8_DIR)/%.asm
	@mkdir -p $(V99X8_HDMI_DIR)
	@echo -e '\t.assume\tadl = 1\n\n\tsection\t.text,"ax",@progbits\n\n\tinclude "$<"' > $@
$(V99X8_HDMI_DIR)/%.c: $(V99X8_DIR)/%.c
	@mkdir -p $(V99X8_HDMI_DIR)
	@echo -e '\t#include "../v99x8/v99x8.c"' > $@
lib/libv99x8-hdmi.a: $(V99X8_HDMI_S_FILES) $(V99X8_HDMI_O_FILES)
.SECONDARY: $(V99X8_HDMI_ASM_FILES)

V99X8_STANDARD_DIR := $(SRC_DIR)/v99x8-standard
V99X8_STANDARD_ASM_FILES := $(patsubst $(V99X8_DIR)/%.asm, $(V99X8_STANDARD_DIR)/%.asm, $(V99X8_ASM_FILES))
V99X8_STANDARD_C_FILES := $(patsubst $(V99X8_DIR)/%.c, $(V99X8_STANDARD_DIR)/%.c, $(V99X8_C_FILES))
V99X8_STANDARD_S_FILES := $(V99X8_STANDARD_C_FILES:.c=.s)
V99X8_STANDARD_O_FILES := $(V99X8_STANDARD_ASM_FILES:.asm=.o) $(V99X8_STANDARD_C_FILES:.asm=.o)
$(V99X8_STANDARD_DIR)/%.asm: $(V99X8_DIR)/%.asm
	@mkdir -p $(V99X8_STANDARD_DIR)
	@echo -e '\t.assume\tadl = 1\n\n\tsection\t.text,"ax",@progbits\n\n\tinclude "$<"' > $@
$(V99X8_STANDARD_DIR)/%.c: $(V99X8_DIR)/%.c
	@mkdir -p $(V99X8_STANDARD_DIR)
	@echo -e '\t#include "../v99x8/v99x8.c"' > $@
lib/libv99x8-standard.a: $(V99X8_STANDARD_S_FILES) $(V99X8_STANDARD_O_FILES)
.SECONDARY: $(V99X8_STANDARD_ASM_FILES)


EZ80_CLANG_TOOLCHAIN_VERSION := $(shell source ./version.sh && echo $$EZ80_CLANG_TOOLCHAIN_VERSION)
TARGET := ez0-clang-$(EZ80_CLANG_TOOLCHAIN_VERSION).tar.gz

$(TARGET):
	@./build-docker.sh

package: $(TARGET)

install:
	@cd tmp/direct/ez80-clang-${EZ80_CLANG_TOOLCHAIN_VERSION} && ./install.sh

format:
	@./clang-format.sh
