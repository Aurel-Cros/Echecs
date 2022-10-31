#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"
#include "structure.h"

int checkMove(int posStartY, int posStartX, int posEndY, int posEndX, int plateau[8][8])
{
    int result = 0, piece = plateau[posStartY][posStartX], target = plateau[posEndY][posEndX], i = 0, diff = 0;
    if ( posEndY < 0 || posEndY > 7 || posEndX < 0 || posEndX > 7 ||
        (plateau[posStartY][posStartX]/10 == plateau[posEndY][posEndX]/10) )
    {
        return 0;
    }
    switch (piece)
    {
        case 10: // Pour les pions blancs
            if ((posStartX==posEndX && (posEndY == posStartY+1 || (posEndY==posStartY+2 && posStartY == 1))) || // Soit on avance de 1, soit de 2 le pion n'a jamais bougé
                (abs(posEndX-posStartX)==1 && posEndY == posStartY+1)) // Soit on avance de 1 en diagonale, pour prendre une pièce
            {
                if (posEndY==posStartY+2 && plateau[posStartY+1][posStartX]!=0) // Si on avance de 2 et que la première case n'est pas vide, c'est NON
                {
                    result = 0;
                }
                else if ((abs(posEndX-posStartX)==1 && posEndY == posStartY+1) && target == 0) // Si mouvement en diagonale, on vérifie la présence d'une cible pour autoriser le mouvement
                {
                    result = 0;
                }
                else
                {
                    result = 1;
                }
            }
            break;
        case 20: // Pions noirs, idem
            if ((posStartX==posEndX && (posEndY == posStartY-1 || (posEndY==posStartY-2 && posStartY == 6))) ||
                (abs(posEndX-posStartX)==1 && posEndY == posStartY-1))
            {
                if (posEndY==posStartY+2 && plateau[posStartY-1][posStartX]!=0)
                {
                    result = 0;
                }
                else if ((abs(posEndX-posStartX)==1 && posEndY == posStartY-1) && target == 0) // Si mouvement en diagonale, on vérifie la présence d'une cible pour autoriser le mouvement
                {
                    result = 0;
                }
                else
                {
                    result = 1;
                }
            }
            break;
        case 11: // Tours blanches et noires
        case 21:
            if (posStartX==posEndX || posStartY==posEndY) // On vérifie qu'elle reste dans la même ligne ou la même colonne, puis on vérifie que le chemin est libre jusqu'à l'arrivée
            {
                result = 1;
                if (posStartX<posEndX) // Si la pièce part à droite
                {
                    diff = posEndX-posStartX;
                    for (i=1;i<diff;i++)
                    {
                        if (plateau[posStartY][posStartX+i]!=0)
                        {
                            result = 0;
                        }
                    }
                }
                else if (posStartX>posEndX)// Si la pièce part à gauche
                {
                    diff = posStartX-posEndX;
                    for (i=1;i<diff;i++)
                    {
                        if (plateau[posStartY][posStartX-i]!=0)
                        {
                            result = 0;
                        }
                    }
                }
                else if (posStartY<posEndY)// Si la pièce part en haut
                {
                    diff = posEndY-posStartY;
                    for (i=1;i<diff;i++)
                    {
                        if (plateau[posStartY+i][posStartX]!=0)
                        {
                            result = 0;
                        }
                    }
                }
                else if (posStartY>posEndY)// Si la pièce part en bas
                {
                    diff = posStartY-posEndY;
                    for (i=1;i<diff;i++)
                    {
                        if (plateau[posStartY-i][posStartX]!=0)
                        {
                            result = 0;
                        }
                    }
                }
            }
            break;
        case 12: // Cavaliers blancs et noirs
        case 22:
            if ((posEndX==posStartX+1 && posEndY==posStartY+2) || (posEndX==posStartX+2 && posEndY==posStartY+1) ||
                (posEndX==posStartX+1 && posEndY==posStartY-2) || (posEndX==posStartX+2 && posEndY==posStartY-1) ||
                (posEndX==posStartX-1 && posEndY==posStartY+2) || (posEndX==posStartX-2 && posEndY==posStartY+1) ||
                (posEndX==posStartX-1 && posEndY==posStartY-2) || (posEndX==posStartX-2 && posEndY==posStartY-1)) // Se déplace forcément de 1 dans un sens et 2 dans l'autre
            {
                result = 1; // Saute, donc on ne vérifie pas le chemin
            }
            break;
        case 13: // Fous blancs et noirs
        case 23:
            if (abs(posEndX-posStartX)==abs(posEndY-posStartY)) // Se déplace forcément en diagonale (différence X/Y entre départ et arrivée identique) - vérification du chemin
            {
                result = 1;
                if (posStartX<posEndX && posStartY<posEndY) //Si la pièce part en haut à droite
                {
                    diff = posEndX-posStartX;
                    for (i=1;i<diff;i++)
                    {
                        if (plateau[posStartY+i][posStartX+i]!=0)
                        {
                            result = 0;
                        }
                    }
                }
                else if (posStartX>posEndX && posStartY<posEndY)// Si la pièce part en haut à gauche
                {
                    diff = posStartX-posEndX;
                    for (i=1;i<diff;i++)
                    {
                        if (plateau[posStartY+i][posStartX-i]!=0)
                        {
                            result = 0;
                        }
                    }
                }
                else if (posStartX<posEndX && posStartY>posEndY)// Si la pièce part en bas droite
                {
                    diff = posEndX-posStartX;
                    for (i=1;i<diff;i++)
                    {
                        if (plateau[posStartY-i][posStartX+i]!=0)
                        {
                            result = 0;
                        }
                    }
                }
                else if (posStartX>posEndX && posStartY>posEndY)// Si la pièce part en bas à gauche
                {
                    diff = posStartY-posEndY;
                    for (i=1;i<diff;i++)
                    {
                        if (plateau[posStartY-i][posStartX-i]!=0)
                        {
                            result = 0;
                        }
                    }
                }
            }
            break;
        case 14: // Reines blanche et noire
        case 24:
            if ((abs(posEndX-posStartX)==abs(posEndY-posStartY)) || ((posStartX==posEndX || posStartY==posEndY))) // En ligne ou en diago
            {
                result = 1;
                if (posStartX<posEndX && posStartY<posEndY) //Si la pièce part en haut à droite
                {
                    diff = posEndX-posStartX;
                    for (i=1;i<diff;i++)
                    {
                        if (plateau[posStartY+i][posStartX+i]!=0)
                        {
                            result = 0;
                        }
                    }
                }
                else if (posStartX>posEndX && posStartY<posEndY)// Si la pièce part en haut à gauche
                {
                    diff = posStartX-posEndX;
                    for (i=1;i<diff;i++)
                    {
                        if (plateau[posStartY+i][posStartX-i]!=0)
                        {
                            result = 0;
                        }
                    }
                }
                else if (posStartX<posEndX && posStartY>posEndY)// Si la pièce part en bas droite
                {
                    diff = posEndX-posStartX;
                    for (i=1;i<diff;i++)
                    {
                        if (plateau[posStartY-i][posStartX+i]!=0)
                        {
                            result = 0;
                        }
                    }
                }
                else if (posStartX>posEndX && posStartY>posEndY)// Si la pièce part en bas à gauche
                {
                    diff = posStartY-posEndY;
                    for (i=1;i<diff;i++)
                    {
                        if (plateau[posStartY-i][posStartX-i]!=0)
                        {
                            result = 0;
                        }
                    }
                }
                else if (posStartX<posEndX) // Si la pièce part à droite
                {
                    diff = posEndX-posStartX;
                    for (i=1;i<diff;i++)
                    {
                        if (plateau[posStartY][posStartX+i]!=0)
                        {
                            result = 0;
                        }
                    }
                }
                else if (posStartX>posEndX)// Si la pièce part à gauche
                {
                    diff = posStartX-posEndX;
                    for (i=1;i<diff;i++)
                    {
                        if (plateau[posStartY][posStartX-i]!=0)
                        {
                            result = 0;
                        }
                    }
                }
                else if (posStartY<posEndY)// Si la pièce part en haut
                {
                    diff = posEndY-posStartY;
                    for (i=1;i<diff;i++)
                    {
                        if (plateau[posStartY+i][posStartX]!=0)
                        {
                            result = 0;
                        }
                    }
                }
                else if (posStartY>posEndY)// Si la pièce part en bas
                {
                    diff = posStartY-posEndY;
                    for (i=1;i<diff;i++)
                    {
                        if (plateau[posStartY-i][posStartX]!=0)
                        {
                            result = 0;
                        }
                    }
                }
            }
            break;
        case 15: // Rois blanc et noir
        case 25:
            if ((abs(posEndX-posStartX)==1 && posStartY==posEndY) || (abs(posEndY-posStartY)==1 && posEndX==posStartX)) // Déplacement de 1 uniquement donc ez
            {
                result = 1;
            }
            break;
    }
    return result;
}

