#include "constantes.h"
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

SDL_Rect positionCaisse;

int temp_actuel, temp_precedent;
int score;
int missionComplete;

int meilleur_score[3];
void save_score(SDL_Surface *ecran, char username[], int level){
    FILE *score_file = NULL;
    char filename[22];
    strcpy(filename, "users_score/");
    strcat(filename, username);
    strcat(filename, ".txt");
    if(level == 1){
        score_file = fopen(filename, "r");
        fscanf(score_file,"%d %d %d", &meilleur_score[0], &meilleur_score[1], &meilleur_score[2]);
        fclose(score_file);
    }

    score_file = fopen(filename, "w");
    fclose(score_file);
    score_file = fopen(filename, "a");
    char score_str[100];
    switch(level){
        case 1:
            if(score< meilleur_score[0])
                fprintf(score_file, "%d ", score);
            else
                fprintf(score_file, "%d ", meilleur_score[0]);
            break;
        case 2:
             if(score< meilleur_score[1])
                fprintf(score_file, "%d ", score);
            else
                fprintf(score_file, "%d ", meilleur_score[1]);
            break;
        case 3:
             if(score< meilleur_score[2])
                fprintf(score_file, "%d ", score);
            else
                fprintf(score_file, "%d ", meilleur_score[2]);
            break;
    }
}

void footer_level(SDL_Surface *ecran, int level){
    SDL_Rect level_position;
    level_position.x = TAILLE_BLOC * 6;
    level_position.y = TAILLE_BLOC * 12;
    // creation de ol"interface graphique du timer
    TTF_Init();
    TTF_Font *level_police =NULL;
    level_police = TTF_OpenFont("fonts/HangedLetters.ttf",40);
    SDL_Surface *level_surface;
        char level_str[100];
        sprintf(level_str, "%d", level);
        SDL_Color level_color = {66, 87, 91};
        char level_text[100];
        strcpy(level_text,"level : ");
        strcat(level_text, level_str);
        level_surface = TTF_RenderText_Blended(level_police, level_text, level_color);
        SDL_BlitSurface(level_surface, NULL, ecran, &level_position);
        SDL_Flip(ecran);

}
void footer_score(SDL_Surface *ecran){
    SDL_Rect score_position;
    score_position.x = TAILLE_BLOC * 3.5;
    score_position.y = TAILLE_BLOC * 11.8;
    // creation de ol"interface graphique du timer
    TTF_Init();
    TTF_Font *score_police =NULL;
    score_police = TTF_OpenFont("fonts/WoodcutterTagsonaRope.ttf",50);
    SDL_Surface *score_surface;
    temp_actuel = SDL_GetTicks();
    if(temp_actuel - temp_precedent > 500){
        score++;
        temp_precedent = temp_actuel;
        SDL_Surface *clo;
        clo = IMG_Load("clock.png");
        SDL_Rect footer_position;
        footer_position.x = 0;
        footer_position.y = TAILLE_BLOC * 12;
        SDL_BlitSurface(clo, NULL, ecran, &footer_position);
        SDL_Flip(ecran);
        char score_str[100];
        sprintf(score_str, "%d", score);
        SDL_Color score_color = {66, 87, 91};
        score_surface = TTF_RenderText_Blended(score_police, score_str, score_color);
        SDL_BlitSurface(score_surface, NULL, ecran, &score_position);
        SDL_Flip(ecran);
    }
}
void show_footer(SDL_Surface *ecran, int level){
    if(missionComplete == 1){
        score =-1;
    }
    footer_level(ecran,level);
    footer_score(ecran);

}

