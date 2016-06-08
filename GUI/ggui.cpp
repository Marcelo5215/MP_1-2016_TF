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
    	return GUI_OK;
	}
	else
		return GUI_ERR;
}

// gui_ret imprimeGrafoNcurses(t_grafo *g){
// }

//==========================================
//Apresenta o menu ao usuário e retorna uma 
//string com o nome do arquivo
//==========================================
char* imprimeMenuNcurses(){
	static char saida[31];
	int opt = 0;
	//===================================
	// 1. Criar Tarefas de um Arquivo
	// 2. Iniciar Gerenciador
	// 3. Sair
	//===================================
	if(!esta_inicializada){
		return NULL;
	}
	bkgd(COLOR_PAIR(1));
	attron(COLOR_PAIR(4));

    while(opt != 51){
	    
	    clear();
   		box(stdscr, ACS_VLINE, ACS_HLINE);
	    mvprintw(1,3,"MENU:");
	    mvprintw(2,6,"1. Criar Tarefas de um Arquivo");
	    mvprintw(3,6,"2. Iniciar Gerenciador");
	    mvprintw(4,6,"3. Sair");
	    mvprintw(5,6,"Digite sua opção:");
	    refresh(); 
	    opt = getch(); 

	    switch (opt){
	        case 49:
	        	clear();
   				box(stdscr, ACS_VLINE, ACS_HLINE);
				mvprintw(1, 3, "Digite o nome do arquivo:");
				refresh();
				getstr(saida);
	            break;
	        case 50:
	        	clear();
   				box(stdscr, ACS_VLINE, ACS_HLINE);
	        	mvprintw(1, 3, "OP 2.");
				refresh();
	    		opt = getch(); 
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
	return saida;
}

void updateSrcParams(){
	//"atualiza" os parametros da tela
		getmaxyx(stdscr, src_rows, src_cols);
}

gui_ret fechaInterface(){
	if(!esta_inicializada){
		return GUI_ERR;
	}
	endwin();
	return GUI_OK;
}
