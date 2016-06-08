#include <curses.h> 
#include <stdio.h>
#include <stdlib.h>
#include "ggui.h"

int main(){
  inicializaInterface();
  imprimeMenuNcurses();
  fechaInterface();
}