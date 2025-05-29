#include "ast.h"
#include <stdlib.h>
#include <string.h>

ASTNode* create_number(int value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_NUMBER;
    node->value = value;
    return node;
}

ASTNode* create_identifier(char* name) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_IDENTIFIER;
    node->name = strdup(name);
    return node;
}

ASTNode* create_binary(ASTNode* left, char op, ASTNode* right) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_BINARY_EXPR;
    node->left = left;
    node->right = right;
    node->op = op;
    return node;
}

ASTNode* create_function(char* name, ASTNode** params, int param_count, ASTNode* body) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_FUNCTION_DEF;
    node->name = strdup(name);
    node->params = params;
    node->param_count = param_count;
    node->body = body;
    return node;
}

ASTNode* create_call(char* name, ASTNode** args, int arg_count) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_FUNCTION_CALL;
    node->name = strdup(name);
    node->args = args;
    node->arg_count = arg_count;
    return node;
}

ASTNode* create_var_decl(char* name, ASTNode* value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_VAR_DECL;
    node->name = strdup(name);
    node->body = value;
    return node;
}

ASTNode* create_print(ASTNode* expr) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_PRINT;
    node->body = expr;
    return node;
}

