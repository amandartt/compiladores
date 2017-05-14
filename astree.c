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
	for(int c = 0; c < depth; c++) //identacao
		printf("| ");

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
		case AST_VECTOR_EXPR: printf("ASTREE_VECTOR_EXPR"); break;
		case AST_FUNC_CALL: printf("ASTREE_FUNC_CALL"); break;
		case AST_LIST_ARG: printf("ASTREE_LIST_ARG"); break;
		case AST_ASSIGN: printf("ASTREE_ASSIGN"); break;
		case AST_VEC_ASSIGN: printf("ASTREE_VEC_ASSIGN"); break;
		case AST_READ: printf("ASTREE_READ"); break;
		case AST_PRINT: printf("ASTREE_PRINT"); break;
		case AST_PRINT_ELEM: printf("ASTREE_PRINT_ELEM"); break;
		case AST_RETURN: printf("ASTREE_RETURN"); break;
		case AST_WHEN_THEN: printf("ASTREE_WHEN_THEN"); break;
		case AST_WHEN_THEN_ELSE: printf("ASTREE_WHEN_THEN_ELSE"); break;
		case AST_WHILE: printf("ASTREE_WHILE"); break;
		case AST_FOR: printf("ASTREE_FOR"); break;
		case AST_SEQ_CMD: printf("ASTREE_SEQ_CMD"); break;

		case AST_CJTODEC_ELEM: printf("AST_CJTODEC_ELEM"); break;
		case AST_DEC_BYTE_VAR_GLOB: printf("AST_DEC_BYTE_VAR_GLOB"); break;
		case AST_DEC_SHORT_VAR_GLOB: printf("AST_DEC_SHORT_VAR_GLOB"); break;
		case AST_DEC_LONG_VAR_GLOB: printf("AST_DEC_LONG_VAR_GLOB"); break;
		case AST_DEC_FLOAT_VAR_GLOB: printf("AST_DEC_FLOAT_VAR_GLOB"); break;
		case AST_DEC_DOUBLE_VAR_GLOB: printf("AST_DEC_DOUBLE_VAR_GLOB"); break;
		case AST_DEC_VEC_GLOB: printf("AST_DEC_VEC_GLOB"); break;
		case AST_DEC_BYTE_VEC_SEQ: printf("AST_DEC_BYTE_VEC_SEQ"); break;
		case AST_DEC_SHORT_VEC_SEQ: printf("AST_DEC_SHORT_VEC_SEQ"); break;
		case AST_DEC_LONG_VEC_SEQ: printf("AST_DEC_LONG_VEC_SEQ"); break;
		case AST_DEC_FLOAT_VEC_SEQ: printf("AST_DEC_FLOAT_VEC_SEQ"); break;
		case AST_DEC_DOUBLE_VEC_SEQ: printf("AST_DEC_DOUBLE_VEC_SEQ"); break;
		case AST_DEC_BYTE_VEC: printf("AST_DEC_BYTE_VEC"); break;
		case AST_DEC_SHORT_VEC: printf("AST_DEC_SHORT_VEC"); break;
		case AST_DEC_LONG_VEC: printf("AST_DEC_LONG_VEC"); break;
		case AST_DEC_FLOAT_VEC: printf("AST_DEC_FLOAT_VEC"); break;
		case AST_DEC_DOUBLE_VEC: printf("AST_DEC_DOUBLE_VEC"); break;
		case AST_SEQNUM_ELEM: printf("AST_SEQNUM_ELEM"); break;
		case AST_DEC_FUNC: printf("AST_DEC_FUNC"); break;
		case AST_BYTE_CABEC: printf("AST_BYTE_CABEC"); break;
		case AST_SHORT_CABEC: printf("AST_SHORT_CABEC"); break;
		case AST_LONG_CABEC: printf("AST_LONG_CABEC"); break;
		case AST_FLOAT_CABEC: printf("AST_FLOAT_CABEC"); break;
		case AST_DOUBLE_CABEC: printf("AST_DOUBLE_CABEC"); break;
		case AST_PARAM_ELEM: printf("ASTREE_PARAM_ELEM"); break;
		case AST_PARAM_BYTE: printf("ASTREE_PARAM_BYTE"); break;
		case AST_PARAM_SHORT: printf("ASTREE_PARAM_SHORT"); break;
		case AST_PARAM_LONG: printf("ASTREE_PARAM_LONG"); break;
		case AST_PARAM_FLOAT: printf("ASTREE_PARAM_FLOAT"); break;
		case AST_PARAM_DOUBLE: printf("ASTREE_PARAM_DOUBLE"); break;


		default: printf("ASTREE_UNDEFINED");
	}

	if(node->symbol){
		printf(",%s)\n", node->symbol->text);
	}else{
		printf(",-)\n");
	}
	for(int i = 0; i < MAX_SONS; i++)
		astreePrint(node->son[i],depth+1);
}

