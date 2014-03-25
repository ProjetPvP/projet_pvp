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
SDL_Surface * rocher = NULL;
SDL_Surface * armurerie = NULL;
SDL_Surface * chateau = NULL;
SDL_Surface * eau_1 = NULL;
SDL_Surface * eau_2_1 = NULL;
SDL_Surface * eau_2_2 = NULL;
SDL_Surface * eau_3 = NULL;
SDL_Surface * eau_4 = NULL;
SDL_Surface * fortification_1 = NULL;
SDL_Surface * fortification_2 = NULL;
SDL_Surface * fortification_3 = NULL;
SDL_Surface * fortification_4 = NULL;
SDL_Surface * fortification_5 = NULL;
SDL_Surface * grandArbre = NULL;
SDL_Surface * montagne = NULL;


//==========================================================//
//                   variables globales                     //
//==========================================================//

typedef struct S_ListePosition * T_ListePosition;
      struct S_ListePosition
      {
            int numero;
            SDL_Rect position;
            struct S_ListePosition* suiv;
            struct S_ListePosition* prec;
      };
typedef struct S_ListePosition * T_ListePosition;

      static int cpt = 0;
      static int cptHitbox = 0;
      static int verifDirection = NUL;
      static int nombreEntites = 0;
      static int nombreEntitesThread = 0;
      struct S_ListePosition;

      static T_ListePosition ListeArbre = NULL;
      static T_ListePosition ListeRocher = NULL;
      static char* tableauDirection[4];




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

T_ListePosition allocListeObjet(SDL_Rect rect, int nombreArbre)
{
      T_ListePosition newPosition = (T_ListePosition)malloc(sizeof(struct S_ListePosition));
      newPosition->numero = nombreArbre;
      newPosition->position = rect;
      newPosition->suiv = NULL;
      newPosition->prec = NULL;
      return newPosition;
}


T_Monstre allocMonstre(char * nom, int vie, int damage, int ligne, int colonne)
{
      T_Monstre newMonstre = (T_Monstre)malloc(sizeof(struct S_Monstre));
      newMonstre->vie = vie;
      newMonstre->degats = damage;

      newMonstre->pos_monstre.ligne = ligne;
      newMonstre->pos_monstre.colonne = colonne;
      newMonstre->nom = (char *)malloc(strlen(nom)* sizeof(char));
      strcpy(newMonstre->nom, nom);
      newMonstre->aggressif = false;
      return newMonstre;
}

T_Param_Thread allocParamThread(t_ecran_de_jeu matrice, int nbdeplacement)
{
      T_Param_Thread newParamThread = (T_Param_Thread)malloc(sizeof(struct S_Param_Thread));
      newParamThread->monstre = allocMonstre(matrice->tab_monstres[nombreEntitesThread].nom,
                                                matrice->tab_monstres[nombreEntitesThread].vie,
                                                matrice->tab_monstres[nombreEntitesThread].degats,
                                                matrice->tab_monstres[nombreEntites].pos_monstre.ligne,
                                                matrice->tab_monstres[nombreEntites].pos_monstre.colonne
                                                );
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

T_ListePosition ajoutObjetListe(T_ListePosition maListe, SDL_Rect pos, int nombreArbre)
{
      T_ListePosition returnListe;
      if(nombreArbre == 0)
      {
            returnListe = allocListeObjet(pos, nombreArbre+1);

      }
      else
      {
            returnListe = maListe;
            while(returnListe->suiv != NULL)
            {
                  returnListe = returnListe->suiv;
            }
            returnListe->suiv = allocListeObjet(pos, nombreArbre+1);
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
                  }
                  else
                  {
                        matrice->ecran[i][j] = ' ';
                  }
            }
      }
}
SDL_Rect affichageObjet(SDL_Surface * objet, SDL_Rect position, int i, int j)
{
      position.x = j;
      position.y = i;
      SDL_BlitSurface(objet, NULL, ecran, &position);
      return position;
}

