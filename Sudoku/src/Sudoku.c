#include "Sudoku.h"

static int SudokuBoardSize = 0;
static int Sudoku_BoardDim = 0;
static int *SudokuGame = NULL;
static int *SudokuSolution = NULL;
static int *HighlightMap = NULL; // 0: normal; 1: Selected by user; 2: Highlighted; 4: Error
static int SelectedByUser = -1;

static int Difficulty = 0;
static bool HighlightEnabled = false;
static int GameAvailableHelp = 0;
static bool AutoHelp = false;

static uint64_t SudokuTimerStart;
static void (*CompletedCallback)();

extern uint64_t GetSudokuTimerStart(){
    return SudokuTimerStart;
}
extern int GetBoardTotalSize(){
    return Sudoku_BoardDim * Sudoku_BoardDim;
}
extern int GetBoardDimension(){
    return Sudoku_BoardDim;
}
extern int GetBoardSize(){
    return SudokuBoardSize;
}
extern int *GetBoard(){
    return SudokuGame;
}
extern int *GetHighlightMap(){
    return HighlightMap;
}
extern int GetAvailableHelp(){
    return GameAvailableHelp;
}


extern void SetDifficulty(int difficulty){
    Difficulty = difficulty;
}
extern void SetHighlightEnalbled(int highlightEnabled){
    HighlightEnabled = highlightEnabled;
}
extern void SetAvailableHelp(int helpCount){
    GameAvailableHelp = helpCount;
}
extern void SetAutoHelp(bool autoHelp){
    AutoHelp = autoHelp;
}

extern void FreeBoards(){
    if (SudokuGame      != NULL)    free(SudokuGame);
    if (SudokuSolution  != NULL)    free(SudokuSolution);
    if (HighlightMap    != NULL)    free(HighlightMap);
    SudokuGame = SudokuSolution = HighlightMap = NULL;
}


extern void GenerateBoard(int boardsize, uint64_t timerStart, void (*SudokuCompletedFnc)()){

    CompletedCallback = SudokuCompletedFnc;

    SudokuBoardSize = boardsize;
    Sudoku_BoardDim = boardsize * boardsize;

    SudokuTimerStart = timerStart;

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
    switch (Difficulty)
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
        for (int val = 1; val <= Sudoku_BoardDim; val++)
        {
            if (!(
                TestRowNum(SudokuGame, i, val, SudokuBoardSize) &&
                TestColNum(SudokuGame, i, val, SudokuBoardSize) &&
                TestAreaNum(SudokuGame, GetAreaFromPos(i, SudokuBoardSize), val, SudokuBoardSize)
            )) return;
        }
    }

    CompletedCallback();
    
}

static void ResetHighlightMap() { memset(HighlightMap, 0, sizeof(int) * GetBoardTotalSize()); };

static void SetActiveI(int activeI){
    
    if (SudokuGame[activeI] != 0)
        ResetHighlightMap();
    
    if (SudokuGame[SelectedByUser] == 0)
        HighlightMap[SelectedByUser] = 0;

    SelectedByUser = activeI;

    if (HighlightEnabled){
        for (int i = 0; i < GetBoardTotalSize(); i++)
        {
            if (SudokuGame[i] == SudokuGame[activeI]) HighlightMap[i] = 2; // Highlighted
        }
    }
    HighlightMap[activeI] = 1; // Selected
}

extern void SetActive(int x, int y){
    int activeI = (y * Sudoku_BoardDim) + x;
    SetActiveI(activeI);
}   

extern void ClearSelection(){
    SelectedByUser = -1;
    ResetHighlightMap();
}

extern void ShowErrors(){
    for (int i = 0; i < GetBoardTotalSize(); i++)
    {
        if (SudokuGame[i] != SudokuSolution[i]) HighlightMap[i] = 3; // Error
    }
}

extern void WriteToCell(int number){
    if (SelectedByUser == -1) {
        ResetHighlightMap();
        if (HighlightEnabled){
            for (int i = 0; i < GetBoardTotalSize(); i++)
            {
                if (SudokuGame[i] == number) HighlightMap[i] = 2; // Highlighted
            }
        }
        return;
    }
    printf("Writing %d to %d\n", number, SelectedByUser);

    int current = SudokuGame[SelectedByUser];
    int new = (current * 10) + number;
    if (new > Sudoku_BoardDim) new = number;
    SudokuGame[SelectedByUser] = new;

    SetActiveI(SelectedByUser);

    if(AutoHelp) ShowErrors();
    
    CheckCompletion();
}
