
CC = gcc
CFLAGS = -Wall -Wextra `sdl2-config --cflags` -Iinclude
LDFLAGS = `sdl2-config --libs` -lm

TARGET = bin/main

SRC = $(shell find src -name '*.c')
OBJ = $(patsubst src/%.c, build/%.o, $(SRC))

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p bin
	$(CC) -o $@ $^ $(LDFLAGS)

build/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build bin







