#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 100

struct pgm{
	int tipo;
	int c;
	int r;
	int mv;
	unsigned char *pData;
};
void readPGMImage(struct pgm *, char *);
void viewPGMImage(struct pgm *);
void writePGMImage(struct pgm *, char *);
