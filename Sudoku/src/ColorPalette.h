#ifndef COLORPALETTE_DEF
#define COLORPALETTE_DEF


#include <SDL2/SDL.h>

#define COLOR_Green         {102, 255, 0, 250}
#define COLOR_DarkGreen     {70, 200, 30, 100}
#define COLOR_White         {255, 255, 255, 255}
#define COLOR_Gray          {80, 80, 80, 255}
#define COLOR_DarkGray      {3, 3, 3, 100}
#define COLOR_Black         {0, 0, 0, 255}

extern SDL_Color C_Green;
extern SDL_Color C_DarkGreen;
extern SDL_Color C_White;
extern SDL_Color C_Gray;
extern SDL_Color C_DarkGray;
extern SDL_Color C_Black;

extern void SetRenderDrawSDLColor(SDL_Renderer *renderer, SDL_Color color);

#endif