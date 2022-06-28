#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "jeu.h"
#include "ia.h"


// Initialise la matrice QSA avec des zéros pour les actions (A MODIFIER POUR LES ETATS POSSIBLES)
void initQsa(float qsa[][6], int nbLignesMap, int nbColonnesMap)
{
    for (int j = 0; j < nbColonnesMap*nbLignesMap; j++)
    {
        qsa[j][1] = j/nbColonnesMap;
        qsa[j][2] = j%nbColonnesMap;
        for (int k = 3; k < 6; k++)
        {
            qsa[j][k] = 0;
        }   
    }  
}

int choix_action_qsa(int **qsa, int ligne)
{
    int action = 0;
    for (int i = 0; i < 4; i++)
    {
        if (qsa[ligne][i] > qsa[ligne][action])
        {
            action = i;
        }
    }
    return action;
}

// Prend les coordonnées du personnage et renvoie l'indice de la ligne état associée
int traduc_etat_ligne(int x, int y)
{
    return ((x/100) + ((y/100)-1));
}

int e_greedy(int **qsa, int *epsilon, int x, int y)
{
    int action;
    int ligne = traduc_etat_ligne(x, y);
    int alea = valeur_random(0, 100);
    if (alea > *epsilon)
    {
        action = choix_action_qsa(qsa, ligne);
    }
    else
    {
        action = valeur_random(0, 3);
    }
    *epsilon = *epsilon * 0.8;
    return action;
}

int pref_learning_base(int **qsa, int x, int y, int T)
{
    int energie[4];
    int ligne = traduc_etat_ligne(x, y);
    int z;
    int action = 3;
    float alpha = valeur_random(0, 9) / 10;
    int cumul = 0;

    for (int i = 0; i < 4; i++)
    {
        energie[i] = exp((qsa[ligne][i]) / T);
        z = energie[i];
    }

    for (int i = 0; i < 4; i++)
    {
        cumul += energie[i] / z;
        if (alpha <= cumul)
        {
            action = i;
            i = 5;
        }
    }

    return action;
}
