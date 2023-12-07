#include "vetorSCM.h"
#include "struct.h"

void quantizacao(int **matrizQuant, int tamMatriz, int **matrizNova, int quant){
    struct pgm image;

    float intv =(float)image.mv/quant;
    int m = 0;

    for(int i = 0; i<tamMatriz; i++){
        for(int j = 0; j<tamMatriz; j++){
            while(m!=quant){
                if(matrizNova[i][j] >= intv*m && matrizNova[i][j]<intv*(m+1)){
                    matrizQuant[i][j] = m;
                }
                m++;
            }
            m=0;
        }
    }
}

void gerarScm(int *vetorSCM, int quant, int **matrizQuantOrig, int **matrizQuantFiltro, int tamMatriz){

    for(int i = 0; i<quant*quant; i++){
        *(vetorSCM+i) = 0;
    }

    for(int i = 0; i<tamMatriz; i++){
        for(int j = 0; j<tamMatriz; j++){
            *(vetorSCM+(matrizQuantOrig[i][j]*quant)+matrizQuantFiltro[i][j]) += 1;
        }
    }

}
void criarArquivo(int *vetorSCM, int quant){
    int m = 0;
    char c;

    FILE *file = fopen("teste.csv", "w");
    if(!file){
        exit(1);
    }
    while(m<quant*quant){
        c = *(vetorSCM+m)+48;
        fputc(c, file);
        fputs(",", file);
        m++;
    }
    fclose(file);

}