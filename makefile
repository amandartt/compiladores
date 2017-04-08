etapa1: lex.yy.o hash.o
		gcc -o etapa1 lex.yy.o hash.o
hash.o: hash.c
		gcc -c hash.c 
lex.yy.o: lex.yy.c
		gcc -c lex.yy.c
lex.yy.c: scanner.l
		flex --header-file=lex.yy.h scanner.l
clean:
	rm *.o lex.yy.c etapa1
