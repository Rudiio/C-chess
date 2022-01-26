#ifndef PIECES_H
#define PIECES_H

#include <SDL2/SDL.h>
#include "ListArray.h"
#include "List.h"

typedef struct piece_ piece;

struct piece_{
    SDL_Texture *wP;
    SDL_Texture *wT;
    SDL_Texture *wC;
    SDL_Texture *wF;
    SDL_Texture *wQ;
    SDL_Texture *wK;
    SDL_Texture *bP;
    SDL_Texture *bT;
    SDL_Texture *bC;
    SDL_Texture *bF;
    SDL_Texture *bQ;
    SDL_Texture *bK;
};


/*-----------------FONCTIONS----------------*/

//fonctions d'initialisation
piece* Init_piece();

//fonctions de chargement de texture
SDL_Texture* charge_texture(char *s,SDL_Renderer **renderer);
void charge_all(piece *textures, SDL_Renderer **renderer);

//fonctions d'affichage des pièces
void affiche_piece(SDL_Renderer **renderer, piece *texture, int x, int y, int type,int color);
void Affiche_pieces_board(Case tab[N][N],piece *texture,SDL_Renderer **renderer);
void affiche_coups(List *coups,SDL_Renderer **renderer);
void affiche_piece_mortes(SDL_Renderer **renderer, piece *texture, int x, int y, int type,int color);
void Affiche_pieces_board_mortes(Case tab[N][N],piece *texture,SDL_Renderer **renderer);

//fonction de libération de mémoire
void libere_piece(piece *texture);


#endif