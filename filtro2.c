#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RANGE 10

void GerarMatrizBorrada(int **, int **, int, int);
void imprimirMatriz(int **, int );
int calcularMedia(int **, int , int , int , int );

int main(int argc, char *argv[]) {
    
    if(argc != 3)exit(1);
    if(!(atoi(argv[1])%2) | !(atoi(argv[2])%2)) exit(2);

    int tamz = atoi(argv[1]);
    int tamj = atoi(argv[2]);

    // Aloca espaço para a matriz original e a matriz nova
    int **matriz = (int **)malloc(tamz * sizeof(int *));
    int **matrizNova = (int **)malloc(tamz * sizeof(int *));

    for (int i = 0; i < tamz; i++) {
        matriz[i] = (int *)malloc(tamz * sizeof(int));
        matrizNova[i] = (int *)malloc(tamz * sizeof(int));
    }

    // Preenche a matriz original com valores aleatórios
    srand(time(NULL));
    for (int i = 0; i < tamz; i++) {
        for (int j = 0; j < tamz; j++) {
            matriz[i][j] = rand() % RANGE;
        }
    }

    printf("matriz gerada:\n");
    imprimirMatriz(matriz, tamz);

    GerarMatrizBorrada(matriz, matrizNova, tamz, tamj);

    printf("\nmatriz apos filtro:\n");
    imprimirMatriz(matrizNova, tamz);


    for (int i = 0; i < tamz; i++) {
        free(matriz[i]);
        free(matrizNova[i]);
    }
    free(matriz);
    free(matrizNova);

    return 0;
}

int calcularMedia(int **m, int lin, int col, int tamj, int tm) {

    int soma = 0;

    for (int i = -tamj / 2; i <= tamj / 2; i++) {
        for (int j = -tamj / 2; j <= tamj / 2; j++) {

            int linv = lin + i;
            int colv = col + j;

            // Verifica se a posição é válida na matriz original
            if ((linv >= 0) && (linv < tm) && (colv >= 0) && (colv < tm)) {
                soma += m[linv][colv];
            }
        }
    }
    
    return soma / (tamj*tamj);
}

void imprimirMatriz(int **m, int t) {
    for (int i = 0; i < t; i++) {
        for (int j = 0; j < t; j++) {
            printf("%4d ", m[i][j]);
        }
        printf("\n");
    }
}

void GerarMatrizBorrada(int **m, int **matrizNova, int tamz, int tamj) {
    for (int i = 0; i < tamz; i++) {
        for (int j = 0; j < tamz; j++) {
            matrizNova[i][j] = calcularMedia(m, i, j, tamj, tamz);
        }
    }
}
