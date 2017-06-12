
%{
	#include <stdio.h>	 
	#include <stdlib.h>	
	#include "astree.h"
	#include "hash.h"	
	#include "y.tab.h"
	#include "semantics.h"

	int yylex();
	int getLineNumber(void);
	void yyerror(const char *s);	

%}

%token KW_BYTE       
%token KW_SHORT      
%token KW_LONG       
%token KW_FLOAT      
%token KW_DOUBLE     
%token KW_WHEN       
%token KW_THEN       
%token KW_ELSE       
%token KW_WHILE      
%token KW_FOR        
%token KW_READ       
%token KW_RETURN     
%token KW_PRINT      
%token KW_TO

%token OPERATOR_LE   
%token OPERATOR_GE   
%token OPERATOR_EQ   
%token OPERATOR_NE   
%token OPERATOR_AND  
%token OPERATOR_OR   

%token<symbol> TK_IDENTIFIER 
%token<symbol> LIT_INTEGER   
%token<symbol> LIT_REAL      
%token<symbol> LIT_CHAR      
%token<symbol> LIT_STRING    

%token TOKEN_ERROR

%type<astree> program
%type<astree> cjto_declar
%type<astree> declar
%type<astree> declar_var_globais
%type<astree> declar_vetor
%type<astree> seq_num
%type<astree> declar_func
%type<astree> cabecalho
%type<astree> list_params
%type<astree> resto_params
%type<astree> param
%type<astree> comando
%type<astree> atrib
%type<astree> read
%type<astree> print
%type<astree> list_elem
%type<astree> resto_list_elem
%type<astree> return
%type<astree> controle_fluxo
%type<astree> bloco_comandos
%type<astree> seq_comandos
%type<astree> expr
%type<astree> chamada_func
%type<astree> list_arg
%type<astree> resto_arg
%type<astree> value
%type<astree> type


%union {
	ASTREE *astree;
	HASH_NODE *symbol;
}

%left OPERATOR_OR OPERATOR_AND 
%right '!'
%left '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NE
%left '-' '+'
%left '*' '/'

%%
// Gramática lang171 - Compiladores
// Amanda e Gabriel


program: cjto_declar 								{$$ = $1; /*astreePrint($$,0);*/ ast = $$;} 
	;

cjto_declar: declar ';' cjto_declar					{$$ = astreeCreate(AST_CJTODEC_ELEM,0,$1,$3,0,0, getLineNumber());}
	| 												{$$ = 0;}
	;

declar: declar_var_globais							{$$ = $1;} 
	| declar_func 									{$$ = $1;}
	;

declar_var_globais: TK_IDENTIFIER ':' type value	{$$ = astreeCreate(AST_DEC_VAR_GLOB,$1,$3,$4,0,0, getLineNumber()); setSymbolAndDataType($$, AST_DEC_VAR_GLOB);}
	| TK_IDENTIFIER ':' declar_vetor				{$$ = astreeCreate(AST_DEC_VEC_GLOB,$1,$3,0,0,0, getLineNumber()); setSymbolAndDataType($$, AST_DEC_VEC_GLOB);}
	;

declar_vetor: type '[' LIT_INTEGER ']' seq_num		{$$ = astreeCreate(AST_DEC_VEC_SEQ,$3,$1,$5,0,0, getLineNumber());}
	| type '[' LIT_INTEGER ']'						{$$ = astreeCreate(AST_DEC_VEC,$3,$1,0,0,0, getLineNumber());}
	;
						
seq_num: LIT_INTEGER seq_num						{$$ = astreeCreate(AST_SEQNUM_ELEM,$1,$2,0,0,0, getLineNumber());}
	| LIT_REAL seq_num								{$$ = astreeCreate(AST_SEQNUM_ELEM,$1,$2,0,0,0, getLineNumber());}
	| LIT_CHAR seq_num								{$$ = astreeCreate(AST_SEQNUM_ELEM,$1,$2,0,0,0, getLineNumber());}
	| LIT_INTEGER									{$$ = astreeCreate(AST_SEQNUM_ELEM,$1,0,0,0,0, getLineNumber());}
	| LIT_REAL										{$$ = astreeCreate(AST_SEQNUM_ELEM,$1,0,0,0,0, getLineNumber());}
	| LIT_CHAR										{$$ = astreeCreate(AST_SEQNUM_ELEM,$1,0,0,0,0, getLineNumber());}
	;

