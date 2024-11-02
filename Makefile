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
	@$(AS) $(ASFLAGS) $$< -o $$@

# Rule to compile .asm files to .o files
$$($(1)_DIR)/%.o: $$($(1)_DIR)/%.asm
	@$(AS) $(ASFLAGS) $$< -o $$@

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

.PHONY: all clean

define build_docker =


endef

EZ80_CLANG_TOOLCHAIN_VERSION := $(shell source ./version.sh && echo $$EZ80_CLANG_TOOLCHAIN_VERSION)
TARGET := ez0-clang-$(EZ80_CLANG_TOOLCHAIN_VERSION).tar.gz

$(TARGET):
	@./build-docker.sh

package: $(TARGET)

install:
	@cd tmp/direct/ez80-clang-${EZ80_CLANG_TOOLCHAIN_VERSION} && ./install.sh
