#include "gerenciador.h"

//TODO
    //VER PESO
    //peso sera a duracao do vertice anterior (prerequisito)

//TODO

int get_maior_peso(t_grafo *g, TipoLista *lista_concluida, int ID_busca);

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
        if(lista == 0){
            insereOrigem(g, id);
        }
        //o laco abaixo le todos os pre requisitos do vertice lido
            for(i=0; i<lista; i++){                    
                fscanf(fp, " %d", &requisito);
                insereAresta(g, requisito, prop_lido.ID, 0);
                insereArestaAnter(g, prop_lido.ID, requisito, 0);
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
    for(atual = getVertices(g); atual!=NULL; atual = atual->prox){
        n_req = tamanhoLista(atual->antecessores);
        fprintf(fp, "%d '%s' %d %d %d %d", atual->propriedades.ID, atual->propriedades.nome,
        atual->propriedades.esta_concluida, atual->propriedades.inicio, atual->propriedades.duracao, n_req);
        //imprime todos os elementos requisitos de dado vertice
        imprimeLista_arq(atual->antecessores, fp);
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
        insereAresta(g, reqID, prop.ID, 0);
        insereArestaAnter(g, prop.ID, reqID, 0);
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

//----------------------------------------
//Funcoes de interface                   |
//----------------------------------------
//inicia o gerenciador
man_ret startMan(){
    t_grafo *g;
    char nome_arq[31];
    int tempo = 8;
    TipoLista *l_atual, *l_concluidas;
    l_atual = criaLista();
    l_concluidas = criaLista();

    g = leitura_arquivo((char*)"entrada.txt");
    //resetar a propriedade esta_concluida de todos os vertices
    manager(g, tempo, l_atual, l_concluidas);

    return MAN_OK;
}


int verificaAntecessores(t_grafo *g, t_vertix *v){ //retorna true se todos os antecessores foram concluidos e false cc
    int i;
    t_vertix *v_aux;
    t_item item_ante;
    for(i = 0; i < tamanhoLista(v->antecessores); i++){
        item_ante = buscaListaInd(v->antecessores, i);
        v_aux = buscaVertice(g, item_ante.ID);
        if (v_aux->propriedades.esta_concluida == false){
            return false;
        }       
    }
    return true;
}

man_ret manager(t_grafo *g, int tempo, TipoLista *l_atual, TipoLista *l_concluidas){
    if (l_concluidas == NULL || l_atual == NULL || g) return MAN_ERR;

    //TipoLista *l_concluidas, *l_atual; //l_concluidas-> lista de tarefas ja concluidas e l_atual-> lista de tarefas ja iniciadas mas nao concluidas
    t_vertix* v, *v_sucessor;
    t_item item_add, item_suc, item_aux;
    int i,j, true_inicio = 0;
    
    for(i = 0; i < tamanhoLista(getOrigens(g)); i++){ //checagem das origens e insercao na lista de concluidos
        item_aux = buscaListaInd(getOrigens(g), i);
        v = buscaVertice(g, item_aux.ID);
        if(v->propriedades.inicio <= tempo){
            if(v->propriedades.inicio + v->propriedades.duracao <= tempo){
                item_add.ID = v->propriedades.ID;
                item_add.peso = v->propriedades.duracao + v->propriedades.inicio;
                if(insereLista(l_concluidas, item_add) == LISTA_ERR){
                    return MAN_ERR;
                } else {
                    v->propriedades.esta_concluida = true;
                }
            } else {
                if(insereLista(l_atual, item_add) == LISTA_ERR){
                    return MAN_ERR;
                }
            }
        }//if
    }//for
    
    for(i = 0; i < tamanhoLista(l_concluidas); i++){ //checagem e insercao para o resto dos vertices
        item_aux = buscaListaInd(l_concluidas, i);
        v = buscaVertice(g, item_aux.ID); //busca vertice no grafo com a ID igual a celula na lista de concluidos
        if(v == NULL){
            return MAN_ERR; //assertiva de saida
        }
        for(j = 0; j < tamanhoLista(v->adjacentes); j++){ //trabalha com os sucessores de cada vertice dos concluidos
            item_suc = buscaListaInd(v->adjacentes, i);
            v_sucessor = buscaVertice(g, item_suc.ID);
            if(v_sucessor == NULL){
                return MAN_ERR; //assertiva de saida
            }
            if (verificaAntecessores(g, v_sucessor)){
                true_inicio = get_maior_peso(g, l_concluidas, item_suc.ID);
                if(true_inicio <= tempo){
                    item_add.ID = v_sucessor->propriedades.ID;
                    item_add.peso = true_inicio + v_sucessor->propriedades.duracao;
                    if(true_inicio + v_sucessor->propriedades.duracao <= tempo){
                        if(insereLista(l_concluidas, item_add) == LISTA_ERR){
                            return MAN_ERR;
                        } else{
                            v_sucessor->propriedades.esta_concluida = true;
                        }

                    } else {
                        if(insereLista(l_atual, item_add) == LISTA_ERR){
                            return MAN_ERR;
                        } 
                    } //else
                } //if 2
            }   //if 1
        }//for sucessores
    }//for lista_concluidos

    return MAN_OK;
}

//funcao que retorna o maior peso dos antecessores do vertice passado por parametro
int get_maior_peso(t_grafo *g, TipoLista *lista_concluida, int ID_busca){
    if(lista_concluida == NULL){ //assertiva de entrada
        return 0;
    }
    t_vertix *v = buscaVertice(g, ID_busca);

    if (v==NULL){ //assertiva de saida
        return 0;
    }
    if (buscaLista(getOrigens(g), ID_busca)!=NULL){ //se pertence à origem 
        return v->propriedades.inicio;
    }
    
    int i=0;
    t_item item_atual, aux;
    int maior = v->propriedades.inicio, compara;
        for(i=0; i< tamanhoLista(v->antecessores); i++){
            item_atual = buscaListaInd(v->antecessores, i);
            aux = buscaListaInd(lista_concluida, item_atual.ID);
            compara = buscaListaInd(lista_concluida, aux.ID).peso; //pega o peso do antecessor do vertice tratado
            
            if(compara > maior){
                maior = compara;
            }
        }

        return maior;
}

    