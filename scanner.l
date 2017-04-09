%{
	#include <stdio.h>
	#include <string.h>
	#include "tokens.h"
	#include "hash.h"

	int lineNumber;
	int running;

	char buf[1000];
	char *s;

%}

%x COMMENT
%x STRING

%%
"byte"					{return KW_BYTE;}
"short"					{return KW_SHORT;}
"long"					{return KW_LONG;}
"float"					{return KW_FLOAT;}
"double"				{return KW_DOUBLE;}
"when"					{return KW_WHEN;}
"then"					{return KW_THEN;}
"else"					{return KW_ELSE;}
"while"					{return KW_WHILE;}
"for"					{return KW_FOR;}
"read"					{return KW_READ;}
"return"				{return KW_RETURN;}
"print"					{return KW_PRINT;}

"<="					{return OPERATOR_LE;}
">="					{return OPERATOR_GE;}
"=="					{return OPERATOR_EQ;}
"!="					{return OPERATOR_NE;}
"&&"					{return OPERATOR_AND;}
"||"					{return OPERATOR_OR;}
[-,;:/()+*<>=!&$#{}\[\]]		{return yytext[0];}

[a-zA-Z_][a-zA-Z_0-9]*			{hash_insert(TK_IDENTIFIER, yytext); return TK_IDENTIFIER;}
[0-9]+					{hash_insert(LIT_INTEGER, yytext); return LIT_INTEGER;}
[0-9]+.[0-9]+				{hash_insert(LIT_REAL, yytext); return LIT_REAL;}
'[-a-zA-Z_]'				{hash_insert(LIT_CHAR, yytext); return LIT_CHAR;}
"\""					{BEGIN(STRING); s = buf; *s++ = *yytext;}

\n					{++lineNumber;}
[ \t]
"//".*
"/*"					BEGIN(COMMENT);
.					{return TOKEN_ERROR;}

<COMMENT>"*/" 			BEGIN(INITIAL);
<COMMENT>.
<COMMENT>\n				{++lineNumber;}

<STRING>"\""			{*s++ = *yytext; *s = 0; hash_insert(LIT_STRING, buf); return LIT_STRING;}
<STRING>.			{*s++ = *yytext;}
<STRING>\n			{++lineNumber; *s++ = '\n';}

%%

void readFile(int argc, char *argv[]){
	int token;
	
	if(argc < 2){
		fprintf(stderr, "%s", "Missing file name! Command format: ./executable_program <file_name> \n");
	}

	FILE* file = fopen(argv[1], "r");
	if(file == NULL){
		fprintf(stderr, "%s", "Can't open file. \n");
		exit(1);
	}

	yyin = file;

	while(running){
		token = yylex();

		if(!running) break;

		switch(token){
			case KW_BYTE:		printf("BYTE na linha %d.\n", lineNumber); break;
			case KW_SHORT:		printf("SHORT na linha %d.\n", lineNumber); break;
			case KW_LONG:		printf("LONG na linha %d.\n", lineNumber); break;
			case KW_FLOAT:		printf("FLOAT na linha %d.\n", lineNumber); break;
			case KW_DOUBLE:		printf("DOUBLE na linha %d.\n", lineNumber); break;
			case KW_WHEN:		printf("WHEN na linha %d.\n", lineNumber); break;
			case KW_THEN:		printf("THEN na linha %d.\n", lineNumber); break;
			case KW_ELSE:		printf("ELSE na linha %d.\n", lineNumber); break;
			case KW_WHILE:		printf("WHILE na linha %d.\n", lineNumber); break;
			case KW_FOR:		printf("FOR na linha %d.\n", lineNumber); break;
			case KW_READ:		printf("READ na linha %d.\n", lineNumber); break;
			case KW_RETURN:		printf("RETURN na linha %d.\n", lineNumber); break;
			case KW_PRINT:		printf("PRINT na linha %d.\n", lineNumber); break;

			case OPERATOR_LE:	printf("<= na linha %d.\n", lineNumber); break;
			case OPERATOR_GE:	printf(">= na linha %d.\n", lineNumber); break;
			case OPERATOR_EQ:	printf("== na linha %d.\n", lineNumber); break;
			case OPERATOR_NE:	printf("!= na linha %d.\n", lineNumber); break;
			case OPERATOR_AND:	printf("&& na linha %d.\n", lineNumber); break;
			case OPERATOR_OR:	printf("|| na linha %d.\n", lineNumber); break;

			case TK_IDENTIFIER: printf("IDENTIFICADOR na linha %d.\n", lineNumber); break;
			case LIT_INTEGER: 	printf("INTEGER na linha %d.\n", lineNumber); break;
			case LIT_REAL: 		printf("REAL na linha %d.\n", lineNumber); break;
			case LIT_CHAR: 		printf("CHAR na linha %d.\n", lineNumber); break;
			case LIT_STRING: 	printf("STRING na linha %d.\n", lineNumber); break;
	
			case TOKEN_ERROR: 	printf("ERRO na linha %d. %s\n", lineNumber, yytext); break;
			default:
								printf("Caractere %s na linha %d.\n", yytext, lineNumber); break;
		}
	}
	hash_print();
}

int getLineNumber(void){
	return lineNumber;
}

int isRunning(void){
	return running;
}

int yywrap(void){
	running = 0;
	return 1;
}

void initMe(void){
	lineNumber = 1;
	running = 1;
	hash_initialize();
}

int main(int argc, char *argv[]) {
	initMe();
	readFile(argc, argv);
	return 0;
}


