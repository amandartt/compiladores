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
								  			"\tmovl _%s(%%rip), %%eax\n"
											"\taddl _%s(%%rip), %%eax\n"
											"\tmovl %%eax, _%s(%%rip)\n",
								  tac->op1->text,tac->op2->text,tac->res->text); break;
			case TAC_SUB: fprintf(output,	"## TAC_SUB\n"
								  			"\tmovl _%s(%%rip), %%eax\n"
											"\tsubl _%s(%%rip), %%eax\n"
											"\tmovl %%eax, _%s(%%rip)\n",
								  tac->op1->text,tac->op2->text,tac->res->text); break;
			case TAC_MUL: fprintf(output,	"## TAC_MUL\n"
								  			"\tmovl _%s(%%rip), %%eax\n"
											"\timull _%s(%%rip), %%eax\n"
											"\tmovl %%eax, _%s(%%rip)\n",
								  tac->op1->text,tac->op2->text,tac->res->text); break;
			case TAC_DIV: fprintf(output,	"## TAC_DIV\n"
								  			"\tmovl _%s(%%rip), %%eax\n"
											"\tcltd\n"
											"\tidivl _%s(%%rip)\n"
											"\tmovl %%eax, _%s(%%rip)\n",
								  tac->op1->text,tac->op2->text,tac->res->text); break;
			case TAC_G: fprintf(output,	"## TAC_G\n"
											"\tmovl _%s(%%rip), %%edx\n"				
								  			"\tmovl _%s(%%rip), %%eax\n"
											"\tcmpl %%eax, %%edx\n"
											"\tsetg %%al\n"
											"\tmovzbl %%al, %%eax\n"
											"\tmovl %%eax, _%s(%%rip)\n",
								  tac->op1->text,tac->op2->text,tac->res->text); break; 
			case TAC_L: fprintf(output,	"## TAC_L\n"
											"\tmovl _%s(%%rip), %%edx\n"				
								  			"\tmovl _%s(%%rip), %%eax\n"
											"\tcmpl %%eax, %%edx\n"
											"\tsetl %%al\n"
											"\tmovzbl %%al, %%eax\n"
											"\tmovl %%eax, _%s(%%rip)\n",
								  tac->op1->text,tac->op2->text,tac->res->text); break; 
			case TAC_GE: fprintf(output,	"## TAC_GE\n"
											"\tmovl _%s(%%rip), %%edx\n"				
								  			"\tmovl _%s(%%rip), %%eax\n"
											"\tcmpl %%eax, %%edx\n"
											"\tsetge %%al\n"
											"\tmovzbl %%al, %%eax\n"
											"\tmovl %%eax, _%s(%%rip)\n",
								  tac->op1->text,tac->op2->text,tac->res->text); break; 
			case TAC_LE: fprintf(output,	"## TAC_LE\n"
											"\tmovl _%s(%%rip), %%edx\n"				
								  			"\tmovl _%s(%%rip), %%eax\n"
											"\tcmpl %%eax, %%edx\n"
											"\tsetle %%al\n"
											"\tmovzbl %%al, %%eax\n"
											"\tmovl %%eax, _%s(%%rip)\n",
								  tac->op1->text,tac->op2->text,tac->res->text); break; 
			case TAC_EQ: fprintf(output,	"## TAC_EQ\n"
											"\tmovl _%s(%%rip), %%edx\n"				
								  			"\tmovl _%s(%%rip), %%eax\n"
											"\tcmpl %%eax, %%edx\n"
											"\tsete %%al\n"
											"\tmovzbl %%al, %%eax\n"
											"\tmovl %%eax, _%s(%%rip)\n",
								  tac->op1->text,tac->op2->text,tac->res->text); break;
			case TAC_NE: fprintf(output,	"## TAC_EQ\n"
											"\tmovl _%s(%%rip), %%edx\n"				
								  			"\tmovl _%s(%%rip), %%eax\n"
											"\tcmpl %%eax, %%edx\n"
											"\tsetne %%al\n"
											"\tmovzbl %%al, %%eax\n"
											"\tmovl %%eax, _%s(%%rip)\n",
								  tac->op1->text,tac->op2->text,tac->res->text); break; 
			case TAC_BEGIN_FUNC: fprintf(output,	"## TAC_BEGIN_FUNC\n"
											"\t%s:\n"				
								  			"\t.cfi_startproc\n"
											"\tpushq	%%rbp\n",
								  tac->op1->text); break; 
			case TAC_END_FUNC: fprintf(output,	"## TAC_END_FUNC\n"
											"\tpopq	%%rbp\n"				
								  			"\t.ret\n"
											"\t.cfi_endproc\n"); break; 
			case TAC_RETURN: fprintf(output,	"## TAC_RETURN\n"
											"\tmovl _%s(%%rip), %%eax\n",
								  tac->op1->text); break; 
		}
}

void asmPushHash(FILE* output){ //LEMBRAR: Johann permitiu considerar tudo como inteiro

}

void asmPrintFixed(FILE* output){ //TODO: print imutável (section TEXT, .str asciz "%f", section DATA"...

}
