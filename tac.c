// Amanda e Gabriel

#include "tac.h"

// local functions
HASH_NODE* makeTemp();
HASH_NODE* makeLabel();
void printTacType(int type);
TAC* makeOpBin(int op, TAC** code);
TAC* makeWhenThen(TAC** code);
TAC* makeWhenThenElse(TAC** code);
TAC* makeWhile(TAC** code);
TAC* makeFor(HASH_NODE* identifier, TAC** code);
TAC* makeAssign(HASH_NODE* identifier, TAC** code);


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

TAC* tacReverse(TAC *tac){
	TAC *t = 0;
	for(t=tac;t->prev;t=t->prev){t->prev->next = t;}
	return t;
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
		case AST_WHEN_THEN: result = makeWhenThen(code); break;
		case AST_WHEN_THEN_ELSE: result = makeWhenThenElse(code); break;
		case AST_WHILE: result = makeWhile(code); break;
		case AST_FOR: result = makeFor(node->symbol,code); break;
		case AST_ASSIGN: result = makeAssign(node->symbol,code); break;
	}
	
	return result;
}

TAC* makeOpBin(int op, TAC** code){
	TAC *newTac = tacCreate(op, makeTemp(), code[0] ? code[0]->res : 0,
							  code[1] ? code[1]->res : 0);
	return tacJoin(code[0], tacJoin(code[1], newTac));
}

TAC* makeWhenThen(TAC** code){
	TAC* iftac = 0;
	TAC* labeltac = 0;
	HASH_NODE* newlabel = 0;
	newlabel = makeLabel();
	iftac = tacCreate(TAC_IFZ,newlabel,code[0] ? code[0]->res : 0, 0);
	labeltac = tacCreate(TAC_LABEL,newlabel,0,0);
	return tacJoin(tacJoin(tacJoin(code[0],iftac),code[1]),labeltac);
}

TAC* makeWhenThenElse(TAC** code){
	TAC* iftac = 0;
	TAC* labeltac1 = 0;
	TAC* labeltac2 = 0;
	TAC* jump = 0;
	HASH_NODE* newlabel1 = 0;
	HASH_NODE* newlabel2 = 0;
	newlabel1 = makeLabel();
	newlabel2 = makeLabel();
	iftac = tacCreate(TAC_IFZ,newlabel1,code[0] ? code[0]->res : 0, 0);
	labeltac1 = tacCreate(TAC_LABEL,newlabel1,0,0);
	labeltac2 = tacCreate(TAC_LABEL,newlabel2,0,0);
	jump = tacCreate(TAC_JUMP,newlabel2,0,0);
	return tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(code[0],iftac),code[1]),jump),labeltac1),code[2]),labeltac2);
}

TAC* makeWhile(TAC** code){
	TAC* iftac = 0;
	TAC* labeltac1 = 0;
	TAC* labeltac2 = 0;
	TAC* jump = 0;
	HASH_NODE* newlabel1 = 0;
	HASH_NODE* newlabel2 = 0;
	newlabel1 = makeLabel();
	newlabel2 = makeLabel();
	iftac = tacCreate(TAC_IFZ,newlabel2,code[0] ? code[0]->res : 0, 0);
	labeltac1 = tacCreate(TAC_LABEL,newlabel1,0,0);
	labeltac2 = tacCreate(TAC_LABEL,newlabel2,0,0);
	jump = tacCreate(TAC_JUMP,newlabel1,0,0);
	return tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(labeltac1,code[0]),iftac),code[1]),jump),labeltac2);
}

TAC* makeFor(HASH_NODE* identifier,TAC** code){
	TAC* initid = 0;
	TAC* ifless = 0;
	TAC* inc = 0;
	TAC* jump = 0;
	TAC* labeltac1 = 0;
	TAC* labeltac2 = 0;
	HASH_NODE* newlabel1 = 0;
	HASH_NODE* newlabel2 = 0;
	newlabel1 = makeLabel();
	newlabel2 = makeLabel();
	initid = makeAssign(identifier,code);
	ifless = tacCreate(TAC_IFLESS,newlabel2,identifier,code[1]? code[1]->res : 0);
	labeltac1 = tacCreate(TAC_LABEL,newlabel1,0,0);
	labeltac2 = tacCreate(TAC_LABEL,newlabel2,0,0);
	inc = tacCreate(TAC_INC,identifier,0,0);
	jump = tacCreate(TAC_JUMP,newlabel1,0,0);

	return tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(labeltac1,initid),ifless),code[2]),inc),jump),labeltac2);
}

TAC* makeAssign(HASH_NODE* identifier, TAC** code){
	TAC* move = 0;
	move = tacCreate(TAC_MOVE, identifier, code[0]? code[0]-> res : 0,0);
	return move; 
}

HASH_NODE* makeTemp(){
	static int serial_temp = 0;
	static char buffer[128];

	sprintf(buffer, "#temporary_%d", serial_temp);
	serial_temp++;
	return hash_insert(SYMBOL_VAR, buffer, 0, 0);
}

HASH_NODE* makeLabel(){
	static int serial_label = 0;
	static char buffer[128];

	sprintf(buffer, "#label_%d", serial_label);
	serial_label++;
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
