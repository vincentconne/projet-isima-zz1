// ******************************************* //
// FICHIER H POUR LE FONCTIONNEMENT DU JEU (SDL)
// ******************************************* //
#ifndef SDL_JEU_H
#define SDL_JEU_H

// IMPORTS SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

// IMPORTS STANDARDS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

// IMPORTS DE FICHIERS
#include "sdl_utils.h"
#include "ia.h"
#include "jeu.h"

// CONSTANTES
#define width 1300
#define height 900
#define VITESSE 5
#define VITESSEIA 10
#define NBCOLMAP width / 100
#define NBLIGNESMAP height / 100
#define INTERVALAFF 1000

// FONCTIONS
void sdlJeu();
void sdlIA();
void introJeu();

#endif