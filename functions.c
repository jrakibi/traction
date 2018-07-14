#include <string.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <windows.h>
#include "constantes.h"
#include <SDL/SDL_ttf.h>
#include <unistd.h>
//Cette fonction consiste a changer la couleur du text du console
void textcolor(unsigned short color) {
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon,color);
}


int level; // variable global
int find_user(char username[],char password[]){
    FILE *users = NULL, *passwords = NULL, *levels = NULL;
    users = fopen("joueur/user.txt", "r");
    passwords = fopen("joueur/password.txt", "r");
    levels = fopen("joueur/level.txt", "r");

        char user[100];
        char mdp[100];
        while(ftell(users)!= 1000){
            fscanf(users, "%s", user);
            fscanf(passwords, "%s", mdp);
            fscanf(levels, "%d", &level);
            if(strcmp(user, username) == 0 && strcmp(mdp, password) == 0){
                return 1;
            } else {
                fseek(users, 1, SEEK_CUR);
                fseek(passwords, 1, SEEK_CUR);
                fseek(levels, 1, SEEK_CUR);
            }
        }
        return 0;
}

char username[100];
void authentification(){
    //ENTRER LES DONNEES DE L UTILISATEUR
    textcolor(BLUE);
    printf("\n\n\n\n");
    printf("_______________________________ AUTHENTIFICATION _______________________________\n\n\n");
    textcolor(GRAY);
    char mdp[100];
    int user_exist = 0;
    do {
    printf("                 Entrer votre nom d'utilisateur    : ");
    textcolor(WHITE);
    scanf("%s", &username);
    textcolor(GRAY);
    printf("                 Entrer votre mot de passe         : ");
    textcolor(WHITE);
    scanf("%s", &mdp);
    textcolor(GRAY);
    //Recherche de l utilisateur dans le fichier de donnees
    user_exist = find_user(username,mdp);
    if(user_exist == 1){
        textcolor(GREEN);
        printf("\t\t\tBIENVENUE Mr. %s",username);
        textcolor(GRAY);
        SDL_Delay(1000);
    } else {
        textcolor(RED);
        printf("nom d'utilisateur ou mot de passe est incorrect\n");
        textcolor(GRAY);
    }
    } while (user_exist == 0);
}

void create_account(){
    textcolor(BLUE);
    printf("\n\n\n\n");
    printf("---------------------------- INSCRIPTION ---------------------------\n\n\n");
    textcolor(GRAY);
    char password[100];
    textcolor(7);
    printf("                   entrer votre nom d'utilisateur :  ");
    textcolor(WHITE);
    scanf("%s", &username);
    textcolor(GRAY);
    printf("                   entrer votre mot de passe :  ");
    textcolor(WHITE);
    scanf("%s", &password);
    textcolor(GRAY);
    int user_exist = 0;
    user_exist = find_user(username, password);
    if(user_exist == 0){
        FILE *user_file = fopen("joueur/user.txt","a");
        FILE *password_file = fopen("joueur/password.txt","a");
        FILE *level_file = fopen("joueur/level.txt","a");

        fputc(' ', user_file);
        fputs(username,user_file);
        fputc(' ', password_file);
        fputs(password,password_file);
        fputc(' ', level_file);
        fputc('1', level_file);

        textcolor(GREEN);
        printf("BONJOUR Mr. %s", username);
        textcolor(GRAY);
        SDL_Delay(1200);
        } else {
            textcolor(RED);
            printf("nom d'utilisateur deja existe saisissez un nouveau nom d'utilisateur");
            textcolor(GRAY);
            create_account();
        }

        //creation du fichier contenant les score du joueur
        FILE *file_score = NULL;
        char filename[22];
        strcpy(filename, "users_score/");
        strcat(filename, username);
        strcat(filename, ".txt");
        file_score = fopen(filename, "w");
        fputs("1000 1000 1000",file_score);
        fclose(file_score);
}

