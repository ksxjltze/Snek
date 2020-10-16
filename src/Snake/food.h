#pragma once
#include "cprocessing.h"
#include "sprite.h"

struct Food
{
	struct Sprite sprite;
	CP_Vector position;
	int grid_pos;
};

void Food_Init(struct Food* food, CP_Image sprite, CP_Vector grid[]);
void Food_Update(struct Food* food);
void Food_Draw(struct Food food);
void Food_Eaten(struct Food* food);