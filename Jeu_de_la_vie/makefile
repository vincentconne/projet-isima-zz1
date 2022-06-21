# compilateur 
CC=gcc
# option
CFLAGS= -g -Wall -Wextra
LDFLAGS= -lSDL2 -lSDL2_ttf

# règle de production finale du TP 
prog:main.o jeu.o SDL.o
	@$(CC) -o prog main.o jeu.o SDL.o $(LDFLAGS)
# règles de production pour chaque fichier
main.o:main.c jeu.h SDL.h
	@$(CC) -c main.c $(CFLAGS)
jeu.o:jeu.c jeu.h
	@$(CC) -c jeu.c $(CFLAGS)
SDL.o:SDL.c SDL.h jeu.h
	@$(CC) -c SDL.c $(CFLAGS)	

# règle qui efface l'exécutable et les fichiers objets
clean:
	@rm -rf prog main.o jeu.o SDL.o *.gch







	
