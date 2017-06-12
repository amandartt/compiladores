%{
	// Amanda Torbes e Gabriel Moita

	#include <stdio.h>
	#include <string.h>
	#include "astree.h"
	#include "hash.h"
	#include "y.tab.h"
	#include "symbol_defs.h"


	extern YYSTYPE yylval;

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
"to"					{return KW_TO;}

"<="					{return OPERATOR_LE;}
">="					{return OPERATOR_GE;}
"=="					{return OPERATOR_EQ;}
"!="					{return OPERATOR_NE;}
"&&"					{return OPERATOR_AND;}
"||"					{return OPERATOR_OR;}
[-,;:/()+*<>=!&$#{}\[\]]		{return yytext[0];}

[a-zA-Z_][a-zA-Z_0-9]*			{yylval.symbol = hash_insert(SYMBOL_IDENTIFIER, yytext, DATATYPE_UNDEFINED, lineNumber); return TK_IDENTIFIER;}
[0-9]+					{yylval.symbol = hash_insert(SYMBOL_LIT_INT, yytext, DATATYPE_LONG, lineNumber); return LIT_INTEGER;}
[0-9]+\.[0-9]+				{yylval.symbol = hash_insert(SYMBOL_LIT_REAL, yytext, DATATYPE_DOUBLE, lineNumber); return LIT_REAL;}
'.'					{yylval.symbol = hash_insert(SYMBOL_LIT_CHAR, yytext, DATATYPE_CHAR, lineNumber); return LIT_CHAR;}
"\""					{BEGIN(STRING); s = buf; *s++ = *yytext; /*return LIT_STRING;*/}

\n					{++lineNumber;}
[ \t]
"//".*
"/*"					BEGIN(COMMENT);
.					{return TOKEN_ERROR;}

<COMMENT>"*/" 				BEGIN(INITIAL);
<COMMENT>.
<COMMENT>\n				{++lineNumber;}

<STRING>"\""		{*s++ = *yytext; *s = 0; yylval.symbol = hash_insert(SYMBOL_LIT_STRING, buf,DATATYPE_STRING, lineNumber); BEGIN(INITIAL); return LIT_STRING;}
<STRING>\\n				{*s++ = '\\'; *s++ = 'n';}
<STRING>\\t     			{*s++ = '\\'; *s++ = 't';}
<STRING>\\\"				{*s++ = '\"';}
<STRING>.				{*s++ = *yytext;}
<STRING>\n				{++lineNumber; *s++ = '\n';}

%%

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


