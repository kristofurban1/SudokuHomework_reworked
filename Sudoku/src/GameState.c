#include "GameState.h"

static int current_GameState;
static int current_SudokuState;

extern void Gamestate_Init(){
    current_GameState   = 0;
    current_SudokuState = 0;
}

extern int GetGamestate() { return current_GameState; }

extern void SetGameState(int newState) { current_GameState = newState; }

extern int GetSudokustate() { return current_SudokuState; }

extern void SetSudokuState(int newState) {current_SudokuState = newState; }