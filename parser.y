
%{
	#include <stdio.h>	 
	#include <stdlib.h>		  

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

%token TK_IDENTIFIER 
%token LIT_INTEGER   
%token LIT_REAL      
%token LIT_CHAR      
%token LIT_STRING    

%token TOKEN_ERROR

%%
// Scratch para Gramática lang171 - Compiladores
// Amanda e Gabriel


program: 				cjto_declar ;

cjto_declar: 			declar ';' cjto_declar
			 			| declar ';' 
			 			| 
			 			;

declar: 				declar_var_globais 
						| declar_func 
						;

declar_var_globais: 	TK_IDENTIFIER ':' type value
						| TK_IDENTIFIER ':' declar_vetor
						;

declar_vetor:			type '[' LIT_INTEGER ']' seq_num
						| type '[' LIT_INTEGER ']';
						
seq_num:				value seq_num
						| value
						;

declar_func:			cabecalho comando
						;

cabecalho:				type TK_IDENTIFIER '(' list_params ')'
						;

list_params:			param resto_params
						| param
						| 
						;

resto_params:			',' param resto_params
						|
						;

param:					type TK_IDENTIFIER
						;

comando:				bloco_comandos
						| atrib
						| controle_fluxo
						| read
						| print
						| return
						| 
						;
						
atrib:					TK_IDENTIFIER '=' expr
						| TK_IDENTIFIER '#' expr '=' expr
						;

read:					KW_READ TK_IDENTIFIER
						;

print:					KW_PRINT list_elem
						;

list_elem:				LIT_STRING resto_list_elem
						| expr resto_list_elem
						;

resto_list_elem:		LIT_STRING resto_list_elem
						| expr resto_list_elem
						| 
						;

return:					KW_RETURN expr
						;

controle_fluxo:			KW_WHEN '(' expr ')' KW_THEN comando
						| KW_WHEN '(' expr ')' KW_THEN comando KW_ELSE comando
						| KW_WHILE '(' expr ')' comando
						| KW_FOR '(' TK_IDENTIFIER '=' expr KW_TO expr ')' comando
						;

bloco_comandos:			'{' seq_comandos '}'
						;

seq_comandos:			comando resto_seq_com
						;

resto_seq_com:			';' comando resto_seq_com
						| 
						;

expr:					expr d_op expr
						| unary_op expr
						| '(' expr ')'
						| value
						| TK_IDENTIFIER
						| TK_IDENTIFIER '[' expr ']'
						| chamada_func
						;

chamada_func:			TK_IDENTIFIER '(' list_arg ')';

list_arg:				arg resto_arg
						| arg
						| 
						;

resto_arg:				',' arg resto_arg
						|
						;

arg:					expr
						;

d_op:					'+'
						| '-'
						| '*'
						| '/'
						| '<'
						| '>'
						| OPERATOR_LE   
						| OPERATOR_GE   
						| OPERATOR_EQ   
						| OPERATOR_NE   
						| OPERATOR_AND  
						| OPERATOR_OR
						;

unary_op:				'!'
						| '-'
						;
type: 					KW_BYTE 
						| KW_SHORT 
						| KW_LONG 
						| KW_FLOAT 
						| KW_DOUBLE 
						;

value: 					LIT_INTEGER 
						| LIT_REAL 
						| LIT_CHAR 
						;

%%

void yyerror(const char *s){
	printf("Linha %d: erro de sintaxe.\n", getLineNumber());
	exit(3);
}
