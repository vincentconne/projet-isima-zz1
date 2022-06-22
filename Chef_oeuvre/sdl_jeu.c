#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "jeu.h"
#include "sdl_jeu.h"
#define width 800
#define height 800

void draw(SDL_Renderer *renderer, int xg, int yg, SDL_Texture *text_texture)
{ // Je pense que vous allez faire moins laid :)
	SDL_Rect rectangle;

	SDL_SetRenderDrawColor(renderer,
						   50, 0, 0, // mode Red, Green, Blue (tous dans 0..255)
						   255);	 // 0 = transparent ; 255 = opaque
	rectangle.x = xg;				 // x haut gauche du rectangle
	rectangle.y = yg;				 // y haut gauche du rectangle
	rectangle.w = 800;				 // sa largeur (w = width)
	rectangle.h = 100;				 // sa hauteur (h = height)

	SDL_RenderFillRect(renderer, &rectangle);

	SDL_QueryTexture(text_texture, NULL, NULL, &rectangle.w, &rectangle.h); // récupération de la taille (w, h) du texte
	SDL_RenderCopy(renderer, text_texture, NULL, &rectangle);
}

void play_with_texture_1(SDL_Texture *my_texture, SDL_Window *window,
						 SDL_Renderer *renderer)
{
	SDL_Rect
		source = {0},			 // Rectangle définissant la zone de la texture à récupérer
		window_dimensions = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
		destination = {0};		 // Rectangle définissant où la zone_source doit être déposée dans le renderer

	SDL_GetWindowSize(
		window, &window_dimensions.w,
		&window_dimensions.h); // Récupération des dimensions de la fenêtre
	SDL_QueryTexture(my_texture, NULL, NULL,
					 &source.w, &source.h); // Récupération des dimensions de l'image

	destination = window_dimensions; // On fixe les dimensions de l'affichage à  celles de la fenêtre

	/* On veut afficher la texture de façon à ce que l'image occupe la totalité de la fenêtre */

	SDL_RenderCopy(renderer, my_texture,
				   &source,
				   &destination); // Création de l'élément à afficher
}

