#ifndef ASTREE_HEADER
#define ASTREE_HEADER

#include <stdio.h>
#include "hash.h"
#include "ast_const.h"


typedef struct astree{
	int type;
	HASH_NODE *symbol;
	struct astree *son[MAX_SONS];
} ASTREE;

ASTREE* astreeCreate(int type, HASH_NODE *symbol, ASTREE *son1, ASTREE *son2, ASTREE *son3, ASTREE *son4);
void astreePrint(ASTREE *node, int depth);


#endif
