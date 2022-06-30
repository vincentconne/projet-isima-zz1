# compilateur 
CC=gcc
# option
CFLAGS= -g -Wall -Wextra -I/opt/homebrew/Cellar/sdl2/2.0.22/include
LDFLAGS= -lSDL2 -lSDL2_ttf -lSDL2_image -lm -L/opt/homebrew/Cellar/sdl2/2.0.22/lib

# règle de production finale du TP 
prog:main.o jeu.o sdl_jeu.o sdl_utils.o ia.o
	@$(CC) -o prog main.o jeu.o sdl_jeu.o sdl_utils.o ia.o $(LDFLAGS)
# règles de production pour chaque fichier
main.o:main.c jeu.h sdl_jeu.h ia.h 
	@$(CC) -c main.c $(CFLAGS)
jeu.o:jeu.c jeu.h
	@$(CC) -c jeu.c $(CFLAGS)
sdl_jeu.o:sdl_jeu.c sdl_jeu.h jeu.h sdl_utils.h
	@$(CC) -c sdl_jeu.c $(CFLAGS)	
sdl_utils.o:sdl_utils.c sdl_utils.h
	@$(CC) -c sdl_utils.c $(CFLAGS)
ia.o:ia.c ia.h jeu.h
	@$(CC) -c ia.c $(CFLAGS)

# règle qui efface l'exécutable et les fichiers objets
clean:
	@rm -rf prog main.o jeu.o sdl_jeu.o sdl_utils.o ia.o *.gch







	
