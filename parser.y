
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

//%type<astree> program
//%type<astree> cjto_declar
//%type<astree> declar
//%type<astree> declar_var_globais
//%type<astree> declar_vetor
//%type<astree> seq_num
//%type<astree> declar_func
//%type<astree> cabecalho
//%type<astree> list_params
//%type<astree> resto_params
//%type<astree> param
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
//%type<symbol> type
%type<symbol> value
%type<symbol> id
%type<symbol> str

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


program: cjto_declar 								//{astreePrint($$,0);}
	;

cjto_declar: declar ';' cjto_declar					//{$$ = astreeCreate(AST_CJTO_DECLAR,0,$1,$3,0,0);}
	| 												//{$$ = 0}
	;

declar: declar_var_globais							//{$$ = $1} 
	| declar_func 									//{$$ = $1}
	;

declar_var_globais: id ':' type value
	| id ':' declar_vetor
	;

declar_vetor: type '[' LIT_INTEGER ']' seq_num
	| type '[' LIT_INTEGER ']';
						
seq_num: value seq_num
	| value
	;

declar_func: cabecalho comando						{astreePrint($2,0);printf("\n");}
	;

cabecalho: type id '(' list_params ')'
	;

list_params: param resto_params
	| 
	;

resto_params: ',' param resto_params
	|
	;

param: type id
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


type: KW_BYTE 
	| KW_SHORT 
	| KW_LONG 
	| KW_FLOAT 
	| KW_DOUBLE 
	;

value: LIT_INTEGER 									{$$ = astreeCreate(AST_SYMBOL,$1,0,0,0,0);}
	| LIT_REAL  									{$$ = astreeCreate(AST_SYMBOL,$1,0,0,0,0);}
	| LIT_CHAR  									{$$ = astreeCreate(AST_SYMBOL,$1,0,0,0,0);}
	;

id: TK_IDENTIFIER									{$$ = astreeCreate(AST_SYMBOL,$1,0,0,0,0);}
	;

str: LIT_STRING										{$$ = astreeCreate(AST_SYMBOL,$1,0,0,0,0);}
	;

%%

void yyerror(const char *s){
	printf("Linha %d [erro de sintaxe]: %s.\n", getLineNumber(), s);
	exit(3);
}
