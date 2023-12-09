#include <stdio.h>
#include <stdlib.h>

int calcularMedia(struct pgm *, int, int, int);
void gerarMatrizBorrada(struct pgm *, int);
void quantizacao(struct pgm *, int);
void quantizacao1(struct pgm *, int);
void gerarScm(struct pgm *, int);
void criarArquivo(struct pgm *, int, char *);