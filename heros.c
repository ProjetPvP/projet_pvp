#include <stdlib.h>
#include <SDL/SDL.h>
#include <stdbool.h>
#include "heros.h"




T_Objet allocObjet(char* nomObjet, int tailleNom, SDL_Surface* image, char* typeObjet, int tailleType)
{
      T_Objet newObjet = (T_Objet)malloc(sizeof(struct S_Objet));
      newObjet->nom = (char*)malloc(tailleNom*sizeof(char));
      strcpy(newObjet->nom, nomObjet);

      newObjet->image = image;

      newObjet->type = (char*)malloc(tailleType*sizeof(char));
      strcpy(newObjet->type,typeObjet);

      return newObjet;
}

T_Inventaire allocInventaire()
{
      T_Inventaire newInventaire = (T_Inventaire)malloc(sizeof(struct S_Inventaire));
      newInventaire->tailleInventaire = 10;
      newInventaire->objet = NULL;
     return newInventaire;
}

T_Heros allocHeros(char* nomHeros, char* nomMap)
{
      T_Heros newHeros = (T_Heros)malloc(sizeof(struct S_Heros));
      newHeros->nom = (char*)malloc(strlen(nomHeros)*sizeof(char));
      strcpy(newHeros->nom, nomHeros);
      newHeros->mapActuelle = (char*)malloc(strlen(nomMap)*sizeof(char));
      strcpy(newHeros->mapActuelle, nomMap);
      newHeros->vie = 20;
      newHeros->inventaire = NULL;
      return newHeros;
}
