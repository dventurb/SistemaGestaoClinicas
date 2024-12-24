CC = gcc
CFLAGS = -Wall -Iinc

SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj
EXEC = executavel

SRC_FILES = main.c $(SRC_DIR)/menu.c $(SRC_DIR)/cliente.c $(SRC_DIR)/medico.c $(SRC_DIR)/consulta.c $(SRC_DIR)/auxiliares.c
OBJ_FILES = $(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(SRC_FILES)))

all: $(OBJ_DIR) $(EXEC)

$(EXEC): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(EXEC)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
ifeq ($(OS),Windows_NT)
	del /f $(OBJ_DIR)\*.o $(EXEC)
else
	rm -f $(OBJ_DIR)/*.o $(EXEC)
endif

rebuild: clean all
