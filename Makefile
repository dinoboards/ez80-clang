SHELL=/bin/bash
BASH_ENV=~/.ez80-clang-aliases

# Define directories
SRC_DIR := src
LIB_DIR := lib

# Define the assembler and archiver
AS := ez80-as
AR := ez80-ar
CLANG := ez80-clang

# Define the assembler flags
ASFLAGS := -march=ez80+full
CFLAGS  := -ffunction-sections -fdata-sections -nostdinc -Wall -Wextra -Wunreachable-code -Werror -mllvm -z80-print-zero-offset -S  -Oz

# Find all .asm files in the src directory
CRT_DIR := $(SRC_DIR)/crt
CRT_ASM_FILES := $(wildcard $(CRT_DIR)/*.asm)
CRT_C_FILES := $(wildcard $(CRT_DIR)/*.c)
CRT_S_FILES := $(CRT_C_FILES:.c=.s)
CRT_O_FILES := $(CRT_C_FILES:.c=.o) $(CRT_ASM_FILES:.asm=.o)

LIBC_DIR := $(SRC_DIR)/libc
LIBC_ASM_FILES := $(wildcard $(LIBC_DIR)/*.asm)
LIBC_C_FILES := $(wildcard $(LIBC_DIR)/*.c)
LIBC_S_FILES := $(LIBC_C_FILES:.c=.s)
LIBC_O_FILES := $(LIBC_C_FILES:.c=.o) $(LIBC_ASM_FILES:.asm=.o)

CPM_DIR := $(SRC_DIR)/cpm
CPM_ASM_FILES := $(wildcard $(CPM_DIR)/*.asm)
CPM_C_FILES := $(wildcard $(CPM_DIR)/*.c)
CPM_S_FILES := $(CPM_C_FILES:.c=.s)
CPM_O_FILES := $(CPM_C_FILES:.c=.o) $(CPM_ASM_FILES:.asm=.o)

# Define the library file
CRT_LIB_FILE := $(LIB_DIR)/libcrt.a
LIBC_LIB_FILE := $(LIB_DIR)/liblibc.a
CPM_LIB_FILE := $(LIB_DIR)/libcpm.a

# Default target
all: $(CRT_LIB_FILE) $(LIBC_LIB_FILE) $(CPM_LIB_FILE)

.SUFFIXES:

$(CRT_DIR)/%.s: $(CRT_DIR)/%.c
	@$(CLANG) $(CFLAGS) $< -o $@

# Rule to compile .c files to .s files for crt
$(CRT_DIR)/%.s: $(CRT_DIR)/%.c
	@$(CLANG) $(CFLAGS) $< -o $@

# Rule to compile .asm files to .o files for crt
$(CRT_DIR)/%.o: $(CRT_DIR)/%.s
	@$(AS) $(ASFLAGS) $< -o $@

# Rule to compile .asm files to .o files for crt
$(CRT_DIR)/%.o: $(CRT_DIR)/%.asm
	@$(AS) $(ASFLAGS) $< -o $@

# Rule to create the crt library file
$(CRT_LIB_FILE): $(CRT_O_FILES)
	@mkdir -p $(LIB_DIR)
	@$(AR) rcs $@ $^

.SECONDARY: $(CRT_S_FILES)


# Rule to compile .c files to .s files for libc
$(LIBC_DIR)/%.s: $(LIBC_DIR)/%.c
	@$(CLANG) $(CFLAGS) $< -o $@

# Rule to compile .asm files to .o files for libc
$(LIBC_DIR)/%.o: $(LIBC_DIR)/%.s
	@$(AS) $(ASFLAGS) $< -o $@

# Rule to compile .asm files to .o files for libc
$(LIBC_DIR)/%.o: $(LIBC_DIR)/%.asm
	@$(AS) $(ASFLAGS) $< -o $@

# Rule to create the libc library file
$(LIBC_LIB_FILE): $(LIBC_O_FILES)
	@mkdir -p $(LIB_DIR)
	@$(AR) rcs $@ $^

.SECONDARY: $(LIBC_S_FILES)


# Rule to compile .c files to .s files for cpm
$(CPM_DIR)/%.s: $(CPM_DIR)/%.c
	@$(CLANG) $(CFLAGS) $< -o $@

# Rule to compile .asm files to .o files for cpm
$(CPM_DIR)/%.o: $(CPM_DIR)/%.s
	@$(AS) $(ASFLAGS) $< -o $@

# Rule to compile .asm files to .o files for cpm
$(CPM_DIR)/%.o: $(CPM_DIR)/%.asm
	@$(AS) $(ASFLAGS) $< -o $@

# Rule to create the CPM library file
$(CPM_LIB_FILE): $(CPM_O_FILES)
	@mkdir -p $(LIB_DIR)
	@$(AR) rcs $@ $^

.SECONDARY: $(CPM_S_FILES)

# Clean up generated files
clean:
	@rm -f $(CRT_O_FILES) $(CRT_LIB_FILE) $(CRT_S_FILES)
	rm -f $(LIBC_O_FILES) $(LIBC_LIB_FILE) $(LIBC_S_FILES)
	rm -f $(CPM_O_FILES) $(CPM_LIB_FILE) $(CPM_S_FILES)


.PHONY: all clean
