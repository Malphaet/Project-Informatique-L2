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


/* ===========  Includes  =========== */

#include <stdio.h>
#include <stdlib.h>
#include "tools.h"

/* ===========  Functions  =========== */

/* ================================================== */
/* ==============	 	Initialisation	 ============ */
/* ================================================== */

/** Initialisation d'une grille en remplissant les cases par 0 */
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

/** Initialise la pile de case fournie avec les valeurs de la grille */
void init_pile_case(GRILLE g, PILE_CASE *pile){
	/* Parcours de la grille */
	int i, j;
	pile->nb_cases=0;
	for(i = 0; i < DIM; i++) for(j = 0; j < DIM; j++)
		/* Si la case est remplie : la mettre dans la pile */
		if(GR(i,j)->value != 0) pile->cases[pile->nb_cases++] = GR(i,j);
}

/** Initialisation d'une case, tous les chiffres sont candidats */
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

/** Modifications des champs d'une case lorsqu'on y inscrit un chiffre */
void remplit_case(CASE *c, int chiffre){
	int j;
	/* Seul le chiffre est candidat */
	for (j=0;j<DIM;j++) c->candidats[j]=0;
	c->candidats[chiffre-1]=1;
	c->nb_candidats=1;
	c->value=chiffre;
}

/** Supprime un candidant de la c, l'ajoute sur la pile en cas de succes
 * Si la grille ne possede plus de solutions suite a l'operation,
 * la fonction renvoie 0 sinon 1.
 */
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

/** Renvoie une copie du contenu d'une case */
CASE *copy_case(CASE *c){
	int i;
	CASE *c2=malloc(sizeof(CASE));
	init_case(c2,c->row,c->col);
	c2->value=c->value;
	c2->nb_candidats=c->nb_candidats;
	for (i=0;i<DIM;i+=1) c2->candidats[i]=c->candidats[i];
	return c2;
}

/** Renvoie la copie carbone d'une grille */
GRILLE *copy_grid(GRILLE *grille){
	GRILLE *grille2=malloc(sizeof(GRILLE)); TEST(grille2);
	init_grille(*grille2);
	rewrite_grid(grille,grille2);
	return grille2;
}

/** Ecris le contenu de la premiere grille dans la seconde grille */
void rewrite_grid(GRILLE *grille_s,GRILLE *grille_d){
	int i,j;
	for (i=0;i<DIM;i+=1) for (j=0;j<DIM;j+=1)
		(*grille_d)[i][j]=copy_case((*grille_s)[i][j]);
}
/* -------------------------------------------------- */
/* --------------	 	Contraintes	 	 ------------ */
/* -------------------------------------------------- */

/**
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

/** Contrainte d'unicite simple */
int contrainte_unicite(GRILLE g, PILE_CASE *p){
	while (p->nb_cases) if (!contrainte_unicite_case(g,p,p->cases[--p->nb_cases]))
		return 0; /* Si une seule erreur est produite, tout doit s'arreter */
	return 1;
}

/** Appliquer les contraintes d'unicite a la grille jusqu'a ce que
 * celle ci soit declaree insoluble ou bien simplifiee au maximum. */
int contrainte_unicite_grille(GRILLE g){
	PILE_CASE Pile;
	init_pile_case(g, &Pile);
	while (contrainte_unicite(g,&Pile)) /* Tant que la grille est soluble, lui appliquer les deux contraintes d'unicite */
		if (!contrainte_unicitheo(g,&Pile)) return 1; /* Si aucun nombre n'as ete ajoute, s'arreter */
	return 0; /* La grille est insoluble */
}

/** Applique les contraintes de la case, sur sa colonne et sa ligne */
int contrainte_unicite_ligne_colone_case(GRILLE g, PILE_CASE *p, CASE *c){
	int i;
	for (i=0; i<DIM; i++) {
		if (i!=c->row) if (!supprime_candidat(GR(i,c->col),p,c->value)) return 0; /* La grille ne contient aucune solution */
		if (i!=c->col) if (!supprime_candidat(GR(c->row,i),p,c->value)) return 0; /* /!\ Arret immediat */
	}
	return 1;
}

/** Applique les contraintes de la case, sur sa region */
int contrainte_unicite_region_case(GRILLE g, PILE_CASE *p, CASE *c){
	int x,y, i,j;
	x=(c->row/DIM_Region)*DIM_Region;
	y=(c->col/DIM_Region)*DIM_Region;

	for (i=0; i<DIM_Region; i++) for (j=0; j<DIM_Region; j++)
		if ((x+i) != c->row || (y+j) != c->col) /* Inutile d'essayer de se supprimer */
			if (!supprime_candidat(GR(x+i,y+j),p,c->value)) return 0;
	return 1;
}

/** Applique toutes les contraintes d'unicite simple associees a la case (ligne + colonne) */
int contrainte_unicite_case(GRILLE g, PILE_CASE *p, CASE *c){
	/* Si une seule erreur est produite, tout doit s'arreter */
	return contrainte_unicite_ligne_colone_case(g,p,c) && contrainte_unicite_region_case(g,p,c);
}


/* ================================================== */
/* ==============		 Calculs		 ============ */
/* ================================================== */

/** Calcule le nombre total de combinaisons possibles pour la grille
 * (Ce qui est combinatoire, les candidats d'une case influants sur la suivante autre)
 */
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

/** Affiche une variable de type GRILLE */
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

/** Affiche les candidats d'une GRILLE */
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

/** Affiche une variable de type CASE */
void affiche_case(CASE *c){
	int i;
	printf("Case (%d,%d): (%d %s) : ",c->row, c->col, c->nb_candidats,c->nb_candidats>1?"candidats":"candidat");
	for (i=0;i<DIM;i++)	if (c->candidats[i]==1) printf("%d ",i+1);
	printf("[%d]\n",c->value);
}

/** Affiche une variable de type PILE_CASE */
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

/** Saisie d'une grille a partir d'un fichier
 * Les "chiffres" peuvent etre > 9 mais doivent etre separes par un (ou plusieurs) espace(s) */
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
