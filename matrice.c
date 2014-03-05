#include <stdlib.h>
#include <SDL/SDL.h>
#include <stdbool.h>
#include "matrice.h"

SDL_Surface * ecran = NULL;

SDL_Surface * HerosHaut = NULL;
SDL_Surface * HerosAnimationHaut = NULL;
SDL_Surface * HerosAnimation2Haut = NULL;

SDL_Surface * HerosBas = NULL;
SDL_Surface * HerosAnimationBas = NULL;
SDL_Surface * HerosAnimation2Bas = NULL;

SDL_Surface * HerosGauche = NULL;
SDL_Surface * HerosAnimationGauche = NULL;
SDL_Surface * HerosAnimation2Gauche = NULL;

SDL_Surface * HerosDroite = NULL;
SDL_Surface * HerosAnimationDroite = NULL;
SDL_Surface * HerosAnimation2Droite = NULL;

SDL_Surface * myMap = NULL;
SDL_Surface * mine = NULL;
SDL_Surface * barreVie = NULL;

//==========================================================//
//                     malloc matrice                       //
//==========================================================//


t_ecran_de_jeu create_ecran_de_jeu(int hauteur, int largeur, int posHerosColonne, int posHerosLigne)                              //malloc de la matrice
{
	t_ecran_de_jeu matrice = (t_ecran_de_jeu)malloc (sizeof(struct s_ecran_de_jeu));
	matrice->ecran = (char**)malloc(hauteur*sizeof(char*));
	int i;
	for(i=0; i<hauteur; i++)
	{
		matrice->ecran[i]=(char*)malloc(largeur*sizeof(char));
	}
	matrice->hauteur = hauteur;
	matrice->largeur = largeur;
	matrice->positionHeros.ligne = posHerosLigne;
	matrice->positionHeros.colonne = posHerosColonne;
	return matrice;
}

//==========================================================//
//                     malloc structures                    //
//==========================================================//

T_Anim allocT_Anim()
{
      T_Anim newAnim = (T_Anim)malloc(sizeof(struct S_Anim));
      newAnim->first = NULL;
      return newAnim;
}

T_Image allocT_Image( SDL_Surface * bla)
{
      T_Image newImage = (T_Image)malloc(sizeof(struct S_Image));
      newImage->image = bla;
      newImage->image_suiv = NULL;
      newImage->position= 0;
      return newImage;
}

T_Anim initialisationAnim(int direction)
{
      T_Anim newAnim = allocT_Anim();
      T_Image newImage1;
      T_Image newImage2;
      T_Image newImage3;
      T_Image newImage4;
      if(direction == DROITE)
      {
            newImage1 = allocT_Image(HerosDroite);
            newImage2 = allocT_Image(HerosAnimationDroite);
            newImage3 = allocT_Image(HerosDroite);
            newImage4 = allocT_Image(HerosAnimation2Droite);
      }
      else if(direction == GAUCHE)
      {
            newImage1 = allocT_Image(HerosGauche);
            newImage2 = allocT_Image(HerosAnimationGauche);
            newImage3 = allocT_Image(HerosGauche);
            newImage4 = allocT_Image(HerosAnimation2Gauche);
      }
      else if(direction == HAUT)
      {
            newImage1 = allocT_Image(HerosHaut);
            newImage2 = allocT_Image(HerosAnimationHaut);
            newImage3 = allocT_Image(HerosHaut);
            newImage4 = allocT_Image(HerosAnimation2Haut);
      }
      else
      {
            newImage1 = allocT_Image(HerosBas);
            newImage2 = allocT_Image(HerosAnimationBas);
            newImage3 = allocT_Image(HerosBas);
            newImage4 = allocT_Image(HerosAnimation2Bas);
      }

      newAnim->first = newImage1;
      newImage1->image_suiv = newImage2;
      newImage1->position = 1;
      newImage2->image_suiv = newImage3;
      newImage2->position = 2;
      newImage3->image_suiv = newImage4;
      newImage3->position = 3;
      newImage4->image_suiv = newImage1;
      newImage4->position = 4;
      return newAnim;
}


//==========================================================//
//                   variables globales                     //
//==========================================================//

      static int cpt = 0;

//==========================================================//
//                     initMatriceVide                      //
//==========================================================//

