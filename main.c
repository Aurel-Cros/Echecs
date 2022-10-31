#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "fonctions.h"
#include "structure.h"
#define PIECEONTARGET plateau[chiffreTarget][lettreTarget] // C'�tait chiant � �crire alors j'ai fait un define. Voil�.

/* Le plateau est un tableau de 8x8. Leur contenu est d�termin� comme suit :
0 pour une case vide
Dizaine 1 pour le joueur blanc (Joueur 1)
10 pour un pion (P)
11 pour les tours (T)
12 pour les cavaliers (C)
13 pour les fous (J)
14 pour la dame (Q)
15 pour le roi (K)

Dizaine 2 pour le joueur noir (Joueur 2)
20 pour un pion [p]
21 pour les tours [t]
22 pour les cavaliers [c]
23 pour les fous [j]
24 pour la dame [q]
25 pour le roi [k]

De cette fa�on, on peut identifier � qui appartient une piece en divisant son id par 10.

*/
int main(int argc, char *argv[])
{
    // D�but du programme
    int plateau[8][8] = {0}, plateauSave[8][8] = {0};                                            // Cr�ation du plateau
    int joueur = 1, gagnant = 0, abandon = 0, retour = 0, buffer = 0;   // Les variables "de jeu"
    int chiffre = 0, lettre = 0, piece = 0, choixOk = 0;                // Les variables servant au choix de la piece
    int chiffreTarget = 0, lettreTarget = 0, pieceTarget = 0;           // Les variables servant au choix du d�placement
    char pieceAffi[4] = "", rejouer[3] = "";                                             // Pour afficher la piece choisie

    resetBoard(plateau, NULL); // On initialise le plateau
    affichage(plateau); // On affiche le plateau

    while (!gagnant) // D�but de la boucle de jeu, Blanc (J1) commence
    {
    reset:

        choixOk = 0;
        chiffre = 0;
        lettre = 0;
        piece = 0;
        buffer = 0;
        choixOk = 0;
        chiffreTarget = 0;
        lettreTarget = 0;
        pieceTarget = 0;

        // On v�rifie si le joueur est en �chec
        // Si le joueur est en �chec, on l'avertit

        checkCheck(joueur, plateau, 1);

        printf("Joueur %d, choississez une piece a deplacer : ", joueur); // Le joueur choisis une case au format �checs (A1, B4, etc...) ou abandonne la partie ("00")
        do
        {
            abandon = choixCase(&piece, &lettre, &chiffre, plateau);
            if (abandon)
            {
                gagnant = joueur%2+1;
                break;
            }
            else if(piece/10 == 0) // Si c'est une case vide, on redemande une saisie
            {
                printf("Vous ne pouvez pas choisir une case vide, choississez une piece de votre camp : ");
            }
            else if (piece/10 == joueur) // Si la piece lui appartient, on sort de la boucle
            {
                choixOk = 1;
            }
            else // Sinon c'est que la piece est � l'adversaire, on redemande une saisie.
            {
                printf("Vous ne pouvez pas choisir une piece adverse, choississez une piece de votre camp : ");
            }
        } while (!choixOk);
        choixOk = 0;
        if (abandon)
        {
            break;
        }
        whatIs(piece, pieceAffi);
        printf("Vous avez choisis : %s\nChoississez son deplacement : ", pieceAffi); // Une fois la pi�ce valide choisie, il s�lectionne son d�placement
        do
        {
            retour = choixCase(&pieceTarget, &lettreTarget, &chiffreTarget, plateau);
            if (retour)
            {
                goto reset;
            }
            choixOk = checkMove(chiffre, lettre, chiffreTarget, lettreTarget, plateau);
            if (!choixOk)
            {
                printf("Mouvement invalide pour cette piece, recommencez : ");
            }
            else
            {
                choixOk = 0;
                if (PIECEONTARGET == 0) // Si c'est une case vide, le d�placement est valid� !
                {
                    choixOk = 1;
                }
                else if (PIECEONTARGET / 10 == joueur) // Si la case contient une piece du joueur, c'est NON !
                {
                    printf("Cette case est occuppee par une de vos pieces, mouvement impossible. Recommencez : ");
                }
                else // La case est occupee par une piece adverse
                {
                    if (piece%10==0 && lettre==lettreTarget) // Si la piece actuelle est un pion qui avance droit, on dit juste impossible d'avancer et on retourne au d�but du tour
                    {
                        printf("Impossible pour le pion de prendre la piece devant lui. Choississez autre chose.\n");
                        goto reset;
                    }
                    else if (PIECEONTARGET%10 == 5) // Si la pi�ce est un roi, alors il y a un gros probl�me car le roi est d�j� en �chec, on ne devrait donc pas pouvoir jouer "par-dessus"
                    {
                        printf("Cette case est occupee par sa majeste le roi.\nVous ne pouvez pas l'en deloger, mais il comprend que c'est la merde et se rend.");
                        gagnant = joueur; // De fait, on arr�te la partie et on va se plaindre au dev
                        choixOk = 1;
                    }
                    else
                    {
                        choixOk = 1;
                    }
                }
            }
        }
        while (!choixOk);
        choixOk = 0;

        // D�placement
        buffer = PIECEONTARGET;
        PIECEONTARGET = piece; // On met � jour la case d'arriv�e avec la pi�ce d�plac�e
        plateau[chiffre][lettre] = 0; // On vide la case de d�part

        if (checkCheck(joueur, plateau, 0)) // Si le roi est toujours en �chec, on annule le coup et on recommence le tour
        {
            printf("Coup invalide, il y a toujours echec au roi ! Trouvez un autre coup.\n");
            PIECEONTARGET = buffer;
            plateau[chiffre][lettre] = piece;
            goto reset;
        }

        affichage(plateau); // On affiche le plateau mis � jour
        joueur = (joueur%2)+1; // On passe la main � l'adversaire
        resetBoard(plateauSave, plateau); // On sauvegarde le plateau, parfois que checkMate serait destructrice par erreur
        if (checkMate(joueur, plateauSave)) // On v�rifie s'il y a �chec et mat
        {
            gagnant = joueur%2+1;           // Si oui on met fin � la boucle de jeu
            printf("ECHEC ET MAT !! MAGNIFIQUE !\n");
        }
    }
    // Fin de partie, on demande si les joueurs veulent relancer une partie
    printf("\nLe joueur %d remporte la partie ! Quel esprit impitoyable...\n\nLancer une nouvelle partie ? (Y/N) : ", gagnant);
    userInput(rejouer, 3);
    if (toupper(rejouer[0]) == 'Y')
    {
        gagnant = 0;
        resetBoard(plateau, NULL);
        goto reset;
    }

    return 0;
}
