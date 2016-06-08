#ifndef H_GUI
#define H_GUI
	#include <stdlib.h>
	#include <curses.h>
	//#include "grafo.h"
	//#include "lista.h"
	//#include "gerenciador.h"

	typedef enum{
		GUI_OK,
		GUI_ERR,
	}gui_ret;

	gui_ret inicializaInterface();
	//gui_ret imprimeGrafoNcurses(t_grafo *g);
	void updateSrcParams();
	char* imprimeMenuNcurses();
	gui_ret fechaInterface();

	

#endif