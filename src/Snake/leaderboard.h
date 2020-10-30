#pragma once
#include "cprocessing.h"
#include "score.h"
#include <stdio.h>

typedef struct Leaders
{
	char* name;
	int score;
} Leader;

void Init_LeaderBoard(void);
void Update_LeaderBoard(void);
void Exit_LeaderBoard(void);

void Read_Leaderboard_Score(void);
void Write_Leaderboard_Score(void);
void Check_If_Leader(void);
void LeaderBoard_ReadInput();