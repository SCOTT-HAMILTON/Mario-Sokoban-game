#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL_image.h>
#include "Constante.h"
#include "Jeu.h"
#include "Jeu.c"
#include "Editeur.h"
#include "Editeur.c"

int main(int argc, char *argv[]){
    SDL_Surface* fenetre, *imgMenu;
    SDL_Rect posImgMenu;
    SDL_Event event;

    int continuer = 1;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_WM_SetIcon(IMG_Load("Sprite/caisse.jpg"), NULL);
    SDL_WM_SetCaption("Mario Sokoban", NULL);
    fenetre = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);

    imgMenu = IMG_Load("Sprite/menu.jpg");
    posImgMenu.x = 0;
    posImgMenu.y = 0;
    SDL_BlitSurface(imgMenu, NULL, fenetre, &posImgMenu);

    while (continuer){
        SDL_WaitEvent(&event);
        switch (event.type){
        case SDL_QUIT:
            continuer = 0;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym){
            case SDLK_ESCAPE:
                continuer = 0;
                break;
            case SDLK_KP1:
                Play(fenetre);
                SDL_BlitSurface(imgMenu, NULL, fenetre, &posImgMenu);
                break;
            case SDLK_KP2:
                createLevel(fenetre);
                SDL_BlitSurface(imgMenu, NULL, fenetre, &posImgMenu);
                break;

            case SDLK_1:
                Play(fenetre);
                SDL_BlitSurface(imgMenu, NULL, fenetre, &posImgMenu);
                break;
            case SDLK_2:
                createLevel(fenetre);
                SDL_BlitSurface(imgMenu, NULL, fenetre, &posImgMenu);
                break;
            default:
                ;
            }
            break;
        }
        SDL_Flip(fenetre);
    }

    SDL_FreeSurface(imgMenu);
    SDL_Quit();
    return EXIT_SUCCESS;
}
