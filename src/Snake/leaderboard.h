#pragma once

#include "cprocessing.h"
#include "score.h"
#include <stdio.h>

typedef struct Leader
{
	char name[30];
	int score;
} Leader;

void Read_Leaderboard_Score(void);
void Write_Leaderboard_Score(void);