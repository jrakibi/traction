#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED
#include "jeu.c"
void save_score(SDL_Surface *ecran, char usename[], int level);
void footer_level(SDL_Surface *ecran, int level);
void footer_score(SDL_Surface *ecran);
void show_footer(SDL_Surface *ecran, int level);
int jouer(SDL_Surface *ecran, int niveau, char username[]);
int decaler(SDL_Surface *ecran, SDL_Rect *positionCaisse,int direction, int (*carte)[NB_BLOC_HAUTEUR][NB_BLOC_HAUTEUR]);
int chargerNiveau(SDL_Surface *ecran, int niveauSuivant, int (*carte)[NB_BLOC_HAUTEUR][NB_BLOC_HAUTEUR]);

#endif // JEU_H_INCLUDED
