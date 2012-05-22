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
	HISTORIQUE current;
	
	int v;
	
	
	if (nbargs<2){
		printf("Le nombre d'arguments est incorrect\n Usage: sudoku <grille>\n");
		exit(EXIT_FAILURE);
	}

	path=kwargs[1];
	init_grille(grille);
	init_historique(&historique);
	init_historique(&parametres);
	saisie_grille(grille,path);

	affiche_grille(grille);
	
	
	/*printf("%f\n",total_candidats(grille));*/
	contrainte_unicite_grille(grille);
	/*printf("%f\n",total_candidats(grille));*/
	
	affiche_grille(grille);
	
	current=historique.suivant;
	printf("Verbosity (0: None / 1: All) :");
	scanf("%d",&v);
	while (current!=NULL){
		print_element(current,v);
		current=current->suivant;
	}
	
	if (!test_is_empty(&grille)){
		printf("Executer un backtracking sur la grille ? (0:Non / 1:Oui) : ");
		scanf("%d",&v);
		if (v){
			init_grille(gres);
			backtracking_resolution(&grille,&gres);
			printf("Solution (Par backtracking)\n");
			affiche_grille(gres);
		}
	}
	return 0;
}
