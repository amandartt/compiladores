#include "asm.h"

// local functions
void asmPrintFixed(FILE* output, TAC* first);
void asmPushHash(FILE* output);
int numConsLabel = 1;
int numLit = 0;


// implementation

void asmGen(TAC* first, FILE* output){ //PARA DESCOBRIR OS ASM: gcc -S -O0 tracker.c
	TAC* tac;
	TAC* tac_print = first;	
	asmPushHash(output);
	asmPrintFixed(output, tac_print);
	int pos = 0;	
	int numLabel = 0;
	int numParamsCall = 0;	
	int numParamsReceive = 0;	
	for(tac=first; tac; tac = tac->next){	
		//printTacType(tac->type);printf("\n");
		switch(tac->type){
			case TAC_SYMBOL: break;
			case TAC_VAR: break;
			case TAC_VEC:
					if(tac->next->type ==  TAC_ARRAY_VALUE){
						fprintf(output,	"%s:\n", tac->res->text); 
					}else{	
						pos = atoi(tac->op1->text) * 4; 
						fprintf(output,	"\n.comm %s, %d\n", tac->res->text, pos); 
					}
					break;
			case TAC_ARRAY_VALUE: fprintf(output,	"\t.long %s\n",
									tac->res->text); break;
			case TAC_ADD:	fprintf(output,	"\n\t## TAC_ADD\n");
						  	if(tac->op1->type == SYMBOL_VAR || tac->op1->type == SYMBOL_VAR_TEMP)
						  		fprintf(output,	"\tmovl %s(%%rip), %%eax\n",  tac->op1->text); 
							else
								fprintf(output,	"\tmovl $%s, %%eax\n",  tac->op1->text); 	
							if(tac->op2->type == SYMBOL_VAR || tac->op1->type == SYMBOL_VAR_TEMP)
						  		fprintf(output,	"\taddl %s(%%rip), %%eax\n",  tac->op2->text); 
							else
								fprintf(output,	"\taddl $%s, %%eax\n",  tac->op2->text); 	 								
							fprintf(output,	"\tmovl %%eax, %s(%%rip)\n",  tac->res->text); 	 									
							break;
			case TAC_SUB: fprintf(output,	"\n\t## TAC_SUB\n");
						  	if(tac->op1->type == SYMBOL_VAR || tac->op1->type == SYMBOL_VAR_TEMP)
						  		fprintf(output,	"\tmovl %s(%%rip), %%eax\n",  tac->op1->text); 
							else
								fprintf(output,	"\tmovl $%s, %%eax\n",  tac->op1->text); 	
							if(tac->op2->type == SYMBOL_VAR || tac->op1->type == SYMBOL_VAR_TEMP)
						  		fprintf(output,	"\tsubl %s(%%rip), %%eax\n",  tac->op2->text); 
							else
								fprintf(output,	"\tsubl $%s, %%eax\n",  tac->op2->text); 	 								
							fprintf(output,	"\tmovl %%eax, %s(%%rip)\n",  tac->res->text); 	 									
							break;
			case TAC_MUL: fprintf(output,	"\n\t## TAC_MUL\n");
						  	if(tac->op1->type == SYMBOL_VAR || tac->op1->type == SYMBOL_VAR_TEMP)
						  		fprintf(output,	"\tmovl %s(%%rip), %%eax\n",  tac->op1->text); 
							else
								fprintf(output,	"\tmovl $%s, %%eax\n",  tac->op1->text); 	
							if(tac->op2->type == SYMBOL_VAR || tac->op1->type == SYMBOL_VAR_TEMP)
						  		fprintf(output,	"\timull %s(%%rip), %%eax\n",  tac->op2->text); 
							else
								fprintf(output,	"\timull $%s, %%eax\n",  tac->op2->text); 	 								
							fprintf(output,	"\tmovl %%eax, %s(%%rip)\n",  tac->res->text); 	 									
							break;
			case TAC_DIV: fprintf(output,	"\n\t## TAC_DIV\n");
						  	if(tac->op1->type == SYMBOL_VAR || tac->op1->type == SYMBOL_VAR_TEMP)
								fprintf(output,"\tmovl %s(%%rip), %%eax\n", tac->op1->text);
						  	else
								fprintf(output,	"\tmovl $%s, %%eax\n",  tac->op1->text);
							fprintf(output,"\tcltd\n");
							if(tac->op1->type == SYMBOL_VAR || tac->op1->type == SYMBOL_VAR_TEMP)
								fprintf(output,"\tidivl %s(%%rip)\n", tac->op2->text);
							else
								fprintf(output,"\tidivl lit%s(%%rip)\n", tac->op2->text);				
							fprintf(output,"\tmovl %%eax, %s(%%rip)\n", tac->res->text); break;
			case TAC_G: fprintf(output,	"\n\t## TAC_G\n");
					  	if(tac->op1->type == SYMBOL_VAR || tac->op1->type == SYMBOL_VAR_TEMP)
					  		fprintf(output,	"\tmovl %s(%%rip), %%edx\n",  tac->op1->text); 
						else
							fprintf(output,	"\tmovl $%s, %%edx\n",  tac->op1->text); 	
						if(tac->op2->type == SYMBOL_VAR || tac->op1->type == SYMBOL_VAR_TEMP)
					  		fprintf(output,	"\tmovl %s(%%rip), %%eax\n",  tac->op2->text); 
						else
							fprintf(output,	"\tmovl $%s, %%eax\n",  tac->op2->text); 		
						fprintf(output,"\tcmpl %%eax, %%edx\n"
										"\tsetg %%al\n"
										"\tmovzbl %%al, %%eax\n"
										"\tmovl %%eax, %s(%%rip)\n",
							tac->res->text); break; 
			case TAC_L: fprintf(output,	"\n\t## TAC_L\n");
					  	if(tac->op1->type == SYMBOL_VAR || tac->op1->type == SYMBOL_VAR_TEMP)
					  		fprintf(output,	"\tmovl %s(%%rip), %%edx\n",  tac->op1->text); 
						else
							fprintf(output,	"\tmovl $%s, %%edx\n",  tac->op1->text); 	
						if(tac->op2->type == SYMBOL_VAR || tac->op1->type == SYMBOL_VAR_TEMP)
					  		fprintf(output,	"\tmovl %s(%%rip), %%eax\n",  tac->op2->text); 
						else
							fprintf(output,	"\tmovl $%s, %%eax\n",  tac->op2->text); 		
						fprintf(output,"\tcmpl %%eax, %%edx\n"
										"\tsetl %%al\n"
										"\tmovzbl %%al, %%eax\n"
										"\tmovl %%eax, %s(%%rip)\n",
							tac->res->text); break; 
			case TAC_GE: fprintf(output,	"\n\t## TAC_GE\n");
					  	if(tac->op1->type == SYMBOL_VAR || tac->op1->type == SYMBOL_VAR_TEMP)
					  		fprintf(output,	"\tmovl %s(%%rip), %%edx\n",  tac->op1->text); 
						else
							fprintf(output,	"\tmovl $%s, %%edx\n",  tac->op1->text); 	
						if(tac->op2->type == SYMBOL_VAR || tac->op1->type == SYMBOL_VAR_TEMP)
					  		fprintf(output,	"\tmovl %s(%%rip), %%eax\n",  tac->op2->text); 
						else
							fprintf(output,	"\tmovl $%s, %%eax\n",  tac->op2->text); 		
						fprintf(output,"\tcmpl %%eax, %%edx\n"
										"\tsetge %%al\n"
										"\tmovzbl %%al, %%eax\n"
										"\tmovl %%eax, %s(%%rip)\n",
							tac->res->text); break; 
			case TAC_LE:fprintf(output,	"\n\t## TAC_LE\n");
					  	if(tac->op1->type == SYMBOL_VAR || tac->op1->type == SYMBOL_VAR_TEMP)
					  		fprintf(output,	"\tmovl %s(%%rip), %%edx\n",  tac->op1->text); 
						else
							fprintf(output,	"\tmovl $%s, %%edx\n",  tac->op1->text); 	
						if(tac->op2->type == SYMBOL_VAR || tac->op1->type == SYMBOL_VAR_TEMP)
					  		fprintf(output,	"\tmovl %s(%%rip), %%eax\n",  tac->op2->text); 
						else
							fprintf(output,	"\tmovl $%s, %%eax\n",  tac->op2->text); 		
						fprintf(output,"\tcmpl %%eax, %%edx\n"
										"\tsetle %%al\n"
										"\tmovzbl %%al, %%eax\n"
										"\tmovl %%eax, %s(%%rip)\n",
							tac->res->text); break; 
			case TAC_EQ: fprintf(output,	"\n\t## TAC_EQ\n");
					  	if(tac->op1->type == SYMBOL_VAR || tac->op1->type == SYMBOL_VAR_TEMP)
					  		fprintf(output,	"\tmovl %s(%%rip), %%edx\n",  tac->op1->text); 
						else
							fprintf(output,	"\tmovl $%s, %%edx\n",  tac->op1->text); 	
						if(tac->op2->type == SYMBOL_VAR || tac->op1->type == SYMBOL_VAR_TEMP)
					  		fprintf(output,	"\tmovl %s(%%rip), %%eax\n",  tac->op2->text); 
						else
							fprintf(output,	"\tmovl $%s, %%eax\n",  tac->op2->text); 		
						fprintf(output,"\tcmpl %%eax, %%edx\n"
										"\tsete %%al\n"
										"\tmovzbl %%al, %%eax\n"
										"\tmovl %%eax, %s(%%rip)\n",
							tac->res->text); break; 
			case TAC_NE: fprintf(output,	"\n\t## TAC_NE\n");
					  	if(tac->op1->type == SYMBOL_VAR || tac->op1->type == SYMBOL_VAR_TEMP)
					  		fprintf(output,	"\tmovl %s(%%rip), %%edx\n",  tac->op1->text); 
						else
							fprintf(output,	"\tmovl $%s, %%edx\n",  tac->op1->text); 	
						if(tac->op2->type == SYMBOL_VAR || tac->op1->type == SYMBOL_VAR_TEMP)
					  		fprintf(output,	"\tmovl %s(%%rip), %%eax\n",  tac->op2->text); 
						else
							fprintf(output,	"\tmovl $%s, %%eax\n",  tac->op2->text); 		
						fprintf(output,"\tcmpl %%eax, %%edx\n"
										"\tsetne %%al\n"
										"\tmovzbl %%al, %%eax\n"
										"\tmovl %%eax, %s(%%rip)\n",
							tac->res->text); break; 
			case TAC_BEGIN_FUNC: fprintf(output,	"\n\t## TAC_BEGIN_FUNC\n"
											"\t.text\n"
											"\t.globl %s\n"
											"%s:\n"				
								  			"\t.cfi_startproc\n"
											"\tpushq	%%rbp\n",
								  tac->res->text, tac->res->text); break; 
			case TAC_END_FUNC: fprintf(output,	"\n\t## TAC_END_FUNC\n"
											"\tpopq	%%rbp\n"				
								  			"\tret\n"
											"\t.cfi_endproc\n"); break; 
			case TAC_RETURN: if(tac->res->type == SYMBOL_VAR || tac->res->type == SYMBOL_VAR_TEMP){ 
							 fprintf(output,"\n\t## TAC_RETURN\n"
											"\tmovl %s(%%rip), %%eax\n",
								  tac->res->text); 
							}else{
								 fprintf(output,"\n\t## TAC_RETURN\n"
											"\tmovl $%s, %%eax\n",
								  tac->res->text); 
							}break; 
			case TAC_MOVE: if(tac->op1->type == SYMBOL_VAR || tac->op1->type == SYMBOL_VAR_TEMP){ 
								fprintf(output,"\n\t## TAC_MOVE\n"
											"\tmovl %s(%%rip), %%eax\n"
											"\tmovl %%eax, %s(%%rip)\n",
								  tac->op1->text, tac->res->text);
							}else{
								fprintf(output,"\n\t## TAC_MOVE\n"
											"\tmovl $%s, %%eax\n"
											"\tmovl %%eax, %s(%%rip)\n",
								  tac->op1->text, tac->res->text);
							} break; 
			case TAC_IFZ: fprintf(output,	"\n\t## TAC_IFZ\n"
											"\tmovl %s(%%rip), %%eax\n"
											"\ttestl %%eax, %%eax\n"
											"\tje .%s\n",
								  tac->op1->text, tac->res->text); break;
			case TAC_IFLESSEQ: 	fprintf(output,	"\n\t## TAC_IFLESSEQ\n"
											"\tmovl %s(%%rip), %%eax\n",
											tac->op1->text);
							   	if (tac->op2->type == SYMBOL_VAR || tac->op2->type == SYMBOL_VAR_TEMP)
									fprintf(output, "\tcmpl %s(%%rip), %%eax\n", tac->op2->text);
								else
									fprintf(output, "\tcmpl $%s, %%eax\n", tac->op2->text);
								fprintf(output,"\tjnbe .%s\n",tac->res->text); break;
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
								if(tac->op2->type == SYMBOL_VAR || tac->op2->type == SYMBOL_VAR_TEMP){
									fprintf(output,	"\n\t## TAC_VEC_WRITE\n"
												"\tmovl %s(%%rip), %%eax\n"
												"\tmovl %%eax, %s+%d(%%rip)\n",
									  tac->op2->text, tac->res->text, pos); 
								}else{
									fprintf(output,	"\n\t## TAC_VEC_WRITE\n"
												"\tmovl $%s, %%eax\n"
												"\tmovl %%eax, %s+%d(%%rip)\n",
									  tac->op2->text, tac->res->text, pos); 
								}
								break;
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
			case TAC_OR: fprintf(output,	"\n\t## TAC_OR\n"
											"\tmovl %s(%%rip), %%eax\n"
											"\ttestl %%eax, %%eax\n"
											"\tje .L%d\n"
											"\tmovl $1, %s(%%rip)\n"	
											"\tjmp .L%d\n"
											".L%d:\n"
											"\tmovl %s(%%rip), %%eax\n"
											"\ttestl %%eax, %%eax\n"
											"\tje .L%d\n"
											"\tmovl $1, %s(%%rip)\n"
											"\tjmp .L%d\n"
											".L%d:\n"
											"\tmovl $0, %s(%%rip)\n"
											".L%d:\n",
										tac->op1->text, numLabel, tac->res->text, numLabel+2, 
										numLabel, tac->op2->text, numLabel+1, tac->res->text, numLabel+2, 
										numLabel+1, tac->res->text, numLabel+2); 
										numLabel = numLabel + 3; 
										break;
			case TAC_AND: fprintf(output,	"\n\t## TAC_AND\n"
											"\tmovl %s(%%rip), %%eax\n"
											"\ttestl %%eax, %%eax\n"
											"\tjne .L%d\n"
											"\tmovl $0, %s(%%rip)\n"	
											"\tjmp .L%d\n"
											".L%d:\n"
											"\tmovl %s(%%rip), %%eax\n"
											"\ttestl %%eax, %%eax\n"
											"\tje .L%d\n"
											"\tmovl $1, %s(%%rip)\n"
											"\tjmp .L%d\n"
											".L%d:\n"
											"\tmovl $0, %s(%%rip)\n"
											".L%d:\n",
										tac->op1->text, numLabel, tac->res->text, numLabel+2, 
										numLabel, tac->op2->text, numLabel+1, tac->res->text, numLabel+2, 
										numLabel+1, tac->res->text, numLabel+2); 
										numLabel = numLabel + 3; 
										break;
			case TAC_NOT: fprintf(output, "\n\t## TAC_NOT\n"
										  "\tcmpl $0, %s(%%rip)\n"
										  "\tsete %%al\n"
	                                      "\tmovzbl %%al, %%eax\n"
	                                      "\tmovl %%eax, %s(%%rip)\n",
										tac->op1->text, tac->res->text);
										break;
			case TAC_PRINT: if(tac->res->type == SYMBOL_LIT_STRING){
								fprintf(output,	"\n\t## TAC_PRINT: STRING\n"
											"\tmovl $.LC%d, %%edi\n"
											"\tmovl $0, %%eax\n"
											"\tcall printf\n",
								  tac->posParam); 
							 }else{
								fprintf(output,	"\n\t## TAC_PRINT: VAR\n"
											"\tmovl %s(%%rip), %%eax\n"
											"\tmovl %%eax, %%esi\n"
											"\tmovl $.LC%d, %%edi\n"
											"\tmovl $0, %%eax\n"
											"\tcall printf\n",
								  tac->res->text, tac->posParam); 
							 } 							
							 break;
			case TAC_READ: fprintf(output, "\n\t## TAC_READ\n"
											"\tmovl $%s, %%esi\n"
											"\tmovl	$.LC0, %%edi\n"
											"\tmovl	$0, %%eax\n"
											"\tcall	__isoc99_scanf\n"
											"\tmovl	$0, %%eax\n",
											tac->res->text);break;
			case TAC_CALL:  numParamsCall = 0;
							fprintf(output,	"\n\t## TAC_CALL\n"
											"\tcall %s\n"
											"\tmovl %%eax, %s(%%rip)\n",
								  tac->op1->text, tac->res->text); 
			case TAC_ARG_CALL:	numParamsCall++;
								fprintf(output,	"\n\t## TAC_ARG_CALL\n");
								if(tac->op1->type == SYMBOL_VAR || tac->op1->type == SYMBOL_VAR_TEMP){
									fprintf(output,	"\tmovl %s(%%rip), ", tac->op1->text);
								}else{
									fprintf(output,	"\tmovl $%s, ", tac->op1->text);
								}	
								switch(numParamsCall){
									case 1: fprintf(output,	"%%edi\n"); break;
									case 2: fprintf(output,	"%%esi\n"); break;
									case 3: fprintf(output,	"%%edx\n"); break;
									case 4: fprintf(output,	"%%ecx\n"); break;
									case 5: fprintf(output, "%%r8d\n"); break;
									case 6: fprintf(output,	"%%r9d\n"); break;
									default: fprintf(stderr,"Erro compilacao: Numero maximo de parametros suportado excedido\n");  exit(5);
								}
								break;
			case TAC_ARG_RECEIVE:
								numParamsReceive++;
								switch(numParamsReceive){
									case 1: fprintf(output,	"\t movl %%edi, "); break;
									case 2: fprintf(output,	"\t movl %%esi, "); break;
									case 3: fprintf(output,	"\t movl %%edx, "); break;
									case 4: fprintf(output,	"\t movl %%ecx, "); break;
									case 5: fprintf(output,	"\t movl %%r8d, "); break;
									case 6: fprintf(output,	"\t movl %%r9d, "); break;
									default: fprintf(stderr,"Erro compilacao: Numero maximo de parametros suportado excedido\n"); exit(5);
								}
								if(tac->res->type == SYMBOL_VAR || tac->res->type == SYMBOL_VAR_TEMP){
								fprintf(output,	"%s(%%rip)\n", tac->res->text);
								}else{
									fprintf(output,	"$%s\n", tac->res->text);
								}
								if(tac->next->next->type != TAC_ARG_RECEIVE) numParamsReceive = 0;
								break;
			default: break; 
		}
	}
}

