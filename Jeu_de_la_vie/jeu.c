#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "jeu.h"
#include "sdl_jeu.h"



int survie[8] = {0, 0, 1, 1, 0, 0, 0, 0};

int naissance[8] = {0, 0, 0, 1, 0, 0, 0, 0};

int modulo(int k, int n){
	int res = k%n;
	if (res<0){
		res = n*1 + res;
	}
	return res;
}

int nb_voisins(int **monde, int i, int j, int indice_fct){
	int res=0;
	if (indice_fct==1){
		res = nb_voisins_tore(monde,i,j);
	}
	else {
		res = nb_voisins_delimite(monde, i, j);
	}
	return res;
}

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


// Calcul la valeur d'une cellule (morte ou vivante) à t+1
int cellule_suiv(int i, int j, int **tabcour, int indice_fct)
{
	int prochaine_valeur;
	int nbvoisins = nb_voisins(tabcour, i, j,indice_fct); // On compte le nombre de voisins de la cellule
	printf("Nombre voisins: %d\n",nbvoisins);
	if (tabcour[i][j])
		prochaine_valeur = survie[nbvoisins]; // Si cellule vivante alors à t+1 prend la valeur dans survie
	else
		prochaine_valeur = naissance[nbvoisins]; // Si cellule morte alors à t+1 prend la valeur dans naissance
	return prochaine_valeur;
}

// Opérations à effectuer à chaque tour de boucle de jeu
int tour(int **tabcour, int **tabsuiv,int indice_fct)
{
	int verif = 1;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (tabsuiv[i][j] != cellule_suiv(i, j, tabcour, indice_fct))
			{
				verif = 0;
			}
			tabsuiv[i][j] = cellule_suiv(i, j, tabcour,indice_fct);
			//printf("valeur i j %d\n",tabsuiv[i][j]);
		}
	}
	return verif;
}

// nb voisin
int nb_voisins_delimite(int **monde, int i, int j)
{
	int cpt_voisins = 0;
	// dessus
	if (i > 0)
	{
		cpt_voisins+=monde[i - 1][j];
	}
	// gauche
	if (j > 0)
	{
		cpt_voisins+=monde[i][j - 1];
	}
	// dessous
	if (i < N - 1)
	{
		cpt_voisins+= monde[i + 1][j];
	}
	// droite
	if (j < N - 1)
	{
		cpt_voisins+=monde[i][j + 1];
	}
	// haut gauche
	if (i > 0 && j > 0)
	{
		cpt_voisins+=monde[i - 1][j - 1];
	}
	// bas gauche
	if (i < N - 1 && j > 0)
	{
		cpt_voisins+=monde[i + 1][j - 1];
	}
	// haut droite
	if (i > 0 && j < N - 1)
	{
		cpt_voisins+=monde[i - 1][j + 1];
	}
	// bas droite
	if (i < N - 1 && j < N - 1)
	{
		cpt_voisins+=monde[i + 1][j + 1];
	}
	return cpt_voisins;
}

// nb voisin dans le tore
int nb_voisins_tore(int **monde, int i, int j)
{
	int cpt_voisins = 0;
	// dessus
	cpt_voisins += monde[modulo((i - 1),N)][j];

	// gauche
	cpt_voisins += monde[i][modulo((j - 1),N)];

	// dessous
	cpt_voisins+=monde[modulo((i + 1),N)][j];
	
	// droite
	cpt_voisins+=monde[i][modulo((j + 1),N)];
	
	// haut gauche
	cpt_voisins+=monde[modulo((i - 1),N)][modulo((j - 1),N)];
	
	// bas gauche
	cpt_voisins+=monde[modulo((i + 1),N)][modulo((j - 1),N)];

	// haut droite
	cpt_voisins+=monde[modulo((i - 1),N)][modulo((j + 1),N)];
	
	// bas droite
	cpt_voisins+=monde[modulo((i + 1),N)][modulo((j + 1),N)];
	
	return cpt_voisins;
}

//Fonction de sauvegarde du monde actuel
void sauvegarde(char *fichier, int **monde){
	FILE *file = fopen(fichier,"w");
	if(file){
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				fprintf(file,"%d ",monde[i][j]);
			}
			fprintf(file,"\n",NULL);
		}
	}
	fclose(file);
}

//Fonction qui charge un monde provenant d'un fichier texte
void charger(char *fichier, int **monde){
	FILE *file = fopen(fichier,"r");
	if(file){
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				fscanf(file,"%d",&monde[i][j]);
				printf("Lecture dans le fichier %d %d : %d\n",i,j,monde[i][j]); 
			}
		}
	}
	fclose(file);
}

// main
void jeu(int indice_fct)
{
	srand(time(NULL));
	int **monde = (int **)malloc(sizeof(int *) * N), **tmp = (int **)malloc(sizeof(int *) * N);
	for (int i = 0; i < N; i++)
	{
		monde[i] = (int *)malloc(sizeof(int) * N);
		tmp[i] = (int *)malloc(sizeof(int) * N);
	}
	// init monde
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			monde[i][j] = 0;
		}
	}
	sdl_Jeu(monde,tmp,indice_fct);
	liberation(monde,tmp);
}

void liberation(int **monde, int **tmp){
	for (int i=0;i<N;i++){
		free(monde[i]);
		free(tmp[i]);
	}
	free(monde);
	free(tmp);
}



