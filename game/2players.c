// Mode de jeu à 2 joueurs

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "board.h"
#include "2players.h"
#include "input.h"
#include "Jeu.h"

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

void Two_Players()
{
    /*Lance une partie entre 2 joueurs*/

    /*Paramètres du jeu */
    //Initialisation de paramètres d'affichage
    SDL_Window *window=NULL;
    SDL_Renderer *renderer=NULL;
    SDL_Texture *board=NULL;
    piece *textures=NULL;
    Case tab[N][N];
    Case mortes[N][N];

    //Paramètres de jeu
    int x,y;
    int continuer=0;
    int current_color=BLANC;
    int change=0;

    /*Mise en place du plateau de jeu*/
    //Initialisation de l'échiquier
    Init_board(tab);

    //Initialisation du cimetière
    Init_mortes(mortes);

    //création de la fenêtre
    creer_fenetre(&window,&renderer);
    background(&renderer); //Affichage du background

    //Mise en place de l'échiquier
    board=charge_texture("textures/board.bmp", &renderer);
    affiche_board(board,&renderer);

    //Initialisation des textures
    textures=Init_piece();
    charge_all(textures,&renderer);

    //Affichage des pièces en début de jeu
    Affiche_pieces_board(tab,textures,&renderer);
    Present_board(&renderer);

    while(continuer!=-1){
        change =0;
        if(echec(tab,current_color)==1){
                if(current_color==NOIR){
                    echec_black(&renderer);
                }
                else{
                    echec_white(&renderer);
                }
            }

        if(checkmate(tab)==1){
            echec_mat_white(&renderer);
            continuer=-1;
        }

        if(checkmate(tab)==2){
            echec_mat_black(&renderer);
            continuer=-1;
        }

        if(current_color==BLANC){
            white(&renderer);
        }
        else{
            black(&renderer);
        }
        Present_board(&renderer);
        
        if(continuer!=-1){
            continuer = selection_couleur(tab,&x,&y,current_color);
            if(continuer!=-1){
            deplacement_possible(tab,x,y,&renderer,textures,board,mortes);

            // MAJ de l'échiquier
            background(&renderer); //Affichage du background
            affiche_board(board,&renderer);
            Affiche_pieces_board(tab,textures,&renderer);
            Affiche_pieces_board_mortes(mortes,textures,&renderer);
            Present_board(&renderer);
            }
        }

        if(current_color==BLANC && change==0){
            current_color=NOIR;
            change = 1;
        }
        if(current_color==NOIR && change==0){
            current_color=BLANC;
            change = 1;
        }
        
    }
    //destruction de la fenêtre
    libere_piece(textures);
    Detruire_fenetre(&window,&renderer);
    SDL_DestroyTexture(board);

}
