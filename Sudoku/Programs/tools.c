/*----------------------------------*/
/*		Sudoku Scholar Project		*/
/*----------------------------------*/
/*		Copyleft Maximilien Rigaut	*/
/*				 Charly Celereau	*/
/*----------------------------------*/
/*		Date : 	 	10/02/12		*/
/*----------------------------------*/

/************* Includes *************/

#include <stdio.h>
#include "tools.h"


/************** Defines *************/

/************* Functions ************/

/* Initialisation d'une grille en remplissant les cases par 0 */
void init_grille(GRILLE Grille)
{
	int i, j;
	for(i = 0;i < DIM; i++)
		for(j = 0; j < DIM; j++)
				Grille[i][j] = 0;
}

/* Affiche une variable de type GRILLE */
void affiche_grille(GRILLE Grille)
{
	int i, j;
	for(i = 0;i < DIM; i++)
	{
		printf("||");
		for(j = 0; j < DIM; j++)
			printf (" %d |", Grille[i][j]);
		printf("| \n");
	}
}

/* Saisie d'une grille à partir d'un fichier */
/* Les "chiffres" peuvent etre > 9 mais doivent etre separes par un (ou plusieurs) espace */
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

/* Initialisation d'une case, tous les chiffres sont candidats */
void init_case(CASE *c, int row, int col)
{
	int i;
	for (i=0;i<DIM;i++)
		c->candidats[i]=1;
	c->nb_candidats=DIM;
	c->value=0;
	c->row = row;
	c->col = col;
}

/* Affichage structure des elements d'une case. */
void affiche_case(CASE c)
{
	int i;
	printf("Nombre de candidats : %d\n",c.nb_candidats);
	printf("Candidats : ");
	for (i=0;i<DIM;i++)
		if (c.candidats[i]==1)
			printf("%d ",i+1);
	printf("\nCase remplie : %s",c.value==0?"NON":"OUI");
	printf("\n");
	printf("Cordonnees : Ligne %d, Colonne %d", c.row, c.col);
}


/* Modifications des champs d'une case lorsqu'on y inscrit un chiffre */
void remplit_case(CASE *c, int chiffre)
{
	int j;
	/* Seul le chiffre est candidat */
	for (j=0;j<DIM;j++) c->candidats[j]=0;
	c->candidats[chiffre-1]=1;
	c->nb_candidats=1;
	c->value=chiffre;
}

	