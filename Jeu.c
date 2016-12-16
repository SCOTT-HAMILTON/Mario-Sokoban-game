#include <SDL/SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "Constante.h"
#include "Fichier.h"
#include "Jeu.h"
#include "Fichier.h"

void Play(SDL_Surface* fenetre){
    SDL_Surface *Level, *MarioActuel, *mario[4], *Sprite[NBR_SPRITE_EDITEUR];
    SDL_Rect posLevel, posMario, posSprite[NBR_SPRITE_EDITEUR], posCaisse;
    SDL_Event event;

    int continuer = 1, ligne = -1, colonne = -1, SpriteChoisi = 0, spriteTouche = 0;
    int tabCarte[NB_BLOCS_HAUTEUR][NB_BLOCS_LARGEUR], vitesseMario = TAILLE_BLOC;
    int caisseTouche = 0, Direction = 0;

    SDL_FillRect(fenetre, NULL, SDL_MapRGB(fenetre->format, 255, 255, 255));

    //init Surface
    Level = IMG_Load("IMGEdit/Level.bmp");
    mario[BAS] = IMG_Load("Sprite/mario_bas.gif");
    mario[DROITE] = IMG_Load("Sprite/mario_droite.gif");
    mario[HAUT] = IMG_Load("Sprite/mario_haut.gif");
    mario[GAUCHE] = IMG_Load("Sprite/mario_gauche.gif");

    Sprite[MUR] = IMG_Load("Sprite/mur.jpg");
    Sprite[CAISSE] = IMG_Load("Sprite/caisse.jpg");
    Sprite[OBJECTIF] = IMG_Load("Sprite/objectif.png");
    Sprite[VIDE] = SDL_CreateRGBSurface(SDL_HWSURFACE, TAILLE_BLOC, TAILLE_BLOC, 32, 0, 0, 0, 0);
    Sprite[MARIO] = IMG_Load("Sprite/mario_bas.gif");

    MarioActuel = mario[BAS];

    //init pos Surface
    posLevel.x = 0; posLevel.y = 0;

    //init Basic variables
    GetLevel(tabCarte);

    //init color Surface
    SDL_FillRect(Sprite[VIDE], NULL, SDL_MapRGB(fenetre->format, 255, 255, 255));

    //init carte
    for (ligne = 0; ligne < NB_BLOCS_HAUTEUR; ligne++){
        for (colonne = 0; colonne < NB_BLOCS_LARGEUR; colonne++){
            printf("%c|", tabCarte[ligne][colonne]);
            SpriteChoisi = tabCarte[ligne][colonne];
            switch (SpriteChoisi){
            case '0':
                posSprite[VIDE].y = (Sint16) ligne * TAILLE_BLOC;
                posSprite[VIDE].x = (Sint16) colonne * TAILLE_BLOC;
                SDL_BlitSurface(Sprite[VIDE], NULL, fenetre, &posSprite[VIDE]);
                break;
            case '1':
                posSprite[MUR].y = (Sint16) ligne * TAILLE_BLOC;
                posSprite[MUR].x = (Sint16) colonne * TAILLE_BLOC;
                SDL_BlitSurface(Sprite[MUR], NULL, fenetre, &posSprite[MUR]);
                break;
            case '2':
                posSprite[CAISSE].y = (Sint16) ligne * TAILLE_BLOC;
                posSprite[CAISSE].x = (Sint16) colonne * TAILLE_BLOC;
                SDL_BlitSurface(Sprite[CAISSE], NULL, fenetre, &posSprite[CAISSE]);
                break;
            case '3':
                posSprite[OBJECTIF].y = (Sint16) ligne * TAILLE_BLOC;
                posSprite[OBJECTIF].x = (Sint16) colonne * TAILLE_BLOC;
                SDL_BlitSurface(Sprite[OBJECTIF], NULL, fenetre, &posSprite[OBJECTIF]);
                break;
            case '4':
                posSprite[MARIO].y = (Sint16) ligne * TAILLE_BLOC;
                posSprite[MARIO].x = (Sint16) colonne * TAILLE_BLOC;
                posMario.x = posSprite[MARIO].x;
                posMario.y = posSprite[MARIO].y;
                break;
            }
        }
        printf("\n");
    }
    SDL_Flip(fenetre);
    SDL_SaveBMP(fenetre, "IMGEdit/Level.bmp");
    Level = IMG_Load("IMGEdit/Level.bmp");
    SDL_EnableKeyRepeat(100, 100);
    while (continuer){
        SDL_WaitEvent(&event);
        switch (event.type){
        case SDL_QUIT:
            continuer = 0;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym){
            case SDLK_UP:
                MarioActuel = mario[HAUT];
                Direction = HAUT;
                break;
            case SDLK_DOWN:
                MarioActuel = mario[BAS];
                Direction = BAS;
                break;
            case SDLK_RIGHT:
                MarioActuel = mario[DROITE];
                Direction = DROITE;
                break;
            case SDLK_LEFT:
                MarioActuel = mario[GAUCHE];
                Direction = GAUCHE;
                break;
            default:
                ;
            }
            break;
        }
        if (event.type == SDL_KEYDOWN){
            spriteTouche = deplacerMario(&posMario, Direction, vitesseMario, tabCarte);
        }

        switch (spriteTouche){
        case MUR:
            break;
        case CAISSE:
            deplacerCaisse(&posMario, &posCaisse, tabCarte, vitesseMario, Direction);
            break;
        }

        SDL_BlitSurface(Level, NULL, fenetre, &posLevel);
        SDL_BlitSurface(MarioActuel, NULL, fenetre, &posMario);
        SDL_BlitSurface(Sprite[CAISSE], NULL, fenetre, &posCaisse);

        SDL_Flip(fenetre);
    }
}

