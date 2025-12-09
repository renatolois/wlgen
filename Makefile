TARGET = wlgen
CC = gcc
CFLAGS = -Wall -Wextra -O2 -Iinclude

SRC_DIR = src
OBJ_DIR = obj

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
MAIN_OBJ = $(OBJ_DIR)/main.o

all: $(TARGET)

$(TARGET): $(MAIN_OBJ) $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(MAIN_OBJ) $(OBJS)

$(OBJ_DIR)/main.o: main.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c main.c -o $(OBJ_DIR)/main.o

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

cleanobj:
	rm -rf $(OBJ_DIR)

.PHONY: all clean cleanobj

