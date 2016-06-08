#ifndef H_ARQUIVO
#define H_ARQUIVO
    #include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "lista.h"
	#include "grafo.h"

	typedef enum{
		MAN_OK,
		MAN_ERR,
	}man_ret;

    t_grafo* leitura_arquivo(char *arq); //cria um grafo a partir dos dados de um arquivo
    man_ret escrita_arquivo(t_grafo* g, char *arq); //escreve o grafo no arquivo passado por entrada
    man_ret insereTarefa(t_grafo *g, char tarefa[]);
	man_ret retiraTarefa(t_grafo *g, int ID);
	man_ret editaTarefa(t_grafo *g, int IDMod, char tarefaNova[]);

#endif
