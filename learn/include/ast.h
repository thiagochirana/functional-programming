#ifndef AST_H
#define AST_H

typedef enum {
    AST_NUMBER,
    AST_IDENTIFIER,
    AST_BINARY_EXPR,
    AST_FUNCTION_DEF,
    AST_FUNCTION_CALL,
    AST_VAR_DECL,
    AST_PRINT
} ASTNodeType;

typedef struct ASTNode {
    ASTNodeType type;

    char* name;

    int value;

    struct ASTNode* left;
    struct ASTNode* right;
    char op;

    struct ASTNode** params;
    int param_count;
    struct ASTNode* body;

    struct ASTNode** args;
    int arg_count;

} ASTNode;

ASTNode* create_number(int value);
ASTNode* create_identifier(char* name);
ASTNode* create_binary(ASTNode* left, char op, ASTNode* right);
ASTNode* create_function(char* name, ASTNode** params, int param_count, ASTNode* body);
ASTNode* create_call(char* name, ASTNode** args, int arg_count);
ASTNode* create_var_decl(char* name, ASTNode* value);
ASTNode* create_print(ASTNode* expr);

#endif

