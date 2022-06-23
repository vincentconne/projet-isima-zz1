#include <stdlib.h>
#include <stdio.h>
#include "jeu.h"
#include "sdl_jeu.h"

int main(int argc,char *argv){
    (void) argc;
    (void) argv;


int tab_markov[7][7];

// Initialisation de la table de Markov

// Ligne 0
tab_markov[0][0]=1; tab_markov[0][1]=2; tab_markov[0][2]=2; tab_markov[0][3]=2;
tab_markov[0][4]=1; tab_markov[0][5]=1; tab_markov[0][6]=1;


// Ligne 1
tab_markov[1][0]=1; tab_markov[1][1]=2; tab_markov[1][2]=1; tab_markov[1][3]=3;
tab_markov[1][4]=2; tab_markov[1][5]=0; tab_markov[1][6]=1;

// Ligne 2
tab_markov[2][0]=1; tab_markov[2][1]=1; tab_markov[2][2]=2; tab_markov[2][3]=3;
tab_markov[2][4]=0; tab_markov[2][5]=2; tab_markov[2][6]=1;

// Ligne 3
tab_markov[3][0]=1; tab_markov[3][1]=3; tab_markov[3][2]=3; tab_markov[3][3]=1;
tab_markov[3][4]=1; tab_markov[3][5]=1; tab_markov[3][6]=0;

// Ligne 4
tab_markov[4][0]=5; tab_markov[4][1]=0; tab_markov[4][2]=0; tab_markov[4][3]=0;
tab_markov[4][4]=5; tab_markov[4][5]=0; tab_markov[4][6]=0;

// Ligne 5
tab_markov[5][0]=5; tab_markov[5][1]=0; tab_markov[5][2]=0; tab_markov[5][3]=0;
tab_markov[5][4]=0; tab_markov[5][5]=5; tab_markov[5][6]=0;

// Ligne 6
tab_markov[6][0]=5; tab_markov[6][1]=0; tab_markov[6][2]=0; tab_markov[6][3]=0;
tab_markov[6][4]=0; tab_markov[6][5]=0; tab_markov[6][6]=5;


/*-------------------------------------------------------------------------------*/


// Etat courant
int *etat_cour = (int*) malloc(sizeof(int)*3);


// Table des etats
int **tab_etats = (int **)malloc(sizeof(int*)*5);
for (int i=0;i<3;i++){
    tab_etats[i]= (int *)malloc(sizeof(int)*3);
}
for (int k=0; k<3; k++){
    for (int l =0; l<5; l++){
        tab_etats[k][l]=0;
    }
}

// Indice de début de ligne qui correspond à la première ligne en affichage
int premier;

// Indice de début de ligne qui correspond à la dernière ligne en affichage
int dernier;

// Libération des tableaux dynamiques
free(etat_cour);

for(int i=0;i<5;i++){
    free(tab_etats[i]);
}
free(tab_etats);


// Lancement de l'introduction du jeu
Intro_jeu();


return 0;

}