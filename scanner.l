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
[-,;:/()+*<>=!&$#{}\[\]]	{return yytext[0];}

[a-zA-Z_][a-zA-Z_0-9]*	{hash_insert(TK_IDENTIFIER, yytext); return TK_IDENTIFIER;}
[0-9]+					{hash_insert(LIT_INTEGER, yytext); return LIT_INTEGER;}
[0-9]+.[0-9]+			{hash_insert(LIT_REAL, yytext); return LIT_REAL;}
'[-a-zA-Z_]'			{hash_insert(LIT_CHAR, yytext); return LIT_CHAR;}
"\""					{BEGIN(STRING); s = buf; *s++ = *yytext; return LIT_STRING;}

\n						{++lineNumber;}
[ \t]
"//".*
"/*"					BEGIN(COMMENT);
.						{return TOKEN_ERROR;}

<COMMENT>"*/" 			BEGIN(INITIAL);
<COMMENT>.
<COMMENT>\n				{++lineNumber;}

<STRING>"\""			{*s++ = *yytext; *s = 0; hash_insert(LIT_STRING, buf); BEGIN(INITIAL);}
<STRING>.				{*s++ = *yytext;}
<STRING>\n				{++lineNumber; *s++ = '\n';}

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
			case KW_BYTE:		printf("Linha %d: BYTE.\n", lineNumber); break;
			case KW_SHORT:		printf("Linha %d: SHORT.\n", lineNumber); break;
			case KW_LONG:		printf("Linha %d: LONG.\n", lineNumber); break;
			case KW_FLOAT:		printf("Linha %d: FLOAT.\n", lineNumber); break;
			case KW_DOUBLE:		printf("Linha %d: DOUBLE.\n", lineNumber); break;
			case KW_WHEN:		printf("Linha %d: WHEN.\n", lineNumber); break;
			case KW_THEN:		printf("Linha %d: THEN.\n", lineNumber); break;
			case KW_ELSE:		printf("Linha %d: ELSE.\n", lineNumber); break;
			case KW_WHILE:		printf("Linha %d: WHILE.\n", lineNumber); break;
			case KW_FOR:		printf("Linha %d: FOR.\n", lineNumber); break;
			case KW_READ:		printf("Linha %d: READ.\n", lineNumber); break;
			case KW_RETURN:		printf("Linha %d: RETURN.\n", lineNumber); break;
			case KW_PRINT:		printf("Linha %d: PRINT.\n", lineNumber); break;

			case OPERATOR_LE:	printf("Linha %d: <=\n", lineNumber); break;
			case OPERATOR_GE:	printf("Linha %d: >=\n", lineNumber); break;
			case OPERATOR_EQ:	printf("Linha %d: ==\n", lineNumber); break;
			case OPERATOR_NE:	printf("Linha %d: !=\n", lineNumber); break;
			case OPERATOR_AND:	printf("Linha %d: &&\n", lineNumber); break;
			case OPERATOR_OR:	printf("Linha %d: ||\n", lineNumber); break;

			case TK_IDENTIFIER: printf("Linha %d: IDENTIFICADOR.\n", lineNumber); break;
			case LIT_INTEGER: 	printf("Linha %d: INTEGER.\n", lineNumber); break;
			case LIT_REAL: 		printf("Linha %d: REAL.\n", lineNumber); break;
			case LIT_CHAR: 		printf("Linha %d: CHAR.\n", lineNumber); break;
			case LIT_STRING: 	printf("Linha %d: STRING.\n", lineNumber); break;
	
			case TOKEN_ERROR: 	printf("Linha %d: ERRO. %s\n", lineNumber, yytext); break;
			default:
								printf("Linha %d: Caractere %s.\n",lineNumber,  yytext); break;
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


