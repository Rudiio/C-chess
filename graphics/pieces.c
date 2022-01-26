#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "pieces.h"
#include "board.h"

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

piece* Init_piece()
{
    /*initialise et renvoie la stucure piece */
    piece *textures=NULL;
    textures=(piece*)malloc(sizeof(piece));

    //Initialisation des pointeurs
    //Pieces blanches
    textures->bP=NULL;
    textures->bT=NULL;
    textures->bC=NULL;
    textures->bF=NULL;
    textures->bQ=NULL;
    textures->bK=NULL;

    //Pieces noires
    textures->wP=NULL;
    textures->wT=NULL;
    textures->wC=NULL;
    textures->wF=NULL;
    textures->wQ=NULL;
    textures->wK=NULL;

    return textures;
}

SDL_Texture* charge_texture(char *s,SDL_Renderer **renderer)
{
    /*charge une texture à partir de son addresse*/
    //déclaration des variables
    SDL_Surface *surface = NULL;
    SDL_Texture *texture= NULL;
    //On charge l'image 
    surface = SDL_LoadBMP(s);

    //On vérifie que l'image a bien été chargée
	if(surface == NULL)
    {
        SDL_Log("ERREUR: Creation de surface echouee > %s\n",SDL_GetError());
	    exit(EXIT_FAILURE);
    }

    //on met la table sur la texture
	texture = SDL_CreateTextureFromSurface(*renderer, surface);

	//On vérife que la texture a bien été chargée
	if(texture == NULL)
    {
        SDL_Log("ERREUR: Creation de tmp echouee > %s\n",SDL_GetError());
	    exit(EXIT_FAILURE);
    }

	//On libère la surface
	 SDL_FreeSurface(surface);

    return texture;
}

void charge_all(piece *textures, SDL_Renderer **renderer)
{
    /*charge toutes les pieces et les met dans la stucture piece*/
    //Pièces noires
    textures->bP=charge_texture("textures/pieces/bP.bmp",renderer);
    textures->bT=charge_texture("textures/pieces/bR.bmp",renderer);
    textures->bC=charge_texture("textures/pieces/bN.bmp",renderer);
    textures->bF=charge_texture("textures/pieces/bB.bmp",renderer);
    textures->bQ=charge_texture("textures/pieces/bQ.bmp",renderer);
    textures->bK=charge_texture("textures/pieces/bK.bmp",renderer);

    //Pièces blanches
    textures->wP=charge_texture("textures/pieces/wP.bmp",renderer);
    textures->wT=charge_texture("textures/pieces/wR.bmp",renderer);
    textures->wC=charge_texture("textures/pieces/wN.bmp",renderer);
    textures->wF=charge_texture("textures/pieces/wB.bmp",renderer);
    textures->wQ=charge_texture("textures/pieces/wQ.bmp",renderer);
    textures->wK=charge_texture("textures/pieces/wK.bmp",renderer);

}


void affiche_piece(SDL_Renderer **renderer, piece *texture, int x, int y, int type,int color)
{
    /*Affiche une pièce type sur l'échiquier à la case x y */

    //creéation du rectangle
    SDL_Rect caze = {DX+x*CASE_SIZE, DY+y*CASE_SIZE, CASE_SIZE, CASE_SIZE};

    //Selection de la texture
    if(color == NOIR){
        if(type == PION){
            SDL_RenderCopy(*renderer, texture->bP, NULL, &caze);
        }
        if(type == TOUR){
            SDL_RenderCopy(*renderer, texture->bT, NULL, &caze);
        }
        if(type == CAVALIER){
            SDL_RenderCopy(*renderer, texture->bC, NULL, &caze);
        }
        if(type == FOU){
            SDL_RenderCopy(*renderer, texture->bF, NULL, &caze);
        }
        if(type == TOUR){
            SDL_RenderCopy(*renderer, texture->bT, NULL, &caze);
        }
        if(type == REINE){
            SDL_RenderCopy(*renderer, texture->bQ, NULL, &caze);
        }
        if(type == ROI){
            SDL_RenderCopy(*renderer, texture->bK, NULL, &caze);
        }
    }
     if(color == BLANC){
        if(type == PION){
            SDL_RenderCopy(*renderer, texture->wP, NULL, &caze);
        }
        if(type == TOUR){
            SDL_RenderCopy(*renderer, texture->wT, NULL, &caze);
        }
        if(type == CAVALIER){
            SDL_RenderCopy(*renderer, texture->wC, NULL, &caze);
        }
        if(type == FOU){
            SDL_RenderCopy(*renderer, texture->wF, NULL, &caze);
        }
        if(type == TOUR){
            SDL_RenderCopy(*renderer, texture->wT, NULL, &caze);
        }
        if(type == REINE){
            SDL_RenderCopy(*renderer, texture->wQ, NULL, &caze);
        }
        if(type == ROI){
            SDL_RenderCopy(*renderer, texture->wK, NULL, &caze);
        }
    }

}

