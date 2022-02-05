// Mode de jeu à 2 joueurs

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>


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


int selection_menu()
{
    /*Renvoie la sélection du joueur dans le menu */
    //déclaration des variables
    int x;
    int y;
    int continuer=0;
    //Prise en compte du clic du joueur
    continuer =mouse2(&x,&y);
    
    //1player mode
    if( (WIDTH/4 - CASE_SIZE)<=x && x<=(CASE_SIZE*2+ WIDTH/4 - CASE_SIZE) && (CASE_SIZE*6)<=y && y<=CASE_SIZE*7)
        return 1;

    //2players mode
    if(continuer ==1 && ((2*WIDTH/4 - CASE_SIZE)<=x && x<=(CASE_SIZE*2+ 2*WIDTH/4 - CASE_SIZE) && (CASE_SIZE*6)<=y && y<=CASE_SIZE*7))
        return 2;

    //exit
    if( (continuer ==-1) || ((3*WIDTH/4 - CASE_SIZE)<=x && x<=(CASE_SIZE*2+ 3*WIDTH/4 - CASE_SIZE) && (CASE_SIZE*6)<=y && y<=CASE_SIZE*7))
        return 3;
    
    return(selection_menu());

}

void One_Player(SDL_Window *window, SDL_Renderer *renderer)
{
    /*Joueur vs IA*/
    /*Paramètres du jeu */
    //Initialisation de paramètres d'affichage
    SDL_Texture *board=NULL;
    piece *textures=NULL;
    Case tab[N][N];
    Case mortes[N][N];

    //Paramètres de jeu
    int x,y;
    int continuer=0;
    int current_color=BLANC;
    int colour_IA=BLANC;
    int colour_J=NOIR;
    int change=0;
    
    /*Mise en place du plateau de jeu*/
    //Initialisation de l'échiquier
    Init_board(tab);

    //Initialisation du cimetière
    Init_mortes(mortes);

    //Mise en place de l'échiquier
    background(&renderer); //Affichage du background
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

        if(checkmate(tab,current_color)==1){
            echec_mat_white(&renderer);
            Present_board(&renderer);
            SDL_Delay(1000);
            continuer=-1;
        }

        if(checkmate(tab,current_color)==2){
            echec_mat_black(&renderer);
            Present_board(&renderer);
            SDL_Delay(1000);
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

            if(current_color==colour_IA){
                Coups_IA(tab,colour_IA,mortes);
                SDL_Delay(500);
                background(&renderer); //Affichage du background
                affiche_board(board,&renderer);
                Affiche_pieces_board(tab,textures,&renderer);
                Affiche_pieces_board_mortes(mortes,textures,&renderer);
                Present_board(&renderer);
            }

            if(current_color==colour_J){
                continuer = selection_couleur(tab,&x,&y,current_color,&renderer,textures,board);
                if(continuer!=-1){
                deplacement_possible(tab,x,y,&renderer,textures,board,mortes);
                Pion_To_Reine(tab);
            }
            
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
    SDL_DestroyTexture(board);

}



void Two_Players(SDL_Window *window, SDL_Renderer *renderer)
{
    /*Lance une partie entre 2 joueurs*/

    /*Paramètres du jeu */
    //Initialisation de paramètres d'affichage
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

    //Mise en place de l'échiquier
    background(&renderer); //Affichage du background
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

        if(checkmate(tab,current_color)==1){
            echec_mat_white(&renderer);
            Present_board(&renderer);
            SDL_Delay(1000);
            continuer=-1;
        }

        if(checkmate(tab,current_color)==2){
            echec_mat_black(&renderer);
            Present_board(&renderer);
            SDL_Delay(1000);
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
            continuer = selection_couleur(tab,&x,&y,current_color,&renderer,textures,board);
            if(continuer!=-1){
            deplacement_possible(tab,x,y,&renderer,textures,board,mortes);
            Pion_To_Reine(tab);

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
    SDL_DestroyTexture(board);

}
