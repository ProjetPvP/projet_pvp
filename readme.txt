pour ajouter un élément de décor : 

Dans matrice.h : 

extern SDL_Surface * nomElement
SDL_Rect positionNomElement;


dans matrice.c : 

SDL_Surface * nomElement = NULL;


dans remplissageMap(), rajouter : 

if(matrice->ecran[i][j] == 'initialeElement[en majuscule]')
{
           positionNomElement.x = j;
           positionNomElement.y = i;
           SDL_BlitSurface(nomElement, NULL, ecran, &positionNomElement);
}







void ajoutHitbox(T_ListePosition liste, SDL_Rect position, t_ecran_de_jeu matrice, int hauteur, int largeur, char c)
{
            int cpt;
            while(liste->suiv != NULL)
            {
                  liste = liste->suiv;
            }
            cpt = liste->numero;
            while(liste->prec != NULL)
            {
                  liste = liste->prec;
            }
      for(int numeroObjet = 0; numeroObjet<cpt; numeroObjet++)
            {
                  position.x = liste->position.x;
                  position.y = liste->position.y;
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