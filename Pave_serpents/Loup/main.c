#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

void clear(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
}

int val_alea(int min, int max){
    static bool initialized = false;
    if (!initialized)
    {
        srand(time(NULL));
        initialized = true;
    }
    return(rand() % (max + 1 -min)) + min;
}

void drawrectangle(SDL_Renderer *renderer)
{
    SDL_Rect rectangle;

    SDL_SetRenderDrawColor(renderer, val_alea(0,255), val_alea(0,255), val_alea(0,255), 255);

    rectangle.x = val_alea(0,800);
    rectangle.y = val_alea(0,800);
    rectangle.w = val_alea(0,800);
    rectangle.h = val_alea(0,800);

    SDL_RenderFillRect(renderer, &rectangle);    
}

void drawline(SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer, val_alea(0,255), val_alea(0,255), val_alea(0,255), 255);

    SDL_RenderDrawLine(renderer, val_alea(0,800), val_alea(0,800), val_alea(0,800), val_alea(0,800));
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    SDL_Window *fenetre = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_DisplayMode screen;

    SDL_Event event;

    SDL_bool prog_on = SDL_TRUE;

    // if (SDL_Init(SDL_INIT_VIDEO) != 0) end_sdl(0, "ERROR SDL INIT", window, renderer);

    SDL_GetCurrentDisplayMode(0, &screen);

    fenetre = SDL_CreateWindow("Fenetre Dessin", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_OPENGL);
    if (fenetre == NULL)
    {
        printf("impossible de creer la fenetre: %s\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(fenetre, -1,
                                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        printf("impossible de creer la fenetre: %s\n", SDL_GetError());
        return 1;
    }

    while (prog_on)
    {
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                prog_on = SDL_FALSE;
                break;

            default:
                break;
            }
        }

        

        drawrectangle(renderer);

        drawline(renderer);

        drawline(renderer);

        SDL_RenderPresent(renderer);

        clear(renderer);

        SDL_Delay(100);
    }

    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(fenetre);

    SDL_Quit();

    return 0;
}