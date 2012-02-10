/*----------------------------------*/
/*		Sudoku Scholar Project		*/
/*----------------------------------*/
/*		Copyleft Maximilien Rigaut	*/
/*				 Charly Celereau	*/
/*----------------------------------*/
/*		Date : 	 	10/02/12		*/
/*----------------------------------*/

#ifndef _STRUCTURES_
#define _STRUCTURES_

/************* Includes *************/
#include "constants.h"

/************** Typedef *************/

typedef int GRILLE[DIM][DIM];

typedef struct CASE
{
	int candidats[DIM];
	int nb_candidats;
	int value;
	/* Position de la case dans la grille (ligne, colone) */
	int row;
	int col;
} CASE;

/************* Prototype ************/
void init_grille(GRILLE);
void affiche_grille(GRILLE);
void saisie_grille(GRILLE, char *adr);
void init_case(CASE *c, int, int);
void affiche_case(CASE c);
void remplit_case(CASE *c, int);

#endif
