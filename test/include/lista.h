/**
* @file lista.h
* @brief Modulo que contem as funcoes que permitem utilizar as funcionalidades de uma lista duplamente encadeada.
*/

#ifndef H_LISTA
#define H_LISTA
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>

	typedef struct Celula_P Celula;
	typedef struct TipoLista_P TipoLista;

	typedef  struct t_item{
		int ID;    ///< Peso e o peso da aresta
	    int peso;  ///< Identificador de tarefas ID
	}t_item;

	typedef enum{
		LISTA_OK,
		LISTA_ERR,
	} lista_ret;

	TipoLista* criaLista();
	lista_ret insereLista(TipoLista *lista, t_item X);
	lista_ret retiraLista(TipoLista *lista, Celula *AUX);
	lista_ret editaCelulaPeso(TipoLista *lista, int ID, int peso);
	int estaVazia(TipoLista *lista);
	lista_ret limpaLista(TipoLista *lista);
	Celula* buscaLista(TipoLista* lista, int ID);
	t_item buscaListaInd(TipoLista* lista, int Ind);
	int tamanhoLista(TipoLista* lista);
	void imprimeLista(TipoLista* lista);
	void imprimeLista_arq(TipoLista* lista, FILE *fp);
	int get_indice(TipoLista *lista, int ID); ///< Calcula o indice do ID na lista

#endif