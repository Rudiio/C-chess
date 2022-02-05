// Création et affichage de la fenêtre et du damier

#include <stdio.h>
#include <stdlib.h>

#include "board.h"
#include "pieces.h"

//define pour l'affichage
#define CASE_SIZE 85
#define WIDTH 1080
#define HEIGTH 720
#define DX 20
#define DY 20
#define CONTOUR 2

//define pour les types de pièces
#define PION 1
#define TOUR 2
#define CAVALIER 3
#define FOU 4
#define REINE 5
#define ROI 6

#define NOIR 1
#define BLANC 2

void creer_fenetre(SDL_Window **window, SDL_Renderer **renderer)
{
    /*Initialise la SDL: crée la fenêtre et le rendu */

    //Initilise la SDL
    if (SDL_Init(SDL_INIT_VIDEO)==-1){
		SDL_Log("ERREUR: Initialisation echouee> %s\n",SDL_GetError()); //Affichage de l'erreur
		exit(EXIT_FAILURE);		//On quitte le programme
    }

    //taille de la fenêtre
	int L=WIDTH;
	int l=HEIGTH;
    *window=NULL;
	*window =SDL_CreateWindow("CCHESS",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED ,L,l,SDL_WINDOW_RESIZABLE);

    //Vérification de la création de la fenêtre
	if(*window == NULL){
		SDL_Log("ERREUR: Creation de fenetre echouee > %s\n",SDL_GetError());
		exit(EXIT_FAILURE);
	}

    //Création du rendu
    *renderer=NULL;
	*renderer= SDL_CreateRenderer(*window,-1,SDL_RENDERER_ACCELERATED);

    //Vérification de la création du rendu
	if(*renderer==NULL){
		SDL_Log("ERREUR: Creation de fenetre echouee > %s\n",SDL_GetError());
		exit(EXIT_FAILURE);
	}

    // //Coloriage du fond
	// SDL_SetRenderDrawColor(*renderer, 255, 255, 250, 255); 
	// SDL_RenderClear(*renderer);

}



void affiche_board(SDL_Texture *board,SDL_Renderer **renderer)
{
	/*Affiche ou recharge l'échiquier sur la fenetre*/

	SDL_Rect dst = {DX, DY, 8*CASE_SIZE , 8*CASE_SIZE};
    SDL_RenderCopy(*renderer, board, NULL, &dst);

}


void background(SDL_Renderer **renderer)
{
	/* Affiche le background de la fenêtre */

	//chargement de la texture
	SDL_Texture *back=charge_texture("textures/background.bmp",renderer);

	SDL_Rect dst = {0, 0, WIDTH, HEIGTH};
    SDL_RenderCopy(*renderer, back, NULL, &dst);

	SDL_DestroyTexture(back);
}

void white(SDL_Renderer **renderer)
{
	/* Affiche sur le coté que  c'est au joueur blanc de jouer*/
	//chargement de la texture
	SDL_Texture *white=charge_texture("textures/button_white-player.bmp",renderer);
	
	SDL_Rect dst = {DX+ N*CASE_SIZE + 63, DY + CASE_SIZE/2, 255,66 };
    SDL_RenderCopy(*renderer, white, NULL, &dst);

	SDL_DestroyTexture(white);
}

void black(SDL_Renderer **renderer)
{
	/* Affiche sur le coté que c'est au jouer noir de jouer */
	//chargement de la texture
	SDL_Texture *black=charge_texture("textures/button_black-player.bmp",renderer);
	
	SDL_Rect dst = {DX+ N*CASE_SIZE + 63, DY + CASE_SIZE/2, 255,66 };
    SDL_RenderCopy(*renderer, black, NULL, &dst);

	SDL_DestroyTexture(black);
}

void echec_black(SDL_Renderer **renderer)
{
	/* Affiche sur le coté que c'est au jouer noir de jouer */
	//chargement de la texture
	SDL_Texture *black=charge_texture("textures/button_echec-noir.bmp",renderer);
	
	SDL_Rect dst = {DX+ N*CASE_SIZE + 63, DY + 2*CASE_SIZE, 255,66 };
    SDL_RenderCopy(*renderer, black, NULL, &dst);

	SDL_DestroyTexture(black);
}

void echec_mat_black(SDL_Renderer **renderer)
{
	/* Affiche sur le coté que c'est au jouer noir de jouer */
	//chargement de la texture
	SDL_Texture *black=charge_texture("textures/button_mat_noir.bmp",renderer);
	
	SDL_Rect dst = {DX+ N*CASE_SIZE + 63, DY + 2*CASE_SIZE, 255,66 };
    SDL_RenderCopy(*renderer, black, NULL, &dst);

	SDL_DestroyTexture(black);
}

void echec_mat_white(SDL_Renderer **renderer)
{
	/* Affiche sur le coté que c'est au jouer noir de jouer */
	//chargement de la texture
	SDL_Texture *black=charge_texture("textures/button_mat_blanc.bmp",renderer);
	
	SDL_Rect dst = {DX+ N*CASE_SIZE + 63, DY + 2*CASE_SIZE, 255,66 };
    SDL_RenderCopy(*renderer, black, NULL, &dst);

	SDL_DestroyTexture(black);
}

