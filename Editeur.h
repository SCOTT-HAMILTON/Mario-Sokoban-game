#ifndef EDITEUR_H
#define EDITEUR_H
    // Editeur
    void createLevel(SDL_Surface* fenetre);
    int getQuadrillage(int* value);
    
    // Fichier
    int SetLevel(int tab[][NB_BLOCS_LARGEUR]);
    int test(int tab[][NB_BLOCS_LARGEUR]);
    void testPos(int tab[][NB_BLOCS_LARGEUR], int* posLigne, int* posColonne);
    int GetLevel(int tab[][NB_BLOCS_LARGEUR]);

#endif // EDITEUR_H
