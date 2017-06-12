#ifndef ASTREE_HEADER
#define ASTREE_HEADER

#include <stdio.h>
#include "hash.h"
#include "ast_defines.h"


typedef struct astree{
	int type;
	int dataType;
	int lineNumber;
	HASH_NODE *symbol;
	struct astree *son[MAX_SONS];
} ASTREE;

ASTREE* ast;

ASTREE* astreeCreate(int type, HASH_NODE *symbol, ASTREE *son1, ASTREE *son2, ASTREE *son3, ASTREE *son4, int lineNumber);
void astreePrint(ASTREE *node, int depth);
void astreeProgram(ASTREE* node, FILE* output);

#endif
