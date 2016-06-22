#include "grafo.h"

///-------------------------------------------------------------
///Funções pertencenttes apenas ao .c (Apenas declarações)     |
///-------------------------------------------------------------
void limpaVertices(t_grafo* g);   //TODO
t_vertix* buscaVertice(t_vertix* v, int ID);
t_vertix* buscaVerticeMinimo(t_grafo* g);
void Relax(t_grafo* g, t_vertix* u, t_vertix* v);
int peso(t_grafo *g, int IDOrigem, int IDDestino);
grafo_ret Dijkstra(t_grafo* g, int IDInicial);

//Cabeca do Grafo
struct Grafo_P{
	TipoLista* origens;
	t_vertix*  vertices; //vertice inicial
	int tempo_atual;
};

///----------------------------------------
///Funcoes para a Utilizacao do Grafo     |
///----------------------------------------

///Criacao de um grafo vazio
t_grafo* criaGrafo(){
	t_grafo* graph = (t_grafo*)malloc(sizeof(t_grafo));
	graph->vertices = NULL;
	graph->origens = criaLista();
	return graph;
}

///Funcao que desaloca os componentes do grafo dado.
/// pGrafo g - 
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

///Essa funcao insere na origem de um grafo um vertice (ja existente)
///t_grafo *g - Grafo no qual sera inserido o elemento; Deve ser diferente de NULL
///int ID - Item que será inserido no grafo;
//		   Deve ser existente no conjunto de vertices e não existente no conjunto de origens.
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

///Essa funcao retira um elemento do conjunto de origens de um grafo
///t_grafo *g - Grafo do qual sera retirado o elemento das origens; Deve ser diferente de NULL.
///int ID - Item que será retirado do conjunto de origens do grafo;
//		   Deve existir no conjunto de origens do grafo.
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

///Essa funcao cria um vertice com as propriedades passadas pelo programador.
///t_grafo *g - Grafo no qual sera criado o vertice; Deve ser diferente de NULL.
///t_prop v - Propriedades que serao inseridas no vertice criado.
t_vertix* criaVertice(t_grafo* g, t_prop v){
	t_vertix* vert = (t_vertix*)malloc(sizeof(t_vertix));
	if(vert == NULL){
		printf("Erro no malloc(criaVertice)\n");
		return NULL;
	}
	vert->adjacentes = criaLista();
	vert->antecessores = criaLista();
	vert->prox = NULL;
	vert->propriedades = v;
	vert->anter = NULL;

	return vert;
}

///Essa funcao insere um vertice com as propriedades passadas pelo programador no grafo
///t_grafo *g - Grafo no qual sera inserido o vertice; Deve ser diferente de NULL.
///t_prop v - Propriedades que serao inseridas no novo vertice do grafo.
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
		AUX->prox->antecessores = criaLista();
		AUX->prox->prox = NULL;
		AUX->prox->anter = AUX;

		return GRAFO_OK;
	}
}

///Essa funcao retira um vertice do grafo com o ID igual ao passado.
///t_grafo *g - Grafo do qual será retirado o vertice; Deve ser diferente de NULL.
///int ID - ID do vertice a ser retirado, que será utlizado para buscá-lo no grafo. Caso nao haja um vertice com tal ID, retornar-se-a uma condicao de erro.
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
		retiraArestaAnter(g, ID, AUX->propriedades.ID);
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
	limpaLista(AUX->antecessores);
	free(AUX);
	//assertiva de saida
	if(buscaVertice(g->vertices, ID) != NULL){
		return GRAFO_ERR;
	}

	return GRAFO_OK;
}

///Funcao que busca o vertice com determinado ID; E uma funcao restrita a esse modulo
///p_vertix V - Ponteiro para o inicio da busca da lista. Deve ser diferente de NULL;
///int ID - Inteiro com o indice do vertice a ser buscado. Caso nao seja encontrado um vertice com o ID correspondente, retorna-se NULL.
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

///Funcao que busca o vertice com determinado ID; 
///pGrafo g - Grafo no qual sera realizada a busca. Caso seja NULL, retorna NULL; 
///int ID - Inteiro com o indice do vertice a ser buscado. Caso nao seja encontrado um vertice com o ID correspondente, retorna-se NULL.
t_vertix* buscaVertice(t_grafo *g, int ID){
	if(g==NULL){
		return NULL;
	}
	return buscaVertice(g->vertices, ID);
}