void initMatrice(t_ecran_de_jeu matrice)                                                     //initialisation de la matrice
{
      for (int i=0; i<HAUTEUR; i++)
      {
            for (int j = 0; j<LARGEUR; j++)
            {
                  if(i==50)
                  {
                        matrice->ecran[i][j] = 'b';
                  }
                  else if (matrice->positionHeros.ligne == i && matrice->positionHeros.colonne == j)
                  {
                        matrice->ecran[i][j] = 'H';
                        matrice->ecran[i-40][j-50] = 'M';
                        positionMine.y = matrice->positionHeros.ligne-40;
                        positionMine.x = matrice->positionHeros.colonne-50;
//                        fprintf(stderr, "posx : [%d], posy : [%d]\n", positionMine.x, positionMine.y);
//                        fprintf(stderr, "posx : [%d], posy : [%d]\n", positionHeros.x, positionHeros.y);
                  }
                  else
                  {
                        matrice->ecran[i][j] = ' ';
                  }
            }
      }
}
//==========================================================//
//                    Lecture matrice                       //
//==========================================================//
SDL_Surface * choixAnimHeros(int direction, T_Anim anim)
{
      if(direction == HAUT)
      {
            return HerosHaut;
      }
      else if(direction == BAS)
      {
            return HerosBas;
      }
      else if(direction == GAUCHE)
      {
            return HerosGauche;
      }
      else if(direction == DROITE)
      {
            anim->first = anim->first->image_suiv;
            if(anim->first->image != NULL)
            {
                  fprintf(stderr, "c'est pas nul");
            }
            return anim->first->image;
      }
      else
      {
            return HerosBas;
      }
}



//==========================================================//
//                    Lecture matrice                       //
//==========================================================//


