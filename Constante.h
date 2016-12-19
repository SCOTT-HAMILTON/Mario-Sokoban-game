#ifndef DEF_Constante
#define DEF_Constante
    #define TAILLE_BLOC         34
    #define NB_BLOCS_LARGEUR    12
    #define NB_BLOCS_HAUTEUR    12
    #define LARGEUR_FENETRE     TAILLE_BLOC * NB_BLOCS_LARGEUR
    #define HAUTEUR_FENETRE     TAILLE_BLOC * NB_BLOCS_HAUTEUR
    #define NBR_SPRITE_EDITEUR 5
    #define HAUTEUR_MARIO 28
    #define LARGEUR_MARIO 20
    #define DIFF_MARIO_Y 6
    #define DIFF_MARIO_X 12

    enum {HAUT, BAS, GAUCHE, DROITE};
    enum {VIDE, MUR, CAISSE, OBJECTIF, MARIO, CAISSE_OK};
    enum {WIN, LOSE};

#endif // Constante_h_