void affiche_piece_mortes(SDL_Renderer **renderer, piece *texture, int x, int y, int type,int color)
{
    /*Affiche une pièce type morte sur l'échiquier à la case x y sur le bas de la fenetres */

    //creéation du rectangle
    SDL_Rect caze = {DX+N*CASE_SIZE + x*CASE_SIZE/2 +CASE_SIZE/4, DY+6*CASE_SIZE + y*CASE_SIZE/2, CASE_SIZE/2, CASE_SIZE/2};

    //Selection de la texture
    if(color == NOIR){
        if(type == PION){
            SDL_RenderCopy(*renderer, texture->bP, NULL, &caze);
        }
        if(type == TOUR){
            SDL_RenderCopy(*renderer, texture->bT, NULL, &caze);
        }
        if(type == CAVALIER){
            SDL_RenderCopy(*renderer, texture->bC, NULL, &caze);
        }
        if(type == FOU){
            SDL_RenderCopy(*renderer, texture->bF, NULL, &caze);
        }
        if(type == TOUR){
            SDL_RenderCopy(*renderer, texture->bT, NULL, &caze);
        }
        if(type == REINE){
            SDL_RenderCopy(*renderer, texture->bQ, NULL, &caze);
        }
        if(type == ROI){
            SDL_RenderCopy(*renderer, texture->bK, NULL, &caze);
        }
    }
     if(color == BLANC){
        if(type == PION){
            SDL_RenderCopy(*renderer, texture->wP, NULL, &caze);
        }
        if(type == TOUR){
            SDL_RenderCopy(*renderer, texture->wT, NULL, &caze);
        }
        if(type == CAVALIER){
            SDL_RenderCopy(*renderer, texture->wC, NULL, &caze);
        }
        if(type == FOU){
            SDL_RenderCopy(*renderer, texture->wF, NULL, &caze);
        }
        if(type == TOUR){
            SDL_RenderCopy(*renderer, texture->wT, NULL, &caze);
        }
        if(type == REINE){
            SDL_RenderCopy(*renderer, texture->wQ, NULL, &caze);
        }
        if(type == ROI){
            SDL_RenderCopy(*renderer, texture->wK, NULL, &caze);
        }
    }

}

void Affiche_pieces_board(Case tab[N][N],piece *texture,SDL_Renderer **renderer)
{
    /*Affiche les pièces sur l'échiquier*/

    //déclaration des variables
    int i;
    int j;

    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            // printf("x =%d y=%d type=%d color=%d \n",i,j,(tab[i][j]).piece,(tab[i][j]).color);
            affiche_piece(renderer,texture,j,i,(tab[i][j]).piece,(tab[i][j]).color);
        }
    }
}

void Affiche_pieces_board_mortes(Case tab[N][N],piece *texture,SDL_Renderer **renderer)
{
    /*Affiche les pièces sur l'échiquier*/

    //déclaration des variables
    int i;
    int j;

    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            // printf("x =%d y=%d type=%d color=%d \n",i,j,(tab[i][j]).piece,(tab[i][j]).color);
            affiche_piece_mortes(renderer,texture,j,i,(tab[i][j]).piece,(tab[i][j]).color);
        }
    }
}

void affiche_coups(List *coups,SDL_Renderer **renderer)
{
    /*Affiche en jaune sur l'échiquier l'ensemble des coups possibles pour les joueur*/
    
    //déclaration des variables
    List *cur=coups;

    while(cur){
        Case_Jaune(renderer,cur->x,cur->y);
        cur=cur->suivant;

    }
}


void libere_piece(piece *texture)
{
    /*Libère la mémoire allouée à la stucture piece*/
    SDL_DestroyTexture(texture->bP);
    SDL_DestroyTexture(texture->bT);
    SDL_DestroyTexture(texture->bC);
    SDL_DestroyTexture(texture->bF);
    SDL_DestroyTexture(texture->bQ);
    SDL_DestroyTexture(texture->bK);
    
    SDL_DestroyTexture(texture->wP);
    SDL_DestroyTexture(texture->wT);
    SDL_DestroyTexture(texture->wC);
    SDL_DestroyTexture(texture->wF);
    SDL_DestroyTexture(texture->wQ);
    SDL_DestroyTexture(texture->wK);

    free(texture);
}
