#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED
    #define TAILLE_BLOC         34
    #define NB_BLOC_LARGEUR     12
    #define NB_BLOC_HAUTEUR     12
    #define LARGEUR_FENETRE     TAILLE_BLOC * NB_BLOC_LARGEUR
    #define HAUTEUR_FENETRE     TAILLE_BLOC * (NB_BLOC_HAUTEUR + 2)


    enum {HAUT, BAS, GAUCHE, DROITE};
    enum {MUR, VIDE, OBJECTIF, CAISSE, CAISSE_OK};


//Black:0 - Blue:1 - Green:2 - Cyan:3 - Red:4 - Magenta:5 - Brown:6 - Light Gray:7 - Dark Gray:8 - Light Blue:9
//Light Green:10 - Light Cyan:11 - Light Red:12- Light Magenta:13 - Yellow:14 - White:15
    #define BALCK   0
    #define BLUE    9
    #define GREEN   10
    #define CYAN    11
    #define RED     12
    #define BROWN   6
    #define GRAY    7
    #define YELLOW  14
    #define WHITE   15
#endif // CONSTANTES_H_INCLUDED
