// Amanda Torbes e Gabriel Moita
// Compiladores - INF-UFRGS - 2017/1

#include "astree.h"	
#include <stdio.h>
#include <stdlib.h>

ASTREE* astreeCreate(int type, HASH_NODE* symbol, ASTREE* son1, ASTREE* son2, ASTREE* son3, ASTREE* son4, int lineNumber){
	ASTREE* new_node = 0;
	new_node = calloc(1,sizeof(ASTREE));
	new_node->type = type;
	new_node->symbol = symbol;
	new_node->lineNumber = lineNumber;
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
	int c;
	for(c = 0; c < depth; c++) //identacao
		printf ("| ");

	printf ("ASTREE(");

	switch(node->type){
		case AST_SYMBOL: printf ("ASTREE_SYMBOL"); break;
		case AST_ADD: printf ("ASTREE_ADD"); break;
		case AST_SUB: printf ("ASTREE_SUB"); break;
		case AST_MUL: printf ("ASTREE_MUL"); break;
		case AST_DIV: printf ("ASTREE_DIV"); break;
		case AST_LOGIC_G: printf ("ASTREE_LOGIC_G"); break;
		case AST_LOGIC_L: printf ("ASTREE_LOGIC_L"); break;
		case AST_LOGIC_LE: printf ("ASTREE_LOGIC_LE"); break;
		case AST_LOGIC_GE: printf ("ASTREE_LOGIC_GE"); break;
		case AST_LOGIC_EQ: printf ("ASTREE_LOGIC_EQ"); break;
		case AST_LOGIC_NE: printf ("ASTREE_LOGIC_NE"); break;
		case AST_LOGIC_AND: printf ("ASTREE_LOGIC_AND"); break;
		case AST_LOGIC_OR: printf ("ASTREE_LOGIC_OR"); break;
		case AST_LOGIC_NOT: printf ("ASTREE_LOGIC_NOT"); break;
		case AST_VECTOR_EXPR: printf ("ASTREE_VECTOR_EXPR"); break;
		case AST_FUNC_CALL: printf ("ASTREE_FUNC_CALL"); break;
		case AST_LIST_ARG_BEGIN: printf ("ASTREE_LIST_ARG_BEGIN"); break;
		case AST_ASSIGN: printf ("ASTREE_ASSIGN"); break;
		case AST_VEC_ASSIGN: printf ("ASTREE_VEC_ASSIGN"); break;
		case AST_READ: printf ("ASTREE_READ"); break;
		case AST_PRINT: printf ("ASTREE_PRINT"); break;
		case AST_PRINT_ELEM: printf ("ASTREE_PRINT_ELEM"); break;
		case AST_RETURN: printf ("ASTREE_RETURN"); break;
		case AST_WHEN_THEN: printf ("ASTREE_WHEN_THEN"); break;
		case AST_WHEN_THEN_ELSE: printf ("ASTREE_WHEN_THEN_ELSE"); break;
		case AST_WHILE: printf ("ASTREE_WHILE"); break;
		case AST_FOR: printf ("ASTREE_FOR"); break;
		case AST_SEQ_CMD: printf ("ASTREE_SEQ_CMD"); break;

		case AST_CJTODEC_ELEM: printf ("AST_CJTODEC_ELEM"); break;
		case AST_DEC_VAR_GLOB: printf ("AST_DEC_VAR_GLOB"); break;
		case AST_DEC_VEC_GLOB: printf ("AST_DEC_VEC_GLOB"); break;
		case AST_DEC_VEC_SEQ: printf ("AST_DEC_VEC_SEQ"); break;
		case AST_DEC_VEC: printf ("AST_DEC_VEC"); break;
		case AST_SEQNUM_ELEM: printf ("AST_SEQNUM_ELEM"); break;
		case AST_DEC_FUNC: printf ("AST_DEC_FUNC"); break;
		case AST_CABEC: printf ("AST_CABEC"); break;
		case AST_PARAM_ELEM: printf ("ASTREE_PARAM_ELEM"); break;
		case AST_PARAM: printf ("ASTREE_PARAM"); break;
		case AST_BYTE: printf ("AST_BYTE"); break;
		case AST_SHORT: printf ("AST_SHORT"); break;
		case AST_LONG: printf ("AST_LONG"); break;
		case AST_FLOAT: printf ("AST_FLOAT"); break;
		case AST_DOUBLE: printf ("AST_DOUBLE"); break;

		case AST_PARENTESIS_EXPR: printf ("ASTREE_PARENTESIS_EXPR"); break;
		case AST_COMMAND_BLOCK: printf ("ASTREE_COMMAND_BLOCK"); break;
		case AST_LIST_ARG_ELEM: printf ("ASTREE_LIST_ARG_ELEM"); break;

		default: printf ("ASTREE_UNDEFINED");
	}
	
	printf("[%d],",node->dataType);

	if(node->symbol){
		printf(",%s)\n", node->symbol->text);
	}else{
		printf(",-)\n");
	}
	int i;
	for(i = 0; i < MAX_SONS; i++)
		astreePrint(node->son[i],depth+1);
}

