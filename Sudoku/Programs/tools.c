/*----------------------------------*/
/*  Sudoku Scholar Project          */
/*----------------------------------*/
/*  Copyleft Maximilien Rigaut      */
/*           Charly Celereau        */
/*----------------------------------*/
/*  Date : 10/02/12                 */
/*----------------------------------*/

/************* Includes *************/

#include <stdio.h>
#include "tools.h"


/************** Defines *************/
#define TEST(p) if ((p)==NULL) {printf("Error in file %s.\n    > function:%s - line:%d\n    > NULL pointer error\n",__FILE__, __func__,__LINE__); exit(EXIT_FAILURE);} 

/************* Functions ************/

/* ================================================== */
/* ==============     Initialisation     ============ */
/* ================================================== */

/* Initialisation d'une grille en remplissant les cases par 0 */
void init_grille(GRILLE Grille)
{
	int i, j;
	CASE c;
	for(i = 0;i < DIM; i++)
		for(j = 0; j < DIM; j++)
			{
				init_case(&c,i,j);
				Grille[i][j] = c;
			}
}

void init_pile_case(GRILLE g, PILE_CASE *pile)
{
/* Parcours de la grille */
	int i, j;
	pile->nb_cases=0;
	for(i = 0; i < DIM; i++)
		for(j = 0; j < DIM; j++)
		/* Si la case est remplie : la mettre dans la pile */
			if(g[i][j].value != 0)
				pile->cases[pile->nb_cases++] = &g[i][j];
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

/* ================================================== */
/* ==============     Modifications      ============ */
/* ================================================== */

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

/* ================================================== */
/* ==============       Affichage        ============ */
/* ================================================== */

/* Affiche une variable de type GRILLE */
void affiche_grille(GRILLE grille){
	int i,j;
	printf("\n"); for (j=0;j<GBSIZE;j++) printf("-"); printf("\n");
	for (i=0;i<DIM;i++){ 
		printf("| ");
		for (j=0;j<DIM; j++){ printf("%d ",grille[i][j].value); if ((j+1)%3==0) printf("| "); }
		if ((i+1)%3==0) { printf("\n"); for (j=0;j<GBSIZE;j++) printf("-"); }
		printf("\n");
	}
	printf("\n");
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
	printf("Cordonnees : Ligne %d, Colonne %d\n", c.row, c.col);
}

/* ================================================== */
/* ==============      Gestion I/O       ============ */
/* ================================================== */

/* Saisie d'une grille a partir d'un fichier */
/* Les "chiffres" peuvent etre > 9 mais doivent etre separes par un (ou plusieurs) espace */
void saisie_grille(GRILLE g, char *adr)
{
	int i,j,val;
	FILE *f;
	f=fopen(adr,"r");
	for (i=0;i<DIM;i++){
		for (j=0;j< DIM;j++)
			{
				fscanf(f,"%d",&val);
				remplit_case(&g[i][j],val);
			}
	}
	fclose(f);
}

