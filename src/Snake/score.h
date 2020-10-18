#pragma once
#include "cprocessing.h"
#include <stdio.h>
struct Timer
{
	//const char* time;
	float count;
	float x;
	float y;
	CP_Color text;
}timer;

void init_timer(void);
//void init_foodscore(void);
void init_score(void);
void update_score(void);
void exit_score(void);