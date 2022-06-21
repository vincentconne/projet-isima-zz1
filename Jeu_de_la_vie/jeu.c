#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include "jeu.h"

// saisie initiale
int saisie()
{
	int nb;
	printf("veuillez saisir le nombre de cellules vivantes initial entre 0 et 400: \n");
	scanf("%d", &nb);
	return nb;
}
// nombre aleatoire
int nombre_aleatoire(int min, int max)
{
	return (rand() % (max - min + 1)) + min;
}
// nombre de un
int nombre_un(int monde[20][20])
{
	int i, j, cpt_un;
	cpt_un = 0;
	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 20; j++)
		{
			if (monde[i][j] == 1)
			{
				cpt_un++;
			}
		}
	}
	return cpt_un;
}
// afficher monde
void affichage(int monde[20][20])
{
	// terminal
	system("cls");
	// init
	int i = 0, j = 0;
	printf("-----------------------------------------\n");
	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 20; j++)
		{
			// cellule vivante?
			if (monde[i][j] == 1)
			{
				printf("|x");
			}
			else
			{ // 0
				printf("| ");
			}
		}
		printf("|\n");
		printf("-----------------------------------------\n");
	}
	// afficher les cellules vivantes
	printf("nombre de cellules vivantes: %d\n", nombre_un(monde));
}

// copie monde1 -> monde2
void recopie(int tab1[20][20], int tab2[20][20])
{
	int i, j;
	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 20; j++)
		{
			tab2[i][j] = tab1[i][j];
		}
	}
}

// nb voisin
int nb_voisins(int monde[20][20], int i, int j)
{
	int cpt_voisins = 0;
	// dessus
	if (i > 0 && monde[i - 1][j] == 1)
	{
		cpt_voisins++;
	}
	// gauche
	if (j > 0 && monde[i][j - 1] == 1)
	{
		cpt_voisins++;
	}
	// dessous
	if (i < 19 && monde[i + 1][j] == 1)
	{
		cpt_voisins++;
	}
	// droite
	if (j < 19 && monde[i][j + 1] == 1)
	{
		cpt_voisins++;
	}
	// haut gauche
	if (i > 0 && j > 0 && monde[i - 1][j - 1] == 1)
	{
		cpt_voisins++;
	}
	// bas gauche
	if (i < 19 && j > 0 && monde[i + 1][j - 1] == 1)
	{
		cpt_voisins++;
	}
	// haut droite
	if (i > 0 && j < 19 && monde[i - 1][j + 1] == 1)
	{
		cpt_voisins++;
	}
	// bas droite
	if (i < 19 && j < 19 && monde[i + 1][j + 1] == 1)
	{
		cpt_voisins++;
	}
	return cpt_voisins;
}

// main
void jeu()
{
	srand(time(NULL));
	int test = 1;
	// variables
	int nb_cell = 0, x = 0, y = 0, monde[20][20], tmp[20][20], i = 0, j = 0, cpt_cell = 0;
	// tour suivant
	bool tour_suivant = false;
	// init monde
	for (i = 0; i < 20; i++)
	{
		for (j = 0; j < 20; j++)
		{
			monde[i][j] = 0;
		}
	}
	// saisi cellules
	nb_cell = saisie();
	while (nb_cell < 0 || nb_cell > 400)
	{
		nb_cell = saisie();
	}
	printf("nombre initial de cellules vivantes : %d \n", nb_cell);
	// choix pos
	for (cpt_cell = 0; cpt_cell < nb_cell; cpt_cell++)
	{
		x = nombre_aleatoire(0, 19);
		y = nombre_aleatoire(0, 19);
		while (monde[x][y] == 1)
		{
			x = nombre_aleatoire(0, 19);
			y = nombre_aleatoire(0, 19);
		}
		monde[x][y] = 1;
	}
	// affiche monde
	affichage(monde);
	// prochain tour
	tour_suivant = true;
	while (tour_suivant == true && test == 1)
	{
		for (i = 0; i < 20; i++)
		{
			for (j = 0; j < 20; j++)
			{
				tmp[i][j] = nb_voisins(monde, i, j);
				// naissance
				if (monde[i][j] == 0 && tmp[i][j] == 3)
				{
					tmp[i][j] = 1;
				}
				else
				{
					// vivante
					if (monde[i][j] == 1 && (tmp[i][j] == 2 || tmp[i][j] == 3))
					{
						tmp[i][j] = 1;
					}
					else
					{
						// meurt
						tmp[i][j] = 0;
					}
				}
			}
		}
		// copie
		recopie(tmp, monde);
		// affiche
		affichage(monde);
		printf("Entrez 1 pour tour suivant:");
		scanf("%d", &test);
	}
}