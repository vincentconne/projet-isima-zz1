// ******************************************************************************* //
// FICHIER C GERANT L'INTELLIGENCE ARTIFICIELLE ET SON APPRENTISSAGE PAR RENFORCEMENT
// ******************************************************************************* //

// IMPORTS
#include "ia.h"

// FONCTIONS

// ---------------------------------------------------- //
// Affichage de la matrice d'apprentissage QSA pour debug.
// ---------------------------------------------------- //
void affichageQSA(float qsa[][7])
{
    for (int i = 0; i < (NBCOLMAP * NBLIGNESMAP) * 2; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            printf("%f ", qsa[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// ----------------------------------------- //
// Affichage de la matrice des runs pour debug.
// ----------------------------------------- //
void affichageRUN(int run[][5], int dernier)
{
    for (int i = 0; i < dernier + 1; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            printf("%d ", run[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// ----------------------------------------- //
// En fonction des coordonnées du personnage
// renvoie l'indice de la ligne correspondante
// dans le tableau QSA.
// ----------------------------------------- //
int traducEtatLigne(int x, int y, int cle)
{
    int res = ( ((x / 100) * NBLIGNESMAP) + (y / 100))*2 + cle;
    return (res);
}

// ------------------------------------------------------------------------- //
// Initialise la matrice QSA pour les actions.
// Si alea alors on initialise avec des nombres aléatoires entre et 0 et MOYREC
// Sinon on initialise qu'avec des zéros
// ------------------------------------------------------------------------- //
void initQsa(float tab[][7], int nbLignesMap, int nbColonnesMap, int alea)
{
    int i = 0;
    for (int j = 0; j < (nbColonnesMap * nbLignesMap) * 2; j+=2)
    {
        tab[j][0] = i / nbLignesMap;
        tab[j][1] = i % nbLignesMap;
        tab[j][2] = 0;

        tab[j + 1][0] = i / nbLignesMap;
        tab[j + 1][1] = i % nbLignesMap;
        tab[j + 1][2] = 1;

        for (int k = 3; k < 7; k++)
        {
            if (alea)
            {
                tab[j][k] = valeurRandom(0, MOYREC);
                tab[j + 1][k] = valeurRandom(0, MOYREC);
            }
            else
            {
                tab[j][k] = 0;
                tab[j + 1][k] = 0;
            }
        }
        i++;
    }
}

// -------------------------------------------------------------------------------------- //
// Retourne la récompense en fonction de la position actuelle du joueur et donc de son état.
// -------------------------------------------------------------------------------------- //
int getReward(int x, int y, int cle)
{
    int reward = 0;
    if (!cle && x >= 0 && x < 100 && y >= 600 && y < 700)
    {
        reward = 1;
    }
    else
    if (cle && x >= 600 && x < 700 && y >= 0 && y < 100)
        reward = 1;
    return reward;
}

// --------------------------------------------------------- //
// Choisis la meilleure action à réaliser depuis l'état actuel
// --------------------------------------------------------- //
int choixActionQSA(float qsa[][7], int x, int y, int cle)
{
    int action = 0;
    int ligne = 0;
    for (int i = 0; i < 4; i++)
    {
        ligne = traducEtatLigne(x, y,cle);
        if (qsa[ligne][3 + i] > qsa[ligne][3 + action])
            action = i;
    }
    return action;
}

// ------------------------------------- //
// Fonction exécutant l'algorithme eGreedy
// ------------------------------------- //
int eGreedy(float qsa[][7], float *epsilon, int x, int y, int cle)
{
    int action;
    float alea = (float)valeurRandom(0, 10) / 10;
    if (alea >= *epsilon)
    {
        action = choixActionQSA(qsa, x, y,cle);
    }
    else
    {
        action = valeurRandom(0, 3);
    }
    *epsilon = *epsilon * 0.999;
    return action;
}

// ----------------------------- //
// N'est pas utilisée
// Fonction alternative à eGreedy
// ----------------------------- //
int prefLearningBase(float qsa[][7], int x, int y, int cle, int T)
{
    int energie[4];
    int z;
    int action = 3;
    float alpha = valeurRandom(0, 9) / 10;
    int cumul = 0;
    int ligne = 0;

    for (int i = 0; i < 4; i++)
    {
        ligne = traducEtatLigne(x, y,cle);
        energie[i] = exp((qsa[ligne][3 + i]) / T);
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

// --------------------------------------- //
// Fonction d'apprentissage par la table QSA
// --------------------------------------- //
void apprentissageQSA(float qsa[][7], int run[][5], int dernier)
{
    int ligneSuiv;

    // Traitement de la première itération
    int x = run[dernier - 1][0];
    int y = run[dernier - 1][1];
    int cle = run[dernier - 1][2];
    int rec = run[dernier][4];
    int action = run[dernier - 1][3];
    int ligne = traducEtatLigne(x, y,cle);

    qsa[ligne][3 + action] += XI * rec - qsa[ligne][3 + action];

    // printf("calcul qsa : %f\n",qsa[ligne][3 + action]);

    // Traitement des autres lignes
    for (int i = dernier - 2; i >= 0; i--)
    {
        float max = 0;

        ligneSuiv = traducEtatLigne(run[i + 1][0], run[i + 1][1],run[i+1][2]);
        for (int i = 0; i < 4; i++)
        {
            if (qsa[ligneSuiv][3 + i] > max)
            {
                max = qsa[ligneSuiv][3 + i];
            }
        }

        x = run[i][0];
        y = run[i][1];
        cle = run[i][2];
        rec = run[i + 1][4];
        action = run[i][3];

        ligne = traducEtatLigne(x, y,cle);
        qsa[ligne][3 + action] = qsa[ligne][3 + action] + XI * ((rec + G * max) - qsa[ligne][3 + action]);
    }
}
