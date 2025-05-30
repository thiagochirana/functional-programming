#include "../include/lexer.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#define MAX_TOKENS 1024

Token* tokens;
int token_count = 0;

void add_token(TokenType type, const char* start, int length) {
    Token token;
    token.type = type;
    token.value = strndup(start, length);
    tokens[token_count++] = token;
}

int match_keyword(const char* str, int length, const char* keyword) {
    return strncmp(str, keyword, length) == 0 && keyword[length] == '\0';
}

Token* tokenize(const char* src, int* out_count) {
    tokens = malloc(sizeof(Token) * MAX_TOKENS);
    token_count = 0;

    const char* p = src;

    while (*p) {
        if (isspace(*p)) {
            p++;
            continue;
        }

        if (isalpha(*p)) {
            const char* start = p;
            while (isalnum(*p) || *p == '_') p++;
            int len = p - start;

            if (match_keyword(start, len, "let")) {
                add_token(TOKEN_LET, start, len);
            } else if (match_keyword(start, len, "fn")) {
                add_token(TOKEN_FN, start, len);
            } else if (match_keyword(start, len, "print")) {
                add_token(TOKEN_PRINT, start, len);
            } else {
                add_token(TOKEN_IDENTIFIER, start, len);
            }

            continue;
        }

        if (isdigit(*p)) {
            const char* start = p;
            while (isdigit(*p)) p++;
            add_token(TOKEN_NUMBER, start, p - start);
            continue;
        }

        if (*p == '(') { add_token(TOKEN_LPAREN, p++, 1); continue; }
        if (*p == ')') { add_token(TOKEN_RPAREN, p++, 1); continue; }
        if (*p == ',') { add_token(TOKEN_COMMA, p++, 1); continue; }
        if (*p == '+') { add_token(TOKEN_PLUS, p++, 1); continue; }
        if (*p == '=') {
            if (*(p + 1) == '>') {
                add_token(TOKEN_ARROW, p, 2);
                p += 2;
            } else {
                add_token(TOKEN_EQUAL, p++, 1);
            }
            continue;
        }
        if (*p == ';') { add_token(TOKEN_SEMICOLON, p++, 1); continue; }

        fprintf(stderr, "Caractere inesperado: %c\n", *p);
        exit(1);
    }

    add_token(TOKEN_EOF, p, 0);
    *out_count = token_count;
    return tokens;
}
