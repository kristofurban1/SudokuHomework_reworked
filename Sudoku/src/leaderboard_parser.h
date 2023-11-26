#ifndef LeaderboardParser_DEF
#define LeaderboardParser_DEF

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "ErrorHandler.h"
#include "datastructures.h"
#include "file_handler.h"

/*
    @brief Filters and orders leaderboard entries.
    @description leaderboard is stored by appending newest entry to end, 
        so there is a need to filter to current game setting, and order by ascenting time.
    @param entrycount_out Returns the number of entries in sorted and filtered array.
    @param b_size Size of sudoku board to filter by.
    @param diff Difficulty of game to filter by.
    @param cheats Cheats to filter by.

    @returns Leaderboard entry array that is filtered and sorted.
*/
extern struct Leaderboard_Entry* GetAndOrderLeaderboardEntries(int *entrycount_out, int b_size, int diff, int cheats);

#endif