#include "astree.h"	
#include <stdio.h>
#include <stdlib.h>

ASTREE* astreeCreate(int type, HASH_NODE* symbol, ASTREE* son1, ASTREE* son2, ASTREE* son3, ASTREE* son4){
	ASTREE* new_node = 0;
	new_node = calloc(1,sizeof(ASTREE));
	new_node->type = type;
	new_node->symbol = symbol;
	new_node->son[0] = son1;
	new_node->son[1] = son2;
	new_node->son[2] = son3;
	new_node->son[3] = son4;
	return new_node;
}

void astreePrint(ASTREE* node, int depth){

	if(!node){
		return;
	}

	//for(int c = 0; c < depth; c++) //identacao
		//printf(" ");

	printf("ASTREE(");

	switch(node->type){
		case AST_SYMBOL: printf("ASTREE_SYMB"); break;
		case AST_ADD: printf("ASTREE_ADD"); break;
		case AST_SUB: printf("ASTREE_SUB"); break;
		case AST_MUL: printf("ASTREE_MUL"); break;
		case AST_DIV: printf("ASTREE_DIV"); break;
		case AST_LOGIC_G: printf("ASTREE_LOGIC_G"); break;
		case AST_LOGIC_L: printf("ASTREE_LOGIC_L"); break;
		case AST_LOGIC_LE: printf("ASTREE_LOGIC_LE"); break;
		case AST_LOGIC_GE: printf("ASTREE_LOGIC_GE"); break;
		case AST_LOGIC_EQ: printf("ASTREE_LOGIC_EQ"); break;
		case AST_LOGIC_NE: printf("ASTREE_LOGIC_NE"); break;
		case AST_LOGIC_AND: printf("ASTREE_LOGIC_AND"); break;
		case AST_LOGIC_OR: printf("ASTREE_LOGIC_OR"); break;
		case AST_LOGIC_NOT: printf("ASTREE_LOGIC_NOT"); break;
		default: printf("ASTREE_?");
	}

	if(node->symbol){
		printf(",%s", node->symbol->text);
	}else{
		printf(",");
	}
	for(int i = 0; i < MAX_SONS; i++)
		astreePrint(node->son[i],depth+1);
		printf(",");
	printf(")");
}

