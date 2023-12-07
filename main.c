#include <stdio.h>
#include "filtro.h"
#include "vetorSCM.h"
#include "pgm.h"
#include "struct.h"

int main(int argc, char *argv[]){

	struct pgm img;
    struct pgm imgBorrada;
    
    //nome entrada, nome saida, tamanho janela, nivel quantização
	if (argc!=4){
		printf("Formato: \n\t %s <imagemEntrada.pgm> <imagemSaida.pgm>\n",argv[0]);
		exit(1);
	}

	readPGMImage(&img,argv[1]);
    gerarMatrizBorrada(&img, &imgBorrada, atoi(argv[3]));
    writePGMImage(&imgBorrada, argv[2]);
    viewPGMImage(&imgBorrada);

	return 0;

}