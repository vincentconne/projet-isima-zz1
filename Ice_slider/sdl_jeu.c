// ******************************************* //
// FICHIER c POUR LE FONCTIONNEMENT DU JEU (SDL)
// ******************************************* //

// IMPORTS
#include "sdl_jeu.h"

// FONCTIONS

// ----------------- //
// Fonction de jeu SDL
// ----------------- //
void sdlJeu()
{
    int stop = 0;
    int sortie = 0;

    // Tableau représentant la grille de jeu
    int tabJeu[9][13] = {{1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1},
                         {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
                         {1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
                         {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1},
                         {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
                         {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
                         {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
                         {1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1},
                         {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1}};

    // Position de l'esquimau au départ
    int posEsquiX = 600;
    int posEsquiY = 800;

    // Position précédente dès que l'on rencontre un obstacle
    int posPrecX;
    int posPrecY;
    int CouplePrec[2] = {0, 0};

    // Action du personnage
    int direction = 8;

    // Diverses variable SDL
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_DisplayMode screen;
    SDL_Event event;
    SDL_bool programOn = SDL_TRUE;

    // Textures SDL
    SDL_Texture *fond;
    SDL_Texture *roc1;
    SDL_Texture *esquimauU;
    SDL_Texture *esquimauR;
    SDL_Texture *esquimauL;
    SDL_Texture *esquimauD;
    SDL_Texture *esquimau;
    SDL_Texture *top_bot_mur;
    SDL_Texture *side_mur;
    SDL_Texture *text_textureSortieTrouvee;

    // Rectangles SDL
    SDL_Rect rect_roc[13];
    SDL_Rect rect_mur[6];
    SDL_Rect rect_esquimau;

    // Initialisation des composants SDL
    initSDL(window, renderer);

    // Récupération taille écran
    SDL_GetCurrentDisplayMode(0, &screen);

    // Création window et renderer
    window = SDL_CreateWindow("Ice Slider",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, width,
                              height,
                              SDL_WINDOW_OPENGL);
    if (NULL == window)
        endSdl(0, "ERROR WINDOW", window, renderer);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
        endSdl(0, "ERROR RENDERER", window, renderer);

    // Création des textures
    esquimauU = IMG_LoadTexture(renderer, "./src/static_forward.png");
    esquimauR = IMG_LoadTexture(renderer, "./src/static_right.png");
    esquimauL = IMG_LoadTexture(renderer, "./src/static_left.png");
    esquimauD = IMG_LoadTexture(renderer, "./src/static_down.png");
    esquimau = esquimauU;
    top_bot_mur = IMG_LoadTexture(renderer, "./src/top_bot_mur.png");
    side_mur = IMG_LoadTexture(renderer, "./src/side_mur.png");

    // Rectangle du personnage
    rect_esquimau.x = 600;
    rect_esquimau.y = 800;
    rect_esquimau.w = 100;
    rect_esquimau.h = 100;

    // Création du fond
    fond = loadTextureFromImage("./src/fond_glace.png", renderer);
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

    // Création des murs et rochers
    roc1 = IMG_LoadTexture(renderer, "./src/rocher.png");
    initRoc(rect_roc);
    initMur(rect_mur);

    SDL_Surface *SortieTrouvee = AffichageSortie();
    text_textureSortieTrouvee = SDL_CreateTextureFromSurface(renderer, SortieTrouvee); // transfert de la surface à la texture de SortieTrouvee
    if (text_textureSortieTrouvee == NULL)
    {
        endSdl(0, "ERROR TEXTURE", window, renderer);
    }
    SDL_FreeSurface(SortieTrouvee); // la texture ne sert plus à rien

    int fin = 1;
    // Boucle de jeu
    while (programOn && stop == 0 && fin)
    { // Voilà la boucle des évènements

        while (SDL_PollEvent(&event))
        {

            if (event.type == SDL_KEYDOWN)
            {
                // Déplacement de l'esquimau
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_SPACE:
                    break;
                case SDL_SCANCODE_LEFT:
                    esquimau = esquimauL;

                    direction = 1;

                    recherche1(tabJeu, direction, posEsquiX, posEsquiY, CouplePrec);
                    posPrecX = CouplePrec[1] * 100;
                    posPrecY = CouplePrec[0] * 100;

                    break;
                case SDL_SCANCODE_RIGHT:
                    esquimau = esquimauR;

                    direction = 3;

                    recherche1(tabJeu, direction, posEsquiX, posEsquiY, CouplePrec);
                    posPrecX = (CouplePrec[1] * 100);
                    posPrecY = CouplePrec[0] * 100;

                    break;
                case SDL_SCANCODE_UP:
                    esquimau = esquimauU;

                    direction = 2;
                    recherche1(tabJeu, direction, posEsquiX, posEsquiY, CouplePrec);
                    posPrecX = CouplePrec[1] * 100;
                    posPrecY = CouplePrec[0] * 100;

                    break;
                case SDL_SCANCODE_DOWN:
                    esquimau = esquimauD;

                    direction = 0;
                    recherche1(tabJeu, direction, posEsquiX, posEsquiY, CouplePrec);
                    posPrecX = CouplePrec[1] * 100;
                    posPrecY = CouplePrec[0] * 100;

                    break;
                default:
                    break;
                }
            }
            else if (event.type == SDL_QUIT)
            {
                programOn = SDL_FALSE;
                fin = 0;
                puts("FIN DE MON PROGRAMME");
                break;
            }
        }

        // Affichage du fond
        SDL_RenderCopy(renderer, fond, &source, &destination);

        // Affichage des rochers
        for (int i = 0; i < 13; i++)
        {
            SDL_RenderCopy(renderer, roc1, NULL, &rect_roc[i]);
        }

        // Affichage des murs
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
            sortie = 3;
        }
        if (sortie == 3)
        {
            draw(renderer, 500, 425, text_textureSortieTrouvee);
        }
        else
        {
            SDL_RenderCopy(renderer, esquimau, NULL, &rect_esquimau);
        }
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(fond);
    SDL_DestroyTexture(roc1);
    SDL_DestroyTexture(esquimauU);
    SDL_DestroyTexture(esquimauR);
    SDL_DestroyTexture(esquimauL);
    SDL_DestroyTexture(esquimauD);
    SDL_DestroyTexture(esquimau);
    SDL_DestroyTexture(top_bot_mur);
    SDL_DestroyTexture(side_mur);
    SDL_DestroyTexture(text_textureSortieTrouvee);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// ----------------------------------------- //
// Fonction de l'intelligence artificielle SDL
// ----------------------------------------- //
void sdlIA()
{
    // Initialisation des tables
    int run[NBITEPO][4];
    float qsa[NBLIGNESMAP * NBCOLMAP][6];
    initQsa(qsa, NBLIGNESMAP, NBCOLMAP, 0);

    // Initialisation de epsilon (e-greedy)
    float eps = 1.0;

    // Initialisation de la matrice générant la carte
    int TabJeu[9][13] = {{1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1},
                         {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
                         {1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
                         {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1},
                         {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
                         {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
                         {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
                         {1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1},
                         {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1}};

    // Initialisation des positions
    int posEsquiX = 600;
    int posEsquiY = 800;

    // Variables de calcul
    int posPrecX;
    int posPrecY;
    int CouplePrec[2] = {0, 0};
    int direction = 8;
    int sortie = 1;

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_DisplayMode screen;
    SDL_Event event;
    SDL_bool programOn = SDL_TRUE;

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
    SDL_Texture *text_textureSortieTrouvee;

    // Rectangles
    SDL_Rect rectRoc[13];
    SDL_Rect rectMur[6];
    SDL_Rect rectEsquimau;

    // Initialisation des composants
    initSDL(window, renderer);

    // Récupération taille écran
    SDL_GetCurrentDisplayMode(0, &screen);

    window = SDL_CreateWindow("Ice Slider",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, width,
                              height,
                              SDL_WINDOW_OPENGL);
    if (NULL == window)
        endSdl(0, "ERROR WINDOW", window, renderer);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
        endSdl(0, "ERROR RENDERER", window, renderer);

    esquimauU = IMG_LoadTexture(renderer, "./src/static_forward.png");
    esquimauR = IMG_LoadTexture(renderer, "./src/static_right.png");
    esquimauL = IMG_LoadTexture(renderer, "./src/static_left.png");
    esquimauD = IMG_LoadTexture(renderer, "./src/static_down.png");
    esquimau = esquimauU;
    top_bot_mur = IMG_LoadTexture(renderer, "./src/top_bot_mur.png");
    side_mur = IMG_LoadTexture(renderer, "./src/side_mur.png");

    rectEsquimau.x = 600;
    rectEsquimau.y = 800;
    rectEsquimau.w = 100;
    rectEsquimau.h = 100;

    fond = loadTextureFromImage("./src/fond_glace.png", renderer);
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
    initRoc(rectRoc);
    initMur(rectMur);

    // Variables de boucle
    int j = 0;
    int i = 0;
    SDL_Surface *SortieTrouvee = AffichageSortie();
    text_textureSortieTrouvee = SDL_CreateTextureFromSurface(renderer, SortieTrouvee); // transfert de la surface à la texture de SortieTrouvee
    if (text_textureSortieTrouvee == NULL)
    {
        endSdl(0, "ERROR TEXTURE", window, renderer);
    }
    SDL_FreeSurface(SortieTrouvee); // la texture ne sert plus à rien
    int cpt = 0;

    // Boucle d'époque
    for (i = 0; i < NBEPOQUE; i++)
    {
        // Boucle des itérations
        while (programOn && sortie && j < NBITEPO)
        {
            // Choix de la nouvelle direction
            direction = eGreedy(qsa, &eps, posEsquiX, posEsquiY);
            // Calcul de l'état suivant
            recherche1(TabJeu, direction, posEsquiX, posEsquiY, CouplePrec);
            // Sauvegarde dans la table run
            run[j][0] = posEsquiX;
            run[j][1] = posEsquiY;
            run[j][2] = direction;
            run[j][3] = getReward(posEsquiX, posEsquiY);
            // On passe à l'étude de l'état suivant
            posEsquiX = CouplePrec[1] * 100;
            posEsquiY = CouplePrec[0] * 100;
            j++;
            // On est à la sortie
            if (posEsquiX == 600 && posEsquiY == 0)
            {
                sortie = 0;
                cpt++;
                run[j][0] = posEsquiX;
                run[j][1] = posEsquiY;
                run[j][2] = -1;
                run[j][3] = getReward(posEsquiX, posEsquiY);
            }
        }
        // Si jamais on a pas trouvé la sortie on décrémente j
        if (sortie)
        {
            j--;
        }
        // On met à jour QSA
        apprentissageQSA(qsa, run, j);
        // Remise à zéro des indices et de la position de l'esquimau
        j = 0;
        sortie = 1;
        posEsquiX = 600;
        posEsquiY = 800;
    }
    printf("Nombre de fois où la sortie a été trouvé : %d\n", cpt);

    int finMouvement = 1;
    j = 0;
    int fin = 1;

    // Boucle d'affichage
    while (programOn && j < NBITEPO && fin)
    {
        while (SDL_PollEvent(&event))
        {
            // Si on veut quitter la fenêtre
            if (event.type == SDL_QUIT)
            {
                programOn = SDL_FALSE;
                fin = 0;
                puts("FIN DE MON PROGRAMME");
                break;
            }
        }
        if (programOn == SDL_TRUE)
        {
            // On fait un choix de direction par décision sur la table de QSA
            direction = choixActionQSA(qsa, posEsquiX, posEsquiY);
            j++;

            // Calcul nouvelle position
            recherche1(TabJeu, direction, posEsquiX, posEsquiY, CouplePrec);
            posPrecX = CouplePrec[1] * 100;
            posPrecY = CouplePrec[0] * 100;

            // Affichage du personnage selon la direction
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
                if (direction == 2 && posEsquiY != posPrecY)
                {
                    rectEsquimau.y -= VITESSEIA;
                    posEsquiY -= VITESSEIA;
                }
                else if (direction == 2 && posEsquiY == posPrecY)
                {
                    finMouvement = 0;
                }
                else if (direction == 0 && posEsquiY != posPrecY)
                {
                    rectEsquimau.y += VITESSEIA;
                    posEsquiY += VITESSEIA;
                }
                else if (direction == 0 && posEsquiY == posPrecY)
                {
                    finMouvement = 0;
                }
                else if (direction == 1 && posEsquiX != posPrecX)
                {
                    rectEsquimau.x -= VITESSEIA;
                    posEsquiX -= VITESSEIA;
                }
                else if (direction == 1 && posEsquiX == posPrecX)
                {
                    finMouvement = 0;
                }
                else if (direction == 3 && posEsquiX != posPrecX)
                {
                    rectEsquimau.x += VITESSEIA;
                    posEsquiX += VITESSEIA;
                }
                else if (direction == 3 && posEsquiX == posPrecX)
                {
                    finMouvement = 0;
                }

                // Affichage du fond
                SDL_RenderCopy(renderer, fond, &source, &destination);

                // Affichage des rochers
                for (int i = 0; i < 13; i++)
                {
                    SDL_RenderCopy(renderer, roc1, NULL, &rectRoc[i]);
                }

                for (int i = 0; i < 2; i++)
                {
                    SDL_RenderCopy(renderer, side_mur, NULL, &rectMur[i]);
                }
                for (int i = 2; i < 6; i++)
                {
                    SDL_RenderCopy(renderer, top_bot_mur, NULL, &rectMur[i]);
                }

                if (posEsquiX == 600 && posEsquiY == 0)
                {
                    sortie = 0;
                }
                if (sortie == 0)
                {
                    draw(renderer, 500, 425, text_textureSortieTrouvee);
                }
                else
                {
                    SDL_RenderCopy(renderer, esquimau, NULL, &rectEsquimau);
                }
                SDL_PumpEvents();
                SDL_RenderPresent(renderer);
            }
        }
    }
    SDL_DestroyTexture(fond);
    SDL_DestroyTexture(roc1);
    SDL_DestroyTexture(esquimauU);
    SDL_DestroyTexture(esquimauR);
    SDL_DestroyTexture(esquimauL);
    SDL_DestroyTexture(esquimauD);
    SDL_DestroyTexture(esquimau);
    SDL_DestroyTexture(top_bot_mur);
    SDL_DestroyTexture(side_mur);
    SDL_DestroyTexture(text_textureSortieTrouvee);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// ---------------------- //
// Fonction de menu du jeu
// ----------------------- //
void introJeu()
{
    int stop = 0;

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_DisplayMode screen;
    SDL_Event event;
    SDL_bool programOn = SDL_TRUE;

    // Textures
    SDL_Texture *fond;

    // Initialisation des composants
    initSDL(window, renderer);

    SDL_GetCurrentDisplayMode(0, &screen);

    // Création de la fenêtre
    window = SDL_CreateWindow("Ice Slider",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, width,
                              height,
                              SDL_WINDOW_OPENGL);

    if (NULL == window)
        endSdl(0, "ERROR WINDOW", window, renderer);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
        endSdl(0, "ERROR RENDERER", window, renderer);

    // Création de la texture de fond
    fond = loadTextureFromImage("./src/menu_ice_slider.png", renderer);
    if (fond == NULL)
        endSdl(0, "ERROR TEXTURE", window, renderer);

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
        endSdl(0, "ERROR TEXTURE", window, renderer);

    TTF_Font *font = NULL, *font2 = NULL;             // la variable 'police de caractère'
    font = TTF_OpenFont("./src/SnowtopCaps.otf", 70); // La police à charger, la taille désirée
    font2 = TTF_OpenFont("./src/SnowtopCaps.otf", 70);
    if (font == NULL)
        endSdl(0, "ERROR TEXTURE", window, renderer);
    if (font2 == NULL)
        endSdl(0, "ERROR TEXTURE", window, renderer);

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
    int finClique = 0;
    int SourisX = 0;
    int SourisY = 0;
    while (programOn && stop == 0)
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
                    SDL_Color color = {116, 165, 241, 255};                                // la couleur du texte
                    text_surface1 = TTF_RenderText_Blended(font, "JOUER", color);          // création du texte dans la surface
                    text_texture1 = SDL_CreateTextureFromSurface(renderer, text_surface1); // transfert de la surface à la texture
                }
                else if (700 < SourisX && SourisX < 1050 &&
                         650 < SourisY && SourisY < 800) // La souris est dans le réctangle IA //
                {
                    SDL_Color color = {116, 165, 241, 255};                     // la couleur du texte
                    text_surface2 = TTF_RenderText_Blended(font2, "IA", color); // création du texte dans la surface
                    text_texture2 = SDL_CreateTextureFromSurface(renderer, text_surface2);
                }
                else
                {
                    SDL_Color color = {255, 255, 255, 255};                                // la couleur du texte
                    text_surface1 = TTF_RenderText_Blended(font, "JOUER", color);          // création du texte dans la surface
                    text_texture1 = SDL_CreateTextureFromSurface(renderer, text_surface1); // transfert de la surface à la texture
                    text_surface2 = TTF_RenderText_Blended(font2, "IA", color);            // création du texte dans la surface
                    text_texture2 = SDL_CreateTextureFromSurface(renderer, text_surface2);
                }
                break;

            case SDL_QUIT:             // Un évènement simple, on a cliqué sur la x de la fenêtre
                programOn = SDL_FALSE; // Il est temps d'arrêter le programme
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
            sdlJeu();
            stop = 1;
        }
        else if (finClique == 2) // Clique Jeu IA
        {
            SDL_DestroyTexture(text_texture1);
            SDL_DestroyTexture(text_texture2);
            SDL_DestroyWindow(window);
            TTF_Quit();
            sdlIA();
            stop = 1;
        }

        SDL_RenderPresent(renderer); // affichage
    }
    SDL_FreeSurface(text_surface1);
    SDL_FreeSurface(text_surface2);
    SDL_DestroyTexture(text_texture1);
    SDL_DestroyTexture(text_texture2);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}