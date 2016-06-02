#include "grafo.h"

//----------------------------------------
//Estruturas do grafo                    |
//----------------------------------------

//Lista de adjacencia
typedef struct vertix_P t_vertix;
struct vertix_P{
	TipoLista* adjacentes;
	t_vertix *prox;
	t_vertix *pai;       //vetice de onde veio
	char nome[100];      //nome da tarefa
	int ID;              //identificador da tarefa
	bool esta_concluida; 
	int inicio;          //tempo de comeco da tarefa
	int duracao;         //tempo de duracao da tarefa
	int cor;   
	int caminho;         //peso total para chegar ao vertice
};

//Cabeca do Grafo
struct Grafo_P{
	TipoLista* origens;
	t_vertix*  vertices; //vertice inicial
	int tempo_atual;
};
