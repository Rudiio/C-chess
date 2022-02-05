//Fonctions principales de jeu

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "Jeu.h"
#include "input.h"

#define N 8
//define pour les types de pièces
#define PION 1
#define TOUR 2
#define CAVALIER 3
#define FOU 4
#define REINE 5
#define ROI 6

#define NOIR 1
#define BLANC 2

/*----------- fonctions d'évaluation de coups possibles ----------------*/

int verifie_case(int x , int y,int color,Case tab[N][N])
{
    /*Vérifie si une case est disponible ou pas 
    Retourne 0 si la case n'est pas disponible, retourne 1 sinon*/

    
    if(x>=N || x<0 || y<0 || y>=N)
        return 0;

    if(color==NOIR){        
        if(tab[x][y].color==NOIR ){
            return 0;
        }
        
        else {
            return 1;
        }
    }

    else if(color==BLANC){
        
        if(tab[x][y].color==BLANC ){
            return 0;
        }
        else{
            return 1;
        }
    }

    return 0;
}

int verifie_case_echec(int x, int y,int x_a,int y_a,Case tab[N][N])
{
    /* Renvoie 1 si la coup met le roi en échec, renvoie 0 sinon */
    
    //déclaration de variables
    Case copy[N][N];
    Copy_tab(tab,copy);

    int type=tab[x_a][y_a].piece;
    int color=tab[x_a][y_a].color;
    
    copy[x][y].piece=type;
    copy[x][y].color=color;
    copy[x_a][y_a].piece=0;
    copy[x_a][y_a].color=0;

    if(echec(copy,color)==1)
        return 1;
    else    
        return 0;

}


List *Coups_pion(int x, int y, Case tab[N][N])
{
    /* Renvoie une liste contenant les coups possibles pour un pion */
    //déclaration des variables
    List *coups =NULL;
    int color =tab[x][y].color;

    if(color==NOIR){
        if(verifie_case(x+1,y-1,color,tab) && tab[x+1][y-1].color==BLANC)
            coups=Ajout_liste(coups,x+1,y-1);
        if( verifie_case(x+1,y+1,color,tab) && tab[x+1][y+1].color==BLANC)
            coups=Ajout_liste(coups,x+1,y+1);
            
        if(x==1){
            if(verifie_case(x+1,y,color,tab) && tab[x+1][y].color==0){
                coups=Ajout_liste(coups,x+1,y);
                if(verifie_case(x+2,y,color,tab) && tab[x+2][y].color==0){
                    coups=Ajout_liste(coups,x+2,y);
                }
            }
        }
        else{
            if(verifie_case(x+1,y,color,tab) && tab[x+1][y].color==0){
                coups=Ajout_liste(coups,x+1,y);
            }
        }
    }

     if(color==BLANC){
         if(verifie_case(x-1,y-1,color,tab) && tab[x-1][y-1].color==NOIR)
            coups=Ajout_liste(coups,x-1,y-1);
        if(verifie_case(x-1,y+1,color,tab) && tab[x-1][y+1].color==NOIR)
            coups=Ajout_liste(coups,x-1,y+1);

        if(x==6){
            if(verifie_case(x-1,y,color,tab) && tab[x-1][y].color==0){
                coups=Ajout_liste(coups,x-1,y);
            
                if(verifie_case(x-2,y,color,tab) && tab[x-2][y].color==0){
                    coups=Ajout_liste(coups,x-2,y);
                }
            }
        }
        else{
            if(verifie_case(x-1,y,color,tab) && tab[x-1][y].color==0){
                coups=Ajout_liste(coups,x-1,y);
            }
        }
    }
    
    return coups;
}

