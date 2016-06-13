#include "ggui.h"

//-------------------------------------------
//Funcoes pertencentes apenas somente ao .c |
//-------------------------------------------
void updateSrcParams();

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
    	init_pair(2,COLOR_GREEN,COLOR_WHITE);     //Tarefas
    	init_pair(3,COLOR_RED,COLOR_WHITE);       //Contador
    	init_pair(4,COLOR_GREEN,COLOR_BLACK);     //MENU 
		init_pair(5,COLOR_BLACK,COLOR_WHITE);     //Fundo Gerenciador
    	return GUI_OK;
	}
	else
		return GUI_ERR;
}

gui_ret imprimeTarefasNcurses(t_grafo *g, int tempo){
	if(!esta_inicializada){
		return GUI_ERR;
	}

	clear();
	bkgd(COLOR_PAIR(5));
   	box(stdscr, ACS_VLINE, ACS_HLINE);
	int linha = 1, coluna = 2;



	mvprintw(linha, coluna, "Todas as Tarefas:");
	mvprintw(linha, src_cols - 20, "TEMPO : %d", tempo);
	linha++;

	t_vertix* AUX;
	for(AUX = getVertices(g); AUX != NULL ;AUX = AUX->prox){
		attron(COLOR_PAIR(2));
	   	mvprintw(linha,coluna, AUX->propriedades.nome);
		attroff(COLOR_PAIR(2));
		refresh();
		updateSrcParams();
		linha++;
	}
	refresh();
	getch();

	return GUI_OK;
}

gui_ret imprimeTarefasNcurses(t_grafo* g, TipoLista *l_atual, TipoLista *l_concluidas, int tempo){
	if(!esta_inicializada){
		return GUI_ERR;
	}
	clear();
	bkgd(COLOR_PAIR(5));
   	box(stdscr, ACS_VLINE, ACS_HLINE);
	int linha = 1, coluna = 2, i;

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
	refresh();
	getch();

	return GUI_OK;
}

// gui_ret imprimeGrafoNcurses(t_grafo *g){
// }

//==========================================
//Apresenta o menu ao usuário e retorna uma 
//string com o nome do arquivo
//==========================================
gui_ret imprimeMenuNcurses(char * nome_arq, int * tempo){
	char temp[31];
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

    while(opt != 51){
	    
	    clear();
   		box(stdscr, ACS_VLINE, ACS_HLINE);
	    mvprintw(1,3,"MENU:");
	    mvprintw(2,6,"1. Criar Tarefas de um Arquivo");
	    mvprintw(3,6,"2. Definir tempo que deseja visualizar.");
	    mvprintw(4,6,"3. Sair e iniciar Gerenciador");
	    mvprintw(5,6,"Digite sua opção:");
	    refresh(); 
	    opt = getch(); 

	    switch (opt){
	        case 49:
	        	clear();
   				box(stdscr, ACS_VLINE, ACS_HLINE);
				mvprintw(1, 3, "Digite o nome do arquivo:");
				refresh();
				getstr(nome_arq);
	            break;
	        case 50:
	        	clear();
   				box(stdscr, ACS_VLINE, ACS_HLINE);
	        	mvprintw(1, 3, "Digite o numero desejado:");
				refresh();
	    		getstr(temp);
	    		*tempo = atoi(temp);
	            break;
	        case 51: 
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
