
BUILD_DIR = build
INCLUDE_DIR = include
LIB_DIR = lib

SRC_FILES = $(wildcard src/*.c)

build-exe: $(SRC_FILES)
	clang -I$(INCLUDE_DIR) -L$(LIB_DIR) -o $(BUILD_DIR)/pong $^ -lm -lraylib -lgdi32 -lopengl32 -lwinmm -ldxguid -lws2_32 -luser32 -lkernel32

clean:
	rm -f $(BUILD_DIR)/pong