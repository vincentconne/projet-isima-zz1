#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#define width 1000
#define height 800

void draw(SDL_Renderer *renderer, int xg, int yg, SDL_Texture *text_texture)
{ // Je pense que vous allez faire moins laid :)
    SDL_Rect rectangle;

    SDL_SetRenderDrawColor(renderer,
                           50, 0, 0, // mode Red, Green, Blue (tous dans 0..255)
                           255);     // 0 = transparent ; 255 = opaque
    rectangle.x = xg;                // x haut gauche du rectangle
    rectangle.y = yg;                // y haut gauche du rectangle
    rectangle.w = 600;               // sa largeur (w = width)
    rectangle.h = 100;               // sa hauteur (h = height)

    SDL_RenderFillRect(renderer, &rectangle);

    SDL_QueryTexture(text_texture, NULL, NULL, &rectangle.w, &rectangle.h); // récupération de la taille (w, h) du texte
    SDL_RenderCopy(renderer, text_texture, NULL, &rectangle);
}

void play_with_texture_4(SDL_Texture *my_texture,
                         SDL_Window *window,
                         SDL_Renderer *renderer)
{
    SDL_Rect
        source = {0},            // Rectangle définissant la zone totale de la planche
        window_dimensions = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0},       // Rectangle définissant où la zone_source doit être déposée dans le renderer
        state = {0};             // Rectangle de la vignette en cours dans la planche

    SDL_GetWindowSize(window, // Récupération des dimensions de la fenêtre
                      &window_dimensions.w,
                      &window_dimensions.h);
    SDL_QueryTexture(my_texture, // Récupération des dimensions de l'image
                     NULL, NULL,
                     &source.w, &source.h);

    /* Mais pourquoi prendre la totalité de l'image, on peut n'en afficher qu'un morceau, et changer de morceau :-) */

    int nb_images = 4;                   // Il y a 8 vignette dans la ligne de l'image qui nous intéresse
    float zoom = 2;                      // zoom, car ces images sont un peu petites
    int offset_x = source.w / nb_images, // La largeur d'une vignette de l'image, marche car la planche est bien réglée
        offset_y = source.h / 4;         // La hauteur d'une vignette de l'image, marche car la planche est bien réglée

    state.x = 0;            // La première vignette est en début de ligne
    state.y = offset_y/2;//2 * offset_y; // On s'intéresse à la 4ème ligne, le bonhomme qui court
    state.w = offset_x;     // Largeur de la vignette
    state.h = offset_y;     // Hauteur de la vignette

    destination.w = offset_x * zoom; // Largeur du sprite à l'écran
    destination.h = offset_y * zoom; // Hauteur du sprite à l'écran

    destination.y = // La course se fait en milieu d'écran (en vertical)
        (window_dimensions.h - destination.h) / 2;

    int speed = 9;
    for (int x = 0; x < window_dimensions.w - destination.w; x += speed)
    {
        destination.x = x;   // Position en x pour l'affichage du sprite
        state.x += offset_x; // On passe à la vignette suivante dans l'image
        state.x %= source.w; // La vignette qui suit celle de fin de ligne est
                             // celle de début de ligne

        SDL_RenderClear(renderer);           // Effacer l'image précédente avant de dessiner la nouvelle
        SDL_RenderCopy(renderer, my_texture, // Préparation de l'affichage
                       &state,
                       &destination);
        SDL_RenderPresent(renderer); // Affichage
        SDL_Delay(80);               // Pause en ms
    }
    SDL_RenderClear(renderer); // Effacer la fenêtre avant de rendre la main
}

int main()
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    int statut = EXIT_FAILURE;
    SDL_DisplayMode screen;

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

    // SDL_Texture *text_texture1 = load_texture_from_image("Cheetah.png", window, renderer);
    SDL_Texture *text_texture1 = IMG_LoadTexture(renderer, "Cheetah.png");
    if (text_texture1 == NULL)
    {
        exit(EXIT_FAILURE);
    }

    while (program_on)
    { // Voilà la boucle des évènements

        if (SDL_PollEvent(&event))
        { // si la file d'évènements n'est pas vide : défiler l'élément en tête
          // de file dans 'event'
            switch (event.type)
            {

                // En fonction de la valeur du type de cet évènement
            case SDL_QUIT:              // Un évènement simple, on a cliqué sur la x de la fenêtre
                program_on = SDL_FALSE; // Il est temps d'arrêter le programme
                break;

            default: // L'évènement défilé ne nous intéresse pas
                break;
            }
        }
        // draw(renderer, 0, 220, text_texture1);
        play_with_texture_4(text_texture1, window, renderer);
        SDL_RenderPresent(renderer); // affichage
    }

    SDL_DestroyTexture(text_texture1);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return statut;
}