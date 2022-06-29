#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "jeu.h"
#include "sdl_jeu.h"
#include "texture.h"
#include "ia.h"

// FONCTIONS

// Initialisation de la SDL2
void initSDL(SDL_Window *window, SDL_Renderer *renderer)
{
    if (0 != SDL_Init(SDL_INIT_VIDEO))
    {
        end_sdl(0, "ERROR SDL INIT", window, renderer);
    }
}

// Initialisation du tableau des rochers
void initRoc(SDL_Rect *rect_roc)
{
    for (int i = 0; i < 13; i++)
    {
        rect_roc[i].w = 100;
        rect_roc[i].h = 100;
    }
    rect_roc[0].x = 200;
    rect_roc[0].y = 100;
    rect_roc[1].x = 100;
    rect_roc[1].y = 200;
    rect_roc[2].x = 100;
    rect_roc[2].y = 700;
    rect_roc[3].x = 200;
    rect_roc[3].y = 400;
    rect_roc[4].x = 600;
    rect_roc[4].y = 300;
    rect_roc[5].x = 600;
    rect_roc[5].y = 500;
    rect_roc[6].x = 700;
    rect_roc[6].y = 700;
    rect_roc[7].x = 800;
    rect_roc[7].y = 400;
    rect_roc[8].x = 900;
    rect_roc[8].y = 600;
    rect_roc[9].x = 1000;
    rect_roc[9].y = 100;
    rect_roc[10].x = 1100;
    rect_roc[10].y = 300;
    rect_roc[11].x = 1100;
    rect_roc[11].y = 700;
    rect_roc[12].x = 500;
    rect_roc[12].y = 200;
}

// Initialisation du tableau des murs
void initMur(SDL_Rect *rect_mur)
{
    rect_mur[0].x = 0;
    rect_mur[0].y = 0;
    rect_mur[0].w = 100;
    rect_mur[0].h = 900;
    rect_mur[1].x = 1200;
    rect_mur[1].y = 0;
    rect_mur[1].w = 100;
    rect_mur[1].h = 900;
    rect_mur[2].x = 100;
    rect_mur[2].y = 0;
    rect_mur[2].w = 500;
    rect_mur[2].h = 100;
    rect_mur[3].x = 700;
    rect_mur[3].y = 0;
    rect_mur[3].w = 500;
    rect_mur[3].h = 100;
    rect_mur[4].x = 100;
    rect_mur[4].y = 800;
    rect_mur[4].w = 500;
    rect_mur[4].h = 100;
    rect_mur[5].x = 700;
    rect_mur[5].y = 800;
    rect_mur[5].w = 500;
    rect_mur[5].h = 100;
}

// recherche de 1
void recherche1(int TabJeu[][13], int direction, int posEsquiX, int posEsquiY, int tab_retour[2])
{
    int i = posEsquiY / 100;
    int j = posEsquiX / 100;
    if (direction == 2)
    {
        while (TabJeu[i][j] != 2 && TabJeu[i][j] != 1)
        {
            i--;
        }
        if (TabJeu[i][j] == 2) // Si je suis sur la case de sortie 2
        {
            tab_retour[0] = i;
            tab_retour[1] = j;
        }
        else
        {
            tab_retour[0] = i + 1;
            tab_retour[1] = j;
        }
    }
    else if (direction == 0)
    {
        while (i < 9 && TabJeu[i][j] != 1)
        {
            i++;
        }

        tab_retour[0] = i - 1;
        tab_retour[1] = j;
    }
    else if (direction == 1)
    {
        while (TabJeu[i][j] != 1)
        {
            j--;
        }

        tab_retour[0] = i;
        tab_retour[1] = j + 1;
    }
    else if (direction == 3)
    {
        while (TabJeu[i][j] != 1)
        {
            j++;
        }

        tab_retour[0] = i;
        tab_retour[1] = j - 1;
    }
}