void astreeProgram(ASTREE* node){
	if(!node){
		return;
	}
	switch(node->type){
		case AST_CJTODEC_ELEM:
			astreeProgram(node->son[0]);
			printf(";");
			astreeProgram(node->son[1]);
			break;
		case AST_DEC_BYTE_VAR_GLOB: 
			printf("\n%s: byte %s",node->son[0]->symbol->text, node->son[1]->symbol->text);
			break;
		case AST_DEC_SHORT_VAR_GLOB: 
			printf("\n%s: short %s",node->son[0]->symbol->text, node->son[1]->symbol->text);
			break;
		case AST_DEC_LONG_VAR_GLOB: 
			printf("\n%s: long %s",node->son[0]->symbol->text, node->son[1]->symbol->text);
			break;
		case AST_DEC_FLOAT_VAR_GLOB: 
			printf("\n%s: float %s",node->son[0]->symbol->text, node->son[1]->symbol->text);
			break;
		case AST_DEC_VEC_GLOB: 
			printf("\n%s: ", node->son[0]->symbol->text);
			astreeProgram(node->son[1]);
			break;
		case AST_DEC_BYTE_VEC:
			printf("byte[%s]", node->son[0]->symbol->text);
			break;
		case AST_DEC_SHORT_VEC:
			printf("short[%s]", node->son[0]->symbol->text);
			break;
		case AST_DEC_LONG_VEC:
			printf("long[%s]", node->son[0]->symbol->text);
			break;
		case AST_DEC_FLOAT_VEC:
			printf("float[%s]", node->son[0]->symbol->text);
			break;
		case AST_DEC_BYTE_VEC_SEQ:	
			printf("byte[%s] ", node->son[0]->symbol->text);
			astreeProgram(node->son[1]);
			break;
		case AST_DEC_SHORT_VEC_SEQ:	
			printf("short[%s] ", node->son[0]->symbol->text);
			astreeProgram(node->son[1]);
			break;
		case AST_DEC_LONG_VEC_SEQ:	
			printf("long[%s] ", node->son[0]->symbol->text);
			astreeProgram(node->son[1]);
			break;
		case AST_DEC_FLOAT_VEC_SEQ:	
			printf("float[%s] ", node->son[0]->symbol->text);
			astreeProgram(node->son[1]);
			break;
		case AST_SEQNUM_ELEM:
			printf("%s ", node->son[0]->symbol->text);
			if(node->son[1]){
				astreeProgram(node->son[1]);
			}
			break;
		case AST_DEC_FUNC:
			//cabecalho
			astreeProgram(node->son[0]);
			printf("{");
			// comando
			astreeProgram(node->son[1]);
			printf("}");
			break;
		case AST_BYTE_CABEC:
			printf("\nbyte %s(", node->son[0]->symbol->text);
			astreeProgram(node->son[1]);	
			printf(")");
			break;
		case AST_SHORT_CABEC:
			printf("\nshort %s(", node->son[0]->symbol->text);	
			astreeProgram(node->son[1]);	
			printf(")");
			break;
		case AST_LONG_CABEC:
			printf("\nlong %s(", node->son[0]->symbol->text);
			astreeProgram(node->son[1]);	
			printf(")");
			break;
		case AST_FLOAT_CABEC:
			printf("\nfloat %s(", node->son[0]->symbol->text);
			astreeProgram(node->son[1]);	
			printf(")");
			break;
		case AST_PARAM_ELEM:
			astreeProgram(node->son[0]);			
			if(node->son[1]){
				printf(", ");
				astreeProgram(node->son[1]);
			}
			break;
		
		case AST_PARAM_BYTE:
			printf("byte %s", node->son[0]->symbol->text);
			break;
		case AST_PARAM_SHORT:
			printf("short %s", node->son[0]->symbol->text);
			break;
		case AST_PARAM_LONG:
			printf("long %s", node->son[0]->symbol->text);
			break;
		case AST_PARAM_FLOAT:
			printf("float %s", node->son[0]->symbol->text);
			break;
		
	}


}

