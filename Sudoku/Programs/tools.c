/*
 * tools.c
 * This file is part of Sudoku Scholar Project
 *
 * Copyright (C) 2012 - Maximilien Rigaut & Charly Celereau
 *
 * Sudoku Scholar Project is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Sudoku Scholar Project is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */


/************* Includes *************/

#include <stdio.h>
#include <stdlib.h>
#include "tools.h"


/************** Defines *************/
/** Utils **/
#define PL printf("You are in function: %s - line: %d\n", __func__,__LINE__); /* (debug) Afficher des informations sur la ligne */
#define TEST(p) if ((p)==NULL) {PL; printf("\n	> NULL pointer error\n"); exit(EXIT_FAILURE);} /* Teste si le pointeur est non nul */
#define FAIL {printf("\nUnexpected Error\n"); PL; exit(EXIT_FAILURE);} /* (debug) Faire echouer le programme */

/** Test **/
#define PP(p) printf("Pile [%d] :",(p)->nb_cases);affiche_case((p)->cases[p->nb_cases-1]); /* Affiche la derniere valeur de la pile */

/** Shortcuts **/
#define ADD_PILE(p,c) (p)->cases[(p)->nb_cases++] = (c); /* Ajouter c dans la pile p */
#define GR(x,y) g[x][y] /* Tres utile pour eviter de dependre de l'implementation de la grille */

/************* Functions ************/

/* ================================================== */
/* ==============	 	Initialisation	 ============ */
/* ================================================== */

/* Initialisation d'une grille en remplissant les cases par 0 */
void init_grille(GRILLE g) {
	int i, j;
	CASE *c; /* Une grille d'addresses me parait plus pertinent */
	for(i = 0;i < DIM; i++)
		for(j = 0; j < DIM; j++){
				c=malloc(sizeof(CASE));TEST(c); /* On alloue l'emplacement memoire lie a la case */
				init_case(c,i,j); /* On initialise la case */
				GR(i,j) = c; /* On l'ajoute a la grille (GR est une macro) */
			}
}

void init_pile_case(GRILLE g, PILE_CASE *pile){
/* Parcours de la grille */
	int i, j;
	pile->nb_cases=0;
	for(i = 0; i < DIM; i++) for(j = 0; j < DIM; j++)
		/* Si la case est remplie : la mettre dans la pile */
		if(GR(i,j)->value != 0) pile->cases[pile->nb_cases++] = GR(i,j);
}

/* Initialisation d'une case, tous les chiffres sont candidats */
void init_case(CASE *c, int row, int col){
	int i;
	for (i=0;i<DIM;i++) c->candidats[i]=1;
	c->nb_candidats=DIM;
	c->value=0;
	c->row=row; c->col=col;
}

/* ================================================== */
/* ==============	 	Modifications	 ============ */
/* ================================================== */

/* Modifications des champs d'une case lorsqu'on y inscrit un chiffre */
void remplit_case(CASE *c, int chiffre){
	int j;
	/* Seul le chiffre est candidat */
	for (j=0;j<DIM;j++) c->candidats[j]=0;
	c->candidats[chiffre-1]=1;
	c->nb_candidats=1;
	c->value=chiffre;
}

int supprime_candidat(CASE *c,PILE_CASE *p,int candidat){
	int i;
	if (!c->candidats[candidat-1]) return 1; /* Si le nombre n'etait pas candidat, il n'est pas utile de le supprimer */
	c->candidats[candidat-1]=0;
	c->nb_candidats--;
	/* Si il ne reste plus qu'un seul candidat, le mettre dans la case */
	if (c->nb_candidats==1)
		for(i=0;i<DIM;i++) if (c->candidats[i]) {
			c->value=i+1;
			ADD_PILE(p,c); /* L'ajouter a la pile */
			return 1;
		}
	/* Erreur la grille n'as plus de solution */
	if (c->nb_candidats<1 && !c->value) return 0;
	return 1;
}

/* -------------------------------------------------- */
/* --------------	 	Contraintes	 	 ------------ */
/* -------------------------------------------------- */

/*
Contraine d'unicite:
    Un nombre ne peut etre present 
    qu'une et unique fois dans une 
    ligne colone et region
Unicite simple:
	On supprime les cases remplies des 
	candidats des cases des lignes,
	colones et regions concernes.
Unicite etendue:
	Si un nombre n'est candidat qu'a une 
	seule et unique place dans une ligne, 
	colone ou region, alors celui ci doit 
	necessairement plcace a cet emplacement.
*/

