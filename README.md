# Projet ZZ1 ISIMA - Groupe 1 - CONNE RUSAK WALCH

Projet de première année ISIMA effectué par le **groupe 1** composé de **Vincent CONNE, Loup RUSAK et Mathilde WALCH**.

***

## X Fenêtré

Dans le dossier **X_fenetre**, vous trouverez **3 sous dossiers** contenant chacun de nos exemples.

Cet exercice avait pour but de nous faire créer des fenêtres, de les déplacer et de les fermer, en manipulant la SDL2.

***

## Pavé de serpents

Comme pour le X_fenetre, vous trouverez 3 sous dossiers de Pave_serpents contenant chacun de nos exemples.

Cet exercice avait pour but de nous faire manipuler les fonctions de bases au niveau des rendus dans une fenêtre, en manipulant des formes, des couleurs ...

***

## Animation de sprites

Comme pour les derniers exercices, vous trouverez 3 sous dossiers de contenant chacun de nos exemples.

Cet exercice avait pour but de apprendre le manipulation de sprite et donc d'images avec SDL2, SDL2_TTF et SDL2_image, notamment en affichant un fond de fenêtre ou en animant une image de personnage.

***

## Jeu de la vie

**Automate cellulaire** dont les règles ont été définies par J. Conway en 1970.

### Principe

L'état de l'automate à l'étape n se crée en fonction de l'état à l'étape n-1. 
L'évolution de l'état d'une cellule dépend de ses huit états voisins les plus proches. 

Les règles:  
* A l'étape suivante, l'étape n-1 occupera une cellule vide avec seulement 3 cellules adjacentes. (Naissance liée à l'environnement optimal)
On utilise un tableau de booléens ```SURVIE``` pour mettre en forme les règles. 
* Les cellules qui sont occupées au niveau n-1 et qui ont deux ou trois cellules adjacentes sont conservées au niveau n. Sinon, il sera vide. (Mort due à la désertification ou à la surpopulation)
Comme pour la survie on utilise aussi un tableau de booléens ```NAISSANCE```.

### Comment jouer ?

1. Vous êtes au menu, choisissez entre les deux modes :
    * **Monde délimité**
    * **Monde thorique**

2. Vous arrivez maintenant sur une page blanche. Vous pouvez soit placer les premières cellules à votre guise à l'aide de la souris ou alors appuyer sur la touche **l** pour charger une configuration fichier texte existante.

3. Si vous avez choisi de placer les cellules par vous-même, appuyez sur **espace** pour lancer le jeu de la vie.

4. Vous voyez maintenant le jeu se dérouler sous vos yeux et vous ralentir le processus en appuyant sur la **flèche du bas** ou alors l'accelérer avec **flèche du haut**.

5. Cas possibles :
    * Si le monde devient vide alors le message *"cycle"* sera écrit.

    * Si le monde devient stable et ne bouge plus alors le message *"monde stable"* sera écrit.

    Dans les deux cas quittez le jeu en appuyant sur la croix pour fermer la fenêtre.

***

## Notre Chef d'oeuvre : ATTENTION DANGER !

Le but de cet exercice, était de proposer un jeu intégrant le principe de la chaîne de Markov.

### Principe

Nous avons donc décidé de proposer un jeu mettant en scène une voiture et des portions de route qui se ferment et se rouvrent selon une chaine de markov se basant sur l'état précédent de la route. L’objectif du jeu étant de ne rouler que sur les routes ouvertes. 

### Comment jouer ?

1. Vous êtes au menu, les règles et commandes sont rappelées dans la partie inférieur de l'interface. Pour débuter cliquez sur le bandeau ***jouer***.

2. Vous arrivez maintenant sur la page de jeu. Vous pouvez prendre le temps de vous familiariser avec de décors et par la suite appuyer sur la touche **espace** pour débuter la "run".

3. Votre objectif est d'éviter les travaux en vous déplaçant de droite à gauche sur la route et faire le score le plus élevé possible. 
    * Pour vous déplacer à droite d'une portion de route appuyez sur la **flèche droite**.
    * Pour vous déplacer à gauche d'une portion de route appuyez sur la **flèche gauche**.

5. Lorsque vous heurtez une zone de chantier avec votre voiture, vous perdez et une fenetre avec votre score est alors affichée.

6. Pour quitter le jeu, appuyez sur la croix de la fenêtre.

***

## Notre Jeu par apprentissage par renforcement : <insérez un nom>

*à venir :P*
 

