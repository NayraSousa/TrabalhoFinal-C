#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RANGE 10

void GerarMatrizBorrada(int **, int **, int, int);
void imprimirMatriz(int **, int );
int calcularMedia(int **, int , int , int , int );

int main(int argc, char *argv[]) {
    
    //Verifica argumentos da linha de comando
    if(argc != 3)exit(1);
    if(!(atoi(argv[1])%2) | !(atoi(argv[2])%2)) exit(2);

    int tamMatriz = atoi(argv[1]);
    int tamJanela = atoi(argv[2]);

    // Aloca espaço para a matriz original e a matriz nova
    int **matriz = (int **)malloc(tamMatriz * sizeof(int *));
    int **matrizNova = (int **)malloc(tamMatriz * sizeof(int *));

    for (int i = 0; i < tamMatriz; i++) {
        matriz[i] = (int *)malloc(tamMatriz * sizeof(int));
        matrizNova[i] = (int *)malloc(tamMatriz * sizeof(int));
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

    GerarMatrizBorrada(matriz, matrizNova, tamMatriz, tamJanela);

    printf("\nmatriz apos filtro:\n");
    imprimirMatriz(matrizNova, tamMatriz);

    // Libera memória alocada
    for (int i = 0; i < tamMatriz; i++) {
        free(matriz[i]);
        free(matrizNova[i]);
    }
    free(matriz);
    free(matrizNova);

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

void GerarMatrizBorrada(int **matriz, int **matrizNova, int tamMatriz, int tamJanela) {
    for (int i = 0; i < tamMatriz; i++) {
        for (int j = 0; j < tamMatriz; j++) {
            matrizNova[i][j] = calcularMedia(matriz, i, j, tamJanela, tamMatriz);
        }
    }
}