int decaler(SDL_Surface *ecran, SDL_Rect *pos,int direction, int (*carte)[NB_BLOC_HAUTEUR][NB_BLOC_HAUTEUR]){

    SDL_Surface *vide = NULL;
    vide = IMG_Load("vide.jpg");
    switch(direction){
        int k;
        case HAUT:
            if(pos->y-1 >= 0){
                if((*carte)[pos->x][pos->y-1] != MUR){
                    (*carte)[pos->x][pos->y] = VIDE;
                    for(k = pos->y-1; k>=0; k--){
                        if((*carte)[pos->x][k] == OBJECTIF || (*carte)[pos->x][k] == MUR || k==0 ){
                            if(k==0 && ((*carte)[pos->x][k] != MUR && (*carte)[pos->x][k] != OBJECTIF)){

                                pos->y = k;
                                return 0;
                            } else {
                                if((*carte)[pos->x][k] == OBJECTIF){
                                   //on retourne la valeur 1 si la caisse est entrer dans l'objectif
                                    pos->y = k;
                                    return 1;
                                }
                                if((*carte)[pos->x][k] == MUR){
                                   //on retourne la valeur 0 si la caisse n'est pas entrer dans l'objectif
                                    pos->y = k+1;
                                    return 0;
                                }

                            }
                           }

                    }
                }
                break;
            }
            break;
        case BAS:
            if(pos->y+1 <= 11){
                if((*carte)[pos->x][pos->y+1] != MUR){
                    (*carte)[pos->x][pos->y] = VIDE;
                    for(k = pos->y+1; k<=11; k++){
                        if((*carte)[pos->x][k] == OBJECTIF || (*carte)[pos->x][k] == MUR || k==11 ){
                            if(k==11 && ((*carte)[pos->x][k] != MUR && (*carte)[pos->x][k] != OBJECTIF)){
                                pos->y = k;
                                return 0;
                            } else {
                                if((*carte)[pos->x][k] == OBJECTIF){
                                   //on retourne la valeur 1 si la caisse est entrer dans l'objectif
                                    pos->y = k;
                                    return 1;
                                }
                                if((*carte)[pos->x][k] == MUR){
                                   //on retourne la valeur 0 si la caisse n'est pas entrer dans l'objectif
                                    pos->y = k-1;
                                    return 0;
                                }

                            }
                        }
                    }
                }
                break;
            }
            break;
        case DROITE:
            if(pos->x+1 <= 11){
                if((*carte)[pos->x+1][pos->y] != MUR){
                    (*carte)[pos->x][pos->y] = VIDE;
                    for(k = pos->x+1; k<=11; k++){
                        if((*carte)[k][pos->y] == OBJECTIF || (*carte)[k][pos->y] == MUR || k==11 ){

                            if(k==11 && ((*carte)[k][pos->y] != MUR && (*carte)[k][pos->y] != OBJECTIF)){
                                pos->x = k;
                                return 0;
                            } else {
                                if((*carte)[k][pos->y] == OBJECTIF){
                                   //on retourne la valeur 1 si la caisse est entrer dans l'objectif
                                    pos->x = k;
                                    return 1;
                                }
                                if((*carte)[k][pos->y] == MUR){
                                   //on retourne la valeur 0 si la caisse n'est pas entrer dans l'objectif
                                    pos->x = k-1;
                                    return 0;
                                }

                            }
                        }
                    }
                }
                break;
            }
            break;
        case GAUCHE:
            if(pos->x-1 >= 0){
                if((*carte)[pos->x-1][pos->y] != MUR){
                    (*carte)[pos->x][pos->y] = VIDE;
                    for(k = pos->x-1; k>=0; k--){
                        if((*carte)[k][pos->y] == OBJECTIF || (*carte)[k][pos->y] == MUR || k==0 ){

                            if(k==0 && ((*carte)[k][pos->y] != MUR && (*carte)[k][pos->y] != OBJECTIF)){
                                pos->x = k;
                                return 0;
                            } else {
                                if((*carte)[k][pos->y] == OBJECTIF){
                                   //on retourne la valeur 1 si la caisse est entrer dans l'objectif
                                    pos->x = k;
                                    return 1;
                                }
                                if((*carte)[k][pos->y] == MUR){
                                   //on retourne la valeur 0 si la caisse n'est pas entrer dans l'objectif
                                    pos->x = k+1;
                                    return 0;
                                }

                            }
                        }
                    }
                }
                break;
            }
            break;


    }
}

int chargerNiveau(SDL_Surface *ecran, int niveauSuivant, int (*carte)[NB_BLOC_HAUTEUR][NB_BLOC_HAUTEUR]){
    FILE *niveauFile = NULL;
    printf("niveau a charger est : %d \n",niveauSuivant);
    switch(niveauSuivant){
        case 1:
            niveauFile = fopen("niveau/niveau1.txt","r");
            break;
        case 2:
            niveauFile = fopen("niveau/niveau2.txt","r");
            break;
        case 3:
            niveauFile = fopen("niveau/niveau3.txt","r");
            break;
        default:
            return 0;
    }

    if(niveauFile != NULL){
    int i=0, j=0;
    for(i=0; i< NB_BLOC_LARGEUR; i++){
        for(j=0; j < NB_BLOC_HAUTEUR; j++){
            switch(fgetc(niveauFile)){
                case '0' :
                    (*carte)[i][j] = 0;
                    break;
                case '1':
                    (*carte)[i][j] = 1;
                    break;
                case '2':
                    (*carte)[i][j] = 2;
                    break;
                case '3':
                    (*carte)[i][j] = 3;
                    break;
            }
        }
    }

    for(i=0;i< NB_BLOC_LARGEUR; i++){
        for(j=0; j < NB_BLOC_HAUTEUR ; j++){
                if((*carte)[i][j] == CAISSE){
                    positionCaisse.x = i;
                    positionCaisse.y = j;
                }
        }
    }
    fclose(niveauFile);
    return 1;
    } else {
        printf("\nimpossible d ouvrir le fichier de niveau");
    }

}

