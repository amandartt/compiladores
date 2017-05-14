// Amanda Torbes e Gabriel Moita

#include "lex.yy.h"
#include "astree.h"
#include "hash.h"
#include "y.tab.h"

void initMe(void);
int isRunning(void);
int yyparse(void);

void readFile(int argc, char *argv[]){
	
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
	yyparse();
	
	//hash_print();
}

int main(int argc, char *argv[]) {
	initMe();
	readFile(argc, argv);
	exit(0);
}
