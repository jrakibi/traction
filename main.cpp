#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "constantes.h"
#include "jeu.h"
#include "functions.h"
#include "score.h"
int main( int argc, char** argv ){

    //ces 2 lignes permet d'afficher le text dans la console meme en utilisant SDL
    freopen("CON", "w", stdout);
    freopen("CON", "w", stderr);

    char check_input[100];
    int i = 0;
    do{
    if(i!=0){
        textcolor(RED);
        printf("\nVeuillez entrer 1 ou 2 SVP \n");
        textcolor(GRAY);
    }
    textcolor(WHITE);
    printf("\n\n\n\n");
    printf(" _________________________________________________________________ \n");
    printf("|                                                                 |\n");
    printf("|                                                                 |\n");
    printf("|                                                                 |\n");
    printf("|            1- Vous avez deja un compte                          |\n");
    printf("|            2- Vous voulez creer un compte un compte             |\n");
    printf("|                                                                 |\n");
    printf("|                                                                 |\n");
    printf("|                                                                 |\n");
    printf(" _________________________________________________________________ \n");
    textcolor(BLUE);
    printf("               Selectionner votre option  :  ");
    textcolor(WHITE);
    scanf("%c",&check_input);
    textcolor(GRAY);
    i++;
    }while(*check_input != '1' && *check_input != '2');

    if(*check_input == '1'){
        authentification();
    } else if (*check_input == '2'){
        create_account();
    }



    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface *ecran = NULL, *menu=NULL;
    //SDL_WM_SetIcon(IMG_Load("icon.GIF"), NULL);
    ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("TRACTION", NULL);
    menu = IMG_Load("menu.JPG");

    SDL_Rect positionMenu;
    positionMenu.x = 0;
    positionMenu.y = 0;
    SDL_BlitSurface(menu, NULL, ecran, &positionMenu);
    SDL_Flip(ecran);
    SDL_Event event;
    int continuer = 1;
    score = -1;
    while(continuer){
        SDL_WaitEvent(&event);
        int jeu_fin;
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;
                    case SDLK_j:
                        jeu_fin = jouer(ecran, level, username);
                        break;
                    case SDLK_SPACE:
                        consulter_score(ecran);
                        break;
                    case SDLK_m:
                        mes_scores(ecran, level, username);
                        break;
                    default:
                        break;
                }


        }

        if(jeu_fin == 1){
            return EXIT_SUCCESS;
        }
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 219, 219, 219));
        SDL_BlitSurface(menu, NULL, ecran, &positionMenu);
        SDL_Flip(ecran);


    }

    SDL_Quit();
    return EXIT_SUCCESS;
}
