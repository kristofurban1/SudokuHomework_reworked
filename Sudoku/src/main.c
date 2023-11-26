#include "main.h"

#define SHOW_SCREEN_DIV false

int MainWindowWidth  = Default_WIDTH;
int MainWindowHeight = Default_HEIGHT;
SDL_Window *MainWindow      = NULL;
SDL_Renderer *MainRenderer  = NULL;

extern int main(int argc, char *argv[]) {
    srand(time(NULL));

    INITIALIZE_ALL();   // SDL
    FileHandler_Init(); // FileHandler
    FontManager_Init(); // FontManager
    Gamestate_Init();   // Gamestate
    
    SDL_SetWindowTitle(MainWindow, WINDOW_TITLE);
    char *icon_path = GetAsset(ASSET_ICON);
    SDL_Surface *icon = IMG_Load(icon_path);
    SDL_SetWindowIcon(MainWindow, icon);
    SDL_FreeSurface(icon);
    free(icon_path);

    struct SaveData* sd = ReadSaveData();
    if (sd->u16CheatLevel < 0 || sd->u16CheatLevel > 7 ) sd->u16CheatLevel = 0;
    if (sd->u16Difficulty < 0 || sd->u16Difficulty > 3 ) sd->u16Difficulty = 0;
    if (sd->BoardSize < MIN_SUDOKUSIZE || sd->BoardSize > MAX_SUDOKUSIZE ) sd->BoardSize = 3;
    MM_SetValues(sd->BoardSize, sd->u16Difficulty, sd->u16CheatLevel);
    MainWindowWidth  = (sd->WindowWidth < Minimum_Width || sd->WindowWidth > Maximum_Width ? Default_WIDTH : sd->WindowWidth);
    MainWindowHeight = (sd->WindowHeight < Minimum_Heigth ? Default_HEIGHT : sd->WindowHeight);
    SDL_SetWindowSize(MainWindow, sd->WindowWidth, sd->WindowHeight);
    free(sd);

    

    SetGameState(GS_TitleScreen);
    SetSudokuState(GS_UNSET);

    SDL_Scancode keypress = SDL_SCANCODE_UNKNOWN;
    SDL_Point cursorClick = {-1, -1};

    SetTitleScreenTimer(1500);

    Uint64 timer_forceRender = 0;

    bool running = true;
    Uint64 deltaTime_ms = 0;
    Uint64 deltaPrev = SDL_GetTicks64();
    while(running){

        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                MainMenu_SaveData();
                    FreeBoards();
                    running = false;
                    break;
                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                        bool changed = false;
                        if (event.window.data1 >= Minimum_Width && event.window.data1 <= Maximum_Width)
                            MainWindowWidth = event.window.data1;
                        else { 
                            if (event.window.data1 < Minimum_Width)
                                MainWindowWidth = Minimum_Width; 
                            else
                                MainWindowWidth = Maximum_Width;
                            changed = true; 
                        }
                        
                        if (event.window.data2 >= Minimum_Heigth)
                            MainWindowHeight = event.window.data2;
                        else { MainWindowHeight = Minimum_Heigth; changed = true; }


                        if (changed) SDL_SetWindowSize(MainWindow, MainWindowWidth, MainWindowHeight);
                    }

                    break;
                
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT){
                        printf("Mouse: LeftClick\n");
                        SDL_Point clickpos;
                        clickpos.x = event.button.x;
                        clickpos.y = event.button.y;
                        cursorClick = clickpos;
                    }
                    break;
                case SDL_KEYDOWN:
                    printf("Keyboard: Buttonpress: %d\n", event.key.keysym.scancode);
                    keypress = event.key.keysym.scancode;
                    break;

                default:
                    break;
            }
        }
        if (timer_forceRender + FPS < SDL_GetTicks64()){
            timer_forceRender = SDL_GetTicks64();

                
            deltaTime_ms = SDL_GetTicks64() - deltaPrev;
            deltaPrev = SDL_GetTicks64();

            #pragma region DrawScreen
            switch (GetGamestate())
            {
            case GS_TitleScreen:
                TitleScreen_MainLoop(deltaTime_ms);
                break;
            
            case GS_MainMenu:
                MainMenu_MainLoop(cursorClick);
                break;
            case GS_SudokuState:
                switch (GetSudokustate())
                    {
                    case GS_Sudoku:
                        SudokuInterface_MainLoop(cursorClick, keypress);
                        break;
                    case GS_SudokuEndScreen:
                        EndScreen_MainLoop(cursorClick, keypress);
                        break;                    
                    default:
                        SetErrorMessage("Unknown gamestate_sudoku"); SetErrorIndentfyer("main: SudokuState control");
                        RAISE_ERROR();
                        break;
                }
                break;
            
            default:
                SetErrorMessage("Unknown gamestate"); SetErrorIndentfyer("main: GameState control");
                RAISE_ERROR();
                break;
            }
            #pragma endregion

            if (SHOW_SCREEN_DIV){
                SDL_SetRenderDrawColor(MainRenderer, 50, 50, 50, 255);
                for (int i = 0; i <= 10; i++)
                {
                    float p = i * 0.1;
                    
                    SDL_RenderDrawLine(MainRenderer, (int)(MainWindowWidth * p), 0, (int)(MainWindowWidth * p), MainWindowHeight);
                    SDL_RenderDrawLine(MainRenderer, 0, (int)(MainWindowHeight * p), MainWindowWidth, (int)(MainWindowHeight * p));

                }
            }

            keypress = SDL_SCANCODE_UNKNOWN;
            cursorClick.x = -1;
            cursorClick.y = -1;

            SDL_RenderPresent(MainRenderer);
        }

        SDL_Delay(1);
    }

    TTF_CloseFont(GetFont());
    SDL_DestroyRenderer(MainRenderer);
    SDL_DestroyWindow(MainWindow);
    SDL_Quit();

    return 0;
}
