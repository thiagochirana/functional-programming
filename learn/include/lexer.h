#ifndef LEXER_H
#define LEXER_H

typedef enum {
    TOKEN_EOF,
    TOKEN_LET,
    TOKEN_FN,
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_COMMA,
    TOKEN_ARROW,
    TOKEN_EQUAL,
    TOKEN_PLUS,
    TOKEN_PRINT,
    TOKEN_SEMICOLON
} TokenType;

typedef struct {
    TokenType type;
    char* value;
} Token;

Token* tokenize(const char* src, int* out_count);

#endif

