#ifndef _HEROS_H
#define _HEROS_H
#include "matrice.h"


struct S_Objet
{
      char* nom;
      SDL_Surface * image;
      char* type;
};
typedef struct S_Objet * T_Objet;

struct S_Inventaire
{
      T_Objet objet;
      int tailleInventaire;
};
typedef struct S_Inventaire * T_Inventaire;


struct S_Heros
{
      int vie;
      char* nom;
      char* mapActuelle;
      T_Inventaire inventaire;
};

typedef struct S_Heros * T_Heros;





























#endif
