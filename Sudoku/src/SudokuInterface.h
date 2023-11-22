#ifndef SudokuInterface_DEF
#define SudokuInterface_DEF

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "debugmalloc.h"
#include "ErrorHandler.h"
#include "GameState.h"
#include "main_menu.h"

#include "Sudoku.h"


extern void SudokuInterface_MainLoop(SDL_Point cursorClick, SDL_Scancode keypress);

#endif