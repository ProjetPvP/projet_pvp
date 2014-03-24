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

SDL_Rect positionHeros;
SDL_Rect positionMap;
SDL_Rect positionMine;
SDL_Rect positionBarreHaut;
SDL_Rect positionBarreVie;
SDL_Rect positionArbre;
SDL_Rect positionMonstre;
SDL_Rect positionRocher;

#ifdef __cplusplus
extern "C"
{
#endif

t_ecran_de_jeu create_ecran_de_jeu(int hauteur, int largeur, int posHerosColonne, int posHerosLigne);
void initMatrice(t_ecran_de_jeu matrice);
t_ecran_de_jeu chargementFichier(char* nomFichier, T_Heros heros);
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
