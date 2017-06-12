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
int testID(HASH_NODE* id,ASTREE* node);
void setSymbolAndDataType(ASTREE *node, int type);
void setDataType(ASTREE *node, int type);
int countDecFuncNumParams(ASTREE *node);
void setNumParams(ASTREE *node, int npar);
void checkSymbolsUse(ASTREE *node);
void verifyParams(ASTREE *node);
int verifyFuncCallParams(ASTREE *node);
int countFuncCallParams(ASTREE* node);
void checkAstNodeDataType(ASTREE *node);
int aritmeticInference(ASTREE *node);
int typeInference(int type1, int type2);
int verifyAssignmentTypes(int type1, int type2);
void hashCheckUndeclared();
void printSemanticError(char* errorDesc, char* param, int lineNumber);


