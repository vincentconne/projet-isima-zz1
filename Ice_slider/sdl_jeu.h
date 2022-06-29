#ifndef SDL_JEU_H
#define SDL_JEU_H

// IMPORTS SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

// CONSTANTES
#define width 1300
#define height 900
#define VITESSE 5
#define VITESSEIA 100
#define NBCOLMAP width / 100
#define NBLIGNESMAP height / 100

// FONCTIONS
void sdl_Jeu();
void sdl_IA();
void Intro_jeu();

#endif