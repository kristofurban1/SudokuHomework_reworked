#ifndef ENDSCREEN_DEF
#define ENDSCREEN_DEF

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "debugmalloc.h"
#include "WINDOW_PARAMETERS.h"
#include "ErrorHandler.h"
#include "FontManager.h"
#include "GameState.h"
#include "ColorPalette.h"
#include "SudokuInterface.h"
#include "leaderboard_parser.h"

/*
    @brief Called by mainloop, displays end screen.
    @description Displays leaderboard, gives option to user to return to menu or start new game.
    @param cursorClick Cursor click position, if there was one. If not input {-1, -1}
*/
extern void EndScreen_MainLoop(SDL_Point cursorClick);

#endif