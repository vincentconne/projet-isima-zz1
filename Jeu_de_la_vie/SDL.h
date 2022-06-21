
#include <SDL2/SDL.h>

#ifndef jeu_h
#define jeu_h


void DessinCases(SDL_Rect rect, SDL_Renderer *renderer, int **tab);
void SDL(int **monde,int **tmp,int indice_fct);

#endif