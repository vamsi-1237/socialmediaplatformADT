# ===============================================
# Makefile for compiling sources across 'code/' and 'Subtask2/'
#
# TARGETS:
# 1. all: Builds code_app and subtask2_app (The new default).
# 2. code_app: Links ONLY files from code/ (e.g., main.c, post.c, etc.)
# 3. subtask2_app: Links ONLY files from Subtask2/ (e.g., 2a.c and 2b.c)
# ===============================================

# --- Directory Configuration ---

SRCDIR_1 = code
SRCDIR_2 = task2b
OBJDIR = obj
BINDIR = bin

# --- Executable Definitions ---

# Individual Targets (Files from one directory linked)
CODE_TARGET = $(BINDIR)/code_app
TASK2B_TARGET = $(BINDIR)/task2b_app

# --- Compiler and Flags ---
CC = gcc
CFLAGS = -Wall -g

# --- Find Sources and Objects ---

# 1. Find all C source files in the two directories
SOURCES_1 = $(wildcard $(SRCDIR_1)/*.c)
SOURCES_2 = $(wildcard $(SRCDIR_2)/*.c)

# 2. Define Object Files based on their source groups
# Objects for the individual 'code' build
CODE_OBJECTS = $(patsubst %.c,$(OBJDIR)/%.o,$(notdir $(SOURCES_1)))

# Objects for the individual 'Subtask2' build
TASK2B_OBJECTS = $(patsubst %.c,$(OBJDIR)/%.o,$(notdir $(SOURCES_2)))

# --- Targets ---

.PHONY: all clean setup code_app subtask2_app

# Default rule: set up directories and build all executables
all: setup $(CODE_TARGET) $(TASK2B_TARGET)

# Rule to create the bin and obj directories if they don't exist
setup:
	@mkdir -p $(OBJDIR) $(BINDIR)

# --- Linking Rules for Individual Executables ---

# Code App Rule
$(CODE_TARGET): $(CODE_OBJECTS)
	@echo "Linking Code App -> $@"
	$(CC) $(CFLAGS) $^ -o $@

# Task2B App Rule
$(TASK2B_TARGET): $(TASK2B_OBJECTS)
	@echo "Linking Task2B App -> $@"
	$(CC) $(CFLAGS) $^ -o $@

# --- Compilation Rules (How to build the .o files) ---
# These rules are general and apply to all object files.

# Pattern rule 1: Compiling C files coming from $(SRCDIR_1) (code)
$(OBJDIR)/%.o: $(SRCDIR_1)/%.c
	@echo "Compiling code/ $< -> $@"
	$(CC) $(CFLAGS) -c $< -o $@

# Pattern rule 2: Compiling C files coming from $(SRCDIR_2) (Task2B)
$(OBJDIR)/%.o: $(SRCDIR_2)/%.c
	@echo "Compiling Task2B/ $< -> $@"
	$(CC) $(CFLAGS) -c $< -o $@

# --- Cleanup ---

clean:
	@rm -rf $(OBJDIR) $(BINDIR)
	@echo "Cleaned up object files and all executables"
