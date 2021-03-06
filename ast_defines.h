// Amanda e Gabriel

/*
*  Constantes utilizadas na AST
*/

#ifndef ASTREE_CONST
#define ASTREE_CONST

#define MAX_SONS 4

#define AST_SYMBOL 				0
#define AST_ADD 				1
#define AST_SUB 				2
#define AST_MUL 				3
#define AST_DIV 				4
#define AST_LOGIC_G 			5
#define AST_LOGIC_L 			6
#define AST_LOGIC_LE			7
#define AST_LOGIC_GE 			8
#define AST_LOGIC_EQ 			9
#define AST_LOGIC_NE			10
#define AST_LOGIC_AND			11
#define AST_LOGIC_OR			12
#define AST_LOGIC_NOT			13
#define AST_VECTOR_EXPR			14
#define AST_FUNC_CALL			15
#define AST_LIST_ARG_BEGIN		16
#define AST_ASSIGN				17
#define AST_VEC_ASSIGN			18
#define AST_READ				19
#define AST_PRINT				20
#define AST_PRINT_ELEM			21
#define AST_RETURN				22
#define AST_WHEN_THEN			23
#define AST_WHEN_THEN_ELSE		24
#define AST_WHILE				25
#define AST_FOR					26
#define AST_SEQ_CMD				27

#define AST_CJTODEC_ELEM		28
#define AST_DEC_VAR_GLOB		29
#define AST_DEC_VEC_GLOB		34
#define AST_DEC_VEC_SEQ			35
#define AST_DEC_VEC				40
#define AST_SEQNUM_ELEM			45
#define AST_DEC_FUNC			46
#define AST_CABEC				47
#define AST_PARAM_ELEM			52
#define AST_PARAM				53

#define AST_PARENTESIS_EXPR		58
#define AST_COMMAND_BLOCK		59
#define AST_LIST_ARG_ELEM		60

#define AST_BYTE			61
#define AST_SHORT			62
#define AST_LONG			63
#define AST_FLOAT			64
#define AST_DOUBLE			65



#endif
