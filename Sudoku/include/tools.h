/*
 * tools.h
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

#ifndef __TOOLS__
#define __TOOLS__

/* ===========  Includes  =========== */
#include "constants.h"
#include "structures.h"

/* =============  Defines  =========== */
/* Utils */
#define PL printf("You are in function: %s - line: %d\n", __func__,__LINE__); /** (debug) Afficher des informations sur la ligne */
#define TEST(p) if ((p)==NULL) {PL; printf("\n	> NULL pointer error\n"); exit(EXIT_FAILURE);} /** Teste si le pointeur est non nul */
#define FAIL {printf("\nUnexpected Error\n"); PL; exit(EXIT_FAILURE);} /** (debug) Faire echouer le programme */

/* Test */
#define PP(p) printf("Pile [%d] :",(p)->nb_cases);affiche_case((p)->cases[p->nb_cases-1]); /** Affiche la derniere valeur de la pile */

/* Shortcuts */
#define ADD_PILE(p,c) (p)->cases[(p)->nb_cases++] = (c); /** Ajouter c dans la pile p */
#define GR(x,y) g[x][y] /** Tres utile pour eviter de dependre de l'implementation de la grille */

#endif
