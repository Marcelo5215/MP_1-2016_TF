#include "grafo.h"

//-------------------------------------------------------------
//Funções pertencenttes apenas ao .c (Apenas declarações)     |
//-------------------------------------------------------------
void limpaVertices(t_grafo* g);   //TODO
t_vertix* buscaVertice(t_vertix* v, int ID);
grafo_ret retiraAresta(t_grafo* g, int IDOrigem, int IDDestino);

//----------------------------------------
//Estruturas do grafo                    |
//----------------------------------------

//Cabeca do Grafo
struct Grafo_P{
	TipoLista* origens;
	t_vertix*  vertices; //vertice inicial
	int tempo_atual;
};

//----------------------------------------
//Funcoes para a Utilizacao do Grafo     |
//----------------------------------------

//cria um grafo
t_grafo* criaGrafo(){
	t_grafo* graph = (t_grafo*)malloc(sizeof(t_grafo));
	graph->vertices = NULL;
	graph->origens = criaLista();
	return graph;
}

//desaloca o grafo
grafo_ret limpaGrafo(t_grafo* g){
	//assertiva de entrada
	if(g == NULL){
		return GRAFO_ERR;
	}
	limpaLista(g->origens);
	limpaVertices(g);
	free(g);
	return GRAFO_OK;
}

//insere uma origem
grafo_ret insereOrigem(t_grafo* g, int ID){
	if(g == NULL){
		return GRAFO_ERR;
	}
	//verifica se o elemento ja e uma origem 
	else if(buscaLista(g->origens, ID) != NULL){
		return GRAFO_ERR;
	}
	//verifica se o elemento e um vertice
	else if(buscaVertice(g->vertices, ID) == NULL){
		return GRAFO_ERR;
	}
	else{
		t_item novo;
		novo.ID = ID;
		novo.peso = 0;
		//se existir insere-o como origem, assertiva de saida
		if(insereLista(g->origens, novo) != LISTA_OK){
			return GRAFO_ERR;
		}
	}
	return GRAFO_OK;
}

//retira a origem desejada do grafo
grafo_ret retiraOrigem(t_grafo* g, int ID){
	//assertivas de entrada
	if(g == NULL || estaVazia(g->origens)){
		return GRAFO_ERR;
	}
	//verifica se o elemento existe
	else if(buscaLista(g->origens, ID) == NULL){
		return GRAFO_ERR;
	}
	//retira o elemento requisitado da lista de origens
	retiraLista(g->origens, buscaLista(g->origens, ID));

	//assertivas de saída
	if(buscaLista(g->origens, ID) != NULL){
		return GRAFO_ERR;
	}

	return GRAFO_OK;
}

t_vertix* criaVertice(t_grafo* g, t_prop v){
	t_vertix* vert = (t_vertix*)malloc(sizeof(t_vertix));
	if(vert == NULL){
		printf("Erro no malloc(criaVertice)\n");
		return NULL;
	}
	vert->adjacentes = criaLista();
	vert->prox = NULL;
	vert->propriedades = v;
	vert->anter = NULL;

	return vert;
}

grafo_ret insereVertice(t_grafo* g, t_prop v){
	//assertivas de entrada
	if(g == NULL){
		return GRAFO_ERR;
	}
	else if(g->vertices == NULL){
		g->vertices = criaVertice(g, v);
		//assertuva de saida
		if(g->vertices == NULL){
			return GRAFO_ERR;
		}
		return GRAFO_OK;
	}
	//verifica de já existe o vertice
	else if(buscaVertice(g->vertices, v.ID) != NULL){
		return GRAFO_ERR;
	}
	else{
		t_vertix* AUX;
		//procura o final da lista 
		for(AUX = g->vertices ; AUX->prox != NULL; AUX = AUX->prox){}

		//aloca o proximo vertice
		AUX->prox = (t_vertix*)malloc(sizeof(t_vertix));
		AUX->prox->propriedades = v;
		AUX->prox->adjacentes = criaLista();
		AUX->prox->prox = NULL;
		AUX->prox->anter = AUX;

		return GRAFO_OK;
	}
}