void asmPushHash(FILE* output){ //LEMBRAR: Johann permitiu considerar tudo como inteiro
	HASH_NODE *node;
	int i;	
	fprintf(output, "\n.data\n");
	for(i=0; i<HASH_SIZE; i++){
		for(node=hash_table[i]; node; node=node->next)
		{
			if(node->type == SYMBOL_VAR_TEMP)
				 fprintf(output,	"%s:\n"
											"\t.long 0\n",
									node->text);
			else if(node->type == SYMBOL_LIT_INT || node->type == SYMBOL_LIT_REAL || node->type == SYMBOL_LIT_SHORT || 
					node->type == SYMBOL_LIT_LONG ||node->type == SYMBOL_LIT_BYTE || node->type == SYMBOL_LIT_CHAR )
				fprintf(output, "lit%s:\n"
										"\t.long %s \n", node->text, node->text);
		}
	}
}

void asmPrintFixed(FILE* output, TAC* first){
	TAC* tac;
	fprintf(output,	".LC0:\n"
					"\t.string \"%%d\"\n"); 	
	for(tac=first; tac; tac = tac->next){	
		switch(tac->type){
			case TAC_DIV:
				if(tac->op2->type != SYMBOL_VAR && tac->op1->type != SYMBOL_VAR_TEMP){
					//fprintf(output,	"lit%d:\n"
					//					"\t.long %s \n", numLit, tac->op2->text); 
					tac->posParam = numLit;	
				}
				break;
			case TAC_ARG_RECEIVE:
				fprintf(output,	"%s:\n"
									"\t.long 0\n",
									tac->res->text); break;
			case TAC_PRINT:
				if(tac->res->type == SYMBOL_LIT_STRING){
					fprintf(output,	".LC%d:\n"
											"\t.string %s\n",
									numConsLabel, tac->res->text); 
					tac->posParam = numConsLabel;
					numConsLabel++;
				}else{
					tac->posParam = 0;
				}
				break;
			case TAC_VAR:
				fprintf(output,	"%s:\n"
								"\t.long %s\n",
						tac->res->text, tac->op1->text); break;
			default: break;
		}
	}
}
