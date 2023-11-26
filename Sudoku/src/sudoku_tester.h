#ifndef SudokuTester_DEF
#define SudokuTester_DEF

#include <stdbool.h>
#include "debugmalloc.h"

/*
    @brief Returns the index of sub area based on position.
    @descripton Sudoku is made of a large grid and a small grid. To properly address sub area to test this function is used.
*/
extern int GetAreaFromPos(int pos, int size);

/*
    @brief Tests if Row/Column/Area specified adheres to the rules of sudoku.

    @param board Pointer to sudoku board
    @param index Index of Row/Colum/Area
    @param num Numbe to test with.
    @param size Size of sudoku board.
*/
extern bool TestRowNum(int *board, int rowIndex, int num, int size);
extern bool TestColNum(int *board, int colIndex, int num, int size);
extern bool TestAreaNum(int *board, int areaIndex, int num, int size);

#endif