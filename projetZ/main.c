#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "jeu.h"
#include "sdl_jeu.h"
#include "texture.h"

#define width 1300
#define height 900

int main()
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    int statut = EXIT_FAILURE;
    SDL_DisplayMode screen;
    int stop = 0;

    if (0 != SDL_Init(SDL_INIT_VIDEO))
    {
        end_sdl(0, "ERROR SDL INIT", window, renderer);
    }

    SDL_GetCurrentDisplayMode(0, &screen);

    window = SDL_CreateWindow("Ice",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, width,
                              height,
                              SDL_WINDOW_OPENGL);
    if (NULL == window)
    {
        end_sdl(0, "ERROR WINDOW", window, renderer);
    }

    renderer = SDL_CreateRenderer(window, -1,
                                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        end_sdl(0, "ERROR RENDERER", window, renderer);
    }

    statut = EXIT_SUCCESS;

    SDL_bool program_on = SDL_TRUE; // Booléen pour dire que le programme doit continuer
    SDL_Event event;                // c'est le type IMPORTANT !!

    SDL_Texture *fond;
    fond = load_texture_from_image("./src/fond_glace.png", window, renderer);
    SDL_Rect
        source = {0},            // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};       // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(
        window, &window_dimensions.w,
        &window_dimensions.h); // Récupération des dimensions de la fenêtre
    SDL_QueryTexture(fond, NULL, NULL,
                     &source.w, &source.h); // Récupération des dimensions de l'image

    destination = window_dimensions; // On fixe les dimensions de l'affichage à  celles de la fenêtre

    SDL_Texture *roc1 = IMG_LoadTexture(renderer, "./src/rocher.png");
    //SDL_Rect entree = {600, 800, 100, 100};
    //SDL_Rect sortie = {600, 0, 100, 100};

    SDL_Rect rect_roc[13];
    rect_roc[0].x = 200;
    rect_roc[0].y = 100;
    rect_roc[0].w = 100;
    rect_roc[0].h = 100;
    rect_roc[1].x = 100;
    rect_roc[1].y = 200;
    rect_roc[1].w = 100;
    rect_roc[1].h = 100;
    rect_roc[2].x = 100;
    rect_roc[2].y = 700;
    rect_roc[2].w = 100;
    rect_roc[2].h = 100;
    rect_roc[3].x = 200;
    rect_roc[3].y = 400;
    rect_roc[3].w = 100;
    rect_roc[3].h = 100;
    rect_roc[4].x = 600;
    rect_roc[4].y = 300;
    rect_roc[4].w = 100;
    rect_roc[4].h = 100;
    rect_roc[5].x = 600;
    rect_roc[5].y = 500;
    rect_roc[5].w = 100;
    rect_roc[5].h = 100;
    rect_roc[6].x = 700;
    rect_roc[6].y = 700;
    rect_roc[6].w = 100;
    rect_roc[6].h = 100;
    rect_roc[7].x = 800;
    rect_roc[7].y = 400;
    rect_roc[7].w = 100;
    rect_roc[7].h = 100;
    rect_roc[8].x = 900;
    rect_roc[8].y = 600;
    rect_roc[8].w = 100;
    rect_roc[8].h = 100;
    rect_roc[9].x = 1000;
    rect_roc[9].y = 100;
    rect_roc[9].w = 100;
    rect_roc[9].h = 100;
    rect_roc[10].x = 1100;
    rect_roc[10].y = 300;
    rect_roc[10].w = 100;
    rect_roc[10].h = 100;
    rect_roc[11].x = 1100;
    rect_roc[11].y = 700;
    rect_roc[11].w = 100;
    rect_roc[11].h = 100;
    rect_roc[12].x = 500;
    rect_roc[12].y = 200;
    rect_roc[12].w = 100;
    rect_roc[12].h = 100;

    SDL_Rect rect_mur[6];
    rect_mur[0].x = 0;
    rect_mur[0].y = 0;
    rect_mur[0].w = 100;
    rect_mur[0].h = 900;
    rect_mur[1].x = 1200;
    rect_mur[1].y = 0;
    rect_mur[1].w = 100;
    rect_mur[1].h = 900;
    rect_mur[2].x = 100; // haut gauche
    rect_mur[2].y = 0;
    rect_mur[2].w = 500;
    rect_mur[2].h = 100;
    rect_mur[3].x = 700; // haut droite
    rect_mur[3].y = 0;
    rect_mur[3].w = 500;
    rect_mur[3].h = 100;
    rect_mur[4].x = 100; // bas gauche
    rect_mur[4].y = 800;
    rect_mur[4].w = 500;
    rect_mur[4].h = 100;
    rect_mur[5].x = 700; // bas droite
    rect_mur[5].y = 800;
    rect_mur[5].w = 500;
    rect_mur[5].h = 100;

    while (program_on && stop == 0)
    { // Voilà la boucle des évènements

        if (SDL_PollEvent(&event))
        { // si la file d'évènements n'est pas vide : défiler l'élément en tête
          // de file dans 'event'
            switch (event.type)
            {

            case SDL_QUIT:              // Un évènement simple, on a cliqué sur la x de la fenêtre
                program_on = SDL_FALSE; // Il est temps d'arrêter le programme
                break;

            default: // Si L'évènement défilé ne nous intéresse pas
                break;
            }
        }
        SDL_RenderCopy(renderer, fond, &source, &destination);
        for (int i = 0; i < 13; i++)
        {
            SDL_RenderCopy(renderer, roc1, NULL, &rect_roc[i]);
        }

        for (int i = 0; i < 6; i++)
        {
            SDL_RenderFillRect(renderer, &rect_mur[i]);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(roc1);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return statut;
}