int GetLevel(int tab[][NB_BLOCS_LARGEUR]){
    char tabtemp[NB_BLOCS_HAUTEUR * NB_BLOCS_LARGEUR + 1];
    FILE *fichier = NULL;int ligne = 0, colonne = 0, i = 0;
    fichier = fopen("IMGEdit/niveau.txt", "r");
    if (fichier == NULL) return EXIT_FAILURE;
    else{
        for (ligne = 0; ligne < NB_BLOCS_HAUTEUR; ligne++){
            for (colonne = 0; colonne < NB_BLOCS_LARGEUR; colonne++){
                tabtemp[i] = fgetc(fichier);
                tab[ligne][colonne] = tabtemp[i];
                i++;
            }
        }
        fclose(fichier);
    }
    return EXIT_SUCCESS;
}

int initPosDepart(int tab[][NB_BLOCS_LARGEUR], int* posligne, int* poscolonne){
    int ligne = 0, colonne = 0;
    for (ligne = 0; ligne < NB_BLOCS_HAUTEUR; ligne++){
        for (colonne = 0; colonne < NB_BLOCS_LARGEUR; colonne++){
            if (tab[ligne][colonne] == '4'){
                *posligne = ligne;
                *poscolonne = colonne;
                ligne = NB_BLOCS_HAUTEUR;
                colonne = NB_BLOCS_LARGEUR;
            }
        }
    }
    return 0;
}

