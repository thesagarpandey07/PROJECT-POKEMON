# ==========================================
# Compiler and Flags
# ==========================================
CC       := g++
CFLAGS   := -Wall -Wextra -Wno-unused-parameter -Isrc -std=c++17

# Linker flags (Raylib and platform dependencies)
LDFLAGS  := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Directories
SRC_DIR  := src
OBJ_DIR  := obj
BIN_DIR  := bin

# Executable Output
TARGET   := $(BIN_DIR)/pokemon_game.exe

# Source & Object Files
SRCS     := $(wildcard $(SRC_DIR)/*.cpp)
OBJS     := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# ==========================================
# Build Rules
# ==========================================

# Default rule: builds the executable
all: $(TARGET)

# Rule to link object files into the final executable
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Rule to compile each .cpp file into a .o file inside obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create obj/ and bin/ directories if they don't exist
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# Clean up built binaries and object files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Prevent name conflicts with files named 'all' or 'clean'
.PHONY: all clean