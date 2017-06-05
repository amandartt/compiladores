#include "semantics.h"

//TODO 
// lembrar de marcar tipos dos nodos - add na estrutura
// contar numero de parametros
// padronizar erros em uma funcao e usar as flags de exit
// criar uma funcao pequena q chame todas as outras de semantica pra no fim dar o exit

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
void setSymbolAndDataType(ASTREE *node, int type){

	if (type == AST_DEC_FUNC){
		if(node->son[0]->symbol->type != SYMBOL_IDENTIFIER){
		fprintf(stderr,"Erro: funcao %s declarada mais de uma vez.\n", node->son[0]->symbol->text); //exit(4);
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
		case AST_PARAM:	
			node->symbol->type = SYMBOL_VAR;
			setDataType(node, node->son[0]->type);
			break;
		case AST_DEC_VAR_GLOB: 				
			node->symbol->type = SYMBOL_VAR;
			setDataType(node, node->son[0]->type);
			break;
		case AST_DEC_VEC_GLOB: 
			node->symbol->type = SYMBOL_VEC;
			setDataType(node, node->son[0]->son[0]->type);
			break;
		case AST_DEC_FUNC:
			node->son[0]->symbol->type = SYMBOL_FUNC;
			setDataType(node->son[0], node->son[0]->son[0]->type);
			break;
	}
}

void setDataType(ASTREE *node, int type){
	switch(type){
		case AST_BYTE: node->symbol->dataType = DATATYPE_BYTE; break;
		case AST_SHORT: node->symbol->dataType = DATATYPE_SHORT; break;
		case AST_LONG: node->symbol->dataType = DATATYPE_LONG; break;
		case AST_FLOAT: node->symbol->dataType = DATATYPE_FLOAT; break;
		case AST_DOUBLE: node->symbol->dataType = DATATYPE_DOUBLE; break;
		default: node->symbol->dataType = DATATYPE_UNDEFINED; break;
	}
	node->dataType = node->symbol->dataType;
}

//TODO
void setAstNodeDataType(ASTREE *node){
	if(node == NULL){
		// pode acontecer? é erro? 
		return;
	}

	switch(node->type){
		case AST_SYMBOL:			
		case AST_VECTOR_EXPR:
		case AST_FUNC_CALL:  // not sure if node->symbol->dataType ou node->symbol->type
			// talvez uma condicao a mais se for literal
			node->dataType = node->symbol->dataType;
			break;
		case AST_LOGIC_L:
		case AST_LOGIC_G:
		case AST_LOGIC_LE:
		case AST_LOGIC_GE:
			if(node->son[0]->dataType == DATATYPE_BOOL || node->son[1]->dataType == DATATYPE_BOOL){
				fprintf(stderr,"Erro: expressao booleana em operacao relacional\n"); //exit(4);
			}
			node->dataType = DATATYPE_BOOL;
			break;
		case AST_LOGIC_EQ:
		case AST_LOGIC_NE:
			if((node->son[0]->dataType == DATATYPE_BOOL && node->son[1]->dataType != DATATYPE_BOOL) || 
			(node->son[1]->dataType == DATATYPE_BOOL && node->son[0]->dataType != DATATYPE_BOOL)){
				fprintf(stderr,"Erro: conflito de tipos em operação de eq/ne\n"); //exit(4);
			}
			node->dataType = DATATYPE_BOOL;
			break;
		case AST_LOGIC_AND:	
		case AST_LOGIC_OR:
			if(node->son[0]->dataType != DATATYPE_BOOL || node->son[1]->dataType != DATATYPE_BOOL){
				fprintf(stderr,"Erro: expressao booleana esperada em operacao and/or\n"); //exit(4);
			}
			node->dataType = DATATYPE_BOOL;	
			break;
		case AST_LOGIC_NOT:
			if(node->son[0]->dataType != DATATYPE_BOOL){
				fprintf(stderr,"Erro: expressao booleana esperada em operacao not\n"); //exit(4);
			}
			node->dataType = DATATYPE_BOOL;
			break;
		case AST_ADD:    
		case AST_SUB: 
		case AST_MUL: 
		case AST_DIV: 
			if(node->son[0]->dataType == DATATYPE_BOOL || node->son[1]->dataType == DATATYPE_BOOL){
				fprintf(stderr,"Erro: expressao booleana nao esperada em expressao aritmetica \n"); //exit(4);
			}
			node->dataType = aritmeticInference(node);
			break;
		case AST_ASSIGN: 
			if(!verifyAssignmentTypes(node->symbol->dataType, node->son[0]->dataType)){
				fprintf(stderr,"Erro: conflito de tipos na atribuicao\n"); //exit(4);
			}
			node->dataType = node->symbol->dataType;
			break;
		case AST_VEC_ASSIGN: 
			if(node->son[0]->dataType != (DATATYPE_LONG || DATATYPE_SHORT)) {
				fprintf(stderr,"Erro: indice do vetor deve ser do tipo inteiro \n"); //exit(4);
			}
			if(!verifyAssignmentTypes(node->symbol->dataType, node->son[1]->dataType)){
				fprintf(stderr,"Erro: conflito de tipos na atribuicao\n"); //exit(4);
			}
			node->dataType = node->symbol->dataType;
			break;
		case AST_PARENTESIS_EXPR:
			node->dataType = node->son[0]->dataType;
			break;
	}

	//printf("type: %d datatype: %d \n", node->type, node->dataType);
}

int aritmeticInference(ASTREE *node){
	// eh soh isso ?? 
	return typeInference(node->son[0]->dataType, node->son[1]->dataType);

}

int typeInference(int type1, int type2){

	if(type1 == DATATYPE_BOOL || type2 == DATATYPE_BOOL){
		return DATATYPE_UNDEFINED;
	}

	if(type1 == DATATYPE_DOUBLE || type2 == DATATYPE_DOUBLE){
		return DATATYPE_DOUBLE;
	}
	else if(type1 == DATATYPE_FLOAT || type2 == DATATYPE_FLOAT){
		return DATATYPE_FLOAT;
	}
	else if(type1 == DATATYPE_LONG || type2 == DATATYPE_LONG){
		return DATATYPE_LONG;
	}
	else if(type1 == DATATYPE_SHORT || type2 == DATATYPE_SHORT){
		return DATATYPE_SHORT;
	}
	else if(type1 == DATATYPE_BYTE || type2 == DATATYPE_BYTE){
		return DATATYPE_BYTE;
	}else{ 
		return DATATYPE_UNDEFINED;
	}	
}

int verifyAssignmentTypes(int type1, int type2){
	if(type1 == DATATYPE_BOOL || type2 == DATATYPE_BOOL){
		return 0;
	}
	if(type1 == DATATYPE_UNDEFINED || type2 == DATATYPE_UNDEFINED){
		return 0;
	}
	return 1;
}

int isBool(ASTREE *node){
	if(node->type == AST_LOGIC_L || node->type == AST_LOGIC_LE || node->type == AST_LOGIC_GE || node->type == AST_LOGIC_EQ || 
	node->type == AST_LOGIC_NE || node->type == AST_LOGIC_AND || node->type == AST_LOGIC_G || node->type == AST_LOGIC_OR ||
	node->type == AST_LOGIC_NOT){
		return 1;
	}
	return 0;
}
