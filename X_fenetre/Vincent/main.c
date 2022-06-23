#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

int main()
{
    SDL_Window *window = NULL;
    int statut = EXIT_FAILURE;
    int i = 0;
    SDL_DisplayMode screen;

    if (0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_Window *window1 = NULL;
    SDL_Window *window2 = NULL;

    SDL_GetCurrentDisplayMode(0, &screen);

    int sortie = 0;
    int j = 0;
    while (!sortie && i < 20 && j < 20)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {

            if (event.type == SDL_QUIT)
            {
                sortie = 1;
                puts("FIN DE MON PROGRAMME");
                break;
            }
        }

        window1 = SDL_CreateWindow("Fenêtre",
                                   0 + j * 50,
                                   screen.h *0.4, screen.w * 0.20 + 40,
                                   screen.h * 0.20 + 40,
                                   SDL_WINDOW_OPENGL);
        window2 = SDL_CreateWindow("Fenêtre",
                                   screen.w - j * 80,
                                   screen.h *0.4, screen.w * 0.20 + 40,
                                   screen.h * 0.20 + 40,
                                   SDL_WINDOW_OPENGL);
        j++;
        if (NULL == window1 && NULL == window2)
        {
            fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
            exit(EXIT_FAILURE);
        }

        /* Création de la fenêtre */
        window = SDL_CreateWindow("Fenêtre",
                                  0 + i * 50,
                                  0 + i * 50, screen.w * 0.20 + 20,
                                  screen.h * 0.20 + 40,
                                  SDL_WINDOW_OPENGL);
        if (NULL == window)
        {
            fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
            exit(EXIT_FAILURE);
        }
        SDL_Delay(50);
        SDL_DestroyWindow(window);

        /* Création de la fenêtre */
        window = SDL_CreateWindow("Fenêtre",
                                  screen.h - i * 50,
                                  0 + i * 50, screen.w * 0.20 - 20,
                                  screen.h * 0.20 - 40,
                                  SDL_WINDOW_OPENGL);
        if (NULL == window)
        {
            fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
            exit(EXIT_FAILURE);
        }
        SDL_Delay(50);
        SDL_DestroyWindow(window);
        i++;
    }

    statut = EXIT_SUCCESS;
    // draw(renderer);
    // SDL_RenderPresent(renderer);                         // affichage
    SDL_Delay(1000);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return statut;
}