grafo_ret retiraVertice(t_grafo* g, int ID){
	//assertivas de entrada
	if(g == NULL){
		return GRAFO_ERR;
	}
	//verifica se existe o vertice
	else if(buscaVertice(g->vertices, ID) == NULL){
		return GRAFO_ERR;
	}

	t_vertix* AUX;
	//remove todas as aresta com ele
	for(AUX = g->vertices ; AUX != NULL; AUX = AUX->prox){
		retiraAresta(g, AUX->propriedades.ID, ID);
	}

	//AUX e o vertice a ser retirado e AUXAnter o vertice antes dele
	t_vertix* AUXAnter;
	AUX = buscaVertice(g->vertices, ID);
	//busca o vertice anterior
	AUXAnter = AUX->anter;

	//se AUX for o ultimo
	if(AUX == NULL){
		return GRAFO_OK;
	}
	//retira o elemento da lista
	if(AUXAnter != NULL){
		AUXAnter->prox = AUX->prox;
		AUX->prox->anter = AUXAnter;
	}
	else{
		g->vertices = AUX->prox;
	}

	limpaLista(AUX->adjacentes);
	free(AUX);
	//assertiva de saida
	if(buscaVertice(g->vertices, ID) != NULL){
		return GRAFO_ERR;
	}

	return GRAFO_OK;
}

//busca o vertice com determinado ID
t_vertix* buscaVertice(t_vertix* v, int ID){
	t_vertix* AUX;
	for(AUX = v ; AUX != NULL; AUX = AUX->prox){
		if(AUX->propriedades.ID == ID){
			return AUX;
		}
	}
	return AUX;
}

grafo_ret insereAresta(t_grafo *g, int IDOrigem, int IDDestino, int peso){
	//assertivas de entrada
	if(g == NULL){
		return GRAFO_ERR;
	}
	else if(buscaVertice(g->vertices, IDOrigem) == NULL){
		return GRAFO_ERR;
	}
	else if(buscaVertice(g->vertices, IDDestino) == NULL){
		return GRAFO_ERR;
	}
	else if(peso < 0){
		return GRAFO_ERR;
	}
	t_vertix* origem;   
	t_item X;        //item a ser inserido
	X.ID = IDDestino;
	X.peso = peso;
	//vertice de origem
	origem = buscaVertice(g->vertices, IDOrigem);

	//verifica se o elemento já está como adjacente a ele
	if(buscaLista(origem->adjacentes, IDDestino) != NULL){
		return GRAFO_ERR;
	}
	else{
		insereLista(origem->adjacentes, X);
		//assertiva de saida, verifica que o elemento foi inserido
		if(buscaLista(origem->adjacentes, X.ID) != NULL){
			return GRAFO_OK;
		}
		return GRAFO_ERR;
	}
}

grafo_ret retiraAresta(t_grafo* g, int IDOrigem, int IDDestino){
	//assertivas de entrada
	if(g == NULL){
		return GRAFO_ERR;
	}
	else if(buscaVertice(g->vertices, IDOrigem) == NULL){
		return GRAFO_ERR;
	}
	else if(buscaVertice(g->vertices, IDDestino) == NULL){
		return GRAFO_ERR;
	}

	t_vertix* origem;
	//encontra o vertice de origem
	origem = buscaVertice(g->vertices, IDOrigem);
	
	//retira da lista de adjacencia a celula com IDDESTINO
	retiraLista(origem->adjacentes, buscaLista(origem->adjacentes, IDDestino));
	//verifica se a aresta foi removida
	if(buscaLista(origem->adjacentes, IDDestino) != NULL){
		return GRAFO_ERR;
	}
	return GRAFO_OK;
}

void limpaVertices(t_grafo* g){
	t_vertix* AUX = NULL;
	t_vertix* AUXa;
	for(AUXa = g->vertices ; AUXa != NULL ; AUXa = AUXa->prox){
		if(AUX != NULL){
			free(AUX);
		}
		limpaLista(AUXa->adjacentes);
		AUX = AUXa;
	}
	//na ultima iteracao o penultimo elemento AUX nao foi desalocado pois o looping sera terminado antes disso
	free(AUX);
}

void imprimeGrafo(t_grafo* g){
	t_vertix* AUX;
	for(AUX = g->vertices ; AUX != NULL; AUX = AUX->prox){
		printf("%d  -> ", AUX->propriedades.ID);
		imprimeLista(AUX->adjacentes);
		printf("\n");
	}
}