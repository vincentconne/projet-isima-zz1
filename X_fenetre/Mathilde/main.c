#include <SDL2/SDL.h>
#include <stdio.h>

int main (int argc, char **argv){

    (void) argc;
    (void) argv;

    SDL_Window *windows_1[14];
    SDL_Window *windows_2[14];

    SDL_DisplayMode screen;
    int i;

    SDL_bool program_on= SDL_TRUE;
    SDL_Event event;

    //Initialisation et gestion d'erreur
    if (SDL_Init(SDL_INIT_VIDEO)!=0){
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_GetCurrentDisplayMode(0, &screen);

    // Création des fenêtres
    for (i=0;i<14; i++){
        windows_1[i] = SDL_CreateWindow("X1", (i+1)*50, (i+1)*50,200+i*10, 200+i*10,SDL_WINDOW_RESIZABLE);
        // Dans l'ordre: nom de la fenêtre (accents possibles), position du point gauche de la fenêtre, 
        //largeur, hauteur, redimensionable

            //Gestion de l'erreur de création de la fenêtre
        if (windows_1[i] == NULL){
            SDL_Log("Error : SDL window creation - %s\n",SDL_GetError());
            SDL_Quit();
            exit(EXIT_FAILURE);
        }
    }

    for (i=0;i<14; i++){
        windows_2[i] = SDL_CreateWindow("X2", 14*50-(i+1)*50, (i+1)*50,200-i*10, 200-i*10,SDL_WINDOW_RESIZABLE);
        // 14*50 correspond à la position de la dernière fenêtre de la première barre

        //Gestion de l'erreur de création de la fenêtre
        if (windows_2[i] == NULL){
            SDL_Log("Error : SDL window creation - %s\n",SDL_GetError());
            SDL_Quit();
            exit(EXIT_FAILURE);
        }
    }

    while(program_on){

        if (SDL_PollEvent(&event)){

            switch (event.type){
                case SDL_QUIT:
                    program_on=SDL_FALSE;
                break;
                case SDL_KEYDOWN:

                    switch (event.key.keysym.sym){
                        case SDLK_SPACE:
                            program_on = 0;
                        break;
                        case SDLK_p:
                            for (i=0; i<14; i++){
                                SDL_SetWindowPosition(windows_1[i],0,0);
                                SDL_SetWindowPosition(windows_2[i], 0, 0);
                            }
                        break;
                        default:
                        break;
                    }
                break;
                default:
                break;
            }
        }

        // Chargement des évènements pour avoir un affichage
        SDL_PumpEvents();

        //Délai d'apparition de la fenêtre en ms
        SDL_Delay(5);
    }

    for (i=0;i<14; i++){
        SDL_DestroyWindow(windows_1[i]);
        SDL_DestroyWindow(windows_2[i]);
    }
    SDL_Quit();

    return 0;
}