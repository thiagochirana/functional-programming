typedef enum {
    NODE_NUMBER,
    NODE_IDENTIFIER,
    NODE_CALL,
    NODE_FUNCTION,
    NODE_LET,
    NODE_PRINT
} NodeType;

typedef struct ASTNode {
    NodeType type;
    char* name;
    int value;
    struct ASTNode** args;
    struct ASTNode* body;
    int arg_count;
} ASTNode;

