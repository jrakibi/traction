#include "constantes.h"
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
void mes_scores(SDL_Surface *ecran, int niveau, char username[]){
    FILE *score_file = NULL;
    score_file= fopen("users_score/score1.txt","r");
    char filename[22];
    strcpy(filename, "users_score/");
    strcat(filename, username);
    strcat(filename, ".txt");
    score_file = fopen(filename, "r");

    //ttf
    SDL_Surface *title = NULL, *level1=NULL, *score1=NULL, *level2=NULL, *score2=NULL, *level3=NULL, *score3=NULL, *fond_image=NULL;
    fond_image = IMG_Load("fondscore.jpg");
    TTF_Init();
    TTF_Font *title_police = NULL, *level_police = NULL, *score_police = NULL;
    title_police = TTF_OpenFont("fonts/AlphaWood.ttf",22);
    score_police = TTF_OpenFont("fonts/TypeKeys.ttf",20);
    level_police = TTF_OpenFont("fonts/1942.ttf",20);

    SDL_Color color_title = {255, 255, 255};
    SDL_Color level_color = {244, 167, 66};
    SDL_Color score_color = {255, 65, 28};
    title = TTF_RenderText_Blended(title_police,"TRACTION SCORES",color_title);
    level1 = TTF_RenderText_Blended(level_police,"level 1 : ",level_color);
    level2 = TTF_RenderText_Blended(level_police,"level 2 : ",level_color);
    level3 = TTF_RenderText_Blended(level_police,"level 3 : ",level_color);

    int meilleur_score;
    char score_level1_str[33], score_level2_str[33], score_level3_str[33];
    char score_str[1000];

        //case 1:
            fscanf(score_file, "%d", &meilleur_score);
            sprintf(score_level1_str,"%d", meilleur_score);

        //case 2:
            fscanf(score_file, "%d", &meilleur_score);
            sprintf(score_level2_str,"%d", meilleur_score);

        //case 3:
            fscanf(score_file, "%d", &meilleur_score);
            sprintf(score_level3_str,"%d", meilleur_score);
            fclose(score_file);

        score1 = TTF_RenderText_Blended(score_police, score_level1_str, score_color);
        score2 = TTF_RenderText_Blended(score_police, score_level2_str, score_color);
        score3 = TTF_RenderText_Blended(score_police, score_level3_str, score_color);

    SDL_Event event;
    int continuer = 1;
    SDL_Rect position;
    while(continuer){
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;
                    default:
                        break;
                }
        }
        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format, 0,0,0));
        position.x = 0;
        position.y = 0;
        SDL_BlitSurface(fond_image, NULL, ecran, &position);

        position.x = 3*TAILLE_BLOC + 16;
        position.y = 4*TAILLE_BLOC;
        SDL_BlitSurface(title,NULL, ecran, &position);

        position.x = 3*TAILLE_BLOC + 6;
        position.y = 6*TAILLE_BLOC;
        SDL_BlitSurface(level1,NULL, ecran, &position);

        position.x = 7*TAILLE_BLOC;
        position.y = 6*TAILLE_BLOC;
        SDL_BlitSurface(score1,NULL, ecran, &position);

        position.x = 3*TAILLE_BLOC + 6;
        position.y = 7*TAILLE_BLOC;
        SDL_BlitSurface(level2,NULL, ecran, &position);

        position.x = 7*TAILLE_BLOC;
        position.y = 7*TAILLE_BLOC;
        SDL_BlitSurface(score2,NULL, ecran, &position);

        position.x = 3*TAILLE_BLOC + 6;
        position.y = 8*TAILLE_BLOC;
        SDL_BlitSurface(level3,NULL, ecran, &position);

        position.x = 7*TAILLE_BLOC;
        position.y = 8*TAILLE_BLOC;
        SDL_BlitSurface(score3,NULL, ecran, &position);


        SDL_Flip(ecran);
    }
    TTF_Quit();
}
void consulter_score(SDL_Surface *ecran){
    FILE *score1_file = NULL, *score2_file = NULL, *score3_file = NULL;
    score1_file= fopen("meilleurs_score/score1.txt","r");
    score2_file= fopen("meilleurs_score/score2.txt","r");
    score3_file= fopen("meilleurs_score/score3.txt","r");

    char score_level1_str[1000], score_level2_str[1000], score_level3_str[1000];
    fgets(score_level1_str,10,score1_file);
    fgets(score_level2_str,10,score2_file);
    fgets(score_level3_str,10,score3_file);
    SDL_Surface *title = NULL, *level1=NULL, *score1=NULL, *level2=NULL, *score2=NULL, *level3=NULL, *score3=NULL, *fond_image=NULL;
    fond_image = IMG_Load("fondscore.jpg");
    TTF_Init();
    TTF_Font *title_police = NULL, *level_police = NULL, *score_police = NULL;
    title_police = TTF_OpenFont("fonts/AlphaWood.ttf",22);
    score_police = TTF_OpenFont("fonts/TypeKeys.ttf",20);
    level_police = TTF_OpenFont("fonts/1942.ttf",20);

    SDL_Color color_title = {255, 255, 255};
    SDL_Color level_color = {244, 167, 66};
    SDL_Color score_color = {255, 65, 28};
    title = TTF_RenderText_Blended(title_police,"TRACTION SCORES",color_title);
    level1 = TTF_RenderText_Blended(level_police,"level 1 : ",level_color);
    level2 = TTF_RenderText_Blended(level_police,"level 2 : ",level_color);
    level3 = TTF_RenderText_Blended(level_police,"level 3 : ",level_color);
    score1 = TTF_RenderText_Blended(score_police, score_level1_str, score_color);
    score2 = TTF_RenderText_Blended(score_police, score_level2_str, score_color);
    score3 = TTF_RenderText_Blended(score_police, score_level3_str, score_color);

    SDL_Rect position;
    SDL_Event event;
    int continuer = 1;
    while(continuer){
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;
                    default:
                        break;
                }
        }
        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format, 0,0,0));
        position.x = 0;
        position.y = 0;
        SDL_BlitSurface(fond_image, NULL, ecran, &position);

        position.x = 3*TAILLE_BLOC + 16;
        position.y = 4*TAILLE_BLOC;
        SDL_BlitSurface(title,NULL, ecran, &position);

        position.x = 3*TAILLE_BLOC + 6;
        position.y = 6*TAILLE_BLOC;
        SDL_BlitSurface(level1,NULL, ecran, &position);

        position.x = 7*TAILLE_BLOC;
        position.y = 6*TAILLE_BLOC;
        SDL_BlitSurface(score1,NULL, ecran, &position);

        position.x = 3*TAILLE_BLOC + 6;
        position.y = 7*TAILLE_BLOC;
        SDL_BlitSurface(level2,NULL, ecran, &position);

        position.x = 7*TAILLE_BLOC;
        position.y = 7*TAILLE_BLOC;
        SDL_BlitSurface(score2,NULL, ecran, &position);

        position.x = 3*TAILLE_BLOC + 6;
        position.y = 8*TAILLE_BLOC;
        SDL_BlitSurface(level3,NULL, ecran, &position);

        position.x = 7*TAILLE_BLOC;
        position.y = 8*TAILLE_BLOC;
        SDL_BlitSurface(score3,NULL, ecran, &position);


        SDL_Flip(ecran);
    }

    TTF_Quit();

}

