SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
LIB_DIR := lib
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
CC := g++
CPP_PREFLAGS := -DSFML_STATIC -std=c++17 -static-libgcc -static-libstdc++ -mwindows
LINK_FLAGS := -I$(LIB_DIR)/SFML-2.5.1/include -L$(LIB_DIR)/SFML-2.5.1/lib -lsfml-audio-s -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lwinmm -lopengl32 -lgdi32 -lfreetype -lopengl32 -lopenal32 -lpthread -lFLAC -lvorbisfile -lvorbisenc -lvorbis -logg

battleship: $(OBJ_FILES)
	$(CC) $(CPP_PREFLAGS) -o $@ $^ $(LINK_FLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CPP_PREFLAGS) -o $@ -c $< $(LINK_FLAGS)

$(OBJ_DIR):
	mkdir -p $@

clean:
	rm -r $(OBJ_DIR)
	rm battleship
