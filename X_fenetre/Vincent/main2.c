#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>

// ANCIEN:
// gcc -Wall -Wextra -o tp5exo32 tp5exo32.c $(sdl2-config --cflags --libs) && ./tp5exo32

// NEW:
// gcc main.c -o test2 -Wall -Wextra -lSDL2 && ./main

void pause();

int main()
{
  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;

  if (SDL_Init(SDL_INIT_VIDEO))
  {
    SDL_Log("Erreur : initialisation SDL > %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  // création fenetre + rendu
  if (SDL_CreateWindowAndRenderer(800, 800, 0, &window, &renderer) != 0)
  {
    SDL_Log("Erreur : création fenetre + rendu > %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  SDL_Rect rectangle;
  for (int i = 1; i <= 8; i++)
  {
    for (int j = 1; j <= 8; j++)
    {
      rectangle.x = (i - 1) * 100;
      rectangle.y = (j - 1) * 100;
      rectangle.w = 100;
      rectangle.h = 100;

      if ((i + j) % 2 == 1)
      {

        if (SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE) != 0)
        {
          SDL_Log("Erreur : imposible de changer couleur > %s\n", SDL_GetError());
          exit(EXIT_FAILURE);
        }

        if (SDL_RenderFillRect(renderer, &rectangle) != 0)
        {
          SDL_Log("Erreur : imposible de dessiner un rectangle > %s\n", SDL_GetError());
          exit(EXIT_FAILURE);
        }
      }

      else
      {
        if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE) != 0)
        {
          SDL_Log("Erreur : imposible de changer couleur > %s\n", SDL_GetError());
          exit(EXIT_FAILURE);
        }

        if (SDL_RenderFillRect(renderer, &rectangle) != 0)
        {
          SDL_Log("Erreur : imposible de dessiner un rectangle > %s\n", SDL_GetError());
          exit(EXIT_FAILURE);
        }
      }
    }
  }
  

  SDL_RenderPresent(renderer);

  SDL_Delay(5000);

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return EXIT_SUCCESS;
}

void pause()
{
  int continuer = 1;
  SDL_Event event;

  while (continuer)
  {
    SDL_WaitEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
      continuer = 0;
    }
  }
}
