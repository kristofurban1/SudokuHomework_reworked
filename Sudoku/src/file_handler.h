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

/*
    @attention Must call before file operations.
    @brief Initializes FileHandler, such as creating required files if they don't exist.
*/
extern void FileHandler_Init();

/*
    @brief Returns default savedata.
*/
extern struct SaveData *GetDefaultSaveData();

/*
    @brief Reads Savedata file.
    @returns SaveData struct (found in datastructures.h)
*/
extern struct SaveData *ReadSaveData();

/*
    @brief Writes savedata
    @param data SaveData struct (found in datastructures.h)
*/
extern void WriteSaveData(struct SaveData *data);

/*
    @brief Reads Leaderboard
    @param entryCount_out Pointer to intiger to store number of entries returned.
    @returns Leaderboard_Entry array, (found in datastructures.h)
*/
extern struct Leaderboard_Entry *ReadLeaderboard(int *entryCount_out);

/*
    @brief Reads Leaderboard
    @param entryCount_out Number of entries.
    @param entries Leaderboard_Entry array, (found in datastructures.h)
*/
extern void WriteLeaderboard(struct Leaderboard_Entry *entries, int entryCount);

/*
    @brief Returns path to asset based on name.
    @param assetName Name of the asset, for example imgage.png
    @returns Full path to specified asset.
*/
extern char *GetAsset(char* assetName);

#endif