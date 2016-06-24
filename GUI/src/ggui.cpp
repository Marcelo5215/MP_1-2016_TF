#include "ggui.h"

//-------------------------------------------
//Funcoes pertencentes apenas somente ao .c |
//-------------------------------------------
void updateSrcParams();
void editorInterface(t_grafo* g);

bool esta_inicializada = false;
int src_rows;
int src_cols;

gui_ret inicializaInterface(){
	if(!esta_inicializada){
		esta_inicializada = true;
		//inicialza a interface
		initscr();

		//"pega" os parametros da tela
		getmaxyx(stdscr, src_rows, src_cols);

		bkgd(COLOR_PAIR(2));
		//possibilita o uso de cores
		start_color();
		//definição dos pares
		init_pair(1,COLOR_WHITE, COLOR_BLACK);     //Fundo
    	init_pair(2,COLOR_GREEN, COLOR_WHITE);     //Tarefas concluidas
    	init_pair(3,COLOR_RED, COLOR_WHITE);       //Tarefas nao começadas
    	init_pair(4,COLOR_GREEN, COLOR_BLACK);     //MENU 
		init_pair(5,COLOR_BLACK, COLOR_WHITE);     //Fundo Gerenciador, contador
    	return GUI_OK;
	}
	else
		return GUI_ERR;
}

int imprimeTarefasNcurses(t_grafo *g){
	if(!esta_inicializada || g == NULL){
		return GUI_ERR;
	}

	clear();
	bkgd(COLOR_PAIR(5));
   	box(stdscr, ACS_VLINE, ACS_HLINE);
	int linha = 1, coluna = 2;
	char op[11];

	mvprintw(linha, coluna, "Todas as Tarefas:");
	linha++;

	t_vertix* AUX;
	for(AUX = getVertices(g); AUX != NULL ;AUX = AUX->prox){
		attron(COLOR_PAIR(2));
	   	mvprintw(linha,coluna, "ID:%d %s Concluida: %d Tempo de inicio: %d Duracao: %d", AUX->propriedades.ID, 
	   			AUX->propriedades.nome, AUX->propriedades.esta_concluida, AUX->propriedades.inicio,
	   			AUX->propriedades.duracao);
		attroff(COLOR_PAIR(2));
		refresh();
		updateSrcParams();
		linha++;
	}
	refresh();
	attron(COLOR_PAIR(1));
	mvprintw(linha+3,coluna, "1 : Voltar");
	mvprintw(linha+4,coluna, "Digite sua opção:");
	refresh();
	getstr(op);
	attroff(COLOR_PAIR(1));


	return atoi(op);
}

int imprimeTarefasNcurses(t_grafo* g, TipoLista *l_atual, TipoLista *l_concluidas, int tempo){
	if(!esta_inicializada){
		return GUI_ERR;
	}
	clear();
	bkgd(COLOR_PAIR(5));
   	box(stdscr, ACS_VLINE, ACS_HLINE);
	int linha = 1, coluna = 2, i;
	char op[11];

	mvprintw(linha, src_cols - 20, "TEMPO : %d", tempo);
	linha++;

	//t_vertix* AUX;
	t_item temp;
	//imprime as tarefas concluidas
	mvprintw(linha, coluna, "Concluidos: ");
	linha++;
	for(i = 0; i < tamanhoLista(l_concluidas) ; i++){
		temp = buscaListaInd(l_concluidas, i);
		attron(COLOR_PAIR(2));
		mvprintw(linha,coluna, "%d",temp.ID);
		refresh();
		attroff(COLOR_PAIR(2));
		linha++;
	}

	//imprime as tarefas ainda não concluidas mas iniciadas
	mvprintw(linha, coluna, "Em andamento: ");
	linha++;
	for(i = 0; i < tamanhoLista(l_atual) ; i++){
		temp = buscaListaInd(l_atual, i);
		attron(COLOR_PAIR(5));
		mvprintw(linha,coluna, "%d", temp.ID);
		refresh();
		attroff(COLOR_PAIR(5));
		linha++;
	}

	mvprintw(linha, coluna, "Não Começadas: ");
	linha++;
	t_vertix* aux;
	for (aux = getVertices(g) ; aux != NULL; aux = aux->prox){
		if(buscaLista(l_atual, aux->propriedades.ID) != NULL || buscaLista(l_concluidas, aux->propriedades.ID) != NULL){
			continue;
		}
		attron(COLOR_PAIR(3));
		mvprintw(linha,coluna, "%d", aux->propriedades.ID);
		linha++;
		attroff(COLOR_PAIR(3));
		refresh();
	}

	attron(COLOR_PAIR(1));
	mvprintw(linha+3,coluna, "Mais opções:     1 : selecionar outro tempo");
	mvprintw(linha+4,coluna+17, "2 : visualizar todas as tarefas");
	mvprintw(linha+5,coluna+17, "3 : Editar Tarefas");
	mvprintw(linha+6,coluna+17, "4 : Procurar Caminho");
	mvprintw(linha+7,coluna+17, "99 : Sair");
	mvprintw(linha+8,coluna+17, "Digite sua opção:");
	refresh();
	getstr(op);
	attroff(COLOR_PAIR(1));

	return atoi(op);
}

