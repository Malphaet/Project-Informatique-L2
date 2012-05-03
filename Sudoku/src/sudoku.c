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

int main(int nbargs,char **kwargs){
	char *path;
	GRILLE grille,gres;
	infos nfo={0,0};
	
	if (nbargs<2){
		printf("Le nombre d'arguments est incorrect\n Usage: Backtrack <grille>\n");
		exit(EXIT_FAILURE);
	}

	path=kwargs[1];
	init_grille(grille);
	saisie_grille(grille,path);

	affiche_grille(grille);
	
	
	printf("%f\n",total_candidats(grille));
	contrainte_unicite_grille(grille);
	printf("%f\n",total_candidats(grille));
	
	init_grille(gres);
	
	backtracking_resolution(&grille,&gres);
	
	affiche_grille(grille);
	/*affiche_grille(gres);*/
	affiche_grille_candidats(grille);
	/*affiche_grille_candidats(gres);*/
	if (0) {
		init_grille(gres); init_grille(grille); saisie_grille(grille,path);
		printf("Infos complementaires :\n");
		backtracking_infos(&grille,&gres,&nfo);
		printf("Nb solutions : %d\n",nfo.nb_sols);
		printf("Nb nodes explorees : %d\n",nfo.depth);
	}
	
	return 0;
}
