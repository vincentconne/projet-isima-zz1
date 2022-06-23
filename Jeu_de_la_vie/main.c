#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "jeu.h"
#include "sdl_jeu.h"
#include "texture.h"


#define width 600
#define height 500

int main()
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    int statut = EXIT_FAILURE;
    SDL_DisplayMode screen;
    int stop = 0;


    if (0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_GetCurrentDisplayMode(0, &screen);

    window = SDL_CreateWindow("Premier dessin",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, width,
                              height,
                              SDL_WINDOW_OPENGL);
    if (NULL == window)
    {
        fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    renderer = SDL_CreateRenderer(window, -1,
                                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        exit(EXIT_FAILURE);
    }

    statut = EXIT_SUCCESS;


    SDL_bool program_on = SDL_TRUE; // Booléen pour dire que le programme doit continuer
    SDL_Event event;                // c'est le type IMPORTANT !!
    SDL_GetCurrentDisplayMode(0, &screen);

    SDL_Texture *fond; 
    fond = load_texture_from_image("./up.png",window,renderer);
    SDL_Rect 
          source = {0},                         // Rectangle définissant la zone de la texture à récupérer
          window_dimensions = {0},              // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
          destination = {0};                    // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(
      window, &window_dimensions.w,
      &window_dimensions.h);                    // Récupération des dimensions de la fenêtre
    SDL_QueryTexture(fond, NULL, NULL,
                   &source.w, &source.h);       // Récupération des dimensions de l'image

    destination = window_dimensions;              // On fixe les dimensions de l'affichage à  celles de la fenêtre


    


    if (TTF_Init() < 0)
    {
        fprintf(stderr, "Erreur SDL_TTF : %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    TTF_Font *font = NULL;                 // la variable 'police de caractère'
    font = TTF_OpenFont("stocky.ttf", 55); // La police à charger, la taille désirée
    if (font == NULL)
    {
        fprintf(stderr, "Erreur SDL_TTF : %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    TTF_SetFontStyle(font, TTF_STYLE_ITALIC); // en italique, gras

    SDL_Color color = {255, 255, 255, 255};                                // la couleur du texte
    SDL_Surface *text_surface1 = NULL;                                     // la surface  (uniquement transitoire)
    text_surface1 = TTF_RenderText_Blended(font, "Monde Delimite", color); // création du texte dans la surface
    SDL_Surface *text_surface2 = NULL;                                     // la surface  (uniquement transitoire)
    text_surface2 = TTF_RenderText_Blended(font, "Monde Torique", color);  // création du texte dans la surface
    if (text_surface1 == NULL && text_surface2 == NULL)
    {
        fprintf(stderr, "Erreur SDL_TTF : %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_Texture *text_texture1 = NULL;                                     // la texture qui contient le texte
    text_texture1 = SDL_CreateTextureFromSurface(renderer, text_surface1); // transfert de la surface à la texture
    SDL_Texture *text_texture2 = NULL;                                     // la texture qui contient le texte
    text_texture2 = SDL_CreateTextureFromSurface(renderer, text_surface2); // transfert de la surface à la texture
    if (text_texture1 == NULL && text_texture2)
    {
        fprintf(stderr, "Erreur SDL_TTF : %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FreeSurface(text_surface1); // la texture ne sert plus à rien
    SDL_FreeSurface(text_surface2); // la texture ne sert plus à rien
    int bool = 0;
    while (program_on && stop == 0)
    { // Voilà la boucle des évènements

        if (SDL_PollEvent(&event))
        { // si la file d'évènements n'est pas vide : défiler l'élément en tête
          // de file dans 'event'
            switch (event.type)
            {
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT && 0 < event.button.x && event.button.x < 600 &&
                    220 < event.button.y && event.button.y < 320)
                {
                    printf("Monde Delimite\n");
                    bool = 2;
                }
                else if (event.button.button == SDL_BUTTON_LEFT && 0 < event.button.x && event.button.x < 600 &&
                         350 < event.button.y && event.button.y < 450)
                {
                    printf("Monde Torique\n");
                    bool = 1;
                }
                break;

            case SDL_QUIT:              // Un évènement simple, on a cliqué sur la x de la fenêtre
                program_on = SDL_FALSE; // Il est temps d'arrêter le programme
                break;

            default: // Si L'évènement défilé ne nous intéresse pas
                break;
            }
        }
        if (bool == 0)
        {
            SDL_RenderCopy(renderer, fond,
                 &source,
                 &destination);
            draw(renderer, 0, 220, text_texture1);
            draw(renderer, 0, 350, text_texture2);
        }
        else
        {
            SDL_DestroyTexture(text_texture1);
            SDL_DestroyTexture(text_texture2);
            SDL_DestroyWindow(window);
            TTF_Quit();
            jeu(bool);
            stop = 1;
        }

        SDL_RenderPresent(renderer); // affichage
    }

    SDL_DestroyTexture(text_texture1);
    SDL_DestroyTexture(text_texture2);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return statut;
}