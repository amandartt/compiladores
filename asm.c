#include "asm.h"

// local functions
void asmPrintFixed(FILE* output);
void asmPushHash(FILE* output);


// implementation

void asmGen(TAC* first, FILE* output){ //PARA DESCOBRIR OS ASM: gcc -S -O0 tracker.c
	TAC* tac;
	asmPrintFixed(output);
	asmPushHash(output);
	int pos = 0;	
	for(tac=first; tac; tac = tac->next){	
		switch(tac->type){
			case TAC_SYMBOL: break;
			case TAC_VAR: fprintf(output,	"%s:\n"
											"\t.long %s\n",
									tac->res->text, tac->op1->text); break;
			case TAC_VEC: fprintf(output,	"%s:\n",
									tac->res->text); break;
			case TAC_ARRAY_VALUE: fprintf(output,	"\t.long %s\n",
									tac->res->text); break;
			case TAC_ADD: fprintf(output,	"\n\t## TAC_ADD\n"
								  			"\tmovl %s(%%rip), %%eax\n"
											"\taddl %s(%%rip), %%eax\n"
											"\tmovl %%eax, %s(%%rip)\n",
								  tac->op1->text,tac->op2->text,tac->res->text); break;
			case TAC_SUB: fprintf(output,	"\n\t## TAC_SUB\n"
								  			"\tmovl %s(%%rip), %%eax\n"
											"\tsubl %s(%%rip), %%eax\n"
											"\tmovl %%eax, %s(%%rip)\n",
								  tac->op1->text,tac->op2->text,tac->res->text); break;
			case TAC_MUL: fprintf(output,	"\n\t## TAC_MUL\n"
								  			"\tmovl %s(%%rip), %%eax\n"
											"\timull %s(%%rip), %%eax\n"
											"\tmovl %%eax, %s(%%rip)\n",
								  tac->op1->text,tac->op2->text,tac->res->text); break;
			case TAC_DIV: fprintf(output,	"\n\t## TAC_DIV\n"
								  			"\tmovl %s(%%rip), %%eax\n"
											"\tcltd\n"
											"\tidivl %s(%%rip)\n"
											"\tmovl %%eax, %s(%%rip)\n",
								  tac->op1->text,tac->op2->text,tac->res->text); break;
			case TAC_G: fprintf(output,		"\n\t## TAC_G\n"
											"\tmovl %s(%%rip), %%edx\n"				
								  			"\tmovl %s(%%rip), %%eax\n"
											"\tcmpl %%eax, %%edx\n"
											"\tsetg %%al\n"
											"\tmovzbl %%al, %%eax\n"
											"\tmovl %%eax, %s(%%rip)\n",
								  tac->op1->text,tac->op2->text,tac->res->text); break; 
			case TAC_L: fprintf(output,		"\n\t## TAC_L\n"
											"\tmovl %s(%%rip), %%edx\n"				
								  			"\tmovl %s(%%rip), %%eax\n"
											"\tcmpl %%eax, %%edx\n"
											"\tsetl %%al\n"
											"\tmovzbl %%al, %%eax\n"
											"\tmovl %%eax, %s(%%rip)\n",
								  tac->op1->text,tac->op2->text,tac->res->text); break; 
			case TAC_GE: fprintf(output,	"\n\t## TAC_GE\n"
											"\tmovl %s(%%rip), %%edx\n"				
								  			"\tmovl %s(%%rip), %%eax\n"
											"\tcmpl %%eax, %%edx\n"
											"\tsetge %%al\n"
											"\tmovzbl %%al, %%eax\n"
											"\tmovl %%eax, %s(%%rip)\n",
								  tac->op1->text,tac->op2->text,tac->res->text); break; 
			case TAC_LE: fprintf(output,	"\n\t## TAC_LE\n"
											"\tmovl %s(%%rip), %%edx\n"				
								  			"\tmovl %s(%%rip), %%eax\n"
											"\tcmpl %%eax, %%edx\n"
											"\tsetle %%al\n"
											"\tmovzbl %%al, %%eax\n"
											"\tmovl %%eax, %s(%%rip)\n",
								  tac->op1->text,tac->op2->text,tac->res->text); break; 
			case TAC_EQ: fprintf(output,	"\n\t## TAC_EQ\n"
											"\tmovl %s(%%rip), %%edx\n"				
								  			"\tmovl %s(%%rip), %%eax\n"
											"\tcmpl %%eax, %%edx\n"
											"\tsete %%al\n"
											"\tmovzbl %%al, %%eax\n"
											"\tmovl %%eax, %s(%%rip)\n",
								  tac->op1->text,tac->op2->text,tac->res->text); break;
			case TAC_NE: fprintf(output,	"\n\t## TAC_EQ\n"
											"\tmovl %s(%%rip), %%edx\n"				
								  			"\tmovl %s(%%rip), %%eax\n"
											"\tcmpl %%eax, %%edx\n"
											"\tsetne %%al\n"
											"\tmovzbl %%al, %%eax\n"
											"\tmovl %%eax, %s(%%rip)\n",
								  tac->op1->text,tac->op2->text,tac->res->text); break; 
			case TAC_BEGIN_FUNC: fprintf(output,	"\n\t## TAC_BEGIN_FUNC\n"
											"\n.globl %s\n"
											"%s:\n"				
								  			"\t.cfi_startproc\n"
											"\tpushq	%%rbp\n",
								  tac->res->text, tac->res->text); break; 
			case TAC_END_FUNC: fprintf(output,	"\n\t## TAC_END_FUNC\n"
											"\tpopq	%%rbp\n"				
								  			"\tret\n"
											"\t.cfi_endproc\n"); break; 
			case TAC_RETURN: fprintf(output,"\n\t## TAC_RETURN\n"
											"\tmovl %s(%%rip), %%eax\n",
								  tac->res->text); break; 
			case TAC_MOVE: fprintf(output,"\n\t## TAC_MOVE\n"
											"\tmovl %s(%%rip), %%eax\n"
											"\tmovl %%eax, %s(%%rip)\n",
								  tac->op1->text, tac->res->text); break; 
			case TAC_IFZ: fprintf(output,	"\n\t## TAC_IFZ\n"
											"\tmovl %s(%%rip), %%eax\n"
											"\ttestl %%eax, %%eax\n"
											"\tje .%s\n",
								  tac->op1->text, tac->res->text); break;
			case TAC_IFLESSEQ: fprintf(output,	"\n\t## TAC_IFLESSEQ\n"
											"\tmovl %s(%%rip), %%eax\n"
											"\tcmpl %s(%%rip), %%eax\n"
											"\tjg .%s\n",
								  tac->op1->text, tac->op2->text, tac->res->text); break;
			case TAC_INC: fprintf(output,	"\n\t## TAC_INC\n"
											"\tmovl %s(%%rip), %%eax\n"
											"\taddl $1, %%eax\n"
											"\tmovl %%eax, %s(%%rip)\n",
								  tac->res->text, tac->res->text); break;
			case TAC_LABEL: fprintf(output,	"\n\t## TAC_LABEL\n"
											".%s:\n",
								  tac->res->text); break;
			case TAC_JUMP: fprintf(output,	"\n\t## TAC_JUMP\n"
											"\tjmp .%s\n",
								  tac->res->text); break;
			case TAC_VEC_WRITE: pos = atoi(tac->op1->text) * 4; 
								fprintf(output,	"\n\t## TAC_VEC_WRITE\n"
											"\tmovl %s(%%rip), %%eax\n"
											"\tmovl %%eax, %s+%d(%%rip)\n",
								  tac->op2->text, tac->res->text, pos); break;
			case TAC_VEC_READ:  pos = atoi(tac->op2->text);
								// caso em que a chave é um int
								if(pos){
									pos*=4;
									fprintf(output,	"\n\t## TAC_VEC_READ\n"
												"\tmovl %s+%d(%%rip), %%eax\n"
												"\tmovl %%eax, %s(%%rip)\n",
									  tac->op1->text, pos, tac->res->text); 
								// caso em que a chave é um temporario
								}else{ 
									fprintf(output,	"\n\t## TAC_VEC_READ\n"
												"\tmovl %s(%%rip), %%eax\n"
												"\tcltq\n"
												"\tmovl %s(,%%rax, 4), %%eax\n"
												"\tmovl %%eax, %s(%%rip)\n",
									  tac->op2->text, tac->op1->text, tac->res->text); 
								} break;
			default: break; 
		}
	}
}

void asmPushHash(FILE* output){ //LEMBRAR: Johann permitiu considerar tudo como inteiro

}

void asmPrintFixed(FILE* output){ //TODO: print imutável (section TEXT, .str asciz "%f", section DATA"...
	HASH_NODE *node;
	int i;	
	for(i=0; i<HASH_SIZE; i++){
		for(node=hash_table[i]; node; node=node->next)
		{
			if(node->type == SYMBOL_VAR_TEMP)
				 fprintf(output,	"%s:\n"
											"\t.long 0\n",
									node->text); 
		}
	}

}
