void Play(SDL_Surface* fenetre);
int initPosDepart(int tab[][NB_BLOCS_LARGEUR], int* posligne, int* poscolonne);
int deplacerMario(SDL_Rect* posMario, int Direction, int vitesseMario, int tab[][NB_BLOCS_LARGEUR]);
int deplacerCaisse(SDL_Rect* posMario, SDL_Rect* Caisse, int tab[][NB_BLOCS_LARGEUR], int vitesseMario, int Direction);
int quadrillageInf(int val);
int quadrillageSup(int val);
