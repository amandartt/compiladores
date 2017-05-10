etapa3: y.tab.o lex.yy.o main.o hash.o astree.o
		gcc -o etapa2 y.tab.o lex.yy.o main.o hash.o astree.o
main.o:	main.c
		gcc -c main.c
hash.o: hash.c
		gcc -c hash.c
astree.o: astree.c
		gcc -c astree.c
y.tab.o: y.tab.c
		gcc -c y.tab.c 
y.tab.c: parser.y
		yacc -d parser.y
lex.yy.o: lex.yy.c
		gcc -c lex.yy.c
lex.yy.c: scanner.l
		flex --header-file=lex.yy.h scanner.l
clean:
	rm *.o lex.yy.c lex.yy.h y.tab.c y.tab.h etapa3
