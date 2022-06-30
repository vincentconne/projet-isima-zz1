// ************************************* //
// FICHIER H POUR LE FONCTIONNEMENT DU JEU
// ************************************* //

#ifndef JEU_H
#define JEU_H

// IMPORTS SDL
#include <SDL2/SDL.h>

// IMPORTS STANDARDS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// IMPORTS STANDARDS
#include <time.h>

// FONCTIONS
int valeurRandom(int min, int max);
void initRoc(SDL_Rect *rectRoc);
void initMur(SDL_Rect *rectMur);
void recherche1(int TabJeu[][13], int direction, int posEsquiX, int posEsquiY, int tabRetour[2]);

#endif