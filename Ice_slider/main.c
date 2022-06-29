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

// Fonction main
int main(void)
{
    int run[NBITEPO][4];

    float qsa[NBLIGNESMAP * NBCOLMAP][6];
    float reward[NBLIGNESMAP * NBCOLMAP][6];

    initTabIa(qsa, NBLIGNESMAP, NBCOLMAP, 0);

    initReward(reward, NBLIGNESMAP, NBCOLMAP);

    Intro_jeu();

    return 0;
}