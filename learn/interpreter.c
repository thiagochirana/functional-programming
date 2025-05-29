typedef struct {
    char* name;
    ASTNode* value;
} Binding;

Binding env[100];
int env_size = 0;

