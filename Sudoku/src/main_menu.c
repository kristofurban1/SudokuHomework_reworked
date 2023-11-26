#include "main_menu.h"

static int selectedSudokuSize = 3;
static int selectedDifficulty = 0;
static bool selectedHighlight = false;
static int selectedCheatLevel = 0;

static SDL_Point cursorClickPos;

extern void MM_SetValues(int size, int diff, int cheatlvl){
    selectedSudokuSize = size;
    selectedDifficulty = diff;
    selectedHighlight  = cheatlvl & 1;
    selectedCheatLevel = cheatlvl >> 1;
}

extern void MM_GetValues(int *size, int *diff, int *cheatlvl){
    *size = selectedSudokuSize;
    *diff = selectedDifficulty;

    *cheatlvl = (selectedHighlight & 1) | (selectedCheatLevel << 1);
}

extern void MainMenu_SaveData(){
    struct SaveData sd;
    sd.WindowWidth = MainWindowWidth;
    sd.WindowHeight = MainWindowHeight;
    int d, c;
    MM_GetValues(&sd.BoardSize, &d, &c);
    sd.u16Difficulty = d;
    sd.u16CheatLevel = c;
    WriteSaveData(&sd);
}

static void RenderTitle(){
    char *text = TITLE_TEXT;
    int render_w, render_h;
    SDL_Texture *rendered_text = RenderFont(MainRenderer, GetFont(), text, C_Green, &render_w, &render_h);
    SDL_Rect rect;
    rect.w = MainWindowWidth * 0.3;
    rect.h = (int)(((float)rect.w / render_w) * render_h);
    rect.x = (MainWindowWidth * 0.5) - (rect.w / 2);
    rect.y = (MainWindowHeight * 0.02);

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
    info_rect.x = (MainWindowWidth * 0.1);
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
    char easy_text[30];
    sprintf(easy_text, "[%c] Easy", selectedDifficulty == 0 ? 'x' : '-');
    int render_w_e, render_h_e;
    SDL_Texture *rendered_text_e = RenderFont(MainRenderer, GetFont(), easy_text, C_White, &render_w_e, &render_h_e);
    SDL_Rect e_rect;
    e_rect.h = MainWindowHeight * 0.05;
    e_rect.w = (int)(((float)e_rect.h / render_h_e) * render_w_e);
    e_rect.x = (MainWindowWidth * 0.1);
    e_rect.y = (MainWindowHeight * 0.35);

    char medium_text[30];
    sprintf(medium_text, "[%c] Medium", selectedDifficulty == 1 ? 'x' : '-');
    int render_w_m, render_h_m;
    SDL_Texture *rendered_text_m = RenderFont(MainRenderer, GetFont(), medium_text, C_White, &render_w_m, &render_h_m);
    SDL_Rect m_rect;
    m_rect.h = MainWindowHeight * 0.05;
    m_rect.w = (int)(((float)m_rect.h / render_h_m) * render_w_m);
    m_rect.x = (MainWindowWidth * 0.1);
    m_rect.y = e_rect.y + e_rect.h + (MainWindowHeight * 0.01);

    char hard_text[30];
    sprintf(hard_text, "[%c] Hard", selectedDifficulty == 2 ? 'x' : '-');
    int render_w_h, render_h_h;
    SDL_Texture *rendered_text_h = RenderFont(MainRenderer, GetFont(), hard_text, C_White, &render_w_h, &render_h_h);
    SDL_Rect h_rect;
    h_rect.h = MainWindowHeight * 0.05;
    h_rect.w = (int)(((float)h_rect.h / render_h_h) * render_w_h);
    h_rect.x = (MainWindowWidth * 0.1);
    h_rect.y = m_rect.y + m_rect.h + (MainWindowHeight * 0.01);

    char extreme_text[30];
    sprintf(extreme_text, "[%c] Extreme", selectedDifficulty == 3 ? 'x' : '-');
    int render_w_ex, render_h_ex;
    SDL_Texture *rendered_text_ex = RenderFont(MainRenderer, GetFont(), extreme_text, C_White, &render_w_ex, &render_h_ex);
    SDL_Rect ex_rect;
    ex_rect.h = MainWindowHeight * 0.05;
    ex_rect.w = (int)(((float)ex_rect.h / render_h_ex) * render_w_ex);
    ex_rect.x = (MainWindowWidth * 0.1);
    ex_rect.y = h_rect.y + h_rect.h + (MainWindowHeight * 0.01);

    
    SetRenderDrawSDLColor(MainRenderer, C_DarkGreen);
    SDL_Rect bg_rect_e;
    bg_rect_e.w = e_rect.w;
    bg_rect_e.h = e_rect.h;
    bg_rect_e.x = e_rect.x;
    bg_rect_e.y = e_rect.y - (e_rect.h * 0.1);
    SDL_RenderFillRect(MainRenderer, &bg_rect_e);
    
    SetRenderDrawSDLColor(MainRenderer, C_DarkGreen);
    SDL_Rect bg_rect_m;
    bg_rect_m.w = m_rect.w;
    bg_rect_m.h = m_rect.h;
    bg_rect_m.x = m_rect.x;
    bg_rect_m.y = m_rect.y - (m_rect.h * 0.1);
    SDL_RenderFillRect(MainRenderer, &bg_rect_m);
    
    SetRenderDrawSDLColor(MainRenderer, C_DarkGreen);
    SDL_Rect bg_rect_h;
    bg_rect_h.w = h_rect.w;
    bg_rect_h.h = h_rect.h;
    bg_rect_h.x = h_rect.x;
    bg_rect_h.y = h_rect.y - (h_rect.h * 0.1);
    SDL_RenderFillRect(MainRenderer, &bg_rect_h);
    
    SetRenderDrawSDLColor(MainRenderer, C_DarkGreen);
    SDL_Rect bg_rect_ex;
    bg_rect_ex.w = ex_rect.w;
    bg_rect_ex.h = ex_rect.h;
    bg_rect_ex.x = ex_rect.x;
    bg_rect_ex.y = ex_rect.y - (ex_rect.h * 0.1);
    SDL_RenderFillRect(MainRenderer, &bg_rect_ex);

    SDL_RenderCopy(MainRenderer, rendered_text_e, NULL, &e_rect);
    SDL_DestroyTexture(rendered_text_e);
    
    SDL_RenderCopy(MainRenderer, rendered_text_m, NULL, &m_rect);
    SDL_DestroyTexture(rendered_text_m);

    SDL_RenderCopy(MainRenderer, rendered_text_h, NULL, &h_rect);
    SDL_DestroyTexture(rendered_text_h);
    
    SDL_RenderCopy(MainRenderer, rendered_text_ex, NULL, &ex_rect);
    SDL_DestroyTexture(rendered_text_ex);

    if (SDL_PointInRect(&cursorClickPos, &bg_rect_e))  selectedDifficulty = 0;
    if (SDL_PointInRect(&cursorClickPos, &bg_rect_m))  selectedDifficulty = 1;
    if (SDL_PointInRect(&cursorClickPos, &bg_rect_h))  selectedDifficulty = 2;
    if (SDL_PointInRect(&cursorClickPos, &bg_rect_ex)) selectedDifficulty = 3;

}


