/*
 * rules.c
 * This file is part of Sudocu Scholar Project
 *
 * Copyright (C) 2012 - Maximilien Rigaut
 *
 * Sudocu Scholar Project is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Sudocu Scholar Project is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

/* ===========  Includes  =========== */

#include <stdio.h>
#include <stdlib.h>
#include "tools.h"
#include "structures.h"

/* ===========  Functions  =========== */

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

/** Contrainte d'unicite etendue */
int contrainte_unicitheo(GRILLE g, PILE_CASE *p){
	int r=0;
	while (contrainte_theocycle_region(g,p) || contrainte_theocycle_ligne_colones(g,p))
		r=1; /* Une modification a ete effectue */
	return r;
}

/** Appliquer les contraintes d'unicite etendue sur les lignes et colones de la grille */
int contrainte_theocycle_ligne_colones(GRILLE g, PILE_CASE *p){
	int i,j,add_p=0;
	CASE* table[DIM],*table_2[DIM];
	for (i=0;i<DIM;i++){
		for (j=0;j<DIM;j++){
			table[j]=GR(i,j); /** Ligne de cases */
			table_2[j]=GR(j,i); /** Colone de cases */
		}
		add_p|=theocycle_table(table,p)|theocycle_table(table_2,p); /* On note si la pile a ete changee ou non */
	}
	return add_p;
}
/** Appliquer les contraintes d'unicite etendue sur chaque region de la grille */
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

/** Dans le tableau si un candidat n'as qu'une place ou aller, alors l'unicite nous dit qu'il se doit d'etre a cette place */
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
			curr_regle=candidat_unique;
			case_added(r->row,r->col,r->value,1,candidat_unique);
			ADD_PILE(p,r); add_p=1; /* Des modifications ont etes effectues, la pile est modifiee */
		}
	}
	return add_p;
}
