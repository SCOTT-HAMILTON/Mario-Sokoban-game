#ifndef CONSTANTE_H
#define CONSTANTE_H
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

    // Images
    #ifndef ASSETDIR
    #define ASSETDIR "/usr/local/share/MarioSokoban/assets/"
    #endif

    #define FILE_EDITEUR_MENU    ASSETDIR ""

    #define FILE_EDITEUR_MENU ASSETDIR "IMGEdit/EditeurMenu.bmp"
    #define FILE_EDIT_FENETRE "IMGEdit/EditFenetre.bmp"
    #define FILE_ERROR        ASSETDIR "IMGEdit/Error.bmp"
    #define FILE_GAGNE        ASSETDIR "IMGEdit/Gagne.bmp"
    #define FILE_LEVEL        "IMGEdit/Level.bmp"
    #define FILE_NIVEAU       "IMGEdit/niveau.txt"
    #define FILE_NIVEAU0      ASSETDIR "IMGEdit/niveau0.txt"
    #define FILE_SUCCESS      ASSETDIR "IMGEdit/Success.bmp"

    #define FILE_MARIO_HAUT   ASSETDIR "Sprite/mario_haut.gif"
    #define FILE_MENU         ASSETDIR "Sprite/menu.jpg"
    #define FILE_MARIO_BAS    ASSETDIR "Sprite/mario_bas.gif"
    #define FILE_MARIO_GAUCHE ASSETDIR "Sprite/mario_gauche.gif"
    #define FILE_OBJECTIF     ASSETDIR "Sprite/objectif.png"
    #define FILE_CAISSE       ASSETDIR "Sprite/caisse.jpg"
    #define FILE_CAISSE_OK    ASSETDIR "Sprite/caisse_ok.jpg"
    #define FILE_MUR          ASSETDIR "Sprite/mur.jpg"
    #define FILE_MARIO_DROITE ASSETDIR "Sprite/mario_droite.gif"
#endif // CONSTANTE_H