void checkWhat (int typeAtk, int xAtk, int yAtk, int typeDef, int xDef, int yDef)
{
    char atk[4] = {0};
    whatIs(typeAtk, atk);
    char def[4] = {0};
    whatIs(typeDef, def);

    printf("Echec au roi, de %s (%c - %d) sur %s (%c - %d).\n", atk, xAtk+65, yAtk+1, def, xDef+65, yDef+1);
}

int checkCheck(int joueur, int plateau[8][8], int alert)
{
    int i = 0, j = 0, roiX = 0, roiY = 0;
    for (i=0;i<8;i++) // On fouille le plateau jusqu'à trouver le roi du joueur à vérifier
    {
        for (j=0;j<8;j++)
        {
            if (plateau[i][j]==10*joueur+5)
            {
                roiY = i;
                roiX = j;
                i=8;
                break;
            }
        }
    }

    // On vérifie la ligne de vue des pieces adverse
    int reine = (joueur%2+1)*10+4;
    int fou = (joueur%2+1)*10+3;
    int cav = (joueur%2+1)*10+2;
    int tour = (joueur%2+1)*10+1;
    int pion = (joueur%2+1)*10;

    for (i=1;i<(8-roiY);i++)
    {
        if (plateau[roiY+i][roiX]==tour || plateau[roiY+i][roiX]==reine) // Haut
        {
            if (alert)
            {
                checkWhat(plateau[roiY+i][roiX],roiY+i,roiX,plateau[roiY][roiX], roiY, roiX);
            }
            return 1;
        }
        else if (plateau[roiY+i][roiX] != 0) // Si ce n'est pas vide mais pas une piece dangereuse, on casse la boucle et on enchaine
        {
            break;
        }
    }
    for (i=1;i-1<roiY;i++)
    {
        if (plateau[roiY-i][roiX]==tour || plateau[roiY-i][roiX]==reine) // Bas
        {
            if (alert)
            {
                checkWhat(plateau[roiY-i][roiX],roiY-i,roiX,plateau[roiY][roiX], roiY, roiX);
            }
            return 1;
        }
        else if (plateau[roiY-i][roiX] != 0)
        {
            break;
        }
    }
    for (i=1;i<(8-roiX);i++)
    {
        if (plateau[roiY][roiX+i]==tour || plateau[roiY][roiX+i]==reine) // Droite
        {
            if (alert)
            {
                checkWhat(plateau[roiY][roiX+i],roiY+i,roiX,plateau[roiY][roiX], roiY, roiX);
            }
            return 1;
        }
        else if (plateau[roiY][roiX+i] != 0)
        {
            break;
        }
    }
    for (i=1;i-1<roiX;i++)
    {
        if (plateau[roiY][roiX-i]==tour || plateau[roiY][roiX-i]==reine) // Gauche
        {
            if (alert)
            {
                checkWhat(plateau[roiY][roiX-i],roiY+i,roiX,plateau[roiY][roiX], roiY, roiX);
            }
            return 1;
        }
        else if (plateau[roiY][roiX-i] != 0)
        {
            break;
        }
    }

    // On vérifie les fous et reine sur les diagonales, + le pion si distance == +1/+1
    for (i=1 ; i<(8-roiY) && i<(8-roiX); i++) // Haut droite
    {
        if (plateau[roiY+i][roiX+i]==fou || plateau[roiY+i][roiX+i]==reine || (plateau[roiY+i][roiX+i]==pion && i==1))
        {
            if (alert)
            {
                checkWhat(plateau[roiY+i][roiX+i],roiY+i,roiX+i,plateau[roiY][roiX], roiY, roiX);
            }
            return 1;
        }
        else if (plateau[roiY+i][roiX+i] != 0)
        {
            break;
        }
    }
    for (i=1 ; i-1<roiY && i<(8-roiX) ; i++) // Bas droite
    {
        if (plateau[roiY-i][roiX+i]==fou || plateau[roiY-i][roiX+i]==reine || (plateau[roiY-i][roiX+i]==pion && i==1))
        {
            if (alert)
            {
                checkWhat(plateau[roiY-i][roiX+i],roiX-i+65,roiY+i+1,plateau[roiY][roiX], roiX+65, roiX+1);
            }
            return 1;
        }
        else if (plateau[roiY-i][roiX+i] != 0)
        {
            break;
        }
    }
    for (i=1 ;i<(8-roiY) && i-1<roiX ; i++) // Haut gauche
    {
        if (plateau[roiY+i][roiX-i]==fou || plateau[roiY+i][roiX-i]==reine || (plateau[roiY+i][roiX-i]==pion && i==1))
        {
            if (alert)
            {
                checkWhat(plateau[roiY+i][roiX-i],roiY+i,roiX-i,plateau[roiY][roiX], roiY, roiX);
            }
            return 1;
        }
        else if (plateau[roiY+i][roiX-i] != 0)
        {
            break;
        }
    }
    for (i=1 ; i-1<roiY && i-1<roiX ; i++) // Bas gauche
    {
        if (plateau[roiY-i][roiX-i]==fou || plateau[roiY-i][roiX-i]==reine || (plateau[roiY-i][roiX-i]==pion && i==1))
        {
            if (alert)
            {
                checkWhat(plateau[roiY-i][roiX-i],roiY-i,roiX-i,plateau[roiY][roiX], roiY, roiX);
            }
            return 1;
        }
        else if (plateau[roiY-i][roiX-i] != 0)
        {
            break;
        }
    }

    // On vérifie les cavaliers - forcé de faire cas par cas pour éviter des recherches en dehors du tableau lorsque les pieces y sont au bord
    if (roiX>0)
    {
        if(roiY>1)
        {
            if (plateau[roiY-2][roiX-1] == cav)
            {
                if (alert)
                {
                    checkWhat(plateau[roiY-2][roiX-1],roiY-2,roiX-1,plateau[roiY][roiX], roiY, roiX);
                }
                return 1;
            }
        }
        if (roiY<6)
        {
            if (plateau[roiY+2][roiX-1] == cav)
            {
                if (alert)
                {
                    checkWhat(plateau[roiY+2][roiX-1],roiY+2,roiX-1,plateau[roiY][roiX], roiY, roiX);
                }
                return 1;
            }
        }
    }
    if (roiX>1)
    {
        if(roiY>0)
        {
            if (plateau[roiY-1][roiX-2] == cav)
            {
                if (alert)
                {
                    checkWhat(plateau[roiY-1][roiX-2],roiY-1,roiX-2,plateau[roiY][roiX], roiY, roiX);
                }
                return 1;
            }
        }
        if (roiY<7)
        {
            if (plateau[roiY+1][roiX-2] == cav)
            {
                if (alert)
                {
                    checkWhat(plateau[roiY+1][roiX-2],roiY+1,roiX-2,plateau[roiY][roiX], roiY, roiX);
                }
                return 1;
            }
        }
    }
    if (roiX<7)
    {
        if(roiY>1)
        {
            if (plateau[roiY-2][roiX+1] == cav)
            {
                if (alert)
                {
                    checkWhat(plateau[roiY-2][roiX+1],roiY-2,roiX+1,plateau[roiY][roiX], roiY, roiX);
                }
                return 1;
            }
        }
        if (roiY<6)
        {
            if (plateau[roiY+2][roiX+1] == cav)
            {
                if (alert)
                {
                    checkWhat(plateau[roiY+2][roiX+1],roiY+2,roiX+1,plateau[roiY][roiX], roiY, roiX);
                }
                return 1;
            }
        }
    }
    if (roiX<6)
    {
        if(roiY>0)
        {
            if (plateau[roiY-1][roiX+2] == cav)
            {
                if (alert)
                {
                    checkWhat(plateau[roiY-1][roiX+2],roiY-1,roiX+2,plateau[roiY][roiX], roiY, roiX);
                }
                return 1;
            }
        }
        if (roiY<7)
        {
            if (plateau[roiY+1][roiX+2] == cav)
            {
                if (alert)
                {
                    checkWhat(plateau[roiY+1][roiX+2],roiY+1,roiX+2,plateau[roiY][roiX], roiY, roiX);
                }
                return 1;
            }
        }
    }
    return 0; // On n'a rien trouvé, alors on le dit
}

