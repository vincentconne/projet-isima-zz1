#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

// void draw(SDL_Renderer* renderer) {                                 // Je pense que vous allez faire moins laid :)
//   SDL_Rect rectangle;

//   SDL_SetRenderDrawColor(renderer,
//                          50, 0, 0,                                  // mode Red, Green, Blue (tous dans 0..255)
//                          255);                                      // 0 = transparent ; 255 = opaque
//   rectangle.x = 0;                                                  // x haut gauche du rectangle
//   rectangle.y = 0;                                                  // y haut gauche du rectangle
//   rectangle.w = 400;                                                // sa largeur (w = width)
//   rectangle.h = 400;                                                // sa hauteur (h = height)

//   SDL_RenderFillRect(renderer, &rectangle);

//   SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//   SDL_RenderDrawLine(renderer,
//                      0, 0,                                          // x,y du point de la première extrémité
//                      400, 400);                                     // x,y seconde extrémité

//   /* tracer un cercle n'est en fait pas trivial, voilà le résultat sans algo intelligent ... */
//   for (float angle = 0; angle < 2 * M_PI; angle += M_PI / 4000) {
//     SDL_SetRenderDrawColor(renderer,
//                            (cos(angle * 2) + 1) * 255 / 2,          // quantité de Rouge
//                            (cos(angle * 5) + 1) * 255 / 2,          //          de vert
//                            (cos(angle) + 1) * 255 / 2,              //          de bleu
//                            255);                                    // opacité = opaque
//     SDL_RenderDrawPoint(renderer,
//                         200 + 100 * cos(angle),                     // coordonnée en x
//                         200 + 150 * sin(angle));                    //            en y
//   }
// }

int main()
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    int statut = EXIT_FAILURE;
    int i = 0;
    SDL_DisplayMode screen;

    if (0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_GetCurrentDisplayMode(0, &screen);
    

    while (i < 16)
    {
        /* Création de la fenêtre */
        window = SDL_CreateWindow("Premier dessin",
                                  0 + i * 50,
                                  0 + i * 50, screen.w * 0.20 + 50,
                                  screen.h * 0.20 +100,
                                  SDL_WINDOW_OPENGL);
        if (NULL == window)
        {
            fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
            exit(EXIT_FAILURE);
        }

        /* Création de la fenêtre */
        window = SDL_CreateWindow("Premier dessin",
                                  screen.h - i * 50,
                                  0 + i * 50, screen.w * 0.20 -50,
                                  screen.h * 0.20 -100,
                                  SDL_WINDOW_OPENGL);
        if (NULL == window)
        {
            fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
            exit(EXIT_FAILURE);
        }


        
        i++;
    }

    //     renderer = SDL_CreateRenderer(window, -1,
    //                                 SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    //   if (renderer == NULL)
    //   {
    //     exit(EXIT_FAILURE);
    //   }

    statut = EXIT_SUCCESS;
    // draw(renderer);
    // SDL_RenderPresent(renderer);                         // affichage
    SDL_Delay(3000);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return statut;
}