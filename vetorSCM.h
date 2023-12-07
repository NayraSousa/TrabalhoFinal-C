#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
struct pgm{
	int tipo; //P2 or P5
	int c; //column
	int r; //row
	int mv; // max value
	int *pData; //pixels
};

void quantizacao(int **, int, int **, int);
void gerarScm(int *, int, int **, int **, int);
void criarArquivo(int *, int);