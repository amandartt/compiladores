
%{
	#include <stdio.h>	 
	#include <stdlib.h>	
	#include "astree.h"
	#include "hash.h"	
	#include "y.tab.h"

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
%type<symbol> value
%type<symbol> id
%type<symbol> str
%type<symbol> int

//descomentar apenas os que estao feitos


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


program: cjto_declar 								{$$ = $1; astreePrint($$,0);}
	;

cjto_declar: declar ';' cjto_declar					{$$ = astreeCreate(AST_CJTODEC_ELEM,0,$1,$3,0,0);}
	| 												{$$ = 0;}
	;

declar: declar_var_globais							{$$ = $1;} 
	| declar_func 									{$$ = $1;}
	;

declar_var_globais: id ':' KW_BYTE value			{$$ = astreeCreate(AST_DEC_BYTE_VAR_GLOB,0,$1,$4,0,0);}
	| id ':' KW_SHORT value							{$$ = astreeCreate(AST_DEC_SHORT_VAR_GLOB,0,$1,$4,0,0);}
	| id ':' KW_LONG value							{$$ = astreeCreate(AST_DEC_LONG_VAR_GLOB,0,$1,$4,0,0);}
	| id ':' KW_FLOAT value							{$$ = astreeCreate(AST_DEC_FLOAT_VAR_GLOB,0,$1,$4,0,0);}
	| id ':' KW_DOUBLE value						{$$ = astreeCreate(AST_DEC_DOUBLE_VAR_GLOB,0,$1,$4,0,0);}
	| id ':' declar_vetor							{$$ = astreeCreate(AST_DEC_VEC_GLOB,0,$1,$3,0,0);}
	;

declar_vetor: KW_BYTE '[' int ']' seq_num			{$$ = astreeCreate(AST_DEC_BYTE_VEC_SEQ,0,$3,$5,0,0);}
	| KW_SHORT '[' int ']' seq_num					{$$ = astreeCreate(AST_DEC_SHORT_VEC_SEQ,0,$3,$5,0,0);}
	| KW_LONG '[' int ']' seq_num					{$$ = astreeCreate(AST_DEC_LONG_VEC_SEQ,0,$3,$5,0,0);}
	| KW_FLOAT '[' int ']' seq_num					{$$ = astreeCreate(AST_DEC_FLOAT_VEC_SEQ,0,$3,$5,0,0);}
	| KW_DOUBLE '[' int ']' seq_num					{$$ = astreeCreate(AST_DEC_DOUBLE_VEC_SEQ,0,$3,$5,0,0);}
	| KW_BYTE '[' int ']'							{$$ = astreeCreate(AST_DEC_BYTE_VEC,0,$3,0,0,0);}
	| KW_SHORT '[' int ']'							{$$ = astreeCreate(AST_DEC_SHORT_VEC,0,$3,0,0,0);}
	| KW_LONG '[' int ']'							{$$ = astreeCreate(AST_DEC_LONG_VEC,0,$3,0,0,0);}
	| KW_FLOAT '[' int ']'							{$$ = astreeCreate(AST_DEC_FLOAT_VEC,0,$3,0,0,0);}
	| KW_DOUBLE '[' int ']'							{$$ = astreeCreate(AST_DEC_DOUBLE_VEC,0,$3,0,0,0);}
	;
						
seq_num: value seq_num								{$$ = astreeCreate(AST_SEQNUM_ELEM,0,$1,$2,0,0);}
	| value											{$$ = astreeCreate(AST_SEQNUM_ELEM,0,$1,0,0,0);}
	;

declar_func: cabecalho comando						{$$ = astreeCreate(AST_DEC_FUNC,0,$1,$2,0,0);}
	;

cabecalho: KW_BYTE id '(' list_params ')'			{$$ = astreeCreate(AST_BYTE_CABEC,0,$2,$4,0,0);}
	| KW_SHORT id '(' list_params ')'				{$$ = astreeCreate(AST_SHORT_CABEC,0,$2,$4,0,0);}
	| KW_LONG id '(' list_params ')'				{$$ = astreeCreate(AST_LONG_CABEC,0,$2,$4,0,0);}
	| KW_FLOAT id '(' list_params ')'				{$$ = astreeCreate(AST_FLOAT_CABEC,0,$2,$4,0,0);}
	| KW_DOUBLE id '(' list_params ')'				{$$ = astreeCreate(AST_DOUBLE_CABEC,0,$2,$4,0,0);}
	;

list_params: param resto_params						{$$ = astreeCreate(AST_PARAM_ELEM,0,$1,$2,0,0);}
	| 												{$$ = 0;}
	;

resto_params: ',' param resto_params				{$$ = astreeCreate(AST_PARAM_ELEM,0,$2,$3,0,0);}
	|												{$$ = 0;}
	;

param: KW_BYTE id									{$$ = astreeCreate(AST_PARAM_BYTE,0,$2,0,0,0);}
	| KW_SHORT id 									{$$ = astreeCreate(AST_PARAM_SHORT,0,$2,0,0,0);}
	| KW_LONG id 									{$$ = astreeCreate(AST_PARAM_LONG,0,$2,0,0,0);} 
	| KW_FLOAT id  									{$$ = astreeCreate(AST_PARAM_FLOAT,0,$2,0,0,0);}
	| KW_DOUBLE id  								{$$ = astreeCreate(AST_PARAM_DOUBLE,0,$2,0,0,0);}
	;

comando: bloco_comandos								{$$ = $1;}
	| atrib											{$$ = $1;}
	| controle_fluxo								{$$ = $1;}
	| read											{$$ = $1;}
	| print											{$$ = $1;}
	| return										{$$ = $1;}
	| 												{$$ = 0;}
	;
						
atrib: id '=' expr									{$$ = astreeCreate(AST_ASSIGN,0,$1,$3,0,0);}
	| id '#' expr '=' expr							{$$ = astreeCreate(AST_VEC_ASSIGN,0,$1,$3,$5,0);}
	;

read: KW_READ id									{$$ = astreeCreate(AST_READ,0,$2,0,0,0);}
	;

print: KW_PRINT list_elem							{$$ = astreeCreate(AST_PRINT,0,$2,0,0,0);}
	;

list_elem: str resto_list_elem						{$$ = astreeCreate(AST_PRINT_ELEM,0,$1,$2,0,0);}
	| expr resto_list_elem							{$$ = astreeCreate(AST_PRINT_ELEM,0,$1,$2,0,0);}
	;

resto_list_elem: str resto_list_elem				{$$ = astreeCreate(AST_PRINT_ELEM,0,$1,$2,0,0);}
	| expr resto_list_elem							{$$ = astreeCreate(AST_PRINT_ELEM,0,$1,$2,0,0);}
	| 												{$$ = 0;}
	;

return:	KW_RETURN expr								{$$ = astreeCreate(AST_RETURN,0,$2,0,0,0);}
	;

controle_fluxo:	KW_WHEN '(' expr ')' KW_THEN comando			{$$ = astreeCreate(AST_WHEN_THEN,0,$3,$6,0,0);}
	| KW_WHEN '(' expr ')' KW_THEN comando KW_ELSE comando		{$$ = astreeCreate(AST_WHEN_THEN_ELSE,0,$3,$6,$8,0);}
	| KW_WHILE '(' expr ')' comando								{$$ = astreeCreate(AST_WHILE,0,$3,$5,0,0);}
	| KW_FOR '(' id '=' expr KW_TO expr ')' comando				{$$ = astreeCreate(AST_FOR,0,$3,$5,$7,$9);}
	;

bloco_comandos:	'{' seq_comandos '}'				{$$ = $2;}
	;

seq_comandos: comando ';' seq_comandos				{$$ = astreeCreate(AST_SEQ_CMD,0,$1,$3,0,0);}
	|												{$$ = 0;}
	;

expr: expr '+' expr									{$$ = astreeCreate(AST_ADD,0,$1,$3,0,0);}
	| expr '-' expr									{$$ = astreeCreate(AST_SUB,0,$1,$3,0,0);}
	| expr '*' expr									{$$ = astreeCreate(AST_MUL,0,$1,$3,0,0);}
	| expr '/' expr									{$$ = astreeCreate(AST_DIV,0,$1,$3,0,0);}
	| expr '>' expr									{$$ = astreeCreate(AST_LOGIC_G,0,$1,$3,0,0);}
	| expr '<' expr									{$$ = astreeCreate(AST_LOGIC_L,0,$1,$3,0,0);}
	| expr OPERATOR_LE expr							{$$ = astreeCreate(AST_LOGIC_LE,0,$1,$3,0,0);}
	| expr OPERATOR_GE expr							{$$ = astreeCreate(AST_LOGIC_GE,0,$1,$3,0,0);}  
	| expr OPERATOR_EQ expr							{$$ = astreeCreate(AST_LOGIC_EQ,0,$1,$3,0,0);}  
	| expr OPERATOR_NE expr							{$$ = astreeCreate(AST_LOGIC_NE,0,$1,$3,0,0);}  
	| expr OPERATOR_AND expr						{$$ = astreeCreate(AST_LOGIC_AND,0,$1,$3,0,0);}  
	| expr OPERATOR_OR expr							{$$ = astreeCreate(AST_LOGIC_OR,0,$1,$3,0,0);}
	| '!' expr										{$$ = astreeCreate(AST_LOGIC_NOT,0,$2,0,0,0);}
	| '(' expr ')'									{$$ = $2;}
	| value											{$$ = $1;}
	| TK_IDENTIFIER									{$$ = astreeCreate(AST_SYMBOL,$1,0,0,0,0);}
	| TK_IDENTIFIER '[' expr ']'					{$1 = astreeCreate(AST_SYMBOL,$1,0,0,0,0); $$ = astreeCreate(AST_VECTOR_EXPR,0,$1,$3,0,0);}
	| chamada_func									{$$ = $1;}
	;

chamada_func: TK_IDENTIFIER '(' list_arg ')'		{$1 = astreeCreate(AST_SYMBOL,$1,0,0,0,0); $$ = astreeCreate(AST_FUNC_CALL,0,$1,$3,0,0);}
	;		

list_arg: expr resto_arg							{$$ = astreeCreate(AST_LIST_ARG,0,$1,$2,0,0);}
	| 												{$$ = 0;}
	;

resto_arg: ',' expr resto_arg						{$$ = astreeCreate(AST_LIST_ARG,0,$2,$3,0,0);}
	|												{$$ = 0;}
	;

value: LIT_INTEGER 									{$$ = astreeCreate(AST_SYMBOL,$1,0,0,0,0);}
	| LIT_REAL  									{$$ = astreeCreate(AST_SYMBOL,$1,0,0,0,0);}
	| LIT_CHAR  									{$$ = astreeCreate(AST_SYMBOL,$1,0,0,0,0);}
	;

id: TK_IDENTIFIER									{$$ = astreeCreate(AST_SYMBOL,$1,0,0,0,0);}
	;

str: LIT_STRING										{$$ = astreeCreate(AST_SYMBOL,$1,0,0,0,0);}
	;

int: LIT_INTEGER									{$$ = astreeCreate(AST_SYMBOL,$1,0,0,0,0);}
	;

%%

void yyerror(const char *s){
	printf("Linha %d [erro de sintaxe]: %s.\n", getLineNumber(), s);
	exit(3);
}
