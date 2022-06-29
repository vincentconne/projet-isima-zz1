#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "jeu.h"
#include "ia.h"
#include "sdl_jeu.h"

void affichageQSA(float qsa[][6]){
    for (int i=0; i<NBCOLMAP*NBLIGNESMAP; i++){
        for (int j=0; j<6; j++){
            printf("%f ",qsa[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void affichageRUN(int run[][4], int dernier){
    for (int i=0; i<dernier+1; i++){
        for (int j=0; j<4; j++){
            printf("%d ",run[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Prend les coordonnées du personnage et renvoie l'indice de la ligne état associée
int traduc_etat_ligne(int x, int y)
{
    return (((x / 100) * NBLIGNESMAP) + (y / 100));
}

// Initialise la matrice QSA avec des zéros pour les actions

void initTabIa(float tab[][6], int nbLignesMap, int nbColonnesMap, int alea)
{
    for (int j = 0; j < nbColonnesMap * nbLignesMap; j++)
    {
        tab[j][0] = j / nbLignesMap;
        tab[j][1] = j % nbLignesMap;
        for (int k = 2; k < 6; k++)
        {
            if (alea)
                tab[j][k] = valeur_random(0, MOYREC);
            else
                tab[j][k] = 0;
        }
    }
}

// Retourne la récompense en fonction de la position actuelle du joueur
int getReward(int x, int y)
{
    int reward = 0;

    if (x >= 600 && x < 700 && y >= 0 && y < 100)
        reward = 1;

    return reward;
}

int choixActionQSA(float qsa[][6], int x, int y)
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

int eGreedy(float qsa[][6], float *epsilon, int x, int y)
{
    int action;
    float alea = (float) valeur_random(0, 10) / 10;
    if (alea >= *epsilon)
    {
        action = choixActionQSA(qsa, x, y);
    }
    else
    {
        action = valeur_random(0, 3);
    }
    *epsilon = *epsilon * 0.99;
    return action;
}

int prefLearningBase(float qsa[][6], int x, int y, int T)
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

void apprentissageQSA(float qsa[][6], int run[][4], int dernier)
{

    int ligneSuiv;

    // Traitement de la première itération
    int x = run[dernier - 1][0];
    int y = run[dernier - 1][1];
    int rec = run[dernier][3];
    int action = run[dernier-1][2];
    int ligne = traduc_etat_ligne(x, y);


    qsa[ligne][2 + action] += XI * rec - qsa[ligne][2 + action];


    // Traitement des autres lignes
    for (int i = dernier - 2; i >=0; i--)
    {
        float max =0;

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
        rec = run[i + 1][3];
        action = run[i][2];


        ligne = traduc_etat_ligne(x, y);
        qsa[ligne][2 + action] = qsa[ligne][2 + action] + XI * ((rec + G * max) - qsa[ligne][2 + action]);

    }
}
