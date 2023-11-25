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

#include "Sudoku.h"


extern void EndScreen_MainLoop(SDL_Point cursorClick, SDL_Scancode keypress);

#endif