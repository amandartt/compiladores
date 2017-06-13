// Amanda e Gabriel

#include "tac.h"

// local functions
HASH_NODE* makeTemp();
void printTacType(int type);
TAC* makeOpBin(int op, TAC** code);



// implementation

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
		printTacType(tac->type);
	}
	if(tac->res) fprintf(stderr, ", %s ", tac->res->text); else fprintf(stderr, ", 0 ");
	if(tac->op1) fprintf(stderr, ", %s ", tac->op1->text); else	fprintf(stderr, ", 0 ");
	if(tac->op2) fprintf(stderr, ", %s ", tac->op2->text); else	fprintf(stderr, ", 0 ");
	
	fprintf(stderr, ")\n");
}

void tacPrintForward(TAC *first){
	TAC *tac;
	for(tac = first; tac; tac=tac->next){
		fprintf(stderr, "TAC(");
		printTacType(tac->type);
	}
	if(tac->res) fprintf(stderr, ", %s ", tac->res->text); else fprintf(stderr, ", 0 ");
	if(tac->op1) fprintf(stderr, ", %s ", tac->op1->text); else	fprintf(stderr, ", 0 ");
	if(tac->op2) fprintf(stderr, ", %s ", tac->op2->text); else	fprintf(stderr, ", 0 ");
	
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
		case AST_SYMBOL: result = tacCreate(TAC_SYMBOL, node->symbol, 0, 0); break;
		case AST_ADD: result = makeOpBin(TAC_ADD, code); break;	
		case AST_SUB: result = makeOpBin(TAC_SUB, code); break;		
		case AST_MUL: result = makeOpBin(TAC_MUL, code); break;	
		case AST_DIV: result = makeOpBin(TAC_DIV, code); break;	
		case AST_LOGIC_G: result = makeOpBin(TAC_G, code); break;	
		case AST_LOGIC_L: result = makeOpBin(TAC_L, code); break;	
		case AST_LOGIC_LE: result = makeOpBin(TAC_LE, code); break;	
		case AST_LOGIC_GE: result = makeOpBin(TAC_GE, code); break;	
		case AST_LOGIC_EQ: result = makeOpBin(TAC_EQ, code); break;	
		case AST_LOGIC_NE: result = makeOpBin(TAC_NE, code); break;	
		case AST_LOGIC_AND: result = makeOpBin(TAC_AND, code); break;	
		case AST_LOGIC_OR: result = makeOpBin(TAC_OR, code); break;			
	}
	
	return result;
}

TAC* makeOpBin(int op, TAC** code){
	TAC *newTac = tacCreate(op, makeTemp(), code[0] ? code[0]->res : 0,
							  code[1] ? code[1]->res : 0);
	return tacJoin(code[0], tacJoin(code[1], newTac));
}

HASH_NODE* makeTemp(){
	static int serial = 0;
	static char buffer[128];

	sprintf(buffer, "#temporary_%d", serial);
	serial++;
	return hash_insert(SYMBOL_VAR, buffer, 0, 0);
}

//TODO: continuar
void printTacType(int type){
	switch(type){
		case TAC_SYMBOL: fprintf(stderr, "TAC_SYMBOL"); break;
		case TAC_ADD: fprintf(stderr, "TAC_ADD"); break;
		case TAC_SUB: fprintf(stderr, "TAC_SUB"); break;
		case TAC_MUL: fprintf(stderr, "TAC_MUL"); break;
		case TAC_DIV: fprintf(stderr, "TAC_DIV"); break;
		case TAC_G: fprintf(stderr, "TAC_G"); break;
		case TAC_L: fprintf(stderr, "TAC_L"); break;
		case TAC_LE: fprintf(stderr, "TAC_LE"); break;
		case TAC_GE: fprintf(stderr, "TAC_GE"); break;
		case TAC_EQ: fprintf(stderr, "TAC_EQ"); break;
		case TAC_NE: fprintf(stderr, "TAC_NE"); break;
		case TAC_AND: fprintf(stderr, "TAC_AND"); break;
		case TAC_OR: fprintf(stderr, "TAC_OR"); break;

	}
}
