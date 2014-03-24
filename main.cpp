#include <stdlib.h>
#include <SDL/SDL.h>
#include <stdbool.h>
#include <pthread.h>
#include "matrice.h"
#include "heros.h"








//==========================================================//
//                            main                          //
//==========================================================//



int main ( int argc, char** argv )
{
      positionHeros.x = 200;
      positionHeros.y = 300;
      positionMap.x = 0;
      positionMap.y = 0;
      positionBarreHaut.x = 0;
      positionBarreHaut.y = 0;
      positionBarreVie.x = 20;
      positionBarreVie.y = 15;

      t_ecran_de_jeu matrice;
      matrice = create_ecran_de_jeu(HAUTEUR, LARGEUR, positionHeros.x, positionHeros.y);
//      initMatrice(matrice);

      barreHaut = SDL_CreateRGBSurface(SDL_HWSURFACE, 600, 50, 32, 0, 0, 0, 0);
      int continuer = 1;
       if (SDL_INIT_VIDEO == -1)
      {
                  fprintf(stderr, "erreur d'initialisation : %s\n", SDL_GetError());
                  exit(EXIT_FAILURE);
      }

      ecran = SDL_SetVideoMode(LARGEUR, HAUTEUR, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

      if (SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255) == 0))
      {
            fprintf(stderr,"c'bon fillrect");
      }

      HerosDroite = SDL_LoadBMP("images/heros_droite.bmp");
      HerosAnimationDroite = SDL_LoadBMP("images/heros_animation_droite.bmp");
      HerosAnimation2Droite = SDL_LoadBMP("images/heros_animation2_droite.bmp");

      HerosBas = SDL_LoadBMP("images/heros_bas.bmp");
      HerosAnimationBas = SDL_LoadBMP("images/heros_animation_bas.bmp");
      HerosAnimation2Bas= SDL_LoadBMP("images/heros_animation2_bas.bmp");

      HerosGauche = SDL_LoadBMP("images/heros_gauche.bmp");
      HerosAnimationGauche = SDL_LoadBMP("images/heros_animation_gauche.bmp");
      HerosAnimation2Gauche = SDL_LoadBMP("images/heros_animation2_gauche.bmp");

      HerosHaut = SDL_LoadBMP("images/heros_haut.bmp");
      HerosAnimationHaut = SDL_LoadBMP("images/heros_animation_haut.bmp");
      HerosAnimation2Haut = SDL_LoadBMP("images/heros_animation2_haut.bmp");

      myMap = SDL_LoadBMP("images/Map1Vide.bmp");
      mine = SDL_LoadBMP("nvMine.bmp");
      arbre = SDL_LoadBMP("images/arbre.bmp");
      //======================================================================//
      //                            création T_anim                           //
      //======================================================================//


      T_Anim animEnCours = initialisationAnim(BAS);
      T_Anim herosDroiteAnim = initialisationAnim(DROITE);
      T_Anim herosGaucheAnim = initialisationAnim(GAUCHE);
      T_Anim herosHautAnim = initialisationAnim(HAUT);
      T_Anim herosBasAnim = initialisationAnim(BAS);


      //======================================================================//
      //                            setColorKey                               //
      //======================================================================//
      SDL_SetColorKey(HerosHaut, SDL_SRCCOLORKEY, SDL_MapRGB(HerosHaut->format, 255, 0, 0));
      SDL_SetColorKey(HerosAnimationHaut, SDL_SRCCOLORKEY, SDL_MapRGB(HerosAnimationDroite->format, 255, 0, 0));
      SDL_SetColorKey(HerosAnimation2Haut, SDL_SRCCOLORKEY, SDL_MapRGB(HerosAnimation2Droite->format, 255, 0, 0));

      SDL_SetColorKey(HerosGauche, SDL_SRCCOLORKEY, SDL_MapRGB(HerosGauche->format, 255, 0, 0));
      SDL_SetColorKey(HerosAnimationGauche, SDL_SRCCOLORKEY, SDL_MapRGB(HerosAnimationDroite->format, 255, 0, 0));
      SDL_SetColorKey(HerosAnimation2Gauche, SDL_SRCCOLORKEY, SDL_MapRGB(HerosAnimation2Droite->format, 255, 0, 0));

      SDL_SetColorKey(HerosDroite, SDL_SRCCOLORKEY, SDL_MapRGB(HerosDroite->format, 255, 0, 0));
      SDL_SetColorKey(HerosAnimationDroite, SDL_SRCCOLORKEY, SDL_MapRGB(HerosAnimationDroite->format, 255, 0, 0));
      SDL_SetColorKey(HerosAnimation2Droite, SDL_SRCCOLORKEY, SDL_MapRGB(HerosAnimation2Droite->format, 255, 0, 0));

      SDL_SetColorKey(HerosBas, SDL_SRCCOLORKEY, SDL_MapRGB(HerosBas->format, 255, 0, 0));
      SDL_SetColorKey(HerosAnimationBas, SDL_SRCCOLORKEY, SDL_MapRGB(HerosAnimationBas->format, 255, 0, 0));
      SDL_SetColorKey(HerosAnimation2Bas, SDL_SRCCOLORKEY, SDL_MapRGB(HerosAnimation2Bas->format, 255, 0, 0));

      SDL_SetColorKey(mine, SDL_SRCCOLORKEY, SDL_MapRGB(mine->format, 255, 0, 0));
      SDL_SetColorKey(arbre, SDL_SRCCOLORKEY, SDL_MapRGB(arbre->format, 255, 0, 0));
      SDL_Flip(ecran);

      T_Heros heros = allocHeros("TestHeros", "sol4.bmp");
      matrice = chargementFichier("maps/depart.map", heros);

      int hit = 0;
      int nbDeplacement =  1;

      T_Param_Thread my_Param_Thread = allocParamThread(matrice, nbDeplacement);

      int direction = NUL;

      Uint8 *keystates = SDL_GetKeyState( NULL );
      int compteurboucle = 0;
      bool thread_created = false;
      pthread_t thread;
      while(continuer)
      {
            SDL_PollEvent(&event);
                  switch (event.type)
                  {
                        case SDL_QUIT : continuer = 0;break;
                        case SDL_KEYDOWN :
                        switch (event.key.keysym.sym)
                        {
                              case SDLK_ESCAPE :
                                              continuer = 0;
                                              break;
                              default :
                                         break;
                        }break;
                  }
                        if (keystates[SDLK_UP])                                     // les keystats permettent le déplacement en diagonal
                        {
                              if (verifierPoussee(matrice, HAUT,matrice->positionHeros, nbDeplacement))
                              {
                                   hit = replacementHeros(matrice, HAUT, nbDeplacement, heros);
                              }
                              animEnCours = herosHautAnim;
                              direction = HAUT;
                        }
                        if (keystates[SDLK_DOWN])
                        {
                              if (verifierPoussee(matrice, BAS, matrice->positionHeros, nbDeplacement))
                              {
                                   hit = replacementHeros(matrice, BAS, nbDeplacement, heros);
                              }
                              direction = BAS;
                              animEnCours = herosBasAnim;
                        }
                        if (keystates[SDLK_RIGHT])
                        {
                              if (verifierPoussee(matrice, DROITE, matrice->positionHeros, nbDeplacement))
                              {
                                    hit = replacementHeros(matrice, DROITE, nbDeplacement, heros);
                              }
                              animEnCours = herosDroiteAnim;
                              direction = DROITE;
                        }
                        if (keystates[SDLK_LEFT])
                        {
                              if (verifierPoussee(matrice, GAUCHE, matrice->positionHeros, nbDeplacement))
                              {
                                    hit = replacementHeros(matrice, GAUCHE, nbDeplacement, heros);
                              }
                              animEnCours = herosGaucheAnim;
                              direction = GAUCHE;
                        }




                  LectureMatrice(matrice, ecran, barreHaut, direction, animEnCours, heros);
                  if(hit == 3)
                  {
                       SDL_Delay(200);
                  }
                  else if(hit == 0)
                  {
                        SDL_Delay(3);
                  }
                  if(thread_created == false)
                  {
                        thread_created = true;
                        int err;
                        //int threadReturnValue;
                        //calculDeplacementMonstre(monstre,matrice,nbDeplacement);
                        //err = pthread_create (&thread, NULL, calculDeplacementMonstre, &my_Param_Thread);

//                        if(err == 0)
//                        {
//                              fprintf(stderr,"Thread créé !\n");
//                        }

                        fprintf(stderr, "Thread terminé\n");

                  }
                   direction = NUL;// Affiche la matrice telle qu'elle est*/

      }
      fprintf(stderr,"Jeu fini\n");
      //pthread_join (thread, NULL);

      return EXIT_SUCCESS;
}
