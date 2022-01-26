//headers de Jeu.c
#ifndef JEU_H
#define JEU_H


#define N 8
#include "List.h"
#include "ListArray.h"
#include "pieces.h"

/*--------------------- FONCTIONS ----------------------*/

//fonction de vérification de case
int verifie_case(int x , int y,int color,Case tab[N][N]);

//fonction pour les pions
List *Coups_pion(int x, int y, Case tab[N][N]);

//fonction pour les tours
List *Coups_tour(int x, int y,Case tab[N][N]);

//fonction pour les cavaliers
List *Coups_cavalier(int x, int y,Case tab[N][N]);

//fonction pour les fous
List *Coups_fou(int x, int y,Case tab[N][N]);

//fonction pour les reines
List* Coups_reine(int x, int y, Case tab[N][N]);

//fonction pour les rois
List *Coups_roi(int x, int y,Case tab[N][N]);

//fonction de calcul des coups possibles
List *Coups_possibles_piece(int x,int y,Case tab[N][N]);

//déplacement des pièces
int deplacement_possible(Case tab[N][N],int x,int y,SDL_Renderer **renderer,piece *textures,SDL_Texture *board,Case mortes[N][N]);

//sélection des pièces selon la couleur
int selection_couleur(Case tab[N][N],int *x,int *y,int color);

//échec et mat
int echec(Case tab[N][N],int color);
int checkmate(Case tab[N][N]);

#endif