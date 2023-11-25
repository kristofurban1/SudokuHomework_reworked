#ifndef Backtracking_DEF
#define Backtracking_DEF

#include <stdbool.h>
#include "debugmalloc.h"
#include "ErrorHandler.h"
#include "sudoku_tester.h"

#include <SDL2/SDL.h>
#include "WINDOW_PARAMETERS.h"

extern int *tmp;

extern void SolveGame(int *board, int sudokuDim);

#endif