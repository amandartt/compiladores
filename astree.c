#include "astree.h"	

ASTREE* astreeCreate(int type, HASH_NODE* symbol, ASTREE* son1, ASTREE* son2, ASTREE* son3, ASTREE* son4){
	return NULL;
}

void astreePrint(ASTREE* node){

	if(!node) return;
	printf("ASTREE(");

	switch(node->type){
		// defines
	}

	if(node->symbol){
		printf("Texto symbol: %s", node->symbol->text);
	}else{
		printf("Type: %d\n", node->type);
	}
	// print filhos
}

