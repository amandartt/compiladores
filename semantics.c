#include "semantics.h"

// funcao nao sera utilizada  -- apagar depois
void semanticSetDeclations(ASTREE *node){
	if(node->type != SYMBOL_VAR){
		if(node->symbol->type != SYMBOL_IDENTIFIER){
			// erro, tipo ja definido
			fprintf(stderr,"Erro: variavel %s declarada mais de uma vez.\n", node->symbol->text); //exit(4);
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
		fprintf(stderr,"Erro: variavel %s declarada mais de uma vez.\n", node->symbol->text); //exit(4);
		return;
	}

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
			node->symbol->type = SYMBOL_FUNC;
			switch(node->son[0]->son[0]->type){
				case AST_BYTE: node->symbol->dataType = DATATYPE_BYTE; break;
				case AST_SHORT: node->symbol->dataType = DATATYPE_SHORT; break;
				case AST_LONG: node->symbol->dataType = DATATYPE_LONG; break;
				case AST_FLOAT: node->symbol->dataType = DATATYPE_FLOAT; break;
				case AST_DOUBLE: node->symbol->dataType = DATATYPE_DOUBLE; break;
			}
			break;
	}


}
