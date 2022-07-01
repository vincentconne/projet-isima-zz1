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
#define NBEPOQUE 10000               // Nombre d'époques
#define NBITEPO 1000                 // Nombre d'itérations par époque
#define XI 0.01                      
#define G 0.8
#define MOYREC 5                    // Valeur moyenne des récompenses

// FONCTIONS
int choixActionQSA(float qsa[][7], int x, int y, int cle);
int eGreedy(float qsa[][7], float *epsilon, int x, int y, int cle);
int prefLearningBase(float qsa[][7], int x, int y, int cle, int T);
void apprentissageQSA(float qsa[][7], int run[][5], int dernier);
int traducEtatLigne(int x, int y, int cle);
void initQsa(float tab[][7], int nbLignesMap, int nbColonnesMap, int alea);
int getReward(int x, int y, int cle);

// FONCTION SUPPLEMENTAIRES
void affichageQSA(float qsa[][7]);
void affichageRUN(int run[][5], int dernier);

#endif