#include "semantics.h"

//TODO 
// lembrar de marcar tipos dos nodos - add na estrutura
// contar numero de parametros

// avaliacao recursiva da arvore
void semanticFullCheck(ASTREE *node){
	if(!node) return;
	
	switch(node->type){
		case AST_SYMBOL:
			//Nothing(?)
			break;
		case AST_ADD:
			//Check expr + define type of the expr				
			//semanticFullCheck?(node->son[0]);
			//semanticFullCheck?(node->son[1]);
			break;
		case AST_SUB:
			//Check expr + define type of the expr
			//semanticFullCheck?(node->son[0]);
			//semanticFullCheck?(node->son[1]);
			break;
		case AST_MUL:
			//Check expr + define type of the expr
			//semanticFullCheck?(node->son[0]);
			//semanticFullCheck?(node->son[1]);
			break;
		case AST_DIV:
			//Check expr + define type of the expr
			//semanticFullCheck?(node->son[0]);
			//semanticFullCheck?(node->son[1]);
			break;
		case AST_LOGIC_G:
			//Check expr + type = EXPR_BOOL
			//semanticFullCheck?(node->son[0]);
			//semanticFullCheck?(node->son[1]);
			break;
		case AST_LOGIC_L:
			//Check expr + type = EXPR_BOOL
			//semanticFullCheck?(node->son[0]);
			//semanticFullCheck?(node->son[1]);
			break;
		case AST_LOGIC_LE:
			//Check expr + type = EXPR_BOOL
			//semanticFullCheck?(node->son[0]);
			//semanticFullCheck?(node->son[1]);
			break;
		case AST_LOGIC_GE:
			//Check expr + type = EXPR_BOOL
			//semanticFullCheck?(node->son[0]);
			//semanticFullCheck?(node->son[1]);
			break;
		case AST_LOGIC_EQ:
			//Check expr + type = EXPR_BOOL
			//semanticFullCheck?(node->son[0]);
			//semanticFullCheck?(node->son[1]);
			break;
		case AST_LOGIC_NE:
			//Check expr + type = EXPR_BOOL
			//semanticFullCheck?(node->son[0]);
			//semanticFullCheck?(node->son[1]);
			break;
		case AST_LOGIC_AND:
			//Check expr + type = EXPR_BOOL
			//semanticFullCheck?(node->son[0]);
			//semanticFullCheck?(node->son[1]);
			break;
		case AST_LOGIC_OR:
			//Check expr + type = EXPR_BOOL
			//semanticFullCheck?(node->son[0]);
			//semanticFullCheck?(node->son[1]);
			break;
		case AST_LOGIC_NOT:
			//Check expr + type = EXPR_BOOL
			//semanticFullCheck?(node->son[0]);
			//semanticFullCheck?(node->son[1]);
			break;
		case AST_PARENTESIS_EXPR:
			//Check inside expr + type = type son[0]
			//semanticFullCheck?(node->son[0]);
			break;
		case AST_VECTOR_EXPR:
			//Verify if son[0] expr is a EXPR_INT type
			//Verify if used as vector(?)
			//semanticFullCheck?(node->son[0]);
			break;
			break;
		case AST_FUNC_CALL:
			//Verify arguments number and types compatibility
			//semanticFullCheck?(node->son[0]); //LIST_ARG_BEGIN or empty
			break;
		case AST_LIST_ARG_BEGIN:
			//Verify type compatibility of son[0], recurse on son[1]
			//semanticFullCheck?(node->son[0]); //expr
			//semanticFullCheck?(node->son[1]); //LIST_ARG_ELEM's
			break;
		case AST_LIST_ARG_ELEM:
			//Verify type compatibility of son[0], recurse on son[1]
			//semanticFullCheck?(node->son[0]); //expr
			//semanticFullCheck?(node->son[1]); //LIST_ARG_ELEM's
			break;
		case AST_ASSIGN:
			//Verify usage of literals, vectors and functions
			//semanticFullCheck?(node->son[0]);
			break;
		case AST_VEC_ASSIGN:
			//Verify if son[0] is a EXPR_INT and compatibility of son[1]
			//semanticFullCheck?(node->son[0]);
			//semanticFullCheck?(node->son[1]);
			break;
		case AST_READ:
			//Nothing(?)
			break;
		case AST_PRINT:
			//Verify if son[0] expressions are EXPR_INT or EXPR_REAL (EXPR_ARIT)
			//semanticFullCheck?(node->son[0]);
			break;
		case AST_PRINT_ELEM:
			if(node->symbol){
				//If string, no check needed.
			}
			else{
				//verify if son[0] is EXPR_INT or EXPR_REAL (EXPR_ARIT)
				//semanticFullCheck?(node->son[0]);
			}
			//Continue on the list
			//semanticFullCheck?(node->son[1]);
			break;
		case AST_RETURN:
			//Verify if son[0] is EXPR_INT or EXPR_REAL (EXPR_ARIT)
			//semanticFullCheck?(node->son[0]);
			break;
		case AST_WHEN_THEN:
			//Verify if son[0] is EXPR_BOOL
			//semanticFullCheck?(node->son[0]);
			//Verify son[1]
			//semanticFullCheck?(node->son[1]);
			break;
		case AST_WHEN_THEN_ELSE:
			//Verify if son[0] is EXPR_BOOL
			//semanticFullCheck?(node->son[0]);
			//Verify son[1]
			//semanticFullCheck?(node->son[1]);
			//Verify son[2]
			//semanticFullCheck?(node->son[2]);
			break;
		case AST_WHILE:
			//Verify if son[0] is EXPR_BOOL
			//semanticFullCheck?(node->son[0]);
			//Verify son[1]
			//semanticFullCheck?(node->son[1]);
			break;
		case AST_FOR:
			//Verify if son[0] is EXPR_INT or EXPR_FLOAT (EXPR_ARIT)
			//semanticFullCheck?(node->son[0]);
			//Verify if son[1] is EXPR_INT or EXPR_FLOAT (EXPR_ARIT)
			//semanticFullCheck?(node->son[1]);
			//Verify son[2]
			//semanticFullCheck?(node->son[2]);
			break;
		case AST_COMMAND_BLOCK:
			//Verify son[0]
			//semanticFullCheck?(node->son[0]);
			break;
		case AST_SEQ_CMD:
			//Verify son[0]
			//semanticFullCheck?(node->son[0]);
			//Verify son[1]
			//semanticFullCheck?(node->son[1]);
			break;
		case AST_CJTODEC_ELEM:
			//Verify son[0]
			//semanticFullCheck?(node->son[0]);
			//Verify son[1]
			//semanticFullCheck?(node->son[1]);
			break;
		case AST_DEC_VAR_GLOB: 
			//Nothing (already made??)
			break;
		case AST_DEC_VEC_GLOB: 
			//Nothing (already made??)
			break;
		case AST_DEC_VEC:
			//Nothing (already made??)
			break;
		case AST_DEC_VEC_SEQ:	
			//Verify son[1] (needed?)
			//semanticFullCheck?(node->son[1]);
			break;
		case AST_SEQNUM_ELEM:
			//Verify son[0] (needed?)
			if(node->son[0]){
				//semanticFullCheck?(node->son[0]);
			}
			break;
		case AST_DEC_FUNC:
			//Verify son[1] (son[0] already made??)
			//semanticFullCheck?(node->son[0]);
			//semanticFullCheck?(node->son[1]);
			break;
		case AST_CABEC:
			//verify list of params(??? novo campo com lista de parametros??) nao precisa, apenas numero de parametros
			//semanticFullCheck?(node->son[0]);
			//semanticFullCheck?(node->son[1]);	
			break;
		case AST_PARAM_ELEM: //talvez "nothing", pois AST_DEC_FUNC chamaria outra função para cuidar disso?
			//anotate no novo campo???
			//semanticFullCheck?(node->son[0]);			
			if(node->son[1]){
				//recursao para continuar anotando??
				//semanticFullCheck?(node->son[1]);
			}
			break;		
		case AST_PARAM:
			//son[0] have the type of the param!
			//semanticFullCheck?(node->son[0]);
			break;
		case AST_BYTE:
			//anotate type?
			break;
		case AST_SHORT:
			//anotate type?
			break;
		case AST_LONG:
			//anotate type?
			break;
		case AST_FLOAT:		
			//anotate type?
			break;
		case AST_DOUBLE:
			//anotate type?
			break;
	}
}


