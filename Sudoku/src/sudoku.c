/*
 * sudoku.c
 * This file is part of Sudoku Scholar Project
 *
 * Copyright (C) 2012 - Maximilien Rigaut & Chary Celereau
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

/* ============  Includes  =========== */

#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

/* ===========  Defines  =========== */

/* ==============  Main  =========== */

int main(void)
{
	char path[]="./data/grilleC.txt";
	int *nb_sols=malloc(sizeof(int));
	GRILLE grille,gres;
	
	/*PILE_CASE Pile;*/
	init_grille(grille); init_grille(gres);
	saisie_grille(grille,path);
	
	/*init_pile_case(grille, &Pile);*/
	affiche_grille(grille);
	/*affiche_grille_candidats(grille);*/
	
	/*printf("%f\n",total_candidats(grille));*/
	contrainte_unicite_simple(grille);
	/* contrainte_unicite_grille(grille); */
	
	printf("%f\n",total_candidats(grille));
	
	
	backtracking_resolution(&grille,&gres,nb_sols);
	
	affiche_grille(grille);
	affiche_grille(gres);
	
	affiche_grille_candidats(gres);
	return 0;
}
