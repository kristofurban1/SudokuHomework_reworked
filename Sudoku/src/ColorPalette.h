#ifndef COLORPALETTE_DEF
#define COLORPALETTE_DEF


#include <SDL2/SDL.h>

#define COLOR_Green         {102, 255, 0, 250}
#define COLOR_DarkGreen     {70, 200, 30, 100}
#define COLOR_White         {255, 255, 255, 255}
#define COLOR_Gray          {80, 80, 80, 255}
#define COLOR_DarkGray      {20, 20, 20, 255}
#define COLOR_Black         {0, 0, 0, 255}
#define COLOR_Red           {255, 30, 30, 255}
#define COLOR_Yellow        {255, 255, 30, 255}

extern SDL_Color C_Green;
extern SDL_Color C_DarkGreen;
extern SDL_Color C_White;
extern SDL_Color C_Gray;
extern SDL_Color C_DarkGray;
extern SDL_Color C_Black;
extern SDL_Color C_Red;
extern SDL_Color C_Yellow;


extern void SetRenderDrawSDLColor(SDL_Renderer *renderer, SDL_Color color);

#endif