# compilateur 
CC=gcc
# option
CFLAGS= -g -Wall -Wextra
LDFLAGS= -lSDL2 -lSDL2_ttf -lSDL2_image

# règle de production finale du TP 
prog:main.o jeu.o sdl_jeu.o texture.o
	@$(CC) -o prog main.o jeu.o sdl_jeu.o texture.o $(LDFLAGS)
# règles de production pour chaque fichier
main.o:main.c jeu.h sdl_jeu.h texture.h
	@$(CC) -c main.c $(CFLAGS)
jeu.o:jeu.c jeu.h
	@$(CC) -c jeu.c $(CFLAGS)
sdl_jeu.o:sdl_jeu.c sdl_jeu.h jeu.h
	@$(CC) -c sdl_jeu.c $(CFLAGS)
texture.o: texture.c texture.h
	@$(CC) -c texture.c $(CFLAGS)	

# règle qui efface l'exécutable et les fichiers objets
clean:
	@rm -rf prog main.o jeu.o sdl_jeu.o texture.o *.gch







	
