#include "../include/parser.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static Token* tokens;
static int current;
static int total;
static ASTNode** nodes;
static int node_count = 0;

static Token peek() {
    return tokens[current];
}

static Token advance() {
    return tokens[current++];
}

static int match(TokenType type) {
    if (peek().type == type) {
        advance();
        return 1;
    }
    return 0;
}

static char* copy_token_value() {
    return strdup(advance().value);
}

static ASTNode* parse_expression();

static ASTNode* parse_primary() {
    Token token = peek();
    if (token.type == TOKEN_NUMBER) {
        advance();
        return create_number(atoi(token.value));
    }

    if (token.type == TOKEN_IDENTIFIER) {
        char* name = copy_token_value();
        if (match(TOKEN_LPAREN)) {
            ASTNode** args = malloc(sizeof(ASTNode*) * 10);
            int argc = 0;
            if (!match(TOKEN_RPAREN)) {
                do {
                    args[argc++] = parse_expression();
                } while (match(TOKEN_COMMA));
                match(TOKEN_RPAREN);
            }
            return create_call(name, args, argc);
        } else {
            return create_identifier(name);
        }
    }

    return NULL;
}

static ASTNode* parse_expression() {
    ASTNode* left = parse_primary();

    while (peek().type == TOKEN_PLUS) {
        char op = advance().value[0];
        ASTNode* right = parse_primary();
        left = create_binary(left, op, right);
    }

    return left;
}

static ASTNode* parse_var_decl() {
    advance(); // let
    char* name = copy_token_value(); // identifier
    match(TOKEN_EQUAL); // =
    match(TOKEN_FN);    // fn
    match(TOKEN_LPAREN);

    ASTNode** params = malloc(sizeof(ASTNode*) * 10);
    int param_count = 0;

    if (!match(TOKEN_RPAREN)) {
        do {
            params[param_count++] = create_identifier(copy_token_value());
        } while (match(TOKEN_COMMA));
        match(TOKEN_RPAREN);
    }

    match(TOKEN_ARROW);
    ASTNode* body = parse_expression();
    match(TOKEN_SEMICOLON);
    return create_var_decl(name, create_function(name, params, param_count, body));
}

static ASTNode* parse_print() {
    advance(); // print
    match(TOKEN_LPAREN);
    ASTNode* expr = parse_expression();
    match(TOKEN_RPAREN);
    match(TOKEN_SEMICOLON);
    return create_print(expr);
}

ASTNode** parse(Token* t, int count, int* out_node_count) {
    tokens = t;
    current = 0;
    total = count;
    node_count = 0;

    nodes = malloc(sizeof(ASTNode*) * 100);

    while (peek().type != TOKEN_EOF) {
        if (peek().type == TOKEN_LET) {
            nodes[node_count++] = parse_var_decl();
        } else if (peek().type == TOKEN_PRINT) {
            nodes[node_count++] = parse_print();
        } else {
            fprintf(stderr, "Erro de sintaxe inesperado: %s\n", peek().value);
            exit(1);
        }
    }

    *out_node_count = node_count;
    return nodes;
}
