#include <dirent.h>
#include <time.h>
#include "funcoesArquivo.h"
#include "funcoesImagens.h"
 
int main()
{
    DIR *d;
    struct dirent *dir;
    struct pgm img;
    int cont = 0;
    d = opendir("/home/nayra/Projects/trabalho-final/TrabalhoFinal-C/pgm");
    if (d){
        
        clock_t begin, end;
	    double time_per_img, time_total=0;
        begin = clock();

        while ((dir = readdir(d)) != NULL){
            if(cont>0){
                printf("%s\n", dir->d_name);
                readPGMImage(&img, dir->d_name);
                gerarMatrizBorrada(&img, 7);
                writePGMImage(&img, "img7x7.pgm");
        
                
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