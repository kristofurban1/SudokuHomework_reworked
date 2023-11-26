#ifndef Sudoku_DEF
#define Sudoku_DEF

#include <stdbool.h>
#include "debugmalloc.h"
#include "ErrorHandler.h"
#include "sudoku_tester.h"
#include "backtracking.h"
#include "GameState.h"

#define DifficultyEasy      0.8
#define DifficultyMedium    0.7
#define DifficultyHard      0.6
#define DifficultyExtreme   0.5

extern uint64_t GetSudokuTimerStart();
extern int GetBoardTotalSize();
extern int GetBoardDimension();
extern int GetBoardSize();
extern int *GetBoard();
extern int *GetHighlightMap();
extern int GetAvailableHelp();

extern void SetDifficulty(int difficulty);
extern void SetHighlightEnalbled(int highlightEnabled);
extern void SetAvailableHelp(int helpCount);
extern void SetAutoHelp(bool autoHelp);


extern void FreeBoards();
extern void GenerateBoard(int boardsize, uint64_t timerStart, void (*SudokuCompletedFnc)());

extern void SetActive(int x, int y);
extern void ClearSelection();
extern void WriteToCell(int number);
extern void ShowErrors();

#endif