#include "lista.h"

///----------------------------------------
///Estruturas da Lista                    |
///----------------------------------------

///Conteudo da lista
struct Celula_P{
	Celula* anter;
	t_item item;
	Celula* prox;
};

///Cabeca da lista
struct TipoLista_P{
	Celula* inicio, *final;
};

///----------------------------------------
///FUNCOES PARA A UTILIZACAO DA LISTA     |
///----------------------------------------

///Cria uma lista duplamente encadeada vazia
///Nao recebe parametros
TipoLista* criaLista(){
	TipoLista *lista = (TipoLista*)malloc(sizeof(TipoLista));
	lista->inicio =(Celula*)malloc(sizeof(Celula));
	lista->inicio->prox = NULL;
	lista->inicio->anter = NULL;
	lista->final = lista->inicio;
	lista->final->prox = NULL;
	lista->final->anter = NULL;  

	return lista; 
}

///insere um elemento a lista, levando em consideração uma célula cabeça.
///Parametros:
///X = item a ser inserido 
///lista = ponteiro pra lista a ser inserido o item
lista_ret insereLista(TipoLista *lista, t_item X){
	if(lista == NULL){ //assertiva de entrada
		return LISTA_ERR;
	}
	
	lista->final->prox = (Celula*)malloc(sizeof(Celula));
	lista->final->prox->anter = lista->final;
	lista->final = lista->final->prox;
	lista->final->item = X;
	lista->final->prox = NULL; 
	return LISTA_OK;
}

///retira um elemento da lista a partir de um ponteiro indicando o elemento a ser retirado
///Parametros:
///AUX = ponteiro da celula a ser retirada
///lista = ponteiro pra lista de onde a celula sera retirada
lista_ret retiraLista(TipoLista *lista, Celula *AUX){
	if(AUX == NULL || lista == NULL){
		return LISTA_ERR;
	}
	if(lista->inicio == AUX)
		lista->inicio = AUX->prox;
	else
		AUX->anter->prox = AUX->prox;
	if(AUX->prox == NULL)
		lista->final = AUX->anter;
	else
		AUX->prox->anter = AUX->anter;

	free(AUX);
	return LISTA_OK;
}

///informa se a determinada lista esta vazia ou não
///Parametros:
///lista = ponteiro pra lista a ser analisada
int estaVazia(TipoLista *lista){ 
	return (lista->inicio == lista->final);
}
///procura na lista o item desejado(X) e retorna um ponteiro para a Celula que contém ele
///Parametros:
///ID = numero de identificacao do item a ser buscado 
///lista = ponteiro pra lista onde o item sera buscado
Celula* buscaLista(TipoLista* lista, int ID){
	Celula *AUX;
	for(AUX = lista->inicio->prox; AUX != NULL ; AUX = AUX->prox){
		if(AUX->item.ID == ID){
			return AUX;
		}
	}
	return NULL;
}

/// limpa as celula cabeça que restará após a execução do programa, e pode ser usada pra limpar uma lista inteira
///Parametros:
///lista = ponteiro pra lista a ser limpada
lista_ret limpaLista(TipoLista *lista){
	if(lista == NULL){
		return LISTA_ERR;
	}
	Celula* AUX;
	for(AUX=lista->inicio->prox ; AUX!=NULL ; AUX=AUX->prox){
		free(AUX->anter);
	}
	free(AUX);
	free(lista->final);
	free(lista);
	return LISTA_OK;
}

///retorna a quantidade de elementos na lista
///Parametros:
///lista = ponteiro pra lista a ser analisada
int tamanhoLista(TipoLista* lista){
	int tam = 0;
	Celula *AUX;
	for(AUX = lista->inicio->prox; AUX != NULL ; AUX = AUX->prox){
		tam++;
	}
	return tam;
}

///imprime elemento a elemento da lista no terminal
///Parametros:
//lista = ponteiro pra lista a ser impressa
void imprimeLista(TipoLista* lista){
	Celula *AUX;
	for(AUX = lista->inicio->prox; AUX != NULL ; AUX = AUX->prox){
		printf(" %d ", AUX->item.ID);
	}
}

///imprime elemento a elemento da lista em um arquivo
///Parametros:
///lista = ponteiro pra lista a ser impressa
///fp = ponteiro para o arquivo onde a lista sera impressa
void imprimeLista_arq(TipoLista* lista, FILE *fp){
	Celula *AUX;
	for(AUX = lista->inicio->prox; AUX != NULL ; AUX = AUX->prox){
		fprintf(fp," %d", AUX->item.ID);
	}
}

///busca elemento pela posicao na lista
///Parametros:
///lista = ponteiro pra lista onde o elemento sera buscado
///ind = posicao do elemento
t_item buscaListaInd(TipoLista *lista, int ind){
	if(lista == NULL || ind > tamanhoLista(lista)){
		printf("ERRO\n");
	}
	t_item o;
	o.ID = -1;
	Celula* AUX;
	int i = 0;
	for(AUX = lista->inicio->prox; AUX != NULL; AUX = AUX->prox){
		if(i == ind){
			return AUX->item;
		}
		i++;
	}

	return o;
}

///retorna indice de um elemento fornecido na lista
///Parametros:
///lista = ponteiro pra lista onde o elemento sera buscado
///ID = ID do item a ser buscado na lista
int get_indice(TipoLista *lista, int ID){
	int ind_desejado = 0;
	Celula *AUX;
	for(AUX = lista->inicio->prox; AUX != NULL ; AUX = AUX->prox){
		if(AUX->item.ID == ID){
			return ind_desejado;
		}
		else{
		ind_desejado++;
		}
	}
	return -1;
}

///Edita o peso da celula especificada 
///@param lista lista na qual o ID se encontra
///@param ID indentificador da lista
///@param peso peso a ser inserido
lista_ret editaCelulaPeso(TipoLista *lista, int ID, int peso){
	if(lista == NULL || peso < 0){
		return LISTA_ERR;
	}
	Celula *AUX;

	AUX = buscaLista(lista, ID);
	if(AUX == NULL)
		return LISTA_ERR;
	AUX->item.peso = peso;

	return LISTA_OK;
}