#ifndef ia_h
#define ia_h

/* Paramètre de définition du monde */
int nb_etats = 20;
// Valeurs des récompenses

// Valeur moyenne des récompenses
int moy_rec = 5;

// Case de départ

/* Paramètre d'apprentissage */
int nb_epoque = 40;
int nb_itepo = 50;
int xi;
int gamma;

/* Paramètre des états */
// Définition des états

/* Paramètre de e_greedy */
// valeur de epsilon en % (de 0 à 100)
int epsilon;

#endif