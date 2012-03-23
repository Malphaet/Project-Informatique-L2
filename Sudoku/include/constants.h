/*
 * constants.h
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



#ifndef __CONSTANTS__
#define __CONSTANTS__

/* =========== Includes  =========== */

/* ===========  Defines  =========== */

#define DIM 9
#define DIM_Region 3

/* A corriger */
#if DIM<10
#define GBSIZE (2*DIM+4+3*(DIM/3-2))
#else
#define GBSIZE (3*DIM+4+3*(DIM/3-2))
#endif

#endif
