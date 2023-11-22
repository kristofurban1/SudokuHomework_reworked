#include "main_menu.h"

int selectedSudokuSize = 3;
int selectedDifficulty = 0;
int selectedCheatLevel = 0;

SDL_Point cursorClickPos;

extern void SetBoardSize(int newsize) { BoardSize = newsize; }
extern int GetBoardSizeFromUser() { return BoardSize; }

static void RenderTitle(){
    char *text = TITLE_TEXT;
    int render_w, render_h;
    SDL_Texture *rendered_text = RenderFont(MainRenderer, GetFont(), text, C_Green, &render_w, &render_h);
    SDL_Rect rect;
    rect.w = MainWindowWidth * 0.3;
    rect.h = (int)(((float)rect.w / render_w) * render_h);
    rect.x = (MainWindowWidth * 0.5) - (rect.w / 2);
    rect.y = (MainWindowHeight * 0.1) - (rect.h / 2);

    SDL_RenderCopy(MainRenderer, rendered_text, NULL, &rect);
    SDL_DestroyTexture(rendered_text);
}

static void RenderSudokuSizeSelector(){

    int targetHeight;

    char *info = "Size: ";
    int info_w, info_h;
    SDL_Texture *rendered_info = RenderFont(MainRenderer, GetFont(), info, C_White, &info_w, &info_h);
    SDL_Rect info_rect;
    info_rect.w = MainWindowWidth * 0.1;
    info_rect.h = (int)(((float)info_rect.w / info_w) * info_h);
    info_rect.x = (MainWindowWidth * 0.1) - (info_rect.w / 2);
    info_rect.y = (MainWindowHeight * 0.25) - (info_rect.h / 2);
    targetHeight = info_rect.h;
    
    char *sub = "<";
    int sub_w, sub_h;
    SDL_Texture *rendered_sub = RenderFont(MainRenderer, GetFont(), sub, C_White, &sub_w, &sub_h);
    SDL_Rect sub_rect;
    sub_rect.h = targetHeight;
    sub_rect.w = (int)(((float)sub_rect.h / sub_h) * sub_w);
    sub_rect.x = info_rect.x + info_rect.w + (MainWindowWidth * 0.01);
    sub_rect.y = (MainWindowHeight * 0.25) - (sub_rect.h / 2);

    char num[2];
    sprintf(num, "%d", selectedSudokuSize);
    
    int num_w, num_h;
    SDL_Texture *rendered_num = RenderFont(MainRenderer, GetFont(), num, C_White, &num_w, &num_h);
    SDL_Rect num_rect;
    num_rect.h = targetHeight;
    num_rect.w = (int)(((float)num_rect.h / num_h) * num_w);
    num_rect.x = sub_rect.x + sub_rect.w + (MainWindowWidth * 0.01);
    num_rect.y = (MainWindowHeight * 0.25) - (num_rect.h / 2);

    char *add = ">";
    int add_w, add_h;
    SDL_Texture *rendered_add = RenderFont(MainRenderer, GetFont(), add, C_White, &add_w, &add_h);
    SDL_Rect add_rect;
    add_rect.h = targetHeight;
    add_rect.w = (int)(((float)add_rect.h / add_h) * add_w);
    add_rect.x = num_rect.x + num_rect.w + (MainWindowWidth * 0.01);;
    add_rect.y = (MainWindowHeight * 0.25) - (add_rect.h / 2);


    SetRenderDrawSDLColor(MainRenderer, C_DarkGreen);
    SDL_Rect bg_rect;
    bg_rect.w = (add_rect.x + add_rect.w) - info_rect.x;
    bg_rect.h = targetHeight + (MainWindowHeight * 0.01);
    bg_rect.x = info_rect.x;
    bg_rect.y = info_rect.y - (MainWindowHeight * 0.01);
    SDL_RenderFillRect(MainRenderer, &bg_rect);
    
    SetRenderDrawSDLColor(MainRenderer, C_Green);
    SDL_Rect sub_bg;
    sub_bg.w = sub_rect.w;
    sub_bg.h = targetHeight + (MainWindowHeight * 0.01);
    sub_bg.x = sub_rect.x;
    sub_bg.y = info_rect.y - (MainWindowHeight * 0.01);
    SDL_RenderFillRect(MainRenderer, &sub_bg);

    SDL_Rect add_bg;
    add_bg.w = add_rect.w;
    add_bg.h = targetHeight + (MainWindowHeight * 0.01);
    add_bg.x = add_rect.x;
    add_bg.y = info_rect.y - (MainWindowHeight * 0.01);
    SDL_RenderFillRect(MainRenderer, &add_bg);

    if (SDL_PointInRect(&cursorClickPos, &sub_bg)) {
        selectedSudokuSize--;
        if (selectedSudokuSize < MIN_SUDOKUSIZE) selectedSudokuSize++;
    }

    if (SDL_PointInRect(&cursorClickPos, &add_bg)) {
        selectedSudokuSize++;
        if (selectedSudokuSize > MAX_SUDOKUSIZE) selectedSudokuSize--;
    }

    SDL_RenderCopy(MainRenderer, rendered_info, NULL, &info_rect);
    SDL_DestroyTexture(rendered_info);

    SDL_RenderCopy(MainRenderer, rendered_sub, NULL, &sub_rect);
    SDL_DestroyTexture(rendered_sub);

    SDL_RenderCopy(MainRenderer, rendered_num, NULL, &num_rect);
    SDL_DestroyTexture(rendered_num);

    SDL_RenderCopy(MainRenderer, rendered_add, NULL, &add_rect);
    SDL_DestroyTexture(rendered_add);

}

static void RenderDifficultySelector(){
    char *text = "Easy: ";
    int render_w, render_h;
    SDL_Texture *rendered_text = RenderFont(MainRenderer, GetFont(), text, C_White, &render_w, &render_h);
    SDL_Rect rect;
    rect.w = MainWindowWidth * 0.13;
    rect.h = (int)(((float)rect.w / render_w) * render_h);
    rect.x = (MainWindowWidth * 0.5) - (rect.w / 2);
    rect.y = (MainWindowHeight * 0.9) - (rect.h / 2);

    SDL_DestroyTexture(rendered_text);
}


static void RenderCheatSelector(){
    
}
static void RenderStartButton(){
    char *text = "Play";
    int render_w, render_h;
    SDL_Texture *rendered_text = RenderFont(MainRenderer, GetFont(), text, C_White, &render_w, &render_h);
    SDL_Rect rect;
    rect.w = MainWindowWidth * 0.13;
    rect.h = (int)(((float)rect.w / render_w) * render_h);
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
    }
}


void MainMenu_MainLoop(SDL_Point cursorPos){
    cursorClickPos = cursorPos;

    SetRenderDrawSDLColor(MainRenderer, C_Black);
    SDL_RenderClear(MainRenderer);

    RenderTitle();
    RenderSudokuSizeSelector();
    RenderDifficultySelector();
    RenderCheatSelector();
    RenderStartButton();
}