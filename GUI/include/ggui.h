#ifndef H_GUI
#define H_GUI
	#include <stdlib.h>
	#include <curses.h>
	#include "grafo.h"
	#include "lista.h"
	#include "gerenciador.h"

	typedef enum{
		GUI_OK,
		GUI_ERR,
	}gui_ret;

	gui_ret inicializaInterface();
	//gui_ret imprimeGrafoNcurses(t_grafo *g);
	void updateSrcParams();
	gui_ret imprimeMenuNcurses(char* nome_arq, int *tempo);
	gui_ret fechaInterface();
	gui_ret imprimeTarefasNcurses(t_grafo *g, int tempo);
	gui_ret imprimeTarefasNcurses(t_grafo* g, TipoLista *l_atual, TipoLista *l_concluidas, int tempo);

	

#endif