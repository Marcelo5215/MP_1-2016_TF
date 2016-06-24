#include "lista.h"

//----------------------------------------
//Estruturas da Lista                    |
//----------------------------------------

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

//----------------------------------------
//FUNCOES PARA A UTILIZACAO DA LISTA     |
//----------------------------------------

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

///Insere um elemento a lista, levando em consideração uma célula cabeça.
///@param X = item a ser inserido 
///@param lista = ponteiro pra lista a ser inserido o item
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

///Retira um elemento da lista a partir de um ponteiro indicando o elemento a ser retirado
///@param AUX = ponteiro da celula a ser retirada
///@param lista = ponteiro pra lista de onde a celula sera retirada
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

///Informa se a determinada lista esta vazia ou não
///@param lista = ponteiro pra lista a ser analisada
int estaVazia(TipoLista *lista){ 
	return (lista->inicio == lista->final);
}
///Procura na lista o item desejado(X) e retorna um ponteiro para a Celula que contém ele
///@param ID = numero de identificacao do item a ser buscado 
///@param lista = ponteiro pra lista onde o item sera buscado
Celula* buscaLista(TipoLista* lista, int ID){
	Celula *AUX;
	for(AUX = lista->inicio->prox; AUX != NULL ; AUX = AUX->prox){
		if(AUX->item.ID == ID){
			return AUX;
		}
	}
	return NULL;
}

///Limpa as celula cabeça que restará após a execução do programa, e pode ser usada pra limpar uma lista inteira
///@param lista - Ponteiro pra lista a ser limpada
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

///Retorna a quantidade de elementos na lista
///@param lista - Ponteiro pra lista a ser analisada
int tamanhoLista(TipoLista* lista){
	int tam = 0;
	Celula *AUX;
	for(AUX = lista->inicio->prox; AUX != NULL ; AUX = AUX->prox){
		tam++;
	}
	return tam;
}

///Imprime elemento a elemento da lista no terminal
//@param lista - Ponteiro pra lista a ser impressa
void imprimeLista(TipoLista* lista){
	Celula *AUX;
	for(AUX = lista->inicio->prox; AUX != NULL ; AUX = AUX->prox){
		printf(" %d ", AUX->item.ID);
	}
}

///Imprime elemento a elemento da lista em um arquivo
///@param lista - Ponteiro pra lista a ser impressa
///@param fp - Ponteiro para o arquivo onde a lista sera impressa
void imprimeLista_arq(TipoLista* lista, FILE *fp){
	Celula *AUX;
	for(AUX = lista->inicio->prox; AUX != NULL ; AUX = AUX->prox){
		fprintf(fp," %d", AUX->item.ID);
	}
}

///Busca elemento pela posicao na lista
///@param lista -Ponteiro pra lista onde o elemento sera buscado
///@param ind -Posicao do elemento
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

///Retorna indice de um elemento fornecido na lista
///@param lista -Ponteiro pra lista onde o elemento sera buscado
///@param ID - ID do item a ser buscado na lista
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