#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "jeu.h"
#include "ia.h"

// Prend les coordonnées du personnage et renvoie l'indice de la ligne état associée
int traduc_etat_ligne(int x, int y)
{
    return ((x / 100) + ((y / 100) - 1));
}

// Initialise la matrice QSA avec des zéros pour les actions
// | x | y | gauche | droite | haut | bas |
void initQsa(float qsa[][6], int nbLignesMap, int nbColonnesMap)
{
    for (int j = 0; j < nbColonnesMap * nbLignesMap; j++)
    {
        qsa[j][1] = j / nbLignesMap;
        qsa[j][2] = j % nbLignesMap;
        for (int k = 3; k < 6; k++)
        {
            qsa[j][k] = 0;
            // qsa[j][k] = valeur_random(0,MOYREC);
        }
    }

    //Affichage de la matrice
    // for (int i = 0; i < 117; i++)
    // {
    //     printf("[ %.1f ; %.1f ]\n", qsa[i][1], qsa[i][2]);
    // }
}

int choixActionQSA(int **qsa, int x, int y)
{
    int action = 0;
    int ligne = 0;
    for (int i = 0; i < 4; i++)
    {
        ligne = traduc_etat_ligne(x, y);
        if (qsa[ligne][2 + i] > qsa[ligne][2 + action])
        {
            action = i;
        }
    }
    return action;
}

int eGreedy(int **qsa, int *epsilon, int x, int y)
{
    int action;
    int alea = valeur_random(0, 100);
    if (alea > *epsilon)
    {
        action = choixActionQSA(qsa, x, y);
    }
    else
    {
        action = valeur_random(0, 3);
    }
    *epsilon = *epsilon * 0.8;
    return action;
}

int prefLearningBase(int **qsa, int x, int y, int T)
{
    int energie[4];
    int z;
    int action = 3;
    float alpha = valeur_random(0, 9) / 10;
    int cumul = 0;
    int ligne = 0;

    for (int i = 0; i < 4; i++)
    {
        ligne = traduc_etat_ligne(x, y);
        energie[i] = exp((qsa[ligne][2 + i]) / T);
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

void apprentissageQSA(int **qsa, int **run, int dernier, int action)
{

    int ligneSuiv;

    // Traitement de la première itération
    int x = run[dernier - 1][0];
    int y = run[dernier - 1][1];
    int rec = run[dernier][2];
    // int action = run[dernier-1][3]; //Soucis de redéfinition
    int ligne = traduc_etat_ligne(x, y);

    qsa[ligne][2 + action] += XI * rec - qsa[ligne][2 + action];

    // Traitement des autres lignes
    for (int i = dernier - 2; i < 0; i--)
    {
        float max;

        ligneSuiv = traduc_etat_ligne(run[i + 1][0], run[i + 1][1]);
        for (int i = 0; i < 4; i++)
        {
            if (qsa[ligneSuiv][2 + i] > max)
            {
                max = qsa[ligneSuiv][2 + i];
            }
        }

        x = run[i][0];
        y = run[i][1];
        rec = run[i + 1][2];
        action = run[i][3];

        ligne = traduc_etat_ligne(x, y);
        qsa[ligne][2 + action] += XI * (rec + G * max - qsa[ligne][2 + action]);
    }
}
