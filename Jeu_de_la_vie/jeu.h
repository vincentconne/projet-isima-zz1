#ifndef jeu_h
#define jeu_h

int saisie();
int nombre_aleatoire(int min, int max);
int nombre_un(int monde[20][20]);
void affichage(int monde[20][20]);
void recopie(int tab1[20][20], int tab2[20][20]);
int nb_voisins (int monde[20][20], int i, int j);
void jeu();

#endif
