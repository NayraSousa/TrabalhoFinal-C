#include <dirent.h>
#include <time.h>
#include "funcoesArquivo.h"
#include "funcoesImagens.h"
 
int main(int argc, char *argv[])
{
    DIR *d;
    struct dirent *dir;
    struct pgm img;
    int cont = 0;
    if(argc != 4){
        printf("Formato: \n\t %s <Arquivo.csv> <Tamanho do Filtro> <Quantização>\n",argv[0]);
        exit(1);
    }
    d = opendir("/home/nayra/Projects/trabalho-final/TrabalhoFinal-C/oncotex_pgm");
    FILE *file = fopen(argv[1], "w");
    fclose(file);
    if(!file) exit(2);
    if (d){
        
        clock_t begin, end;
	    double time_per_img, time_total=0;
        begin = clock();

        while ((dir = readdir(d)) != NULL){
            if(cont>1){
                
                printf("\n");
                printf("%s\n", dir->d_name);
                readPGMImage(&img, dir->d_name);
                gerarMatrizBorrada(&img, atoi(argv[2]));
                quantizacao(&img, atoi(argv[3]));
                quantizacao1(&img, atoi(argv[3]));
                // gerarScm(&img, atoi(argv[3]));
                // // criarArquivo(&img, atoi(argv[3]), argv[1]);
                
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