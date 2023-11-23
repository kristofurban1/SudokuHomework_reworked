#include "ColorPalette.h"

SDL_Color C_Green       = COLOR_Green;
SDL_Color C_DarkGreen   = COLOR_DarkGreen;
SDL_Color C_White       = COLOR_White;
SDL_Color C_Gray        = COLOR_Gray;
SDL_Color C_DarkGray    = COLOR_DarkGray;
SDL_Color C_Black       = COLOR_Black;
SDL_Color C_Red         = COLOR_Red;
SDL_Color C_Yellow      = COLOR_Yellow;

void SetRenderDrawSDLColor(SDL_Renderer *renderer, SDL_Color color){
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}