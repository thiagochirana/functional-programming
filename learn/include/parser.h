#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "ast.h"

ASTNode** parse(Token* tokens, int token_count, int* out_node_count);

#endif
