/*
 * backtrack.c
 * This file is part of Sudoku Scholar Project
 *
 * Copyright (C) 2012 - Maximilien Rigaut
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
#include "structures.h"
#include "tools.h"

/* ===========  Functions  =========== */

/** Si la g contient une solution l'ecrire dans gres */
int backtracking_resolution(GRILLE *g,GRILLE *gres){
	int pos,tf;
	
	GRILLE *g2=malloc(sizeof(GRILLE));
	CASE *C1,*Ctemp=malloc(sizeof(CASE)); TEST(Ctemp);
	/** La grille est elle resolue ? */
	if (test_is_empty(g)) {
		rewrite_grid(g,gres); return 1;
	}
	
	/** On essaye tous les candidats eventuels pour la case */
	for (pos=0;pos<DIM;pos+=1){
		g2=copy_grid(g); /** Copier la grille */
		
		C1=first_empty_case(g2);
		if (C1==NULL) return 0;
		
		tf=first_candidate(C1,pos);
		if (tf==DIM+1) return 0;
		
		remplit_case(C1,tf);
		
		/** Application des contraintes d'unicite 
		L'utilisation des contraintes d'unicite etendues apporte une gain de performances significatif (~60%)*/
		if (contrainte_unicite_grille(*g2) && check_grid(g2,C1))
			if (backtracking_resolution(g2,gres)) return 1;
		if (tf-1>pos) pos=tf-1;
		supprime_grille(*g2); 
	}
	return 0;
}

int backtracking_infos(GRILLE *g,GRILLE *gres,infos *nfo){
	int pos,tf;
	
	GRILLE *g2=malloc(sizeof(GRILLE));
	CASE *C1,*Ctemp=malloc(sizeof(CASE)); TEST(Ctemp);
	if (test_is_empty(g)) {
		rewrite_grid(g,gres);
		affiche_grille(*gres);
		nfo->nb_sols++;
		return 1;
	}
	
	for (pos=0;pos<DIM;pos+=1){
		g2=copy_grid(g);
		C1=first_empty_case(g2);
		if (C1==NULL) return 0;
		
		tf=first_candidate(C1,pos);

		if (tf==DIM+1) return 0;
		remplit_case(C1,tf);
		if (!nfo->nb_sols) nfo->depth++;
		if (contrainte_unicite_simple(*g2)) backtracking_infos(g2,gres,nfo);
		if (tf-1>pos) pos=tf-1;
		supprime_grille(*g2); 
	}
	return 0;
}

/** Teste si la grille est une feuille
 * Cad si elle est valable (et eventuellement finie)
 */
int test_is_empty(GRILLE *g){
	int i,j;
	for (i=0;i<DIM;i+=1) for (j=0;j<DIM;j+=1)
		if ((*g)[i][j]->nb_candidats>1) return 0;
	return 1;
}

/** Renvoie la premiere case vide de la grille */
CASE *first_empty_case(GRILLE *g){
	int i,j;
	for (i=0;i<DIM;i+=1)
		for (j=0;j<DIM;j+=1)
			if (!(*g)[i][j]->value) return (*g)[i][j];
	return NULL;
}

/** Renvoie la premiere case vide de la grille */
CASE *smaller_case(GRILLE *g){
	int i,j;
	int smaller=DIM+1;
	CASE *c=NULL;
	for (i=0;i<DIM;i+=1)
		for (j=0;j<DIM;j+=1)
			if (!(!(*g)[i][j]->value) && (*g)[i][j]->value<smaller) {
				smaller=(*g)[i][j]->value;
				c=(*g)[i][j];
			}
	if (!c) c=first_empty_case(g);
	return c;
}


/** Renvoie le premier candidat a partir de la position pos */
int first_candidate(CASE *c, int pos){
	int i;
	for (i=pos;i<DIM;i+=1) if (c->candidats[i]) return i+1;
	return DIM+1;
}

/** Verifie que la grille possede une solution */
int check_grid(GRILLE *g2,CASE *C1){
	int x,y,i,j,I,J,tf;
	x=C1->row;
	y=C1->col;
	tf=C1->value;
	I=(x/DIM_Region)*DIM_Region; J=(y/DIM_Region)*DIM_Region;
	
	for (i=0;i<DIM;i+=1)
		if ((i!=x && (*g2)[i][y]->value==tf) || (i!=y && (*g2)[x][i]->value==tf)) return 0;
		
	for (i=0;i<DIM_Region;i+=1) for (j=0;j<DIM_Region;j+=1)
		if ( (*g2)[i+I][j+J]->value==tf && (i+I!=x ||j+J!=y) ) return 0;
	
	return 1;
}