int jouer(SDL_Surface *ecran, int niveau, char username[]){
    SDL_Surface *mur = NULL, *vide = NULL, *objectif = NULL, *caisse = NULL, *caisse_ok = NULL;
    mur = IMG_Load("mur.png");
    caisse = IMG_Load("caisse.jpg");
    objectif = IMG_Load("objectif.png");
    caisse_ok = IMG_Load("caisse_ok.png");
    vide = IMG_Load("vide.png");


    int carte[NB_BLOC_LARGEUR][NB_BLOC_HAUTEUR] = {0};
    //creation de la carte + remplissement du carte aleatoire -----> a remplire apres en dependant de chaque niveau (level:1 ... n)
    int niveauSuivant = niveau;// ce variable sert a indiquer le niveau du jeu atteint par l'utilisateur
    chargerNiveau(ecran, niveauSuivant, &carte);

    SDL_Rect position;
    SDL_Event event;
    int i=0, j=0;
    int continuer = 1;
    temp_actuel = 0, temp_precedent=0;

    while(continuer){
            //a revenir pour changer les parmetre haut de decaler et mm BAS

        SDL_PollEvent(&event);
                show_footer(ecran, niveauSuivant);

        missionComplete = 0;
        switch(event.type){


        case SDL_QUIT:
            continuer = 0;
            break;
        case SDL_KEYDOWN:


            switch(event.key.keysym.sym){
                case SDLK_ESCAPE:
                    continuer = 0;
                    break;
                case SDLK_UP:
                    missionComplete = decaler(ecran, &positionCaisse, HAUT, &carte);
                    break;
                case SDLK_DOWN:
                    missionComplete = decaler(ecran, &positionCaisse, BAS, &carte);
                    break;
                case SDLK_RIGHT:
                    missionComplete = decaler(ecran, &positionCaisse, DROITE, &carte);
                    break;
                case SDLK_LEFT:
                    missionComplete = decaler(ecran, &positionCaisse, GAUCHE, &carte);
                    break;
                default:
                    break;
            }
            break;

        }

        for(i=0; i<NB_BLOC_LARGEUR; i++){
            for(j=0; j < NB_BLOC_HAUTEUR; j++){
                position.x = i * TAILLE_BLOC;
                position.y = j * TAILLE_BLOC;
                switch(carte[i][j]){
                    case MUR:
                        SDL_BlitSurface(mur, NULL, ecran, &position);
                        break;
                    case VIDE:
                        SDL_BlitSurface(vide, NULL, ecran, &position);
                        break;
                    case OBJECTIF:
                        SDL_BlitSurface(vide, NULL, ecran, &position); // case vide puis la case de l objectif --> raison d'esthetique
                        SDL_BlitSurface(objectif, NULL, ecran, &position);
                        break;
                }
            }
        }

        position.x = positionCaisse.x * TAILLE_BLOC;
        position.y = positionCaisse.y * TAILLE_BLOC;
        SDL_BlitSurface(caisse, NULL, ecran, &position);
        SDL_Flip(ecran);


        if(missionComplete == 1){
            for(i=0;i< NB_BLOC_LARGEUR; i++){
                for(j=0; j < NB_BLOC_HAUTEUR ; j++){
                    if(carte[i][j] == OBJECTIF){
                        position.x = i * TAILLE_BLOC;
                        position.y = j * TAILLE_BLOC;
                        SDL_BlitSurface(caisse_ok, NULL, ecran, &position);
                        SDL_Flip(ecran);
                        FILE *score_file = NULL;
                        switch(niveauSuivant){
                            case 1:
                                score_file = fopen("meilleurs_score/score1.txt", "r");
                                break;
                            case 2:
                                score_file = fopen("meilleurs_score/score2.txt", "r");
                                break;
                            case 3:
                                score_file = fopen("meilleurs_score/score3.txt", "r");
                                break;
                        }

                        char meilleur_score_str[1000];
                        fgets(meilleur_score_str,1000,score_file);
                        int meilleur_score = atoi(meilleur_score_str);


                        if(score < meilleur_score){
                            FILE *score_save_file = NULL;
                            switch(niveauSuivant){
                            case 1:
                                score_save_file = fopen("meilleurs_score/score1.txt", "w+");
                                break;
                            case 2:
                                score_save_file = fopen("meilleurs_score/score2.txt", "w+");
                                break;
                            case 3:
                                score_save_file = fopen("meilleurs_score/score3.txt", "w+");
                                break;
                            }
                            fprintf(score_save_file,"%d",score);
                        }
                        //Passage a l'autre niveau dès quand arrive a entrer la caisse dans sa propre position
                        SDL_Delay(1200);
                        SDL_BlitSurface(vide, NULL, ecran, &position);
                        SDL_Flip(ecran);
                        save_score(ecran, username, niveauSuivant);
                        niveauSuivant++;
                        chargerNiveau(ecran, niveauSuivant, &carte);


                    }
                }
            }
        }

        if(niveauSuivant == 4){
            SDL_Surface *gameover;
            gameover = IMG_Load("gameover.gif");
            position.x = 0;
            position.y = 0;
            SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255,255,255));
            SDL_BlitSurface(gameover, NULL, ecran, &position);
            SDL_Flip(ecran);
            SDL_Delay(1000);
            return 1;
        }
    }

}
