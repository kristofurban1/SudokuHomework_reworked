#ifndef SudokuTester_DEF
#define SudokuTester_DEF

#include <stdbool.h>
#include "debugmalloc.h"

extern int GetAreaFromPos(int pos, int size);

extern bool TestRowNum(int *board, int rowIndex, int num, int size);
extern bool TestColNum(int *board, int colIndex, int num, int size);
extern bool TestAreaNum(int *board, int areaIndex, int num, int size);

#endif