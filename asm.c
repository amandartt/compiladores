#include "asm.h"

// local functions
void asmPrintFixed(FILE* output);
void asmPushHash(FILE* output);


// implementation

void asmGen(TAC* first, FILE* output){ //PARA DESCOBRIR OS ASM: gcc -S -O0 tracker.c
	TAC* tac;
	asmPushHash(output);	
	for(tac=first; tac; tac = tac->next)
		switch(tac->type){
			case TAC_SYMBOL: break;
			case TAC_ADD: fprintf(output,	"## TAC_ADD\n"
								  			"\tmovss _%s(%%rip), %%eax\n"
											"\taddss _%s(%%rip), %%eax\n"
											"\tmovss %%eax, _%s(%%rip)\n",
								  tac->op1->text,tac->op2->text,tac->res->text); break;
			case TAC_SUB: fprintf(output,	"## TAC_SUB\n"
								  			"\tmovss _%s(%%rip), %%eax\n"
											"\tsubss _%s(%%rip), %%eax\n"
											"\tmovss %%eax, _%s(%%rip)\n",
								  tac->op1->text,tac->op2->text,tac->res->text); break;
			case TAC_MUL: fprintf(output,	"## TAC_MUL\n"
								  			"\tmovss _%s(%%rip), %%eax\n"
											"\tmulss _%s(%%rip), %%eax\n"
											"\tmovss %%eax, _%s(%%rip)\n",
								  tac->op1->text,tac->op2->text,tac->res->text); break;
			case TAC_DIV: fprintf(output,	"## TAC_DIV\n"
								  			"\tmovss _%s(%%rip), %%eax\n"
											"\tdivss _%s(%%rip), %%eax\n"
											"\tmovss %%eax, _%s(%%rip)\n",
								  tac->op1->text,tac->op2->text,tac->res->text); break;
		}
}

void asmPushHash(FILE* output){ //LEMBRAR: converter todos os numericos para float (para nao precisar se preocupar com compatibilidade de operandos)

}

void asmPrintFixed(FILE* output){ //TODO: print imutável (section TEXT, .str asciz "%f", section DATA"...

}
