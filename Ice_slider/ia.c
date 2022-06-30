// ******************************************************************************* //
// FICHIER C GERANT L'INTELLIGENCE ARTIFICIELLE ET SON APPRENTISSAGE PAR RENFORCEMENT
// ******************************************************************************* //

// IMPORTS
#include "ia.h"

// FONCTIONS

// ---------------------------------------------------- //
// Affichage de la matrice d'apprentissage QSA pour debug.
// ---------------------------------------------------- //
void affichageQSA(float qsa[][6])
{
    for (int i = 0; i < NBCOLMAP * NBLIGNESMAP; i++)
    {
        for (int j = 0; j < 6; j++)
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
void affichageRUN(int run[][4], int dernier)
{
    for (int i = 0; i < dernier + 1; i++)
    {
        for (int j = 0; j < 4; j++)
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
int traducEtatLigne(int x, int y)
{
    return (((x / 100) * NBLIGNESMAP) + (y / 100));
}

// ------------------------------------------------------------------------- //
// Initialise la matrice QSA pour les actions.
// Si alea alors on initialise avec des nombres aléatoires entre et 0 et MOYREC
// Sinon on initialise qu'avec des zéros
// ------------------------------------------------------------------------- //
void initQsa(float tab[][6], int nbLignesMap, int nbColonnesMap, int alea)
{
    for (int j = 0; j < nbColonnesMap * nbLignesMap; j++)
    {
        tab[j][0] = j / nbLignesMap;
        tab[j][1] = j % nbLignesMap;
        for (int k = 2; k < 6; k++)
        {
            if (alea)
                tab[j][k] = valeurRandom(0, MOYREC);
            else
                tab[j][k] = 0;
        }
    }
}

// -------------------------------------------------------------------------------------- //
// Retourne la récompense en fonction de la position actuelle du joueur et donc de son état.
// -------------------------------------------------------------------------------------- //
int getReward(int x, int y, int cle)
{
    int reward = 0;
    if (!cle && x >= 0 && x < 100 && y >= 600 && y < 700){
        reward = 1;
    } else 
    if (cle && x >= 600 && x < 700 && y >= 0 && y < 100)
        reward = 1;
    return reward;
}

// --------------------------------------------------------- //
// Choisis la meilleure action à réaliser depuis l'état actuel
// --------------------------------------------------------- //
int choixActionQSA(float qsa[][6], int x, int y)
{
    int action = 0;
    int ligne = 0;
    for (int i = 0; i < 4; i++)
    {
        ligne = traducEtatLigne(x, y);
        if (qsa[ligne][2 + i] > qsa[ligne][2 + action])
            action = i;
    }
    return action;
}

// ------------------------------------- //
// Fonction exécutant l'algorithme eGreedy
// ------------------------------------- //
int eGreedy(float qsa[][6], float *epsilon, int x, int y)
{
    int action;
    float alea = (float)valeurRandom(0, 10) / 10;
    if (alea >= *epsilon)
    {
        action = choixActionQSA(qsa, x, y);
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
int prefLearningBase(float qsa[][6], int x, int y, int T)
{
    int energie[4];
    int z;
    int action = 3;
    float alpha = valeurRandom(0, 9) / 10;
    int cumul = 0;
    int ligne = 0;

    for (int i = 0; i < 4; i++)
    {
        ligne = traducEtatLigne(x, y);
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

// --------------------------------------- //
// Fonction d'apprentissage par la table QSA
// --------------------------------------- //
void apprentissageQSA(float qsa[][6], int run[][4], int dernier)
{
    int ligneSuiv;

    // Traitement de la première itération
    int x = run[dernier - 1][0];
    int y = run[dernier - 1][1];
    int rec = run[dernier][3];
    int action = run[dernier - 1][2];
    int ligne = traducEtatLigne(x, y);


    qsa[ligne][2 + action] += XI * rec - qsa[ligne][2 + action];

    // Traitement des autres lignes
    for (int i = dernier - 2; i >= 0; i--)
    {
        float max = 0;

        ligneSuiv = traducEtatLigne(run[i + 1][0], run[i + 1][1]);
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

        ligne = traducEtatLigne(x, y);
        qsa[ligne][2 + action] = qsa[ligne][2 + action] + XI * ((rec + G * max) - qsa[ligne][2 + action]);
    }
}
