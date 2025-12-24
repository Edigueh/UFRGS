# Makefile for Competitive Programming
# Works dynamically with any C++ file in the CP directory

# ============================================================================
# CONFIGURATION
# ============================================================================

# Compiler detection (tries g++ first, then clang++)
CXX := $(shell command -v g++ 2> /dev/null || command -v clang++ 2> /dev/null)
ifeq ($(CXX),)
    $(error No C++ compiler found. Please install g++ or clang++)
endif

# C++ Standard
STD := c++17

# Include directories (for bits/stdc++.h)
INCLUDES := -I$(CURDIR)

# Compiler flags for competitive programming
CXXFLAGS := -std=$(STD) $(INCLUDES) -O2 -Wall -Wextra -Wshadow

# Debug flags
DEBUGFLAGS := -std=$(STD) $(INCLUDES) -g -O0 -Wall -Wextra -Wshadow -DDEBUG \
              -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG

# Output directory for binaries
BUILD_DIR := build

# ============================================================================
# FILE CONFIGURATION
# ============================================================================

# Default file if none specified
FILE ?= sandbox/sandbox.cpp

# Extract filename without extension
BASENAME := $(basename $(notdir $(FILE)))

# Output executable
OUTPUT := $(BUILD_DIR)/$(BASENAME)

# Input/Output files (optional)
IN ?=
OUT ?=

# ============================================================================
# TARGETS
# ============================================================================

.PHONY: all run debug clean help list

# Default target: compile the specified file
all: $(OUTPUT)

# Compile the C++ file
$(OUTPUT): $(FILE)
	@echo "Compiling $(FILE)..."
	@mkdir -p $(BUILD_DIR)
	@$(CXX) $(CXXFLAGS) $(FILE) -o $(OUTPUT)
	@echo "✓ Compiled successfully: $(OUTPUT)"

# Compile and run
run: $(OUTPUT)
	@echo "Running $(OUTPUT)..."
	@echo "----------------------------------------"
ifeq ($(IN),)
	@$(OUTPUT)
else
	@if [ -f "$(IN)" ]; then \
		if [ -n "$(OUT)" ]; then \
			$(OUTPUT) < $(IN) > $(OUT); \
			echo "✓ Output written to $(OUT)"; \
		else \
			$(OUTPUT) < $(IN); \
		fi \
	else \
		echo "Error: Input file $(IN) not found"; \
		exit 1; \
	fi
endif

# Compile with debug flags and run with sanitizers
debug: $(FILE)
	@echo "Compiling $(FILE) in DEBUG mode..."
	@mkdir -p $(BUILD_DIR)
	@$(CXX) $(DEBUGFLAGS) $(FILE) -o $(OUTPUT)_debug
	@echo "✓ Compiled successfully: $(OUTPUT)_debug"
	@echo "Running in DEBUG mode..."
	@echo "----------------------------------------"
ifeq ($(IN),)
	@$(OUTPUT)_debug
else
	@if [ -f "$(IN)" ]; then \
		if [ -n "$(OUT)" ]; then \
			$(OUTPUT)_debug < $(IN) > $(OUT); \
			echo "✓ Output written to $(OUT)"; \
		else \
			$(OUTPUT)_debug < $(IN); \
		fi \
	else \
		echo "Error: Input file $(IN) not found"; \
		exit 1; \
	fi
endif

# Clean all compiled files
clean:
	@echo "Cleaning build directory..."
	@rm -rf $(BUILD_DIR)
	@echo "✓ Clean complete"

# List all C++ files in the directory
list:
	@echo "Available C++ files:"
	@echo "===================="
	@find . -name "*.cpp" -not -path "./$(BUILD_DIR)/*" | sort

# Help target
help:
	@echo "Competitive Programming Makefile"
	@echo "================================"
	@echo ""
	@echo "Usage:"
	@echo "  make [TARGET] FILE=<file.cpp> [IN=<input.txt>] [OUT=<output.txt>]"
	@echo ""
	@echo "Targets:"
	@echo "  all (default) - Compile the specified file"
	@echo "  run          - Compile and run the program"
	@echo "  debug        - Compile with debug flags and sanitizers"
	@echo "  clean        - Remove all compiled files"
	@echo "  list         - List all available C++ files"
	@echo "  help         - Show this help message"
	@echo ""
	@echo "Examples:"
	@echo "  make FILE=sandbox/sandbox.cpp"
	@echo "  make run FILE=EasyProblems/Watermelon.cpp"
	@echo "  make run FILE=sandbox/sandbox.cpp IN=input.txt"
	@echo "  make run FILE=sandbox/sandbox.cpp IN=input.txt OUT=output.txt"
	@echo "  make debug FILE=sandbox/sandbox.cpp IN=test.txt"
	@echo "  make clean"
	@echo "  make list"
	@echo ""
	@echo "Configuration:"
	@echo "  Compiler: $(CXX)"
	@echo "  Standard: $(STD)"
	@echo "  Default file: $(FILE)"
