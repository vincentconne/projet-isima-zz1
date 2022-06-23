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

#define VITESSE 200

int score = 0;

void draw(SDL_Renderer *renderer, int xg, int yg, SDL_Texture *text_texture)
{
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

void draw_score(SDL_Renderer *renderer, int xg, int yg, SDL_Texture *text_texture)
{ // Je pense que vous allez faire moins laid :)
	SDL_Rect rectangle;

	SDL_SetRenderDrawColor(renderer,
						   50, 0, 0, // mode Red, Green, Blue (tous dans 0..255)
						   255);	 // 0 = transparent ; 255 = opaque
	rectangle.x = xg;				 // x haut gauche du rectangle
	rectangle.y = yg;				 // y haut gauche du rectangle
	rectangle.w = 100;				 // sa largeur (w = width)
	rectangle.h = 30;				 // sa hauteur (h = height)

	SDL_RenderFillRect(renderer, &rectangle);

	SDL_QueryTexture(text_texture, NULL, NULL, &rectangle.w, &rectangle.h); // récupération de la taille (w, h) du texte
	SDL_RenderCopy(renderer, text_texture, NULL, &rectangle);
}

// Mise à jour de la texture du score a chaque changement
SDL_Texture *update_score(TTF_Font *font, SDL_Color *color, SDL_Renderer *renderer)
{

	char score_char[10];
	sprintf(score_char, "%d", score);
	printf("score int : %d score char : %s\n", score, score_char);

	SDL_Surface *surface_score = NULL;
	surface_score = TTF_RenderText_Blended(font, score_char, *color);
	if (surface_score == NULL)
	{
		fprintf(stderr, "Erreur SDL_TTF : %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_Texture *texture_score;
	texture_score = SDL_CreateTextureFromSurface(renderer, surface_score);

	if (texture_score == NULL)
	{
		fprintf(stderr, "Erreur SDL_TTF : %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_FreeSurface(surface_score);

	return texture_score;
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

void sdl_Jeu(int premier, int dernier, int **tab_etats, int etat_cour[3], int tab_markov[][7])
{

	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_DisplayMode screen;

	char score_char[10];
	sprintf(score_char, "%d", score);

	if (0 != SDL_Init(SDL_INIT_VIDEO))
	{
		fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_GetCurrentDisplayMode(0, &screen);

	// Création de la fenêtre
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

	// Création du renderer
	renderer = SDL_CreateRenderer(window, -1,
								  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		exit(EXIT_FAILURE);
	}

	// Compteur de score
	if (TTF_Init() < 0)
	{
		fprintf(stderr, "Erreur SDL_TTF : %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	TTF_Font *font = NULL;				   // la variable 'police de caractère'
	font = TTF_OpenFont("stocky.ttf", 20); // La police à charger, la taille désirée
	if (font == NULL)
	{
		fprintf(stderr, "Erreur SDL_TTF : %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	TTF_SetFontStyle(font, TTF_STYLE_ITALIC); // en italique, gras

	SDL_Color color = {255, 255, 255, 255}; // la couleur du texte

	SDL_Surface *surface_texte_score = NULL;
	surface_texte_score = TTF_RenderText_Blended(font, "SCORE", color);
	if (surface_texte_score == NULL)
	{
		fprintf(stderr, "Erreur SDL_TTF : %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_Texture *texture_texte_score = NULL;
	texture_texte_score = SDL_CreateTextureFromSurface(renderer, surface_texte_score);
	if (texture_texte_score == NULL)
	{
		fprintf(stderr, "Erreur SDL_TTF : %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_FreeSurface(surface_texte_score);

	SDL_Texture *texture_score = NULL;

	// Création de la texture de la voiture
	SDL_Texture *voiture = IMG_LoadTexture(renderer, "./src/Voiture.png");

	SDL_Rect rect_voiture;
	rect_voiture.x = 375;
	rect_voiture.y = 650;
	rect_voiture.w = 60;
	rect_voiture.h = 120;

	SDL_RenderCopy(renderer, voiture, NULL, &rect_voiture);

	// Création des textures pour le fond
	SDL_Texture *background = IMG_LoadTexture(renderer, "./src/sansblanc1.png");
	SDL_Texture *background2 = IMG_LoadTexture(renderer, "./src/sansblanc2.png");

	if (voiture == NULL && background == NULL && background2 == NULL)
	{
		exit(EXIT_FAILURE);
	}

	int i = 1;
	int exit = 0;

	SDL_Texture *travaux = IMG_LoadTexture(renderer, "./src/barriere.png");

	SDL_Rect rect_travaux[5][3]; //= {32*(SDL_GetTicks()/1000%6)}
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			rect_travaux[i][j].x = 150 + j * 200;
			rect_travaux[i][j].y = i * 160; //(i*800)/5
			rect_travaux[i][j].w = 100;
			rect_travaux[i][j].h = 100;
		}
	}

	// initialisation pour les tours de lignes

	int ligne = premier;
	int p = 0;
	int ite = 0;

	// boucle de travail
	SDL_bool sortie = SDL_FALSE;
	while (!exit || sortie == SDL_FALSE)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN)
			{
				// Déplacement de la voiture
				switch (event.key.keysym.scancode)
				{
				case SDL_SCANCODE_LEFT:
					if (rect_voiture.x - VITESSE > 100)
					{
						rect_voiture.x -= VITESSE;
					}
					break;
				case SDL_SCANCODE_RIGHT:
					if (rect_voiture.x + VITESSE < 650)
					{
						rect_voiture.x += VITESSE;
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

		// Affichage de la route (défilement)
		if (i == 1)
		{
			play_with_texture_1(background, window, renderer);
			i = 0;
		}
		else
		{
			play_with_texture_1(background2, window, renderer);
			i = 1;
		}
		for (p = 0; p < 5; p++)
		{
			for (int k = 0; k < 3; k++)
			{
				if (tab_etats[ligne][k])
				{
					SDL_RenderCopy(renderer, travaux, NULL, &rect_travaux[p][k]);
				}
			}
			ligne = (ligne + 1) % 5;
		}
		texture_score = update_score(font, &color, renderer);
		draw_score(renderer, 0, 0, texture_texte_score);
		draw_score(renderer, 0, 30, texture_score);
		SDL_RenderCopy(renderer, voiture, NULL, &rect_voiture);
		sortie = Collision(rect_travaux, rect_voiture);
		SDL_RenderPresent(renderer);
		SDL_PumpEvents();
		SDL_Delay(1000);
		SDL_RenderClear(renderer);
		nouveau_etat(etat_cour, tab_etats, &dernier, &premier, tab_markov);
		ligne = premier;

		score = score + 1;
		printf("Passage\n");
	}
	SDL_DestroyTexture(travaux);
	SDL_DestroyTexture(voiture);
	IMG_Quit();
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Intro_jeu(int premier, int dernier, int **tab_etats, int etat_cour[3], int tab_markov[][7])
{
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_DisplayMode screen;
	int stop = 0;

	if (0 != SDL_Init(SDL_INIT_VIDEO))
	{
		fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_GetCurrentDisplayMode(0, &screen);

	// Création de la fenêtre
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

	// Création du renderer
	renderer = SDL_CreateRenderer(window, -1,
								  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		exit(EXIT_FAILURE);
	}

	SDL_bool program_on = SDL_TRUE; // Booléen pour dire que le programme doit continuer
	SDL_Event event;				// c'est le type IMPORTANT !!

	// Création de la texture de fond
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

	SDL_Color color = {255, 255, 255, 255};								  // la couleur du texte
	SDL_Surface *text_surface1 = NULL;									  // la surface  (uniquement transitoire)
	text_surface1 = TTF_RenderText_Blended(font, "JOUER", color);		  // création du texte dans la surface
	SDL_Surface *text_surface2 = NULL;									  // la surface  (uniquement transitoire)
	text_surface2 = TTF_RenderText_Blended(font, "REGLES DU JEU", color); // création du texte dans la surface
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
			sdl_Jeu(premier, dernier, tab_etats, etat_cour, tab_markov);
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

SDL_bool Collision(SDL_Rect tab_rect[5][3], SDL_Rect rect_voiture)
{
	SDL_Rect Endroit_Collision = {0};

	SDL_bool retour = SDL_FALSE; // false
	int j = 0;
	// printf("rect voiture: %d %d %d %d \n",rect_voiture.x,rect_voiture.x + rect_voiture.w,rect_voiture.y,rect_voiture.y + rect_voiture.h);
	while (retour == SDL_FALSE || j < 3)
	{
		 //retour = SDL_IntersectRect(&(tab_rect[4][j]), &(rect_voiture), &Endroit_Collision);
		//retour = SDL_HasIntersection(&(tab_rect[4][j]), &(rect_voiture));
		retour = SDL_HasIntersection(&(rect_voiture), &(tab_rect[4][j]));
		// printf("rect travaux: %d %d %d %d \n",tab_rect[4][j].x,tab_rect[4][j].x + tab_rect[4][j].w,tab_rect[4][j].y,tab_rect[4][j].y + tab_rect[4][j].h);
		j++;
		printf("RETOUR %d\n", retour);
	}
	return retour;
}
