#include "grafo.h"

//-------------------------------------------------------------
//Funções pertencenttes apenas ao .c (Apenas declarações)     |
//-------------------------------------------------------------
void limpaVertices(t_grafo* g);   //TODO
t_vertix* buscaVertice(t_vertix* v, int ID);
t_vertix* buscaVerticeMinimo(t_grafo* g);
void Relax(t_grafo* g, t_vertix* u, t_vertix* v);
int peso(t_grafo *g, int IDOrigem, int IDDestino);
grafo_ret Dijkstra(t_grafo* g, int IDInicial);


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
	retiraOrigem(g, ID);
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
		if(AUX->prox != NULL)
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

//busca o vertice com determinado ID, funcao privada a esse modulo
t_vertix* buscaVertice(t_vertix* v, int ID){
	if(v == NULL){
		return NULL;
	}
	t_vertix* AUX;
	for(AUX = v ; AUX != NULL; AUX = AUX->prox){
		if(AUX->propriedades.ID == ID){
			return AUX;
		}
	}
	return AUX;
}

//busca o vertice com determinado ID 
t_vertix* buscaVertice(t_grafo *g, int ID){
	return buscaVertice(g->vertices, ID);
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
		printf("Origens: ");
		imprimeLista(g->origens);
		printf("\n");
}

//--------------------------------
//Funcoes para utilizar Djikstra |
//--------------------------------

grafo_ret Dijkstra(t_grafo* g, int IDInicial){
	if(g == NULL){
		return GRAFO_ERR;
	}

	t_vertix* AUX, *inicial;
	t_item interesse;
	for(AUX = g->vertices ; AUX != NULL; AUX = AUX->prox){
		AUX->caminho = (int)INFINITY;
		AUX->pai = NULL;
		AUX->cor = G_BRANCO;
	}
	inicial = buscaVertice(g->vertices, IDInicial);
	inicial->caminho = 0;

	//enquanto ainda existir vertices brancos e pega o menor
	while((AUX = buscaVerticeMinimo(g)) !=  NULL){
		//para cada adjacente a esse vertice
		for(int i = 0; i < tamanhoLista(AUX->adjacentes) ; i++){
			interesse = buscaListaInd(AUX->adjacentes, i);
			Relax(g, AUX, buscaVertice(g->vertices, interesse.ID));
		}
	}

	return GRAFO_OK;
}

t_vertix* buscaVerticeMinimo(t_grafo* g){
	t_vertix* AUX, *MIN = NULL;
	int min = (int)INFINITY;
	for(AUX = g->vertices ; AUX != NULL; AUX = AUX->prox){
		if(AUX->cor == G_BRANCO){
			if(AUX->caminho < min){
				min = AUX->caminho;
				MIN = AUX;
			}
		}
	}
	if(MIN != NULL){
		MIN->cor = G_PRETO; 
	}

	return MIN;
}
void Relax(t_grafo* g, t_vertix* u, t_vertix* v){
	if(v->caminho > u->caminho + peso(g, u->propriedades.ID, v->propriedades.ID)){
		v->caminho = u->caminho + peso(g, u->propriedades.ID, v->propriedades.ID);
		v->pai = u;
	}
}

int peso(t_grafo *g, int IDOrigem, int IDDestino){
	t_vertix* AUX;
	t_item interesse;
	AUX = buscaVertice(g->vertices, IDOrigem);
	for(int i = 0; i < tamanhoLista(AUX->adjacentes) ; i++){
		interesse = buscaListaInd(AUX->adjacentes, i);
		if(interesse.ID == IDDestino){
			return interesse.peso;
		}
	}

	return -1;	
}

int menorCaminho(t_grafo *g, int IDOrigem, int IDDestino){
	//assertivas de entrada
	if(g == NULL){
		return -1;
	}
	else if(buscaVertice(g->vertices, IDOrigem) == NULL){
		return -1;
	}
	else if(buscaVertice(g->vertices, IDDestino) == NULL){
		return -1;
	}

	Dijkstra(g, IDOrigem);
	t_vertix* destino = buscaVertice(g->vertices, IDDestino);

	//assetivas de saida
	//tenta formar um caminho até o vertice de origem
	//verifica se existe um caminho ate a origem
	t_vertix* AUX = destino;
	while(AUX != NULL && AUX->propriedades.ID != IDOrigem){
		AUX = AUX->pai;
	}
	if(AUX == NULL){
		return -1;
	}

	return(destino->caminho);
}

TipoLista* getOrigens(t_grafo *g){
	return g->origens;
}

t_vertix* getVertices(t_grafo* g){
	return g->vertices;
}