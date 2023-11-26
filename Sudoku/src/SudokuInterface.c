#include "SudokuInterface.h"

static SDL_Point cursorClick;
static SDL_Scancode keypress;

static int size; 
static int diff;
static bool hl;
static int cheat;

/*
    @brief Gets called by GameCompletedCallback, appends game to leaderboard and calls endscreen.
*/
static void SudokuGameCompleted(){
    printf("SudokuInterface: Game completed callback.\n");
    SetGameState(GS_SudokuState);
    SetSudokuState(GS_SudokuEndScreen);
    FreeBoards();

    uint64_t timeEnlapsed = SDL_GetTicks64() - GetSudokuTimerStart();

    int entryCount;
    struct Leaderboard_Entry *entires = ReadLeaderboard(&entryCount);

    // Add 1 extra spot;
    if (entryCount == 0) 
        entires = malloc(sizeof(struct Leaderboard_Entry)); 
    else 
        entires = realloc(entires, sizeof(struct Leaderboard_Entry) * (entryCount+1)); 
    malloc_verify(entires);

    entires[entryCount].BoardSize = size;
    entires[entryCount].u16CheatLevel = (cheat << 1 ) | (hl & 1);
    entires[entryCount].u16Difficulty = diff;
    entires[entryCount].Seconds = timeEnlapsed / 1000;
    entryCount++;
    
    WriteLeaderboard(entires, entryCount);
    free(entires);
}


extern void GenerateSudoku(int _size, int _diff, bool _hl, int _cheat){

    size  = _size; 
    diff  = _diff;
    hl    = _hl;
    cheat = _cheat;

    SetDifficulty(diff);
    SetHighlightEnalbled(hl);
    switch (cheat)
    {
    case 0:;
        SetAvailableHelp(0);
        break;
    case 1:;
        SetAvailableHelp(3);
        break;
    case 2:;
        SetAvailableHelp(-1);
        break;
    case 3:;
        SetAutoHelp(true);
        break;
    default:;
        SetAvailableHelp(0);
        break;
    }
    
    GenerateBoard(size, SDL_GetTicks64(), &SudokuGameCompleted);

}

static SDL_Point start;
static SDL_Point end;

/*
    Render_xxx
        static functions that break down the mainloop, they do not take parameters and dont return anything.
        @important Some that handle keypress or mouseclick will expect cursorClickPos to be set correctly.
        @memory The textures rendered may take larger amounts of memory based on Window Size, 
            homewer as soon as they are allocated they will be freed so they don't add up to anything substential.
*/

static void RenderHelpButton(){
    char text[10];
    if (GetAvailableHelp() < 0) sprintf(text, "Help");
    else sprintf(text, "Help (%d)", GetAvailableHelp());

    int render_w, render_h;
    SDL_Texture *rendered_text = RenderFont(MainRenderer, GetFont(), text, C_White, &render_w, &render_h);
    SDL_Rect rect;
    rect.h = MainWindowHeight * 0.05;
    rect.w = (int)(((float)rect.h / render_h) * render_w);
    rect.x = (MainWindowWidth * 0.85) - rect.w;
    rect.y = (MainWindowHeight * 0.01);

    SetRenderDrawSDLColor(MainRenderer, C_DarkGreen);
    SDL_Rect bg_rect;
    bg_rect.w = rect.w * 1.1;
    bg_rect.h = rect.h;
    bg_rect.x = (MainWindowWidth * 0.85) - bg_rect.w;
    bg_rect.y = rect.y - (rect.h * 0.1);
    SDL_RenderFillRect(MainRenderer, &bg_rect);

    SDL_RenderCopy(MainRenderer, rendered_text, NULL, &rect);
    SDL_DestroyTexture(rendered_text);

    if (SDL_PointInRect(&cursorClick, &bg_rect)){
        printf("SudokuInterface: Help\n");
        if (GetAvailableHelp() != 0){
            ShowErrors();

            if (GetAvailableHelp() > 0) SetAvailableHelp(GetAvailableHelp() - 1);
        }
    }
}

static void RenderBackButton(){
    char *text = "Back";
    int render_w, render_h;
    SDL_Texture *rendered_text = RenderFont(MainRenderer, GetFont(), text, C_White, &render_w, &render_h);
    SDL_Rect rect;
    rect.h = MainWindowHeight * 0.05;
    rect.w = (int)(((float)rect.h / render_h) * render_w);
    rect.x = (MainWindowWidth * 0.99) - rect.w;
    rect.y = (MainWindowHeight * 0.01);

    SetRenderDrawSDLColor(MainRenderer, C_DarkGreen);
    SDL_Rect bg_rect;
    bg_rect.w = rect.w * 1.1;
    bg_rect.h = rect.h;
    bg_rect.x = (MainWindowWidth * 0.99) - bg_rect.w;
    bg_rect.y = rect.y - (rect.h * 0.1);
    SDL_RenderFillRect(MainRenderer, &bg_rect);

    SDL_RenderCopy(MainRenderer, rendered_text, NULL, &rect);
    SDL_DestroyTexture(rendered_text);

    if (SDL_PointInRect(&cursorClick, &bg_rect)){
        printf("SudokuInterface: BackButtonClick\n");
        SetGameState(GS_MainMenu);
        SetSudokuState(GS_UNSET);
        FreeBoards();
    }

}

