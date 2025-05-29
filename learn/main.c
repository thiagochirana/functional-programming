#include "lexer.h"
#include "parser.h"
#include "ast.h"
#include "interpreter.h"
#include <stdio.h>
#include <stdlib.h>

char* read_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    rewind(file);

    char* buffer = malloc(length + 1);
    if (!buffer) {
        perror("Erro ao alocar memória");
        exit(1);
    }

    fread(buffer, 1, length, file);
    buffer[length] = '\0';

    fclose(file);
    return buffer;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Uso: learn arquivo.ln\n");
        return 1;
    }

    const char* filename = argv[1];
    char* source_code = read_file(filename);

    int token_count;
    Token* tokens = tokenize(source_code, &token_count);

    int ast_count;
    ASTNode** ast = parse(tokens, token_count, &ast_count);
    
    interpret(ast, ast_count);

    free(source_code);
    return 0;
}
