#include "backtracking.h"

extern void (*render_temp)(SDL_Point, SDL_Scancode) = NULL;
SDL_Point asd1 = {-1, -1};
SDL_Scancode asd2 = SDL_SCANCODE_UNKNOWN;

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

void SolveGame(int *board, int sudokuSize){
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
            //printf("hi\n");
        }
        
        
        
    }
    free(startValues);
}

int *tmp;

bool Verify_Solution(int *board_org, int size){
    int dim = size * size;
    int first_empty = 0;
    for (int i = 0; i < dim * dim; i++)
        if (board_org[i] == 0) {
            first_empty = i;
            break;
        }
    
    printf("FE: %d\n", first_empty);
    int alloc_size = sizeof(int) * dim * dim;
    int *board_toFill    = malloc(alloc_size); malloc_verify(board_toFill); 
    int *board_startvals = malloc(alloc_size); malloc_verify(board_startvals);
    tmp = board_toFill;
    memcpy(board_toFill, board_org, alloc_size);
    memset(board_startvals, 0, alloc_size);
    for (int i = 0; i < dim*dim; i++)
        if (board_org[i] != 0) board_startvals[i] = -1;

    int solutionCount = 0;
    int index = first_empty;
    bool result = false;
    while (solutionCount < 2)
    {
        if (board_startvals[index] == -1) { index++; continue; }
        if (index >= dim * dim) {result = true; goto BT_VFS_BREAK; }
        if (board_startvals[index] == 0) board_startvals[index] = 1;

        if(
            TestRowNum(board_toFill, index / dim, board_toFill[index], size) &&
            TestColNum(board_toFill, index % dim, board_toFill[index], size) &&
            TestAreaNum(board_toFill, GetAreaFromPos(index, size), board_toFill[index], size)
        ) index++;

        else if (!GuessNextValue(board_toFill, board_startvals, index, dim)) { 
            GNV_RECURSIVE_TEST:

            index--;  
            if (index < first_empty) {result = true; goto BT_VFS_BREAK; }
            if (!GuessNextValue(board_toFill, board_startvals, index, dim)) goto GNV_RECURSIVE_TEST;
        }

        if (index >= dim * dim) {result = true; goto BT_VFS_BREAK; }

        printf("boayrd_tofill[%d]: %d\n", index, board_toFill[index]);
        
        render_temp(asd1, asd2);
        SDL_RenderPresent(MainRenderer);
        
        SDL_Delay(100);
        
    }

BT_VFS_BREAK:
    free(board_toFill);
    free(board_startvals);
    
    return result;
}