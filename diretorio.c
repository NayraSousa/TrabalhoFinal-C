/*********************************************************/
/* Alunos: Julia Abreu, Leticia Saraiva e Nayra de Sousa */
/* Avaliação 04: Trabalho Final                          */
/* 04.505.23 − 2023.2 − Prof. Daniel Ferreira            */
/*********************************************************/

#include <dirent.h>
#include <time.h>
#include "funcoesArquivo.h"
#include "funcoesImagens.h"
 
int main(int argc, char *argv[]){

    DIR *d;
    struct dirent *dir;
    struct pgm img;
    int cont = 0;

    d = opendir("/home/nayra/Projects/trabalho-final/TrabalhoFinal-C/oncotex_pgm");

    if(argc != 5){
        printf("Formato: \n\t %s <Arquivo.csv> <Relatorio.txt> <Tamanho do Filtro> <Quantização>\n",argv[0]);
        exit(1);
    }

    FILE *file = fopen(argv[1], "w");
    FILE *arquivo = fopen(argv[2], "w");
    for(int i = 0; i<=(atoi(argv[4])*atoi(argv[4])); i++){
        fprintf(file, "%i", i);
        fputs(",", file);
    }
    
    fclose(file);
    fclose(arquivo);

    if(!file) exit(2);
    if(!arquivo) exit(3);

    if (d){
        //começa a contar o tempo
        clock_t begin, end;
	    double time_per_img, time_total=0;
        begin = clock();
        //ler todas as imagens que está no diretório
        while ((dir = readdir(d)) != NULL){
            //pula o "." e ".."
            if(cont>1){
                
                printf("\n");
                printf("%s\n", dir->d_name);
                readPGMImage(&img, dir->d_name);
                //escreve no relatório a ordem de processamento
                FILE *arquivo = fopen(argv[2], "a");
                fputs(dir->d_name, arquivo);
                fputs("\n", arquivo);

                unsigned int *pDataBorrado = (unsigned int*) malloc(img.r*img.c*sizeof(unsigned int));
                unsigned int *pDataOrigQuantizado = (unsigned int*) malloc(img.r*img.c*sizeof(unsigned int));
                unsigned int *pDataBorradoQuantizado = (unsigned int*) malloc(img.r*img.c*sizeof(unsigned int));
                unsigned int *vetorSCM = (unsigned int*) malloc(atoi(argv[4])*atoi(argv[4])*sizeof(unsigned int));

                gerarMatrizBorrada(&img, atoi(argv[3]), pDataBorrado);
                quantizacao(&img, atoi(argv[4]), pDataOrigQuantizado, pDataBorrado, pDataBorradoQuantizado);
                gerarScm(&img, atoi(argv[4]), pDataOrigQuantizado, pDataBorradoQuantizado, vetorSCM);
                criarArquivo(&img, atoi(argv[4]), argv[1], vetorSCM);
                //adiciona no final "epithelium" ou "stroma"
                if(dir->d_name[0] == '0'){
                    fprintf(file, "epithelium");
                }
                if(dir->d_name[0] == '1'){
                    fprintf(file, "stroma");
                }

                fclose(file);
                fclose(arquivo);

            }
            cont++;
        }
        closedir(d);
        end = clock();
        //para de contar o tempo
	    time_total = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("Tempo Total: %lf\n",time_total);
    }

	return 0;
}		