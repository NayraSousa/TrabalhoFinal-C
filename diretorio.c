#include <dirent.h>
#include <time.h>
#include "funcoesArquivo.h"
 
int main(void)
{
    DIR *d;
    struct dirent *dir;
    struct pgm img;
    int cont = 0;
    char nomeArquivo[50];
    d = opendir("/home/nayra/Projects/trabalho-final/TrabalhoFinal-C/oncotex_pgm");

    if (d){
        clock_t begin, end;
	    double time_per_img, time_total=0;
        begin = clock();
        //move o cursor
        while ((dir = readdir(d)) != NULL){
            if(cont>1){
                strcpy(nomeArquivo, dir->d_name);
                printf("%s\n", nomeArquivo);
                readPGMImage(&img, nomeArquivo);
                
			// 			// Saída.
            }
            cont++;
        }
        closedir(d);
        end = clock();

	    time_total = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("Tempo Total: %lf\n",time_total);
    }

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