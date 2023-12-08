#include <dirent.h>
#include <stdio.h>
#include <time.h>
#include "funcoesArquivo.h"
 
int main(void)
{
    DIR *d;
    struct dirent *dir;
    struct pgm img;
    d = opendir("/home/nayra/Downloads/datasets/oncotex_pgm/datasets/oncotex_pgm");

    if (d){
        clock_t begin, end;
	    double time_per_img, time_total=0;
        begin = clock();
        //move o cursor
        for(int i = 0; i<2; i++){
            dir = readdir(d);
        }
        
        while ((dir = readdir(d)) != NULL)
        {
            readPGMImage(&img, dir->d_name);
            viewPGMImage(&img);
						// Saída.
        }
        closedir(d);
        end = clock();

	    time_total = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("Tempo Total: %lf\n",time_total);
    }

	return 0;
}		