int checkMate(int joueur, int plateau[8][8])
{
    if (!checkCheck(joueur, plateau,0)) // Si le joueur n'est pas en échec, inutile de run la fonction plus loin que ça
    {
        return 0;
    }
    pRest pRest[16] = {{0,0,0}}; // pRest contenant type, x et y pour identifier les pieces restantes et leur position
    int plateauReset[8][8] = {0};
    int nbPieces = 0, i = 0, j = 0, k = 0;

    resetBoard(plateauReset, plateau); // On copie le plateau pour le remettre dans l'état actuel après chaque simulation d'un coup - c'est un poil plus lourd mais plus lisible

    for (i=0;i<8;i++) // On parcours le tableau pour savoir combien de pieces il reste au joueur en échec
    {
        for (j=0;j<8;j++)
        {
            if (plateauReset[i][j]/10==joueur)
            {
                nbPieces++;
                pRest[nbPieces].type = plateauReset[i][j];
                pRest[nbPieces].y = i;
                pRest[nbPieces].x = j;
            }
        }
    }
    for (i=0;i<nbPieces;i++) // On passe chaque pièce en revue et tous ses coups possibles pour voir si l'un d'eux enlève la mise en échec
    {
        switch (pRest[i].type)
        {
        case 10:                                                                            // Check les mouvements de pion
            if (checkMove(pRest[i].y, pRest[i].x, pRest[i].y+1, pRest[i].x, plateauReset)) // Avance de 1
            {
                plateauReset[pRest[i].y+1][pRest[i].x] = pRest[i].type;
                plateauReset[pRest[i].y][pRest[i].x] = 0;
                if (!checkCheck(joueur, plateauReset, 0)) // Si le plateau avec le nouveau mouvement ne contient plus d'échec, on renvoie 0.
                {
                    return 0;
                }
                resetBoard(plateauReset, plateau);
            }
            if (checkMove(pRest[i].y, pRest[i].x, pRest[i].y+2, pRest[i].x, plateauReset) && pRest[i].y == 1) // Avance de 2 si jamais bougé
            {
                plateauReset[pRest[i].y+1][pRest[i].x] = pRest[i].type;
                plateauReset[pRest[i].y][pRest[i].x] = 0;
                if (!checkCheck(joueur, plateauReset, 0))
                {
                    return 0;
                }
                resetBoard(plateauReset, plateau);
            }
            if (checkMove(pRest[i].y, pRest[i].x, pRest[i].y+1, pRest[i].x+1, plateauReset)) // Prise diago droite
            {
                plateauReset[pRest[i].y+1][pRest[i].x+1] = pRest[i].type;
                plateauReset[pRest[i].y][pRest[i].x] = 0;
                if (!checkCheck(joueur, plateauReset, 0))
                {
                    return 0;
                }
                resetBoard(plateauReset, plateau);
            }
            if (checkMove(pRest[i].y, pRest[i].x, pRest[i].y+1, pRest[i].x-1, plateauReset)) // Prise diago gauche
            {
                plateauReset[pRest[i].y+1][pRest[i].x-1] = pRest[i].type;
                plateauReset[pRest[i].y][pRest[i].x] = 0;
                if (!checkCheck(joueur, plateauReset, 0))
                {
                    return 0;
                }
                resetBoard(plateauReset, plateau);
            }
            break;
        case 20:
            if (checkMove(pRest[i].y, pRest[i].x, pRest[i].y-1, pRest[i].x, plateauReset)) // Idem case 10 pour les pions noirs
            {
                plateauReset[pRest[i].y+1][pRest[i].x] = pRest[i].type;
                plateauReset[pRest[i].y][pRest[i].x] = 0;
                if (!checkCheck(joueur, plateauReset, 0))
                {
                    return 0;
                }
                resetBoard(plateauReset, plateau);
            }
            if (checkMove(pRest[i].y, pRest[i].x, pRest[i].y-2, pRest[i].x, plateauReset))
            {
                plateauReset[pRest[i].y+1][pRest[i].x] = pRest[i].type;
                plateauReset[pRest[i].y][pRest[i].x] = 0;
                if (!checkCheck(joueur, plateauReset, 0))
                {
                    return 0;
                }
                resetBoard(plateauReset, plateau);
            }
            if (checkMove(pRest[i].y, pRest[i].x, pRest[i].y-1, pRest[i].x+1, plateauReset))
            {
                plateauReset[pRest[i].y+1][pRest[i].x+1] = pRest[i].type;
                plateauReset[pRest[i].y][pRest[i].x] = 0;
                if (!checkCheck(joueur, plateauReset, 0))
                {
                    return 0;
                }
                resetBoard(plateauReset, plateau);
            }
            if (checkMove(pRest[i].y, pRest[i].x, pRest[i].y-1, pRest[i].x-1, plateauReset))
            {
                plateauReset[pRest[i].y+1][pRest[i].x-1] = pRest[i].type;
                plateauReset[pRest[i].y][pRest[i].x] = 0;
                if (!checkCheck(joueur, plateauReset, 0))
                {
                    return 0;
                }
                resetBoard(plateauReset, plateau);
            }
            break;
        case 11: // Check les axes des tours
        case 21:
            for (k = 1 ; k<8 && checkMove(pRest[i].y, pRest[i].x, pRest[i].y+k, pRest[i].x, plateauReset) ; k++) // Vers le haut
            {
                plateauReset[pRest[i].y+k][pRest[i].x] = pRest[i].type;
                plateauReset[pRest[i].y][pRest[i].x] = 0;
                if (!checkCheck(joueur, plateauReset, 0))
                {
                    return 0;
                }
                resetBoard(plateauReset, plateau);
                if (plateauReset[pRest[i].y-k][pRest[i].x] != 0) // Si on trouve un obstacle, on ira pas plus loin donc on stoppe ce chemin
                {
                    break;
                }
            }
            for (k = 1 ; k<8 && checkMove(pRest[i].y, pRest[i].x, pRest[i].y-k, pRest[i].x, plateauReset) ; k++) // Vers le bas
            {
                plateauReset[pRest[i].y-k][pRest[i].x] = pRest[i].type;
                plateauReset[pRest[i].y][pRest[i].x] = 0;
                if (!checkCheck(joueur, plateauReset, 0))
                {
                    return 0;
                }
                resetBoard(plateauReset, plateau);
                if (plateauReset[pRest[i].y-k][pRest[i].x] != 0)
                {
                    break;
                }
            }
            for (k = 1 ; k<8 && checkMove(pRest[i].y, pRest[i].x, pRest[i].y, pRest[i].x+k, plateauReset) ; k++) // Vers la droite
            {
                plateauReset[pRest[i].y][pRest[i].x+k] = pRest[i].type;
                plateauReset[pRest[i].y][pRest[i].x] = 0;
                if (!checkCheck(joueur, plateauReset, 0))
                {
                    return 0;
                }
                resetBoard(plateauReset, plateau);
                if (plateauReset[pRest[i].y][pRest[i].x+k] != 0)
                {
                    break;
                }
            }
            for (k = 1 ; k<8 && checkMove(pRest[i].y, pRest[i].x, pRest[i].y, pRest[i].x-k, plateauReset) ; k++) // Vers la gauche
            {
                plateauReset[pRest[i].y][pRest[i].x-k] = pRest[i].type;
                plateauReset[pRest[i].y][pRest[i].x] = 0;
                if (!checkCheck(joueur, plateauReset, 0))
                {
                    return 0;
                }
                resetBoard(plateauReset, plateau);
                if (plateauReset[pRest[i].y][pRest[i].x-k] != 0)
                {
                    break;
                }
            }
            break;
        case 13: // Check les diagos des fous
        case 23:
            for (k = 1 ; k<8 && checkMove(pRest[i].y, pRest[i].x, pRest[i].y+k, pRest[i].x+k, plateauReset) ; k++) // Haut/Droite
            {
                plateauReset[pRest[i].y+k][pRest[i].x+k] = pRest[i].type;
                plateauReset[pRest[i].y][pRest[i].x] = 0;
                if (!checkCheck(joueur, plateauReset, 0))
                {
                    return 0;
                }
                resetBoard(plateauReset, plateau);
                if (plateauReset[pRest[i].y-k][pRest[i].x] != 0)
                {
                    break;
                }
            }
            for (k = 1 ; k<8 && checkMove(pRest[i].y-k, pRest[i].x, pRest[i].y+k, pRest[i].x-k, plateauReset) ; k++) // Haut/Gauche
            {
                plateauReset[pRest[i].y-k][pRest[i].x] = pRest[i].type;
                plateauReset[pRest[i].y][pRest[i].x] = 0;
                if (!checkCheck(joueur, plateauReset, 0))
                {
                    return 0;
                }
                resetBoard(plateauReset, plateau);
                if (plateauReset[pRest[i].y-k][pRest[i].x] != 0)
                {
                    break;
                }
            }
            for (k = 1 ; k<8 && checkMove(pRest[i].y, pRest[i].x+k, pRest[i].y-k, pRest[i].x+k, plateauReset) ; k++) // Bas/Droite
            {
                plateauReset[pRest[i].y][pRest[i].x+k] = pRest[i].type;
                plateauReset[pRest[i].y][pRest[i].x] = 0;
                if (!checkCheck(joueur, plateauReset, 0))
                {
                    return 0;
                }
                resetBoard(plateauReset, plateau);
                if (plateauReset[pRest[i].y][pRest[i].x+k] != 0)
                {
                    break;
                }
            }
            for (k = 1 ; k<8 && checkMove(pRest[i].y, pRest[i].x-k, pRest[i].y-k, pRest[i].x-k, plateauReset) ; k++) // Bas/Gauche
            {
                plateauReset[pRest[i].y][pRest[i].x-k] = pRest[i].type;
                plateauReset[pRest[i].y][pRest[i].x] = 0;
                if (!checkCheck(joueur, plateauReset, 0))
                {
                    return 0;
                }
                resetBoard(plateauReset, plateau);
                if (plateauReset[pRest[i].y][pRest[i].x-k] != 0)
                {
                    break;
                }
            }
            break;
        case 14: // Check la reine
        case 24:
            for (k = 1 ; k<8 && checkMove(pRest[i].y, pRest[i].x, pRest[i].y+k, pRest[i].x, plateauReset) ; k++) // Vers le haut
            {
                plateauReset[pRest[i].y+k][pRest[i].x] = pRest[i].type;
                plateauReset[pRest[i].y][pRest[i].x] = 0;
                if (!checkCheck(joueur, plateauReset, 0))
                {
                    return 0;
                }
                resetBoard(plateauReset, plateau);
                if (plateauReset[pRest[i].y-k][pRest[i].x] != 0)
                {
                    break;
                }
            }
            for (k = 1 ; k<8 && checkMove(pRest[i].y, pRest[i].x, pRest[i].y-k, pRest[i].x, plateauReset) ; k++) // Vers le bas
            {
                plateauReset[pRest[i].y-k][pRest[i].x] = pRest[i].type;
                plateauReset[pRest[i].y][pRest[i].x] = 0;
                if (!checkCheck(joueur, plateauReset, 0))
                {
                    return 0;
                }
                resetBoard(plateauReset, plateau);
                if (plateauReset[pRest[i].y-k][pRest[i].x] != 0)
                {
                    break;
                }
            }
            for (k = 1 ; k<8 && checkMove(pRest[i].y, pRest[i].x, pRest[i].y, pRest[i].x+k, plateauReset) ; k++) // Vers la droite
            {
                plateauReset[pRest[i].y][pRest[i].x+k] = pRest[i].type;
                plateauReset[pRest[i].y][pRest[i].x] = 0;
                if (!checkCheck(joueur, plateauReset, 0))
                {
                    return 0;
                }
                resetBoard(plateauReset, plateau);
                if (plateauReset[pRest[i].y][pRest[i].x+k] != 0)
                {
                    break;
                }
            }
            for (k = 1 ; k<8 && checkMove(pRest[i].y, pRest[i].x, pRest[i].y, pRest[i].x-k, plateauReset) ; k++) // Vers la gauche
            {
                plateauReset[pRest[i].y][pRest[i].x-k] = pRest[i].type;
                plateauReset[pRest[i].y][pRest[i].x] = 0;
                if (!checkCheck(joueur, plateauReset, 0))
                {
                    return 0;
                }
                resetBoard(plateauReset, plateau);
                if (plateauReset[pRest[i].y][pRest[i].x-k] != 0)
                {
                    break;
                }
            }
            break;
            for (k = 1 ; k<8 && checkMove(pRest[i].y, pRest[i].x, pRest[i].y+k, pRest[i].x+k, plateauReset) ; k++) // Haut/Droite
            {
                plateauReset[pRest[i].y+k][pRest[i].x] = pRest[i].type;
                plateauReset[pRest[i].y][pRest[i].x] = 0;
                if (!checkCheck(joueur, plateauReset, 0))
                {
                    return 0;
                }
                resetBoard(plateauReset, plateau);
                if (plateauReset[pRest[i].y-k][pRest[i].x] != 0)
                {
                    break;
                }
            }
            for (k = 1 ; k<8 && checkMove(pRest[i].y-k, pRest[i].x, pRest[i].y+k, pRest[i].x-k, plateauReset) ; k++) // Haut/Gauche
            {
                plateauReset[pRest[i].y-k][pRest[i].x] = pRest[i].type;
                plateauReset[pRest[i].y][pRest[i].x] = 0;
                if (!checkCheck(joueur, plateauReset, 0))
                {
                    return 0;
                }
                resetBoard(plateauReset, plateau);
                if (plateauReset[pRest[i].y-k][pRest[i].x] != 0)
                {
                    break;
                }
            }
            for (k = 1 ; k<8 && checkMove(pRest[i].y, pRest[i].x+k, pRest[i].y-k, pRest[i].x+k, plateauReset) ; k++) // Bas/Droite
            {
                plateauReset[pRest[i].y][pRest[i].x+k] = pRest[i].type;
                plateauReset[pRest[i].y][pRest[i].x] = 0;
                if (!checkCheck(joueur, plateauReset, 0))
                {
                    return 0;
                }
                resetBoard(plateauReset, plateau);
                if (plateauReset[pRest[i].y][pRest[i].x+k] != 0)
                {
                    break;
                }
            }
            for (k = 1 ; k<8 && checkMove(pRest[i].y, pRest[i].x-k, pRest[i].y-k, pRest[i].x-k, plateauReset) ; k++) // Bas/Gauche
            {
                plateauReset[pRest[i].y][pRest[i].x-k] = pRest[i].type;
                plateauReset[pRest[i].y][pRest[i].x] = 0;
                if (!checkCheck(joueur, plateauReset, 0))
                {
                    return 0;
                }
                resetBoard(plateauReset, plateau);
                if (plateauReset[pRest[i].y][pRest[i].x-k] != 0)
                {
                    break;
                }
            }
            break;
        case 12: // Les 8 coups des cavaliers
        case 22:
            if (checkMove(pRest[i].y, pRest[i].x, pRest[i].y+1, pRest[i].x+2, plateauReset)) // Avance de 1 + 2
            {
                plateauReset[pRest[i].y+1][pRest[i].x] = pRest[i].type;
                plateauReset[pRest[i].y][pRest[i].x] = 0;
                if (!checkCheck(joueur, plateauReset, 0))
                {
                    return 0;
                }
                resetBoard(plateauReset, plateau);
            }
            if (checkMove(pRest[i].y, pRest[i].x, pRest[i].y+2, pRest[i].x+1, plateauReset)) // Avance de 2 + 1
            {
                plateauReset[pRest[i].y+1][pRest[i].x] = pRest[i].type;
                plateauReset[pRest[i].y][pRest[i].x] = 0;
                if (!checkCheck(joueur, plateauReset, 0))
                {
                    return 0;
                }
                resetBoard(plateauReset, plateau);
            }
            if (checkMove(pRest[i].y, pRest[i].x, pRest[i].y+1, pRest[i].x-2, plateauReset)) // Avance de 1 - 2
            {
                plateauReset[pRest[i].y+1][pRest[i].x] = pRest[i].type;
                plateauReset[pRest[i].y][pRest[i].x] = 0;
                if (!checkCheck(joueur, plateauReset, 0))
                {
                    return 0;
                }
                resetBoard(plateauReset, plateau);
            }
            if (checkMove(pRest[i].y, pRest[i].x, pRest[i].y+2, pRest[i].x-1, plateauReset)) // Avance de 2 - 1
            {
                plateauReset[pRest[i].y+1][pRest[i].x] = pRest[i].type;
                plateauReset[pRest[i].y][pRest[i].x] = 0;
                if (!checkCheck(joueur, plateauReset, 0))
                {
                    return 0;
                }
                resetBoard(plateauReset, plateau);
            }
            if (checkMove(pRest[i].y, pRest[i].x, pRest[i].y-1, pRest[i].x+2, plateauReset)) // Avance de -1 + 2
            {
                plateauReset[pRest[i].y+1][pRest[i].x] = pRest[i].type;
                plateauReset[pRest[i].y][pRest[i].x] = 0;
                if (!checkCheck(joueur, plateauReset, 0))
                {
                    return 0;
                }
                resetBoard(plateauReset, plateau);
            }
            if (checkMove(pRest[i].y, pRest[i].x, pRest[i].y-2, pRest[i].x+1, plateauReset)) // Avance de -2 + 1
            {
                plateauReset[pRest[i].y+1][pRest[i].x] = pRest[i].type;
                plateauReset[pRest[i].y][pRest[i].x] = 0;
                if (!checkCheck(joueur, plateauReset, 0))
                {
                    return 0;
                }
                resetBoard(plateauReset, plateau);
            }
            if (checkMove(pRest[i].y, pRest[i].x, pRest[i].y-1, pRest[i].x-2, plateauReset)) // Avance de -1 - 2
            {
                plateauReset[pRest[i].y+1][pRest[i].x] = pRest[i].type;
                plateauReset[pRest[i].y][pRest[i].x] = 0;
                if (!checkCheck(joueur, plateauReset, 0))
                {
                    return 0;
                }
                resetBoard(plateauReset, plateau);
            }
            if (checkMove(pRest[i].y, pRest[i].x, pRest[i].y-2, pRest[i].x-1, plateauReset)) // Avance de -2 - 1
            {
                plateauReset[pRest[i].y+1][pRest[i].x] = pRest[i].type;
                plateauReset[pRest[i].y][pRest[i].x] = 0;
                if (!checkCheck(joueur, plateauReset, 0))
                {
                    return 0;
                }
                resetBoard(plateauReset, plateau);
            }
            break;
        case 15:
        case 25:
            for (k=-1 ; k < 2 ; k+=2) // On vérifie -1 et +1
            {
                if (checkMove(pRest[i].y, pRest[i].x, pRest[i].y+k, pRest[i].x, plateauReset)) // Vers le haut
                {
                    plateauReset[pRest[i].y+k][pRest[i].x] = pRest[i].type;
                    plateauReset[pRest[i].y][pRest[i].x] = 0;
                    if (!checkCheck(joueur, plateauReset, 0))
                    {
                        return 0;
                    }
                    resetBoard(plateauReset, plateau);
                }
                if (checkMove(pRest[i].y, pRest[i].x, pRest[i].y, pRest[i].x+k, plateauReset)) // Vers la droite
                {
                    plateauReset[pRest[i].y][pRest[i].x+k] = pRest[i].type;
                    plateauReset[pRest[i].y][pRest[i].x] = 0;
                    if (!checkCheck(joueur, plateauReset, 0))
                    {
                        return 0;
                    }
                    resetBoard(plateauReset, plateau);
                }
            }
            break;
        }
    }
    return 1; // Si on a rien trouvé... bah on lui dit que c'est niqué mdr.
}
