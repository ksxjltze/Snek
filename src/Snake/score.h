#pragma once
#include "cprocessing.h"
#include <stdio.h>
#include "gameover.h"
#include "file_manager.h"

struct Score
{
	CP_Color text;
	float y;
	int total;
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

void Init_Scores_Var(void);
void Update_Score(void);
void Exit_Score(void);
void Draw_Score(void);
void Score_Manager(void);