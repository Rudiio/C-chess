#ifndef LIST_H
#define LIST_H

#include "ListArray.h"

typedef struct List_ List;

struct List_{
    int x;
    int y;
    struct List_ *suivant;
};

/*-----------------FONCTIONS--------------------*/

//fonctions d'initialisation et de rajout de liste
List* Ajout_liste(List* coups,int x, int y);

//fonction d'affichage
void Affiche_liste(List *coups);

//fonction de libération
void libere(List *coups);

//fonction de fusion de listes
List *Link_liste(List *L1, List *L2);

//fonction de vérification de présence dans la liste
int Est_dans_list(List *coups,int x, int y);

//fonction de suppression
List *Supprime_elem(List *coups, int x, int y);

//fonctions de meilleur coups
void meilleurs_IA(List *coups,Case tab[N][N],int *mx,int *my,int *x,int *y,int xpos,int ypos);

#endif