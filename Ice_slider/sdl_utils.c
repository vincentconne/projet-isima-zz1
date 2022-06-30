// ************************************* //
// FICHIER C FONCTIONS UTILES POUR SDL
// ************************************* //

// IMPORTS
#include "sdl_utils.h"

// FONCTIONS

// ----------------------- //
// Initialisation de la SDL2
// ----------------------- //
void initSDL(SDL_Window *window, SDL_Renderer *renderer)
{
    if (0 != SDL_Init(SDL_INIT_VIDEO))
    {
        endSdl(0, "ERROR SDL INIT", window, renderer);
    }
}

// ----------------------- //
// Chargement d'une texture
// ----------------------- //
SDL_Texture *loadTextureFromImage(char *fileImageName, SDL_Renderer *renderer)
{
  SDL_Surface *myImage = NULL;   // Variable de passage
  SDL_Texture *myTexture = NULL; // La texture

  myImage = IMG_Load(fileImageName); // Chargement de l'image dans la surface
                                        // image=SDL_LoadBMP(file_image_name); fonction standard de la SDL,
                                        // uniquement possible si l'image est au format bmp */
  if (myImage == NULL)
  {
    fprintf(stderr, "Erreur IMG_LoadTexture : %s", SDL_GetError());
    exit(EXIT_FAILURE);
  };

  myTexture = SDL_CreateTextureFromSurface(renderer, myImage); // Chargement de l'image de la surface vers la texture
  SDL_FreeSurface(myImage);                                     // la SDL_Surface ne sert que comme élément transitoire
  if (myTexture == NULL)
  {
    fprintf(stderr, "Erreur SSL_CreateTextureFromSurface : %s", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  return myTexture;
}

// Gestion des erreurs et fin SDL
void endSdl(char ok, char const *msg, SDL_Window *window, SDL_Renderer *renderer)
{
  char msg_formated[255];
  int l;

  if (!ok)
  {
    strncpy(msg_formated, msg, 250);
    l = strlen(msg_formated);
    strcpy(msg_formated + l, " : %s\n");

    SDL_Log(msg_formated, SDL_GetError());
  }

  if (renderer != NULL)
  {
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
  }
  if (window != NULL)
  {
    SDL_DestroyWindow(window);
    window = NULL;
  }

  SDL_Quit();
}

void draw(SDL_Renderer *renderer, int xg, int yg, SDL_Texture *text_texture)
{
    SDL_Rect rectangle;

    rectangle.x = xg;  // x haut gauche du rectangle
    rectangle.y = yg;  // y haut gauche du rectangle
    rectangle.w = 100; // sa largeur (w = width)
    rectangle.h = 100; // sa hauteur (h = height)

    SDL_QueryTexture(text_texture, NULL, NULL, &rectangle.w, &rectangle.h); // récupération de la taille (w, h) du texte
    SDL_RenderCopy(renderer, text_texture, NULL, &rectangle);
}