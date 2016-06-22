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

    t_grafo* leitura_arquivo(char *arq); ///Cria um grafo a partir dos dados de um arquivo
    man_ret escrita_arquivo(t_grafo* g, char *arq); ///Escreve o grafo no arquivo passado por entrada
    man_ret insereTarefa(t_grafo *g, char tarefa[]);
	man_ret retiraTarefa(t_grafo *g, int ID);
	man_ret editaTarefa(t_grafo *g, int IDMod, char tarefaNova[]);
	man_ret startMan();
	man_ret manager(t_grafo *g, int tempo, TipoLista *l_atual, TipoLista *l_concluidas);
	//(NOVO)
	char* getTarefa(t_vertix *v);
	int verificaAntecessores(t_grafo *g, t_vertix *v); /// Verifica se todos os antecessores ja foram concluidos
	int get_maior_peso(t_grafo *g, TipoLista *lista_concluida, int ID_busca); ///Retorna o maior peso (tempo de termino) dos antecessores


#endif
