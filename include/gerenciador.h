#ifndef H_ARQUIVO
#define H_ARQUIVO
    #include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "lista.h"
	#include "grafo.h"

    t_grafo* leitura_arquivo(char *arq); //cria um grafo a partir dos dados de um arquivo
    grafo_ret escrita_arquivo(t_grafo* g, char *arq); //escreve o grafo no arquivo passado por entrada

#endif
