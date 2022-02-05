//Gestion de listes pour les déplacements possibles

#include <stdio.h>
#include <stdlib.h>

#include "List.h"

#define N 8


List* Ajout_liste(List* coups,int x, int y)
{
    /*Initialise ou rajoute un nouvel élément à la liste */
    //déckaration des variables
    List *temp=coups;
    List *new=NULL;

    //création de la nouvelle case
    new=(List*)malloc(sizeof(List));
    new->x=x;
    new->y=y;
    new->suivant=NULL;

    //Liste vide
    if(coups==NULL)
        return new;
    
    //Liste non vide
    while(temp->suivant){
        temp=temp->suivant;
    }

    temp->suivant=new;

    return coups;
}

List *Link_liste(List *L1, List *L2)
{
    /* Relie deux listes et renvoie la nouvelle liste */
    //déclaration des variables
    List *cur=L1;

    if(L1 ==NULL && L2==NULL)
        return NULL;
    
    if(L1==NULL)
        return L2;
    
    if(L2==NULL)
        return L1;
        
    while(cur->suivant){
        cur=cur->suivant;
    }

    cur->suivant=L2;

    return L1;
}

void Affiche_liste(List *coups)
{
    /*Affiche une liste*/

    //déclaration des variables
    List *temp=coups;

    while (temp){
        printf("x=%d y=%d \n",temp->x,temp->y);
        temp=temp->suivant;
    }
}

void libere(List *coups)
{
    /* Libère une liste de la mémoire */

    //déclaration des variables
    List *cur=coups;
    List *temp=coups;

    while(cur){
        temp=cur->suivant;
        free(cur);
        cur=temp;
    }

}

int Est_dans_list(List *coups,int x, int y)
{
    /* Renvoie liste s'il existe une case contenant x et y dans la la liste */
    //déclaration des variables
    List *cur =coups;

    if(coups==NULL){
        return 0;
    }
    while(cur){
        if(cur->x==x && cur->y==y)
            return 1;
        cur=cur->suivant;
    }

    return 0;
}

List *Supprime_elem(List *coups, int x, int y)
{
    /* Supprime l'élément de la liste coups contenant x et y */
    // printf("x**%d y**%d\n",x,y);

    //déclaration des variables
    List *cur=coups;
    List *prec=coups;
    // printf("affiche liste debut dans supprime elemc\n");
    // Affiche_liste(coups);

    if(coups->x==x && coups->y==y){
    // printf("affiche liste premier elem dans supprime elemc\n");
    // Affiche_liste(coups);
        prec=coups->suivant;
        free(coups);
        // printf("affiche liste premier elem freee dans supprime elemc\n");
        // Affiche_liste(prec);
        return prec;
    }
    cur=coups->suivant;
    while(cur && cur->x!=x && cur->y!=y){
        prec=cur;
        cur=cur->suivant;
    }
    // printf("affiche liste boucle dans supprime elemc\n");
    // Affiche_liste(coups);

    // printf("affiche liste prec dans supprime elemc\n");
    // Affiche_liste(prec);
    // printf("affiche liste cur dans supprime elemc\n");
    // Affiche_liste(cur);
    prec->suivant=cur->suivant;
    free(cur);

    // printf("affiche liste boucle free dans supprime elemc\n");
    // Affiche_liste(coups);
    return coups;

}

void meilleurs_IA(List *coups,Case tab[N][N],int *mx,int *my,int *x,int *y,int xpos,int ypos)
{
    /*Renvoie le meilleur coup de la liste de coups */
    //déclaration des variables
    List *cur=coups;
    while(cur){
        if(tab[cur->x][cur->y].piece>tab[*mx][*my].piece){
            *mx=cur->x;
            *my=cur->y;
            *x=xpos;
            *y=ypos;
        }
        cur=cur->suivant;
    }

}