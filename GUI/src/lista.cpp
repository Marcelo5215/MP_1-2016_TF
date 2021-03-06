#include "lista.h"

//----------------------------------------
//Estruturas da Lista                    |
//----------------------------------------

struct Celula_P{
	Celula* anter;
	t_item item;
	Celula* prox;
};

struct TipoLista_P{
	Celula* inicio, *final;
};

//----------------------------------------
//FUNCOES PARA A UTILIZACAO DA LISTA     |
//----------------------------------------

//Cria uma lista duplamente encadeada vazia
TipoLista* criaLista(){
	TipoLista *lista = (TipoLista*)malloc(sizeof(TipoLista));
	lista->inicio =(Celula*)malloc(sizeof(Celula));
	lista->final = lista->inicio;
	lista->final->prox = NULL;
	lista->final->anter = NULL;  

	return lista; 
}

//insere um elemento a lista, levando em consideração uma célula cabeça.
lista_ret insereLista(TipoLista *lista, t_item X){
	if(lista == NULL){
		return LISTA_ERR;
	}
	lista->final->prox = (Celula*)malloc(sizeof(Celula));
	lista->final->prox->anter = lista->final;
	lista->final = lista->final->prox;
	lista->final->item = X;
	lista->final->prox = NULL; 
	return LISTA_OK;
}

//retira um elemento da lista a partir de um ponteiro indicando o elemento a ser retirado
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

//informa se a determinada lista esta vazia ou não
int estaVazia(TipoLista *lista){ 
	return (lista->inicio == lista->final);
}
//procura na lista o elemento desejado(X) e retorna um ponteiro para a Celula que contém ele
Celula* buscaLista(TipoLista* lista, int ID){
	Celula *AUX;
	for(AUX = lista->inicio->prox; AUX != NULL ; AUX = AUX->prox){
		if(AUX->item.ID == ID){
			return AUX;
		}
	}
	return NULL;
}

// limpa as celula cabeça que restará após a execução do programa, e pode ser usada pra limpa uma lista inteira
lista_ret limpaLista(TipoLista *lista){
	if(lista == NULL){
		return LISTA_ERR;
	}
	Celula* AUX;
	for(AUX=lista->inicio->prox ; AUX!=NULL ; AUX=AUX->prox){
		free(AUX->anter);
	}
	free(lista->final);
	free(lista);
	return LISTA_OK;
}

int tamanhoLista(TipoLista* lista){
	int tam = 0;
	Celula *AUX;
	for(AUX = lista->inicio->prox; AUX != NULL ; AUX = AUX->prox){
		tam++;
	}
	return tam;
}

void imprimeLista(TipoLista* lista){
	Celula *AUX;
	for(AUX = lista->inicio->prox; AUX != NULL ; AUX = AUX->prox){
		printf(" %d ", AUX->item.ID);
	}
}

void imprimeLista_arq(TipoLista* lista, FILE *fp){
	Celula *AUX;
	for(AUX = lista->inicio->prox; AUX != NULL ; AUX = AUX->prox){
		fprintf(fp," %d", AUX->item.ID);
	}
}


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