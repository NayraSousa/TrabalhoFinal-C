all: prog.e

prog.e: diretorio.o funcoesArquivo.o
	gcc -o prog.e diretorio.o funcoesArquivo.o

diretorio.o: diretorio.c
	gcc -o diretorio.o -c diretorio.c

funcoesArquivo.o: funcoesArquivo.c 
	gcc -o funcoesArquivo.o -c funcoesArquivo.c
clean:
	rm -f *.o prog.e	