List *Coups_tour(int x, int y,Case tab[N][N])
{
    /*renvoie une liste contenant les coups possibles pour une tour*/
    //déclaration des variables
    List *coups = NULL;
    int color = tab[x][y].color;
    int i=0,j=0;

    if(color==NOIR){
        //On vérifie les coups possibles vers la gauche
        i=x;
        j=y-1;
        while(verifie_case(x,j,color,tab) && tab[x][j].color!=BLANC && j>=0){
            coups=Ajout_liste(coups,x,j);
            j--;
        }   
        if( j>=0 && (tab[x][j]).color == BLANC ){
            coups=Ajout_liste(coups,x,j);
        }
        
        //On vérifie les coups possibles vers la droite
        i=x;
        j=y+1;
        while(verifie_case(x,j,color,tab) && tab[x][j].color!=BLANC && j<N){
            coups=Ajout_liste(coups,x,j);
            j++;
        }   
        if(j<N && tab[x][j].color == BLANC){
            coups=Ajout_liste(coups,x,j);
        }

        //On vérifie les coups possibles vers le haut
        i=x-1;
        j=y;
        while(verifie_case(i,y,color,tab) && tab[i][y].color!=BLANC && i>=0){
            coups=Ajout_liste(coups,i,y);
            i--;
        }

        if(i>=0 && tab[i][y].color == BLANC){
            coups=Ajout_liste(coups,i,y);
        }

        //On vérifie les coups possibles vers le bas
        i=x+1;
        j=y;
        while(verifie_case(i,y,color,tab) && tab[i][y].color!=BLANC && i<N){
            coups=Ajout_liste(coups,i,y);
            i++;
        }   
        if(i<N && tab[i][y].color == BLANC){
            coups=Ajout_liste(coups,i,y);
        }
    }
    if(color==BLANC){
        //On vérifie les coups possibles vers la gauche
        i=x;
        j=y-1;
        while(verifie_case(x,j,color,tab) && tab[x][j].color!=NOIR && j>=0){
            coups=Ajout_liste(coups,x,j);
            j--;
        }   
        if(j>=0 && tab[x][j].color == NOIR){
            coups=Ajout_liste(coups,x,j);
        }
        
        //On vérifie les coups possibles vers la droite
        i=x;
        j=y+1;
        while(verifie_case(x,j,color,tab) && tab[x][j].color!=NOIR && j<N){
            coups=Ajout_liste(coups,x,j);
            j++;
        }   
        if(j<N && tab[x][j].color == NOIR){
            coups=Ajout_liste(coups,x,j);
        }

        //On vérifie les coups possibles vers le haut
        i=x-1;
        j=y;
        while(verifie_case(i,y,color,tab) && tab[i][y].color!=NOIR && i>=0){
            coups=Ajout_liste(coups,i,y);
            i--;
        }   
        if(i>=0 && tab[i][y].color == NOIR){
            coups=Ajout_liste(coups,i,y);
        }

        //On vérifie les coups possibles vers le bas
        i=x+1;
        j=y;
        while(verifie_case(i,y,color,tab) && tab[i][y].color!=NOIR && i<N){
            coups=Ajout_liste(coups,i,y);
            i++;
        }   
        if(i<N && tab[i][y].color == NOIR){
            coups=Ajout_liste(coups,i,y);
        }

    }
    return coups;
}

List *Coups_cavalier(int x, int y,Case tab[N][N])
{
    /*renvoie une liste contenant les coups possibles pour un cavalier*/
    //déclaration des variables
    List *coups = NULL;
    int color = tab[x][y].color;

    //case 1
    if(verifie_case(x-1,y-2,color,tab))
        coups=Ajout_liste(coups,x-1,y-2);
    
    //case 2
    if(verifie_case(x-2,y-1,color,tab))
        coups=Ajout_liste(coups,x-2,y-1);
    
    //case 3
    if(verifie_case(x-2,y+1,color,tab))
        coups=Ajout_liste(coups,x-2,y+1);
    
    //case 4
    if(verifie_case(x-1,y+2,color,tab))
        coups=Ajout_liste(coups,x-1,y+2);
    
    //case 5
    if(verifie_case(x+1,y+2,color,tab))
        coups=Ajout_liste(coups,x+1,y+2);
    
    //case 6
    if(verifie_case(x+2,y+1,color,tab))
        coups=Ajout_liste(coups,x+2,y+1);
    
    //case 7
    if(verifie_case(x+2,y-1,color,tab))
        coups=Ajout_liste(coups,x+2,y-1);
    
    //case 1
    if(verifie_case(x+1,y-2,color,tab))
        coups=Ajout_liste(coups,x+1,y-2);
    

    return coups;
}

