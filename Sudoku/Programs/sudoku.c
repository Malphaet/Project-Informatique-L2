/*----------------------------------*/
/*		Sudoku Scholar Project		*/
/*----------------------------------*/
/*		Copyleft Maximilien Rigaut	*/
/*				 Charly Celereau	*/
/*----------------------------------*/
/*		Date : 	 	10/02/12		*/
/*----------------------------------*/

/************* Includes *************/

#include <stdio.h>
#include "structures.h"

/************** Defines *************/

/*************** Main **************/

int main(void)
{
	char path[]="../Data/grilles_test.txt";
	GRILLE grille;
	PILE_CASE Pile;
	init_grille(grille);
	saisie_grille(grille,path);
	affiche_grille(grille);
	affiche_case(grille[1][1]);
	init_pile_case(grille, &Pile);
	affiche_pile(&Pile);
	return 0;
}


/************ Test Functions *************/
void affiche_pile(PILE_CASE *Pile)
{
	int i;
	CASE **pile_ptr = Pile->cases;
	for(i = 0; i < Pile->nb_cases; i++)
	{
			affiche_case(*pile_ptr[i]);
	}
}
