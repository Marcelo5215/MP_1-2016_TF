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
    if (arq == NULL) //assertiva para manter a consistencia do grafo a ser criado
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
man_ret escrita_arquivo(t_grafo *g, char *arq){
    //assertivas de entrada
    if(arq == NULL || g == NULL)
        return MAN_ERR;

    FILE *fp = fopen(arq, "w");

    if(fp==NULL ){
        return MAN_ERR;
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
    return MAN_OK;
}

//----------------------------------------
//Funcoes para manipulacao de tarefas    |
//----------------------------------------

man_ret insereTarefa(t_grafo *g, char* tarefa){
    if(g == NULL || tarefa == NULL){
        return MAN_ERR;
    }
    t_prop prop;
    char *campo, string[121];
    strcpy(string, tarefa);
    int i, pre, reqID;

    //separa a tarefa em campos
    //ID da tarefa
    campo = strtok(string, " '");
    if(campo == NULL) return MAN_ERR;
    prop.ID = atoi(campo);
    //nome da tarefa
    campo = strtok(NULL, "'");
    if(campo == NULL) return MAN_ERR;
    strcpy(prop.nome, campo);
    //se esta concluida ou nao
    campo = strtok(NULL, " '");
    if(campo == NULL) return MAN_ERR;
    if(atoi(campo)){
        prop.esta_concluida = true;
    }
    else{
        prop.esta_concluida = false;
    }
    //quando a tarefa inicia
    campo = strtok(NULL, " '");
    if(campo == NULL) return MAN_ERR;
    prop.inicio = atoi(campo);
    //qual sua duracao
    campo = strtok(NULL, " '");
    if(campo == NULL) return MAN_ERR;
    prop.duracao = atoi(campo);


    if(insereVertice(g, prop) != GRAFO_OK){
        return MAN_ERR; 
    }

    // quantos prerequisitos
    campo = strtok(NULL, " '");
    if(campo == NULL) return MAN_ERR;
    pre = atoi(campo);

    for(i = 0 ; i < pre ; i++){
        campo = strtok(NULL, " '");
        reqID = atoi(campo);
        insereAresta(g, prop.ID, reqID, 0);
    }

    return MAN_OK;
}

man_ret retiraTarefa(t_grafo *g, int ID){
    if(retiraVertice(g, ID) != GRAFO_OK){
        return MAN_ERR;
    }

    return MAN_OK;
}

man_ret editaTarefa(t_grafo *g, int IDMod, char tarefaNova[]){
    if(insereTarefa(g, tarefaNova) != MAN_OK){
        return MAN_ERR;
    }
    if(retiraTarefa(g, IDMod) != MAN_OK){
        return MAN_ERR;
    }

    return MAN_OK;
}