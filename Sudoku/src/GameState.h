#ifndef GameState_DEF
#define GameState_DEF

#include "debugmalloc.h"
#include "ErrorHandler.h"

#define GS_TitleScreen_Durration 2000

extern enum GameStates{
    GS_TitleScreen = 0, 
    GS_MainMenu = 1,
    GS_SudokuState = 2
} GameStates;

extern enum SudokuState{
    GS_Sudoku = 0,
    GS_SudokuEndScreen = 1,
    GS_UNSET = 3
} SudokuState;

/*
    @brief Loads default gamestates.
*/
extern void Gamestate_Init();

/*
    @brief Gets-Sets Sudoku- and Game-states.
*/
extern int GetGamestate();
extern void SetGameState(int newState);
extern int GetSudokustate();
extern void SetSudokuState(int newState);



#endif