// Amanda Torbes e Gabriel Moita

#include "lex.yy.h"
#include "astree.h"
#include "hash.h"
#include "y.tab.h"
#include "semantics.h"

void initMe(void);
int isRunning(void);
int yyparse(void);

void readFile(int argc, char *argv[]){
	
	if(argc < 3){
		fprintf(stderr, "%s", "Missing file name! Command format: ./executable_program <input_name> <output_name> \n");
		exit(1);
	}

	FILE* input = fopen(argv[1], "r");
	if(input == NULL){
		fprintf(stderr, "%s", "Can't open input file. \n");
		exit(1);
	}

	yyin = input;

	yyparse();
	
}

int main(int argc, char *argv[]) {
	semanticErrors = 0;
	initMe();
	readFile(argc, argv);

	int numErrors = semanticFullCheck(ast);
	if(numErrors){
		fprintf(stderr,"%d erros semanticos.\n", numErrors);
		exit(4);
	}

	FILE* output = fopen(argv[2], "w+");

	if(output == NULL){
		fprintf(stderr, "%s", "Can't open output file. \n");
		exit(1);
	}

	astreeProgram(ast,output); 
	fclose(output);	
	//hash_print();
	exit(0);
}
