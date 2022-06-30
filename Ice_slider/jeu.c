// *************************************************************** //
// FICHIER C GERANT DIVERSES FONCTIONS POUR LE FONCTIONNEMENT DU JEU
// *************************************************************** //

// IMPORTS
#include "jeu.h"

// FONCTIONS

// -------------------------------------------------- //
// Retourne une valeur aléatoire entre un min et un max
// -------------------------------------------------- //
int valeurRandom(int min, int max)
{
    static bool initialized = false;
    if (!initialized)
    {
        srand(time(NULL));
        initialized = true;
    }

    return (rand() % (max + 1 - min)) + min;
}

// ---------------------------------- //
// Initialisation du tableau des rochers
// ---------------------------------- //
void initRoc(SDL_Rect *rectRoc)
{
    for (int i = 0; i < 13; i++)
    {
        rectRoc[i].w = 100;
        rectRoc[i].h = 100;
    }
    rectRoc[0].x = 200;
    rectRoc[0].y = 100;
    rectRoc[1].x = 100;
    rectRoc[1].y = 200;
    rectRoc[2].x = 100;
    rectRoc[2].y = 700;
    rectRoc[3].x = 200;
    rectRoc[3].y = 400;
    rectRoc[4].x = 600;
    rectRoc[4].y = 300;
    rectRoc[5].x = 600;
    rectRoc[5].y = 500;
    rectRoc[6].x = 700;
    rectRoc[6].y = 700;
    rectRoc[7].x = 800;
    rectRoc[7].y = 400;
    rectRoc[8].x = 900;
    rectRoc[8].y = 600;
    rectRoc[9].x = 1000;
    rectRoc[9].y = 100;
    rectRoc[10].x = 1100;
    rectRoc[10].y = 300;
    rectRoc[11].x = 1100;
    rectRoc[11].y = 700;
    rectRoc[12].x = 500;
    rectRoc[12].y = 200;
}

// ---------------------------------- //
// Initialisation du tableau des murs
// ---------------------------------- //
void initMur(SDL_Rect *rectMur)
{
    rectMur[0].x = 0;
    rectMur[0].y = 0;
    rectMur[0].w = 100;
    rectMur[0].h = 900;
    rectMur[1].x = 1200;
    rectMur[1].y = 0;
    rectMur[1].w = 100;
    rectMur[1].h = 900;
    rectMur[2].x = 100;
    rectMur[2].y = 0;
    rectMur[2].w = 500;
    rectMur[2].h = 100;
    rectMur[3].x = 700;
    rectMur[3].y = 0;
    rectMur[3].w = 500;
    rectMur[3].h = 100;
    rectMur[4].x = 100;
    rectMur[4].y = 800;
    rectMur[4].w = 500;
    rectMur[4].h = 100;
    rectMur[5].x = 700;
    rectMur[5].y = 800;
    rectMur[5].w = 500;
    rectMur[5].h = 100;
}

// ---------------------- //
// Recherche des obstacles
// ---------------------- //
void recherche1(int TabJeu[][13], int direction, int posEsquiX, int posEsquiY, int tabRetour[2])
{
    int i = posEsquiY / 100;
    int j = posEsquiX / 100;

    if (direction == 2)
    {
        while (TabJeu[i][j] != 2 && TabJeu[i][j] != 1)
            i--;
        if (TabJeu[i][j] == 2) // Si je suis sur la case de sortie 2
        {
            tabRetour[0] = i;
            tabRetour[1] = j;
        }
        else
        {
            tabRetour[0] = i + 1;
            tabRetour[1] = j;
        }
    }
    else if (direction == 0)
    {
        while (i < 9 && TabJeu[i][j] != 1)
            i++;
        tabRetour[0] = i - 1;
        tabRetour[1] = j;
    }
    else if (direction == 1)
    {
        while (TabJeu[i][j] != 1)
            j--;

        tabRetour[0] = i;
        tabRetour[1] = j + 1;
    }
    else if (direction == 3)
    {
        while (TabJeu[i][j] != 1)
            j++;
        tabRetour[0] = i;
        tabRetour[1] = j - 1;
    }
}