void remplissageMap(t_ecran_de_jeu matrice)
{
      for(int i=0; i<HAUTEUR; i++)
      {
            for(int j=0; j<LARGEUR; j++)
            {
                  if(matrice->ecran[i][j] == 'M')
                  {
                        positionMine = affichageObjet(mine, positionMine, i, j);
                  }
                  if(matrice->ecran[i][j] == 'A')
                  {
                        positionArbre = affichageObjet(arbre, positionArbre, i, j);
                  }
                  if(matrice->ecran[i][j] == 'R')
                  {
                        positionRocher = affichageObjet(rocher, positionRocher, i, j);
                  }
                  if(matrice->ecran[i][j] == 'S')
                  {
                        positionArmurerie = affichageObjet(armurerie, positionArmurerie, i, j);
                  }
                  if(matrice->ecran[i][j] == 'C')
                  {
                        positionChateau = affichageObjet(chateau, positionChateau, i, j);
                  }
                  if(matrice->ecran[i][j] == '1')
                  {
                        positionEau_1 = affichageObjet(eau_1, positionEau_1, i, j);
                  }
                  if(matrice->ecran[i][j] == '2')
                  {
                        positionEau_2_1 = affichageObjet(eau_2_1, positionEau_2_1, i, j);
                  }
                  if(matrice->ecran[i][j] == '3')
                  {
                        positionEau_2_2 = affichageObjet(eau_2_2, positionEau_2_2, i, j);
                  }
                  if(matrice->ecran[i][j] == '4')
                  {
                        positionEau_3 = affichageObjet(eau_3, positionEau_3, i, j);
                  }
                  if(matrice->ecran[i][j] == '5')
                  {
                        positionEau_4 = affichageObjet(eau_4, positionEau_4, i, j);
                  }
                  if(matrice->ecran[i][j] == '6')
                  {
                        positionFortification_1 = affichageObjet(fortification_1, positionFortification_1, i, j);
                  }
                  if(matrice->ecran[i][j] == '7')
                  {
                        positionFortification_2 = affichageObjet(fortification_2, positionFortification_2, i, j);
                  }
                  if(matrice->ecran[i][j] == '8')
                  {
                        positionFortification_3 = affichageObjet(fortification_3, positionFortification_3, i, j);
                  }
                  if(matrice->ecran[i][j] == '9')
                  {
                        positionFortification_4 = affichageObjet(fortification_4, positionFortification_4, i, j);

                  }
                  if(matrice->ecran[i][j] == '0')
                  {
                        positionFortification_5 = affichageObjet(fortification_5, positionFortification_5, i, j);
                  }
                  if(matrice->ecran[i][j] == 'G')
                  {
                        positionGrandArbre = affichageObjet(grandArbre, positionGrandArbre, i, j);
                  }
                  if(matrice->ecran[i][j] == 'Z')
                  {
                        positionMontagne = affichageObjet(montagne, positionMontagne, i, j);
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
T_ListePosition debutListe(T_ListePosition liste)
{
      while(liste != NULL && liste->prec != NULL)
      {
            liste = liste->prec;
      }
      return liste;
}


//==========================================================//
//                     ChargementFichier                    //
//==========================================================//
t_ecran_de_jeu chargementFichier(char* nomFichier, T_Heros heros, int x, int y)
{
      nombreEntites = 0;
      int nombreArbre = 0;
      int nombreRocher = 0;

      char nord[1024];
      char sud[1024];
      char est[1024];
      char ouest[1024];
      char nomMap[1024];
      char test[1024];
      char ligne[1024];
      t_ecran_de_jeu matrice = create_ecran_de_jeu(HAUTEUR, LARGEUR, x, y);
      initMatrice(matrice);
      FILE* fichier = fopen(nomFichier, "r");


      if (fichier != NULL)
      {
            fprintf(stderr, "prout");
            fgets(nord, 1024, fichier);
            tableauDirection[0] = replaceString(nord);
            fprintf(stderr, "tableaudirection[1] = %s\n", tableauDirection[0]);
            fgets(sud, 1024, fichier);
            tableauDirection[1] = replaceString(sud);
            fgets(est, 1024, fichier);
            tableauDirection[2] = replaceString(est);
            fgets(ouest, 1024, fichier);
            tableauDirection[3] = replaceString(ouest);
            fprintf(stderr, "tableaudirection[4] = %s\n", tableauDirection[3]);
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
                  if(cptLigneMod3 % 3 == 0)
                  {
                        c = ligne[0];
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
                        fprintf(stderr, "%c %d %d\n", c, x, y);
                        if(c == 'A')
                        {
                              ListeArbre = ajoutObjetListe(ListeArbre, temp, nombreArbre);
                              nombreArbre++;
                        }
                        if(c == 'R')
                        {
                              ListeRocher = ajoutObjetListe(ListeRocher, temp, nombreRocher);
                              nombreRocher++;
                        }
//                        if (c == 'E')
//                        {
//                              char* nomMonstre = (char*)malloc(10*sizeof(char));
//                              strcpy(nomMonstre,"");
//                              char nomMonstrefin[1];
//                              sprintf(nomMonstrefin,"%d",nombreEntites);
//                              strcat(nomMonstre, "monstre");
//                              strcat(nomMonstre, nomMonstrefin);
//                              temp.y = y;
//                              temp.x = x;
//                              matrice->tab_monstres[nombreEntites] = (*allocMonstre(nomMonstre,10,10,temp.y, temp.x));
//                              nombreEntites++;
//                        }
                  }
                  cptLigneMod3++;
            }
      }
      else
      {
            fprintf(stderr,"ERREUR LORS DE L'OUVERTURE DU FICHIER" );
      }

      fprintf(stderr, "prout avntfinfichier");
      ListeArbre = debutListe(ListeArbre);
      ListeRocher = debutListe(ListeRocher);
      fprintf(stderr, "proutfinfichier");
      fclose(fichier);
      cptHitbox = 0;
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
                    if(matrice->ecran[positionHeros.ligne+i][positionHeros.colonne-1] == 'e')
                    {
                         damagetaken = true;
                         heros->vie -= 5;
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
                    if(matrice->ecran[positionHeros.ligne+i][positionHeros.colonne+largeur+1] == 'e')
                    {
                         damagetaken = true;
                         heros->vie -= 5;
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
                    if(matrice->ecran[positionHeros.ligne+hauteur+1][positionHeros.colonne+i] == 'e')
                    {
                         damagetaken = true;
                         heros->vie -= 5;
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
                    if(matrice->ecran[positionHeros.ligne-1][positionHeros.colonne+i] == 'e')
                    {
                         damagetaken = true;
                         heros->vie -= 5;
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
            else if (matrice->ecran[positionHeros.ligne][positionHeros.colonne+1+LARGEURHEROSPIXEL] == ' ')
            {
                  return true;
            }
      }
      else if (direction == HAUT)
      {
            if (positionHeros.ligne < 1+deplacement)
            {
                  if(strcmp(tableauDirection[0], "NULL") == 1)
                  {

                  }
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
            else if (matrice->ecran[positionHeros.ligne+1+HAUTEURHEROSPIXEL][positionHeros.colonne] == ' ')
            {
                  return true;
            }
      }
      return false;
}
int compteurListe(T_ListePosition liste)
{
      int numero;
      fprintf(stderr, "on est dans compteurliste\n");
      if(liste != NULL)
      {
            T_ListePosition tmp = liste;
            while (tmp->suiv != NULL)
            {
                  tmp = tmp->suiv;
            }
            numero = tmp->numero;
            fprintf(stderr, "numero : %d\n", numero);
            return numero;
      }
      else return 0;
}
void ajoutHitboxListe(T_ListePosition liste, SDL_Rect position, t_ecran_de_jeu matrice, int hauteur, int largeur, char c)
{
      if(liste != NULL)
      {
            int numero = compteurListe(liste);
            for(int numeroObjet = 0; numeroObjet<numero; numeroObjet++)
                  {
                        position.x = liste->position.x;
                        position.y = liste->position.y;
                        fprintf(stderr, "ajoutHitbox %d%d\n",position.x, position.y);
                        liste = liste->suiv;
                        for(int i=0; i<largeur; i++)
                        {
                              matrice->ecran[position.y][position.x+i+1] = tolower(c);
                              matrice->ecran[position.y+hauteur][position.x+i+1] = tolower(c);
                        }
                        for(int i=0; i<hauteur; i++)
                        {
                              matrice->ecran[position.y+i+1][position.x] = tolower(c);
                              matrice->ecran[position.y+i+1][position.x+largeur] = tolower(c);
                        }
                  }
      }
}

void ajoutHitboxSimple(SDL_Rect position, t_ecran_de_jeu matrice, int hauteur, int largeur, char c, int nb)
{
      if (nb != 0)
      {
            for(int i=0; i<largeur; i++)
            {
                  matrice->ecran[position.y][position.x+i+1] = tolower(c);
                  matrice->ecran[position.y+hauteur][position.x+i+1] = tolower(c);
            }
            for(int i=0; i<hauteur; i++)
            {
                  matrice->ecran[position.y+i+1][position.x] = tolower(c);
                  matrice->ecran[position.y+i+1][position.x+largeur] = tolower(c);
            }
      }
}


int replacementHeros(t_ecran_de_jeu matrice, int direction, int nb, T_Heros heros)
{
      int nbChateau = 0;
      int nbArmurerie = 0;
      int nbEau_1 = 0;
      int nbEau_2_1 = 0;
      int nbEau_2_2 = 0;
      int nbEau_3 = 0;
      int nbEau_4 = 0;
      int nbFortification1 = 0;
      int nbFortification2 = 0;
      int nbFortification3 = 0;
      int nbFortification4 = 0;
      int nbFortification5 = 0;
      int nbGrandArbre = 0;
      int nbMontagne = 0;
      for (int i=51; i<HAUTEUR; i++)
      {
            for (int j=0; j<LARGEUR; j++)
            {
                  if(matrice->ecran[i][j] != 'M' && matrice->ecran[i][j] != 'm'
                     && matrice->ecran[i][j] != 'A' && matrice->ecran[i][j] != 'a'
                     && matrice->ecran[i][j] != 'C' && matrice->ecran[i][j] != 'c'
                     && matrice->ecran[i][j] != 'S' && matrice->ecran[i][j] != 's'
                     && matrice->ecran[i][j] != 'w' && matrice->ecran[i][j] != '1'
                     && matrice->ecran[i][j] != '2' && matrice->ecran[i][j] != '3'
                     && matrice->ecran[i][j] != '4' && matrice->ecran[i][j] != '5'
                     && matrice->ecran[i][j] != '6' && matrice->ecran[i][j] != '7'
                     && matrice->ecran[i][j] != '8' && matrice->ecran[i][j] != '9'
                     && matrice->ecran[i][j] != '0' && matrice->ecran[i][j] != 'f'
                     && matrice->ecran[i][j] != 'F' && matrice->ecran[i][j] != 'G'
                     && matrice->ecran[i][j] != 'g' && matrice->ecran[i][j] != 'R'
                     && matrice->ecran[i][j] != 'r' && matrice->ecran[i][j] != 'Z'
                     && matrice->ecran[i][j] != 'z')
                  {
                        matrice->ecran[i][j] = ' ';
                  }
                  else
                  {
                        if(matrice->ecran[i][j] == 'C')
                        {
                              nbChateau++;
                        }
                        if(matrice->ecran[i][j] == 'S')
                        {
                              nbArmurerie++;
                        }
                        if(matrice->ecran[i][j] == '1')
                        {
                              nbEau_1++;
                        }
                        if(matrice->ecran[i][j] == '2')
                        {
                              nbEau_2_1++;
                        }
                        if(matrice->ecran[i][j] == '3')
                        {
                              nbEau_2_2++;
                        }
                        if(matrice->ecran[i][j] == '4')
                        {
                              nbEau_3++;
                        }
                        if(matrice->ecran[i][j] == '5')
                        {
                              nbEau_4++;
                        }
                        if(matrice->ecran[i][j] == '6')
                        {
                              nbFortification1++;
                        }
                        if(matrice->ecran[i][j] == '7')
                        {
                              nbFortification2++;
                        }
                        if(matrice->ecran[i][j] == '8')
                        {
                              nbFortification3++;
                        }
                        if(matrice->ecran[i][j] == '9')
                        {
                              nbFortification4++;
                        }
                        if(matrice->ecran[i][j] == '0')
                        {
                              nbFortification5++;
                        }
                        if(matrice->ecran[i][j] == 'G')
                        {
                              nbGrandArbre++;
                        }
                        if(matrice->ecran[i][j] == 'Z')
                        {
                              nbMontagne++;
                        }
                  }
                  if ((matrice->positionHeros.ligne == i) && (matrice->positionHeros.colonne == j))
                  {
                        matrice->ecran[i][j] = 'H';
                  }
            }
      }
//      if(nombreEntites>0)
//      {
//            for (int k = 0; k < nombreEntites; k++)
//            {
//                  matrice->ecran[matrice->tab_monstres[k].pos_monstre.ligne][matrice->tab_monstres[k].pos_monstre.colonne] = 'E';
//            }
//      }

      if (cptHitbox == 0)
      {

            ajoutHitboxSimple(positionChateau, matrice, HAUTEURCHATEAU, LARGEURCHATEAU, 'C', nbChateau);
            ajoutHitboxSimple(positionArmurerie, matrice, HAUTEURARMURERIE, LARGEURARMURERIE, 'S', nbArmurerie);
            ajoutHitboxSimple(positionEau_1, matrice, HAUTEUREAU1, LARGEUREAU1, 'W', nbEau_1);
            ajoutHitboxSimple(positionEau_2_1, matrice, HAUTEUREAU2, LARGEUREAU2, 'W', nbEau_2_1);
            ajoutHitboxSimple(positionEau_2_2, matrice, HAUTEUREAU2, LARGEUREAU2, 'W', nbEau_2_2);
            ajoutHitboxSimple(positionEau_3, matrice, HAUTEUREAU3, LARGEUREAU3, 'W', nbEau_3);
            ajoutHitboxSimple(positionEau_4, matrice, HAUTEUREAU4, LARGEUREAU4, 'W', nbEau_4);
            ajoutHitboxSimple(positionFortification_1, matrice, HAUTEURFORTIFICATION1, LARGEURFORTIFICATION1, 'F', nbFortification1);
            ajoutHitboxSimple(positionFortification_2, matrice, HAUTEURFORTIFICATION2, LARGEURFORTIFICATION2, 'F', nbFortification2);
            ajoutHitboxSimple(positionFortification_3, matrice, HAUTEURFORTIFICATION3, LARGEURFORTIFICATION3, 'F', nbFortification3);
            ajoutHitboxSimple(positionFortification_4, matrice, HAUTEURFORTIFICATION4, LARGEURFORTIFICATION4, 'F', nbFortification4);
            ajoutHitboxSimple(positionFortification_5, matrice, HAUTEURFORTIFICATION5, LARGEURFORTIFICATION5, 'F', nbFortification5);
            ajoutHitboxSimple(positionGrandArbre, matrice, HAUTEURGRANDARBRE, LARGEURGRANDARBRE, 'G', nbGrandArbre);
            ajoutHitboxSimple(positionMontagne, matrice, HAUTEURMONTAGNE, LARGEURMONTAGNE, 'Z', nbMontagne);


            ajoutHitboxListe(ListeArbre, positionArbre, matrice, HAUTEURARBRE, LARGEURARBRE, 'A');
            ajoutHitboxListe(ListeRocher, positionRocher, matrice, TAILLEROCHER, TAILLEROCHER, 'R');
      cptHitbox++;
      }
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

      return verificationDeplacementHitbox(matrice, matrice->positionHeros, LARGEURHEROSPIXEL, HAUTEURHEROSPIXEL, direction, nb, heros);
}
void replacementMonstre(t_ecran_de_jeu matrice)
{
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
      for (int k = 0; k < nombreEntites; k++){
            matrice->ecran[matrice->tab_monstres[k].pos_monstre.ligne][matrice->tab_monstres[k].pos_monstre.colonne] = 'E';
      }
}

void* calculDeplacementMonstre(void* my_Param_Thread)
{
      int id_thread = nombreEntitesThread;
      nombreEntitesThread++;
      Uint32 tempsActuel = 0;
      Uint32 tempsPrecedent = 0;
      int directionMonstre = GAUCHE;
      int cptmvt = 0;
      int tempsAggro = 0;
      int nbTours = 0;
      while(1)
      {
          if(Param_Thread->matrice->positionHeros.ligne == Param_Thread_Monstre.pos_monstre.ligne || Param_Thread->matrice->positionHeros.colonne == Param_Thread_Monstre.pos_monstre.colonne)
            {
                 Param_Thread_Monstre.aggressif = true;
            }
            if (Param_Thread_Monstre.aggressif == true) //Si 30 ms se sont écoulées depuis le dernier tour de boucle
            {

                  while((Param_Thread_Monstre.pos_monstre.colonne != Param_Thread->matrice->positionHeros.colonne
                  || Param_Thread_Monstre.pos_monstre.ligne != Param_Thread->matrice->positionHeros.ligne)
                  && Param_Thread_Monstre.aggressif == true){
                        tempsActuel = SDL_GetTicks();
                      //  Detection de la position du monstre par rapport au héros
                        if(Param_Thread->matrice->positionHeros.colonne == Param_Thread_Monstre.pos_monstre.colonne){
                              if(Param_Thread->matrice->positionHeros.ligne > Param_Thread_Monstre.pos_monstre.ligne){
                                   //deplacementMonstre(Param_Thread,BAS,id_thread);
                                    Param_Thread_Monstre.pos_monstre.ligne += Param_Thread->nbdeplacement;
                                    replacementMonstre(Param_Thread->matrice);
                                    SDL_Delay(10);
                              }
                              else{
                                    //deplacementMonstre(Param_Thread, HAUT,id_thread);
                                    Param_Thread_Monstre.pos_monstre.ligne -= Param_Thread->nbdeplacement;
                                    replacementMonstre(Param_Thread->matrice);
                                    SDL_Delay(10);
                              }
                        }
                        else if(Param_Thread->matrice->positionHeros.ligne == Param_Thread_Monstre.pos_monstre.ligne){
                              if(Param_Thread->matrice->positionHeros.colonne > Param_Thread_Monstre.pos_monstre.colonne){
                                    Param_Thread_Monstre.pos_monstre.colonne += Param_Thread->nbdeplacement;
                                    replacementMonstre(Param_Thread->matrice);
                                   // deplacementMonstre(Param_Thread, DROITE,id_thread);
                                    SDL_Delay(10);
                              }
                              else{
                                    Param_Thread_Monstre.pos_monstre.colonne -= Param_Thread->nbdeplacement;
                                    replacementMonstre(Param_Thread->matrice);
                                  // deplacementMonstre(Param_Thread, GAUCHE,id_thread);
                                    SDL_Delay(10);
                              }
                        }
                        if(tempsActuel - tempsPrecedent > 2500){
                               Param_Thread_Monstre.aggressif = false;
                        }
                  }
            }
            else{
                  tempsActuel = SDL_GetTicks();
                  if (tempsActuel - tempsPrecedent > 10)
                  {

                        switch(directionMonstre)
                        {
                        case GAUCHE :
                                    Param_Thread_Monstre.pos_monstre.colonne -= Param_Thread->nbdeplacement;
                                    replacementMonstre(Param_Thread->matrice);
                                    cptmvt++;
                                    if(cptmvt == 30){
                                          directionMonstre = HAUT;
                                          cptmvt = 0;
                                    }
                                    break;
                        case HAUT  :
                                   Param_Thread_Monstre.pos_monstre.ligne -= Param_Thread->nbdeplacement;
                                   //Param_Thread->matrice->ecran[Param_Thread->matrice->tab_monstres[nombreEntitesThread].pos_monstre.ligne-1][Param_Thread->matrice->tab_monstres[nombreEntitesThread].pos_monstre.colonne] = ' ';
                                    //fprintf(stderr,"DEPLACEMENT MONSTRE %d", directionMonstre);
                                    replacementMonstre(Param_Thread->matrice);
                                    cptmvt++;
                                    if(cptmvt == 30){
                                          directionMonstre = DROITE;
                                          cptmvt = 0;
                                    }
                                    break;
                        case DROITE :
                                    Param_Thread_Monstre.pos_monstre.colonne += Param_Thread->nbdeplacement;
                                    //Param_Thread->matrice->ecran[Param_Thread->matrice->tab_monstres[nombreEntitesThread].pos_monstre.ligne][Param_Thread->matrice->tab_monstres[nombreEntitesThread].pos_monstre.colonne+1] = ' ';
                                   // fprintf(stderr,"DEPLACEMENT MONSTRE %d", directionMonstre);
                                    replacementMonstre(Param_Thread->matrice);
                                    cptmvt++;
                                    if(cptmvt == 30){
                                          directionMonstre = BAS;
                                          cptmvt = 0;
                                    }
                                    break;
                        case BAS :
                                     Param_Thread_Monstre.pos_monstre.ligne += Param_Thread->nbdeplacement;
                                     //Param_Thread->matrice->ecran[Param_Thread->matrice->tab_monstres[nombreEntitesThread].pos_monstre.ligne-1][Param_Thread->matrice->tab_monstres[nombreEntitesThread].pos_monstre.colonne-1] = ' ';
                                   // fprintf(stderr,"DEPLACEMENT MONSTRE %d", directionMonstre);
                                    replacementMonstre(Param_Thread->matrice);
                                    cptmvt++;
                                    if(cptmvt == 30){
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
                        //fprintf(stderr,"SDL_DELAY\n");
                        SDL_Delay(10 - (tempsActuel - tempsPrecedent));
                  }
           }

      }
      return 0;
}
