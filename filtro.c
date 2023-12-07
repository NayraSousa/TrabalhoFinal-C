#include "filtro.h"
#include "struct.h"

int calcularMedia(struct pgm *img, int tamJanela) {

    int soma = 0;

    for (int i = -tamJanela / 2; i <= tamJanela / 2; i++) {
        for (int j = -tamJanela / 2; j <= tamJanela / 2; j++) {

            int linhaVizinha = img->r + i;
            int colunaVizinha = img->c + j;

            // Verifica se a posição é válida na matriz original
            if ((linhaVizinha >= 0) && (linhaVizinha < img->c) && (colunaVizinha >= 0) && (colunaVizinha < img->c)) {
                soma += *(img->pData+linhaVizinha*img->r+colunaVizinha);
            }
        }
    }
    
    return soma / (tamJanela*tamJanela);
}

void gerarMatrizBorrada(struct pgm *img, struct pgm *imgBorrada, int tamJanela) {
    for (int i = 0; i < img->r; i++) {
        for (int j = 0; j < img->c; j++) {
            *(imgBorrada->pData+i*img->r+j) = calcularMedia(&img, tamJanela);
        }
    }
}