#ifndef FontManager_DEF
#define FontManager_DEF

#include "ErrorHandler.h"
#include "file_handler.h"

#include "debugmalloc.h"

#include <SDL2/SDL_ttf.h>

#define FontSize 500

/*
    @brief Renders texture of text with given font and color.
    @param renderer Pointer to SDL_Renderer.
    @param font Pointer to TTF font.
    @param text Zero-Terminated string to render.
    @param fg Frontground color of text.
    @param width Pointer to return width of texture.
    @param height Pointer to return height of texture.
*/
extern SDL_Texture *RenderFont(SDL_Renderer *renderer, TTF_Font *font, char *text, SDL_Color fg, int *width, int *height);

/*
    @brief Returns loaded TTF font.
*/
extern TTF_Font *GetFont();

/*
    @brief Initializes font manager, loads default font (Accessable by GetFont).
*/
extern void FontManager_Init();

#endif