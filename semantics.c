#include "semantics.h"

//TODO 
// lembrar de marcar tipos dos nodos - add na estrutura
// contar numero de parametros
// padronizar erros em uma funcao e usar as flags de exit
// criar uma funcao pequena q chame todas as outras de semantica pra no fim dar o exit

// avaliacao recursiva da arvore
int semanticFullCheck(ASTREE *node){
	hash_ckeck_undeclared();	
	checkAstNodeDataType(node);
	return semanticErrors;
}


// completo(?) i guess so
void setSymbolAndDataType(ASTREE *node, int type){

	if (type == AST_DEC_FUNC){
		if(node->son[0]->symbol->type != SYMBOL_IDENTIFIER){
		printSemanticError("funcao declarada mais de uma vez", node->son[0]->symbol->text);
		return;
		}
	}
	else if(node->symbol->type != SYMBOL_IDENTIFIER){
		printSemanticError("variavel declarada mais de uma vez", node->symbol->text);
		return;
	}
	
/*	if(node->symbol)
		printf("node %s type %d\n",node->symbol->text,type);
	else
		printf("node %s type %d\n",node->son[0]->symbol->text,type);
*/
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
void checkAstNodeDataType(ASTREE *node){
	if(node == NULL){
		return;
	}

	int i;
	for(i=0; i<4; i++){
		checkAstNodeDataType(node->son[i]);
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
				printSemanticError("expressao booleana em operacao relacional", NULL);
			}
			node->dataType = DATATYPE_BOOL;
			break;
		case AST_LOGIC_EQ:
		case AST_LOGIC_NE:
			if((node->son[0]->dataType == DATATYPE_BOOL && node->son[1]->dataType != DATATYPE_BOOL) || 
			(node->son[1]->dataType == DATATYPE_BOOL && node->son[0]->dataType != DATATYPE_BOOL)){
				printSemanticError("conflito de tipos em operação de eq/ne", NULL);
			}
			node->dataType = DATATYPE_BOOL;
			break;
		case AST_LOGIC_AND:	
		case AST_LOGIC_OR:
			if(node->son[0]->dataType != DATATYPE_BOOL || node->son[1]->dataType != DATATYPE_BOOL){
				printSemanticError("expressao booleana esperada em operacao and/or", NULL); 
			}
			node->dataType = DATATYPE_BOOL;	
			break;
		case AST_LOGIC_NOT:
			if(node->son[0]->dataType != DATATYPE_BOOL){
				printSemanticError("expressao booleana esperada em operacao not", NULL); 
			}
			node->dataType = DATATYPE_BOOL;
			break;
		case AST_ADD:    
		case AST_SUB: 
		case AST_MUL: 
		case AST_DIV: 
			if(node->son[0]->dataType == DATATYPE_BOOL || node->son[1]->dataType == DATATYPE_BOOL){
				printSemanticError("expressao booleana nao esperada em expressao aritmetica", NULL);
			}
			node->dataType = aritmeticInference(node);
			break;
		case AST_ASSIGN: 
			if(!verifyAssignmentTypes(node->symbol->dataType, node->son[0]->dataType)){
				printSemanticError("conflito de tipos na atribuicao", NULL);
			}
			node->dataType = node->symbol->dataType;
			break;
		case AST_VEC_ASSIGN: //TODO arrumar -> caso de liteirais creio
			if(node->son[0]->dataType != (DATATYPE_LONG || DATATYPE_SHORT)) {
				printSemanticError("indice do vetor deve ser do tipo inteiro", NULL); 
			}
			if(!verifyAssignmentTypes(node->symbol->dataType, node->son[1]->dataType)){
				printSemanticError("conflito de tipos na atribuicao", NULL);
			}
			node->dataType = node->symbol->dataType;
			break;
		case AST_PARENTESIS_EXPR:
			node->dataType = node->son[0]->dataType;
			break;
		case AST_FOR:
			if(node->son[0]->dataType == DATATYPE_BOOL || node->son[1]->dataType == DATATYPE_BOOL){
				printSemanticError("expresao booleana em comando for", NULL);	
			}	
			break;
		case AST_WHILE:
			if(node->son[0]->dataType != DATATYPE_BOOL){
				printSemanticError("expresao booleana esperada em comando while", NULL);	
			}
			break;
		case AST_WHEN_THEN:
		case AST_WHEN_THEN_ELSE:
			if(node->son[0]->dataType != DATATYPE_BOOL){
				printSemanticError("expresao booleana esperada em comando when", NULL);
			}
			break;		
		case AST_RETURN:	
			if(node->son[0]->dataType == DATATYPE_BOOL){
				printSemanticError("return do tipo booleano nao esperado", NULL);
			}
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

void hash_ckeck_undeclared(){
	HASH_NODE *node;
	int i;	 
	for(i=0; i<HASH_SIZE; i++){
		for(node=hash_table[i]; node; node=node->next){ 
			if(node->type == SYMBOL_IDENTIFIER){
				//erro variavel nao declarada
				printSemanticError("variavel nao declarada", node->text); 
			}
		}
	} 
}

void printSemanticError(char* errorDesc, char* param){
	if(param != NULL){
		fprintf(stderr,"Erro semantico: %s [%s].\n", errorDesc, param);	
	}else{
		fprintf(stderr,"Erro semantico: %s.\n", errorDesc);	
	}
	semanticErrors++;	
}
