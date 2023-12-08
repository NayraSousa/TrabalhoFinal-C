#include <dirent.h>
#include <time.h>
#include "funcoesArquivo.h"
 
int main(void)
{
    DIR *d;
    struct dirent *dir;
    struct pgm img;
    char *inicial;
    d = opendir("/home/nayra/Projects/trabalho-final/TrabalhoFinal-C/oncotex_pgm");

    if (d){
        clock_t begin, end;
	    double time_per_img, time_total=0;
        begin = clock();
        //move o cursor
        
        while ((dir = readdir(d)) != NULL)
        {
            if(strcmp(dir->d_name, ".") == 0 | strcmp(dir->d_name, "..")== 0){
                continue;
            }
                printf("%s\n", dir->d_name);
                readPGMImage(&img, dir->d_name);
                viewPGMImage(&img);
			// 			// Saída.
        
        }
        closedir(d);
        end = clock();

	    time_total = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("Tempo Total: %lf\n",time_total);
    }

	return 0;
}		