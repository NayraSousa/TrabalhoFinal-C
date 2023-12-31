/***************************************************************/
/* Alunos: Julia Abreu, Leticia Saraiva e Nayra de Sousa       */
/* Avaliação 04: Trabalho Final                                */
/* Matrículas: 20231045050106, 20231045050149, 20231045050130  */
/* Compilador: gcc 11.4.0                                      */
/* 04.505.23 − 2023.2 − Prof. Daniel Ferreira                  */
/***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "funcoesArquivo.h"
#include "funcoesImagens.h"

int calcularMedia(struct pgm *image, int linha, int coluna, int tamJanela) {

    int soma = 0;
    //O i e o j vão da linha anterior até a linha posterior
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

void gerarMatrizBorrada(struct pgm *image, int tamJanela, unsigned int *pDataBorrado) {
    printf("Borrando imagem\n");
    for (int i = 0; i < image->r; i++) {
        for(int j = 0; j<image->c;j++){
            *(pDataBorrado+(i*image->r)+j) = calcularMedia(image, i, j, tamJanela);
        }
    }
}

void quantizacao(struct pgm *image, int quant, unsigned int *pDataOrigQuantizado, unsigned int *pDataBorrado, unsigned int *pDataBorradoQuantizado){
    printf("Quantizando imagem\n");

    float intv =(float)image->mv/quant;
    int m = 0;

    for(int i = 0; i<image->r; i++){
        for(int j = 0; j<image->c; j++){
            while(m!=quant){
                //verifica se o elemento do vetor original está entre o intervalo, sendo m o nível de quantização
                if(*(image->pData+(i*image->r)+j) >= intv*m && *(image->pData+(i*image->r)+j)<intv*(m+1)){
                    *(pDataOrigQuantizado+(i*image->r)+j) = m;
                }
                //verifica se o elemento do vetor borrado está entre o intervalo, sendo m o nível de quantização
                if(*(pDataBorrado+(i*image->r)+j) >= intv*m && *(pDataBorrado+(i*image->r)+j)<intv*(m+1)){
                    *(pDataBorradoQuantizado+(i*image->r)+j) = m;
                }
                m++;
            }
            m=0;
        }
    }
}

void gerarScm(struct pgm *image, int quant, unsigned int *pDataOrigQuantizado, unsigned int *pDataBorradoQuantizado, unsigned int *vetorSCM){
    printf("Gerando SCM\n");

    for(int i = 0; i<quant*quant; i++){
        *(vetorSCM+i) = 0;
    }
    for(int i = 0; i<image->r; i++){
        for(int j = 0; j<image->c; j++){
            int linha = *(pDataOrigQuantizado+i*image->r+j);
            int coluna = *(pDataBorradoQuantizado+i*image->r+j);
            *(vetorSCM+linha*quant+coluna) += 1;
        }
    }

}

void criarArquivo(struct pgm *image, int quant, char *filename, unsigned int *vetorSCM){
    printf("Gerando Arquivo\n");
    int m = 0; //contador

    FILE *file = fopen(filename, "a");
    if(!file){
        exit(1);
    }
    
    fputs("\n", file);
    while(m<(quant*quant)){
        //transforma de int pra char
        fprintf(file, "%hhu", *(vetorSCM+m));
        fputs(",", file);
        m++;
    }

}

