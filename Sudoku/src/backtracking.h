#ifndef Backtracking_DEF
#define Backtracking_DEF

#include <stdbool.h>
#include "debugmalloc.h"
#include "ErrorHandler.h"
#include "sudoku_tester.h"

#include <SDL2/SDL.h>
#include "WINDOW_PARAMETERS.h"


/*
    @brief Creates a sudoku solution.
    @param board Pointer to an already allocated memory. This space will contained the solved boards after functions returns.
    @param sudokuDim The dimension of the sudoku board.

    @memory Uses around 4 * sudokuDim^2 bytes of memory.
    @executionTime Since a sudoku game cannot be solved mathematically, the time it will take to solve it is based on chance.
        The currently allowed maximum sudoku size only take a couple seconds at max.
*/
extern void SolveGame(int *board, int sudokuDim);

#endif