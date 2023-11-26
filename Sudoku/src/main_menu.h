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

extern void MM_SetValues(int size, int diff, int cheatlvl);
extern void MM_GetValues(int *size, int *diff, int *cheatlvl);

#define MIN_SUDOKUSIZE 2
#define MAX_SUDOKUSIZE 4

extern void MM_SetValues(int size, int diff, int cheatlvl);
extern void MM_GetValues(int *size, int *diff, int *cheatlvl);

extern void MainMenu_SaveData();

extern void MainMenu_MainLoop(SDL_Point cursorPos);

#endif