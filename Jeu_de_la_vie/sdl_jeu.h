#include <SDL2/SDL.h>
#ifndef sdl_jeu_h
#define sdl_jeu_h


void DessinCases(SDL_Rect rect, SDL_Renderer *renderer, int **tab);
void sdl_Jeu(int **monde,int **tmp,int indice_fct);
void draw(SDL_Renderer *renderer, int xg, int yg, SDL_Texture *text_texture);
void AfficheMessage(SDL_Renderer *renderer);

#endif