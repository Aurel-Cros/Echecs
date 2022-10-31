#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// fonctions.c
void whatIs(int piece, char *display);
void affichage(int plateau[8][8]);
void resetBoard(int plateau[8][8], int plateauRef[8][8]);

void viderBuffer();
int userInput(char *chaine, int longueur);
int choixCase(int *piece, int *lettre, int *chiffre, int plateau[8][8]);

// fonctionsCheck.c
int checkMove(int posStartX, int posStartY, int posEndX, int posEndY, int plateau[8][8]);
void checkWhat (int typeAtk, int xAtk, int yAtk, int typeDef, int xDef, int yDef);
int checkCheck(int joueur, int plateau[8][8], int alert);
int checkMate(int joueur, int plateau[8][8]);
