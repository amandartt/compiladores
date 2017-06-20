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
TAC* makeVecAssign(HASH_NODE* identifier, TAC** code);
TAC* makeFuncDef(HASH_NODE* identifier, TAC** code, ASTREE *funcDef);
TAC* makeFuncCall(ASTREE *funcCall);
TAC* makeReturn(TAC** code);
TAC* makeRead(HASH_NODE* identifier);
TAC* makePrint(ASTREE* print, TAC** code);
TAC* makeVecValues(HASH_NODE* identifier, TAC** code);
TAC* makeVar(HASH_NODE* identifier, TAC** code);
TAC* makeVec(HASH_NODE* identifier, HASH_NODE* length, TAC** code);
TAC* makeVecExpr(HASH_NODE* identifier, TAC** code);


// implementation

TAC* tacCreate(int type, HASH_NODE *res, HASH_NODE *op1, HASH_NODE *op2, int posParam){
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
	newTac->posParam = posParam;

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

		if(tac->res) fprintf(stderr, ",%s", tac->res->text); else fprintf(stderr, ",");
		if(tac->op1) fprintf(stderr, ",%s", tac->op1->text); else	fprintf(stderr, ",");
		if(tac->op2) fprintf(stderr, ",%s", tac->op2->text); else if(tac->posParam) fprintf(stderr, ",%d", tac->posParam); else fprintf(stderr, ",");
		fprintf(stderr, ")\n");
	}
}

void tacPrintForward(TAC *first){
	TAC *tac;
	for(tac = first; tac; tac=tac->next){
		fprintf(stderr, "TAC(");
		printTacType(tac->type);

		if(tac->res) fprintf(stderr, ",%s", tac->res->text); else fprintf(stderr, ",");
		if(tac->op1) fprintf(stderr, ",%s", tac->op1->text); else	fprintf(stderr, ",");
		if(tac->op2) fprintf(stderr, ",%s", tac->op2->text); else if(tac->posParam) fprintf(stderr, ",%d", tac->posParam); else fprintf(stderr, ",");
		fprintf(stderr, ")\n");
	}
	
}

//TODO continuar...
TAC * tacGenerate(ASTREE *node){
	TAC *code[MAX_SONS];
	TAC *result = 0;
	int i = 0;

	if(!node) { return 0; }
	for(i=0; i<MAX_SONS; i++){
		code[i]= 0;
	}
	for(i=0; i<MAX_SONS; i++){
		code[i]= tacGenerate(node->son[i]);
	}
	switch(node->type){
		case AST_SYMBOL: 
		case AST_PARAM:
			result = tacCreate(TAC_SYMBOL, node->symbol, 0, 0, 0); break;
		case AST_VECTOR_EXPR: result = makeVecExpr(node->symbol,code); break;
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
		case AST_VEC_ASSIGN: result = makeVecAssign(node->symbol,code); break;
		case AST_DEC_FUNC: result = makeFuncDef(node->son[0]->symbol, code, node); break;
		case AST_FUNC_CALL: result = makeFuncCall(node); break;
		case AST_RETURN: result = makeReturn(code); break;
		case AST_READ: result = makeRead(node->symbol); break;
		case AST_PRINT: result = makePrint(node, code); break;
		case AST_SEQNUM_ELEM: result = makeVecValues(node->symbol, code); break;
		case AST_DEC_VAR_GLOB: result = makeVar(node->symbol, code); break;
		case AST_DEC_VEC_GLOB: result = makeVec(node->symbol, node->son[0]->symbol, code); break;
	
		case AST_COMMAND_BLOCK: result = code[0]; break;
		case AST_SEQ_CMD: result = tacJoin(code[0],code[1]); break;
		case AST_PARENTESIS_EXPR: result = code[0]; break;	
		
		default: result = tacJoin(tacJoin(tacJoin(code[0], code[1]), code[2]), code[3]);
	}
	
	return result;
}

TAC* makeOpBin(int op, TAC** code){
	TAC *newTac = tacCreate(op, makeTemp(), code[0] ? code[0]->res : 0,
							  code[1] ? code[1]->res : 0, 0);
	return tacJoin(code[0], tacJoin(code[1], newTac));
}

