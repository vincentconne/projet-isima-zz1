#ifndef jeu_h
#define jeu_h

#define N 5

int modulo(int k, int n);
int nb_voisins(int **monde, int i, int j, int indice_fct);
int saisie();
int nombre_aleatoire(int min, int max);
int nombre_un(int **monde);
void affichage(int **monde);
//void recopie(int **tab1, int **tab2);
int cellule_suiv(int i, int j, int **tabcour, int indice_fct);
int tour(int **tabcour, int **tabsuiv,int indice_fct);
int nb_voisins_delimite(int **monde, int i, int j);
int nb_voisins_tore(int monde[N][N], int i, int j);
void jeu(int indice_fct);

#endif
