# ==========================================
# Paths & Settings
# ==========================================
RAYLIB_DIR := external/raylib/src
RAYLIB_LIB := $(RAYLIB_DIR)/libraylib.a

SRC_DIR    := src
OBJ_DIR    := obj

CC         := g++
CFLAGS     := -Wall -Wextra -Wno-unused-parameter -Isrc -I$(RAYLIB_DIR) -std=c++17

# ==========================================
# Operating System Detection & Linker Flags
# ==========================================
ifeq ($(OS),Windows_NT)
    # Native Windows flags
    LDFLAGS := -L$(RAYLIB_DIR) -lraylib -lopengl32 -lgdi32 -lwinmm
    TARGET  := pokemon_game.exe
    RM      := del /Q /S
else
    # Linux / WSL flags
    LDFLAGS := -L$(RAYLIB_DIR) -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
    TARGET  := pokemon_game.exe
    RM      := rm -rf
endif

# Automatically gather all .cpp files in src/
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# ==========================================
# Build Rules
# ==========================================

all: $(RAYLIB_LIB) $(TARGET)

# 1. Compile Raylib submodule if libraylib.a is missing
$(RAYLIB_LIB):
	@echo "=========================================="
	@echo " Building Raylib Submodule... "
	@echo "=========================================="
	$(MAKE) -C $(RAYLIB_DIR)

# 2. Link executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# 3. Compile C++ object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create obj directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $@

# Clean project build files
clean:
	$(RM) $(OBJ_DIR) $(TARGET)

# Clean project build files AND Raylib compiled library
clean-all: clean
	$(MAKE) -C $(RAYLIB_DIR) clean

.PHONY: all clean clean-all