///Funcao que insere uma aresta de sucessores no grafo com as caracteristicas passadas por parametro.
///pGrafo g - Grafo no qual sera realizada a insercao. Caso seja NULL, retorna-se erro.
///int IDOrigem - Inteiro com o indice do vertice a ser colocado como origem. 
//			     Caso nao seja encontrado um vertice existente no grafo com o ID correspondente, retorna-se erro.
///int IDDestino - Inteiro com o indice do vertice a ser colocado como origem. 
//				  Caso nao seja encontrado um vertice existente no grafo com o ID correspondente ou o vertice destino
//				  já tenha sido inserido no conjunto de arestas, tambem retorna-se erro.
///int peso - Inteiro com o peso a ser inserido na aresta. Deve ser maior ou igual a 0 (zero).
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

///Funcao que insere uma aresta de antecessores no grafo com as caracteristicas passadas por parametro.
///pGrafo g - Grafo no qual sera realizada a insercao. Caso seja NULL, retorna-se erro.
///int IDOrigem - Inteiro com o indice do vertice a ser colocado como origem. 
//			     Caso nao seja encontrado um vertice existente no grafo com o ID correspondente, retorna-se erro.
///int IDDestino - Inteiro com o indice do vertice a ser colocado como origem. 
//				  Caso nao seja encontrado um vertice existente no grafo com o ID correspondente ou o vertice destino
//				  já tenha sido inserido no conjunto de arestas, tambem retorna-se erro.
///int peso - Inteiro com o peso a ser inserido na aresta. Deve ser maior ou igual a 0 (zero).
grafo_ret insereArestaAnter(t_grafo *g, int IDOrigem, int IDDestino, int peso){
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
	if(buscaLista(origem->antecessores, IDDestino) != NULL){
		return GRAFO_ERR;
	}
	else{
		insereLista(origem->antecessores, X);
		//assertiva de saida, verifica que o elemento foi inserido
		if(buscaLista(origem->antecessores, X.ID) != NULL){
			return GRAFO_OK;
		}
		return GRAFO_ERR;
	}
}

///Funcao que retira uma aresta de sucessores no grafo com as caracteristicas passadas por parametro.
///pGrafo g - Grafo no qual sera realizada a remocao. Caso seja NULL, retorna-se erro.
///int IDOrigem - Inteiro com o indice do vertice origem a ser buscado. 
//				 Caso nao seja encontrado um vertice existente no grafo com o ID correspondente, retorna-se erro.
///int IDDestino - Inteiro com o indice do vertice destino a ser buscado. 
//				  Caso nao seja encontrado um vertice existente no grafo com o ID correspondente, tambem retorna-se erro.
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

///Funcao que retira uma aresta de antecessores no grafo com as caracteristicas passadas por parametro.
///pGrafo g - Grafo no qual sera realizada a remocao. Caso seja NULL, retorna-se erro.
///int IDOrigem - Inteiro com o indice do vertice origem a ser buscado. 
//				 Caso nao seja encontrado um vertice existente no grafo com o ID correspondente, retorna-se erro.
///int IDDestino - Inteiro com o indice do vertice destino a ser buscado. 
//				  Caso nao seja encontrado um vertice existente no grafo com o ID correspondente, tambem retorna-se erro.
grafo_ret retiraArestaAnter(t_grafo* g, int IDOrigem, int IDDestino){
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
	retiraLista(origem->antecessores, buscaLista(origem->antecessores, IDDestino));
	//verifica se a aresta foi removida
	if(buscaLista(origem->antecessores, IDDestino) != NULL){
		return GRAFO_ERR;
	}
	return GRAFO_OK;
}

///Essa funcao realiza a liberacao dos vertices do grafo, a fim de evitar o vazamento de memoria do programa.
/// pGrafo g - grafo que tera os vertices liberados.
void limpaVertices(t_grafo* g){
	t_vertix* AUX = NULL;
	t_vertix* AUXa;
	for(AUXa = g->vertices ; AUXa != NULL ; AUXa = AUXa->prox){
		if(AUX != NULL){
			free(AUX);
		}
		limpaLista(AUXa->adjacentes);
		limpaLista(AUXa->antecessores);
		AUX = AUXa;
	}
	//na ultima iteracao o penultimo elemento AUX nao foi desalocado pois o looping sera terminado antes disso
	free(AUX);
}

///Funcao que imprime os indices dos vertices do grafo, assim como os indices de suas arestas
/// pGrafo - Grafo que tera seus elementos impressos; Caso seja NULL, a funcao termina antes de comecar a busca.

