#include <stdlib.h>
#include <SDL/SDL.h>
#include <stdbool.h>
#include <stdio.h>
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
SDL_Surface * arbre= NULL;
SDL_Surface * mine = NULL;
SDL_Surface * barreHaut = NULL;
SDL_Surface * barreVie = NULL;

//==========================================================//
//                   variables globales                     //
//==========================================================//

      static int cpt = 0;
      static int verifDirection = NUL;
      static int nombreEntites = 0;
      struct S_ListePosition;
      typedef struct S_ListePosition * T_ListePosition;
      struct S_ListePosition
      {
            int numero;
            SDL_Rect position;
            T_ListePosition suiv;
            T_ListePosition prec;
      };
typedef struct S_ListePosition * T_ListePosition;
      static T_ListePosition ListeArbre;





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
	matrice->nord = NULL;
	matrice->sud = NULL;
	matrice->est = NULL;
	matrice->ouest = NULL;
	matrice->hauteur = hauteur;
	matrice->largeur = largeur;

	matrice->positionHeros.ligne = posHerosLigne;
	matrice->positionHeros.colonne = posHerosColonne;

	matrice->tab_monstres = (T_Monstre)malloc(sizeof(struct S_Monstre));
	return matrice;
}



void changement_tailleTableau(t_ecran_de_jeu matrice)
{
      matrice->tab_monstres = realloc(matrice->tab_monstres, nombreEntites * sizeof(struct S_Monstre));
}

//==========================================================//
//                     malloc structures                    //
//==========================================================//

T_Anim allocT_Anim()
{
      T_Anim newAnim = (T_Anim)malloc(sizeof(struct S_Anim));
      newAnim->first = NULL;
      newAnim->current = NULL;
      return newAnim;
}

T_Image allocT_Image( SDL_Surface * image)
{
      T_Image newImage = (T_Image)malloc(sizeof(struct S_Image));
      newImage->image = image;
      newImage->image_suiv = NULL;
      newImage->position= 0;
      return newImage;
}

T_ListePosition allocListeArbre(SDL_Rect rect, int nombreArbre)
{
      T_ListePosition newPosition = (T_ListePosition)malloc(sizeof(struct S_ListePosition));
      newPosition->numero = nombreArbre;
      newPosition->position = rect;
      newPosition->suiv = NULL;
      newPosition->prec = NULL;
      return newPosition;
}


T_Monstre allocMonstre(int vie, int damage, int ligne, int colonne)
{
      T_Monstre newMonstre = (T_Monstre)malloc(sizeof(struct S_Monstre));
      newMonstre->vie = vie;
      newMonstre->degats = damage;

      newMonstre->pos_monstre.ligne = ligne;
      newMonstre->pos_monstre.colonne = colonne;

      newMonstre->aggressif = false;
      return newMonstre;
}

T_Param_Thread allocParamThread (t_ecran_de_jeu matrice, int nbdeplacement)
{
      T_Param_Thread newParamThread = (T_Param_Thread)malloc(sizeof(struct S_Param_Thread));
      newParamThread->monstre = allocMonstre(10,10, 10,10);
      newParamThread->matrice = (t_ecran_de_jeu)malloc(sizeof(struct s_ecran_de_jeu));
      newParamThread->matrice = matrice;
      newParamThread->nbdeplacement = nbdeplacement;

      return newParamThread;
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
      newAnim->current = newImage1;
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

T_ListePosition ajoutArbreListe(T_ListePosition maListe, SDL_Rect pos, int nombreArbre)
{
      T_ListePosition returnListe;
      if(nombreArbre == 0)
      {
            returnListe = allocListeArbre(pos, nombreArbre+1);

      }
      else
      {
            returnListe = maListe;
            while(returnListe->suiv != NULL)
            {
                  returnListe = returnListe->suiv;
            }
            returnListe->suiv = allocListeArbre(pos, nombreArbre+1);
            returnListe->suiv->prec = returnListe;
      }
      return returnListe;
}


//==========================================================//
//                    initMatriceVide                       //
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
//                        matrice->ecran[i-40][j-50] = 'M';
//                        positionMine.y = matrice->positionHeros.ligne-40;
//                        positionMine.x = matrice->positionHeros.colonne-50;
                  }
                  else
                  {
                        matrice->ecran[i][j] = ' ';
                  }
            }
      }
}

