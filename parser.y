
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
//%type<astree> comando
%type<astree> atrib
//%type<astree> read
//%type<astree> print
//%type<astree> list_elem
//%type<astree> resto_list_elem
//%type<astree> return
//%type<astree> controle_fluxo
//%type<astree> bloco_comandos
//%type<astree> seq_comandos
%type<astree> expr
//%type<astree> chamada_func
//%type<astree> list_arg
//%type<astree> resto_arg
//%type<symbol> type
%type<symbol> value

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


program: cjto_declar ;

cjto_declar: declar ';' cjto_declar
	| 
	;

declar: declar_var_globais 
	| declar_func 
	;

declar_var_globais: TK_IDENTIFIER ':' type value
	| TK_IDENTIFIER ':' declar_vetor
	;

declar_vetor: type '[' LIT_INTEGER ']' seq_num
	| type '[' LIT_INTEGER ']';
						
seq_num: value seq_num
	| value
	;

declar_func: cabecalho comando
	;

cabecalho: type TK_IDENTIFIER '(' list_params ')'
	;

list_params: param resto_params
	| 
	;

resto_params: ',' param resto_params
	|
	;

param: type TK_IDENTIFIER
	;

comando: bloco_comandos
	| atrib
	| controle_fluxo
	| read
	| print
	| return
	| 
	;
						
atrib: TK_IDENTIFIER '=' expr					{astreePrint($3,0);printf("\n");}
	| TK_IDENTIFIER '#' expr '=' expr			{astreePrint($5,0);printf("\n");}
	;

read: KW_READ TK_IDENTIFIER
	;

print: KW_PRINT list_elem
	;

list_elem: LIT_STRING resto_list_elem
	| expr resto_list_elem
	;

resto_list_elem: LIT_STRING resto_list_elem
	| expr resto_list_elem
	| 
	;

return:	KW_RETURN expr
	;

controle_fluxo:	KW_WHEN '(' expr ')' KW_THEN comando
	| KW_WHEN '(' expr ')' KW_THEN comando KW_ELSE comando
	| KW_WHILE '(' expr ')' comando
	| KW_FOR '(' TK_IDENTIFIER '=' expr KW_TO expr ')' comando
	;

bloco_comandos:	'{' seq_comandos '}'
	;

seq_comandos: comando ';' seq_comandos
	|
	;

expr: expr '+' expr								{$$ = astreeCreate(AST_ADD,0,$1,$3,0,0);}
	| expr '-' expr								{$$ = astreeCreate(AST_SUB,0,$1,$3,0,0);}
	| expr '*' expr								{$$ = astreeCreate(AST_MUL,0,$1,$3,0,0);}
	| expr '/' expr								{$$ = astreeCreate(AST_DIV,0,$1,$3,0,0);}
	| expr '>' expr								{$$ = astreeCreate(AST_LOGIC_G,0,$1,$3,0,0);}
	| expr '<' expr								{$$ = astreeCreate(AST_LOGIC_L,0,$1,$3,0,0);}
	| expr OPERATOR_LE expr						{$$ = astreeCreate(AST_LOGIC_LE,0,$1,$3,0,0);}
	| expr OPERATOR_GE expr						{$$ = astreeCreate(AST_LOGIC_GE,0,$1,$3,0,0);}  
	| expr OPERATOR_EQ expr						{$$ = astreeCreate(AST_LOGIC_EQ,0,$1,$3,0,0);}  
	| expr OPERATOR_NE expr						{$$ = astreeCreate(AST_LOGIC_NE,0,$1,$3,0,0);}  
	| expr OPERATOR_AND expr					{$$ = astreeCreate(AST_LOGIC_AND,0,$1,$3,0,0);}  
	| expr OPERATOR_OR expr						{$$ = astreeCreate(AST_LOGIC_OR,0,$1,$3,0,0);}
	| '!' expr									{$$ = astreeCreate(AST_LOGIC_NOT,0,$2,0,0,0);}
	| '(' expr ')'								{}
	| value										{$$ = $1;}
	| TK_IDENTIFIER								{$$ = $1;}
	| TK_IDENTIFIER '[' expr ']'				{}
	| chamada_func								{}
	;

chamada_func: TK_IDENTIFIER '(' list_arg ')';

list_arg: expr resto_arg
	| 
	;

resto_arg: ',' expr resto_arg
	|
	;


type: KW_BYTE 
	| KW_SHORT 
	| KW_LONG 
	| KW_FLOAT 
	| KW_DOUBLE 
	;

value: LIT_INTEGER 								{$$ = astreeCreate(AST_SYMBOL,$1,0,0,0,0);}
	| LIT_REAL  								{$$ = astreeCreate(AST_SYMBOL,$1,0,0,0,0);}
	| LIT_CHAR  								{$$ = astreeCreate(AST_SYMBOL,$1,0,0,0,0);}
	;

%%

void yyerror(const char *s){
	printf("Linha %d [erro de sintaxe]: %s.\n", getLineNumber(), s);
	exit(3);
}
