#include "file_handler.h"

char *BasePath;

bool FileExists(const char *filename){
    FILE *fp = fopen(filename, "r");
    if (fp != NULL){
        fclose(fp);
        return true;
    }
    return false;
}

char *AppendToBasePath(char *endOfPath, char *basePath){
    int eop_len  = strlen(endOfPath);
    int base_len = strlen(basePath);

    char *final = malloc((eop_len + base_len + 1) * sizeof(char));

    strcpy(final, basePath);
    strcat(final, endOfPath);
    
    return final;
}

void WriteLeaderboard(struct Leaderboard_Entry *entries, int entryCount){
    char *pszLeaderboardPath = AppendToBasePath(PATH_LEADERBOARD, BasePath);
    FILE *fp = fopen(pszLeaderboardPath, "w");
    free(pszLeaderboardPath);
    fwrite(&entryCount, sizeof(int), 1, fp);
    fwrite(entries, sizeof(Leaderboard_Entry), entryCount, fp);
    fclose(fp);
}

struct Leaderboard_Entry *ReadLeaderboard(int *entryCount_out){
    char *pszLeaderboardPath = AppendToBasePath(PATH_LEADERBOARD, BasePath);
    FILE *fp = fopen(pszLeaderboardPath, "r");
    free(pszLeaderboardPath);

    int entryCount;
    fread(&entryCount, sizeof(int), 1, fp);

    struct Leaderboard_Entry *entries;
        entries = malloc(sizeof(Leaderboard_Entry) * entryCount);
        SetErrorIndentfyer("file_handler: ReadLeaderboard"); malloc_verify(entries);
    
    fread(entries, sizeof(Leaderboard_Entry), entryCount, fp);
    fclose(fp);
    entryCount_out = &entryCount;
    return entries;
}

void FileHandler_Init(){
    BasePath = SDL_GetBasePath();


    char *dataFolder = AppendToBasePath(DIR_DATA, BasePath);
    mkdir(dataFolder);
    free(dataFolder);

    char *pszLeaderboardPath = AppendToBasePath(PATH_LEADERBOARD, BasePath);
    if (!FileExists(pszLeaderboardPath)){
        WriteLeaderboard(NULL, 0);
    }
    free(pszLeaderboardPath);
}

char *GetAsset(char* assetName){
    char *pszAssetFolder = AppendToBasePath(DIR_ASSETS, BasePath);
    char *pszAssetPath = AppendToBasePath(assetName, pszAssetFolder);
    free(pszAssetFolder);

    return pszAssetPath;
}