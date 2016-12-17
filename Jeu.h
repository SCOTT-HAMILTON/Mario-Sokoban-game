void Play(SDL_Surface* fenetre);
int initPosDepart(int tab[][NB_BLOCS_LARGEUR], int* posligne, int* poscolonne);
int deplacerMario(SDL_Rect* posMario, int Direction, int vitesseMario, int tab[][NB_BLOCS_LARGEUR], SDL_Rect* posCaisse);
int deplacerCaisse(SDL_Rect* posMario, int tab[][NB_BLOCS_LARGEUR], int vitesseMario, int Direction, SDL_Surface* fenetre, SDL_Surface **Sprite, SDL_Rect* posCaisse);
int quadrillageInf(int val);
int quadrillageSup(int val);
