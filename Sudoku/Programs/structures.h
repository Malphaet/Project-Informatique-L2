/*----------------------------------*/
/*  Sudoku Scholar Project          */
/*----------------------------------*/
/*  Copyleft Maximilien Rigaut      */
/*           Charly Celereau        */
/*----------------------------------*/
/*  Date : 10/02/12                 */
/*----------------------------------*/

#ifndef __STRUCTURES__
#define __STRUCTURES__

/************* Includes *************/
#include "constants.h"

/************** Typedef *************/

/* Case */
typedef struct CASE
{
	int candidats[DIM]; /* Nombres candidats pour la resolution de la case */
	int nb_candidats; /* Nombre de candidats potentiels */
	int value; /* Valeur de la case : 0 si non resolue; la valeur adaptee sinon */
	/* Position de la case dans la grille (ligne, colone) */
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
typedef CASE GRILLE[DIM][DIM];
/************* Prototype ************/

void init_grille(GRILLE); 					/* Tested */
void affiche_grille(GRILLE);				/* Tested */
void saisie_grille(GRILLE, char *);			/* Tested */
void init_case(CASE *, int, int);			/* Tested */
void affiche_case(CASE);					/* Tested */
void remplit_case(CASE *, int);				/* Seems Working | Warning:Might be not well implemented */
void init_pile_case(GRILLE, PILE_CASE *);	/* Tested */
void affiche_pile(PILE_CASE *);				/* Tested */
int supprime_candidat(CASE *,int);			/* Seems Working | Warning:Might be not well implemented */
int contrainte_unicite_ligne_case(GRILLE, PILE_CASE *, CASE *);		/* Seems Working */
int contrainte_unicite_colone_case(GRILLE, PILE_CASE *, CASE *);	/* Seems Working */
int contrainte_unicite_case(GRILLE, PILE_CASE *, CASE *);			/* Seems Working */
int contrainte_unicite(GRILLE, PILE_CASE *);	/* Not Implemented */
int contrainte_unicite_grille(GRILLE);		/* Not Implemented */


#endif
