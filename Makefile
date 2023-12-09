all: prog.e

prog.e: diretorio.o funcoesArquivo.o funcoesImagens.o
	gcc -o prog.e diretorio.o funcoesArquivo.o funcoesImagens.o

diretorio.o: diretorio.c
	gcc -o diretorio.o -c diretorio.c

funcoesArquivo.o: funcoesArquivo.c 
	gcc -o funcoesArquivo.o -c funcoesArquivo.c

funcoesImagens.o: funcoesImagens.c
	gcc -o funcoesImagens.o -c funcoesImagens.c

clean:
	rm -f *.o prog.e	