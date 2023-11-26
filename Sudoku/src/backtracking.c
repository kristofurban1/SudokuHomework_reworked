#include "backtracking.h"

static void clamp(int *val, int max){
    if (*val > max) *val = 1;
}

static void GuessStartValue(int *board, int *startValues, int index, int dim){
    int val = (rand() % dim) + 1; // ranmnd % dim => 0 - dim-1  +1=> 1 - dim
    board[index] = val;
    startValues[index] = val;
}

static bool GuessNextValue(int *board, int *startValues, int index, int dim){
    int nextval = board[index] + 1;
    clamp(&nextval, dim);

    if (nextval == startValues[index]) {
       
        board[index] = 0;
        startValues[index] = 0;
        return false;
    }

    board[index] = nextval;
    return true;
}

extern void SolveGame(int *board, int sudokuSize){
    int sudokuDim = sudokuSize * sudokuSize; 
    int targetMax = sudokuDim;
    int index = 0;

    // Soduku solution (aka board) is already initalized.
    int *startValues = malloc(sizeof(int) * sudokuDim * sudokuDim);
    memset(startValues, 0,  sizeof(int) * sudokuDim * sudokuDim);
    

    while (index < sudokuDim * sudokuDim)
    {
        if (startValues[index] == 0) GuessStartValue(board, startValues, index, sudokuDim);


        if(
            TestRowNum(board, index / sudokuDim, board[index], sudokuSize) &&
            TestColNum(board, index % sudokuDim, board[index], sudokuSize) &&
            TestAreaNum(board, GetAreaFromPos(index, sudokuSize), board[index], sudokuSize)
        ) index++;
        else if (!GuessNextValue(board, startValues, index, sudokuDim)) { 
            GNV_RECURSIVE_TEST:

            index--;  
            if (!GuessNextValue(board, startValues, index, sudokuDim)) goto GNV_RECURSIVE_TEST;
        }
        
        
    }
    free(startValues);
}