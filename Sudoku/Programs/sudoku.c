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

int main(void){
	char path[]="../Data/grille.txt";
	GRILLE grille;
	init_grille(grille);
	saisie_grille(grille,path);
	affiche_grille(grille);
	return 0;
}

/************ Functions *************/

