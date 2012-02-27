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

/************* Includes *************/

#include <stdio.h>
#include "structures.h"

/************** Defines *************/

/*************** Main **************/

int main(void)
{
	char path[]="../Data/grille2.txt";
	
	GRILLE grille;
	PILE_CASE Pile;
	init_grille(grille);
	saisie_grille(grille,path);
	init_pile_case(grille, &Pile);
	affiche_grille(grille);
	affiche_grille_candidats(grille);
	/* affiche_case(grille[0][2]); */
	
	/*
	i=0; while (i<DIM) affiche_case(grille[1][i++]);
	contrainte_unicite_ligne_case(grille, &Pile, &grille[1][1]);
	i=0; while (i<DIM) affiche_case(grille[1][i++]);
	*/
	printf("%f\n",total_candidats(grille));
	contrainte_unicite_grille(grille);
	printf("%f\n",total_candidats(grille));
	affiche_grille(grille);
	affiche_grille_candidats(grille);
	return 0;
}