// gui_ret imprimeGrafoNcurses(t_grafo *g){
// }

//==========================================
//Apresenta o menu ao usuário e solicita nome do arquivo
//e o tempo de inicio 
//==========================================
gui_ret imprimeMenuNcurses(char * nome_arq, char* nome_arq_saida,int * tempo){
	char temp[31], op[10];
	int opt = 0;
	//===================================
	// 1. Criar Tarefas de um Arquivo
	// 2. Iniciar Gerenciador
	// 3. Sair
	//===================================
	if(!esta_inicializada){
		return GUI_ERR;
	}
	updateSrcParams();
	bkgd(COLOR_PAIR(1));
	attron(COLOR_PAIR(4));

    while(opt != 99){
	    
	    clear();
   		box(stdscr, ACS_VLINE, ACS_HLINE);
	    mvprintw(1,3,"MENU:");
	    mvprintw(3,6,"1. Criar Tarefas de um Arquivo");
	    mvprintw(4,6,"2. Definir tempo que deseja visualizar.");
	    mvprintw(5,6,"3. Nome do arquivo de saida.");
	    mvprintw(6,6,"99. Sair e iniciar Gerenciador");
	    mvprintw(7,6,"Digite sua opção:");
	    refresh(); 
	    getstr(op); 
	    opt = atoi(op);

	    switch (opt){
	        case 1:
	        	clear();
   				box(stdscr, ACS_VLINE, ACS_HLINE);
				mvprintw(1, 3, "Digite o nome do arquivo:");
				refresh();
				getstr(nome_arq);
	            break;
	        case 2:
	        	clear();
   				box(stdscr, ACS_VLINE, ACS_HLINE);
	        	mvprintw(1, 3, "Digite o numero desejado:");
				refresh();
	    		getstr(temp);
	    		*tempo = atoi(temp);
	            break;
	        case 3: 
	        	clear();
   				box(stdscr, ACS_VLINE, ACS_HLINE);
				mvprintw(1, 3, "Digite o nome do arquivo de saida:");
				refresh();
				getstr(nome_arq_saida);
	            break;
	        case 99: 
	            break;
	        default:
				clear();
   				box(stdscr, ACS_VLINE, ACS_HLINE);
	        	mvprintw(1, 3, "Opção inválida. Precione enter.");
				refresh();
	    		opt = getch();
	        	break; 
	    }
	}

	attroff(COLOR_PAIR(4));
	return GUI_OK;
}

//
void updateSrcParams(){
	//"atualiza" os parametros da tela
	endwin();
	initscr();
	getmaxyx(stdscr, src_rows, src_cols);
}

gui_ret fechaInterface(){
	if(!esta_inicializada){
		return GUI_ERR;
	}
	clear();
	endwin();
	return GUI_OK;
}