TAC* makeWhenThen(TAC** code){
	TAC* iftac = 0;
	TAC* labeltac = 0;
	HASH_NODE* newlabel = 0;
	newlabel = makeLabel();
	iftac = tacCreate(TAC_IFZ,newlabel,code[0] ? code[0]->res : 0, 0, 0);
	labeltac = tacCreate(TAC_LABEL,newlabel,0,0, 0);
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
	iftac = tacCreate(TAC_IFZ,newlabel1,code[0] ? code[0]->res : 0, 0, 0);
	labeltac1 = tacCreate(TAC_LABEL,newlabel1,0,0,0);
	labeltac2 = tacCreate(TAC_LABEL,newlabel2,0,0,0);
	jump = tacCreate(TAC_JUMP,newlabel2,0,0,0);
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
	iftac = tacCreate(TAC_IFZ,newlabel2,code[0] ? code[0]->res : 0, 0, 0);
	labeltac1 = tacCreate(TAC_LABEL,newlabel1,0,0,0);
	labeltac2 = tacCreate(TAC_LABEL,newlabel2,0,0,0);
	jump = tacCreate(TAC_JUMP,newlabel1,0,0,0);
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
	ifless = tacCreate(TAC_IFLESSEQ,newlabel2,identifier,code[1]? code[1]->res : 0, 0);
	labeltac1 = tacCreate(TAC_LABEL,newlabel1,0,0,0);
	labeltac2 = tacCreate(TAC_LABEL,newlabel2,0,0,0);
	inc = tacCreate(TAC_INC,identifier,0,0,0);
	jump = tacCreate(TAC_JUMP,newlabel1,0,0,0);

	return tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(labeltac1,initid),ifless),code[2]),inc),jump),labeltac2);
}

TAC* makeAssign(HASH_NODE* identifier, TAC** code){
	TAC* move = 0;
	move = tacCreate(TAC_MOVE, identifier, code[0]? code[0]-> res : 0,0,0);
	return tacJoin(code[0],move); 
}

TAC* makeVecAssign(HASH_NODE* identifier, TAC** code){
	TAC* vecAssign = 0;
	vecAssign = tacCreate(TAC_VEC_WRITE, identifier, code[0]? code[0]-> res : 0,code[1]? code[1]-> res : 0,0);
	return tacJoin(code[0],tacJoin(code[1],vecAssign)); 
}

TAC* makeFuncDef(HASH_NODE* identifier, TAC** code, ASTREE *funcDef){
	ASTREE* buff;
	TAC* tacBuff = 0;
	TAC* tacArg = 0;
	TAC* params = 0;
	int i = 1;

	TAC* funcBody = code[1];
	TAC* beginFunc = tacCreate(TAC_BEGIN_FUNC, identifier, 0, 0, 0);
	// save params
	for(buff = funcDef->son[0]->son[1]; buff; buff = buff->son[1]){
		tacBuff = tacGenerate(buff->son[0]);
		tacArg = tacCreate(TAC_ARG_RECEIVE, identifier, tacBuff->res, 0, i);
		params = tacJoin(tacJoin(params,tacBuff), tacArg);
		i++;
	}

	TAC* endFunc = tacCreate(TAC_END_FUNC, identifier, 0, 0, 0);
	return tacJoin(tacJoin(tacJoin(params, beginFunc),funcBody), endFunc);
}

TAC* makeFuncCall(ASTREE *funcCall){
	TAC* tacCall = 0;	
	TAC* params = 0;
	ASTREE* buff = 0;
	TAC* tacBuff = 0;
	TAC* tacArg = 0;
	int i = 1;
	HASH_NODE* func_name = funcCall->symbol;
	for(buff = funcCall->son[0]; buff; buff = buff->son[1]){
		tacBuff = tacGenerate(buff->son[0]); //expr or a symbol... tacGenerate can process
		tacArg = tacCreate(TAC_ARG_CALL,func_name, tacBuff->res,0,i); //This generates a Warning, but he said to save the param number...
		params = tacJoin(tacJoin(params,tacBuff),tacArg);
		i++;
	}

	HASH_NODE* tempCall = makeTemp();
	tacCall = tacCreate(TAC_CALL, tempCall, funcCall->symbol,0,0);
	return tacJoin(params,tacCall);
}