List *Coups_fou(int x, int y,Case tab[N][N])
{
    /*renvoie une liste contenant les coups possibles pour un fou*/
    //déclaration des variables
    List *coups = NULL;
    int couleur = tab[x][y].color;
    int i=0,j=0;

    if(couleur==NOIR){
        //On vérifie les coups possibles vers la diag haut-gauche
        i=x-1;
        j=y-1;

        while(verifie_case(i,j,couleur,tab) && tab[i][j].color!=BLANC && i>=0 && j>=0){
            coups=Ajout_liste(coups,i,j);
            j--;
            i--;
        }   
        if(i>=0 && j>=0 && (tab[i][j]).color== BLANC)
        {
            coups=Ajout_liste(coups,i,j);
        }

        //On vérifie les coups possibles vers la diag haut-droite
        i=x-1;
        j=y+1;

        while(verifie_case(i,j,couleur,tab) && tab[i][j].color!=BLANC && i>=0 && j<N){
            coups=Ajout_liste(coups,i,j);
            j++;
            i--;
        }   

        if(i>=0 && j<N && (tab[i][j]).color == BLANC){
            coups=Ajout_liste(coups,i,j);
        }

        //On vérifie les coups possibles vers la diag bas-droite
        i=x+1;
        j=y+1;
        while(verifie_case(i,j,couleur,tab) && tab[i][j].color!=BLANC && i<N && j<N){
            coups=Ajout_liste(coups,i,j);
            i++;
            j++;
        }   
        if(i<N && j<N && tab[i][j].color == BLANC){
            coups=Ajout_liste(coups,i,j);
        }

        //On vérifie les coups possibles vers la diag bas-gauche
        i=x+1;
        j=y-1;

        while(verifie_case(i,j,couleur,tab) && tab[i][j].color!=BLANC && i<N && j>=0){
            coups=Ajout_liste(coups,i,j);
            i++;
            j--;
        }   
        if(i<N && j>=0 && tab[i][j].color == BLANC){
            coups=Ajout_liste(coups,i,j);
        }
    }
    if(couleur==BLANC){
        //On vérifie les coups possibles vers la diag haut-gauche
        i=x-1;
        j=y-1;
        while(verifie_case(i,j,couleur,tab) && tab[i][j].color!=NOIR && i>=0 && j>=0){
            coups=Ajout_liste(coups,i,j);
            j--;
            i--;
        }   
        if(i>=0 && j>=0 && tab[i][j].color == NOIR){
            coups=Ajout_liste(coups,i,j);
        }
        
        //On vérifie les coups possibles vers la diag haut-droite
        i=x-1;
        j=y+1;
        while(verifie_case(i,j,couleur,tab) && tab[i][j].color!=NOIR && i<N && j<N){
            coups=Ajout_liste(coups,i,j);
            j++;
            i--;
        }   
        if( i<N && j<N && tab[i][j].color == NOIR){
            coups=Ajout_liste(coups,i,j);
        }

        //On vérifie les coups possibles vers la diag bas-droite
        i=x+1;
        j=y+1;
        while(verifie_case(i,j,couleur,tab) && tab[i][j].color!=NOIR && i<N && j<N){
            coups=Ajout_liste(coups,i,j);
            i++;
            j++;
        }   
        if( i<N && j<N && tab[i][j].color == NOIR){
            coups=Ajout_liste(coups,i,j);
        }

        //On vérifie les coups possibles vers la diag bas-gauche
        i=x+1;
        j=y-1;
        while(verifie_case(i,j,couleur,tab) && tab[i][j].color!=NOIR && i<N && j>=0){
            coups=Ajout_liste(coups,i,j);
            i++;
            j--;
        }   
        if(i<N && j>=0 && tab[i][j].color == NOIR ){
            coups=Ajout_liste(coups,i,j);
        }
    }
    return coups;
}   

List* Coups_reine(int x, int y, Case tab[N][N])
{
    /*renvoie une liste contenant les coups possibles pour une reine*/
    //déclaration des variables
    List *coups = NULL;
    List *coups1 =NULL;
    List *coups2 =NULL;

    //calculs des coups
    coups1= Coups_tour(x,y,tab);
    coups2= Coups_fou(x,y,tab);
    coups = Link_liste(coups1,coups2);

    return coups;
}

