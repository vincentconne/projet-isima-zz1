#ifndef SDL_JEU_H
#define SDL_JEU_H

// IMPORTS SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>


// FONCTIONS
void sdl_Jeu();
void Intro_jeu();
void draw(SDL_Renderer *renderer, int xg, int yg, SDL_Texture *text_texture);

#endif