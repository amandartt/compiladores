#include "astree.h"
#include "y.tab.h"
#include "symbol_defs.h"


void semanticSetDeclations(ASTREE *node);

// **inferencia de tipo
// em atribuições
// em expressoes
// ** funcao para saber se é booleano

void setDataType(ASTREE *node, int type);