/* Contrainte d'unicite simple */
int contrainte_unicite(GRILLE g, PILE_CASE *p){
	while (p->nb_cases) if (!contrainte_unicite_case(g,p,p->cases[--p->nb_cases]))
		return 0; /* Si une seule erreur est produite, tout doit s'arreter */
	return 1;
}

/* Contrainte d'unicite etendue */
int contrainte_unicitheo(GRILLE g, PILE_CASE *p){
	int r=0;
	while (contrainte_theocycle_region(g,p) || contrainte_theocycle_ligne_colones(g,p))
		r=1; /* Une modification a ete effectue */
	return r;
}

/* Appliquer les contraintes d'unicite a la grille jusqu'a ce que
   celle ci soit declaree insoluble ou bien simplifiee au maximum. */
int contrainte_unicite_grille(GRILLE g){
	PILE_CASE Pile;
	init_pile_case(g, &Pile);
	while (contrainte_unicite(g,&Pile)) /* Tant que la grille est soluble, lui appliquer les deux contraintes d'unicite */
		if (!contrainte_unicitheo(g,&Pile)) return 1; /* Si aucun nombre n'as ete ajoute, s'arreter */
	return 0; /* La grille est insoluble */
}

/* Applique les contraintes de la case, sur sa colonne et sa ligne */
int contrainte_unicite_ligne_colone_case(GRILLE g, PILE_CASE *p, CASE *c){
	int i;
	for (i=0; i<DIM; i++) {
		if (i!=c->row) if (!supprime_candidat(GR(i,c->col),p,c->value)) return 0; /* La grille ne contient aucune solution */
		if (i!=c->col) if (!supprime_candidat(GR(c->row,i),p,c->value)) return 0; /* /!\ Arret immediat */
	}
	return 1;
}

/* Applique les contraintes de la case, sur sa region */
int contrainte_unicite_region_case(GRILLE g, PILE_CASE *p, CASE *c){
	int x,y, i,j;
	x=(c->row/DIM_Region)*DIM_Region;
	y=(c->col/DIM_Region)*DIM_Region;

	for (i=0; i<DIM_Region; i++) for (j=0; j<DIM_Region; j++)
		if ((x+i) != c->row || (y+j) != c->col) /* Inutile d'essayer de se supprimer */
			if (!supprime_candidat(GR(x+i,y+j),p,c->value)) return 0;
	return 1;
}

/* Applique toutes les contraintes d'unicite simple associees a la case (ligne + colonne) */
int contrainte_unicite_case(GRILLE g, PILE_CASE *p, CASE *c){
	/* Si une seule erreur est produite, tout doit s'arreter */
	return contrainte_unicite_ligne_colone_case(g,p,c) && contrainte_unicite_region_case(g,p,c);
}

/* Appliquer les contraintes d'unicite etendue sur les lignes et colones de la grille */
int contrainte_theocycle_ligne_colones(GRILLE g, PILE_CASE *p){
	int i,j,add_p=0;
	CASE* table[DIM],*table_2[DIM];
	for (i=0;i<DIM;i++){
		for (j=0;j<DIM;j++){
			table[j]=GR(i,j); /* Ligne de cases */
			table_2[j]=GR(j,i); /* Colone de cases */
		}
		add_p|=theocycle_table(table,p)|theocycle_table(table_2,p); /* On note si la pile a etee changee ou non */
	}
	return add_p;
}
/* Appliquer les contraintes d'unicite etendue sur chaque region de la grille */
int contrainte_theocycle_region(GRILLE g, PILE_CASE *p){
	int x,y, i,j,k,l, add_p=0;
	CASE * table[DIM];
	
	for (i=0; i<DIM_Region; i++) for (j=0; j<DIM_Region; j++){ /* Pour chaque region de la grille */
		for (k=0;k<DIM_Region; k++) for (l=0;l<DIM_Region;l++){ /* On ajoute au tableau les cases de la region */
			x=i*DIM_Region+k; y=j*DIM_Region+l;
			table[k+DIM_Region*l]=GR(x,y);
		}
		add_p|=theocycle_table(table,p); /* On note si la pile a etee changee */
	}
	return add_p;
}

