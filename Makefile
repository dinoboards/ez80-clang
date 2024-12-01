MAKEFLAGS += --no-builtin-rules
SHELL=/bin/bash
BASH_ENV=~/.ez80-clang
BASH_ENV=version.sh

export PATH := ./tmp/opt/ez80-clang/bin:$(PATH)
# Define the system include path
export EZ80_CLANG_SYSTEM_INCLUDE_PATH := $(PWD)/tmp/opt/ez80-clang/include -isystem $(PWD)/include

# Define directories
SRC_DIR := src
LIB_DIR := lib

# Define the assembler and archive
AS := ez80-as
AR := ez80-ar
CLANG := ez80-clang

# Define the assembler flags
ASFLAGS := -march=ez80+full
CFLAGS  := -ffunction-sections -fdata-sections -nostdinc -Wall -Wextra -Wunreachable-code -Werror -mllvm -z80-print-zero-offset -S -Oz


# $1 -> library name & directory name
# $2 -> optional ASFLAGS
# $3 -> optional CFLAGS
define build_lib =
$(1)_LIB_FILE := $(LIB_DIR)/lib$(1).a

all: $$($(1)_LIB_FILE)

$(1)_DIR := $$(SRC_DIR)/$(1)
$(1)_ASM_FILES := $$(wildcard $$($(1)_DIR)/*.asm)
$(1)_C_FILES := $$(wildcard $$($(1)_DIR)/*.c)
$(1)_S_FILES := $$($(1)_C_FILES:.c=.s)
$(1)_O_FILES := $$($(1)_C_FILES:.c=.o) $$($(1)_ASM_FILES:.asm=.o)

$$($(1)_DIR)/%.s: $$($(1)_DIR)/%.c
	@$(CLANG) $(CFLAGS) $(3) $$< -o $$@

# Rule to compile .c files to .s files
$$($(1)_DIR)/%.s: $$($(1)_DIR)/%.c
	@$(CLANG) $(CFLAGS) $(3) $$< -o $$@

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

.PHONY: all clean

$(eval $(call build_lib,ez80))
$(eval $(call build_lib,crt))
$(eval $(call build_lib,crtexe))
$(eval $(call build_lib,libc))
$(eval $(call build_lib,cpm))
$(eval $(call build_lib,malloc))
$(eval $(call build_lib,io))
$(eval $(call build_lib,ez80rc))
$(eval $(call build_lib,v99x8-hdmi,--defsym ENABLE_DELAY=0))
$(eval $(call build_lib,v99x8-standard,--defsym ENABLE_DELAY=1))

EZ80_CLANG_VERSION := $(shell source ./version.sh && echo $$EZ80_CLANG_VERSION)
TARGET := ez0-clang-$(EZ80_CLANG_VERSION).tar.gz

extract-llvm-release:
	@./extract-clang.sh
	@cp ./direct-shims/* ./tmp/opt/ez80-clang/bin

download-llvm-release:
	@./download-clang.sh
	@cp ./direct-shims/* ./tmp/opt/ez80-clang/bin

docker:
	@./build-docker.sh

docker-push:
	@./push-docker.sh

$(TARGET):
	@./build-package.sh

package: $(TARGET)

package-local: format extract-llvm-release all $(TARGET)

install:
	@cd tmp/direct/ez80-clang-${EZ80_CLANG_VERSION} && ./install.sh

format:
	@./clang-format.sh

