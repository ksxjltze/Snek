#pragma once
#include "cprocessing.h"
#include <stdio.h>
#include "gameover.h"


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

void init_timerscore(void);
void init_foodscore(void);
void init_score(void);
void update_score(void);
void exit_score(void);