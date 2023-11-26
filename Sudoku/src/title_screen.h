#ifndef TitleScreen_DEF
#define TitleScreen_DEF

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "debugmalloc.h"
#include "ErrorHandler.h"
#include "FontManager.h"
#include "GameState.h"
#include "ColorPalette.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define TITLESCREEN_TEXT "SUDOKU"

extern void SetTitleScreenTimer(int ms);
extern void TitleScreen_MainLoop(Uint64 deltatime);

#endif