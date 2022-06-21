#include <stdio.h>
#include "SDL2/SDL.h"
#include <stdbool.h>
#include <time.h>


typedef struct rect
{
    int x1;
    int y1;
    int x2;
    int y2;
} rect;

void clear(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
}

int valeur_random(int MIN, int MAX)
{
    static bool initialized = false;
    if (!initialized)
    {
        srand(time(NULL));
        initialized = true;
    }

    return (rand() % (MAX + 1 - MIN)) + MIN;
}

void drawLine(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, valeur_random(0, 255), valeur_random(0, 255), valeur_random(0, 255), 255);
    SDL_RenderDrawLine(renderer, valeur_random(0, 700), valeur_random(0, 700), valeur_random(0, 700), valeur_random(0, 700));
    SDL_RenderPresent(renderer);
}



int main()
{

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_DisplayMode screen;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(
        "Mon serpent multicolore",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        800,
        800,
        SDL_WINDOW_OPENGL);

    if (window == NULL)
    {
        printf("impossible de creer la fenetre: %s\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL)
    {
        printf("impossible de creer la fenetre: %s\n", SDL_GetError());
        return 1;
    }

    rect rectangle;
    rectangle.x1 = 300;
    rectangle.y1 = 400;
    rectangle.x2 = 500;
    rectangle.y2 = 600;

    SDL_bool program_on = SDL_TRUE; // Booléen pour dire que le programme doit continuer
    SDL_Event event;                // c'est le type IMPORTANT !!
    SDL_GetCurrentDisplayMode(0, &screen);

    while (program_on)
    { // Voilà la boucle des évènements

        if (SDL_PollEvent(&event))
        { // si la file d'évènements n'est pas vide : défiler l'élément en tête
          // de file dans 'event'
            switch (event.type)
            {                           // En fonction de la valeur du type de cet évènement
            case SDL_QUIT:              // Un évènement simple, on a cliqué sur la x de la fenêtre
                program_on = SDL_FALSE; // Il est temps d'arrêter le programme
                break;

            default: // L'évènement défilé ne nous intéresse pas
                break;
            }
        }
        // Affichages et calculs souvent ici
        srand(time(NULL));
        int x1 = valeur_random(-3, 3);
        int y1 = valeur_random(-3, 3);
        int x2 = valeur_random(-3, 3);
        int y2 = valeur_random(-3, 3);

        int choix = rand() % 3;

        if (choix == 0)
        {
            if (rectangle.x1 + x1 < 780 && rectangle.x1 + x1 > 20)
            {
                rectangle.x1 += x1;
            }
        }
        else if (choix == 1)
        {
            if (rectangle.y1 + y1 < 780 && rectangle.y1 + y1 > 20)
            {
                rectangle.y1 += y1;
            }
        }
        else if (choix == 2)
        {
            if (rectangle.x2 + x2 < 780 && rectangle.x2 + x2 > 20)
            {
                rectangle.x2 += x2;
            }
        }
        else if (choix == 3)
        {
            if (rectangle.y2 + y2 < 780 && rectangle.y2 + y2 > 20)
            {
                rectangle.y2 += y2;
            }
        }

        SDL_SetRenderDrawColor(renderer, valeur_random(0, 255), valeur_random(0, 255), valeur_random(0, 255), 255);
        SDL_RenderDrawLine(renderer, rectangle.x1, rectangle.y1, rectangle.x2, rectangle.y2);
        SDL_RenderPresent(renderer);
        // drawLine(renderer);
        clear(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
