#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pgm{
	int tipo;
	int c;
	int r;
	int mv;
	unsigned char *pData;
	unsigned char *pDataBorrado;
	unsigned char *pDataOrigQuantizado;
	unsigned char *pDataBorradoQuantizado;
	unsigned char *vetorSCM;
};
void readPGMImage(struct pgm *, char *);
void viewPGMImage(struct pgm *);
void writePGMImage(struct pgm *, char *);