static void RenderCheatSelector(){
    char hl_text[30];
    sprintf(hl_text, "[%c] Highlight", selectedHighlight ? 'x' : '-');
    int render_w_hl, render_h_hl;
    SDL_Texture *rendered_text_hl = RenderFont(MainRenderer, GetFont(), hl_text, C_White, &render_w_hl, &render_h_hl);
    SDL_Rect hl_rect;
    hl_rect.h = MainWindowHeight * 0.05;
    hl_rect.w = (int)(((float)hl_rect.h / render_h_hl) * render_w_hl);
    hl_rect.x = (MainWindowWidth * 0.6);
    hl_rect.y = (MainWindowHeight * 0.35);

    char lim_text[30];
    sprintf(lim_text, "[%c] Limited helps (3)", selectedCheatLevel == 1 ? 'x' : '-');
    int render_w_lim, render_h_lim;
    SDL_Texture *rendered_text_lim = RenderFont(MainRenderer, GetFont(), lim_text, C_White, &render_w_lim, &render_h_lim);
    SDL_Rect lim_rect;
    lim_rect.h = MainWindowHeight * 0.05;
    lim_rect.w = (int)(((float)lim_rect.h / render_h_lim) * render_w_lim);
    lim_rect.x = (MainWindowWidth * 0.6);
    lim_rect.y = hl_rect.y + hl_rect.h + (MainWindowHeight * 0.01);

    char unl_text[30];
    sprintf(unl_text, "[%c] Unlimited helps", selectedCheatLevel == 2 ? 'x' : '-');
    int render_w_unl, render_h_unl;
    SDL_Texture *rendered_text_unl = RenderFont(MainRenderer, GetFont(), unl_text, C_White, &render_w_unl, &render_h_unl);
    SDL_Rect unl_rect;
    unl_rect.h = MainWindowHeight * 0.05;
    unl_rect.w = (int)(((float)unl_rect.h / render_h_unl) * render_w_unl);
    unl_rect.x = (MainWindowWidth * 0.6);
    unl_rect.y = lim_rect.y + lim_rect.h + (MainWindowHeight * 0.01);

    char auto_text[30];
    sprintf(auto_text, "[%c] Automatic helps",  selectedCheatLevel == 3 ? 'x' : '-');
    int render_w_auto, render_h_auto;
    SDL_Texture *rendered_text_auto = RenderFont(MainRenderer, GetFont(), auto_text, C_White, &render_w_auto, &render_h_auto);
    SDL_Rect auto_rect;
    auto_rect.h = MainWindowHeight * 0.05;
    auto_rect.w = (int)(((float)auto_rect.h / render_h_auto) * render_w_auto);
    auto_rect.x = (MainWindowWidth * 0.6);
    auto_rect.y = unl_rect.y + unl_rect.h + (MainWindowHeight * 0.01);

    
    SetRenderDrawSDLColor(MainRenderer, C_DarkGreen);
    SDL_Rect bg_rect_hl;
    bg_rect_hl.w = hl_rect.w;
    bg_rect_hl.h = hl_rect.h;
    bg_rect_hl.x = hl_rect.x;
    bg_rect_hl.y = hl_rect.y - (hl_rect.h * 0.1);
    SDL_RenderFillRect(MainRenderer, &bg_rect_hl);
    
    SetRenderDrawSDLColor(MainRenderer, C_DarkGreen);
    SDL_Rect bg_rect_lim;
    bg_rect_lim.w = lim_rect.w;
    bg_rect_lim.h = lim_rect.h;
    bg_rect_lim.x = lim_rect.x;
    bg_rect_lim.y = lim_rect.y - (lim_rect.h * 0.1);
    SDL_RenderFillRect(MainRenderer, &bg_rect_lim);
    
    SetRenderDrawSDLColor(MainRenderer, C_DarkGreen);
    SDL_Rect bg_rect_unl;
    bg_rect_unl.w = unl_rect.w;
    bg_rect_unl.h = unl_rect.h;
    bg_rect_unl.x = unl_rect.x;
    bg_rect_unl.y = unl_rect.y - (unl_rect.h * 0.1);
    SDL_RenderFillRect(MainRenderer, &bg_rect_unl);
    
    SetRenderDrawSDLColor(MainRenderer, C_DarkGreen);
    SDL_Rect bg_rect_auto;
    bg_rect_auto.w = auto_rect.w;
    bg_rect_auto.h = auto_rect.h;
    bg_rect_auto.x = auto_rect.x;
    bg_rect_auto.y = auto_rect.y - (auto_rect.h * 0.1);
    SDL_RenderFillRect(MainRenderer, &bg_rect_auto);

    SDL_RenderCopy(MainRenderer, rendered_text_hl, NULL, &hl_rect);
    SDL_DestroyTexture(rendered_text_hl);
    
    SDL_RenderCopy(MainRenderer, rendered_text_lim, NULL, &lim_rect);
    SDL_DestroyTexture(rendered_text_lim);

    SDL_RenderCopy(MainRenderer, rendered_text_unl, NULL, &unl_rect);
    SDL_DestroyTexture(rendered_text_unl);
    
    SDL_RenderCopy(MainRenderer, rendered_text_auto, NULL, &auto_rect);
    SDL_DestroyTexture(rendered_text_auto);

    if (SDL_PointInRect(&cursorClickPos, &bg_rect_hl))   selectedHighlight = !selectedHighlight;
    if (SDL_PointInRect(&cursorClickPos, &bg_rect_lim))  selectedCheatLevel = selectedCheatLevel == 1 ? 0 : 1;
    if (SDL_PointInRect(&cursorClickPos, &bg_rect_unl))  selectedCheatLevel = selectedCheatLevel == 2 ? 0 : 2;
    if (SDL_PointInRect(&cursorClickPos, &bg_rect_auto)) selectedCheatLevel = selectedCheatLevel == 3 ? 0 : 3;
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
        GenerateSudoku(selectedSudokuSize, selectedDifficulty, selectedHighlight, selectedCheatLevel);
        MainMenu_SaveData();
    }
}

