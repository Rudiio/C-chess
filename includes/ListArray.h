#ifndef LISTARRAY_H
#define LISTARRAY_H

#define N 8

#include <SDL2/SDL.h>
#include "board.h"

typedef struct case_ Case;

struct case_ {
    int piece;
    int color;
};


/*---------------- FOCNTIONS --------------*/

//Fonctions d'initialisation
void Init_board(Case tab[N][N]);
void Init_mortes(Case tab[N][N]);

//Fonctions d'affichage
void print_tab(Case tab[N][N]);

//Fonction de déplacement
void move(Case tab[N][N],int actual_x, int actual_y, int new_x,int new_y);

//fonction d'ajout dans le cimetière
void Ajout_mortes(Case mortes[N][N],int type, int color);



#endif