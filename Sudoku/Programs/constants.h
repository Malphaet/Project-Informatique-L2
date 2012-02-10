/*----------------------------------*/
/*		Sudoku Scholar Project		*/
/*----------------------------------*/
/*		Copyleft Maximilien Rigaut	*/
/*				 Charly Celereau	*/
/*----------------------------------*/
/*		Date : 	 	10/02/12		*/
/*----------------------------------*/

#ifndef __CONSTANTS__
#define __CONSTANTS__

/************* Includes *************/

/************** Defines *************/

#define DIM 9
#define DIM_Region 3

#if DIM<10
#define GBSIZE (2*DIM+4+3*(DIM/3-2))
#else
#define GBSIZE (3*DIM+4+3*(DIM/3-2))
#endif
/************** Typedef *************/

#endif
