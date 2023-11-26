#ifndef SudokuInterface_DEF
#define SudokuInterface_DEF

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "debugmalloc.h"
#include "WINDOW_PARAMETERS.h"
#include "ErrorHandler.h"
#include "FontManager.h"
#include "GameState.h"
#include "ColorPalette.h"

#include "Sudoku.h"

static SDL_Point cursorClick;
static SDL_Scancode keypress;

static SDL_Point start;
static SDL_Point end;

extern void GenerateSudoku(int size, int diff, bool hl, int cheat);

extern void RenderHelpButton();
extern void RenderBackButton();
extern void RenderGrid();
extern void RenderCell(int x, int y, int val, int visual);
extern void SudokuInterface_MainLoop(SDL_Point cursorClick, SDL_Scancode keypress);

extern void SudokuGameCompleted();

#endif