void echec_white(SDL_Renderer **renderer)
{
	/* Affiche sur le coté que c'est au jouer noir de jouer */
	//chargement de la texture
	SDL_Texture *black=charge_texture("textures/button_echec-blanc.bmp",renderer);
	
	SDL_Rect dst = {DX+ N*CASE_SIZE + 63, DY + 2*CASE_SIZE, 255,66 };
    SDL_RenderCopy(*renderer, black, NULL, &dst);

	SDL_DestroyTexture(black);
}

void Present_board(SDL_Renderer **renderer)
{
	/*Affiche sur la fenêtre ce qui est contenu sur le  rendu*/
	SDL_RenderPresent(*renderer);
}

void Case_Jaune(SDL_Renderer **renderer, int SDL_x, int SDL_y)
{
	/* Colorie une case en jaune transparent (pour les cases compatibles) */

	//Le rectangle sur lequel on mettra la texture
	SDL_Rect rect ={0,0, CASE_SIZE-CONTOUR, CASE_SIZE-CONTOUR };
	SDL_Texture *texture=NULL;

	texture = SDL_CreateTexture(*renderer, SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET, CASE_SIZE-CONTOUR, CASE_SIZE-CONTOUR);
	//On vérifie si la texture a bien été chargée
	if(texture == NULL)
    {
        SDL_Log("ERREUR: Creation de tmp echouee > %s\n",SDL_GetError());
	    exit(EXIT_FAILURE);
    }
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND); //Transparence
	SDL_SetRenderDrawColor(*renderer, 238, 232, 170, 200); //On peint en jaune
	SDL_SetRenderTarget(*renderer, texture); /* On va dessiner sur la texture */
	SDL_RenderFillRect(*renderer, &rect);
	SDL_SetRenderTarget(*renderer, NULL);

	SDL_Rect rect2 ={DY + SDL_y*CASE_SIZE+CONTOUR,DX + SDL_x*CASE_SIZE +CONTOUR , CASE_SIZE-2*CONTOUR , CASE_SIZE-2*CONTOUR};
	SDL_RenderCopy(*renderer, texture, NULL, &rect2);

	SDL_DestroyTexture(texture);

}

void Case_selectionnee(SDL_Renderer **renderer, int SDL_x, int SDL_y)
{
	/* Colorie une case en jaune transparent (pour les cases compatibles) */

	//Le rectangle sur lequel on mettra la texture
	SDL_Rect rect ={0,0, CASE_SIZE-CONTOUR, CASE_SIZE-CONTOUR };
	SDL_Texture *texture=NULL;

	texture = SDL_CreateTexture(*renderer, SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET, CASE_SIZE-CONTOUR, CASE_SIZE-CONTOUR);
	//On vérifie si la texture a bien été chargée
	if(texture == NULL)
    {
        SDL_Log("ERREUR: Creation de tmp echouee > %s\n",SDL_GetError());
	    exit(EXIT_FAILURE);
    }
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND); //Transparence
	SDL_SetRenderDrawColor(*renderer, 154, 205, 50, 200); //On peint en jaune
	SDL_SetRenderTarget(*renderer, texture); /* On va dessiner sur la texture */
	SDL_RenderFillRect(*renderer, &rect);
	SDL_SetRenderTarget(*renderer, NULL);

	SDL_Rect rect2 ={DY + SDL_y*CASE_SIZE+CONTOUR,DX + SDL_x*CASE_SIZE +CONTOUR , CASE_SIZE-2*CONTOUR , CASE_SIZE-2*CONTOUR};
	SDL_RenderCopy(*renderer, texture, NULL, &rect2);

	SDL_DestroyTexture(texture);

}

void menu(SDL_Renderer **renderer)
{
	/*Affiche le menu du jeu */

	//chargement de la texture
	SDL_Texture *logo=charge_texture("textures/logo.bmp",renderer);
	
	SDL_Rect dst = {WIDTH/3 -CASE_SIZE/2, DY, CASE_SIZE+ WIDTH/3,400 };
    SDL_RenderCopy(*renderer, logo, NULL, &dst);

	SDL_DestroyTexture(logo);

	SDL_Texture *bouton_1P=charge_texture("textures/button_1p.bmp",renderer);
	SDL_Texture *bouton_2P=charge_texture("textures/button_2p.bmp",renderer);
	SDL_Texture *bouton_quit=charge_texture("textures/button_quit.bmp",renderer);

	SDL_Rect dst1={WIDTH/4 - CASE_SIZE ,CASE_SIZE*6,CASE_SIZE*2, CASE_SIZE};
	SDL_Rect dst2={2*WIDTH/4 - CASE_SIZE, CASE_SIZE*6,CASE_SIZE*2,CASE_SIZE};
	SDL_Rect dst3={3*WIDTH/4 - CASE_SIZE ,CASE_SIZE*6,CASE_SIZE*2,CASE_SIZE};

	SDL_RenderCopy(*renderer, bouton_1P, NULL, &dst1);
	SDL_DestroyTexture(bouton_1P);
	SDL_RenderCopy(*renderer, bouton_2P, NULL, &dst2);
	SDL_DestroyTexture(bouton_2P);
	SDL_RenderCopy(*renderer, bouton_quit, NULL, &dst3);
	SDL_DestroyTexture(bouton_quit);
}

void Detruire_fenetre(SDL_Window **window,SDL_Renderer **renderer)
{
    /*Detruit la fenetre et le rendu*/
    SDL_DestroyRenderer(*renderer);
    SDL_DestroyWindow(*window);

    
}