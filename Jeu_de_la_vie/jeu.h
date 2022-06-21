#ifndef jeu_h
#define jeu_h

#define N 5

int survie[8] = {1, 1, 1, 1, 1, 0, 0, 0};

int naissance[8] = {0, 0, 1, 0, 0, 0, 0, 0};

int saisie();
int nombre_aleatoire(int min, int max);
int nombre_un(int monde[][N]);
void affichage(int monde[][N]);
void recopie(int tab1[][N], int tab2[][N]);
int nb_voisins (int monde[][N], int i, int j);
void jeu();

#endif
