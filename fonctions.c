#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"
#include "structure.h"

void whatIs(int piece, char *display)
{
    switch (piece)
    {
        case 0:
        case 9:
            sprintf(display, "   ");
            break;
        case 10:
            sprintf(display, "(P)");
            break;
        case 20:
            sprintf(display, "[p]");
            break;
        case 11:
            sprintf(display, "(T)");
            break;
        case 12:
            sprintf(display, "(C)");
            break;
        case 13:
            sprintf(display, "(J)");
            break;
        case 14:
            sprintf(display, "(Q)");
            break;
        case 15:
            sprintf(display, "(K)");
            break;
        case 21:
            sprintf(display, "[t]");
            break;
        case 22:
            sprintf(display, "[c]");
            break;
        case 23:
            sprintf(display, "[j]");
            break;
        case 24:
            sprintf(display, "[q]");
            break;
        case 25:
            sprintf(display, "[k]");
            break;
    }
}

void affichage(int plateau[8][8])
{
    int i = 0, j = 0;
    printf("     _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _  _ _ _ _ _\n\n");
    printf("     A  |  B  |  C  |  D  |  E  |  F  |  G  |  H  | \n\n"); // D'abord la ligne de rep�res en lettres
    for (i=7;i>-1;i--)
    {
        printf("%d |",i+1); // On d�marre chaque ligne par un rep�re num�rique
        for (j=0;j<8;j++) // On boucle pour imprimer les 8 cases de la ligne
        {
            char displayCase[4] = "";
            whatIs(plateau[i][j], displayCase); // On fait une traduction du code piece vers l'affichage utilisateur pour la case en cours et on l'affiche
            printf(" %s |", displayCase);
        }
        printf ("\n\n");
    }
}

void resetBoard(int plateauTarget[8][8], int plateauRef[8][8])
{
    int i = 0, j = 0;
    if (!plateauRef)
    {
        int boardRes[8][8] = {{11,12,13,14,15,13,12,11},{10,10,10,10,10,10,10,10},{0},{0},{0},{0},{20,20,20,20,20,20,20,20},{21,22,23,24,25,23,22,21}};

        for (i=0;i<8;i++)
        {
            for (j=0;j<8;j++)
            {
                plateauTarget[i][j] = boardRes[i][j];
            }
        }
    }
    else
    {
         for (i=0;i<8;i++)
        {
            for (j=0;j<8;j++)
            {
                plateauTarget[i][j] = plateauRef[i][j];
            }
        }
    }
}

void viderBuffer()
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

int userInput(char *chaine, int longueur)
{
    char *positionEntree = NULL;

    if (fgets(chaine, longueur, stdin) != NULL)
    {
        positionEntree = strchr(chaine, '\n');
        if (positionEntree != NULL)
        {
            *positionEntree = '\0';
        }
        else
        {
            viderBuffer();
        }
        return 1;
    }
    else
    {
        viderBuffer();
        return 0;
    }
}

int choixCase(int *square, int *lettre, int *chiffre, int plateau[8][8]) // La fonction renvoie 1 si le joueur en abandonne, avec l'input 00
{
    char *testChoix = NULL;
    char caseChoix[3] = {0};
    int choixOk = 0, chiffreTemp = 0, lettreTemp = 0, pieceTemp = 0;
    while (!choixOk)
    {
        if(userInput(caseChoix,4)) // Le joueur s�lectionne une case
        {
            chiffreTemp = caseChoix[1] - '0'; // On convertit le chiffre entr�e en entier

            testChoix = strpbrk(caseChoix,"abcdefghABCDEFGH"); // On check que la lettre entr�e correspond � une du tableau

            if (testChoix != NULL && chiffreTemp < 9 && chiffreTemp > 0) // On v�rifie qu'on a bien entre A et H et de 1 � 8
            {
                switch (caseChoix[0]) // On convertit la lettre entr�e en rang�e pour notre double tableau
                {
                    case 'a':
                        lettreTemp=0;
                        break;
                    case 'b':
                        lettreTemp=1;
                        break;
                    case 'c':
                        lettreTemp=2;
                        break;
                    case 'd':
                        lettreTemp=3;
                        break;
                    case 'e':
                        lettreTemp=4;
                        break;
                    case 'f':
                        lettreTemp=5;
                        break;
                    case 'g':
                        lettreTemp=6;
                        break;
                    case 'h':
                        lettreTemp=7;
                        break;
                    case 'A':
                        lettreTemp=0;
                        break;
                    case 'B':
                        lettreTemp=1;
                        break;
                    case 'C':
                        lettreTemp=2;
                        break;
                    case 'D':
                        lettreTemp=3;
                        break;
                    case 'E':
                        lettreTemp=4;
                        break;
                    case 'F':
                        lettreTemp=5;
                        break;
                    case 'G':
                        lettreTemp=6;
                        break;
                    case 'H':
                        lettreTemp=7;
                        break;
                    default :
                        lettreTemp=10;
                        break;
                }
                chiffreTemp--; // On enl�ve 1 � l'input utilisateur pour faire correspondre avec notre tableau
                pieceTemp = plateau[chiffreTemp][lettreTemp]; // On r�cup�re quelle piece est sur la case et on indique que le choix est bon
                choixOk = 1;
                *chiffre = chiffreTemp;
                *lettre = lettreTemp;
                *square = pieceTemp;
                return 0;
            }
            else if (caseChoix[0]=='0' && caseChoix[1]=='0')
            {
                return 1;
            }
            else
            {
                printf("Case invalide, veuillez entrer une case valide : ");
            }
        }
        else
        {
            printf("Erreur, la demande d'input a echoue.");
        }
    }
    return 0;
}

