CC = gcc

CFLAGS = $(shell pkg-config --cflags gtk4) -Iinc -Wall -Wextra -g
LDFLAGS = $(shell pkg-config --libs gtk4)

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
BIN = executavel

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
ifeq ($(OS),Windows_NT)
	del /f $(OBJ)\*.o $(BIN)
else
	rm -f src/*.o $(BIN)
endif

rebuild: clean all
