#ifndef ia_h
#define ia_h

/* Paramètre de définition du monde */
#define NBETATS 20
// Valeurs des récompenses

// Valeur moyenne des récompenses
#define MOYREC 5

// Case de départ

/* Paramètre d'apprentissage */
#define NBEPOQUE 40
#define NBITEPO 50
int xi;


/* Paramètre des états */
// Définition des états

/* Paramètre de e_greedy */
// valeur de epsilon en % (de 0 à 100)
int epsilon;

// Fonctions
void initQsa(float qsa[][6], int nbLignesMap, int nbColonnesMap);

#endif