#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>

void draw(SDL_Renderer *renderer){
    SDL_Rect rectangle;

    SDL_SetRenderDrawColor(renderer, 50, 0, 0,255);

    rectangle.x = 100;
    rectangle.y = 100;
    rectangle.w = 400;
    rectangle.h = 400;

    SDL_RenderFillRect(renderer, &rectangle);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_RenderDrawLine(renderer, 0, 0, 400, 400);
}

int main(int argc, char **argv){
    (void)argc;
    (void)argv;

    SDL_Window *fenetre = NULL;

    SDL_Renderer *renderer = NULL;

    SDL_DisplayMode screen;

    //if (SDL_Init(SDL_INIT_VIDEO) != 0) end_sdl(0, "ERROR SDL INIT", window, renderer);

    SDL_GetCurrentDisplayMode(0,&screen);

    fenetre = SDL_CreateWindow("Fenetre Dessin",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,screen.w * 07, screen.h * 0,7);

    renderer = SDL_CreateRenderer(fenetre, -1,
                                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    draw(renderer);

    SDL_RenderPresent(renderer);

    SDL_Delay(1000);

    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(fenetre);

    SDL_Quit();

    return 0;
}