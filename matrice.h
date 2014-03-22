#ifndef _MATRICE_H
#define _MATRICE_H
#include <stdlib.h>
#include <SDL/SDL.h>
#include <stdbool.h>
#include "heros.h"
#define HAUTEUR 400
#define LARGEUR 600
#define LARGEURHEROSPIXEL 16
#define HAUTEURHEROSPIXEL 27
#define LARGEURMINE 20

/* Déclaration de la structure héros pour utilisation */
struct S_Heros;
typedef struct S_Heros* T_Heros;

enum {
      HAUT,
      BAS,
      GAUCHE,
      DROITE,
      NUL};
char tableau_ecran[HAUTEUR][LARGEUR];

struct s_pos
{
      int ligne;
       int colonne;
};
typedef struct s_pos t_pos;

struct s_ecran_de_jeu
{
      char** ecran;
      int hauteur;
      int largeur;
      t_pos positionHeros;
};     //creation de la structure qui va former l'écran

typedef struct s_ecran_de_jeu * t_ecran_de_jeu;

typedef struct S_Image
{
      SDL_Surface* image;
      struct S_Image* image_suiv;
      int position;
} * T_Image;

typedef struct S_Anim
{
 T_Image first;
 T_Image current;
} * T_Anim;

SDL_Event event;
extern SDL_Surface * ecran;
extern SDL_Surface * HerosHaut;
extern SDL_Surface * HerosAnimationHaut;
extern SDL_Surface * HerosAnimation2Haut;
extern SDL_Surface * HerosBas;
extern SDL_Surface * HerosAnimationBas;
extern SDL_Surface * HerosAnimation2Bas;
extern SDL_Surface * HerosGauche;
extern SDL_Surface * HerosAnimationGauche;
extern SDL_Surface * HerosAnimation2Gauche;
extern SDL_Surface * HerosDroite;
extern SDL_Surface * HerosAnimationDroite;
extern SDL_Surface * HerosAnimation2Droite;
extern SDL_Surface * myMap;
extern SDL_Surface * mine;
extern SDL_Surface * barreHaut;
extern SDL_Surface * barreVie;

SDL_Rect positionHeros;
SDL_Rect positionMap;
SDL_Rect positionMine;
SDL_Rect positionBarreHaut;
SDL_Rect positionBarreVie;

#ifdef __cplusplus
extern "C"
{
#endif

t_ecran_de_jeu create_ecran_de_jeu(int hauteur, int largeur, int posHerosColonne, int posHerosLigne);
void initMatrice(t_ecran_de_jeu matrice);
T_Anim initialisationAnim(int direction);
void LectureMatrice(t_ecran_de_jeu matrice, SDL_Surface* ecran, SDL_Surface *  barreVie, int direction, T_Anim anim, T_Heros heros);
bool takedamage(t_ecran_de_jeu matrice, int direction, t_pos positionHeros, T_Heros heros, int largeur, int hauteur);
int verificationDeplacementHitbox(t_ecran_de_jeu matrice, t_pos pos, int largeur, int hauteur, int direction, int deplacement, T_Heros heros);
bool verifierPoussee(t_ecran_de_jeu matrice, int direction, t_pos positionHeros, int deplacement);
void replacementHeros(t_ecran_de_jeu matrice, int direction, int nb, T_Heros heros);

#ifdef __cplusplus
}
#endif

#endif