List *Coups_roi(int x, int y,Case tab[N][N])
{
    /*renvoie une liste contenant les coups possibles pour un roi*/
    //déclaration des variables
    List *coups = NULL;
    int color = tab[x][y].color;
    
    //case du haut
    if(verifie_case(x-1,y,color,tab))
        coups=Ajout_liste(coups,x-1,y);
    
    //case de la diag haut-droite
    if(verifie_case(x-1,y+1,color,tab) )
        coups=Ajout_liste(coups,x-1,y+1);
    
    //case de droite
    if(verifie_case(x,y+1,color,tab) )
        coups=Ajout_liste(coups,x,y+1);
    
    //case de la diag bas-droite
    if(verifie_case(x+1,y+1,color,tab) )
        coups=Ajout_liste(coups,x+1,y+1);
    
    //case du bas
    if(verifie_case(x+1,y,color,tab))
        coups=Ajout_liste(coups,x+1,y);
    
    //case de la diag bas-gauche
    if(verifie_case(x+1,y-1,color,tab) )
        coups=Ajout_liste(coups,x+1,y-1);
    
    //case de gauche
    if(verifie_case(x,y-1,color,tab) )
        coups=Ajout_liste(coups,x,y-1);
    
    //case de la diag haut gauche
    if(verifie_case(x-1,y-1,color,tab) )
        coups=Ajout_liste(coups,x-1,y-1);

    return coups;
}

List *Coups_possibles_piece(int x,int y,Case tab[N][N])
{
    /*Renvoie la liste contenant les coups possibles pour une pièce*/
    List *coups=NULL;
    if(tab[x][y].piece==PION){
        coups=Coups_pion(x,y,tab);
        return coups;
    }
    
    if(tab[x][y].piece==TOUR){
        coups=Coups_tour(x,y,tab);
        return coups;
    }
    
    if(tab[x][y].piece==CAVALIER){
        coups= Coups_cavalier(x,y,tab);
        return coups;
    }
    
    if(tab[x][y].piece==FOU){
        coups=Coups_fou(x,y,tab);
        return coups;
    }
    
    if(tab[x][y].piece==REINE){
        coups=Coups_reine(x,y,tab);
        return coups;
    }
    
    if(tab[x][y].piece==ROI){
        coups= Coups_roi(x,y,tab);
        return coups;
    }

    return NULL;
}

int deplacement_possible(Case tab[N][N],int x,int y,SDL_Renderer **renderer,piece *textures,SDL_Texture *board,Case mortes[N][N])
{
    /* Effectue un déplacement selon les coups possibles pour une pièce */

    //déclaration des variables
    List *coups=NULL;
    int px=-1;
    int py=-1;

    //calculs des coups possibles
    coups = Coups_possibles_piece(x,y,tab);
    // printf("coups avant\n");
    // Affiche_liste(coups);
    coups = Supprime_echec(coups,x,y,tab);
    // printf("coups apres\n");
    // Affiche_liste(coups);
    
    //Affichage des coups possibles
    affiche_board(board,renderer);
    Case_selectionnee(renderer,x,y);
    affiche_coups(coups,renderer);
    Affiche_pieces_board(tab,textures,renderer);
    Present_board(renderer);

    //Prise en compte de la case sélectionnée par le joueur
    mouse(&px,&py);

    //vérification de la case sélectionnée
    if(Est_dans_list(coups,px,py)){
        if(tab[px][py].piece!=0){
            Ajout_mortes(mortes,tab[px][py].piece,tab[px][py].color);
        }
        move(tab,x,y,px,py);         //déplacement de la pièce
        libere(coups);
        return 1;
    }
    else if(tab[px][py].color==tab[x][y].color){
        libere(coups);
        return deplacement_possible(tab,px,py,renderer,textures,board,mortes);
    }
    else{
        libere(coups);
        return deplacement_possible(tab,x,y,renderer,textures,board,mortes);
    }

    return 0;


}

