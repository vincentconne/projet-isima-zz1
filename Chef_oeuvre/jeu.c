#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "jeu.h"

int valeur_random(int MIN, int MAX)
{
    static bool initialized = false;
    if (!initialized)
    {
        srand(time(NULL));
        initialized = true;
    }

    return (rand() % (MAX + 1 - MIN)) + MIN;
}

// Traduction de l'état en la ligne à lire pour la chaine de Markov
int traduc_etat_markov(int etat_cour[3])
{

    int res;

    switch (etat_cour[0])
    {
    case 0:
        switch (etat_cour[1])
        {
        case 0:
            if (etat_cour[2])
            {
                res = 2;
            }
            else
            {
                res = 0;
            }
            break;
        case 1:
            if (etat_cour[2])
            {
                res = 5;
            }
            else
            {
                res = 3;
            }
            break;
        }
    case 1:
        switch (etat_cour[1])
        {
        case 0:
            if (etat_cour[2])
            {
                res = 6;
            }
            else
            {
                res = 1;
            }
            break;
        case 1:
            res = 4;
            break;
        }
        break;
    }
    return res;
}

// Passage de Markov à l'état choisi
void traduc_markov_etat(int colonne, int etat_suiv[3])
{
    switch (colonne)
    {
    case 0:
        etat_suiv[0] = 0;
        etat_suiv[1] = 0;
        etat_suiv[2] = 0;
        break;
    case 1:
        etat_suiv[0] = 1;
        etat_suiv[1] = 0;
        etat_suiv[2] = 0;
        break;
    case 2:
        etat_suiv[0] = 0;
        etat_suiv[1] = 0;
        etat_suiv[2] = 1;
        break;
    case 3:
        etat_suiv[0] = 0;
        etat_suiv[1] = 1;
        etat_suiv[2] = 0;
        break;
    case 4:
        etat_suiv[0] = 1;
        etat_suiv[1] = 1;
        etat_suiv[2] = 0;
        break;
    case 5:
        etat_suiv[0] = 0;
        etat_suiv[1] = 1;
        etat_suiv[2] = 1;
        break;
    case 6:
        etat_suiv[0] = 1;
        etat_suiv[1] = 0;
        etat_suiv[2] = 1;
        break;
    }
}


// Calcul du nouvel état de la route
void nouveau_etat(int etat_cour[3], int **tab_etats, int *dernier, int *premier, int tab_markov[][7])
{

    int alea = valeur_random(1, 10);
    int i = traduc_etat_markov(etat_cour);
    int j = 0;
    int somme_proba = 0;

    while ((alea > somme_proba) && (j < 7))
    {
        somme_proba += tab_markov[i][j];
        j++;
    }
     traduc_markov_etat(j-1, etat_cour);

    // Ajout du nouvel état dans la table
    for (int k=0; k<3; k++){
        tab_etats[*dernier][k] = etat_cour[k];
    }


    // Mise à jour des indices du tableau
    *premier = *dernier;
    *dernier = (5 + *dernier - 1) % 5;
}
