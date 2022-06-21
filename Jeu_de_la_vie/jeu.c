#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include "jeu.h"

int survie[8] = {1, 1, 1, 1, 1, 0, 0, 0};

int naissance[8] = {0, 0, 1, 0, 0, 0, 0, 0};

// saisie initiale   NE VA PAS NOUS SERVIR, UTILISATEUR ENTRE A LA MAIN
int saisie()
{
	int nb;
	printf("veuillez saisir le nombre de cellules vivantes initial entre 0 et N carré: \n");
	scanf("%d", &nb);
	return nb;
}

// nombre aleatoire
int nombre_aleatoire(int min, int max)
{
	return (rand() % (max - min + 1)) + min;
}
// nombre de un COMPTAGE CELLULES VIVANTES
int nombre_un(int **monde)
{
	int i, j, cpt_un;
	cpt_un = 0;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
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
void affichage(int **monde)
{
	// init
	int i = 0, j = 0;
	printf("-----------------------------------------\n");
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			// cellule vivante?
			if (monde[i][j] == 1)
			{
				printf("1"); // NOIR
			}
			else
			{				 // 0
				printf("0"); // BLANC
			}
		}
		printf("|\n");
		printf("-----------------------------------------\n");
	}
	// afficher les cellules vivantes
	printf("nombre de cellules vivantes: %d\n", nombre_un(monde));
}

// copie monde1 -> monde2
void recopie(int **tab1, int **tab2)
{
	int i, j;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			tab2[i][j] = tab1[i][j];
		}
	}
}

// Calcul la valeur d'une cellule (morte ou vivante) à t+1
int cellule_suiv(int i, int j, int **tabcour)
{
	int prochaine_valeur;
	int nbvoisins = nb_voisins_delimite(tabcour, i, j); // On compte le nombre de voisins de la cellule
	if (tabcour[i][j])
		prochaine_valeur = survie[nbvoisins - 1]; // Si cellule vivante alors à t+1 prend la valeur dans survie
	else
		prochaine_valeur = naissance[nbvoisins - 1]; // Si cellule morte alors à t+1 prend la valeur dans naissance
	return prochaine_valeur;
}

// Opérations à effectuer à chaque tour de boucle de jeu
int tour(int **tabcour, int **tabsuiv)
{
	int verif = 1;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (tabsuiv[i][j] != cellule_suiv(i, j, tabcour))
			{
				verif = 0;
			}
			tabsuiv[i][j] = cellule_suiv(i, j, tabcour);
		}
	}
	int **tmp = tabcour;

	tabcour = tabsuiv;
	tabsuiv = tmp;

	return verif;
}

// nb voisin
int nb_voisins_delimite(int **monde, int i, int j)
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
	if (i < N - 1 && monde[i + 1][j] == 1)
	{
		cpt_voisins++;
	}
	// droite
	if (j < N - 1 && monde[i][j + 1] == 1)
	{
		cpt_voisins++;
	}
	// haut gauche
	if (i > 0 && j > 0 && monde[i - 1][j - 1] == 1)
	{
		cpt_voisins++;
	}
	// bas gauche
	if (i < N - 1 && j > 0 && monde[i + 1][j - 1] == 1)
	{
		cpt_voisins++;
	}
	// haut droite
	if (i > 0 && j < N - 1 && monde[i - 1][j + 1] == 1)
	{
		cpt_voisins++;
	}
	// bas droite
	if (i < N - 1 && j < N - 1 && monde[i + 1][j + 1] == 1)
	{
		cpt_voisins++;
	}
	return cpt_voisins;
}

// nb voisin dans le tore
int nb_voisins_tore(int monde[N][N], int i, int j)
{
	int cpt_voisins = 0;
	// dessus
	if (monde[(i - 1) % N][j] == 1)
	{
		cpt_voisins++;
	}
	// gauche
	if (monde[i][(j - 1) % N] == 1)
	{
		cpt_voisins++;
	}
	// dessous
	if (monde[(i + 1) % N][j] == 1)
	{
		cpt_voisins++;
	}
	// droite
	if (monde[i][(j + 1) % N] == 1)
	{
		cpt_voisins++;
	}
	// haut gauche
	if (monde[(i - 1) % N][(j - 1) % N] == 1)
	{
		cpt_voisins++;
	}
	// bas gauche
	if (monde[(i + 1) % N][(j - 1) % N] == 1)
	{
		cpt_voisins++;
	}
	// haut droite
	if (monde[(i - 1) % N][(j + 1) % N] == 1)
	{
		cpt_voisins++;
	}
	// bas droite
	if (monde[(i + 1) % N][(j + 1) % N] == 1)
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
	int nb_cell = 0, x = 0, y = 0, cpt_cell;
	int **monde = (int **)malloc(sizeof(int *) * N), **tmp = (int **)malloc(sizeof(int *) * N);
	for (int i = 0; i < N; i++)
	{
		monde[i] = (int *)malloc(sizeof(int) * N);
		tmp[i] = (int *)malloc(sizeof(int) * N);
	}
	// tour suivant
	bool tour_suivant = false;
	// init monde
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			monde[i][j] = 0;
		}
	}
	// saisi cellules
	nb_cell = saisie();
	while (nb_cell < 0 || nb_cell > N * N)
	{
		nb_cell = saisie();
	}
	printf("nombre initial de cellules vivantes : %d \n", nb_cell);
	// choix pos
	for (cpt_cell = 0; cpt_cell < nb_cell; cpt_cell++)
	{
		x = nombre_aleatoire(0, N - 1);
		y = nombre_aleatoire(0, N - 1);
		while (monde[x][y] == 1)
		{
			x = nombre_aleatoire(0, N - 1);
			y = nombre_aleatoire(0, N - 1);
		}
		monde[x][y] = 1;
	}
	// affiche monde
	affichage(monde);
	// prochain tour
	tour_suivant = true;
	while (tour_suivant == true && test == 1)
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				tmp[i][j] = nb_voisins_delimite(monde, i, j);
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
