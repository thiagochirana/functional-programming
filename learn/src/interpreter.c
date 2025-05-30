#include "../include/interpreter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    ASTNode* value;
} Binding;

static Binding functions[100];
static int func_count = 0;

static Binding local_env[100];
static int local_count = 0;

void store_function(char* name, ASTNode* value) {
    functions[func_count++] = (Binding){ strdup(name), value };
}

ASTNode* get_function(char* name) {
    for (int i = 0; i < func_count; i++) {
        if (strcmp(functions[i].name, name) == 0)
            return functions[i].value;
    }
    return NULL;
}

void push_local(char* name, ASTNode* value) {
    local_env[local_count++] = (Binding){ strdup(name), value };
}

ASTNode* get_local(char* name) {
    for (int i = local_count - 1; i >= 0; i--) {
        if (strcmp(local_env[i].name, name) == 0)
            return local_env[i].value;
    }
    return NULL;
}

int eval(ASTNode* node);

int eval_call(ASTNode* call) {
    ASTNode* func = get_function(call->name);
    if (!func) {
        fprintf(stderr, "Função não encontrada: %s\n", call->name);
        exit(1);
    }

    local_count = 0; // reset env para a chamada

    for (int i = 0; i < func->param_count; i++) {
        int arg_val = eval(call->args[i]);
        ASTNode* arg_node = create_number(arg_val);
        push_local(func->params[i]->name, arg_node);
    }

    return eval(func->body);
}

int eval(ASTNode* node) {
    switch (node->type) {
        case AST_NUMBER:
            return node->value;
        case AST_IDENTIFIER: {
            ASTNode* val = get_local(node->name);
            if (!val) {
                fprintf(stderr, "Variável não encontrada: %s\n", node->name);
                exit(1);
            }
            return eval(val);
        }
        case AST_BINARY_EXPR: {
            int left = eval(node->left);
            int right = eval(node->right);
            switch (node->op) {
                case '+': return left + right;
                default:
                    fprintf(stderr, "Operador não suportado: %c\n", node->op);
                    exit(1);
            }
        }
        case AST_FUNCTION_CALL:
            return eval_call(node);
        default:
            fprintf(stderr, "Tipo de nó inválido no eval: %d\n", node->type);
            exit(1);
    }
}

void interpret(ASTNode** nodes, int count) {
    for (int i = 0; i < count; i++) {
        ASTNode* node = nodes[i];
        switch (node->type) {
            case AST_VAR_DECL:
                store_function(node->name, node->body);
                break;
            case AST_PRINT: {
                int result = eval(node->body);
                printf("%d\n", result);
                break;
            }
            default:
                fprintf(stderr, "Instrução não reconhecida.\n");
                exit(1);
        }
    }
}
