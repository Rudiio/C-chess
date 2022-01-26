#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "ListArray.h"
#include "input.h"

#define N 8

#define PION 1
#define TOUR 2
#define CAVALIER 3
#define FOU 4
#define REINE 5
#define ROI 6

#define NOIR 1
#define BLANC 2

void Init_board(Case tab[N][N])
{
    /*Initialise l'échiquier en plaçant les pieces à leur place */
    
    //déclaration des variables
    int i, j;

    //On remplit le tableau de 0
    for(i=0; i<N ; i++){
        for(j=0; j<N ;j++){
            (tab[i][j]).piece=0;
            (tab[i][j]).color=0;
        }
    }

    //On place les pions à leur place
    for(j=0; j<N ;j++){
        (tab[1][j]).piece=PION;
        (tab[1][j]).color=NOIR;
    }

    for(j=0; j<N ;j++){
        (tab[6][j]).piece=PION;
        (tab[6][j]).color=BLANC;
    }

    //On place les autres pieces
    //Les Tours
    //Noir
    (tab[0][0]).piece=TOUR;
    (tab[0][0]).color=NOIR;
    (tab[0][7]).piece=TOUR;
    (tab[0][7]).color=NOIR;

    //Blanc
    (tab[7][0]).piece=TOUR;
    (tab[7][0]).color=BLANC;
    (tab[7][7]).piece=TOUR;
    (tab[7][7]).color=BLANC;

    //Les cavaliers
    //Noir
    (tab[0][1]).piece=CAVALIER;
    (tab[0][1]).color=NOIR;
    (tab[0][6]).piece=CAVALIER;
    (tab[0][6]).color=NOIR;

    //Blancs
    (tab[7][1]).piece=CAVALIER;
    (tab[7][1]).color=BLANC;
    (tab[7][6]).piece=CAVALIER;
    (tab[7][6]).color=BLANC;

    //Les fous
    //Noir
    (tab[0][2]).piece=FOU;
    (tab[0][2]).color=NOIR;
    (tab[0][5]).piece=FOU;
    (tab[0][5]).color=NOIR;

    //Blancs
    (tab[7][2]).piece=FOU;
    (tab[7][2]).color=BLANC;
    (tab[7][5]).piece=FOU;
    (tab[7][5]).color=BLANC;

    //Les reines
    //Noir
    (tab[0][3]).piece=REINE;
    (tab[0][3]).color=NOIR;

    //Blancs
    (tab[7][3]).piece=REINE;
    (tab[7][3]).color=BLANC;

    //Les rois
    //Noir
    (tab[0][4]).piece=ROI;
    (tab[0][4]).color=NOIR;

    //Blancs
    (tab[7][4]).piece=ROI;
    (tab[7][4]).color=BLANC;
}

void print_tab(Case tab[N][N])
{
    /*Affiche le tableau*/
    //déclaration des variables
    int i;
    int j;

    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            printf("%d ",(tab[i][j]).piece);

        }
        printf("\n");
    }
}

void move(Case tab[N][N],int actual_x, int actual_y, int new_x,int new_y)
{
    /* Déplace une pièce du tableau dans une autres case */

    //Déplacement de la pièce
    (tab[new_x][new_y]).piece=(tab[actual_x][actual_y]).piece;
    (tab[new_x][new_y]).color=(tab[actual_x][actual_y]).color;

    //nettoyage de l'ancienne case
    (tab[actual_x][actual_y]).piece=0;
    (tab[actual_x][actual_y]).color=0;
}

void Init_mortes(Case tab[N][N])
{
    /*Initialise le cimetière en plaçant des 0 partout */
    
    //déclaration des variables
    int i, j;

    //On remplit le tableau de 0
    for(i=0; i<N ; i++){
        for(j=0; j<N ;j++){
            (tab[i][j]).piece=0;
            (tab[i][j]).color=0;
        }
    }
}

void Ajout_mortes(Case mortes[N][N],int type, int color)
{
    /*Ajoute les pièces mortes dans le cimetière */
    //déclaration des variables
    int x=0,y=0;
    if(color == NOIR){
        while(x<2 && mortes[x][y].piece!=0){
            while(y<N && mortes[x][y].piece!=0){
                y++;
            }
        if(mortes[x][y].piece!=0)    
            x++;
        }

    mortes[x][y].piece=type;
    mortes[x][y].color=color;
    }

    if(color == BLANC){
        x=2;
        y=0;
        while(x<4 && mortes[x][y].piece!=0){
            while(y<N && mortes[x][y].piece!=0){
            y++;
            }
        if(mortes[x][y].piece!=0)
            x++;
        }
    mortes[x][y].piece=type;
    mortes[x][y].color=color;
    }
    
}