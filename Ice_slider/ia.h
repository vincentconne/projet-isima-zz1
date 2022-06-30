// **************************************************************************** //
// FICHIER H POUR LE FONCTIONNEMENT DE L'IA ET DE L'APPRENTISSAGE PAR RENFORCEMENT
// **************************************************************************** //

#ifndef IA_H
#define IA_H

// IMPORTS STANDARDS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// IMPORTS DE FICHIERS
#include "jeu.h"
#include "sdl_jeu.h"

// PARAMETRES APPRENTISSAGE
#define NBEPOQUE 1000               // Nombre d'époques
#define NBITEPO 100                 // Nombre d'itérations par époque
#define XI 0.6                      
#define G 0.8
#define MOYREC 5                    // Valeur moyenne des récompenses

// FONCTIONS
int choixActionQSA (float qsa[][6], int x, int y);
int eGreedy (float qsa[][6], float *epsilon, int x , int y);
int prefLearningBase(float qsa[][6], int x, int y, int T);
void apprentissageQSA(float qsa[][6], int run[][4], int dernier);
int traducEtatLigne(int x, int y);
void initQsa(float tab[][6], int nbLignesMap, int nbColonnesMap, int alea);
int getReward(int x, int y);

// FONCTION SUPPLEMENTAIRES
void affichageQSA(float qsa[][6]);
void affichageRUN(int run[][4], int dernier);

#endif