declar_func: cabecalho comando						{$$ = astreeCreate(AST_DEC_FUNC,0,$1,$2,0,0, getLineNumber()); setSymbolAndDataType($$, AST_DEC_FUNC);}
	;

cabecalho: type TK_IDENTIFIER '(' list_params ')'	{$$ = astreeCreate(AST_CABEC,$2,$1,$4,0,0, getLineNumber());}
	;

list_params: param resto_params						{$$ = astreeCreate(AST_PARAM_ELEM,0,$1,$2,0,0, getLineNumber());}
	| 												{$$ = 0;}
	;

resto_params: ',' param resto_params				{$$ = astreeCreate(AST_PARAM_ELEM,0,$2,$3,0,0, getLineNumber());}
	|												{$$ = 0;}
	;

param: type TK_IDENTIFIER							{$$ = astreeCreate(AST_PARAM,$2,$1,0,0,0, getLineNumber()); setSymbolAndDataType($$, AST_PARAM);}
	;

comando: bloco_comandos								{$$ = $1;}
	| atrib											{$$ = $1;}
	| controle_fluxo								{$$ = $1;}
	| read											{$$ = $1;}
	| print											{$$ = $1;}
	| return										{$$ = $1;}
	| 												{$$ = 0;}
	;
						
atrib: TK_IDENTIFIER '=' expr									{$$ = astreeCreate(AST_ASSIGN,$1,$3,0,0,0, getLineNumber());}
	| TK_IDENTIFIER '#' expr '=' expr							{$$ = astreeCreate(AST_VEC_ASSIGN,$1,$3,$5,0,0, getLineNumber());}
	;

read: KW_READ TK_IDENTIFIER							{$$ = astreeCreate(AST_READ,$2,0,0,0,0, getLineNumber());}
	;

print: KW_PRINT list_elem							{$$ = astreeCreate(AST_PRINT,0,$2,0,0,0, getLineNumber());}
	;

list_elem: LIT_STRING resto_list_elem				{$$ = astreeCreate(AST_PRINT_ELEM,$1,$2,0,0,0, getLineNumber());}
	| expr resto_list_elem							{$$ = astreeCreate(AST_PRINT_ELEM,0,$1,$2,0,0, getLineNumber());}
	;

resto_list_elem: LIT_STRING resto_list_elem			{$$ = astreeCreate(AST_PRINT_ELEM,$1,$2,0,0,0, getLineNumber());}
	| expr resto_list_elem							{$$ = astreeCreate(AST_PRINT_ELEM,0,$1,$2,0,0, getLineNumber());}
	| 												{$$ = 0;}
	;

return:	KW_RETURN expr								{$$ = astreeCreate(AST_RETURN,0,$2,0,0,0, getLineNumber());}
	;

controle_fluxo:	KW_WHEN '(' expr ')' KW_THEN comando			{$$ = astreeCreate(AST_WHEN_THEN,0,$3,$6,0,0, getLineNumber());}
	| KW_WHEN '(' expr ')' KW_THEN comando KW_ELSE comando		{$$ = astreeCreate(AST_WHEN_THEN_ELSE,0,$3,$6,$8,0, getLineNumber());}
	| KW_WHILE '(' expr ')' comando								{$$ = astreeCreate(AST_WHILE,0,$3,$5,0,0, getLineNumber());}
	| KW_FOR '(' TK_IDENTIFIER '=' expr KW_TO expr ')' comando				{$$ = astreeCreate(AST_FOR,$3,$5,$7,$9,0, getLineNumber());}
	;

bloco_comandos:	'{' seq_comandos '}'				{$$ = astreeCreate(AST_COMMAND_BLOCK,0,$2,0,0,0, getLineNumber());}
	;

seq_comandos: comando ';' seq_comandos				{$$ = astreeCreate(AST_SEQ_CMD,0,$1,$3,0,0, getLineNumber());}
	|												{$$ = 0;}
	;