static void RenderGrid(){
    int boardSize = end.x - start.x;
    float cellSize  = (float)boardSize / GetBoardDimension();
    SetRenderDrawSDLColor(MainRenderer, C_Gray);
    for (size_t i = 0; i < GetBoardDimension() + 1; i++)
    {
        int x = (int)(i * cellSize + 0.5);

        SDL_RenderDrawLine(MainRenderer, start.x + x, start.y, start.x + x, start.y + boardSize);
        SDL_RenderDrawLine(MainRenderer, start.x, start.y + x, start.x + boardSize, start.y + x);
    }
    
    SetRenderDrawSDLColor(MainRenderer, C_Green);
    for (int i = 0; i < GetBoardSize() + 1; i++)
    {
        int x = i * (cellSize * GetBoardSize());

        SDL_RenderDrawLine(MainRenderer, start.x + x, start.y, start.x + x, start.y + boardSize);
        SDL_RenderDrawLine(MainRenderer, start.x, start.y + x, start.x + boardSize, start.y + x);
    }
    
}
static void RenderCell(int x, int y, int val, int visual){
    int boardSize = end.x - start.x;
    float cellSize  = (float)boardSize / GetBoardDimension();

    int posx = (int)(cellSize * x + 0.5);
    int posy = (int)(cellSize * y + 0.5);
    
    SDL_Color color;
    switch (visual)
    {
    case 0:
        color = C_White;    // Default
        break;
    case 1: 
        color = C_Green;      // Selected
        break;
    case 2:
        color = C_Yellow;   // Highlight
        break;
    case 3: 
        color = C_Red;      // Error
        break;
    default:
        color = C_White; // Unknown
        break;
    }
    
    SDL_Rect rect;
    if (val != 0){
        char cellVal[10];
        sprintf(cellVal, "%d" ,val);
        int render_w, render_h;
        SDL_Texture *rendered_text = RenderFont(MainRenderer, GetFont(), cellVal, color, &render_w, &render_h);
        
        rect.h = (int)(cellSize * 0.8 + 0.5) ;
        rect.w = (int)(cellSize * 0.8 + 0.5);
        rect.x = posx + start.x + (int)(cellSize * 0.1 + 0.5);
        rect.y = posy + start.y + (int)(cellSize * 0.2 + 0.5);

        SDL_RenderCopy(MainRenderer, rendered_text, NULL, &rect);
        SDL_DestroyTexture(rendered_text);
    }
    else{
        rect.w = cellSize;
        rect.h = cellSize;
        rect.x = posx + start.x;
        rect.y = posy + start.y;

        if (visual == 1){
            SetRenderDrawSDLColor(MainRenderer, C_DarkGreen);
            SDL_RenderFillRect(MainRenderer, &rect);
        }
    }
    

    if (SDL_PointInRect(&cursorClick, &rect)){
        printf("Clicked cell: %d:%d\n", x, y);
        SetActive(x, y);
    };
}

static void RenderTimer(){
    uint64_t timerStart = GetSudokuTimerStart();
    uint64_t timerNow = SDL_GetTicks64();
    uint64_t enalpsed = timerNow - timerStart;

    int totalSeconds = enalpsed / 1000;
    int totalMinutes = totalSeconds / 60;

    int seconds = totalSeconds % 60;
    int minutes = totalMinutes % 60;
    int hours = totalMinutes / 60;

    char secs[3];
    char mins[3];
    char  hrs[3];
    sprintf(secs, "%d%d", seconds / 10, seconds % 10);
    sprintf(mins, "%d%d", minutes / 10, minutes % 10);
    sprintf( hrs, "%d%d", hours / 10, hours % 10);

    char timer[15];
    sprintf(timer, "%s:%s:%s", hrs, mins, secs);

    int render_w, render_h;
    SDL_Texture *rendered_text = RenderFont(MainRenderer, GetFont(), timer, C_White, &render_w, &render_h);
    SDL_Rect rect;
    rect.h = MainWindowHeight * 0.05;
    rect.w = (int)(((float)rect.h / render_h) * render_w);
    rect.x = 0;
    rect.y = 0;

    SDL_RenderCopy(MainRenderer, rendered_text, NULL, &rect);
    SDL_DestroyTexture(rendered_text);
}

extern void SudokuInterface_MainLoop(SDL_Point cursorclick, SDL_Scancode _keypress){
    cursorClick = cursorclick;
    keypress = _keypress;

    SetRenderDrawSDLColor(MainRenderer, C_Black);
    SDL_RenderClear(MainRenderer);

    int w = MainWindowWidth * 0.85;
    int h = w;
    if (MainWindowHeight * 0.85 < h){
        h = MainWindowHeight * 0.85;
        w = h;
    }

    start.x = (MainWindowWidth  / 2) - (w / 2);
    start.y = (MainWindowHeight / 2) - (h / 2);
    end.x = start.x + w;
    end.y = start.y + h;
    SDL_Rect bg;
    bg.x = start.x;
    bg.y = start.y;
    bg.w = w;
    bg.h = h;
    SetRenderDrawSDLColor(MainRenderer, C_DarkGray);
    SDL_RenderFillRect(MainRenderer, &bg);

    RenderHelpButton();
    
    RenderGrid();

    int *board = GetBoard();
    int *hlmap = GetHighlightMap();
    for (int i = 0; i < GetBoardTotalSize(); i++)
    {
        int x = i % GetBoardDimension();
        int y = i / GetBoardDimension();

        RenderCell(x, y, board[i], hlmap[i]);
    }
    
    RenderBackButton();

    RenderTimer();

    if (keypress == SDL_SCANCODE_UNKNOWN) return;

    if (keypress == SDL_SCANCODE_ESCAPE) ClearSelection();

    if      (!(keypress < 30 || keypress > 38)) WriteToCell(keypress - 29);
    else if (!(keypress < 89 || keypress > 97)) WriteToCell(keypress - 88);
    else if (keypress == 53 || keypress == 98)  WriteToCell(0);

}