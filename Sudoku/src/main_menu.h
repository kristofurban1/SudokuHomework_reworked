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

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define TITLE_TEXT "SUDOKU"

static int BoardSize;
extern void SetBoardSize(int newsize);
extern int GetBoardSizeFromUser();

#define MIN_SUDOKUSIZE 2
#define MAX_SUDOKUSIZE 8

extern int selectedSudokuSize;
extern int selectedDifficulty;
extern int selectedCheatLevel;

static void RenderTitle();
static void RenderSudokuSizeSelector();
static void RenderDifficultySelector();
static void RenderCheatSelector();
static void RenderStartButton();


extern void MainMenu_MainLoop(SDL_Point cursorPos);

#endif