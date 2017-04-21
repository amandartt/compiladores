
%{
	#include <stdio.h>	 
	#include <stdlib.h>		  

	int yylex();
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
	program: var_globais ;

	type: KW_BYTE | KW_SHORT | KW_LONG | KW_FLOAT | KW_DOUBLE ;
	value: LIT_INTEGER | LIT_REAL | LIT_CHAR ;
	var_globais: TK_IDENTIFIER ':' type value ';' ;

%%

void yyerror(const char *s){
	printf("Linha %d: erro de sintaxe.\n", getLineNumber());
	exit(3);
}
