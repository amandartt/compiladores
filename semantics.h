#include "astree.h"
#include "y.tab.h"
#include "symbol_defs.h"


void semanticSetDeclations(ASTREE *node);

// **inferencia de tipo
// em atribuições
// em expressoes
// ** funcao para saber se é booleano

void semanticFullCheck(ASTREE *node);
void setDataType(ASTREE *node, int type);
void setAstNodeDataType(ASTREE *node);
int aritmeticInference(ASTREE *node);
int typeInference(int type1, int type2);
int isBool(ASTREE *node);
