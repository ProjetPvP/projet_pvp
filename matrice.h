#include <stdlib.h>
#include <SDL/SDL.h>
#include <stdbool.h>
#define HAUTEUR 400
#define LARGEUR 600
#define LARGEURHEROSPIXEL 34
#define HAUTEURHEROSPIXEL 34
#define LARGEURMINE 20

enum {
      HAUT,
      BAS,
      GAUCHE,
      DROITE};
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

SDL_Event event;
SDL_Surface * ecran = NULL;
SDL_Surface * Heros = NULL;
SDL_Surface * myMap = NULL;
SDL_Surface * mine = NULL;
SDL_Surface * barreVie = NULL;

SDL_Rect positionHeros;
SDL_Rect positionMap;
SDL_Rect positionMine;
SDL_Rect positionBarreVie;

t_ecran_de_jeu create_ecran_de_jeu(int hauteur, int largeur, int posHerosColonne, int posHerosLigne);
void initMatrice(t_ecran_de_jeu matrice);
void LectureMatrice(t_ecran_de_jeu matrice, SDL_Surface* ecran, SDL_Surface *  barreVie);
bool takedamage(t_ecran_de_jeu matrice, int direction, t_pos positionHeros, int deplacement, char c);
int verificationDeplacementHitbox(t_ecran_de_jeu matrice, t_pos pos, int largeur, int hauteur, int direction, int deplacement);
bool verifierPoussee(t_ecran_de_jeu matrice, int direction, t_pos positionHeros, int deplacement);
void replacementHeros(t_ecran_de_jeu matrice, int direction, int nb);


