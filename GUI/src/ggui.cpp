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
		init_pair(1,COLOR_WHITE,COLOR_BLACK);     //Fundo
    	init_pair(2,COLOR_GREEN,COLOR_WHITE);     //Tarefas concluidas
    	init_pair(3,COLOR_RED,COLOR_WHITE);       //Tarefas nao começadas
    	init_pair(4,COLOR_GREEN,COLOR_BLACK);     //MENU 
		init_pair(5,COLOR_BLACK,COLOR_WHITE);     //Fundo Gerenciador, contador
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
	mvprintw(linha+6,coluna+17, "99 : Sair");
	mvprintw(linha+7,coluna+17, "Digite sua opção:");
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
