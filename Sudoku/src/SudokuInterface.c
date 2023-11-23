#include "SudokuInterface.h"

static SDL_Point cursorClick;
static SDL_Scancode keypress;

void GenerateSudoku(int size, int diff, bool hl, int cheat){
    difficulty = diff;
    HighlightEnabled = hl;
    switch (cheat)
    {
    case 0:;
        GameAvailableHelp = 0;
        break;
    case 1:;
        GameAvailableHelp = 3;
        break;
    case 2:;
        GameAvailableHelp = -1;
        break;
    case 3:;
        AutoHelp = true;
        break;
    default:;
        GameAvailableHelp = 0;
        break;
    }
    
    GenerateBoard(size);

}

static SDL_Point start;
static SDL_Point end;

extern void RenderHelpButton(){
    char text[10];
    if (GameAvailableHelp < 0) sprintf(text, "Help");
    else sprintf(text, "Help (%d)", GameAvailableHelp);

    int render_w, render_h;
    SDL_Texture *rendered_text = RenderFont(MainRenderer, GetFont(), text, C_White, &render_w, &render_h);
    SDL_Rect rect;
    rect.h = MainWindowHeight * 0.06;
    rect.w = (int)(((float)rect.h / render_h) * render_w);
    rect.x = (MainWindowWidth * 0.9) - rect.w;
    rect.y = (MainWindowHeight * 0.01);

    SetRenderDrawSDLColor(MainRenderer, C_DarkGreen);
    SDL_Rect bg_rect;
    bg_rect.w = rect.w * 1.1;
    bg_rect.h = rect.h;
    bg_rect.x = (MainWindowWidth * 0.9) - bg_rect.w;
    bg_rect.y = rect.y - (rect.h * 0.1);
    SDL_RenderFillRect(MainRenderer, &bg_rect);

    SDL_RenderCopy(MainRenderer, rendered_text, NULL, &rect);
    SDL_DestroyTexture(rendered_text);

    if (SDL_PointInRect(&cursorClick, &bg_rect)){
        printf("SudokuInterface: Help\n");
    }
}

extern void RenderBackButton(){
    char *text = "Back";
    int render_w, render_h;
    SDL_Texture *rendered_text = RenderFont(MainRenderer, GetFont(), text, C_White, &render_w, &render_h);
    SDL_Rect rect;
    rect.h = MainWindowHeight * 0.06;
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
    }

}

extern void RenderGrid(){
    int boardSize = end.x - start.x;
    int cellSize  = boardSize / GetBoardDimension();
    SetRenderDrawSDLColor(MainRenderer, C_Gray);
    for (size_t i = 0; i < GetBoardDimension() + 1; i++)
    {
        int x = i * cellSize;

        SDL_RenderDrawLine(MainRenderer, start.x + x, start.y, start.x + x, start.y + boardSize);
        SDL_RenderDrawLine(MainRenderer, start.x, start.y + x, start.x + boardSize, start.y + x);
    }
    
    SetRenderDrawSDLColor(MainRenderer, C_Green);
    for (int i = 0; i < GetBoardSize() + 1; i++)
    {
        int x = i * (cellSize * GetBoardSize());

        printf("x: %d\n", x);

        SDL_RenderDrawLine(MainRenderer, start.x + x, start.y, start.x + x, start.y + boardSize);
        SDL_RenderDrawLine(MainRenderer, start.x, start.y + x, start.x + boardSize, start.y + x);
    }
    printf("\n");
    
}
extern void RenderCell(int x, int y, int val, int visual){

}

void SudokuInterface_MainLoop(SDL_Point cursorclick, SDL_Scancode _keypress){
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
    RenderBackButton();
    

    RenderGrid();
}