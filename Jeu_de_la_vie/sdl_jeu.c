#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL_ttf.h>
#include "jeu.h"
#include "sdl_jeu.h"

void draw(SDL_Renderer *renderer, int xg, int yg, SDL_Texture *text_texture)
{ // Je pense que vous allez faire moins laid :)
	SDL_Rect rectangle;

	SDL_SetRenderDrawColor(renderer,
						   50, 0, 0, // mode Red, Green, Blue (tous dans 0..255)
						   255);	 // 0 = transparent ; 255 = opaque
	rectangle.x = xg;				 // x haut gauche du rectangle
	rectangle.y = yg;				 // y haut gauche du rectangle
	rectangle.w = 600;				 // sa largeur (w = width)
	rectangle.h = 100;				 // sa hauteur (h = height)

	SDL_RenderFillRect(renderer, &rectangle);

	SDL_QueryTexture(text_texture, NULL, NULL, &rectangle.w, &rectangle.h); // récupération de la taille (w, h) du texte
	SDL_RenderCopy(renderer, text_texture, NULL, &rectangle);
}

void DessinCases(SDL_Rect rect, SDL_Renderer *renderer, int **tab)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (tab[i][j] == 0)
			{
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			}
			rect.x = (600 / N) * i;
			rect.y = (600 / N) * j;
			rect.w = rect.h = (600 / N);
			SDL_RenderFillRect(renderer, &rect);
		}
	}
	SDL_RenderPresent(renderer);
}

void sdl_Jeu(int **monde, int **tmp, int indice_fct)
{
	int a = 0;
	int **tab[2] = {monde, tmp};
	int p = 0;

	int vitesse = 1000;

	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_Window *window;
	int width = 600;
	int height = 600;

	window = SDL_CreateWindow("SDL2 Programme 0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
							  width, height,
							  SDL_WINDOW_RESIZABLE);

	if (window == 0)
	{
		fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
		// on peut aussi utiliser SLD_Log()
	}
	SDL_Renderer *renderer;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //  SDL_RENDERER_SOFTWARE
	if (renderer == 0)
	{
		fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
		// faire ce qu'il faut pour quitter proprement
	}

	SDL_Rect rect;

	// couleur de fond
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	// dessiner CASES
	DessinCases(rect, renderer, tab[p]);

	// afficher à l'ecran
	SDL_RenderPresent(renderer);
	int CaseX, CaseY;

	SDL_Event event;
	// while (running && occur < 22)
	// {
	int run = 1;
	int finClique = 0;
	while (run)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_WINDOWEVENT:
				printf("window event\n");
				switch (event.window.event)
				{
				case SDL_WINDOWEVENT_CLOSE:
					printf("appui sur la croix\n");
					break;
				// case SDL_WINDOWEVENT_SIZE_CHANGED:
				// 	width = event.window.data1;
				// 	height = event.window.data2;
				// 	printf("Size : %d%d\n", width, height);
				default:
					DessinCases(rect, renderer, tab[p]);
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				printf("Veuillez choisir la nouvelle couleur : ");
				printf("Appui :%d %d\n", event.button.x, event.button.y);
				CaseX = event.button.x / (600 / N);
				CaseY = event.button.y / (600 / N);

				if (!finClique)
				{
					tab[p][CaseX][CaseY] = 1;
				}
				DessinCases(rect, renderer, tab[p]);

				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_SPACE:
					finClique = 1;
					break;
				default:
					break;
				}

			case SDL_QUIT:
				printf("on quitte\n");
				run = 0;
				break;
			}
		}
		if (finClique)
		{
			while (!a)
			{
				a = tour(tab[p], tab[1 - p], indice_fct);
				p = 1 - p;
				// affiche
				DessinCases(rect, renderer, tab[p]);
				SDL_Delay(vitesse);
				while (SDL_PollEvent(&event))
				{
					switch (event.type)
					{
					case SDL_KEYDOWN:
						switch (event.key.keysym.sym)
						{
						case SDLK_UP:
							vitesse = vitesse / 2;
							break;
						case SDLK_DOWN:
							vitesse = vitesse * 2;
							break;
						case SDLK_s:
							sauvegarde(FIC,tab[p]);
							break;
						default:
							break;
						}
					}
				}
			}
			AfficheMessage(renderer);
		}
		SDL_Delay(100); //  delai minimal
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

// SDL_RenderClear(renderer);

void AfficheMessage(SDL_Renderer *renderer)
{
	SDL_bool program_on = SDL_TRUE; // Booléen pour dire que le programme doit continuer
	SDL_Event event;				// c'est le type IMPORTANT !!
	// SDL_GetCurrentDisplayMode(0, &screen);

	if (TTF_Init() < 0)
	{
		fprintf(stderr, "Erreur SDL_TTF : %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	TTF_Font *font = NULL;				   // la variable 'police de caractère'
	font = TTF_OpenFont("stocky.ttf", 55); // La police à charger, la taille désirée
	if (font == NULL)
	{
		fprintf(stderr, "Erreur SDL_TTF : %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	TTF_SetFontStyle(font, TTF_STYLE_ITALIC | TTF_STYLE_BOLD); // en italique, gras

	SDL_Color color = {255, 255, 255, 255};								 // la couleur du texte
	SDL_Surface *text_surface1 = NULL;									 // la surface  (uniquement transitoire)
	text_surface1 = TTF_RenderText_Blended(font, "MONDE STABLE", color); // création du texte dans la surface
	if (text_surface1 == NULL)
	{
		fprintf(stderr, "Erreur SDL_TTF : %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_Texture *text_texture1 = NULL;									   // la texture qui contient le texte
	text_texture1 = SDL_CreateTextureFromSurface(renderer, text_surface1); // transfert de la surface à la texture

	if (text_texture1 == NULL)
	{
		fprintf(stderr, "Erreur SDL_TTF : %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_FreeSurface(text_surface1); // la texture ne sert plus à rien
	while (program_on)
	{ // Voilà la boucle des évènements
		if (SDL_PollEvent(&event))
		{ // si la file d'évènements n'est pas vide : défiler l'élément en tête
		  // de file dans 'event'
			switch (event.type)
			{
			case SDL_QUIT:				// Un évènement simple, on a cliqué sur la x de la fenêtre
				program_on = SDL_FALSE; // Il est temps d'arrêter le programme
				break;

			default: // L'évènement défilé ne nous intéresse pas
				break;
			}
		}
		draw(renderer, 0, 220, text_texture1);

		SDL_RenderPresent(renderer); // affichage
	}
	SDL_DestroyTexture(text_texture1);
	TTF_Quit();
}