static void RenderExitButton(){
    char *text = "X";
    int render_w, render_h;
    SDL_Texture *rendered_text = RenderFont(MainRenderer, GetFont(), text, C_White, &render_w, &render_h);
    SDL_Rect rect;
    rect.w = MainWindowWidth * 0.05;
    rect.h = rect.w;
    rect.x = MainWindowWidth - rect.w;
    rect.y = MainWindowHeight * 0.01;

    SetRenderDrawSDLColor(MainRenderer, C_Red);
    SDL_Rect bg_rect;
    bg_rect.w = rect.w * 1.1;
    bg_rect.h = rect.h;
    bg_rect.x = (MainWindowWidth) - (bg_rect.w);
    bg_rect.y = rect.y - (rect.h * 0.1);
    SDL_RenderFillRect(MainRenderer, &bg_rect);

    SDL_RenderCopy(MainRenderer, rendered_text, NULL, &rect);
    SDL_DestroyTexture(rendered_text);

    if (SDL_PointInRect(&cursorClickPos, &bg_rect)){
        printf("MainMenu: ExitButtonClick\n");
        SDL_Event e;
        e.type = SDL_QUIT;
        SDL_PushEvent(&e);
    }
}


extern void MainMenu_MainLoop(SDL_Point cursorPos){
    cursorClickPos = cursorPos;

    SetRenderDrawSDLColor(MainRenderer, C_Black);
    SDL_RenderClear(MainRenderer);

    RenderTitle();
    RenderSudokuSizeSelector();
    RenderDifficultySelector();
    RenderCheatSelector();
    RenderStartButton();
    RenderExitButton();
}