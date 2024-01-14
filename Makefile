CC = gcc
CFLAGS = -Wall -I$(INCLUDE_DIR)
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = bin

SRC_FILES := $(filter-out $(SRC_DIR)/main.c, $(wildcard $(SRC_DIR)/*.c))
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

lsh: $(OBJ_FILES) $(BUILD_DIR)/main.o
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(shell mkdir -p $(BUILD_DIR))

.PHONY: clean

clean:
	rm -rf $(BUILD_DIR) lsh