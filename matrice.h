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
#define LARGEURARBRE 23
#define HAUTEURARBRE 40
#define TAILLEROCHER 20
#define LARGEURARMURERIE 80
#define HAUTEURARMURERIE 60
#define LARGEURCHATEAU 238
#define HAUTEURCHATEAU 183
#define HAUTEUREAU1 60
#define LARGEUREAU1 80
#define HAUTEUREAU2 60
#define LARGEUREAU2 260
#define HAUTEUREAU3 348
#define LARGEUREAU3 137
#define HAUTEUREAU4 595
#define LARGEUREAU4 60
#define HAUTEURFORTIFICATION1 20
#define LARGEURFORTIFICATION1 260
#define HAUTEURFORTIFICATION2 328
#define LARGEURFORTIFICATION2 20
#define HAUTEURFORTIFICATION3 22
#define LARGEURFORTIFICATION3 580
#define HAUTEURFORTIFICATION4 349
#define LARGEURFORTIFICATION4 19
#define HAUTEURFORTIFICATION5 22
#define LARGEURFORTIFICATION5 220
#define HAUTEURGRANDARBRE 100
#define LARGEURGRANDARBRE 100
#define Param_Thread (*(T_Param_Thread*)my_Param_Thread)

/* Déclaration de la structure héros pour utilisation */
struct S_Heros;
typedef struct S_Heros* T_Heros;

struct S_Monstre;
typedef struct S_Monstre* T_Monstre;



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

typedef struct S_Monstre
{
      bool aggressif;
      int vie;
      int degats;
      t_pos pos_monstre;

}* T_Monstre;



struct s_ecran_de_jeu
{
      char** ecran;
      int hauteur;
      int largeur;
      char* nord;
      char* sud;
      char* est;
      char* ouest;
      t_pos positionHeros;
      T_Monstre tab_monstres;

};     //creation de la structure qui va former l'écran
typedef struct s_ecran_de_jeu * t_ecran_de_jeu;

typedef struct S_Param_Thread{
            T_Monstre monstre;
            t_ecran_de_jeu matrice;
            int nbdeplacement;
}* T_Param_Thread;


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
extern SDL_Surface * arbre;
extern SDL_Surface * barreHaut;
extern SDL_Surface * barreVie;
extern SDL_Surface * rocher;
extern SDL_Surface * armurerie;
extern SDL_Surface * chateau;
extern SDL_Surface * eau_1;
extern SDL_Surface * eau_2_1;
extern SDL_Surface * eau_2_2;
extern SDL_Surface * eau_3;
extern SDL_Surface * eau_4;
extern SDL_Surface * fortification_1;
extern SDL_Surface * fortification_2;
extern SDL_Surface * fortification_3;
extern SDL_Surface * fortification_4;
extern SDL_Surface * fortification_5;
extern SDL_Surface * grandArbre;

SDL_Rect positionHeros;
SDL_Rect positionMap;
SDL_Rect positionMine;
SDL_Rect positionBarreHaut;
SDL_Rect positionBarreVie;
SDL_Rect positionArbre;
SDL_Rect positionMonstre;
SDL_Rect positionRocher;
SDL_Rect positionArmurerie;
SDL_Rect positionChateau;
SDL_Rect positionEau_1;
SDL_Rect positionEau_2_1;
SDL_Rect positionEau_2_2;
SDL_Rect positionEau_3;
SDL_Rect positionEau_4;
SDL_Rect positionFortification_1;
SDL_Rect positionFortification_2;
SDL_Rect positionFortification_3;
SDL_Rect positionFortification_4;
SDL_Rect positionFortification_5;
SDL_Rect positionGrandArbre;

#ifdef __cplusplus
extern "C"
{
#endif

t_ecran_de_jeu create_ecran_de_jeu(int hauteur, int largeur, int posHerosColonne, int posHerosLigne);
void initMatrice(t_ecran_de_jeu matrice);
t_ecran_de_jeu chargementFichier(char* nomFichier, T_Heros heros, int x, int y);
T_Anim initialisationAnim(int direction);
T_Param_Thread allocParamThread (t_ecran_de_jeu matrice, int nbdeplacement);
T_Monstre allocMonstre(int vie, int damage, int ligne, int colonne);
void LectureMatrice(t_ecran_de_jeu matrice, SDL_Surface* ecran, SDL_Surface *  barreVie, int direction, T_Anim anim, T_Heros heros);
int takedamage(t_ecran_de_jeu matrice, int direction, t_pos positionHeros, T_Heros heros, int largeur, int hauteur);
int verificationDeplacementHitbox(t_ecran_de_jeu matrice, t_pos pos, int largeur, int hauteur, int direction, int deplacement, T_Heros heros);
bool verifierPoussee(t_ecran_de_jeu matrice, int direction, t_pos positionHeros, int deplacement);
int replacementHeros(t_ecran_de_jeu matrice, int direction, int nb, T_Heros heros);
void* calculDeplacementMonstre(void* my_Param_Thread);
void deplacementMonstre(T_Monstre monstre, t_ecran_de_jeu matrice, int direction);
#ifdef __cplusplus
}
#endif

#endif
