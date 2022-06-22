#include <SDL2/SDL.h>
#ifndef sdl_jeu_h
#define sdl_jeu_h

void sdl_Jeu();
void Intro_jeu();
void play_with_texture_1(SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer);
void draw(SDL_Renderer *renderer, int xg, int yg, SDL_Texture *text_texture);

#endif