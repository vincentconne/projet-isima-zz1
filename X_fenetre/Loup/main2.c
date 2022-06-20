#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;

  SDL_bool prog_on = SDL_TRUE;

  SDL_Window *tabfenetre[5];

  SDL_Event event;

  /* Initialisation de la SDL  + gestion de l'échec possible */
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    SDL_Log("Error : SDL initialisation - %s\n",
            SDL_GetError());
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < 5; i++)
  {
    tabfenetre[i] = SDL_CreateWindow("fenetre", 0 + i * 50, 100 + i * 50, 100, 100, SDL_WINDOW_RESIZABLE);
  }

  int x = 0, y = 0;

  for (int j = 0; j < 5; j++)
  {
    for (int i = 0; i < 10; i++)
    {
      SDL_GetWindowPosition(tabfenetre[j], &x, &y);
      printf("%d %d\n", x, y);
      SDL_SetWindowPosition(tabfenetre[j], x + 10, y + 10);
      SDL_Delay(1000);
    }
  }

  SDL_PumpEvents();

  /* Normalement, on devrait ici remplir les fenêtres... */
  SDL_Delay(5000); // Pause exprimée  en ms

  /* et on referme tout ce qu'on a ouvert en ordre inverse de la création */

  while (prog_on)
  { // Voilà la boucle des évènements

    if (SDL_PollEvent(&event))
    { // si la file d'évènements n'est pas vide : défiler l'élément en tête
      // de file dans 'event'
      switch (event.type)
      {                      // En fonction de la valeur du type de cet évènement
      case SDL_QUIT:         // Un évènement simple, on a cliqué sur la x de la fenêtre
        prog_on = SDL_FALSE; // Il est temps d'arrêter le programme
        break;
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_SPACE:
          prog_on = SDL_FALSE;
          for (int i = 0; i < 5; i++)
          {
            SDL_DestroyWindow(tabfenetre[i]);
          }
          break;

        default:
          break;
        }
        // Il est temps d'arrêter le programme
        break;
      default: // L'évènement défilé ne nous intéresse pas
        break;
      }
    }
    // Affichages et calculs souvent ici
  }

  SDL_Quit();

  return 0;
}