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

/*
    @brief Gets parameters from mainmenu or endscreen and calls Generate Board.
*/
extern void GenerateSudoku(int size, int diff, bool hl, int cheat);

/*
    @brief Called by mainloop, displays Sudoku game and interface.
    @description Displays sudoku board, exit and help button. Handles keyboard and mouse interactions with the game.
    @param cursorClick Cursor click position, if there was one. If not input {-1, -1}
    @param keypress Pressed key scancose, if there was one. If not input SDL_SCANCODE_UNKNOWN
*/
extern void SudokuInterface_MainLoop(SDL_Point cursorClick, SDL_Scancode keypress);

#endif