#ifndef BOARD_H
#define BOARD_H

//headers pour l'affichage
#include <SDL2/SDL.h>

/*---------------FONCTIONS---------------------*/

//fonctions d'affichage
void creer_fenetre(SDL_Window **window, SDL_Renderer **renderer);
void Present_board(SDL_Renderer **renderer);


//Affichage et rechargement de l'échiquier
void affiche_board(SDL_Texture *board,SDL_Renderer **renderer);
void Case_Jaune(SDL_Renderer **renderer, int SDL_x, int SDL_y);
void Case_selectionnee(SDL_Renderer **renderer, int SDL_x, int SDL_y);

//fonctions de destruction
void Detruire_fenetre(SDL_Window **window,SDL_Renderer **renderer);

//affichage du background
void background(SDL_Renderer **renderer);

//affichage du joueur
void white(SDL_Renderer **renderer);
void black(SDL_Renderer **renderer);

//affichage échec
void echec_black(SDL_Renderer **renderer);
void echec_white(SDL_Renderer **renderer);

//affichage echec et mat
void echec_mat_black(SDL_Renderer **renderer);
void echec_mat_white(SDL_Renderer **renderer);

//menu
void menu(SDL_Renderer **renderer);

#endif