void remplissageMap(t_ecran_de_jeu matrice)
{
      for(int i=0; i<HAUTEUR; i++)
      {
            for(int j=0; j<LARGEUR; j++)
            {
                  if(matrice->ecran[i][j] == 'M')
                  {
                        positionMine.x = j;
                        positionMine.y = i;
                        SDL_BlitSurface(mine, NULL, ecran, &positionMine);
                  }
                  if(matrice->ecran[i][j] == 'A')
                  {
                        positionArbre.x = j;
                        positionArbre.y = i;
                        SDL_BlitSurface(arbre, NULL, ecran, &positionArbre);
                  }
            }
      }
}

//==========================================================//
//                     Affiche barre vie                    //
//==========================================================//


void afficheBarreVie(T_Heros heros, SDL_Surface* ecran)
{
      SDL_Rect rect;
      rect.x = positionBarreVie.x;
      rect.y = positionBarreVie.y;
      rect.w = heros->vie*2;
      rect.h = 20;
      SDL_FillRect(ecran, &rect, SDL_MapRGB(ecran->format, 255, 0, 0));

}

char* replaceString(char* string)
{
      char* strTmp = (char*)malloc(strlen(string)*sizeof(char));
      strcpy(strTmp, string);
      strTmp[strlen(string)-1] = '\0';
      return strTmp;
}

//==========================================================//
//                     ChargementFichier                    //
//==========================================================//
t_ecran_de_jeu chargementFichier(char* nomFichier, T_Heros heros)
{
      nombreEntites = 0;
      int nombreArbre = 0;

      char nord[1024];
      char sud[1024];
      char est[1024];
      char ouest[1024];
      char nomMap[1024];
      char test[1024];
      char ligne[1024];
      t_ecran_de_jeu matrice = create_ecran_de_jeu(HAUTEUR, LARGEUR, positionHeros.x, positionHeros.y);
      initMatrice(matrice);
      FILE* fichier = fopen(nomFichier, "r");

      if (fichier != NULL)
      {
            fprintf(stderr, "prout");
            fgets(nord, 1024, fichier);
            fgets(sud, 1024, fichier);
            fgets(est, 1024, fichier);
            fgets(ouest, 1024, fichier);
            fgets(nomMap, 1024, fichier);
            fgets(test, 1024, fichier);

            fprintf(stderr, "[%s, %s, %s, %s, %s, %s]\n",replaceString(nord), replaceString(sud), replaceString(est), replaceString(ouest), replaceString(nomMap), replaceString(test) );
            strcpy(heros->mapActuelle, replaceString(nomMap));
            fprintf(stderr, "%s\n", heros->mapActuelle);
            int cptLigneMod3 = 0;
            char c;
            int y;
            int x;
            while(fgets(ligne, 1024, fichier) != NULL)
            {
                  fprintf(stderr, "cptmod3 : %d\n", cptLigneMod3);
                  if(cptLigneMod3 % 3 == 0)
                  {
                        c = ligne[0];
                        if(c == 'M')
                        {
                              nombreEntites++;
                        }
                  }
                  else
                  {
                        if(cptLigneMod3 % 3 == 1)
                        {
                              y = strtol(ligne, NULL, 10);
                        }
                        else
                        {
                              x = strtol(ligne, NULL, 10);
                        }
                  }
                  if (cptLigneMod3 %3 == 2)
                  {
                        matrice->ecran[y][x] = c;
                        SDL_Rect temp;
                        temp.y = y;
                        temp.x = x;
                        if(c == 'A')
                        {
                              ListeArbre = ajoutArbreListe(ListeArbre, temp, nombreArbre);
                              nombreArbre++;
                        }
                  }
                  cptLigneMod3++;
            }
      }
      else
      {
            fprintf(stderr,"ERREUR LORS DE L'OUVERTURE DU FICHIER" );
      }
      while(ListeArbre->prec != NULL)
      {
            ListeArbre = ListeArbre->prec;
      }
      fprintf(stderr, "nombrearbre : [%d]\n", ListeArbre->numero);
      fclose(fichier);
return matrice;

}




