// Amanda Torbes e Gabriel Moita

#include "lex.yy.h"
#include "astree.h"
#include "hash.h"
#include "y.tab.h"

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

	FILE* output = fopen(argv[2], "w+");

	if(output == NULL){
		fprintf(stderr, "%s", "Can't open output file. \n");
		exit(1);
	}

	astreeProgram(ast,output); 
	fclose(output);

	
	//hash_print();
}

int main(int argc, char *argv[]) {
	initMe();
	readFile(argc, argv);
	exit(0);
}