int deplacerMario(SDL_Rect* posMario, int Direction, int vitesseMario, int tab[][NB_BLOCS_LARGEUR]){
    SDL_Rect pos2, posObstacle;
    int Ligne, Colonne;
    /*Pour connaitre la pos sur la carte du perso*/
    Ligne = quadrillageInf(posMario->y);
    Colonne = quadrillageInf(posMario->x);
    printf("\nLigne:%d, Colonne:%d\n", Ligne, Colonne);
    Ligne /= TAILLE_BLOC;
    Colonne /= TAILLE_BLOC;
    printf("Ligne:%d, Colonne:%d\n", Ligne, Colonne);
        /*gestions des colisions*/
    //les limites de la fenetre
    if (Direction == HAUT && posMario->y <= 0){
        return 0;
    }
    if (Direction == BAS && posMario->y + TAILLE_BLOC >= HAUTEUR_FENETRE){
        return 0;
    }

    if (Direction == GAUCHE && posMario->x <= 0){
        return 0;
    }
    if (Direction == DROITE && posMario->x + TAILLE_BLOC >= LARGEUR_FENETRE){
        return 0;
    }

    //les Mur
    if (tab[Ligne + 1][Colonne] == '1' && Direction == BAS){// si la case du dessous est un mur
        posObstacle.y = quadrillageSup(posMario->y);
        if (posMario->y + TAILLE_BLOC >= posObstacle.y){// si les pieds de mario touche le mur
            return MUR;
        }
    }

    if (tab[Ligne - 1][Colonne] == '1' && Direction == HAUT){// si la case du dessus est un mur
        posObstacle.y = quadrillageInf(posMario->y);
        if (posMario->y <= posObstacle.y){// si la tete de mario touche le mur
            return MUR;
        }
    }

    if (tab[Ligne][Colonne + 1] == '1' && Direction == DROITE){// si la case de droite est un mur
        posObstacle.x = quadrillageSup(posMario->x);
        if (posMario->x + TAILLE_BLOC >= posObstacle.x){// si mario touche le mur
            return MUR;
        }
    }

    if (tab[Ligne][Colonne - 1] == '1' && Direction == GAUCHE){// si la case de gauche est un mur
        posObstacle.x = quadrillageInf(posMario->x);
        if (posMario->x <= posObstacle.x){// si mario touche le mur
            return MUR;
        }
    }

    //les Caisse
    if (tab[Ligne + 1][Colonne] == '2' && Direction == BAS){// si la case du dessous est une caisse
        posObstacle.y = quadrillageSup(posMario->y);
        if (posMario->y + TAILLE_BLOC >= posObstacle.y){// si les pieds de mario touche la caisse
            return CAISSE;
        }
    }

    if (tab[Ligne - 1][Colonne] == '2' && Direction == HAUT){// si la case du dessus est une caisse
        posObstacle.y = quadrillageInf(posMario->y);
        if (posMario->y <= posObstacle.y){// si la tete de mario touche la caisse
            return CAISSE;
        }
    }

    if (tab[Ligne][Colonne + 1] == '2' && Direction == DROITE){// si la case de droite est une caisse
        posObstacle.x = quadrillageSup(posMario->x);
        if (posMario->x + TAILLE_BLOC >= posObstacle.x){// si mario touche la caisse
            return CAISSE;
        }
    }

    if (tab[Ligne][Colonne - 1] == '2' && Direction == GAUCHE){// si la case de gauche est une caisse
        posObstacle.x = quadrillageInf(posMario->x);
        if (posMario->x <= posObstacle.x){// si mario touche la caisse
            return CAISSE;
        }
    }

    //mouvement si on y arrive
    if (Direction == BAS){
        posMario->y += vitesseMario;
    }

    if (Direction == HAUT){
        posMario->y -= vitesseMario;
    }
    if (Direction == DROITE){
        posMario->x += vitesseMario;
    }
    if (Direction == GAUCHE){
        posMario->x -= vitesseMario;
    }
    return 0;
}

int deplacerCaisse(SDL_Rect* posMario, SDL_Rect* posCaisse, int tab[][NB_BLOCS_LARGEUR], int vitesseMario, int Direction){
    int taill_bloc = TAILLE_BLOC * 2;
    int Ligne, Colonne;

    Ligne = quadrillageInf(posMario->y);
    Colonne = quadrillageInf(posMario->x);
    printf("\nLigne:%d, Colonne:%d\n", Ligne, Colonne);
    Ligne /= TAILLE_BLOC;
    Colonne /= TAILLE_BLOC;
    printf("Ligne:%d, Colonne:%d\n", Ligne, Colonne);

    //mur
    if (Direction == HAUT && tab[Ligne - 2][Colonne] == '1'){// si il y a un mur au dessus la caisse
        return 0;
    }

    if (Direction == BAS && tab[Ligne + 2][Colonne] == '1'){// si il y a un mur en dessous la caisse
        return 0;
    }

    //mouvement si on y arrive
    posCaisse = posMario;
    if (Direction == BAS){
        posCaisse->y += taill_bloc;
    }

    if (Direction == HAUT){
        posCaisse->y -= taill_bloc;
    }
    if (Direction == DROITE){
        posCaisse->x += taill_bloc;
    }
    if (Direction == GAUCHE){
        posCaisse->x -= taill_bloc;
    }
}

int quadrillageSup(int val){
    if (val % TAILLE_BLOC != 0){
        while (val % TAILLE_BLOC != 0){
            val++;
        }
    }else{
        val += TAILLE_BLOC;
    }
    return val;
}

int quadrillageInf(int val){
    while (val % TAILLE_BLOC != 0){
        val--;
    }
    return val;
}