TAC* makeReturn(TAC** code){
	TAC* ret = 0;
	ret = tacCreate(TAC_RETURN,code[0]? code[0]->res : 0, 0, 0,0);
	return tacJoin(code[0],ret);
}

TAC* makeRead(HASH_NODE* identifier){
	TAC* symb = tacCreate(TAC_SYMBOL, identifier,0,0,0);
	TAC* ret = tacCreate(TAC_READ,identifier, 0, 0,0);
	return tacJoin(symb,ret);
}

TAC* makePrint(ASTREE* print, TAC** code){
	ASTREE* buff = 0;
	TAC* prints = 0;
	TAC* tacBuff = 0;
	TAC* tacPrint = 0;
	buff = print->son[0];
	while(buff){				
		if(buff->symbol){
			tacBuff = tacCreate(TAC_SYMBOL,buff->symbol, 0, 0, 0);
			buff = buff->son[0];
		}else{
			tacBuff = tacGenerate(buff->son[0]);
			buff = buff->son[1];
		}
		tacPrint = tacCreate(TAC_PRINT,tacBuff ? tacBuff->res: 0,0,0,0);	
		prints = tacJoin(tacJoin(prints,tacBuff),tacPrint);
	}
	
	return prints;
}

TAC* makeVecValues(HASH_NODE* identifier, TAC** code){
	TAC *vecValue = tacCreate(TAC_ARRAY_VALUES, identifier, 0, 0, 0);
	return tacJoin(vecValue, code[0]);
}

TAC* makeVar(HASH_NODE* identifier, TAC** code){
	TAC *name = tacCreate(TAC_SYMBOL, identifier,0,0,0);
	TAC *var = tacCreate(TAC_VAR, identifier, code[1]->res, 0, 0);
	return tacJoin(name,tacJoin(code[1],var));
}

TAC* makeVec(HASH_NODE* identifier, HASH_NODE* length, TAC** code){
	TAC *vec = tacCreate(TAC_VEC, identifier, length, 0, 0);
	return tacJoin(vec, code[0]);
}

TAC* makeVecExpr(HASH_NODE* identifier, TAC** code){	
	TAC *value = tacCreate(TAC_VEC_EXPR, makeTemp(), identifier, code[0]? code[0]->res: 0, 0);
	return tacJoin(code[0],value);
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
		case TAC_ASSIGN: fprintf(stderr, "TAC_ASSIGN"); break;
		case TAC_VEC_WRITE: fprintf(stderr, "TAC_VEC_WRITE"); break;
		case TAC_VEC_READ: fprintf(stderr, "TAC_VEC_READ"); break;
		case TAC_RETURN: fprintf(stderr, "TAC_RETURN"); break;
		case TAC_PRINT: fprintf(stderr, "TAC_PRINT"); break;
		case TAC_READ: fprintf(stderr, "TAC_READ"); break;
		case TAC_CALL: fprintf(stderr, "TAC_CALL"); break;
		case TAC_ARG_CALL: fprintf(stderr, "TAC_ARG_CALL"); break;
		case TAC_ARG_RECEIVE: fprintf(stderr, "TAC_ARG_RECEIVE"); break;
		case TAC_IFZ: fprintf(stderr, "TAC_IFZ"); break;
		case TAC_LABEL: fprintf(stderr, "TAC_LABEL"); break;
		case TAC_BEGIN_FUNC: fprintf(stderr, "TAC_BEGIN_FUNC"); break;
		case TAC_END_FUNC: fprintf(stderr, "TAC_END_FUNC"); break;
		case TAC_JUMP: fprintf(stderr, "TAC_JUMP"); break;
		case TAC_IFLESSEQ: fprintf(stderr, "TAC_IFLESSEQ"); break;
		case TAC_INC: fprintf(stderr, "TAC_INC"); break;
		case TAC_MOVE: fprintf(stderr, "TAC_MOVE"); break;
		case TAC_ARRAY_VALUES: fprintf(stderr, "TAC_ARRAY_VALUES"); break;
		case TAC_VAR: fprintf(stderr, "TAC_VAR"); break;
		case TAC_VEC: fprintf(stderr, "TAC_VEC"); break;
		case TAC_VEC_EXPR: fprintf(stderr, "TAC_VEC_EXPR");break;
		default:
			fprintf(stderr, "Type not found"); break;
	}
}