void LectureMatrice(t_ecran_de_jeu matrice, SDL_Surface* ecran, SDL_Surface *  barreVie, int direction, T_Anim anim)
{
      SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
      SDL_FillRect(barreVie, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
      SDL_BlitSurface(barreVie, NULL, ecran, &positionBarreVie);

      positionHeros.x = matrice->positionHeros.colonne;
      positionHeros.y = matrice->positionHeros.ligne;
      SDL_BlitSurface(choixAnimHeros(direction, anim), NULL, ecran, &positionHeros);
      SDL_BlitSurface(mine, NULL, ecran, &positionMine);

      SDL_Flip(ecran);
}




//==========================================================//
//                      takedamage                          //
//==========================================================//


bool takedamage(t_ecran_de_jeu matrice, int direction, t_pos positionHeros, int deplacement, char c)
{
//      if (direction == GAUCHE)
//      {
//            if (positionHeros.colonne-1 == 'm' )
//            exit(EXIT_SUCCESS);
//      }
//      else if (direction == DROITE)
//      {
//            if (positionHeros.colonne+1 == 'm' )
//            exit(EXIT_SUCCESS);
//      }
//      else if (direction == HAUT)
//      {
//            if (positionHeros.ligne-1 == 'm' )
//            exit(EXIT_SUCCESS);
//      }
//      else if (direction == BAS)
//      {
//            if (positionHeros.ligne+1 == 'm' )
//            exit(EXIT_SUCCESS);
//      }
      exit(EXIT_SUCCESS);
      return false;
}


//==========================================================//
//                      création hitbox                     //
//==========================================================//
int verificationDeplacementHitbox(t_ecran_de_jeu matrice, t_pos pos, int largeur, int hauteur, int direction, int deplacement)
{
      if(direction == GAUCHE)
      {
            for(int i=0; i<hauteur; i++)
            {
                  if(matrice->ecran[pos.ligne+i][pos.colonne-1] != ' ')
                  {
                        takedamage(matrice, direction, pos, deplacement, matrice->ecran[pos.ligne+i][pos.colonne-1]);
                  }
            }
      }
      if(direction == DROITE)
      {
            for(int i=0; i<hauteur; i++)
            {
                  if(matrice->ecran[pos.ligne+i][pos.colonne+largeur+1] != ' ')
                  {
                        takedamage(matrice, direction, pos, deplacement, matrice->ecran[pos.ligne+i][pos.colonne+largeur+1]);
                  }
            }
      }
      if(direction == BAS)
      {
            for(int i=0; i<largeur; i++)
            {
                  if(matrice->ecran[pos.ligne+hauteur+1][pos.colonne+i] != ' ')
                  {
                        takedamage(matrice, direction, pos, deplacement, matrice->ecran[pos.ligne+hauteur+1][pos.colonne+i]);
                  }
            }
      }
      if(direction == HAUT)
      {
            for(int i=0; i<largeur; i++)
            {
                  if(matrice->ecran[pos.ligne-1][pos.colonne+i] != ' ')
                  {
                        takedamage(matrice, direction, pos, deplacement, matrice->ecran[pos.ligne-1][pos.colonne+i]);
                  }
            }
      }
      return 0;
}

//==========================================================//
//                      vérifier poussee                    //
//==========================================================//

bool verifierPoussee(t_ecran_de_jeu matrice, int direction, t_pos positionHeros, int deplacement)
{
      if (direction == GAUCHE)
      {
            if (positionHeros.colonne < 1+deplacement)
            {
                  return false;
            }
            else if (matrice->ecran[positionHeros.ligne][positionHeros.colonne-1] == ' ')
            {
                  return true;
            }
      }
      else if (direction == DROITE)
      {
            if (positionHeros.colonne > LARGEUR-2-deplacement-LARGEURHEROSPIXEL)            // parce que la matrice est définie sur [0-(LARGEUR-1)][0-(HAUTEUR-1)]
            {                                                                               // LARGEURHEROSPIXEL pour pas que le heros dépasse l'écran
                  return false;
            }
            else if (matrice->ecran[positionHeros.ligne][positionHeros.colonne+1] == ' ')
            {
                  return true;
            }
      }
      else if (direction == HAUT)
      {
            if (positionHeros.ligne < 1+deplacement)
            {
                  return false;
            }
            else if (matrice->ecran[positionHeros.ligne-1][positionHeros.colonne] == ' ')
            {
                  return true;
            }
      }
      else if (direction == BAS)
      {
            if (positionHeros.ligne > HAUTEUR -2-deplacement-HAUTEURHEROSPIXEL)                 // HAUTEURHEROSPIXEL pour pas que le heros dépasse l'écran
            {
                  return false;
            }
            else if (matrice->ecran[positionHeros.ligne+1][positionHeros.colonne] == ' ')
            {
                  return true;
            }
      }
      //takedamage(matrice, direction, positionHeros, deplacement, 'c');
      return false;
}

void replacementHeros(t_ecran_de_jeu matrice, int direction, int nb)
{
      if (direction == BAS)
      {
            matrice->positionHeros.ligne += nb;
      }
      if (direction == HAUT)
      {
            matrice->positionHeros.ligne -= nb;
      }
      if (direction == GAUCHE)
      {
            matrice->positionHeros.colonne -= nb;
      }
      if (direction == DROITE)
      {
            matrice->positionHeros.colonne += nb;
      }

      for (int i=51; i<HAUTEUR; i++)
      {
            for (int j=0; j<LARGEUR; j++)
            {
                  if(matrice->ecran[i][j] != 'M' && matrice->ecran[i][j] != 'm')
                  {
                        matrice->ecran[i][j] = ' ';
                  }
                  if ((matrice->positionHeros.ligne == i) && (matrice->positionHeros.colonne == j))
                  {
                        matrice->ecran[i][j] = 'H';
                  }
            }
      }
      if (cpt == 0)
      {
            for(int i=0; i<LARGEURMINE; i++)
            {
                  matrice->ecran[positionMine.y+i+1][positionMine.x] = 'M';
                  matrice->ecran[positionMine.y+i+1][positionMine.x+LARGEURMINE] = 'M';
                  matrice->ecran[positionMine.y][positionMine.x+i+1] = 'M';
                  matrice->ecran[positionMine.y+LARGEURMINE][positionMine.x+i+1] = 'M';
            }
//            int cpt2 = 0;
//            for(int i=0; i<HAUTEUR; i++)
//            {
//                  for(int j=0; j<LARGEUR; j++)
//                  {
//                        if (matrice->ecran[i][j] != ' ')
//                        {
//                              cpt2++;
//                              fprintf(stderr, "%c", matrice->ecran[i][j]);
//                              fprintf(stderr, "[%d][%d]", i,j);
//                        }
//                  }
//                  if(cpt2 != 0)
//                  {
//                        fprintf(stderr, "\n");
//                  }
//                  cpt2 = 0;
//            }
      }
      cpt++;
      verificationDeplacementHitbox(matrice, matrice->positionHeros, LARGEURHEROSPIXEL, HAUTEURHEROSPIXEL, direction, nb);
}
