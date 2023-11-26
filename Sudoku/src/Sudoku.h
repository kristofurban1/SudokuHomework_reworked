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

/*
    These functions help access and manipulate specific parameters used by interface to control the game.
*/
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

/*
    @brief Frees the allocated boards after the game is done.
*/
extern void FreeBoards();

/*
    @brief Sets up sudoku parameters and calls SudokuSolver, then removes random cells..
    @memory Uses 3 × 4 × size^4 bytes of memory. For example a 3x3 board uses 973bytes of memory.

    @param boardsize Size of sudoku board
    @param timerStart The moment in time the game starts, used to calculate playtime.
    @param SudokuCompletedFnc Callback to function in interface, signals that the user won the game.
*/
extern void GenerateBoard(int boardsize, uint64_t timerStart, void (*SudokuCompletedFnc)());

/*
    @brief Translates coordinates to index and calls SetActiveI
*/
extern void SetActive(int x, int y);

/*
    @brief Clears user cell selection.
*/
extern void ClearSelection();

/*
    @brief Writes number to currently selected cell.
    @description Since using keyboard we can only write single digit numbers, and variable sudoku exceeds that single digit limit,
        this function tries to add inputted number to the number currently contained in cell.
        For example: number: 3, cell: 2 => 23
        In case this new number axceeds the limits of the current maximum value, it sets the number as cellvalue.
        For example: limit: 9 number 7, cell 2 => 27, since 27 is bigger than 9, cell value will be just 9.
        In cases this makes emptying a cell 2 keypresses (0).

        IF user has AutoErrorChecking, calls showErrors.
        Calls CheckCompletion
    @param number Number write to cell.
*/
extern void WriteToCell(int number);

/*
    @brief compares board to already calculated solution, writes error to highlight map.
*/
extern void ShowErrors();

#endif