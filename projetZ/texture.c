// IMPORTS SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

// IMPORTS STANDARDS
#include <stdio.h>
#include <stdlib.h>

// Chargement d'une texture
SDL_Texture* load_texture_from_image(char *file_image_name, SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_Surface *my_image = NULL;   // Variable de passage
    SDL_Texture *my_texture = NULL; // La texture

    my_image = IMG_Load(file_image_name); // Chargement de l'image dans la surface
                                          // image=SDL_LoadBMP(file_image_name); fonction standard de la SDL,
                                          // uniquement possible si l'image est au format bmp */
    if (my_image == NULL)
    {
        fprintf(stderr, "Erreur IMG_LoadTexture : %s", SDL_GetError());
        exit(EXIT_FAILURE);
    };

    my_texture = SDL_CreateTextureFromSurface(renderer, my_image); // Chargement de l'image de la surface vers la texture
    SDL_FreeSurface(my_image);                                     // la SDL_Surface ne sert que comme élément transitoire
    if (my_texture == NULL)
    {
        fprintf(stderr, "Erreur SSL_CreateTextureFromSurface : %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    return my_texture;
}

// Gestion des erreurs et fin SDL
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