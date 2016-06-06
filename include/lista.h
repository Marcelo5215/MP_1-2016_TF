#ifndef H_LISTA
#define H_LISTA
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "grafo.h"

	typedef struct Celula;
	typedef struct TipoLista_P TipoLista;

	typedef enum{
		LISTA_OK,
		LISTA_ERR,
	} lista_ret;

	TipoLista* criaLista();
	lista_ret insereLista(TipoLista *lista, t_item X);
	lista_ret retiraLista(TipoLista *lista, Celula *AUX);
	int estaVazia(TipoLista *lista);
	void limpaLista(TipoLista *lista);
	Celula* buscaLista(TipoLista* lista, int ID);

#endif