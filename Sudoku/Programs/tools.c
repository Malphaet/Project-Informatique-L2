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
#define PL printf("You are in function: %s - line: %d\n", __func__,__LINE__);

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

int supprime_candidat(CASE *c,int candidat){
	int i;
	if (!c->candidats[candidat-1]) return 0;
	c->candidats[candidat-1]=0;
	c->nb_candidats--;
	printf("%d - ",c->nb_candidats);
	if (c->nb_candidats==1) for(i=0;i<DIM;i++) if (c->candidats[i]) {c->value=i+1; PL;}
	else if (!c->nb_candidats) c->value=0;

	return 1;
}

/* -------------------------------------------------- */
/* --------------       Contraintes      ------------ */
/* -------------------------------------------------- */

/* Applique les contraintes de la case, sur la ligne */
int contrainte_unicite_ligne_case(GRILLE g, PILE_CASE *p, CASE *c){
	int i=0;
	
	while (i<DIM) 
		if (i++!=c->col-1){
			if (supprime_candidat(&g[c->row][i],c->value))  p->cases[p->nb_cases++] = c;
			else return 0; /* /!\ Arret immediat */
		}
	return 1;
}

/* Applique les contraintes de la case, sur la colonne */
int contrainte_unicite_colone_case(GRILLE g, PILE_CASE *p, CASE *c){
	int i=0;
	
	while (i<DIM) 
		if (i++!=c->row){
			if (supprime_candidat(&g[i][c->col],c->value))  p->cases[p->nb_cases++] = c;
			else return 0;
		}
	return 1;
}

int contrainte_unicite_region_case(GRILLE g, PILE_CASE *p, CASE *c){
	int x,y, i,j;
	
	x=(c->col/DIM_Region)*DIM_Region;
	y=(c->row/DIM_Region)*DIM_Region;

	for (i=0; i<DIM_Region; i++)
		for (j=0; j<DIM_Region; j++)
			if ((x+i) != c->row || (y+j) != c->col){ /* Inutile d'essayer de se supprimer */
				if (supprime_candidat(&g[x+i][y+j],c->value)) p->cases[p->nb_cases++] = c;
				else return 0; /* /!\ Arret immediat */
			}
	return 1;
}

/* Applique toutes les contraintes associees a la case (ligne + colonne) */
int contrainte_unicite_case(GRILLE g, PILE_CASE *p, CASE *c){
	
	contrainte_unicite_colone_case(g,p,c);
	contrainte_unicite_ligne_case(g,p,c);
	contrainte_unicite_region_case(g,p,c);
	
	return 1;
}

int contrainte_unicite(GRILLE g, PILE_CASE *p){
	while (p->nb_cases){
		if (!contrainte_unicite_case(g,p,p->cases[p->nb_cases---1])) return 0;
	}
	return 1;	
}

int contrainte_unicite_grille(GRILLE g){
	PILE_CASE Pile;
	init_pile_case(g, &Pile);
	
	return contrainte_unicite(g,&Pile);
}
/* ================================================== */
/* ==============        Calculs         ============ */
/* ================================================== */

double total_candidats(GRILLE g){
	int i,j;
	double r=1;
	for (i=0;i<DIM; i++)
		for (j=0;j<DIM;j++)
			r*=g[i][j].nb_candidats;
	return r;
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
		if ((i+1)%DIM_Region==0) { printf("\n"); for (j=0;j<GBSIZE;j++) printf("-"); }
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
	printf("\nCase remplie : %s",!c.value?"NON":"OUI");
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
				if (val) remplit_case(&g[i][j],val);
			}
	}
	fclose(f);
}

