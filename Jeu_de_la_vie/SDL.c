#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "jeu.h"
#include "SDL.h"

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
			rect.x = 50 * i;
			rect.y = 50 * j;
			rect.w = rect.h = 50;
			SDL_RenderFillRect(renderer, &rect);
		}
	}
	SDL_RenderPresent(renderer);
}

void SDL(int **monde, int **tmp, int indice_fct)
{
	int a = 0;
	int **tab[2] = {monde, tmp};
	int p = 0;

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

	int test = 0;
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
				CaseX = event.button.x / 50;
				CaseY = event.button.y / 50;

				if (!finClique)
				{
					tab[p][CaseX][CaseY] = 1;
				}
				DessinCases(rect, renderer, tab[p]);
				// SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				// rect.x = 50 * CaseX;
				// rect.y = 50 * CaseY;
				// rect.w = rect.h = 50;
				// SDL_RenderFillRect(renderer, &rect);
				// SDL_RenderPresent(renderer);

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

				a = tour(tab[p], tab[1 - p], indice_fct);
				p = 1 - p;
				// affiche
				affichage(tab[p]);
				// printf("Entrez 1 pour tour suivant:");
				// scanf("%d", &test);
				DessinCases(rect, renderer, tab[p]);
		}

		// here
	 SDL_Delay(100); //  delai minimal
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

// SDL_RenderClear(renderer);