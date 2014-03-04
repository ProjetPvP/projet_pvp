#include <stdlib.h>
#include <SDL/SDL.h>
#include <stdbool.h>
#include "matrice.h"
#define HAUTEUR 400
#define LARGEUR 600
#define LARGEURHEROSPIXEL 34
#define HAUTEURHEROSPIXEL 34
#define LARGEURMINE 20








//==========================================================//
//                            main                          //
//==========================================================//



int main ( int argc, char** argv )
{
      positionHeros.x = 200;
      positionHeros.y = 300;
      positionMap.x = 0;
      positionMap.y = 0;
      positionBarreVie.x = 0;
      positionBarreVie.y = 0;
      t_ecran_de_jeu matrice;
      matrice = create_ecran_de_jeu(HAUTEUR, LARGEUR, positionHeros.x, positionHeros.y);
      initMatrice(matrice);
      barreVie = SDL_CreateRGBSurface(SDL_HWSURFACE, 600, 50, 32, 0, 0, 0, 0);
      int continuer = 1;
       if (SDL_INIT_VIDEO == -1)
      {
                  fprintf(stderr, "erreur d'initialisation : %s\n", SDL_GetError());
                  exit(EXIT_FAILURE);
      }

      ecran = SDL_SetVideoMode(LARGEUR, HAUTEUR, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);

      if (SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255) == 0))
      {
            fprintf(stderr,"c'bon fillrect");
      }

      Heros = SDL_LoadBMP("heros_droite.bmp");
      SDL_SetColorKey(Heros, SDL_SRCCOLORKEY, SDL_MapRGB(Heros->format, 255, 0, 0));
      myMap = SDL_LoadBMP("sol4.bmp");
      mine = SDL_LoadBMP("nvMine.bmp");
      SDL_SetColorKey(mine, SDL_SRCCOLORKEY, SDL_MapRGB(mine->format, 255, 0, 0));
      SDL_Flip(ecran);

      int nbDeplacement =  1;
      Uint8 *keystates = SDL_GetKeyState( NULL );
      while(continuer)
      {
            SDL_PollEvent(&event);
            switch (event.type)
            {
                  case SDL_QUIT : continuer = 0;break;
                  case SDL_KEYDOWN :
                  switch (event.key.keysym.sym)
                  {
                        case SDLK_ESCAPE : continuer = 0;break;
                        default : break;
                  }break;
            }

            if (keystates[SDLK_UP])                                     // les keystats permettent le déplacement en diagonal.
            {
                  if (verifierPoussee(matrice, HAUT,matrice->positionHeros, nbDeplacement))
                  {
                        replacementHeros(matrice, HAUT, nbDeplacement);
                  }
            }
            if (keystates[SDLK_DOWN])
            {
                  if (verifierPoussee(matrice, BAS, matrice->positionHeros, nbDeplacement))
                  {
                        replacementHeros(matrice, BAS, nbDeplacement);
                  }
            }
            if (keystates[SDLK_RIGHT])
            {
                  if (verifierPoussee(matrice, DROITE, matrice->positionHeros, nbDeplacement))
                  {
                        replacementHeros(matrice, DROITE, nbDeplacement);
                  }
            }
            if (keystates[SDLK_LEFT])
            {
                  if (verifierPoussee(matrice, GAUCHE, matrice->positionHeros, nbDeplacement))
                  {
                        replacementHeros(matrice, GAUCHE, nbDeplacement);
                  }
            }




            LectureMatrice(matrice, ecran, barreVie); // Affiche la matrice telle qu'elle est
      }

    return 0;
}
