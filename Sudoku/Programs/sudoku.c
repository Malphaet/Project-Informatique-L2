/*----------------------------------*/
/*  Sudoku Scholar Project          */
/*----------------------------------*/
/*  Copyleft Maximilien Rigaut      */
/*           Charly Celereau        */
/*----------------------------------*/
/*  Date : 10/02/12                 */
/*----------------------------------*/

/************* Includes *************/

#include <stdio.h>
#include "structures.h"

/************** Defines *************/

/*************** Main **************/

int main(void)
{
	char path[]="../Data/grille2.txt";
	/*int i;*/
	GRILLE grille;
	PILE_CASE Pile;
	init_grille(grille);
	saisie_grille(grille,path);
	init_pile_case(grille, &Pile);
	
	affiche_grille(grille);
	/* affiche_case(grille[1][1]); */
	/* affiche_pile(&Pile); */
	/* while (supprime_candidat(&grille[0][0],i++)) affiche_case(grille[0][0]); */
		
	/* i=0; while (i<DIM) affiche_case(grille[1][i++]);
	contrainte_unicite_ligne_case(grille, &Pile, &grille[1][1]);
	i=0; while (i<DIM) affiche_case(grille[1][i++]);*/

	contrainte_unicite_case(grille, &Pile, &grille[2][0]);
	
	return 0;
}


/************ Test Functions *************/
void affiche_pile(PILE_CASE *Pile)
{
	int i;
	CASE **pile_ptr = Pile->cases;
	for(i = 0; i < Pile->nb_cases; i++)
			affiche_case(*pile_ptr[i]);
}
