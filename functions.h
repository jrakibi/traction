#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include "functions.c"
int find_user(char username[],char password[]); //retourne 1 si l'utilisateur est trouvé sinnon retourne 0

void authentification();
void create_account();
void textcolor(unsigned short color);
#endif // FUNCTIONS_H_INCLUDED
