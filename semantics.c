#include "semantics.h"

// funcao nao sera utilizada  -- apagar depois
void semanticSetDeclations(ASTREE *node){
	if(node->type != SYMBOL_VAR){
		if(node->symbol->type != SYMBOL_IDENTIFIER){
			// erro, tipo ja definido
		}	
		node->symbol->type = SYMBOL_VAR;
		if(node->son[0]->type == KW_BYTE){
			node->symbol->dataType = DATATYPE_BYTE;
		}		
	}

	int i;
	for(i=0; i<MAX_SONS; i++){
		semanticSetDeclations(node->son[i]);
	}
}


// incompleto
void setDataType(ASTREE *node, int type){
	if(node->symbol->type != SYMBOL_IDENTIFIER){
		// ERRO, tipo ja definido
		return;
	}

	switch(type){
		case AST_DEC_VAR_GLOB: 			
			node->symbol->type = SYMBOL_VAR;
			// outro switch pra datatype???  byte, int, real, etc?
			break;
		case AST_DEC_VEC_GLOB: 
			node->symbol->type = SYMBOL_VEC;
			break;
		case AST_DEC_FUNC:
			node->symbol->type = SYMBOL_FUNC;
			break;
	}


}
