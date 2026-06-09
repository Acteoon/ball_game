CFLAGS = -Wall -Wextra -O2 -Iinclude
LDFLAGS = -lraylib -lm

SRC_DIR = src
OBJ_DIR = objects

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
BIN = game

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

run: $(BIN)
	./$(BIN)

clean:
	rm -f $(BIN) $(OBJ)
	rmdir $(OBJ_DIR) 2>/dev/null; true

.PHONY: run clean
