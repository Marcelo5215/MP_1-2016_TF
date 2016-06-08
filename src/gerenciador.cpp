#include "gerenciador.h"

//TODO
    //VER PESO
    //peso sera a duracao do vertice anterior (prerequisito)

//TODO

//----------------------------------------
//Funcoes para manipulacao com arquivos  |
//----------------------------------------

//cria um grafo a partir do arquivo passado
t_grafo* leitura_arquivo(char *arq){
        if (arq==NULL) //assertiva para manter a consistencia do grafo a ser criado
            return NULL;

    FILE* fp = fopen(arq, "r");

        if(fp == NULL){
            printf("Erro na abertura do arquivo!\n");
            return NULL;
        }

        t_grafo* g = criaGrafo(); //cria um grafo vazio
        t_prop prop_lido;

    char nome[101];
    int id = 0, inicio = 0, duracao = 0, lista = 0, lido=0, i =0, requisito;

        while(fscanf(fp, "%d '%[^''']s", &id, nome)>0){ //le primeiro o id, depois a string (ate o char ')
            fgetc(fp); fgetc(fp); //limpa o buffer pra ler o resto dos dados da linha
            fscanf(fp, "%d %d %d %d\n", &lido, &inicio, &duracao, &lista);
                
            //armazena os campos de prop de acordo com o que for lido
            strcpy(prop_lido.nome, nome);
            prop_lido.ID = id;
            prop_lido.inicio = inicio;

            
            prop_lido.duracao = duracao;                
            // armazena se a visitacao do vertice de forma booleana
            if(lido){
                prop_lido.esta_concluida = true;
                }
            else{
                 prop_lido.esta_concluida = false;
                 }                    
                
            insereVertice(g, prop_lido);
            if(inicio == 0){
                insereOrigem(g, id);
            }
            //o laco abaixo le todos os pre requisitos do vertice lido
                for(i=0; i<lista; i++){                    
                    fscanf(fp, " %d", &requisito);
                    insereAresta(g, prop_lido.ID, requisito, 0);
                }
        }


        fclose(fp);
        return g;
    }


//escreve o grafo desejado no arquivo passado por parametro
grafo_ret escrita_arquivo(t_grafo *g, char *arq){
       //assertivas de entrada
       if(arq == NULL || g == NULL)
        return GRAFO_ERR;

       FILE *fp = fopen(arq, "w");

        if(fp==NULL ){
            return GRAFO_ERR;
        }

        int n_req = 0;
        t_vertix* atual;

        //laco que percorre todos os vertices do grafo
        for(atual = g->vertices; atual!=NULL; atual = atual->prox){
            n_req = tamanhoLista(atual->adjacentes);
            fprintf(fp, "%d '%s' %d %d %d %d", atual->propriedades.ID, atual->propriedades.nome,
            atual->propriedades.esta_concluida, atual->propriedades.inicio, atual->propriedades.duracao, n_req);
            //imprime todos os elementos requisitos de dado vertice
            imprimeLista_arq(atual->adjacentes, fp);
            fprintf(fp,"\n");
            
        }


    fclose(fp);
    return GRAFO_OK;
}

