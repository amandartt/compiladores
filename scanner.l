%{
	// Amanda Torbes e Gabriel Moita

	#include <stdio.h>
	#include <string.h>
	#include "y.tab.h"
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
"to"					{return KW_TO;}

"<="					{return OPERATOR_LE;}
">="					{return OPERATOR_GE;}
"=="					{return OPERATOR_EQ;}
"!="					{return OPERATOR_NE;}
"&&"					{return OPERATOR_AND;}
"||"					{return OPERATOR_OR;}
[-,;:/()+*<>=!&$#{}\[\]]	{return yytext[0];}

[a-zA-Z_][a-zA-Z_0-9]*	{hash_insert(TK_IDENTIFIER, yytext); return TK_IDENTIFIER;}
[0-9]+					{hash_insert(LIT_INTEGER, yytext); return LIT_INTEGER;}
[0-9]+\.[0-9]+			{hash_insert(LIT_REAL, yytext); return LIT_REAL;}
'.'				{hash_insert(LIT_CHAR, yytext); return LIT_CHAR;}
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
<STRING>\\n				{*s++ = '\n';}
<STRING>\\t     		{ *s++ = '\t'; }
<STRING>\\\"			{*s++ = '\"';}
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


