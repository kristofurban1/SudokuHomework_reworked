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

extern bool Verify_Solution(int *board_org, int size);

extern void (*render_temp)(SDL_Point, SDL_Scancode);

#endif