void imprimeGrafo(t_grafo* g){
	if(g==NULL){
		return;
	}
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

///Funcao de encapsulamento para obter as origens do grafo.
/// pGrafo g - Retorna NULL caso seja NULL.
TipoLista* getOrigens(t_grafo *g){
	if(g==NULL){
		return NULL;
	}
	return g->origens;
}
///Funcao de encapsulamento para obter os vertices do grafo.
/// pGrafo g - Retorna NULL caso seja NULL.
t_vertix* getVertices(t_grafo* g){
	if(g==NULL){
		return NULL;
	}
	return g->vertices;
}

///Funcao de encapsulamento para obter o tempo atual do grafo.
/// pGrafo g - Caso seja NULL, retorna o valor -1.
int getTempo(t_grafo *g){
	if(g==NULL){
		return -1;
	}
	return g->tempo_atual;
}

///Funcao que altera o tempo atual do grafo.
/// pGrafo g - Caso seja NULL, retorna o valor de erro.
/// int tempo - Inteiro que sera inserido como o tempo atual do grafo. Caso seja menor que 0, retorna-se erro.
grafo_ret setTempo(t_grafo *g, int tempo){
	if(g == NULL){
		return GRAFO_ERR;
	}
	else if(tempo < 0){
		return GRAFO_ERR;
	}

	g->tempo_atual = tempo;

	return GRAFO_OK;
}

///--------------------------------
///Funcoes para utilizar Djikstra |
///--------------------------------

///Funcao principal do Djikstra, a qual realiza o algoritmo em si
/// pGrafo g - Ponteiro para o grafo no qual sera realizado o algoritmo. Retorna-se erro caso seja NULL.
/// int IDInicial - E um inteiro que contem o ID do vertice no qual o processo sera iniciado.
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

///Essa funcao realiza a visita do vertice de valor do caminho minimo atual no grafo.
/// pGrafo g - Ponteiro para o grafo no qual sera ocorrido essa busca.
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

///Essa funcao compara se o caminho ate um vertice de interesse e menor do que o caminho vertice atual.
/// pGrafo g - Ponteiro para o grafo no qual ocorrera a comparacao
/// pVertix u - Vertice atual que sera comparado
/// pVertix v - Vertice de interesse que sera comparado com o atual
void Relax(t_grafo* g, t_vertix* u, t_vertix* v){
	if(v->caminho > u->caminho + peso(g, u->propriedades.ID, v->propriedades.ID)){
		v->caminho = u->caminho + peso(g, u->propriedades.ID, v->propriedades.ID);
		v->pai = u;
	}
}

///A funcao peso retorna o peso da aresta entre o vertice origem e o vertice destino
///pGrafo g - Ponteiro para o grafo no qual ocorrera a busca
///int IDOrigem - ID do vertice origem da aresta buscada
///int IDDestino - ID do vertice destino da aresta buscada
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

///Essa funcao retorna o menor caminho para chegar ao vertice de destino
///pGrafo g - Ponteiro para o grafo no qual ocorrera a busca. Caso seja NULL, retorna-se -1.
///int IDOrigem - ID do vertice origem da aresta buscada. Caso nao exista no grafo, retorna-se -1.
///int IDDestino - ID do vertice destino da aresta buscada, onde ocorrera a obtencao do caminho. Caso nao exista no grafo, retorna-se -1.
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

///Funcao que utiliza o maior caminho do vertice destino as origens para impressao na interface grafica
/// t_grafo *g - Grafo onde ocorrera o preocesso de busca. Retorna-se erro caso seja NULL.
/// int IDDestino - Inteiro que representa o indice do destino para a impressao do seu caminho. Caso seja
//					uma origem, imprime-se apenas o próprio vertice. Retorna-se erro caso nao pertenca ao
//					grafo.
grafo_ret achaCaminhoMin(t_grafo* g, int IDDestino){
	if(g==NULL){
		return GRAFO_ERR;
	}
	if(buscaVertice(g, IDDestino)==NULL){
		return GRAFO_ERR;
	}
	int IDOrigem = 0, max = 0, IDOrigemMax = 0, caminho = 0;
	t_vertix *v;
	t_item item_aux;

	for(int i = 0; i < tamanhoLista(getOrigens(g)) ; i++){
		IDOrigem = buscaListaInd(getOrigens(g), i).ID;
		max = -2;
        caminho = menorCaminho(g, IDOrigem, IDDestino);
        if(caminho > max && caminho != -1){
			max = caminho;
			IDOrigemMax = IDOrigem;
		}
	}
	
	if (max == -2){ //vertice eh uma origem
		//Imprime o vertice sozinho
	} else{
		menorCaminho(g, IDOrigemMax, IDDestino);
		v = buscaVertice(g, item_aux.ID);
		//imprime a partir de v e caminhando com v->pai
	}
	
	return GRAFO_OK;
}
