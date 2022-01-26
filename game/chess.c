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
    Two_Players();

    return 0;
}