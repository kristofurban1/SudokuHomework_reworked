#include "end_screen.h"

static SDL_Point cursorClickPos;

static void Render_PlayAgain(){
    char *text = "Play again";
    int render_w, render_h;
    SDL_Texture *rendered_text = RenderFont(MainRenderer, GetFont(), text, C_White, &render_w, &render_h);
    SDL_Rect rect;
    rect.h = MainWindowHeight * 0.05;
    rect.w = (int)(((float)rect.h / render_h) * render_w);;
    rect.x = (MainWindowWidth  * 0.97) - rect.w;
    rect.y = (MainWindowHeight * 0.99) - rect.h;

    SetRenderDrawSDLColor(MainRenderer, C_DarkGreen);
    SDL_Rect bg_rect;
    bg_rect.w = rect.w * 1.1;
    bg_rect.h = rect.h;
    bg_rect.x = (MainWindowWidth  * 0.97) - bg_rect.w + ((bg_rect.w - rect.w) / 2);
    bg_rect.y = rect.y - (rect.h * 0.1);
    SDL_RenderFillRect(MainRenderer, &bg_rect);

    SDL_RenderCopy(MainRenderer, rendered_text, NULL, &rect);
    SDL_DestroyTexture(rendered_text);

    if (SDL_PointInRect(&cursorClickPos, &bg_rect)){
        printf("EndScreen: PlayAgainButtonClick\n");
        SetGameState(GS_SudokuState);
        SetSudokuState(GS_Sudoku);
        struct SaveData *sd = ReadSaveData();
        GenerateSudoku(sd->BoardSize, sd->u16Difficulty, sd->u16CheatLevel & 1, sd->u16CheatLevel >> 1);
    } 
}
static void Render_BackToMenu(){
    char *text = "Back to Menu";
    int render_w, render_h;
    SDL_Texture *rendered_text = RenderFont(MainRenderer, GetFont(), text, C_White, &render_w, &render_h);
    SDL_Rect rect;
    rect.h = MainWindowHeight * 0.05;
    rect.w = (int)(((float)rect.h / render_h) * render_w);;
    rect.x = (MainWindowWidth  * 0.03);
    rect.y = (MainWindowHeight * 0.99) - rect.h;

    SetRenderDrawSDLColor(MainRenderer, C_DarkGreen);
    SDL_Rect bg_rect;
    bg_rect.w = rect.w * 1.1;
    bg_rect.h = rect.h;
    bg_rect.x = (MainWindowWidth  * 0.03) - ((bg_rect.w - rect.w) / 2);
    bg_rect.y = rect.y - (rect.h * 0.1);
    SDL_RenderFillRect(MainRenderer, &bg_rect);

    SDL_RenderCopy(MainRenderer, rendered_text, NULL, &rect);
    SDL_DestroyTexture(rendered_text);

    if (SDL_PointInRect(&cursorClickPos, &bg_rect)){
        printf("EndScreen: PlayAgainButtonClick\n");
        SetGameState(GS_MainMenu);
        SetSudokuState(GS_UNSET);
    } 
}

