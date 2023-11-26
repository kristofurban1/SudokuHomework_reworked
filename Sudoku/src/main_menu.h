#ifndef MAIN_MENU_DEF
#define MAIN_MENU_DEF

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "debugmalloc.h"
#include "ErrorHandler.h"
#include "FontManager.h"
#include "GameState.h"
#include "ColorPalette.h"
#include "datastructures.h"
#include "SudokuInterface.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define TITLE_TEXT "SUDOKU"

/*
    @brief MainMenu Set/Get Values
    @description When saving or loading savedata, these values get parsed.

    @param size Boardsize value to set / Pointer to return BoardSize
    @param diff Difficulty valueto set / Pointer to return Difficulty
    @param cheatlvl Cheat level to set / Pointer to return Cheat level
*/
extern void MM_SetValues(int size, int diff, int cheatlvl);
extern void MM_GetValues(int *size, int *diff, int *cheatlvl);

/*
    Maximum and minimum sizes of sudokuboards. Not advised to  change. Technically it will render it but 
        due to the exponentially increasing density it may not be visible, or the Sudoku Solving algorithm may take too long to calculate.
*/
#define MIN_SUDOKUSIZE 2
#define MAX_SUDOKUSIZE 4

/*
    @brief Saves the window and set gamedata in case application exits.
*/
extern void MainMenu_SaveData();

/*
    @brief Called by mainloop, displays mainmenu.
    @description Displays title, board size, difficulty and cheat settings, exit and start buttons.
    @param cursorClick Cursor click position, if there was one. If not input {-1, -1}
*/
extern void MainMenu_MainLoop(SDL_Point cursorPos);

#endif