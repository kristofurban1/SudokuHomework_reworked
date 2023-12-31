#include "sudoku_tester.h"


extern int GetAreaFromPos(int pos, int size){
    int dim = size * size;

    int pos_in_row = pos / dim;
    int area_row_index = pos_in_row / size;

    int pos_in_col = pos % dim;
    int area_col_index = pos_in_col / size;

    int areaIndex = (area_row_index * size) + area_col_index;

    return areaIndex;
}

extern bool TestRowNum(int *board, int rowIndex, int num, int size){
    int dim = size * size;
    bool found = false;
    for (int col = 0; col < dim; col++)
    {
        int index = (rowIndex * dim) + col;
        if (board[index] == num){
            if (found) return false;
            found = true;
        }
    }
    return true;
}

extern bool TestColNum(int *board, int colIndex, int num, int size){
    int dim = size * size;
    bool found = false;
    for (int row = 0; row < dim; row++)
    {
        int index = (row * dim) + colIndex; 
        if (board[index] == num){
            if (found) return false;
            found = true;
        }
    }
    return true;
}

extern bool TestAreaNum(int *board, int areaIndex, int num, int size){
    int dim = size * size;
    bool found = false;
    int tmp = areaIndex * size;
    int startCol = tmp % dim;
    int startRow = (tmp / dim) * size;
    for (int areacellIndex = 0; areacellIndex < dim; areacellIndex++)
    {
        int x = areacellIndex % size;
        int y = areacellIndex / size;
        int col = startCol + x;
        int row = startRow + y;
        int index = (row * dim) + col;
        if (board[index] == num){
            if (found) return false;
            found = true;
        }
    }
    return true;
}