// completo(?) i guess so
void setDataType(ASTREE *node, int type){

	if (type == AST_DEC_FUNC){
		if(node->son[0]->symbol->type != SYMBOL_IDENTIFIER){
		fprintf(stderr,"Erro: variavel %s declarada mais de uma vez.\n", node->son[0]->symbol->text); //exit(4);
		return;
		}
	}
	else if(node->symbol->type != SYMBOL_IDENTIFIER){
		fprintf(stderr,"Erro: variavel %s declarada mais de uma vez.\n", node->symbol->text); //exit(4);
		return;
	}
	
	if(node->symbol)
		printf("node %s type %d\n",node->symbol->text,type);
	else
		printf("node %s type %d\n",node->son[0]->symbol->text,type);

	switch(type){
		case AST_DEC_VAR_GLOB: 			
			node->symbol->type = SYMBOL_VAR;
			// outro switch pra dataType:  byte, short, long, float, double
			switch(node->son[0]->type){
				case AST_BYTE: node->symbol->dataType = DATATYPE_BYTE; break;
				case AST_SHORT: node->symbol->dataType = DATATYPE_SHORT; break;
				case AST_LONG: node->symbol->dataType = DATATYPE_LONG; break;
				case AST_FLOAT: node->symbol->dataType = DATATYPE_FLOAT; break;
				case AST_DOUBLE: node->symbol->dataType = DATATYPE_DOUBLE; break;
			}
			break;
		case AST_DEC_VEC_GLOB: 
			node->symbol->type = SYMBOL_VEC;
			switch(node->son[0]->son[0]->type){
				case AST_BYTE: node->symbol->dataType = DATATYPE_BYTE; break;
				case AST_SHORT: node->symbol->dataType = DATATYPE_SHORT; break;
				case AST_LONG: node->symbol->dataType = DATATYPE_LONG; break;
				case AST_FLOAT: node->symbol->dataType = DATATYPE_FLOAT; break;
				case AST_DOUBLE: node->symbol->dataType = DATATYPE_DOUBLE; break;
			}
			break;
		case AST_DEC_FUNC:
			node->son[0]->symbol->type = SYMBOL_FUNC;
			switch(node->son[0]->son[0]->type){
				case AST_BYTE: node->son[0]->symbol->dataType = DATATYPE_BYTE; break;
				case AST_SHORT: node->son[0]->symbol->dataType = DATATYPE_SHORT; break;
				case AST_LONG: node->son[0]->symbol->dataType = DATATYPE_LONG; break;
				case AST_FLOAT: node->son[0]->symbol->dataType = DATATYPE_FLOAT; break;
				case AST_DOUBLE: node->son[0]->symbol->dataType = DATATYPE_DOUBLE; break;
			}
			break;
	}
}

