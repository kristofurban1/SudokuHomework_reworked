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
int *GetHighlightMap(){
    return HighlightMap;
}

void FreeBoards(){
    if (SudokuGame      != NULL)    free(SudokuGame);
    if (SudokuSolution  != NULL)    free(SudokuSolution);
    if (HighlightMap    != NULL)    free(HighlightMap);
    SudokuGame = SudokuSolution = HighlightMap = NULL;
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

    SolveGame(SudokuSolution, SudokuBoardSize);

    memcpy(SudokuGame, SudokuSolution, allocationSize);

    float diff_remainFilled;
    switch (difficulty)
    {
    case 0:
        diff_remainFilled = DifficultyEasy;
        break;
    case 1:
        diff_remainFilled = DifficultyMedium;
        break;
    case 2:
        diff_remainFilled = DifficultyHard;
        break;
    case 3:
        diff_remainFilled = DifficultyExtreme;
        break;
    
    default:
        diff_remainFilled = DifficultyEasy;
        break;
    }


    int toRemove = GetBoardTotalSize() * (1 - diff_remainFilled);

    int first_rem = rand() % GetBoardTotalSize();
    SudokuGame[first_rem] = 0;
    toRemove--;
    while (toRemove != 0)
    {
        int to_rem;
        do{
           to_rem = rand() % GetBoardTotalSize();
        } while(SudokuGame[to_rem] == 0);
        SudokuGame[to_rem] = 0;
        toRemove--;
        /*
        if (!Verify_Solution(SudokuGame, SudokuBoardSize))
            SudokuGame[to_rem] = SudokuSolution[to_rem]; // if cannot be removed, replace and try again.
        
        else toRemove--;
        */
    }


}

static void CheckCompletion(){
    for (int i = 0; i < GetBoardTotalSize(); i++)
        if (SudokuGame[i] == 0) return;
    

    for (int i = 0; i < Sudoku_BoardDim; i++)
    {
        for (int val = 0; val < Sudoku_BoardDim; val++)
        {
            if (!(
                TestRowNum(SudokuGame, i, val, SudokuBoardSize) &&
                TestColNum(SudokuGame, i, val, SudokuBoardSize) &&
                TestAreaNum(SudokuGame, GetAreaFromPos(i, SudokuBoardSize), val, SudokuBoardSize)
            )) return;
        }
        
        SetGameState(GS_MainMenu);
        SetSudokuState(GS_UNSET);
        FreeBoards();
    }
    
}

void ResetHighlightMap() { memset(HighlightMap, 0, sizeof(int) * GetBoardTotalSize()); };
0
static void SetActiveI(int activeI){
    
    ResetHighlightMap();

    SelectedByUser = activeI;

    if (HighlightEnabled){
        for (int i = 0; i < GetBoardTotalSize(); i++)
        {
            if (SudokuGame[i] == SudokuGame[activeI]) HighlightMap[i] = 2; // Highlighted
        }
    }
    HighlightMap[activeI] = 1; // Selected
}

void SetActive(int x, int y){
    int activeI = (y * Sudoku_BoardDim) + x;
    SetActiveI(activeI);
}   

void ClearSelection(){
    SelectedByUser = -1;
    ResetHighlightMap();
}

void ShowErrors(){

}

void WriteToCell(int number){
    if (SelectedByUser == -1) return;
    printf("Writing %d to %d\n", number, SelectedByUser);

    int current = SudokuGame[SelectedByUser];
    int new = (current * 10) + number;
    if (new > Sudoku_BoardDim) new = number;
    SudokuGame[SelectedByUser] = new;

    SetActiveI(SelectedByUser);

    CheckCompletion();

    if(AutoHelp) ShowErrors();
}
