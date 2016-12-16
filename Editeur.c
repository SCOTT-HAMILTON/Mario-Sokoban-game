#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL_image.h>
#include "Constante.h"
#include "Editeur.h"
#include "Fichier.h"

void createLevel(SDL_Surface* fenetre){
    SDL_Surface *Sprite[NBR_SPRITE_EDITEUR], *Menu, *EditSurface;
    SDL_Event event;SDL_Rect posSprite[NBR_SPRITE_EDITEUR], posMenu;
    SDL_Rect posEditSurface;SDL_Surface *Error, *Success;
    SDL_Rect posError, posSuccess;

    int continuer = 1, pos_sourisX = 0, pos_sourisY = 0, menu = 1;
    int SpriteChoisi = 0;int tabCarte[NB_BLOCS_HAUTEUR][NB_BLOCS_LARGEUR], ligne = 0, colonne = 0;

    SDL_FillRect(fenetre, NULL, SDL_MapRGB(fenetre->format, 255, 255, 255));
    SDL_SaveBMP(fenetre, "IMGEdit/EditFenetre.bmp");

    //init Surface
    Sprite[MUR] = IMG_Load("Sprite/mur.jpg");
    Sprite[CAISSE] = IMG_Load("Sprite/caisse.jpg");
    Sprite[OBJECTIF] = IMG_Load("Sprite/objectif.png");
    Sprite[VIDE] = SDL_CreateRGBSurface(SDL_HWSURFACE, TAILLE_BLOC, TAILLE_BLOC, 32, 0, 0, 0, 0);
    Sprite[MARIO] = IMG_Load("Sprite/mario_bas.gif");
    Menu = IMG_Load("IMGEdit/EditeurMenu.bmp");
    EditSurface = IMG_Load("IMGEdit/EditFenetre.bmp");
    Error = IMG_Load("IMGEdit/Error.png");
    Success = IMG_Load("IMGEdit/Success.png");

    //init pos Surface
    posMenu.x = 0;posMenu.y = 0;
    posEditSurface.x = 0; posEditSurface.y = 0;

    posError.x = 0;posError.y = 0;

    posSuccess.x = fenetre->w / 2 - Success->w / 2;
    posSuccess.y = fenetre->h / 2 - Success->h / 2;

    //init color Surface
    SDL_FillRect(Sprite[VIDE], NULL, SDL_MapRGB(Sprite[VIDE]->format, 255, 255, 255));

    //init Basic variables
    for (ligne = 0; ligne < NB_BLOCS_HAUTEUR; ligne++){
        for (colonne = 0; colonne < NB_BLOCS_LARGEUR; colonne++){
            tabCarte[ligne][colonne] = VIDE;
        }
    }

    while (continuer){
        if (menu == 1){
            SDL_BlitSurface(Menu, NULL, fenetre, &posMenu);
            SDL_WaitEvent(&event);
            switch (event.type){
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_MOUSEBUTTONUP:
                switch (event.button.button){
                case SDL_BUTTON_LEFT:
                    pos_sourisX = (int) event.button.x;
                    pos_sourisY = (int) event.button.y;
                    if (pos_sourisY >= 136 && pos_sourisY <= 136 + TAILLE_BLOC){
                        if(pos_sourisX >= 82 && pos_sourisX <= 82 + TAILLE_BLOC){
                            SpriteChoisi = CAISSE;
                            menu = 0;
                            SDL_BlitSurface(EditSurface, NULL, fenetre, &posEditSurface);
                        }

                        if(pos_sourisX >= 152 && pos_sourisX <= 152 + TAILLE_BLOC){
                            SpriteChoisi = MUR;
                            menu = 0;
                            SDL_BlitSurface(EditSurface, NULL, fenetre, &posEditSurface);
                        }

                        if(pos_sourisX >= 222 && pos_sourisX <= 222 + TAILLE_BLOC){
                            SpriteChoisi = OBJECTIF;
                            menu = 0;
                            SDL_BlitSurface(EditSurface, NULL, fenetre, &posEditSurface);
                        }

                        if(pos_sourisX >= 292 && pos_sourisX <= 292 + TAILLE_BLOC){
                            SpriteChoisi = MARIO;
                            menu = 0;
                            SDL_BlitSurface(EditSurface, NULL, fenetre, &posEditSurface);
                        }
                    }
                }
            }
        }
        else{
            SDL_WaitEvent(&event);
            switch (event.type){
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_MOUSEBUTTONDOWN:
                switch (event.button.button){
                case SDL_BUTTON_LEFT:
                    if (SpriteChoisi == MARIO && test(tabCarte) == EXIT_FAILURE);
                    else{
                        pos_sourisX = (int) event.button.x;
                        pos_sourisY = (int) event.button.y;
                        getQuadrillage(&pos_sourisX);
                        getQuadrillage(&pos_sourisY);
                        posSprite[SpriteChoisi].x = (Sint16) pos_sourisX;
                        posSprite[SpriteChoisi].y = (Sint16) pos_sourisY;
                        SDL_BlitSurface(Sprite[SpriteChoisi], NULL, fenetre, &posSprite[SpriteChoisi]);
                        ligne = pos_sourisY / TAILLE_BLOC;
                        colonne = pos_sourisX / TAILLE_BLOC;
                        tabCarte[ligne][colonne] = SpriteChoisi;
                    }
                    break;
                case SDL_BUTTON_RIGHT:
                    pos_sourisX = (int) event.button.x;
                    pos_sourisY = (int) event.button.y;
                    getQuadrillage(&pos_sourisX);
                    getQuadrillage(&pos_sourisY);
                    posSprite[VIDE].x = (Sint16) pos_sourisX;
                    posSprite[VIDE].y = (Sint16) pos_sourisY;
                    SDL_BlitSurface(Sprite[VIDE], NULL, fenetre, &posSprite[VIDE]);
                    ligne = pos_sourisY / TAILLE_BLOC;
                    colonne = pos_sourisX / TAILLE_BLOC;
                    tabCarte[ligne][colonne] = VIDE;
                }
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym){
                case SDLK_SPACE:
                    SDL_SaveBMP(fenetre, "IMGEdit/EditFenetre.bmp");
                    EditSurface = IMG_Load("IMGEdit/EditFenetre.bmp");
                    Menu = IMG_Load("IMGEdit/EditeurMenu.bmp");
                    menu = 1;
                    break;
                case SDLK_e:
                    ligne = -1;colonne = -1;
                    testPos(tabCarte, &ligne, &colonne);
                    if (ligne != -1 || colonne != -1){
                        ligne *= TAILLE_BLOC;
                        colonne *= TAILLE_BLOC;
                        posSprite[VIDE].x = ligne;
                        posSprite[VIDE].y = colonne;
                        SDL_BlitSurface(Sprite[VIDE], NULL, fenetre, &posSprite[VIDE]);
                        SDL_Flip(fenetre);
                    }
                    if (SetLevel(tabCarte) == EXIT_FAILURE){
                        SDL_BlitSurface(Error, NULL, fenetre, &posError);
                        SDL_Flip(fenetre);
                    }else{
                        SDL_BlitSurface(Success, NULL, fenetre, &posSuccess);
                        SDL_Flip(fenetre);
                    }
                    SDL_Delay(2000);
                case SDLK_DELETE:
                    SDL_FillRect(fenetre, NULL, SDL_MapRGB(fenetre->format, 255, 255, 255));
                    SDL_SaveBMP(fenetre, "IMGEdit/EditFenetre.bmp");
                    EditSurface = IMG_Load("IMGEdit/EditFenetre.bmp");
                    for (ligne = 0; ligne < NB_BLOCS_HAUTEUR; ligne++){
                        for (colonne = 0; colonne < NB_BLOCS_LARGEUR; colonne++){
                            tabCarte[ligne][colonne] = VIDE;
                        }
                    }
                    break;
                default:
                    ;
                }
            }
        }
        SDL_Flip(fenetre);
    }
}

