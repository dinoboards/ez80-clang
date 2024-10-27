SHELL=/bin/bash
BASH_ENV=~/.ez80-clang-aliases

# Define directories
SRC_DIR := src
CRT_DIR := $(SRC_DIR)/crt
CLIB_DIR := $(SRC_DIR)/clib
LIB_DIR := lib

# Define the assembler and archiver
AS := ez80-as
AR := ez80-ar
CLANG := ez80-clang

# Define the assembler flags
ASFLAGS := -march=ez80+full -a=./crt.lst
CFLAGS := -nostdinc -Wall -Wextra -Wunreachable-code -Werror -mllvm -z80-print-zero-offset -S -O3

# Find all .asm files in the src directory
CRT_ASM_FILES := $(wildcard $(CRT_DIR)/*.asm)
CRT_C_FILES := $(wildcard $(CRT_DIR)/*.c)
CLIB_ASM_FILES := $(wildcard $(CLIB_DIR)/*.asm)
CLIB_C_FILES := $(wildcard $(CLIB_DIR)/*.c)

# Generate .s and .o file names
CRT_S_FILES := $(CRT_C_FILES:.c=.s)
CRT_O_FILES := $(CRT_C_FILES:.c=.o) $(CRT_ASM_FILES:.asm=.o)
CLIB_S_FILES := $(CLIB_C_FILES:.c=.s)
CLIB_O_FILES := $(CLIB_C_FILES:.c=.o) $(CLIB_ASM_FILES:.asm=.o)

# Define the library file
CRT_LIB_FILE := $(LIB_DIR)/libcrt.a
CLIB_LIB_FILE := $(LIB_DIR)/libclib.a

# Default target
all: $(CRT_LIB_FILE) $(CLIB_LIB_FILE)

# Rule to compile .c files to .s files for clib
$(CRT_DIR)/%.s: $(CRT_DIR)/%.c
	$(CLANG) $(CFLAGS) $< -o $@

# Rule to compile .asm files to .o files for clib
$(CRT_DIR)/%.o: $(CRT_DIR)/%.s
	$(AS) $(ASFLAGS) $< -o $@

# Rule to compile .asm files to .o files for crt
$(CRT_DIR)/%.o: $(CRT_DIR)/%.asm
	$(AS) $(ASFLAGS) $< -o $@

# Rule to create the crt library file
$(CRT_LIB_FILE): $(CRT_O_FILES)
	@mkdir -p $(LIB_DIR)
	$(AR) rcs $@ $^

.SUFFIXES:

# Rule to compile .c files to .s files for clib
$(CLIB_DIR)/%.s: $(CLIB_DIR)/%.c
	$(CLANG) $(CFLAGS) $< -o $@

# Rule to compile .asm files to .o files for clib
$(CLIB_DIR)/%.o: $(CLIB_DIR)/%.s
	$(AS) $(ASFLAGS) $< -o $@

# Rule to compile .asm files to .o files for clib
$(CLIB_DIR)/%.o: $(CLIB_DIR)/%.asm
	$(AS) $(ASFLAGS) $< -o $@

# Rule to create the clib library file
$(CLIB_LIB_FILE): $(CLIB_O_FILES)
	@mkdir -p $(LIB_DIR)
	$(AR) rcs $@ $^

.SECONDARY: $(CLIB_S_FILES)
.SECONDARY: $(CRT_S_FILES)


# Clean up generated files
clean:
	@rm -f $(CRT_O_FILES) $(CLIB_O_FILES) $(CRT_LIB_FILE) $(CLIB_LIB_FILE) $(CLIB_S_FILES) $(CRT_S_FILES)



.PHONY: all clean
