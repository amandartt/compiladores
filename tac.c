// Amanda e Gabriel

#include "tac.h"

TAC* tacCreate(int type, HASH_NODE *res, HASH_NODE *op1, HASH_NODE *op2){
	TAC* newTac;

	if(!(newTac = (TAC*) calloc(1, sizeof(TAC))) ){
		fprintf(stderr, "Error creating TAC! \n");
		exit(1);
	}
	newTac->type = type;
	newTac->res = res;
	newTac->op1 = op1;
	newTac->op2 = op2;
	newTac->prev = 0;
	newTac->next = 0;

	return newTac;
}

TAC* tacJoin(TAC *l1 ,TAC *l2){
	TAC *tac;
	
	if(!l1) { return l2; }	
	if(!l2) { return l1; }
	for(tac = l2; tac->prev; tac=tac->prev){
		; // go to root
	}
	tac->prev = l1;
	l1->next = tac;
	return l2;
}

void tacPrintBack(TAC *last){
	TAC *tac;
	for(tac = last; tac; tac=tac->prev){
		fprintf(stderr, "TAC(");
		//TODO missing one line
		//print	
	}
	if(tac->res){
		fprintf(stderr, ", %s ", tac->res->text);
	}else{
		fprintf(stderr, ", 0 ");
	}
	fprintf(stderr, ")\n");
}

//TODO continuar...
TAC * tacGenerate(ASTREE *node){
	TAC *code[MAX_SONS];
	TAC *result;
	int i = 0;

	if(!node) { return 0; }
	for(i=0; i<MAX_SONS; i++){
		code[i]= tacGenerate(node->son[i]);
	}
	switch(node->type){
		case AST_SYMBOL: result = tacCreate(TAC_SYMBOL, node->symbol, 0, 0);
			break;
		
	}
	// por enquanto
	return NULL;
}
