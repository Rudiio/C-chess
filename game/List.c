//Gestion de listes pour les déplacements possibles

#include <stdio.h>
#include <stdlib.h>

#include "List.h"


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

    //déclaration des variables
    List *cur=coups;
    List *prec=coups;
    
    if(coups->x==x && coups->y==y){
        prec=coups->suivant;
        free(coups);
        return prec;
    }

    while(cur && cur->x!=x && cur->y!=y){
        prec=cur;
        cur=cur->suivant;
    }
    prec->suivant=cur->suivant;
    free(cur);

    return coups;

}


