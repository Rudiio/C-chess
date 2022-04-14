// Programme principal du jeu

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "2players.h"

#define N 8
//define pour l'affichage
#define CASE_SIZE 85
#define WIDTH 1080
#define HEIGTH 720
#define DX 20
#define DY 20

//define pour les types de pièces
#define PION 1
#define TOUR 2
#define CAVALIER 3
#define FOU 4
#define REINE 5
#define ROI 6

#define NOIR 1
#define BLANC 2


int main(int argc, char **argv)
{   
    //déclaration des variables
    SDL_Window *window=NULL;
    SDL_Renderer *renderer=NULL;
    int sel;

    //création de la fenêtre
    creer_fenetre(&window,&renderer);
    background(&renderer); //Affichage du background
    menu(&renderer);    //Affichage des boutons
    Present_board(&renderer);   

    sel=selection_menu();

    if(sel==1)
        One_Player(window,renderer);
    if(sel==2)
        Two_Players(window,renderer);
    if(sel==3)
        printf("On quitte le jeu");
        
    //Destruction de la fenêtre et du rendu
    Detruire_fenetre(&window,&renderer);
    SDL_Quit();

    return 0;
}