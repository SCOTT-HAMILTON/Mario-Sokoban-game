void Play(SDL_Surface* fenetre);
int initPosDepart(int tab[][NB_BLOCS_LARGEUR], int* posligne, int* poscolonne);
int deplacerMario(SDL_Rect* posMario, int Direction, int vitesseMario, int tab[][NB_BLOCS_LARGEUR], SDL_Surface* fenetre);
int quadrillageInf(int val);
int quadrillageSup(int val);
void printTab(int tab[][NB_BLOCS_LARGEUR]);
int testWin(int tab[][NB_BLOCS_LARGEUR], int nbrObj);