/* Dans le tableau si un candidat n'as qu'une place ou aller, alors l'unicite nous dit qu'il se doit d'etre a cette place */
int theocycle_table(CASE * table[DIM],PILE_CASE *p){
	int i,j,nb,add_p=0;
	CASE *r;
	
	for (i=0;i<DIM;i++){ /* Pour chaque candidat 1...DIM */
		nb=0;
		/* Pour chaque case du tableau, si le nombre est candidat, verifier son unicite*/
		for (j=0;j<DIM;j++) if (table[j]->candidats[i]){
			if (nb++) break; /* Inutile de continuer, plusieurs places sont possibles */
			r=table[j]; /* Le nombre est candidat */
		}
		if (nb==1 && !r->value) { /* Le candidat est uniquement present dans cette case, l'ajouter */
			remplit_case(r,i+1);
			ADD_PILE(p,r); add_p=1; /* Des modifications ont etes effectues, la pile est modifiee */
		}
	}
	return add_p;
}

/* ================================================== */
/* ==============		 Calculs		 ============ */
/* ================================================== */

double total_candidats(GRILLE g){
	int i,j;
	double r=1;
	for (i=0;i<DIM; i++) for (j=0;j<DIM;j++) /* Pour tous les elements de la grille */
		r*=GR(i,j)->nb_candidats; /* On fait le produit de leur candidats */
	return r;
}

/* ================================================== */
/* ==============	 	Affichage		============= */
/* ================================================== */

/* Affiche une variable de type GRILLE */
void affiche_grille(GRILLE grille){
	int i,j;
	printf("\n"); for (j=0;j<GBSIZE;j++) printf("-"); printf("\n");
	for (i=0;i<DIM;i++){ 
		printf("| ");
		for (j=0;j<DIM; j++){ printf("%d ",grille[i][j]->value); if ((j+1)%3==0) printf("| "); }
		if ((i+1)%DIM_Region==0) { printf("\n"); for (j=0;j<GBSIZE;j++) printf("-"); }
		printf("\n");
	}
	printf("\n");
}

/* Affiche les candidats d'une GRILLE */
void affiche_grille_candidats(GRILLE grille){
	int i,j;
	printf("\n"); for (j=0;j<GBSIZE;j++) printf("-"); printf("\n");
	for (i=0;i<DIM;i++){ 
		printf("| ");
		for (j=0;j<DIM; j++){ printf("%d ",grille[i][j]->nb_candidats); if ((j+1)%3==0) printf("| "); }
		if ((i+1)%DIM_Region==0) { printf("\n"); for (j=0;j<GBSIZE;j++) printf("-"); }
		printf("\n");
	}
	printf("\n");
}

/* Affiche une variable de type CASE */
void affiche_case(CASE *c){
	int i;
	printf("Case (%d,%d): (%d %s) : ",c->row, c->col, c->nb_candidats,c->nb_candidats>1?"candidats":"candidat");
	for (i=0;i<DIM;i++)	if (c->candidats[i]==1) printf("%d ",i+1);
	printf("[%d]\n",c->value);
}

/* Affiche une variable de type PILE_CASE */
void affiche_pile(PILE_CASE *p){
	int i; 
	printf("Pile [%d] :\n",p->nb_cases); 
	for (i=0; i<p->nb_cases; i++) {
		printf("    > "); affiche_case((p)->cases[i]);
	}
	
}
/* ================================================== */
/* ==============	 	Gestion I/O	 	============= */
/* ================================================== */

/* Saisie d'une grille a partir d'un fichier */
/* Les "chiffres" peuvent etre > 9 mais doivent etre separes par un (ou plusieurs) espace */
void saisie_grille(GRILLE g, char *adr){
	int i,j,val;
	FILE *f=fopen(adr,"r");
	for (i=0;i<DIM;i++) for (j=0;j< DIM;j++){ /* Pour chaque element de la grille */
		fscanf(f,"%d",&val); 
		if (val) remplit_case(GR(i,j),val); /* On lui ajoute la valeur lue dans le fichier */
	}
	fclose(f);
}

/* ================================================== */
/* ==============		 	Test		 ============ */
/* ================================================== */
/* (debug) Test basique de conformite de la grille, peut etre ammene a evoluer dans le futur */
void test_norm(GRILLE g){
	int i, j, r=1;
	for (i=0;i<DIM;i++)
		for (j=0;j<DIM;j++){
			if (!test_case(GR(i,j))) {r=0; affiche_case(GR(i,j));}
			if (GR(i,j)->row!=i || GR(i,j)->col!=j) {r=0; affiche_case(GR(i,j));}
		}
	printf("%s\n",r?"Grille conforme":"Grille malformee");		
}

/* (debug) Test de conformite de case */
int test_case(CASE *c){
	return !(c->col>DIM||c->col<0||c->row<0||c->row>DIM||c->nb_candidats<0||c->nb_candidats>DIM);
}