int selection_couleur(Case tab[N][N],int *x,int *y,int color,SDL_Renderer **renderer,piece *textures,SDL_Texture *board)
{
    /*Permet au joueur de sélectionner uniquement des pièces de sa couler */
    int continuer = mouse(x,y);

    //Affichage du coup sélectionné
    // affiche_board(board,renderer);
    // Case_selectionnee(renderer,*x,*y);
    // Affiche_pieces_board(tab,textures,renderer);
    // Present_board(renderer);
    
    if(continuer ==-1)
        return -1;

    if(color==NOIR){
        if(tab[*x][*y].color!=NOIR)
        {
            return selection_couleur(tab,x,y,color,renderer,textures,board);
        }

        else
        {
            return 1;
        }
    }

    if(color==BLANC){
        if(tab[*x][*y].color!=BLANC)
        {
            return selection_couleur(tab,x,y,color,renderer,textures,board);
        }

        else
        {
            return 1;
        }
    }

    return 0;
}

int checkmate(Case tab[N][N],int color)
{
    /*Renvoie 1 si le roi Noir est en échec et mat, renvoie 2 si le roi blanc est en échec.
    Renvoie 0 sinon */

    //déclaration des variables
    List *coups=NULL;
    List *temp=NULL;
    int i,j;

    //Vérification pour les noirs
    if(color==NOIR){
        for(i=0;i<N;i++){
            for(j=0;j<N;j++){
                if(tab[i][j].color==color){
                    temp=Coups_possibles_piece(i,j,tab);
                    temp=Supprime_echec(temp,i,j,tab);
                    coups =Link_liste(coups,temp);
                    temp=NULL;
                }
            }
        }
        if(coups==NULL){
            libere(coups);
            return 1;
        }
    }

    //Vérification pour les  BLANCS
    if(color==BLANC){
        for(i=0;i<N;i++){
            for(j=0;j<N;j++){
                if(tab[i][j].color==color){
                    temp=Coups_possibles_piece(i,j,tab);
                    temp=Supprime_echec(temp,i,j,tab);
                    coups =Link_liste(coups,temp);
                    temp=NULL;
                }
            }
        }
        if(coups==NULL){
            libere(coups);
            return 2;
        }
    }

    libere(coups);
    return 0;


    

    


    // //déclaration des variables
    // List *coups=NULL;
    // List *coups_roi=NULL;
    // List *cur=NULL;
    // int temp=0;
    // int x_roi, y_roi;
    // int x,y;

    // //Vérification pour le roi noir
    // for(x=0;x<N;x++){
    //     for(y=0;y<N;y++){
    //         if(tab[x][y].color==BLANC && tab[x][y].piece!=ROI){
    //             coups =Link_liste(coups,Coups_possibles_piece(x,y,tab));
    //         }
    //         if(tab[x][y].piece==ROI && tab[x][y].color==NOIR){
    //             x_roi =x;
    //             y_roi =y;
    //         }
    //     }
    // }
    // //on liste les coups pour du roi
    // coups_roi=Coups_roi(x_roi,y_roi,tab);
    // coups_roi=Ajout_liste(coups_roi,x_roi,y_roi);

    // //On vérifie si les coups du roi sont dans la liste des coups de toutes les pièces
    // cur=coups_roi;
    // while(cur  && temp==0){
    //     if(Est_dans_list(coups,cur->x,cur->y)==0){
    //         temp=-1;
    //     }
    //     cur=cur->suivant;
    // }
    // // printf("temp= %d",temp);
    // if(temp==0){
    //     libere(coups);
    //     libere(coups_roi);
    //     return 1;
    // }


    // //Pour le roi blanc
    // temp=0;
    // libere(coups);
    // libere(coups_roi);
    // coups=NULL;
    // coups_roi=NULL;
    
    // //Vérification pour le roi blanc
    // for(x=0;x<N;x++){
    //     for(y=0;y<N;y++){
    //         if(tab[x][y].color==NOIR && tab[x][y].piece!=ROI){
    //             coups =Link_liste(coups,Coups_possibles_piece(x,y,tab));
    //         }
    //         if(tab[x][y].piece==ROI && tab[x][y].color==BLANC){
    //             x_roi =x;
    //             y_roi =y;
    //         }
    //     }
    // }

    // //on liste les coups pour du roi
    // coups_roi=Coups_roi(x_roi,y_roi,tab);
    // coups_roi=Ajout_liste(coups_roi,x_roi,y_roi);

    // //On vérifie si les coups du roi sont dans la liste des coups de toutes les pièces
    // cur=coups_roi;
    // while(cur  && temp==0){
    //     if(Est_dans_list(coups,cur->x,cur->y)==0){
    //         temp=-1;
    //     }
    //     cur=cur->suivant;
    // }

    // if(temp==0){
    //     libere(coups);
    //     libere(coups_roi);
    //     return 2;
    // }
    
    // libere(coups);
    // libere(coups_roi);

    // return 0;
}

