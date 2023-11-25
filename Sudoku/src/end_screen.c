#include "end_screen.h"

static SDL_Point cursorClickPos;

static void Render_PlayAgain(){
    char *text = "Play again";
    int render_w, render_h;
    SDL_Texture *rendered_text = RenderFont(MainRenderer, GetFont(), text, C_White, &render_w, &render_h);
    SDL_Rect rect;
    rect.h = MainWindowHeight * 0.05;
    rect.w = (int)(((float)rect.h / render_h) * render_w);;
    rect.x = (MainWindowWidth * 0.5) - (rect.w / 2);
    rect.y = (MainWindowHeight * 0.9) - (rect.h / 2);

    SetRenderDrawSDLColor(MainRenderer, C_DarkGreen);
    SDL_Rect bg_rect;
    bg_rect.w = rect.w * 1.1;
    bg_rect.h = rect.h;
    bg_rect.x = (MainWindowWidth * 0.5) - (bg_rect.w / 2);
    bg_rect.y = rect.y - (rect.h * 0.1);
    SDL_RenderFillRect(MainRenderer, &bg_rect);

    SDL_RenderCopy(MainRenderer, rendered_text, NULL, &rect);
    SDL_DestroyTexture(rendered_text);

    if (SDL_PointInRect(&cursorClickPos, &bg_rect)){
        printf("MainMenu: StartButtonClick\n");
        SetGameState(GS_SudokuState);
        SetSudokuState(GS_Sudoku);
        //GenerateSudoku(selectedSudokuSize, selectedDifficulty, selectedHighlight, selectedCheatLevel);
        MainMenu_SaveData();
    }
}
static void Render_BackToMenu(){

}

extern void EndScreen_MainLoop(SDL_Point cursorClick, SDL_Scancode keypress){
    cursorClickPos = cursorClick;
}