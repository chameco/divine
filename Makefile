CC = gcc
SRCS = $(filter-out main.c,$(foreach file,$(wildcard src/*),$(notdir $(file))))
GAME = divine
BUILD_DIR = build_$(CC)
LIB_DIR = lib_$(CC)
OBJS = $(addprefix $(BUILD_DIR)/, $(SRCS:.c=.o))

CFLAGS_gcc = -Iinclude -std=c99 -g -Wall -Werror
CFLAGS = $(CFLAGS_$(CC))

LINKER_FLAGS_gcc = -lm -lGLEW -lglfw -lGL -lSOIL
LINKER_FLAGS = $(LINKER_FLAGS_$(CC))

vpath %.c src

.PHONY: all directories clean

all: directories $(GAME)

directories: $(BUILD_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.c
	$(CC) -o $@ -c $(CFLAGS) $<

$(GAME): $(BUILD_DIR)/main.o $(OBJS)
	$(CC) $^ $(LINKER_FLAGS) -o $@

clean:
	rm $(BUILD_DIR)/*.o
