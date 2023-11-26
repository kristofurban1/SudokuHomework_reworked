#include "ColorPalette.h"

extern SDL_Color C_Green       = COLOR_Green;
extern SDL_Color C_DarkGreen   = COLOR_DarkGreen;
extern SDL_Color C_White       = COLOR_White;
extern SDL_Color C_Gray        = COLOR_Gray;
extern SDL_Color C_DarkGray    = COLOR_DarkGray;
extern SDL_Color C_Black       = COLOR_Black;
extern SDL_Color C_Red         = COLOR_Red;
extern SDL_Color C_Yellow      = COLOR_Yellow;

extern void SetRenderDrawSDLColor(SDL_Renderer *renderer, SDL_Color color){
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}