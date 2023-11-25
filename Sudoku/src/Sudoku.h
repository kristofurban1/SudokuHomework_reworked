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

extern int SudokuBoardSize;
extern int Sudoku_BoardDim;
extern int *SudokuGame;
extern int *SudokuSolution;
extern int *HighlightMap; // 0: normal; 1: Selected by user; 2: Highlighted; 4: Error
extern int SelectedByUser;

extern int difficulty;
extern bool HighlightEnabled;
extern int GameAvailableHelp;
extern bool AutoHelp;

extern int GetBoardTotalSize();
extern int GetBoardDimension();
extern int GetBoardSize();
extern int *GetBoard();
extern int *GetHighlightMap();

extern void FreeBoards();
extern void GenerateBoard(int boardsize);

extern void SetActive(int x, int y);
extern void ClearSelection();
extern void WriteToCell(int number);

extern void ResetHighlightMap();
extern void ShowErrors();





#endif