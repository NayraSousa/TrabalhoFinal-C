#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void espelharJanela(int *, int, int, int *, int);
void imprimirMatriz(int, int *);
int main(int argc, char **argv){

    if(argc!=3) exit(1);
    if((atoi(argv[1])%2==0) | (atoi(argv[2])%2==0)) exit(2);

    int tamOriginal = atoi(argv[1]);
    int tamJanela = atoi(argv[2]);

    int *matrizAleatoria = (int*)malloc(tamOriginal*tamOriginal*sizeof(int));
    int *matrizJanela = (int*)malloc(tamJanela*tamJanela*sizeof(int));
    srand(time(NULL));

    if(!matrizAleatoria) printf("Memória não alocada");
    //cria a matriz com números aleatórios
    for(int i = 0;i<tamOriginal*tamOriginal; i++) *(matrizAleatoria+i) = rand()%100;
    //cria a matriz janela inicialmente com zero
    for(int i = 0;i<tamJanela*tamJanela; i++) *(matrizJanela+i) = 0;

    imprimirMatriz(tamOriginal, matrizAleatoria);
    imprimirMatriz(tamJanela, matrizJanela);
    for(int i = 0; i<tamOriginal*tamOriginal; i++){
        //exclui as bordas
        if((i >= 0 && i<=tamOriginal) | (i<tamOriginal*tamOriginal && i>tamOriginal*tamOriginal-tamOriginal) | i%tamOriginal==0){
            printf("borda\n");
        }
        else{
        espelharJanela(matrizAleatoria, tamOriginal, i, matrizJanela, tamJanela);
        imprimirMatriz(tamJanela, matrizJanela);}
    }

    return 0;
    free(matrizAleatoria);
    free(matrizJanela);
    
}
void imprimirMatriz(int tamOriginal, int *matrizAleatoria){
    for(int i = 0; i<tamOriginal*tamOriginal; i++){
        if(!(i%tamOriginal)) printf("\n");
        printf("%5d ", *(matrizAleatoria+i));   
    }
    printf("\n");
}
//algoritmo para preencher a matriz sem os números das bordas
void espelharJanela(int *matrizAleatoria, int tamOriginal, int numCentral, int *matrizJanela, int tamJanela){

    int contadorFrente = numCentral - 1;
    int contadorTras = contadorFrente;
    int controleQuebraLinha = tamJanela/2;

    for(int i = 0 ; i <= (tamJanela*tamJanela)/2; i++){
        if(controleQuebraLinha==tamJanela){
            contadorFrente += tamOriginal-tamJanela;
            contadorTras -= tamOriginal-tamJanela;
            controleQuebraLinha = 0;
        }

        *(matrizJanela + (tamJanela*tamJanela)/2 +i) = *(matrizAleatoria + contadorFrente);
        *(matrizJanela + (tamJanela*tamJanela)/2 -i) = *(matrizAleatoria + contadorTras);
        
        contadorFrente++;
        controleQuebraLinha++;
        contadorTras--;

    }
}

