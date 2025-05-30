
CC = gcc
CFLAGS = -Iinclude -Wall -Wextra
SRC = main.c src/lexer.c src/parser.c src/ast.c src/interpreter.c
BIN = learn

build:
	$(CC) $(SRC) $(CFLAGS) -o $(BIN)

clean:
	rm -f $(BIN)