expr: expr '+' expr									{$$ = astreeCreate(AST_ADD,0,$1,$3,0,0, getLineNumber());}
	| expr '-' expr									{$$ = astreeCreate(AST_SUB,0,$1,$3,0,0, getLineNumber());}
	| expr '*' expr									{$$ = astreeCreate(AST_MUL,0,$1,$3,0,0, getLineNumber());}
	| expr '/' expr									{$$ = astreeCreate(AST_DIV,0,$1,$3,0,0, getLineNumber());}
	| expr '>' expr									{$$ = astreeCreate(AST_LOGIC_G,0,$1,$3,0,0, getLineNumber());}
	| expr '<' expr									{$$ = astreeCreate(AST_LOGIC_L,0,$1,$3,0,0, getLineNumber());}
	| expr OPERATOR_LE expr							{$$ = astreeCreate(AST_LOGIC_LE,0,$1,$3,0,0, getLineNumber());}
	| expr OPERATOR_GE expr							{$$ = astreeCreate(AST_LOGIC_GE,0,$1,$3,0,0, getLineNumber());}  
	| expr OPERATOR_EQ expr							{$$ = astreeCreate(AST_LOGIC_EQ,0,$1,$3,0,0, getLineNumber());}  
	| expr OPERATOR_NE expr							{$$ = astreeCreate(AST_LOGIC_NE,0,$1,$3,0,0, getLineNumber());}  
	| expr OPERATOR_AND expr						{$$ = astreeCreate(AST_LOGIC_AND,0,$1,$3,0,0, getLineNumber());}  
	| expr OPERATOR_OR expr							{$$ = astreeCreate(AST_LOGIC_OR,0,$1,$3,0,0, getLineNumber());}
	| '!' expr										{$$ = astreeCreate(AST_LOGIC_NOT,0,$2,0,0,0, getLineNumber());}
	| '(' expr ')'									{$$ = astreeCreate(AST_PARENTESIS_EXPR,0,$2,0,0,0, getLineNumber());}
	| LIT_INTEGER									{$$ = astreeCreate(AST_SYMBOL,$1,0,0,0,0, getLineNumber());}
	| LIT_REAL										{$$ = astreeCreate(AST_SYMBOL,$1,0,0,0,0, getLineNumber());}
	| LIT_CHAR										{$$ = astreeCreate(AST_SYMBOL,$1,0,0,0,0, getLineNumber());}
	| TK_IDENTIFIER									{$$ = astreeCreate(AST_SYMBOL,$1,0,0,0,0, getLineNumber());}
	| TK_IDENTIFIER '[' expr ']'					{$$ = astreeCreate(AST_VECTOR_EXPR,$1,$3,0,0,0, getLineNumber());}
	| chamada_func									{$$ = $1;}
	;

chamada_func: TK_IDENTIFIER '(' list_arg ')'		{$$ = astreeCreate(AST_FUNC_CALL,$1,$3,0,0,0, getLineNumber());}
	;		

list_arg: expr resto_arg							{$$ = astreeCreate(AST_LIST_ARG_BEGIN,0,$1,$2,0,0, getLineNumber());}
	| 												{$$ = 0;}
	;

resto_arg: ',' expr resto_arg						{$$ = astreeCreate(AST_LIST_ARG_ELEM,0,$2,$3,0,0, getLineNumber());}
	|												{$$ = 0;}
	;

value: LIT_INTEGER 									{$$ = astreeCreate(AST_SYMBOL,$1,0,0,0,0, getLineNumber());}
	| LIT_REAL  									{$$ = astreeCreate(AST_SYMBOL,$1,0,0,0,0, getLineNumber());}
	| LIT_CHAR  									{$$ = astreeCreate(AST_SYMBOL,$1,0,0,0,0, getLineNumber());}
	;

type: KW_BYTE 									{$$ = astreeCreate(AST_BYTE,0,0,0,0,0, getLineNumber());}
	| KW_SHORT 									{$$ = astreeCreate(AST_SHORT,0,0,0,0,0, getLineNumber());}
	| KW_LONG 									{$$ = astreeCreate(AST_LONG,0,0,0,0,0, getLineNumber());} 
	| KW_FLOAT 									{$$ = astreeCreate(AST_FLOAT,0,0,0,0,0, getLineNumber());}
	| KW_DOUBLE  								{$$ = astreeCreate(AST_DOUBLE,0,0,0,0,0, getLineNumber());}
	;
%%

void yyerror(const char *s){
	printf("Linha %d [erro de sintaxe]: %s.\n", getLineNumber(), s);
	exit(3);
}
