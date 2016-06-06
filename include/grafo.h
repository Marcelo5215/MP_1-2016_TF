#ifndef H_GRAFO
#define H_GRAFO
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "lista.h"

	typedef  struct t_item{
		int ID, peso;    //peso e o peso da aresta
	                     //Identificador de tarefas ID
	}t_item;

	typedef struct t_prop{
		char nome[100];      //nome da tarefa
		int ID;              //identificador da tarefa
		bool esta_concluida; 
		int inicio;          //tempo de comeco da tarefa
		int duracao;         //tempo de duracao da tarefa
	}t_prop;

	//Lista de adjacencia
	typedef struct vertix_P{
		TipoLista* adjacentes;
		t_vertix *prox;
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
	grafo_ret insereVertice(t_grafo* g, t_prop v);            // Insere um vertice no grafo
	grafo_ret retiraVertice(t_grafo* g, int ID);            // Retira um vertice do grafo
	grafo_ret insereOrigem(t_grafo* g, int ID);             // Insere um vertice origem no grafo
	grafo_ret retiraOrigem(t_grafo* g, int ID);             // Retira um vertice origem no grafo
 	//void imprimeGrafo(t_grafo* g);                          // Imprime o grafo na tela
	//grafo_ret imprimeGrafoArq(t_grafo* g, char *nomeArq);   // Gera um arquivo de saida como especificado com o grafo

	grafo_ret insereAresta(t_grafo* g, char origem[],char destino[],float peso);   // Insere uma aresta
	grafo_ret retiraAresta(t_grafo* g, char origem[],char destino[]);            // Retira a aresta desejada

#endif