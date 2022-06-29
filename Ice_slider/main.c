// IMPORTS SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// IMPORTS STANDARDS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// IMPORTS FICHIERS
#include "jeu.h"
#include "sdl_jeu.h"
#include "ia.h"

// CONSTANTES
#define width 1300
#define height 900

#define VITESSE 10

#define NBCOLMAP width / 100
#define NBLIGNESMAP height / 100

// Fonction main
int main(void)
{
    int run[NBITEPO][4];

   
    float qsa[NBLIGNESMAP * NBCOLMAP][6];
    initQsa(qsa, NBLIGNESMAP, NBCOLMAP);

    Intro_jeu();

    return 0;
}