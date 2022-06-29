#ifndef IA_H
#define IA_H

/* Paramètre de définition du monde */
#define NBETATS 37
// Valeurs des récompenses

// Valeur moyenne des récompenses
#define MOYREC 5

// Case de départ

/* Paramètre d'apprentissage */
#define NBEPOQUE 40
#define NBITEPO 50
#define XI 0.4
#define G 0.8

/* Paramètre des états */
// Définition des états

/* Paramètre de e_greedy */
// valeur de epsilon en % (de 0 à 100) qui sera modifiée
#define EPSILON = 0.8;

/* FONCTIONS */
int choixActionQSA (int **qsa, int x, int y);
int eGreedy (int **qsa, int *epsilon, int x , int y);
int prefLearningBase(int ** qsa, int x, int y, int T);
void apprentissageQSA(int **qsa, int **run, int dernier, int action);
int traduc_etat_ligne(int x, int y);
void initTabIa(float tab[][6], int nbLignesMap, int nbColonnesMap, int alea);
void initReward(float reward[][6], int nbLignesMap, int nbColonnesMap);

#endif