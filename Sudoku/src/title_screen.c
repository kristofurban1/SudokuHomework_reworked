#include "title_screen.h"

static int TitleScreen_timer;

void SetTitleScreenTimer(int ms){
    TitleScreen_timer = ms;
}
void TitleScreen_MainLoop(Uint64 deltatime){
    TitleScreen_timer -= deltatime;
    if (TitleScreen_timer < 0) { SetGameState(GS_MainMenu); return; }

    SetRenderDrawSDLColor(MainRenderer, C_White);
    SDL_RenderClear(MainRenderer);

    char *text = TITLESCREEN_TEXT;
    int render_w, render_h;
    SDL_Texture *rendered_text = RenderFont(MainRenderer, GetFont(), text, C_Black, &render_w, &render_h);
    SDL_Rect rect;
    rect.w = MainWindowWidth * 0.5;
    rect.h = (int)(((float)rect.w / render_w) * render_h);
    rect.x = (MainWindowWidth / 2) - (rect.w / 2);
    rect.y = (MainWindowHeight / 2) - (rect.h / 2);

    SDL_RenderCopy(MainRenderer, rendered_text, NULL, &rect);
    
    SDL_DestroyTexture(rendered_text);

}