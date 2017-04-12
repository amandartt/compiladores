// Amanda Torbes e Gabriel Moita

#include "lex.yy.h"
#include "hash.h"
#include "tokens.h"

void initMe(void);
int isRunning(void);
int getLineNumber(void);

void readFile(int argc, char *argv[]){
	int token;
	
	if(argc < 2){
		fprintf(stderr, "%s", "Missing file name! Command format: ./executable_program <file_name> \n");
		exit(1);
	}

	FILE* file = fopen(argv[1], "r");
	if(file == NULL){
		fprintf(stderr, "%s", "Can't open file. \n");
		exit(1);
	}

	yyin = file;

	while(isRunning()){
		token = yylex();

		if(!isRunning()) break;

		switch(token){
			case KW_BYTE:		printf("Linha %d: BYTE.\n", getLineNumber()); break;
			case KW_SHORT:		printf("Linha %d: SHORT.\n", getLineNumber()); break;
			case KW_LONG:		printf("Linha %d: LONG.\n", getLineNumber()); break;
			case KW_FLOAT:		printf("Linha %d: FLOAT.\n", getLineNumber()); break;
			case KW_DOUBLE:		printf("Linha %d: DOUBLE.\n", getLineNumber()); break;
			case KW_WHEN:		printf("Linha %d: WHEN.\n", getLineNumber()); break;
			case KW_THEN:		printf("Linha %d: THEN.\n", getLineNumber()); break;
			case KW_ELSE:		printf("Linha %d: ELSE.\n", getLineNumber()); break;
			case KW_WHILE:		printf("Linha %d: WHILE.\n", getLineNumber()); break;
			case KW_FOR:		printf("Linha %d: FOR.\n", getLineNumber()); break;
			case KW_READ:		printf("Linha %d: READ.\n", getLineNumber()); break;
			case KW_RETURN:		printf("Linha %d: RETURN.\n", getLineNumber()); break;
			case KW_PRINT:		printf("Linha %d: PRINT.\n", getLineNumber()); break;

			case OPERATOR_LE:	printf("Linha %d: <=\n", getLineNumber()); break;
			case OPERATOR_GE:	printf("Linha %d: >=\n", getLineNumber()); break;
			case OPERATOR_EQ:	printf("Linha %d: ==\n", getLineNumber()); break;
			case OPERATOR_NE:	printf("Linha %d: !=\n", getLineNumber()); break;
			case OPERATOR_AND:	printf("Linha %d: &&\n", getLineNumber()); break;
			case OPERATOR_OR:	printf("Linha %d: ||\n", getLineNumber()); break;

			case TK_IDENTIFIER: 	printf("Linha %d: IDENTIFICADOR.\n", getLineNumber()); break;
			case LIT_INTEGER: 	printf("Linha %d: INTEGER.\n", getLineNumber()); break;
			case LIT_REAL: 		printf("Linha %d: REAL.\n", getLineNumber()); break;
			case LIT_CHAR: 		printf("Linha %d: CHAR.\n", getLineNumber()); break;
			case LIT_STRING: 	printf("Linha %d: STRING.\n", getLineNumber()); break;
	
			case TOKEN_ERROR: 	printf("Linha %d: ERRO. %s\n", getLineNumber(), yytext); break;
			default:
								printf("Linha %d: Caractere %s.\n",getLineNumber(),  yytext); break;
		}
	}
	hash_print();
}

int main(int argc, char *argv[]) {
	initMe();
	readFile(argc, argv);
	return 0;
}