//==========================================================//
//                    Lecture matrice                       //
//==========================================================//
SDL_Surface * choixAnimHeros(int direction, T_Anim anim)
{
     if(verifDirection != direction){
          anim->current = anim->first;
     }
     SDL_Surface* animTemp = anim->current->image;
      if(direction == NUL)
      {
          return anim->first->image;
      }
      anim->current = anim->current->image_suiv;
      verifDirection = direction;
      return animTemp;

}



//==========================================================//
//                    Lecture matrice                       //
//==========================================================//


void LectureMatrice(t_ecran_de_jeu matrice, SDL_Surface* ecran, SDL_Surface *  barreVie, int direction, T_Anim anim, T_Heros heros)
{
      SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
      SDL_FreeSurface(myMap);
      SDL_Surface * myMap = SDL_LoadBMP(heros->mapActuelle);
      SDL_BlitSurface(myMap, NULL, ecran, &positionMap);
      SDL_FillRect(barreHaut, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
      SDL_BlitSurface(barreHaut, NULL, ecran, &positionBarreHaut);
      afficheBarreVie(heros, ecran);
      remplissageMap(matrice);
      positionHeros.x = matrice->positionHeros.colonne;
      positionHeros.y = matrice->positionHeros.ligne;
      SDL_BlitSurface(choixAnimHeros(direction, anim), NULL, ecran, &positionHeros);

      SDL_Flip(ecran);
}




int takedamage(t_ecran_de_jeu matrice, int direction, t_pos positionHeros, T_Heros heros, int largeur, int hauteur)
{
      bool damagetaken = false;
      heros->vie -= 5;
      if(heros->vie <= 0)
      {
       exit(EXIT_SUCCESS);
      }
     else
     {
          if(direction == GAUCHE)
          {
               for(int i=0; i<hauteur; i++)
               {
                    if(matrice->ecran[positionHeros.ligne+i][positionHeros.colonne-1] != ' ')
                    {
                         damagetaken = true;
                    }
               }
               if(damagetaken == true)
               {
                  for(int i=0; i<20; i++)
                  {
                    matrice->positionHeros.colonne += 1;
                  }
               }
          }
          else if(direction == DROITE)
          {
               for(int i=0; i<hauteur; i++)
               {
                    if(matrice->ecran[positionHeros.ligne+i][positionHeros.colonne+largeur+1] != ' ')
                    {
                         damagetaken = true;
                    }
               }
               if(damagetaken == true)
               {
                  for(int i=0; i<20; i++)
                  {
                    matrice->positionHeros.colonne -= 1;

                  }
               }
          }
          else if(direction == BAS)
          {
               for(int i=0; i<largeur; i++)
               {
                    if(matrice->ecran[positionHeros.ligne+hauteur+1][positionHeros.colonne+i] != ' ')
                    {
                         damagetaken = true;
                    }
               }
               if(damagetaken == true)
               {
                  for(int i=0; i<20; i++)
                  {
                    matrice->positionHeros.ligne -= 1;

                  }
               }
          }
          else if(direction == HAUT)
          {
               for(int i=0; i<largeur; i++)
               {
                    if(matrice->ecran[positionHeros.ligne-1][positionHeros.colonne+i] != ' ')
                    {
                         damagetaken = true;
                    }
               }
               if(damagetaken == true)
               {
                  for(int i=0; i<20; i++)
                  {
                    matrice->positionHeros.ligne += 1;
                  }
               }
          }
     }
     return 3;
}

//==========================================================//
//                      création hitbox                     //
//==========================================================//
int verificationDeplacementHitbox(t_ecran_de_jeu matrice, t_pos pos, int largeur, int hauteur, int direction, int deplacement, T_Heros heros)
{
      bool damagetaken = false;

      if(direction == GAUCHE)
      {
            for(int i=0; i<hauteur; i++)
            {
                  if(matrice->ecran[pos.ligne+i][pos.colonne-1] != ' ')
                  {
                              damagetaken = true;
                  }
            }
      }
      if(direction == DROITE)
      {
            for(int i=0; i<hauteur; i++)
            {
                  if(matrice->ecran[pos.ligne+i][pos.colonne+largeur+1] != ' ')
                  {
                              damagetaken = true;
                  }
            }
      }
      if(direction == BAS)
      {
            for(int i=0; i<largeur; i++)
            {
                  if(matrice->ecran[pos.ligne+hauteur+1][pos.colonne+i] != ' ')
                  {
                              damagetaken = true;
                  }
            }
      }
      if(direction == HAUT)
      {
            for(int i=0; i<largeur; i++)
            {
                  if(matrice->ecran[pos.ligne-1][pos.colonne+i] != ' ')
                  {
                       damagetaken = true;

                  }
            }
      }
      if(damagetaken)
      {
            return takedamage(matrice, direction,  pos, heros, largeur, hauteur);
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
      return false;
}

int replacementHeros(t_ecran_de_jeu matrice, int direction, int nb, T_Heros heros)
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
                  if(matrice->ecran[i][j] != 'M' && matrice->ecran[i][j] != 'm' && matrice->ecran[i][j] != 'A' && matrice->ecran[i][j] != 'a')
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
            int cptArbre;
            while(ListeArbre->suiv != NULL)
            {
                  ListeArbre = ListeArbre->suiv;
            }
            cptArbre = ListeArbre->numero;
            while(ListeArbre->prec != NULL)
            {
                  ListeArbre = ListeArbre->prec;
            }
            for(int i=0; i<LARGEURMINE; i++)
            {
                  matrice->ecran[positionMine.y+i+1][positionMine.x] = 'm';
                  matrice->ecran[positionMine.y+i+1][positionMine.x+LARGEURMINE] = 'm';
                  matrice->ecran[positionMine.y][positionMine.x+i+1] = 'm';
                  matrice->ecran[positionMine.y+LARGEURMINE][positionMine.x+i+1] = 'm';
            }
            for(int numeroArbre = 0; numeroArbre<cptArbre; numeroArbre++)
            {
                  positionArbre.x = ListeArbre->position.x;
                  positionArbre.y = ListeArbre->position.y;
                  ListeArbre = ListeArbre->suiv;
                  for(int i=0; i<LARGEURARBRE; i++)
                  {
                        matrice->ecran[positionArbre.y][positionArbre.x+i+1] = 'a';
                        matrice->ecran[positionArbre.y+HAUTEURARBRE][positionArbre.x+i+1] = 'a';
                  }
                  for(int i=0; i<HAUTEURARBRE; i++)
                  {
                        matrice->ecran[positionArbre.y+i+1][positionArbre.x] = 'a';
                        matrice->ecran[positionArbre.y+i+1][positionArbre.x+LARGEURARBRE] = 'a';
                  }
            }
      }
      cpt++;
      return verificationDeplacementHitbox(matrice, matrice->positionHeros, LARGEURHEROSPIXEL, HAUTEURHEROSPIXEL, direction, nb, heros);
}


