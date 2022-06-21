#include <SDL2/SDL.h>
#include <stdio.h>
#include "time.h"
#define MAX 350

void end_sdl(char ok,char const* msg,SDL_Window* window,SDL_Renderer* renderer) {
  char msg_formated[255];                                                         
  int l;

  if (!ok) {
    strncpy(msg_formated, msg, 250);                                              
    l = strlen(msg_formated);                                                     
    strcpy(msg_formated + l, " : %s\n");                                          

    SDL_Log(msg_formated, SDL_GetError());                                        
  }                                                                               

  if (renderer != NULL) {
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
  }
  if (window != NULL)   { 
    SDL_DestroyWindow(window);
    window= NULL;
  }

  SDL_Quit();                                                                                                                                                 
}


void ran_nb(int *n){
    *n = rand()%MAX;
}

int main(int argc, char** argv) {
  (void)argc;
  (void)argv;

  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;

  SDL_bool program_on = SDL_TRUE;
  SDL_Event event;


 // Gestion de l'échec
  if (SDL_Init(SDL_INIT_VIDEO) != 0){
    end_sdl(0, "ERROR SDL INIT", window, renderer);
    exit(EXIT_FAILURE);
    }


  //Création de la fenêtre
  window = SDL_CreateWindow("Premier dessin",0,0, 700,700,SDL_WINDOW_OPENGL);
  if (window == NULL) end_sdl(0, "ERROR WINDOW CREATION", window, renderer);

  //Création du renderer
  renderer = SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == NULL){
    end_sdl(0, "ERRORE RENDERER CREATION", window, renderer);
    exit(EXIT_FAILURE);
  }

  // draw(renderer);
  // SDL_RenderPresent(renderer);
  // SDL_PumpEvents();
  // SDL_Delay(10);

  while (program_on){

      if (SDL_PollEvent(&event)){
          switch(event.type){
            case SDL_QUIT:
                program_on = SDL_FALSE;
            break;
            default:
            break;
          }


        int a,b,c,d;
        ran_nb(&a);
        ran_nb(&b);
        ran_nb(&c);
        ran_nb(&d);

        SDL_SetRenderDrawColor(renderer,204, 219, 89,255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 176, 123, 5, 255);
        SDL_RenderDrawLine(renderer,0+a, 0+b,700-c, 700-d);
        printf("valeur de a %d, de b %d, de c %d, et de d %d\n",a,b,c,d);

        SDL_RenderPresent(renderer);
        SDL_PumpEvents();
        SDL_Delay(70);
      }
  }


  // fermeture de la SDL
  end_sdl(1, "Normal ending", window, renderer);
  return EXIT_SUCCESS;
}