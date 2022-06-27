#ifndef TEXTURE_H
#define TEXTURE_H

// IMPORTS SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

// IMPORTS STANDARDS
#include <stdio.h>
#include <stdlib.h>

// FONCTIONS
SDL_Texture *load_texture_from_image(char *file_image_name, SDL_Window *window, SDL_Renderer *renderer);
void end_sdl(char ok, char const *msg, SDL_Renderer *renderer);

#endif