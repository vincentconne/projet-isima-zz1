// ************************************* //
// FICHIER H FONCTIONS UTILES POUR SDL
// ************************************* //

#ifndef SDLUTILS_H
#define SDLUTILS_H

// IMPORTS SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

// IMPORTS STANDARDS
#include <stdio.h>
#include <stdlib.h>

// FONCTIONS
SDL_Texture *loadTextureFromImage(char *file_image_name, SDL_Renderer *renderer);
void initSDL(SDL_Window *window, SDL_Renderer *renderer);
void endSdl(char ok, char const *msg, SDL_Window *window, SDL_Renderer *renderer);
void draw(SDL_Renderer *renderer, int xg, int yg, SDL_Texture *text_texture);
SDL_Surface *AffichageSortie();

#endif