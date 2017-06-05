#include "astree.h"
#include "y.tab.h"
#include "hash.h"
#include "symbol_defs.h"

int semanticErrors;

void semanticSetDeclations(ASTREE *node);

// **inferencia de tipo
// em atribuições
// em expressoes
// ** funcao para saber se é booleano

int semanticFullCheck(ASTREE *node);
void setSymbolAndDataType(ASTREE *node, int type);
void setDataType(ASTREE *node, int type);
void checkSymbolsUse(ASTREE *node);
void checkAstNodeDataType(ASTREE *node);
void verifyParams(ASTREE *node);
int aritmeticInference(ASTREE *node);
int typeInference(int type1, int type2);
int verifyAssignmentTypes(int type1, int type2);
void hash_ckeck_undeclared();
void printSemanticError(char* errorDesc, char* param);



/*
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
*/
