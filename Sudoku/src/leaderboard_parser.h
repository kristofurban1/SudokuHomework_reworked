#ifndef LeaderboardParser_DEF
#define LeaderboardParser_DEF

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "ErrorHandler.h"
#include "datastructures.h"
#include "file_handler.h"

extern struct Leaderboard_Entry* GetAndOrderLeaderboardEntries(int *entrycount_out, int b_size, int diff, int cheats);

#endif