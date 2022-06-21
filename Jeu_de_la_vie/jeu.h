#ifndef jeu_h
#define jeu_h

#define N 5

int saisie();
int nombre_aleatoire(int min, int max);
int nombre_un(int **monde);
void affichage(int **monde);
void recopie(int **tab1, int **tab2);
int nb_voisins_vivants(int **monde, int i, int j);
void jeu();

#endif
