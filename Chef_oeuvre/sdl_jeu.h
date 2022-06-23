#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#ifndef sdl_jeu_h
#define sdl_jeu_h

void sdl_Jeu(int premier, int dernier, int **tab_etats, int etat_cour[3], int tab_markov[][7]);
void Intro_jeu(int premier, int dernier, int **tab_etats, int etat_cour[3], int tab_markov[][7]);
void play_with_texture_1(SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer);
void draw(SDL_Renderer *renderer, int xg, int yg, SDL_Texture *text_texture);
SDL_bool Collision(SDL_Rect tab_etats[5][3], SDL_Rect rect_voiture);
SDL_Texture* update_score(TTF_Font *font, SDL_Color *color, SDL_Renderer *renderer);
void draw_score(SDL_Renderer *renderer, int xg, int yg, SDL_Texture *text_texture);

#endif