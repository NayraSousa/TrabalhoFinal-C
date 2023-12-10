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
    int j = 0;
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

                unsigned int *pDataBorrado = (unsigned int*) malloc(img.r*img.c*sizeof(unsigned int));
                unsigned int *pDataOrigQuantizado = (unsigned int*) malloc(img.r*img.c*sizeof(unsigned int));
                unsigned int *pDataBorradoQuantizado = (unsigned int*) malloc(img.r*img.c*sizeof(unsigned int));
                unsigned int *vetorSCM = (unsigned int*) malloc(atoi(argv[3])*atoi(argv[3])*sizeof(unsigned int));

                gerarMatrizBorrada(&img, atoi(argv[2]), pDataBorrado);
                quantizacao(&img, atoi(argv[3]), pDataOrigQuantizado, pDataBorrado, pDataBorradoQuantizado);
                gerarScm(&img, atoi(argv[3]), pDataOrigQuantizado, pDataBorradoQuantizado, vetorSCM);
                criarArquivo(&img, atoi(argv[3]), argv[1], vetorSCM);
                if(dir->d_name[0] == 0){
                    fprintf(file, "epitelio");
                }
                if(dir->d_name[0] == 1){
                    fprintf(file, "stroma");
                }

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