void deplacementMonstre(T_Monstre monstre, t_ecran_de_jeu matrice, int direction){
      fprintf(stderr,"DEPLACEMENT MONSTRE %d", direction);
}

void* calculDeplacementMonstre(void* my_Param_Thread)
{
      Uint32 tempsActuel = 0;
      Uint32 tempsPrecedent = 0;
      int directionMonstre = GAUCHE;
      int cptmvt = 0;
      int nbTours = 0;
      while(1)
      {
            if(Param_Thread->matrice->positionHeros.ligne == Param_Thread->monstre->pos_monstre.ligne || Param_Thread->matrice->positionHeros.colonne == Param_Thread->monstre->pos_monstre.colonne)
            {
                 Param_Thread->monstre->aggressif = true;
            }
            if (Param_Thread->monstre->aggressif == true) //Si 30 ms se sont écoulées depuis le dernier tour de boucle
            {
                  while(Param_Thread->monstre->pos_monstre.colonne != Param_Thread->matrice->positionHeros.colonne
                  && Param_Thread->monstre->pos_monstre.ligne != Param_Thread->matrice->positionHeros.ligne
                  && Param_Thread->monstre->aggressif == true){
                      //  Detection de la position du monstre par rapport au héros
                        if((abs(Param_Thread->monstre->pos_monstre.ligne - Param_Thread->matrice->positionHeros.ligne))
                           <
                           (abs(Param_Thread->monstre->pos_monstre.colonne) - Param_Thread->matrice->positionHeros.colonne))
                        {
                              if(Param_Thread->monstre->pos_monstre.ligne > Param_Thread->matrice->positionHeros.ligne){
                                   deplacementMonstre(Param_Thread->monstre, Param_Thread->matrice, directionMonstre);
                              }
                              else if(Param_Thread->monstre->pos_monstre.ligne < Param_Thread->matrice->positionHeros.ligne){
                                    deplacementMonstre(Param_Thread->monstre, Param_Thread->matrice, directionMonstre);
                              }
                        }
                        else{
                              if(Param_Thread->monstre->pos_monstre.colonne > Param_Thread->matrice->positionHeros.colonne){
                                    deplacementMonstre(Param_Thread->monstre, Param_Thread->matrice, directionMonstre);
                              }
                              else if(Param_Thread->monstre->pos_monstre.colonne < Param_Thread->matrice->positionHeros.colonne){
                                    deplacementMonstre(Param_Thread->monstre, Param_Thread->matrice, directionMonstre);
                              }
                        }
                  }
            }
            else{
                  tempsActuel = SDL_GetTicks();
                  if (tempsActuel - tempsPrecedent > 10)
                  {
                        //fprintf(stderr,"IF : %d \n", tempsActuel -tempsPrecedent);
                        switch(directionMonstre)
                        {
                        case GAUCHE :
                                    Param_Thread->monstre->pos_monstre.colonne -= Param_Thread->nbdeplacement;
                                    cptmvt++;
                                    fprintf(stderr,"DEPLACEMENT MONSTRE %d", directionMonstre);
                                    if(cptmvt == 30){
                                          fprintf(stderr,"\n");
                                          directionMonstre = HAUT;
                                          cptmvt = 0;
                                    }
                                    break;
                        case HAUT  :
                                    Param_Thread->monstre->pos_monstre.ligne += Param_Thread->nbdeplacement;
                                    fprintf(stderr,"DEPLACEMENT MONSTRE %d", directionMonstre);
                                    cptmvt++;
                                    if(cptmvt == 30){
                                          fprintf(stderr,"\n");
                                          directionMonstre = DROITE;
                                          cptmvt = 0;
                                    }
                                    break;
                        case DROITE :
                                    Param_Thread->monstre->pos_monstre.colonne += Param_Thread->nbdeplacement;
                                    fprintf(stderr,"DEPLACEMENT MONSTRE %d", directionMonstre);
                                    cptmvt++;
                                    if(cptmvt == 30){
                                          fprintf(stderr,"\n");
                                          directionMonstre = BAS;
                                          cptmvt = 0;
                                    }
                                    break;
                        case BAS :
                                    Param_Thread->monstre->pos_monstre.ligne += Param_Thread->nbdeplacement;
                                    fprintf(stderr,"DEPLACEMENT MONSTRE %d", directionMonstre);
                                    cptmvt++;
                                    if(cptmvt == 30){
                                          fprintf(stderr,"\n");
                                          directionMonstre = GAUCHE;
                                          cptmvt = 0;
                                          nbTours++;
                                    }
                                    break;
                        //case default :
                          //          break;
                        }
                        tempsPrecedent = tempsActuel;
                  }
                 else  //Si ça fait moins de 30 ms depuis le dernier tour de boucle, on endort le programme le temps qu'il faut
                  {
                       // fprintf(stderr,"ELSE : %d \n", 10 - (tempsActuel - tempsPrecedent));
                        SDL_Delay(10 - (tempsActuel - tempsPrecedent));
                  }
           }
      }
      return 0;
}
