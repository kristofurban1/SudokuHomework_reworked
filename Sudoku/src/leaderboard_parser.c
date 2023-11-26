#include "leaderboard_parser.h"

static struct Leaderboard_Entry* FilterEntries(struct Leaderboard_Entry* entries, int entrycount, int *entrycount_out, int b_size, int diff, int cheats){

    struct Leaderboard_Entry* filtered = malloc(sizeof(struct Leaderboard_Entry) * entrycount);
        malloc_verify(filtered);
    int found = 0;

    for (int i = 0; i < entrycount; i++)
    {
        if (
            entries[i].BoardSize        == b_size &&
            entries[i].u16Difficulty    == diff &&
            entries[i].u16CheatLevel    == cheats
        ) {
            filtered[found] = entries[i];
            found++;
        }
    }

    filtered = realloc(filtered, sizeof(struct Leaderboard_Entry) * found);

    *entrycount_out = found;
    return filtered;
}

static void SortEntries(struct Leaderboard_Entry* entries, int entrycount){
    int start = 0;
    while (start < entrycount -1)
    {
        int min = entrycount-1;
        for (int i = start; i < entrycount; i++)
            if (entries[i].Seconds < entries[min].Seconds) min = i;
        
        if (min == start) {
            start++;
            continue;
        }
        
        struct Leaderboard_Entry swp = entries[min];
        entries[min] = entries[start];
        entries[start] = swp;
        start++;
    }
    
}

extern struct Leaderboard_Entry* GetAndOrderLeaderboardEntries(int *entrycount_out, int b_size, int diff, int cheats){
    int entryCount;
    struct Leaderboard_Entry *entires = ReadLeaderboard(&entryCount);
    if (entryCount == 0){
        *entrycount_out = entryCount;
        return entires;
    }


    int filtered_count;
    struct Leaderboard_Entry *filtered = FilterEntries(entires, entryCount, &filtered_count, b_size, diff, cheats);
    free(entires);

    SortEntries(filtered, filtered_count);

    *entrycount_out = filtered_count;
    return filtered;
}