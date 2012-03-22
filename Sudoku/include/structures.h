/*
 * structures.h
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

#ifndef __STRUCTURES__
#define __STRUCTURES__

/* ============ Includes  =========== */
#include "constants.h"

/* ============ Typedef  =========== */

/** Structure d'une case */
typedef struct CASE
{
	int candidats[DIM]; /** Nombres candidats pour la resolution de la case */
	int nb_candidats; /** Nombre de candidats potentiels */
	int value; /** Valeur de la case : 0 si non resolue; la valeur adaptee sinon */
	/** Position de la case dans la grille (ligne, colone) */
	int row;
	int col;
} CASE;

/* Pile de cases */
typedef struct
{
	CASE* cases[DIM*DIM]; /* Au plus, on aura DIM*DIM cases dans la pile */
	int nb_cases; /* Nombre d'elements dans de la pile */
} PILE_CASE;

/* Grille de Sudoku */
typedef CASE* GRILLE[DIM][DIM];

/* ============ Prototype  =========== */

/* = Fonctions d'initialisation = */
void init_case(CASE *, int, int);									/* Tested */
void init_pile_case(GRILLE, PILE_CASE *);							/* Tested */
void init_grille(GRILLE);											/* Tested */

/* = Fonctions de saisie = */
void saisie_grille(GRILLE, char *);									/* Tested */
void remplit_case(CASE *, int);										/* Tested */
CASE *copy_case(CASE *);											/* In-dev */
GRILLE *copy_grid(GRILLE*);
void rewrite_grid(GRILLE *,GRILLE *);

/* = Fonctions de contraintes = */
int supprime_candidat(CASE *,PILE_CASE *,int);						/* Seems Working */
int contrainte_unicite_grille(GRILLE);								/* Seems Working */

/* === Unicite simple === */
int contrainte_unicite_ligne_colone_case(GRILLE,PILE_CASE*,CASE*);	/* Seems Working */
int contrainte_unicite_case(GRILLE, PILE_CASE *, CASE *);			/* Seems Working */
int contrainte_unicite(GRILLE, PILE_CASE *);						/* Seems Working */

/* === Unicite etendue === */
int theocycle_table(CASE * table[DIM],PILE_CASE*);					/* Seems Working */
int contrainte_theocycle_ligne_colones(GRILLE, PILE_CASE *);		/* Seems Working */
int contrainte_theocycle_region(GRILLE,PILE_CASE *);				/* Seems Working */
int contrainte_unicitheo(GRILLE, PILE_CASE *);

/* === Backtracking === */
int backtracking_resolution(GRILLE *,GRILLE *);
int test_is_empty(GRILLE *);
int test_is_solution(GRILLE *);
int first_candidate(CASE *, int);
CASE *first_empty_case(GRILLE *);
int check_grid(GRILLE *g2,CASE *C1);

/* Tools */
double total_candidats(GRILLE);										/* Seems Working */

/* = Fonctions d'affichage = */
void affiche_pile(PILE_CASE *);										/* Tested */
void affiche_case(CASE *);											/* Tested */
void affiche_grille(GRILLE);										/* Tested */
void affiche_grille_candidats(GRILLE);								/* Tested */

/* = Fonctions de test = */
void test_norm(GRILLE);												/* Tested */
int test_case(CASE *);												/* Tested */

#endif