void editorInterface(t_grafo* g){
	int ID;
	int coluna = 2, opt = 0;
	char op[11], tarefa[501];

	while(opt != 99){
		clear();	
		bkgd(COLOR_PAIR(5));
   		box(stdscr, ACS_VLINE, ACS_HLINE);
   		mvprintw(1, coluna, "1: Adicionar tarefa:"); 
		mvprintw(2, coluna, "2: Remover tarefa:"); 
		mvprintw(3, coluna, "3: Editar tarefa:"); 
		mvprintw(4, coluna, "99: sair do editor"); 
		mvprintw(5, coluna, "OPCAO: "); 
		getstr(op);
		opt = atoi(op);

		switch(opt){
			case 1:
				clear();
				attron(COLOR_PAIR(2));
				mvprintw(1, coluna, "Digite a tarefa no formato especificado: ");
				getstr(tarefa);
				if(insereTarefa(g, tarefa) != MAN_OK){
					attroff(COLOR_PAIR(2));
					attron(COLOR_PAIR(3));
					mvprintw(4, coluna, "OCORREU UM ERRO NA INSERCAO DA TAREFA!!!, Precione ENTER!");
					getch();
					attroff(COLOR_PAIR(3));
					attron(COLOR_PAIR(2));
				}
				attroff(COLOR_PAIR(2));
				break;
			case 2:
				clear();
				attron(COLOR_PAIR(2));
				mvprintw(1, coluna, "Digite o ID da tarefa a ser removida: ");
				getstr(tarefa);
				if(retiraTarefa(g, atoi(tarefa)) == MAN_ERR){
					attroff(COLOR_PAIR(2));
					attron(COLOR_PAIR(3));
					mvprintw(4, coluna, "OCORREU UM ERRO NA REMOCAO DA TAREFA!!!, Precione ENTER!");
					getch();
					attroff(COLOR_PAIR(3));
					attron(COLOR_PAIR(2));
				}
				attroff(COLOR_PAIR(2));
				break;
			case 3:
				clear();
				attron(COLOR_PAIR(2));
				mvprintw(1, coluna, "Digite o ID da tarefa a ser editada: ");
				getstr(tarefa);
				ID = atoi(tarefa);
				mvprintw(2, coluna, "Digite a nova tarefa no modelo especificado: ");
				getstr(tarefa);
				if(editaTarefa(g, ID ,tarefa)!= MAN_OK){
					attroff(COLOR_PAIR(2));
					attron(COLOR_PAIR(3));
					mvprintw(4, coluna, "OCORREU UM ERRO NA EDICAO DA TAREFA!!!, Precione ENTER!");
					getch();
					attroff(COLOR_PAIR(3));
					attron(COLOR_PAIR(2));
				}
				attroff(COLOR_PAIR(2));
				break;
			case 99:
				break;
			default:
				opt = intERROR();
				break;

		}
	}

	return;
}

