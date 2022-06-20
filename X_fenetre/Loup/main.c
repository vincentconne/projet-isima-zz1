#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    SDL_bool prog_on = SDL_TRUE;

    SDL_Window *tabfenetre1[11];
    SDL_Window *tabfenetre2[11];

    SDL_Event event;

    for (int i = 0; i < 11; i++)
    {
        tabfenetre1[i] = SDL_CreateWindow("fenetre", 0 + i * 50, 100 + i * 50, 100*1.1, 100*1.1, SDL_WINDOW_RESIZABLE);
        tabfenetre2[i] = SDL_CreateWindow("fenetre", 500 - i * 50, 100 + i * 50, 100*1.1, 100*1.1, SDL_WINDOW_RESIZABLE);
    }

    SDL_PumpEvents();

    SDL_Delay(5000);

    while (prog_on)
    {
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                prog_on = SDL_FALSE;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_m:
                    for (int i = 0; i < 11; i++)
                    {
                        int x, x2, y2, y;
                        SDL_GetWindowPosition(tabfenetre1[i],&x,&y);
                        SDL_GetWindowPosition(tabfenetre2[i],&x2,&y2);
                        for (int j = 0; j < 10; j++)
                        {
                            SDL_SetWindowPosition(tabfenetre1[i],x+(j*10),y);
                            SDL_SetWindowPosition(tabfenetre2[i],x2+(j*10),y2);
                            SDL_Delay(5);
                        
                        //SDL_Delay(1000);
                    }
                    break;
                case SDLK_SPACE:
                    prog_on = SDL_FALSE;
                    for (int i = 0; i < 11; i++)
                    {
                        SDL_DestroyWindow(tabfenetre1[i]);
                        SDL_DestroyWindow(tabfenetre2[i]);
                    }
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
        }
    }

    SDL_Quit();

    return 0;   

}


