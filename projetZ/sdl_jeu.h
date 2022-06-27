#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#ifndef sdl_jeu_h
#define sdl_jeu_h

int sdl_Jeu(int premier, int dernier, int **tab_etats, int etat_cour[3], int tab_markov[][7]);
void Intro_jeu(int premier, int dernier, int **tab_etats, int etat_cour[3], int tab_markov[][7]);
void play_with_texture_1(SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer);
void draw(SDL_Renderer *renderer, int xg, int yg, SDL_Texture *text_texture);
int collision(int **tab_etats, int position, int dernier);
SDL_Texture* update_score(TTF_Font *font, SDL_Color *color, SDL_Renderer *renderer);
void draw_score(SDL_Renderer *renderer, int xg, int yg, SDL_Texture *text_texture);
SDL_Surface * AffichageEspace();
void fenetre_Fin(int score);

#endif