int echec(Case tab[N][N],int color)
{
    /* Renvoie 1 si le roi est en échec */
        //déclaration des variables
    List *coups=NULL;
    List *temp=NULL;
    int x_roi, y_roi;
    int x,y;

    //Vérification pour le roi noir
    if(color==NOIR){
        for(x=0;x<N;x++){
            for(y=0;y<N;y++){
                if(tab[x][y].color==BLANC && tab[x][y].piece!=ROI){
                    temp=Coups_possibles_piece(x,y,tab);
                    coups =Link_liste(coups,temp);
                    temp=NULL;
                }
                if(tab[x][y].piece==ROI && tab[x][y].color==NOIR){
                    x_roi =x;
                    y_roi =y;
                }
            }
        }
        if(Est_dans_list(coups,x_roi,y_roi)==1){
            libere(coups);
            return 1;
        }
    }

    if(color==BLANC){
        for(x=0;x<N;x++){
            for(y=0;y<N;y++){
                if(tab[x][y].color==NOIR && tab[x][y].piece!=ROI){
                    temp=Coups_possibles_piece(x,y,tab);
                    coups =Link_liste(coups,temp);
                    temp=NULL;
                }
                if(tab[x][y].piece==ROI && tab[x][y].color==BLANC){
                    x_roi =x;
                    y_roi =y;
                }
            }
        }
        if(Est_dans_list(coups,x_roi,y_roi)==1){
            libere(coups);
            return 1;
        }
    }
    libere(coups);

    return 0;
}

void Pion_To_Reine(Case tab[N][N])
{
    /*vérifie si un pion peut être transformé en reine et le transforme si c'est le cas*/

    //déclaration des variables
    int j;

    //pour les pions blancs
    for(j=0;j<N;j++){
        if(tab[0][j].piece==PION && tab[0][j].color==BLANC){
            tab[0][j].piece=REINE;
        }
    }

    //pour les pions noirs
    for(j=0;j<N;j++){
        if(tab[7][j].piece==PION && tab[7][j].color==NOIR){
            tab[7][j].piece=REINE;
        }
    }
}

List *Supprime_echec(List *coups,int x,int y, Case tab[N][N])
{
    /*Supprime de la liste les coups qui mettent le roi en échec*/

    //déclaration des variables
    List *cur=coups;

    while(cur){
        if(verifie_case_echec(cur->x,cur->y,x,y,tab)==1){
            coups=Supprime_elem(coups,cur->x,cur->y);
            cur=coups;
            // printf("echec\n");
        }

        else{
            // printf("pas echec\n");
            cur=cur->suivant;
        }
        // printf("affiche liste coups dans supprime echec\n");
        // Affiche_liste(coups);
    }
    // printf("affiche liste coups dans fin supprime echec\n");
    //     Affiche_liste(coups);
    return coups;
}

void Coups_IA(Case tab[N][N],int color_IA,Case mortes[N][N])
{
    /*Calcule le meilleur coup pour l'IA et déplace la pièce */
    //déclaration des variables
    List *coups=NULL;
    int i;
    int j;
    int x=-1;
    int y=-1;
    int mx=-1;
    int my=-1;

    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            if(tab[i][j].color==color_IA){
                coups=Coups_possibles_piece(i,j,tab);
                coups=Supprime_echec(coups,i,j,tab);

                if(mx==-1 && my==-1 && coups!=NULL){
                    x=i;
                    y=j;
                    mx=coups->x;
                    my=coups->y;
                }

            if(coups!=NULL){
                 meilleurs_IA(coups,tab,&mx,&my,&x,&y,i,j);
            }

            libere(coups);
            coups=NULL;
            }
        }
    }
    libere(coups);

    //Ajout d'une pièce mangée au cimetière
    if(tab[mx][my].piece!=0){
            Ajout_mortes(mortes,tab[mx][my].piece,tab[mx][my].color);
        }
        
    //déplacement de la pièce
    move(tab,x,y,mx,my);

    
}

