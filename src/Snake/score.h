#pragma once
#include "cprocessing.h"
#include <stdio.h>
#include "gameover.h"
#include "filemanager.h"


struct Score
{
	CP_Color text;
	float y;
	int total;
	int highscore;
}score;
struct Timer
{
	const char* text;
	float count;
	float offset;
	float x;
}Time_score;

struct Food_count
{
	const char* text;
	int count;
	float x;
}Food_score;

void Init_Timerscore(void);
void Init_Foodscore(void);
void Init_Score(void);
void Update_Score(void);
void Exit_Score(void);
void Highscore_Manager(int player_score);