void sdl_Jeu()
{

	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_DisplayMode screen;

	if (0 != SDL_Init(SDL_INIT_VIDEO))
	{
		fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_GetCurrentDisplayMode(0, &screen);

	window = SDL_CreateWindow("Autoroute",
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

	SDL_GetCurrentDisplayMode(0, &screen);

	SDL_Texture *voiture = IMG_LoadTexture(renderer, "./src/Voiture.png");

	SDL_Rect rect_voiture;
	rect_voiture.x = 350;
	rect_voiture.y = 600;
	rect_voiture.w = 100;
	rect_voiture.h = 200;

	SDL_RenderCopy(renderer, voiture, NULL, &rect_voiture);

	SDL_Texture *background = IMG_LoadTexture(renderer, "./src/frame1.png");

	if (voiture == NULL && background == NULL)
	{
		exit(EXIT_FAILURE);
	}
	int exit = 0;
	while (!exit)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.scancode)
				{
				case SDL_SCANCODE_LEFT:
					if (rect_voiture.x - 10 > 100)
					{
						rect_voiture.x -= 10;
					}
					break;
				case SDL_SCANCODE_RIGHT:
					if (rect_voiture.x + 10 < 600)
					{
						rect_voiture.x += 10;
					}
					break;
				case SDL_SCANCODE_UP:
					if (rect_voiture.y - 10 > 0)
					{
						rect_voiture.y -= 10;
					}
					break;
				case SDL_SCANCODE_DOWN:
					if (rect_voiture.y + 10 < 600)
					{
						rect_voiture.y += 10;
					}
					break;
				default:
					break;
				}
			}
			else if (event.type == SDL_QUIT)
			{
				exit = 1;
				puts("FIN DE MON PROGRAMME");
				break;
			}
		}
		// play_with_texture_4(voiture, window, renderer, background);
		// draw(renderer, &rectangle);
		// clear(renderer);
		play_with_texture_1(background, window, renderer);
		SDL_RenderCopy(renderer, voiture, NULL, &rect_voiture);
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
	}

	SDL_DestroyTexture(voiture);
	IMG_Quit();
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Intro_jeu()
{
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	int statut = EXIT_FAILURE;
	SDL_DisplayMode screen;
	int stop = 0;

	if (0 != SDL_Init(SDL_INIT_VIDEO))
	{
		fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_GetCurrentDisplayMode(0, &screen);

	window = SDL_CreateWindow("ATTENTION TRAVAUX",
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
	SDL_Event event;				// c'est le type IMPORTANT !!
	SDL_GetCurrentDisplayMode(0, &screen);

	SDL_Texture *fond = IMG_LoadTexture(renderer, "./src/Titre.png");
 
   if (fond == NULL)
   {
       exit(EXIT_FAILURE);
   }

	SDL_Rect
		source = {0},			 // Rectangle définissant la zone de la texture à récupérer
		window_dimensions = {0}, // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
		destination = {0};		 // Rectangle définissant où la zone_source doit être déposée dans le renderer

	SDL_GetWindowSize(
		window, &window_dimensions.w,
		&window_dimensions.h); // Récupération des dimensions de la fenêtre
	SDL_QueryTexture(fond, NULL, NULL,
					 &source.w, &source.h); // Récupération des dimensions de l'image

	destination = window_dimensions; // On fixe les dimensions de l'affichage à  celles de la fenêtre

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

	TTF_SetFontStyle(font, TTF_STYLE_ITALIC); // en italique, gras

	SDL_Color color = {255, 255, 255, 255};								   // la couleur du texte
	SDL_Surface *text_surface1 = NULL;									   // la surface  (uniquement transitoire)
	text_surface1 = TTF_RenderText_Blended(font, "JOUER", color); // création du texte dans la surface
	SDL_Surface *text_surface2 = NULL;									   // la surface  (uniquement transitoire)
	text_surface2 = TTF_RenderText_Blended(font, "REGLES DU JEU", color);  // création du texte dans la surface
	if (text_surface1 == NULL && text_surface2 == NULL)
	{
		fprintf(stderr, "Erreur SDL_TTF : %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_Texture *text_texture1 = NULL;									   // la texture qui contient le texte
	text_texture1 = SDL_CreateTextureFromSurface(renderer, text_surface1); // transfert de la surface à la texture
	SDL_Texture *text_texture2 = NULL;									   // la texture qui contient le texte
	text_texture2 = SDL_CreateTextureFromSurface(renderer, text_surface2); // transfert de la surface à la texture
	if (text_texture1 == NULL && text_texture2)
	{
		fprintf(stderr, "Erreur SDL_TTF : %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_FreeSurface(text_surface1); // la texture ne sert plus à rien
	SDL_FreeSurface(text_surface2); // la texture ne sert plus à rien
	int finClique = 0;
	while (program_on && stop == 0)
	{ // Voilà la boucle des évènements

		if (SDL_PollEvent(&event))
		{ // si la file d'évènements n'est pas vide : défiler l'élément en tête
		  // de file dans 'event'
			switch (event.type)
			{
			case SDL_MOUSEBUTTONUP:
				if (event.button.button == SDL_BUTTON_LEFT && 0 < event.button.x && event.button.x < 800 &&
					400 < event.button.y && event.button.y < 500)
				{
					printf("JOUER\n");
					finClique = 2;
				}
				else if (event.button.button == SDL_BUTTON_LEFT && 0 < event.button.x && event.button.x < 800 &&
						 550 < event.button.y && event.button.y < 650)
				{
					printf("REGLES DU JEU\n");
					finClique = 1;
				}
				break;

			case SDL_QUIT:				// Un évènement simple, on a cliqué sur la x de la fenêtre
				program_on = SDL_FALSE; // Il est temps d'arrêter le programme
				break;

			default: // Si L'évènement défilé ne nous intéresse pas
				break;
			}
		}
		if (finClique == 0)
		{
			SDL_RenderCopy(renderer, fond,
						   &source,
						   &destination);
			draw(renderer, 0, 400, text_texture1);
			draw(renderer, 0, 550, text_texture2);
		}
		else
		{
			SDL_DestroyTexture(text_texture1);
			SDL_DestroyTexture(text_texture2);
			SDL_DestroyWindow(window);
			TTF_Quit();
			sdl_Jeu();
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