void sdl_Jeu()
{
    int stop = 0;

    int TabJeu[9][13] = {{1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1},
                         {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
                         {1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
                         {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1},
                         {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
                         {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
                         {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
                         {1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1},
                         {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1}};
    int posEsquiX = 600;
    int posEsquiY = 800;
    int posPrecX;
    int posPrecY;
    int CouplePrec[2] = {0, 0};
    int direction = 8;
    int SORTIE = 0;

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_DisplayMode screen;

    SDL_Event event;

    SDL_bool program_on = SDL_TRUE;

    // Textures
    SDL_Texture *fond;
    SDL_Texture *roc1;
    SDL_Texture *esquimauU;
    SDL_Texture *esquimauR;
    SDL_Texture *esquimauL;
    SDL_Texture *esquimauD;
    SDL_Texture *esquimau;
    SDL_Texture *top_bot_mur;
    SDL_Texture *side_mur;

    // Rectangles
    // SDL_Rect entree = {600, 800, 100, 100};
    // SDL_Rect sortie = {600, 0, 100, 100};
    SDL_Rect rect_roc[13];
    SDL_Rect rect_mur[6];
    SDL_Rect rect_esquimau;

    // Initialisation des composants
    initSDL(window, renderer);

    // Récupération taille écran
    SDL_GetCurrentDisplayMode(0, &screen);

    window = SDL_CreateWindow("Projet Z",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, width,
                              height,
                              SDL_WINDOW_OPENGL);
    if (NULL == window)
        end_sdl(0, "ERROR WINDOW", window, renderer);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
        end_sdl(0, "ERROR RENDERER", window, renderer);

    esquimauU = IMG_LoadTexture(renderer, "./src/static_forward.png");
    esquimauR = IMG_LoadTexture(renderer, "./src/static_right.png");
    esquimauL = IMG_LoadTexture(renderer, "./src/static_left.png");
    esquimauD = IMG_LoadTexture(renderer, "./src/static_down.png");
    esquimau = esquimauU;
    top_bot_mur = IMG_LoadTexture(renderer, "./src/top_bot_mur.png");
    side_mur = IMG_LoadTexture(renderer, "./src/side_mur.png");

    rect_esquimau.x = 600;
    rect_esquimau.y = 800;
    rect_esquimau.w = 100;
    rect_esquimau.h = 100;

    fond = load_texture_from_image("./src/fond_glace.png", renderer);
    SDL_Rect
        source = {0},            // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};       // Rectangle définissant où la zone_source doit être déposée dans le renderer
    SDL_GetWindowSize(
        window, &window_dimensions.w,
        &window_dimensions.h); // Récupération des dimensions de la fenêtre
    SDL_QueryTexture(fond, NULL, NULL,
                     &source.w, &source.h); // Récupération des dimensions de l'image
    destination = window_dimensions;        // On fixe les dimensions de l'affichage à  celles de la fenêtre

    roc1 = IMG_LoadTexture(renderer, "./src/rocher.png");

    initRoc(rect_roc);
    initMur(rect_mur);

    // Boucle de jeu
    while (program_on && stop == 0 && SORTIE != 3)
    { // Voilà la boucle des évènements

        while (SDL_PollEvent(&event))
        { // si la file d'évènements n'est pas vide : défiler l'élément en tête
          // de file dans 'event'
            if (event.type == SDL_KEYDOWN)
            {
                // Déplacement de la esquimau
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_SPACE:
                    break;
                case SDL_SCANCODE_LEFT:
                    esquimau = esquimauL;

                    direction = 1;

                    recherche1(TabJeu, direction, posEsquiX, posEsquiY, CouplePrec);
                    posPrecX = CouplePrec[1] * 100;
                    posPrecY = CouplePrec[0] * 100;

                    break;
                case SDL_SCANCODE_RIGHT:
                    esquimau = esquimauR;

                    direction = 3;

                    recherche1(TabJeu, direction, posEsquiX, posEsquiY, CouplePrec);
                    posPrecX = (CouplePrec[1] * 100);
                    posPrecY = CouplePrec[0] * 100;

                    break;
                case SDL_SCANCODE_UP:
                    esquimau = esquimauU;

                    direction = 2;
                    recherche1(TabJeu, direction, posEsquiX, posEsquiY, CouplePrec);
                    posPrecX = CouplePrec[1] * 100;
                    posPrecY = CouplePrec[0] * 100;

                    break;
                case SDL_SCANCODE_DOWN:
                    esquimau = esquimauD;

                    direction = 0;
                    recherche1(TabJeu, direction, posEsquiX, posEsquiY, CouplePrec);
                    posPrecX = CouplePrec[1] * 100;
                    posPrecY = CouplePrec[0] * 100;

                    break;
                default:
                    break;
                }
            }
            else if (event.type == SDL_QUIT)
            {
                program_on = SDL_FALSE;
                puts("FIN DE MON PROGRAMME");
                break;
            }
        }

        // Affichage du fond
        SDL_RenderCopy(renderer, fond, &source, &destination);

        // Affichage des rocks
        for (int i = 0; i < 13; i++)
        {
            SDL_RenderCopy(renderer, roc1, NULL, &rect_roc[i]);
        }

        for (int i = 0; i < 2; i++)
        {
            SDL_RenderCopy(renderer, side_mur, NULL, &rect_mur[i]);
        }
        for (int i = 2; i < 6; i++)
        {
            SDL_RenderCopy(renderer, top_bot_mur, NULL, &rect_mur[i]);
        }

        // Changement de position de l'esquimau (glisse)
        if (direction == 2 && posEsquiY != posPrecY)
        {
            rect_esquimau.y -= VITESSE;
            posEsquiY -= VITESSE;
        }
        else if (direction == 0 && posEsquiY != posPrecY)
        {
            rect_esquimau.y += VITESSE;
            posEsquiY += VITESSE;
        }
        else if (direction == 1 && posEsquiX != posPrecX)
        {
            rect_esquimau.x -= VITESSE;
            posEsquiX -= VITESSE;
        }
        else if (direction == 3 && posEsquiX != posPrecX)
        {
            rect_esquimau.x += VITESSE;
            posEsquiX += VITESSE;
        }

        if (posEsquiX == 600 && posEsquiY == 0)
        {
            SORTIE = 3;
        }
        SDL_RenderCopy(renderer, esquimau, NULL, &rect_esquimau);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(roc1);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void sdl_IA()
{
    int run[NBITEPO][4];

    float qsa[NBLIGNESMAP * NBCOLMAP][6];

    initTabIa(qsa, NBLIGNESMAP, NBCOLMAP, 0);

    int j = 0;
    int i = 0;
    float eps = 1.0;

    // int stop = 0;

    int TabJeu[9][13] = {{1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1},
                         {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
                         {1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
                         {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1},
                         {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
                         {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
                         {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
                         {1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1},
                         {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1}};
    int posEsquiX = 600;
    int posEsquiY = 800;
    int posPrecX;
    int posPrecY;
    int CouplePrec[2] = {0, 0};
    int direction = 8;
    int SORTIE = 1;

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_DisplayMode screen;

    SDL_Event event;

    SDL_bool program_on = SDL_TRUE;

    // Textures
    SDL_Texture *fond;
    SDL_Texture *roc1;
    SDL_Texture *esquimauU;
    SDL_Texture *esquimauR;
    SDL_Texture *esquimauL;
    SDL_Texture *esquimauD;
    SDL_Texture *esquimau;
    SDL_Texture *top_bot_mur;
    SDL_Texture *side_mur;

    // Rectangles
    // SDL_Rect entree = {600, 800, 100, 100};
    // SDL_Rect sortie = {600, 0, 100, 100};
    SDL_Rect rect_roc[13];
    SDL_Rect rect_mur[6];
    SDL_Rect rect_esquimau;

    // Initialisation des composants
    initSDL(window, renderer);

    // Récupération taille écran
    SDL_GetCurrentDisplayMode(0, &screen);

    window = SDL_CreateWindow("Projet Z",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, width,
                              height,
                              SDL_WINDOW_OPENGL);
    if (NULL == window)
        end_sdl(0, "ERROR WINDOW", window, renderer);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
        end_sdl(0, "ERROR RENDERER", window, renderer);

    esquimauU = IMG_LoadTexture(renderer, "./src/static_forward.png");
    esquimauR = IMG_LoadTexture(renderer, "./src/static_right.png");
    esquimauL = IMG_LoadTexture(renderer, "./src/static_left.png");
    esquimauD = IMG_LoadTexture(renderer, "./src/static_down.png");
    esquimau = esquimauU;
    top_bot_mur = IMG_LoadTexture(renderer, "./src/top_bot_mur.png");
    side_mur = IMG_LoadTexture(renderer, "./src/side_mur.png");

    rect_esquimau.x = 600;
    rect_esquimau.y = 800;
    rect_esquimau.w = 100;
    rect_esquimau.h = 100;

    fond = load_texture_from_image("./src/fond_glace.png", renderer);
    SDL_Rect
        source = {0},            // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};       // Rectangle définissant où la zone_source doit être déposée dans le renderer
    SDL_GetWindowSize(
        window, &window_dimensions.w,
        &window_dimensions.h); // Récupération des dimensions de la fenêtre
    SDL_QueryTexture(fond, NULL, NULL,
                     &source.w, &source.h); // Récupération des dimensions de l'image
    destination = window_dimensions;        // On fixe les dimensions de l'affichage à  celles de la fenêtre

    roc1 = IMG_LoadTexture(renderer, "./src/rocher.png");

    initRoc(rect_roc);
    initMur(rect_mur);

    int finMouvement = 1;
    // Boucle des epoques
    for (i = 0; i < NBEPOQUE; i++)
    {
        printf("Période: %d\n", i);
        // Boucle de jeu
        while (program_on && SORTIE && j < NBITEPO)
        { // Voilà la boucle des évènements

            while (SDL_PollEvent(&event))
            { // si la file d'évènements n'est pas vide : défiler l'élément en tête
              // de file dans 'event'
                if (event.type == SDL_QUIT)
                {
                    program_on = SDL_FALSE;
                    puts("FIN DE MON PROGRAMME");
                    break;
                }
            }
            if (program_on == SDL_TRUE)
            {
                // Calculs IA
                direction = eGreedy(qsa, &eps, posEsquiX, posEsquiY);
                // printf("Nouvelle action choisie : %d\n", direction);

                // Sauvegarde etat + action
                run[j][0] = posEsquiX;
                run[j][1] = posEsquiY;
                run[j][2] = direction;
                run[j][3] = getReward(posEsquiX, posEsquiY);
                // run[j][3] = reward[traduc_etat_ligne(posEsquiX,posEsquiY)][direction+2];
                j++;
                // printf("j: %d\n", j);

                // Calcul nouvelle position
                recherche1(TabJeu, direction, posEsquiX, posEsquiY, CouplePrec);
                // printf("La nouvelle position : %d %d\n",CouplePrec[1],CouplePrec[0]);
                posPrecX = CouplePrec[1] * 100;
                posPrecY = CouplePrec[0] * 100;

                switch (direction)
                {
                case 0:
                    esquimau = esquimauD;
                    break;
                case 2:
                    esquimau = esquimauU;
                    break;
                case 1:
                    esquimau = esquimauL;
                    break;
                case 3:
                    esquimau = esquimauR;
                    break;
                default:
                    break;
                }

                finMouvement = 1;
                while (finMouvement)
                {
                    // printf("finMouv : %d \n", finMouvement);
                    if (direction == 2 && posEsquiY != posPrecY)
                    {
                        rect_esquimau.y -= VITESSE;
                        posEsquiY -= VITESSE;
                    }
                    else if (direction == 2 && posEsquiY == posPrecY)
                    {
                        finMouvement = 0;
                    }
                    else if (direction == 0 && posEsquiY != posPrecY)
                    {
                        rect_esquimau.y += VITESSE;
                        posEsquiY += VITESSE;
                    }
                    else if (direction == 0 && posEsquiY == posPrecY)
                    {
                        finMouvement = 0;
                    }
                    else if (direction == 1 && posEsquiX != posPrecX)
                    {
                        rect_esquimau.x -= VITESSE;
                        posEsquiX -= VITESSE;
                    }
                    else if (direction == 1 && posEsquiX == posPrecX)
                    {
                        finMouvement = 0;
                    }
                    else if (direction == 3 && posEsquiX != posPrecX)
                    {
                        rect_esquimau.x += VITESSE;
                        posEsquiX += VITESSE;
                    }
                    else if (direction == 3 && posEsquiX == posPrecX)
                    {
                        finMouvement = 0;
                    }

                    // Affichage du fond
                    SDL_RenderCopy(renderer, fond, &source, &destination);

                    // Affichage des rocks
                    for (int i = 0; i < 13; i++)
                    {
                        SDL_RenderCopy(renderer, roc1, NULL, &rect_roc[i]);
                    }

                    for (int i = 0; i < 2; i++)
                    {
                        SDL_RenderCopy(renderer, side_mur, NULL, &rect_mur[i]);
                    }
                    for (int i = 2; i < 6; i++)
                    {
                        SDL_RenderCopy(renderer, top_bot_mur, NULL, &rect_mur[i]);
                    }

                    if (posEsquiX == 600 && posEsquiY == 0)
                    {
                        SORTIE = 0;
                        run[j][0] = posEsquiX;
                        run[j][1] = posEsquiY;
                        run[j][2] = direction;
                        run[j][3] = getReward(posEsquiX, posEsquiY);
                        // run[j][3] = reward[traduc_etat_ligne(posEsquiX,posEsquiY)][direction+2];
                    }
                    SDL_RenderCopy(renderer, esquimau, NULL, &rect_esquimau);
                    SDL_PumpEvents();
                    SDL_RenderPresent(renderer);
                }
            }
            else
            {
                i = NBEPOQUE + 1;
            }
        }
        // printf("I: %d\n",i);
        // MAJ QSA & REI POS
        apprentissageQSA(qsa, run, j, direction);
        j = 0;
        SORTIE = 1;
        posEsquiX = 600;
        posEsquiY = 800;
        rect_esquimau.x = 600;
        rect_esquimau.y = 800;
    }

    SDL_DestroyTexture(roc1);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Intro_jeu()
{
    int stop = 0;

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_DisplayMode screen;

    SDL_Event event;

    SDL_bool program_on = SDL_TRUE;

    // Textures
    SDL_Texture *fond;

    // Initialisation des composants
    initSDL(window, renderer);

    SDL_GetCurrentDisplayMode(0, &screen);

    // Création de la fenêtre
    window = SDL_CreateWindow("ICE SLIDER",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, width,
                              height,
                              SDL_WINDOW_OPENGL);

    if (NULL == window)
        end_sdl(0, "ERROR WINDOW", window, renderer);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
        end_sdl(0, "ERROR RENDERER", window, renderer);

    // Création de la texture de fond
    fond = load_texture_from_image("./src/menu_ice_slider.png", renderer);
    if (fond == NULL)
        end_sdl(0, "ERROR TEXTURE", window, renderer);

    SDL_Rect
        source = {0},            // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};       // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(
        window, &window_dimensions.w,
        &window_dimensions.h); // Récupération des dimensions de la fenêtre
    SDL_QueryTexture(fond, NULL, NULL,
                     &source.w, &source.h); // Récupération des dimensions de l'image

    destination = window_dimensions; // On fixe les dimensions de l'affichage à  celles de la fenêtre

    if (TTF_Init() < 0)
        end_sdl(0, "ERROR TEXTURE", window, renderer);

    TTF_Font *font = NULL, *font2 = NULL;             // la variable 'police de caractère'
    font = TTF_OpenFont("./src/SnowtopCaps.otf", 70); // La police à charger, la taille désirée
    font2 = TTF_OpenFont("./src/SnowtopCaps.otf", 70);
    if (font == NULL)
        end_sdl(0, "ERROR TEXTURE", window, renderer);
    if (font2 == NULL)
        end_sdl(0, "ERROR TEXTURE", window, renderer);

    TTF_SetFontStyle(font, TTF_STYLE_NORMAL); // en italique, gras

    SDL_Color color = {255, 255, 255, 255};                       // la couleur du texte
    SDL_Surface *text_surface1 = NULL;                            // la surface  (uniquement transitoire)
    text_surface1 = TTF_RenderText_Blended(font, "JOUER", color); // création du texte dans la surface
    SDL_Surface *text_surface2 = NULL;                            // la surface  (uniquement transitoire)
    text_surface2 = TTF_RenderText_Blended(font2, "IA", color);   // création du texte dans la surface
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
    // SDL_FreeSurface(text_surface1); // la texture ne sert plus à rien
    // SDL_FreeSurface(text_surface2); // la texture ne sert plus à rien
    int finClique = 0;
    int SourisX = 0;
    int SourisY = 0;
    while (program_on && stop == 0)
    { // Voilà la boucle des évènements

        if (SDL_PollEvent(&event))
        { // si la file d'évènements n'est pas vide : défiler l'élément en tête
          // de file dans 'event'
            switch (event.type)
            {
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT && 220 < event.button.x && event.button.x < 600 &&
                    650 < event.button.y && event.button.y < 800)
                { // Cas Jeu à la main
                    finClique = 1;
                }
                else if (event.button.button == SDL_BUTTON_LEFT && 700 < event.button.x && event.button.x < 1050 &&
                         650 < event.button.y && event.button.y < 800)
                { // Cas Jeu IA
                    finClique = 2;
                }
                break;
            case SDL_MOUSEMOTION:
                if (220 < SourisX && SourisX < 600 &&
                    650 < SourisY && SourisY < 800) // La souris est dans le réctangle JOUER //
                {
                    SDL_Color color = {116,165,241, 255};                                   // la couleur du texte
                    text_surface1 = TTF_RenderText_Blended(font, "JOUER", color);          // création du texte dans la surface
                    text_texture1 = SDL_CreateTextureFromSurface(renderer, text_surface1); // transfert de la surface à la texture
                }
                else if (700 < SourisX && SourisX < 1050 &&
                         650 < SourisY && SourisY < 800) // La souris est dans le réctangle IA //
                {
                    SDL_Color color = {116,165,241, 255};                        // la couleur du texte
                    text_surface2 = TTF_RenderText_Blended(font2, "IA", color); // création du texte dans la surface
                    text_texture2 = SDL_CreateTextureFromSurface(renderer, text_surface2);
                }
                else
                {
                    SDL_Color color = {255, 255, 255, 255};                        // la couleur du texte
                    text_surface1 = TTF_RenderText_Blended(font, "JOUER", color);          // création du texte dans la surface
                    text_texture1 = SDL_CreateTextureFromSurface(renderer, text_surface1); // transfert de la surface à la texture
                    text_surface2 = TTF_RenderText_Blended(font2, "IA", color); // création du texte dans la surface
                    text_texture2 = SDL_CreateTextureFromSurface(renderer, text_surface2);
                }
                break;

            case SDL_QUIT:              // Un évènement simple, on a cliqué sur la x de la fenêtre
                program_on = SDL_FALSE; // Il est temps d'arrêter le programme
                break;

            default: // Si L'évènement défilé ne nous intéresse pas
                break;
            }
        }
        if (finClique == 0) // Pas encore cliqué
        {
            SDL_GetMouseState(&SourisX, &SourisY);
            SDL_RenderCopy(renderer, fond,
                           &source,
                           &destination);
            draw(renderer, 320, 700, text_texture1);
            draw(renderer, 850, 700, text_texture2);
        }
        else if (finClique == 1) // Clique Jeu à la main
        {
            SDL_DestroyTexture(text_texture1);
            SDL_DestroyTexture(text_texture2);
            SDL_DestroyWindow(window);
            TTF_Quit();
            sdl_Jeu();
            stop = 1;
        }
        else if (finClique == 2) // Clique Jeu IA
        {
            SDL_DestroyTexture(text_texture1);
            SDL_DestroyTexture(text_texture2);
            SDL_DestroyWindow(window);
            TTF_Quit();
            sdl_IA();
            stop = 1;
        }

        SDL_RenderPresent(renderer); // affichage
    }

    SDL_DestroyTexture(text_texture1);
    SDL_DestroyTexture(text_texture2);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

// SDL_FreeSurface(text_surface1); // la texture ne sert plus à rien
//     SDL_FreeSurface(text_surface2); // la texture ne sert plus à rien