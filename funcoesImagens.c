#include <stdio.h>
#include <stdlib.h>
#include "funcoesArquivo.h"
#include "funcoesImagens.h"

int calcularMedia(struct pgm *image, int linha, int coluna, int tamJanela) {

    int soma = 0;

    for (int i = -tamJanela / 2; i <= tamJanela / 2; i++) {
        for (int j = -tamJanela / 2; j <= tamJanela / 2; j++) {

            int linhaVizinha = linha+i;
            int colunaVizinha = coluna+j;

            // Verifica se a posição é válida na matriz original
            if ((linhaVizinha >= 0) && (linhaVizinha < image->r) && (colunaVizinha >= 0) && (colunaVizinha < image->c)) {
                soma += *(image->pData+(image->r*linhaVizinha)+colunaVizinha);
            }
        }
    }
    
    return soma / (tamJanela*tamJanela);
}
void gerarMatrizBorrada(struct pgm *image, int tamJanela) {
    printf("Borrando imagem\n");
    for (int i = 0; i < image->r; i++) {
        for(int j = 0; j<image->c;j++){
            *(image->pDataBorrado+(i*image->r)+j) = calcularMedia(image, i, j, tamJanela);
        }
    }
}
void quantizacao(struct pgm *image, int quant){
    printf("Quantização imagem\n");

    float intv =(float)image->mv/quant;
    int m = 0;

    for(int i = 0; i<image->r; i++){
        for(int j = 0; j<image->c; j++){
            while(m!=quant){
                if(*(image->pData+(i*image->r)+j) >= intv*m && *(image->pData+(i*image->r)+j)<intv*(m+1)){
                    *(image->pDataOrigQuantizado+(i*image->r)+j) = m;
                }
                if(*(image->pDataBorrado+(i*image->r)+j) >= intv*m && *(image->pDataBorrado+(i*image->r)+j)<intv*(m+1)){
                    *(image->pDataBorradoQuantizado+(i*image->r)+j) = m;
                }
                m++;
            }
            m=0;
        }
    }
}
void gerarScm(struct pgm *image, int quant){
    printf("Gerando SCM\n");
    image->vetorSCM = (unsigned char*) malloc(quant*quant* sizeof(unsigned char));
    for(int i = 0; i<quant*quant; i++){
        *(image->vetorSCM+i) = 0;
    }

    for(int i = 0; i<image->r; i++){
        for(int j = 0; j<image->c; j++){
            *(image->vetorSCM+(*(image->pDataOrigQuantizado+(i*image->r)+j)*quant)+*(image->pDataBorradoQuantizado+(i*image->r)+j)) += 1;
        }
        printf("%c", *(image->vetorSCM+i));
    }

}
void criarArquivo(struct pgm *image, int quant, char *filename){
    int m = 0;
    char c;

    FILE *file = fopen(filename, "a");
    if(!file){
        exit(1);
    }
    while(m<quant*quant){
        c = *(image->vetorSCM+m)+48;
        fputc(c, file);
        fputs(",", file);
        m++;
    }
    fputs("\n", file);
    fclose(file);

}
