SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
CC := g++
CPP_PREFLAGS := -std=c++17
LINK_FLAGS := -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system

$(BIN_DIR)/main: $(OBJ_FILES) | $(BIN_DIR)
	$(CC) $(CPP_PREFLAGS) -o $@ $^ $(LINK_FLAGS)

$(BIN_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CPP_PREFLAGS) -o $@ -c $< $(LINK_FLAGS)

$(OBJ_DIR):
	mkdir -p $@

clean:
	rm -r $(OBJ_DIR) $(BIN_DIR)