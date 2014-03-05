#include <stdlib.h>
#include <SDL/SDL.h>
#include <stdbool.h>
#include "matrice.h"









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
      T_Anim HerosDroite = initialisationHerosDroite();
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

      HerosDroite = SDL_LoadBMP("images/heros_droite.bmp");
      HerosAnimationDroite = SDL_LoadBMP("images/heros_animation_droite.bmp");
      HerosAnimation2Droite = SDL_LoadBMP("images/heros_animation2_droite.bmp");
      HerosBas = SDL_LoadBMP("images/heros_bas.bmp");
      HerosGauche = SDL_LoadBMP("images/heros_gauche.bmp");
      HerosHaut = SDL_LoadBMP("images/heros_haut.bmp");


      SDL_SetColorKey(HerosHaut, SDL_SRCCOLORKEY, SDL_MapRGB(HerosHaut->format, 255, 0, 0));
      SDL_SetColorKey(HerosBas, SDL_SRCCOLORKEY, SDL_MapRGB(HerosBas->format, 255, 0, 0));
      SDL_SetColorKey(HerosGauche, SDL_SRCCOLORKEY, SDL_MapRGB(HerosGauche->format, 255, 0, 0));
      SDL_SetColorKey(HerosDroite, SDL_SRCCOLORKEY, SDL_MapRGB(HerosDroite->format, 255, 0, 0));
      myMap = SDL_LoadBMP("sol4.bmp");
      mine = SDL_LoadBMP("nvMine.bmp");
      SDL_SetColorKey(mine, SDL_SRCCOLORKEY, SDL_MapRGB(mine->format, 255, 0, 0));
      SDL_Flip(ecran);
      int direction;
      int nbDeplacement =  1;
      Uint8 *keystates = SDL_GetKeyState( NULL );
      int compteurboucle = 0;
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
            if(compteurboucle == 0)
            {
                  if (keystates[SDLK_UP])                                     // les keystats permettent le déplacement en diagonal.
                  {
                        if (verifierPoussee(matrice, HAUT,matrice->positionHeros, nbDeplacement))
                        {
                              replacementHeros(matrice, HAUT, nbDeplacement);
                        }
                        direction = HAUT;
                  }
                  if (keystates[SDLK_DOWN])
                  {
                        if (verifierPoussee(matrice, BAS, matrice->positionHeros, nbDeplacement))
                        {
                              replacementHeros(matrice, BAS, nbDeplacement);
                        }
                        direction = BAS;
                  }
                  if (keystates[SDLK_RIGHT])
                  {
                        if (verifierPoussee(matrice, DROITE, matrice->positionHeros, nbDeplacement))
                        {
                              replacementHeros(matrice, DROITE, nbDeplacement);
                        }
                        direction = DROITE;
                  }
                  if (keystates[SDLK_LEFT])
                  {
                        if (verifierPoussee(matrice, GAUCHE, matrice->positionHeros, nbDeplacement))
                        {
                              replacementHeros(matrice, GAUCHE, nbDeplacement);
                        }
                        direction = GAUCHE;
                  }
            }
            if(compteurboucle >3 )
            {
                  compteurboucle = 0;
            }
            else compteurboucle++;



            LectureMatrice(matrice, ecran, barreVie, direction); // Affiche la matrice telle qu'elle est
      }

    return 0;
}
