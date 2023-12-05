#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RANGE 256

void gerarMatrizBorrada(int **, int **, int, int);
void imprimirMatriz(int **, int );
int calcularMedia(int **, int , int , int , int );
void quantizacao(int **, int , int **, int);
void gerarScm(int *, int, int **, int **, int);

int main(int argc, char *argv[]) {
    
    //Verifica argumentos da linha de comando
    if(argc != 4)exit(1);
    if(!(atoi(argv[1])%2) | !(atoi(argv[2])%2)) exit(2);

    int tamMatriz = atoi(argv[1]);
    int tamJanela = atoi(argv[2]);
    int quant = atoi(argv[3]);

    // Aloca espaço para a matriz original e a matriz nova
    int **matriz = (int **)malloc(tamMatriz * sizeof(int *));
    int **matrizNova = (int **)malloc(tamMatriz * sizeof(int *));
    int **matrizQuantOrig = (int **)malloc(tamMatriz * sizeof(int *));
    int **matrizQuantFiltro = (int **)malloc(tamMatriz * sizeof(int *));
    int *vetorSCM = (int *)malloc(quant*quant*sizeof(int));


    for (int i = 0; i < tamMatriz; i++) {
        matriz[i] = (int *)malloc(tamMatriz * sizeof(int));
        matrizNova[i] = (int *)malloc(tamMatriz * sizeof(int));
        matrizQuantOrig[i] = (int *)malloc(tamMatriz * sizeof(int));
        matrizQuantFiltro[i] = (int *)malloc(tamMatriz * sizeof(int));
    }

    // Preenche a matriz original com valores aleatórios
    srand(time(NULL));
    for (int i = 0; i < tamMatriz; i++) {
        for (int j = 0; j < tamMatriz; j++) {
            matriz[i][j] = rand() % RANGE;
        }
    }

    printf("matriz gerada:\n");
    imprimirMatriz(matriz, tamMatriz);

    gerarMatrizBorrada(matriz, matrizNova, tamMatriz, tamJanela);

    printf("\nmatriz apos filtro:\n");
    imprimirMatriz(matrizNova, tamMatriz);

    printf("\nmatriz quantizada por %i:\n", quant);

    printf("Matriz Original:\n");
    quantizacao(matrizQuantOrig, tamMatriz, matriz, quant);
    imprimirMatriz(matrizQuantOrig, tamMatriz);

    printf("\n");

    printf("Matriz filtro:\n");
    quantizacao(matrizQuantFiltro, tamMatriz, matrizNova, quant);
    imprimirMatriz(matrizQuantFiltro, tamMatriz);
    printf("\n");

    printf("Vetor SCM:\n");
    gerarScm(vetorSCM, quant, matrizQuantOrig, matrizQuantFiltro, tamMatriz);
    for(int i = 0; i<quant*quant;i++){
        if(i%quant==0){
            printf("\n");
        }
        printf("%i ", *(vetorSCM+i));
    }
    printf("\n");


    // Libera memória alocada
    for (int i = 0; i < tamMatriz; i++) {
        free(matriz[i]);
        free(matrizNova[i]);
        free(matrizQuantOrig[i]);
        free(matrizQuantFiltro[i]);
    }
    free(matriz);
    free(matrizNova);
    free(matrizQuantOrig);
    free(matrizQuantFiltro);

    return 0;
}

int calcularMedia(int **matriz, int linha, int coluna, int tamJanela, int tamanhoMatriz) {

    int soma = 0;

    for (int i = -tamJanela / 2; i <= tamJanela / 2; i++) {
        for (int j = -tamJanela / 2; j <= tamJanela / 2; j++) {

            int linhaVizinha = linha + i;
            int colunaVizinha = coluna + j;

            // Verifica se a posição é válida na matriz original
            if ((linhaVizinha >= 0) && (linhaVizinha < tamanhoMatriz) && (colunaVizinha >= 0) && (colunaVizinha < tamanhoMatriz)) {
                soma += matriz[linhaVizinha][colunaVizinha];
            }
        }
    }
    
    return soma / (tamJanela*tamJanela);
}

void imprimirMatriz(int **matriz, int tamanhoMatriz) {
    for (int i = 0; i < tamanhoMatriz; i++) {
        for (int j = 0; j < tamanhoMatriz; j++) {
            printf("%4d ", matriz[i][j]);
        }
        printf("\n");
    }
}

void gerarMatrizBorrada(int **matriz, int **matrizNova, int tamMatriz, int tamJanela) {
    for (int i = 0; i < tamMatriz; i++) {
        for (int j = 0; j < tamMatriz; j++) {
            matrizNova[i][j] = calcularMedia(matriz, i, j, tamJanela, tamMatriz);
        }
    }
}

void quantizacao(int **matrizQuant, int tamMatriz, int **matrizNova, int quant){

    float intv = (float)RANGE/quant;
    int m = 0;

    for(int i = 0; i<tamMatriz; i++){
        for(int j = 0; j<tamMatriz; j++){
            while(m!=quant){
                if(matrizNova[i][j] > intv*m && matrizNova[i][j]<intv*(m+1)){
                    matrizQuant[i][j] = m;
                }
                ++m;
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