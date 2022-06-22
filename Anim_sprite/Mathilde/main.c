#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//Fonction de gestion des erreurs
void end_sdl(int ok,
             char const* msg,
             SDL_Window* window,
             SDL_Renderer* renderer) {
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

  if (!ok) {
    exit(EXIT_FAILURE);                                                           
  }                                                                               
}


SDL_Texture* load_texture_from_image(char  *  file_image_name, SDL_Window *window, SDL_Renderer *renderer ){
    SDL_Surface *my_image = NULL;
    SDL_Texture* my_texture = NULL;

    //Chargement de l'image
    my_image = IMG_Load(file_image_name);

    // Gestion de d'erreurs de chargement
    if (my_image == NULL) end_sdl(0, "Chargement de l'image impossible", window, renderer);

    // Passage de la surface en texture
    my_texture = SDL_CreateTextureFromSurface(renderer, my_image);
    // Libération de la surface
    SDL_FreeSurface(my_image);
    // Gestion d'erreur de chargement pour la texture
    if (my_texture == NULL) end_sdl(0, "Echec de la transformation de la surface en texture", window, renderer);

    return my_texture;
}

void play_with_texture(SDL_Texture *my_texture, SDL_Window *window,
                         SDL_Renderer *renderer) {
  SDL_Rect 
          source = {0},                         // Rectangle définissant la zone de la texture à récupérer
          window_dimensions = {0},              // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
          destination = {0};                    // Rectangle définissant où la zone_source doit être déposée dans le renderer
  
  SDL_GetWindowSize(
      window, &window_dimensions.w,
      &window_dimensions.h);                    // Récupération des dimensions de la fenêtre
  SDL_QueryTexture(my_texture, NULL, NULL,
                   &source.w, &source.h);       // Récupération des dimensions de l'image

  
  destination = window_dimensions;              // On fixe les dimensions de l'affichage à  celles de la fenêtre
  

  SDL_RenderCopy(renderer, my_texture,
                 &source,
                 &destination);                 // Création de l'élément à afficher
  //SDL_RenderPresent(renderer);                  // Affichage
  // SDL_PumpEvents();
  // SDL_Delay(20);                              // Pause en ms

  //SDL_RenderClear(renderer);                    // Effacer la fenêtre
}


void animation(SDL_Texture *my_texture,SDL_Texture *text_bg,SDL_Window *window, SDL_Renderer *renderer,int i){
    SDL_Rect 
        source = {0},                             // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0},                  // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};
    SDL_GetWindowSize(                                
      window, &window_dimensions.w,                 
      &window_dimensions.h);                      // Récupération des dimensions de la fenêtre
    
    SDL_QueryTexture(my_texture, NULL, NULL,         
                   &source.w,                       
                   &source.h);                    // Récupération des dimensions de l'image

    // Redimensionnement de l'image
    float zoom = 0.5;
    destination.h = source.w*zoom;
    destination.w = source.h*zoom;
    //destination.y = (window_dimensions.w)*(2/3);
    destination.y= 500;
    destination.x = (window_dimensions.w/10)*i;
    
    play_with_texture(text_bg,window,renderer);

    SDL_RenderCopy(renderer,my_texture,&source,&destination);
    // SDL_RenderPresent(renderer);

    // SDL_PumpEvents();
    // SDL_Delay(100);

    // SDL_RenderClear(renderer);

}

int main(){
    SDL_Texture *cha_run[10];
    SDL_Texture *text_bg=NULL;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer=NULL;

    /* Création de la fenêtre */
    window = SDL_CreateWindow("Chat",0,0,700,700,SDL_WINDOW_OPENGL);
    if (window == NULL) end_sdl(0, "ERROR WINDOW CREATION", window, renderer);


    /* Création du renderer */
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) end_sdl(0, "ERROR RENDERER CREATION", window, renderer);

    cha_run[0] = load_texture_from_image("./Run/Run__000.png",window,renderer);
    cha_run[1] = load_texture_from_image("./Run/Run__001.png",window,renderer);
    cha_run[2] = load_texture_from_image("./Run/Run__002.png",window,renderer);
    cha_run[3] = load_texture_from_image("./Run/Run__003.png",window,renderer);
    cha_run[4] = load_texture_from_image("./Run/Run__004.png",window,renderer);
    cha_run[5] = load_texture_from_image("./Run/Run__005.png",window,renderer);
    cha_run[6] = load_texture_from_image("./Run/Run__006.png",window,renderer);
    cha_run[7] = load_texture_from_image("./Run/Run__007.png",window,renderer);
    cha_run[8] = load_texture_from_image("./Run/Run__008.png",window,renderer);
    cha_run[9] = load_texture_from_image("./Run/Run__009.png",window,renderer);

    text_bg= load_texture_from_image("/Users/mathildewalch/Downloads/Run/bg.png",window,renderer);


    for (int i=0; i<10;i++){
      animation(cha_run[i],text_bg,window,renderer,i);
      SDL_RenderPresent(renderer);
      SDL_PumpEvents();
      //SDL_Delay(100);


    SDL_Delay(300);

    }




}