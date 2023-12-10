Projeto final da cadeira de Laboratório de Programação.

O qual precisava pegar imagens de exames no formato .pgm, lê-las, borrá-las com filtros 3x3, 5x5, 7x7, quantizá-las com os níveis 8 e 16, aplicar as matrizes quantizadas em uma matriz SCM e posteriormente gerar um arquivo .csv com o resultado da matriz SCM para poder passá-lo pela ferramente Weka, onde irá calcular a precisão dos resultados e o recall.

Para rodar o programa corretamente, precisa passar por linha de comando o nome do arquivo .csv(onde será salvo os dados), o nome do arquivo .txt(onde será salvo a ordem de processamento das imagens), o tamanho do filtro e o nível de quantização.

Para ler o diretório, precisa passar o caminho dele no arquivo diretorio.c e no arquivo funcoesArquivo.c precisa passar esse caminho e adicionar "/" no final na variável diretorio.