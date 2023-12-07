#include <stdio.h>
#include "vetorSCM.h"

struct pg{
	int tipo; //P2 or P5
	int c; //column
	int r; //row
	int mv; // max value
	int *pData; //pixels
};
int calcularMedia2(struct pgm *, int);
void gerarMatrizBorrada3(struct pgm *, struct pgm *, int);