int getQuadrillage(int* value){
    while (*value % TAILLE_BLOC != 0){
        *value -= 1;
    }
    return 0;
}

int SetLevel(int tab[][NB_BLOCS_LARGEUR]){
    FILE *fichier = NULL;int ligne = 0, colonne = 0;
    fichier = fopen("IMGEdit/niveau.txt", "w+");
    if (fichier == NULL) return EXIT_FAILURE;
    else{
        for (ligne = 0; ligne < NB_BLOCS_HAUTEUR; ligne++){
            for (colonne = 0; colonne < NB_BLOCS_LARGEUR; colonne++){
                fprintf(fichier, "%d", (char) tab[ligne][colonne]);
            }
        }
        fclose(fichier);
    }
    return EXIT_SUCCESS;
}

int test(int tab[][NB_BLOCS_LARGEUR]){
    int ligne = 0, colonne = 0;
    for (ligne = 0; ligne < NB_BLOCS_HAUTEUR; ligne++){
            for (colonne = 0; colonne < NB_BLOCS_LARGEUR; colonne++){
                if (tab[ligne][colonne] == MARIO){
                    return EXIT_FAILURE;
                }
            }
    }
    return EXIT_SUCCESS;
}

void testPos(int tab[][NB_BLOCS_LARGEUR], int* posLigne, int* posColonne){
    int ligne = 0, colonne = 0;
    for (ligne = 0; ligne < NB_BLOCS_HAUTEUR; ligne++){
        for (colonne = 0; colonne < NB_BLOCS_LARGEUR; colonne++){
            if (tab[ligne][colonne] == MARIO){
                *posColonne = colonne;
                *posLigne = ligne;
            }
        }
    }
}


