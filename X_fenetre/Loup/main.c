#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>

int main(int argc, char **argv){
    (void)argc;
    (void)argv;

    SDL_bool prog_on = SDL_TRUE;

    SDL_Window *tabfenetre[5];

    SDL_Event event;

    for (int i = 0; i < 5; i++)
    {
        tabfenetre[i] = SDL_CreateWindow("fenetre", 0 + i * 50, 100 + i * 50, 100, 100, SDL_WINDOW_RESIZABLE);
    }

    
}