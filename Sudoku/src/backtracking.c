#include "backtracking.h"


/*
    @brief Makes sure the value rolls over to 1.
    @descripton If value exceeds maximum, it rolls over to 1, otherwise it remains unchanged.
    @param val Value
    @param max Maximum value
*/
static void clamp(int *val, int max){
    if (*val > max) *val = 1;
}

/*
    @brief If the current item has no starting value, it randomly assigns it one.
    @descripton
        Using this method it will greatly decrese the chance of duplicate boards.
    
    @param board Pointer to the solution board
    @param startValues Pointer to board that contains the starting values
    @param index Current item on board to assign value.
    @param dim Dimension of the board.
*/
static void GuessStartValue(int *board, int *startValues, int index, int dim){
    int val = (rand() % dim) + 1; // ranmnd % dim => 0 - dim-1  +1=> 1 - dim
    board[index] = val;
    startValues[index] = val;
}


/*
    @brief Guesses a value based on given position.
    @description
        Increments number at index, if it reaches the starting value it returns false. Also prevents runaway with claming value.
    
    @param board Pointer to the solution board
    @param startValues Pointer to board that contains the starting values, this way the algorithm knows when it has tested every value.
    @param index Current item on board to increment.
    @param dim Dimension of the board.
*/
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