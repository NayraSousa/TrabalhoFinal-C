#include <stdio.h>
#include <stdlib.h>

int calcularMedia(struct pgm *, int, int, int);
void gerarMatrizBorrada(struct pgm *, int, unsigned int *);
void quantizacao(struct pgm *, int, unsigned int *, unsigned int *, unsigned int *);
void gerarScm(struct pgm *, int, unsigned int *, unsigned int *, unsigned int *);
void criarArquivo(struct pgm *, int, char *, unsigned int *);