#ifndef IA_H
#define IA_H

/* Paramètre de définition du monde */
#define NBETATS 37
// Valeurs des récompenses

// Valeur moyenne des récompenses
#define MOYREC 0.5

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
int epsilon = 0.8;

#endif