/*
    File Handler


*/

#ifndef FILEHANDLER_DEF
#define FILEHANDLER_DEF


#include <stdio.h>
#include <stdbool.h>
#include <io.h>

#include <SDL2/SDL.h>

#include "datastructures.h"
#include "WINDOW_PARAMETERS.h"

#include "ErrorHandler.h"

#include "debugmalloc.h"

#define PATH_SAVEDATA       "data\\savedata.bin"
#define PATH_LEADERBOARD    "data\\leaderboard.bin"

#define DIR_DATA            "data\\"
#define DIR_ASSETS          "data\\assets\\"

#define ASSET_FONT          "font.ttf"
#define ASSET_ICON          "icon.png"

extern void FileHandler_Init();

extern struct SaveData *GetDefaultSaveData();

extern struct SaveData *ReadSaveData();

extern void WriteSaveData(struct SaveData *data);

extern struct Leaderboard_Entry *ReadLeaderboard(int *entryCount_out);

extern void WriteLeaderboard(struct Leaderboard_Entry *entries, int entryCount);

extern char *GetAsset(char* assetName);

#endif