int imprimeCaminhoInterface(t_grafo* g, int IDDestino){
    if(g==NULL){
        return 1;
    }
    char ID[15], op[15];
    do{
	    clear();
	    bkgd(COLOR_PAIR(5));
	   	box(stdscr, ACS_VLINE, ACS_HLINE);
	   	mvprintw(2, 2, "Digite o ID da tarefa que deseja saber o caminho: ");
	   	getstr(ID);
	   	IDDestino = atoi(ID);
	   	if (buscaVertice(g, IDDestino) == NULL){
			attron(COLOR_PAIR(3));
	   		mvprintw(4, 2, "ERRO AO PROCURAR CAMINHO, VERIFIQUE SE A ENTRADA E VALIDA.");
	   		getch();
			attroff(COLOR_PAIR(3));
		}
	}while(buscaVertice(g, IDDestino) == NULL);
    
    TipoLista *l_concluidas = criaLista();
    t_item item_aux, item_suc;
    t_item item_add;
    t_vertix *v, *v_sucessor;
    int true_inicio=0;
    int i =0, j=0;

    //Esses lacos criam a lista de concluidos com os pesos de todas as tarefas
    for(i = 0; i < tamanhoLista(getOrigens(g)); i++){ //checagem das origens e insercao na lista de concluidos
        item_aux = buscaListaInd(getOrigens(g), i);
        v = buscaVertice(g, item_aux.ID);
                item_add.ID = v->propriedades.ID;
                item_add.peso = v->propriedades.duracao + v->propriedades.inicio;
                if(insereLista(l_concluidas, item_add) == LISTA_ERR){
                    return 1;
                }
    }//for
    
    for(i = 0; i < tamanhoLista(l_concluidas); i++){ //checagem e insercao para o resto dos vertices
        item_aux = buscaListaInd(l_concluidas, i);
        v = buscaVertice(g, item_aux.ID); //busca vertice no grafo com a ID igual a celula na lista de concluidos
        if(v == NULL){
            return 1; //assertiva de saida
        }
        for(j = 0; j < tamanhoLista(v->adjacentes); j++){ //trabalha com os sucessores de cada vertice dos concluidos
            item_suc = buscaListaInd(v->adjacentes, j);
            v_sucessor = buscaVertice(g, item_suc.ID);
            if(v_sucessor == NULL){
                return 1; //assertiva de saida
            }
                true_inicio = get_maior_peso(g, l_concluidas, item_suc.ID);
                item_add.ID = v_sucessor->propriedades.ID;
                item_add.peso = true_inicio + v_sucessor->propriedades.duracao;
                    if(buscaLista(l_concluidas, item_add.ID)==NULL){ //evitar a insercao de duplicados
                        if(insereLista(l_concluidas, item_add) == LISTA_ERR){
                             return 1;
                        }
                    }
                    
        }//for sucessores
    }//for lista_concluidos
    achaCaminhoMin(g,l_concluidas, IDDestino);
    //fim dos lacos, prosseguir para a impressao

    clear();
   	box(stdscr, ACS_VLINE, ACS_HLINE);

    int linha = 1, coluna = 2;
    t_vertix* AUX = buscaVertice(g, IDDestino);
    while(AUX != NULL){
    	mvprintw(linha, coluna, "%d -- %s", AUX->propriedades.ID, AUX->propriedades.nome);
    	linha++;
    	AUX = AUX->pai;
    }
    AUX = buscaVertice(g, IDDestino);
    mvprintw(linha, coluna, "Tempo para completar essa tarefa: %d",
             get_maior_peso(g, l_concluidas, AUX->propriedades.ID) + AUX->propriedades.duracao);

    attron(COLOR_PAIR(1));
	mvprintw(linha+3,coluna, "Mais opções:     1 : selecionar outro tempo");
	mvprintw(linha+4,coluna+17, "2 : visualizar todas as tarefas");
	mvprintw(linha+5,coluna+17, "3 : Editar Tarefas");
	mvprintw(linha+6,coluna+17, "4 : Procurar Caminho");
	mvprintw(linha+7,coluna+17, "99 : Sair");
	mvprintw(linha+8,coluna+17, "Digite sua opção:");
	refresh();
	getstr(op);
	attroff(COLOR_PAIR(1));   
 
    return atoi(op);
}

//informa de possiveis erros 
int intERROR(){
	clear();
	char op[11];
	updateSrcParams();
	mvprintw(src_rows/4, src_cols/4, "OPCAO INVALIDA, OU TEMPORARIAMENTE NAO IMPLEMENTADA.");
	mvprintw(src_rows/4 +1, src_cols/4, "Selecione outra : ");
	refresh();
	getstr(op);

	return atoi(op);
}

//solicita um tempo 
int getUserTempo(){
	clear();
	updateSrcParams();
	char temp[30];
	mvprintw(src_rows/4, 2, "Digite o tempo desejado: ");
	refresh();
	getstr(temp);

	return atoi(temp);
}
