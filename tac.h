// Amanda e Gabriel

#ifndef TAC_HEADER
#define TAC_HEADER

#include "tac_defines.h"
#include <stdio.h>
#include "hash.h"
#include "astree.h"

typedef struct tac_struct{
	int type;
	HASH_NODE *res;
	HASH_NODE *op1;
	HASH_NODE *op2;
	struct tac_struct *prev;
	struct tac_struct *next;
} TAC;

TAC* tacCreate(int type, HASH_NODE *res, HASH_NODE *op1, HASH_NODE *op2);
TAC* tacJoin(TAC *l1 ,TAC *l2);
void tacPrintBack(TAC *last);
TAC * tacGenerate(ASTREE *node);

#endif