void astreeProgram(ASTREE* node, FILE* output){

	if(!node){
		return;
	}
	switch(node->type){
		case AST_SYMBOL:
			//printf("%s",node->symbol->text);
			fprintf(output, "%s",node->symbol->text);
			break;
		case AST_ADD:
			astreeProgram(node->son[0],output);
			//printf("+");
			fprintf(output, "+");
			astreeProgram(node->son[1],output);
			break;
		case AST_SUB:
			astreeProgram(node->son[0],output);
			//printf("-");
			fprintf(output, "-");
			astreeProgram(node->son[1],output);
			break;
		case AST_MUL:
			astreeProgram(node->son[0],output);
			//printf("*");
			fprintf(output, "*");
			astreeProgram(node->son[1],output);
			break;
		case AST_DIV:
			astreeProgram(node->son[0],output);
			//printf("/");
			fprintf(output, "/");
			astreeProgram(node->son[1],output);
			break;
		case AST_LOGIC_G:
			astreeProgram(node->son[0],output);
			//printf(">");
			fprintf(output, ">");
			astreeProgram(node->son[1],output);
			break;
		case AST_LOGIC_L:
			astreeProgram(node->son[0],output);
			//printf("<");
			fprintf(output, "<");
			astreeProgram(node->son[1],output);
			break;
		case AST_LOGIC_LE:
			astreeProgram(node->son[0],output);
			//printf("<=");
			fprintf(output, "<=");
			astreeProgram(node->son[1],output);
			break;
		case AST_LOGIC_GE:
			astreeProgram(node->son[0],output);
			//printf(">=");
			fprintf(output, ">=");
			astreeProgram(node->son[1],output);
			break;
		case AST_LOGIC_EQ:
			astreeProgram(node->son[0],output);
			//printf("==");
			fprintf(output, "==");
			astreeProgram(node->son[1],output);
			break;
		case AST_LOGIC_NE:
			astreeProgram(node->son[0],output);
			//printf("!=");
			fprintf(output, "!=");
			astreeProgram(node->son[1],output);
			break;
		case AST_LOGIC_AND:
			astreeProgram(node->son[0],output);
			//printf("&&");
			fprintf(output, "&&");
			astreeProgram(node->son[1],output);
			break;
		case AST_LOGIC_OR:
			astreeProgram(node->son[0],output);
			//printf("||");
			fprintf(output, "||");
			astreeProgram(node->son[1],output);
			break;
		case AST_LOGIC_NOT:
			//printf("!");
			fprintf(output, "!");
			astreeProgram(node->son[0],output);
			break;
		case AST_PARENTESIS_EXPR:
			//printf("(");
			fprintf(output, "(");
			astreeProgram(node->son[0],output);
			//printf(")");
			fprintf(output, ")");
			break;
		case AST_VECTOR_EXPR:
			//printf("%s[",node->son[0]->symbol->text);
			fprintf(output, "%s[",node->symbol->text);
			astreeProgram(node->son[0],output);
			//printf("]");
			fprintf(output, "]");
			break;
		case AST_FUNC_CALL:
			//printf("%s(",node->son[0]->symbol->text);
			fprintf(output, "%s(",node->symbol->text);
			astreeProgram(node->son[0],output); //LIST_ARG_BEGIN or empty
			//printf(")");
			fprintf(output, ")");
			break;
		case AST_LIST_ARG_BEGIN:
			astreeProgram(node->son[0],output); //expr
			astreeProgram(node->son[1],output); //LIST_ARG_ELEM's
			break;
		case AST_LIST_ARG_ELEM:
			//printf(",");
			fprintf(output, ",");
			astreeProgram(node->son[0],output); //expr
			astreeProgram(node->son[1],output); //LIST_ARG_ELEM's
			break;
		case AST_ASSIGN:
			//printf("%s = ",node->symbol->text);
			fprintf(output, "%s = ",node->symbol->text);
			astreeProgram(node->son[0],output);
			break;
		case AST_VEC_ASSIGN:
			//printf("%s#",node->symbol->text);
			fprintf(output, "%s#",node->symbol->text);
			astreeProgram(node->son[0],output);
			//printf(" = ");
			fprintf(output, " = ");
			astreeProgram(node->son[1],output);
			break;
		case AST_READ:
			//printf("read %s",node->symbol->text);
			fprintf(output, "read %s",node->symbol->text);
			break;
		case AST_PRINT:
			//printf("print");
			fprintf(output, "print");
			astreeProgram(node->son[0],output);
			break;
		case AST_PRINT_ELEM:
			//printf(" ");
			fprintf(output, " ");
			if(node->symbol){
				//printf("%s",node->symbol->text);
				fprintf(output,"%s",node->symbol->text);
			}
			else
				astreeProgram(node->son[0],output);
			astreeProgram(node->son[1],output);
			break;
		case AST_RETURN:
			//printf("return ");
			fprintf(output, "return ");
			astreeProgram(node->son[0],output);
			break;
		case AST_WHEN_THEN:
			//printf("when (");
			fprintf(output, "when (");
			astreeProgram(node->son[0],output);
			//printf(") then ");
			fprintf(output, ") then ");
			astreeProgram(node->son[1],output);
			break;
		case AST_WHEN_THEN_ELSE:
			//printf("when (");
			fprintf(output, "when (");
			astreeProgram(node->son[0],output);
			//printf(") then ");
			fprintf(output, ") then ");
			astreeProgram(node->son[1],output);
			//printf(" else ");
			fprintf(output, " else ");
			astreeProgram(node->son[2],output);
			break;
		case AST_WHILE:
			//printf("while (");
			fprintf(output, "while (");
			astreeProgram(node->son[0],output);
			//printf(") ");
			fprintf(output, ") ");
			astreeProgram(node->son[1],output);
			break;
		case AST_FOR:
			//printf("for (");
			fprintf(output, "for (");
			//printf("%s",node->symbol->text); //id
			fprintf(output, "%s",node->symbol->text);
			//printf(" = ");
			fprintf(output, " = ");
			astreeProgram(node->son[0],output);
			//printf(" to ");
			fprintf(output, " to ");
			astreeProgram(node->son[1],output);
			//printf(") ");
			fprintf(output, ") ");
			astreeProgram(node->son[2],output);
			break;
		case AST_COMMAND_BLOCK:
			//printf("{");
			fprintf(output, "{");
			astreeProgram(node->son[0],output);
			//printf("}");
			fprintf(output, "}");
			break;
		case AST_SEQ_CMD:
			astreeProgram(node->son[0],output);
			//printf(";");
			fprintf(output, ";");
			astreeProgram(node->son[1],output);
			break;
		case AST_CJTODEC_ELEM:
			astreeProgram(node->son[0],output);
			//printf(";");
			fprintf(output, ";");
			astreeProgram(node->son[1],output);
			break;
		case AST_DEC_VAR_GLOB: 
			//printf("%s: ", node->symbol->text);
			fprintf(output, "%s: ", node->symbol->text);
			astreeProgram(node->son[0],output);
			//printf(" %s", node->son[2]->symbol->text);
			fprintf(output, " %s",node->son[1]->symbol->text);
			break;
		case AST_DEC_VEC_GLOB: 
			//printf("%s: ", node->symbol->text);
			fprintf(output, "%s: ", node->symbol->text);
			astreeProgram(node->son[0],output);
			break;
		case AST_DEC_VEC:
			astreeProgram(node->son[0],output);
			//printf("[%s]", node->son[1]->symbol->text);
			fprintf(output, "[%s]", node->symbol->text);
			break;
		case AST_DEC_VEC_SEQ:	
			astreeProgram(node->son[0],output);
			//printf("[%s] ", node->symbol->text);
			fprintf(output, "[%s] ", node->symbol->text);
			astreeProgram(node->son[1],output);
			break;
		case AST_SEQNUM_ELEM:
			//printf("%s ", node->son[0]->symbol->text);
			fprintf(output, "%s ", node->symbol->text);
			if(node->son[0]){
				astreeProgram(node->son[0],output);
			}
			break;
		case AST_DEC_FUNC:
			astreeProgram(node->son[0],output);
			astreeProgram(node->son[1],output);
			break;
		case AST_CABEC:
			astreeProgram(node->son[0],output);
			//printf(" %s(", node->symbol->text);
			fprintf(output, " %s(", node->symbol->text);
			astreeProgram(node->son[1],output);	
			//printf(")");
			fprintf(output, ")");
			break;
		case AST_PARAM_ELEM:
			astreeProgram(node->son[0],output);			
			if(node->son[1]){
				//printf(", ");
				fprintf(output, ", ");
				astreeProgram(node->son[1],output);
			}
			break;		
		case AST_PARAM:
			astreeProgram(node->son[0],output);	
			//printf(" %s", node->symbol->text);
			fprintf(output, " %s", node->symbol->text);
			break;
		case AST_BYTE:
			//printf("byte");
			fprintf(output, "byte");
			break;
		case AST_SHORT:
			//printf("short");
			fprintf(output, "short");
			break;
		case AST_LONG:
			//printf("long");
			fprintf(output, "long");
			break;
		case AST_FLOAT:		
			//printf("float");
			fprintf(output, "float");
			break;
		case AST_DOUBLE:
			//printf("double");
			fprintf(output, "double");
			break;
		
		
	}
}

