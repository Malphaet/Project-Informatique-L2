/***********************************************************************
 *        TP 2 : Organisation et programmation des contraintes         *
 ***********************************************************************/

#include <stdio.h>
#include <stdlib.h> 

#define DIM 9


/************************* Types Definitions **************************/

typedef int GRILLE[DIM][DIM];

typedef struct CASE
{
	int candidats[DIM];
	int nb_candidats;
	int chiffre;
	int row; // Ligne d'une case dans une grille
	int col; // Colonne d'une case dans une grille
} CASE


/***************************** Functions ******************************/

/* Ex. 2 : Initialisation d'une grille en remplissant les cases par 0 */
void init_grille(GRILLE Grille)
{
	int i, j;
	for(i = 0;  i < DIM; i++)
	{
		for(j = 0; j < DIM; j++)
		{
				Grille[i][j] = 0;
		}
	}	
}

/* Ex. 3 : Affiche une variable de type GRILLE */
void affiche_grille(GRILLE Grille)
{
	int i, j;
	for(i = 0;  i < DIM; i++)
	{
		printf("||");
		for(j = 0; j < DIM; j++)
		{
			printf (" %d |", Grille[i][j]);
		}
		printf("| \n");
	}
}

/* Ex. 5 : Saisie d'une grille à partir d'un fichier */
/* Les "chiffres" peuvent être > 9 mais doivent être séparés par un (ou plusieurs) espace */
void saisie_grille(GRILLE g, char *adr)
{
  int i,j;
  FILE *f;
  f=fopen(adr,"r");
  for (i=0;i<DIM;i++){
    for (j=0;j< DIM;j++)
      fscanf(f,"%d",&g[i][j]);
  }
  fclose(f);
}

/* Ex. 7 : Initialisation d'une case, tous les chiffres sont candidats */
void init_case(CASE *c, int r, int c){
  int i;
  for (i=0;i<DIM;i++)
    c->chiffres[i]=1;
  c->nb_candidats=DIM;
  c->chiffre=0;
  c->row = r;
  c->col = c;
}

/* Ex. 8 : Affichage structuré des éléments d'une case. */
void affiche_case(CASE c){
  int i;
  printf("Nombre de candidats : %d\n",c.nb_candidats);
  printf("Candidats : ");
  for (i=0;i<DIM;i++)
    if (c.chiffres[i]==1)
      printf("%d ",i+1);
  printf("\nCase remplie : %s",c.chiffre==0?"NON":"OUI");
  printf("\n");
  printf("Cordonnees : Ligne %d, Colonne %d", c.row, c.col);
}


/* Ex. 9 : Modifications des champs d'une case lorsqu'on y inscrit un chiffre */
void remplit_case(CASE *c, int chiffre){
  int j;
  for (j=0;j<DIM;j++)
    c->chiffres[j]=0; // plus de candidats ...
  c->chiffres[chiffre-1]=1; // ... sauf le chiffre lui même
  c->nb_candidats=1;
  c->chiffre=chiffre;
}

int main(void){
  GRILLE grille;
  CASE c;
  /* init_grille(grille); */
  /* affiche_grille(grille); */
  /* saisie_grille_clavier(grille);  */
  /* affiche_grille(grille); */
  /* saisie_grille_clavier_bis(grille);  */
  /* affiche_grille(grille); */
  saisie_grille(grille,"../donnees/grille1");
  affiche_grille(grille);
  init_case(&c);
  affiche_case(c);
  remplit_case(&c,3);
  affiche_case(c);
  return 0;