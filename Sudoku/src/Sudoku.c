#include "Sudoku.h"

int SudokuBoardSize = 0;
int Sudoku_BoardDim = 0;
int *SudokuGame = NULL;
int *SudokuSolution = NULL;
int *HighlightMap = NULL; // 0: normal; 1: Selected by user; 2: Highlighted; 4: Error
int SelectedByUser = -1;

int difficulty = 0;
bool HighlightEnabled = false;
int GameAvailableHelp = 0;
bool AutoHelp = false;

int GetBoardTotalSize(){
    return Sudoku_BoardDim * Sudoku_BoardDim;
}
int GetBoardDimension(){
    return Sudoku_BoardDim;
}
int GetBoardSize(){
    return SudokuBoardSize;
}
int *GetBoard(){
    return SudokuGame;
}


void GenerateBoard(int boardsize){
    SudokuBoardSize = boardsize;
    Sudoku_BoardDim = boardsize * boardsize;

    int allocationSize = sizeof(int) * Sudoku_BoardDim * Sudoku_BoardDim;

    SudokuGame = malloc(allocationSize);
        malloc_verify(SudokuGame);
    memset(SudokuGame, 0, allocationSize);

    SudokuSolution = malloc(allocationSize);
        malloc_verify(SudokuSolution);
    memset(SudokuSolution, 0, allocationSize);

    HighlightMap = malloc(allocationSize);
        malloc_verify(HighlightMap);
    memset(HighlightMap, 0, allocationSize);

    SolveGame(SudokuSolution, Sudoku_BoardDim);
}



void ResetHighlightMap();
void ShowSelectedByUser();
void HighlightNumber(int number);
void ShowErrors();