#include "Init.h"


/*
    @brief Initalizes the SDL module.
    @attention Runs only once. Is included in INITIALIZE_ALL.
    @param flags SDL Subsystems to initialize.
*/
static void Init_SDL(Uint32 flags){
    SetErrorIndentfyer("SDL Initialization.");
    SDL_verify(SDL_Init(flags));
}

extern void Create_Window(SDL_Window **window, int WinPosX, int WinPosY, int Width, int Height, SDL_WindowFlags flags){
    *window = SDL_CreateWindow("SLD test", WinPosX, WinPosY, Width, Height, flags);
    SetErrorIndentfyer("SDL Window Creation.");
    SDL_ptr_verify(MainWindow);
}

extern void Create_Renderer(SDL_Window *target_window, SDL_Renderer **renderer, SDL_RendererFlags flags){
    *renderer = SDL_CreateRenderer(target_window, -1, flags);
    SetErrorIndentfyer("SDL Renderer Creation.");
    SDL_ptr_verify(renderer);
}


/*
    @brief Initalizes the TTF module.
    @attention Runs only once. Is included in INITIALIZE_ALL.
*/
static void Init_TTF(){
    SetErrorIndentfyer("TTF Initialization.");
    SDL_verify(TTF_Init());
}

/*
    @brief Initalizes the IMG module.
    @attention Runs only once. Is included in INITIALIZE_ALL.
*/
static void Init_IMG(){
    SetErrorIndentfyer("IMG Initialization.");
    SDL_verify(IMG_Init(IMG_INIT_PNG));
}

extern void INITIALIZE_ALL(){
    Init_SDL(SDL_FLAGS);
    Create_Window(&MainWindow, WindowPosX, WindowPosY, MainWindowWidth, MainWindowHeight, WindowFlags);
    Create_Renderer(MainWindow, &MainRenderer, RendererFlags);
    Init_TTF();
    Init_IMG();
    
}