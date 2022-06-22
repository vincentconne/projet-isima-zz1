#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// void end_sdl(SDL_Texture *texture, SDL_Window *fenetre, SDL_Renderer *renderer)
// {
//     SDL_DestroyTexture(texture);

//     SDL_DestroyRenderer(renderer);

//     SDL_DestroyWindow(fenetre);

//     IMG_Quit();

//     SDL_Quit();
// }

void afficher_fond(SDL_Texture *texture, SDL_Window *fenetre, SDL_Renderer *renderer)
{
    SDL_Rect
        source = {0},            // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};       // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(
        fenetre, &window_dimensions.w,
        &window_dimensions.h); // Récupération des dimensions de la fenêtre
    SDL_QueryTexture(texture, NULL, NULL,
                     &source.w, &source.h); // Récupération des dimensions de l'image

    destination = window_dimensions; // On fixe les dimensions de l'affichage à  celles de la fenêtre

    /* On veut afficher la texture de façon à ce que l'image occupe la totalité de la fenêtre */

    SDL_RenderCopy(renderer, texture,
                   &source,
                   &destination); // Création de l'élément à afficher
}

void anim_texture(SDL_Texture *texture, SDL_Window *fenetre, SDL_Renderer *renderer, SDL_Texture *fond)
{
    SDL_Rect
        source = {0},
        window_dimensions = {0},
        destination = {0},
        state = {0};

    // Récupération des dimensions de la fenetre
    SDL_GetWindowSize(fenetre, &window_dimensions.w, &window_dimensions.h);

    // Récupération des dimensions de la fenetre
    SDL_QueryTexture(texture, NULL, NULL, &source.w, &source.h);

    int nb_images_ligne = 8;
    int nb_lignes = 3;
    float zoom = 2;

    int offset_x = source.w / nb_images_ligne;
    int offset_y = source.h / nb_lignes;

    state.x = 0;
    state.y = 0 * offset_y;
    state.w = offset_x;
    state.h = offset_y;

    destination.w = offset_x * zoom;
    destination.h = offset_y * zoom;

    destination.y = (window_dimensions.h - destination.h) / 1.3;

    int speed = 50;
    for (int x = 0; x < window_dimensions.w - destination.w; x += speed)
    {
        destination.x = x;
        state.x += offset_x;
        state.x %= source.w;

        afficher_fond(fond, fenetre, renderer);
        SDL_RenderCopy(renderer, texture,
                       &state,
                       &destination);
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }
    SDL_RenderClear(renderer);
}



int main(void)
{
    // Variables
    SDL_bool prog_on = SDL_TRUE;

    SDL_Event event;

    // Creation de la fenetre
    SDL_Window *fenetre = NULL;
    fenetre = SDL_CreateWindow("Animation Sprite", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_OPENGL);
    if (fenetre == NULL)
    {
        exit(EXIT_FAILURE);
    }

    // Creation du renderer
    SDL_Renderer *renderer = NULL;
    renderer = SDL_CreateRenderer(fenetre, -1,
                                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        exit(EXIT_FAILURE);
    }

    // Creation et chargement de la texture
    SDL_Texture *texture = NULL;
    texture = IMG_LoadTexture(renderer, "./sprite.png");
    if (texture == NULL)
        exit(EXIT_FAILURE);

    SDL_Texture *fond = NULL;
    fond = IMG_LoadTexture(renderer, "./fond.png");
    if (texture == NULL)
        exit(EXIT_FAILURE);

    SDL_bool interessant = SDL_FALSE;

    // Boucle de jeu
    while (prog_on)
    {
        while (SDL_PollEvent(&event) && !interessant)
        {
            switch (event.type)
            {
            case SDL_QUIT:
                prog_on = SDL_FALSE;
                interessant = SDL_TRUE;
                break;

            default:
                break;
            }
        }
        interessant = SDL_FALSE;
        anim_texture(texture, fenetre, renderer, fond);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(fenetre);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