//TODO
// FALTAM AS EXP ADD, SUB ETC
void setAstNodeDataType(ASTREE *node){
	if(node == NULL){
		// pode acontecer? é erro? 
		return;
	}

	switch(node->type){
		case AST_SYMBOL:
		case AST_VECTOR_EXPR:
		case AST_FUNC_CALL:
			node->dataType = node->symbol->dataType;
			break;
		case AST_LOGIC_L:
		case AST_LOGIC_LE:
		case AST_LOGIC_GE:
		case AST_LOGIC_EQ:
		case AST_LOGIC_NE:
		case AST_LOGIC_AND:
		case AST_LOGIC_G:
		case AST_LOGIC_OR:
		case AST_LOGIC_NOT:
			node->dataType = EXPR_BOOL;
			break;
		case AST_ADD: //TODO break;   
		case AST_SUB: //TODO break;
		case AST_MUL: //TODO break;
		case AST_DIV: //TODO break;
		case AST_ASSIGN: //TODO break;
		case AST_VEC_ASSIGN: //TODO break; 
			break;
	}

	//printf("type: %d datatype: %d \n", node->type, node->dataType);
}

int typeInference(int type1, int type2){
	if(type1 == AST_DOUBLE || type2 == AST_DOUBLE){
		return DATATYPE_DOUBLE;
	}
	else if(type1 == AST_FLOAT || type2 == AST_FLOAT){
		return DATATYPE_FLOAT;
	}
	else if(type1 == AST_LONG || type2 == AST_LONG){
		return DATATYPE_LONG;
	}
	else if(type1 == AST_SHORT || type2 == AST_SHORT){
		return DATATYPE_SHORT;
	}
	else if(type1 == AST_BYTE || type2 == AST_BYTE){
		return DATATYPE_BYTE;
	}
}

int isBool(ASTREE *node){
	if(node->type == AST_LOGIC_L || node->type == AST_LOGIC_LE || node->type == AST_LOGIC_GE || node->type == AST_LOGIC_EQ || 
	node->type == AST_LOGIC_NE || node->type == AST_LOGIC_AND || node->type == AST_LOGIC_G || node->type == AST_LOGIC_OR ||
	node->type == AST_LOGIC_NOT){
		return 1;
	}
	return 0;
}
