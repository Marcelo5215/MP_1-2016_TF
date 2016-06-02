#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SDL/SDL.h"

int main(){
	SDL_Surface *screen;
	SDL_Surface *image;

	SDL_Init(SDL_INIT_EVERYTHING);

	screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
	image = SDL_LoadBMP("hello.bmp");

	SDL_BlitSurface(image, NULL, screen, NULL);

	SDL_Flip(screen);

	SDL_Delay(100000);

	SDL_FreeSurface(image);

	SDL_Quit();

	return 0;
}