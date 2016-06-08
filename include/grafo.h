#ifndef H_GRAFO
#define H_GRAFO
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <math.h>
	#include "lista.h"

	//----------------------------------------
	//Estruturas do grafo                    |
	//----------------------------------------
	
	// propriedades do vertice
	typedef struct t_prop{
		char nome[101];      //nome da tarefa
		int ID;              //identificador da tarefa
		bool esta_concluida;
		int inicio;          //tempo de comeco da tarefa
		int duracao;         //tempo de duracao da tarefa
	}t_prop;	

	//Lista de adjacencia
	typedef struct t_vertix{
		TipoLista* adjacentes;
		t_vertix *prox, *anter;
		t_vertix *pai;       //vetice de onde veio para funções de busca, ou Djikstra
		t_prop propriedades;
		int cor;
		int caminho;         //peso total para chegar ao vertice
	}t_vertix;

	typedef struct Grafo_P t_grafo;

	typedef enum{
		GRAFO_OK,
		GRAFO_ERR,
		G_BRANCO,
		G_CINZA,
		G_PRETO,
	} grafo_ret;

	t_grafo* criaGrafo();                                   // Cria um grafo Vazio
	grafo_ret limpaGrafo(t_grafo* g);                        
	grafo_ret insereVertice(t_grafo* g, t_prop v);            // Insere um vertice no grafo com as determinadas propriedades
	grafo_ret retiraVertice(t_grafo* g, int ID);            // Retira um vertice do grafo
	t_vertix* buscaVertice(t_grafo *g, int ID);
	grafo_ret insereOrigem(t_grafo* g, int ID);             // Insere um vertice origem no grafo
	grafo_ret retiraOrigem(t_grafo* g, int ID);             // Retira um vertice origem no grafo
 	void imprimeGrafo(t_grafo* g);                          // Imprime o grafo na tela
	//grafo_ret imprimeGrafoArq(t_grafo* g, char *nomeArq);   // Gera um arquivo de saida como especificado com o grafo

	grafo_ret insereAresta(t_grafo* g, int IDOrigem, int IDDestino, int peso);   // Insere uma aresta
	grafo_ret retiraAresta(t_grafo* g, int IDOrigem, int IDDestino);            // Retira a aresta desejada
	int menorCaminho(t_grafo *g, int IDOrigem, int IDDestino);

	TipoLista* getOrigens(t_grafo *g);
	t_vertix* getVertices(t_grafo* g);

#endif