static void RenderLeaderboard(){
    struct SaveData *sd = ReadSaveData();

    int entryCount;
    struct Leaderboard_Entry *entries =  GetAndOrderLeaderboardEntries(&entryCount, sd->BoardSize, sd->u16Difficulty, sd->u16CheatLevel);
    free(sd);

    //leaderboard: 0.1 - 0.5 x 0.1 - 0.8
    SDL_Rect lb_bg;
    SetRenderDrawSDLColor(MainRenderer, C_DarkGray);
    lb_bg.x = MainWindowWidth * 0.1;
    lb_bg.y = MainWindowHeight * 0.1;
    lb_bg.w = (MainWindowWidth * 0.5) - (MainWindowWidth * 0.1);
    lb_bg.h = (MainWindowHeight * 0.8) - (MainWindowHeight * 0.1);
    SDL_RenderFillRect(MainRenderer, &lb_bg);
    
    char entryCount_text[30];
    sprintf(entryCount_text, "Number of entries: %d", entryCount);
    int render_w_ec, render_h_ec;
    SDL_Texture *rendered_text_ec = RenderFont(MainRenderer, GetFont(), entryCount_text, C_White, &render_w_ec, &render_h_ec);
    SDL_Rect rect_ec;
    rect_ec.w = MainWindowWidth * 0.3;
    rect_ec.h = (int)(((float)rect_ec.w / render_w_ec) * render_h_ec);;
    rect_ec.x = (MainWindowWidth  * 0.55);
    rect_ec.y = (MainWindowHeight * 0.3) - rect_ec.h;

    SDL_RenderCopy(MainRenderer, rendered_text_ec, NULL, &rect_ec);
    SDL_DestroyTexture(rendered_text_ec);
    
    char avg_text[30];

    if (entryCount == 0){
        sprintf(avg_text, "Avarage time: NaN");
    }
    else{
        int secSum = 0;
        for (int i = 0; i < entryCount; i++)
            secSum += entries[i].Seconds;

        int totalSeconds = secSum / entryCount;
        int totalMinutes = totalSeconds / 60;

        int seconds = totalSeconds % 60;
        int minutes = totalMinutes % 60;
        int hours = totalMinutes / 60;


        char  secs[3];
        char  mins[3];
        char   hrs[3];
        sprintf( secs, "%d%d", seconds / 10, seconds % 10);
        sprintf( mins, "%d%d", minutes / 10, minutes % 10);
        sprintf(  hrs, "%d%d", hours / 10, hours % 10);

        sprintf(avg_text, "Avarage time: %s:%s:%s", hrs, mins, secs);
    }


    int render_w_avg, render_h_avg;
    SDL_Texture *rendered_text_avg = RenderFont(MainRenderer, GetFont(), avg_text, C_White, &render_w_avg, &render_h_avg);
    SDL_Rect rect_avg;
    rect_avg.w = MainWindowWidth * 0.3;
    rect_avg.h = (int)(((float)rect_avg.w / render_w_avg) * render_h_avg);;
    rect_avg.x = (MainWindowWidth  * 0.55);
    rect_avg.y = (MainWindowHeight * 0.6) - rect_avg.h;

    SDL_RenderCopy(MainRenderer, rendered_text_avg, NULL, &rect_avg);
    SDL_DestroyTexture(rendered_text_avg);

    if (entryCount == 0) {

        return;
    }
    

    int table_height = lb_bg.h * 0.98;
    int shown_entries = 15;
    float entry_height = (float)table_height / shown_entries;

    for (int i = 0; i < entryCount && i < shown_entries; i++)
    {
        int totalSeconds = entries[i].Seconds;
        int totalMinutes = totalSeconds / 60;

        int seconds = totalSeconds % 60;
        int minutes = totalMinutes % 60;
        int hours = totalMinutes / 60;

        int id = i + 1;

        char  secs[3];
        char  mins[3];
        char   hrs[3];
        char idchr[3];
        sprintf( secs, "%d%d", seconds / 10, seconds % 10);
        sprintf( mins, "%d%d", minutes / 10, minutes % 10);
        sprintf(  hrs, "%d%d", hours / 10, hours % 10);
        sprintf(idchr, "%d%d", id / 10, id % 10);

        

        char text[30];
        printf("test\n");
        sprintf(text, "%s. %s:%s:%s", idchr, hrs, mins, secs);
        int render_w, render_h;
        SDL_Texture *rendered_text = RenderFont(MainRenderer, GetFont(), text, C_White, &render_w, &render_h);
        SDL_Rect rect;
        rect.h = (int)entry_height;
        rect.w = (int)(((float)rect.h / render_h) * render_w);;
        rect.x = lb_bg.x + (lb_bg.w * 0.03);
        rect.y = lb_bg.y + (lb_bg.h * 0.01) + (int)(entry_height * i);

        SDL_RenderCopy(MainRenderer, rendered_text, NULL, &rect);
        SDL_DestroyTexture(rendered_text);
    }
    


    free(entries);
}

extern void EndScreen_MainLoop(SDL_Point cursorClick, SDL_Scancode keypress){
    cursorClickPos = cursorClick;

    SetRenderDrawSDLColor(MainRenderer, C_Black);
    SDL_RenderClear(MainRenderer);

    Render_PlayAgain();
    Render_BackToMenu();

    RenderLeaderboard();
}