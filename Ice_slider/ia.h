#ifndef IA_H
#define IA_H

/* Paramètre de définition du monde */
//#define NBETATS 37
// Valeurs des récompenses

// Valeur moyenne des récompenses
#define MOYREC 5

// Case de départ

/* Paramètre d'apprentissage */
#define NBEPOQUE 100
#define NBITEPO 50
#define XI 0.6
#define G 0.8

/* Paramètre des états */
// Définition des états

/* Paramètre de e_greedy */
// valeur de epsilon en % (de 0 à 100) qui sera modifiée


/* FONCTIONS */
int choixActionQSA (float qsa[][6], int x, int y);
int eGreedy (float qsa[][6], float *epsilon, int x , int y);
int prefLearningBase(float qsa[][6], int x, int y, int T);
void apprentissageQSA(float qsa[][6], int run[][4], int dernier, int action);
int traduc_etat_ligne(int x, int y);
void initTabIa(float tab[][6], int nbLignesMap, int nbColonnesMap, int alea);
int getReward(int x, int y);

#endif