CC = gcc

CFLAGS = $(shell pkg-config --cflags gtk4) -Iinc -Iui/inc -Iui/lib -I./lib -Wall -Wextra -g
LDFLAGS = $(shell pkg-config --libs gtk4) -lcrypt -lhpdf lib/libhpdftbl.a -lm

SRC = $(wildcard src/*.c) $(wildcard ui/src/*.c) $(wildcard ui/lib/*.c)
OBJ = $(SRC:.c=.o)
BIN = hospital-management

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
ifeq ($(OS),Windows_NT)
	del /f $(OBJ)\*.o $(BIN)
else
	rm -f src/*.o ui/src/*.o  ui/lib/*.o $(BIN)
endif

rebuild: clean all
