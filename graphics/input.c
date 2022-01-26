#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>


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


int mouse(int *x, int *y)
{
    /* Prend en charge les clics de la souris et renvoie la position du clic */
    SDL_Event event;
    int sx;
    int sy;

    while(1){
        //Attente d'un évènement
        SDL_WaitEvent(&event);

        switch(event.type){     //choix multiple
            case SDL_QUIT:
                return -1;

            case SDL_MOUSEBUTTONDOWN:       //Un bouton de la souris est préssée
                
                //Positions de la souris
				sy=event.button.x;
				sx=event.button.y;

                //Conversion des positions en cases
                if((DX<=sx && sx<=DX+(N*CASE_SIZE)) && (DY<=sy && sy<=(DY+N*CASE_SIZE))){
                    *x=(sx-DX)/CASE_SIZE;
                    *y=(sy-DY)/CASE_SIZE;

                    return 1;
                }

                return -1;
            case SDL_KEYDOWN :
                switch(event.key.keysym.sym){
                    case SDLK_ESCAPE:
                    return -1;
                }
        }
    }

}