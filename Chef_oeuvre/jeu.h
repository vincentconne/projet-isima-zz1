#ifndef jeu_h
#define jeu_h

int valeur_random(int MIN, int MAX);
int traduc_etat_markov(int etat_cour[]);
void traduc_markov_etat(int colonne, int *etat_suiv);
void nouveau_etat(int *etat_cour, int **tab_etats, int dernier, int premier, int tab_markov[7][7]);

#endif