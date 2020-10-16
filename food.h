#pragma once
#include "cprocessing.h"
#include "sprite.h"

struct Food
{
	struct Sprite sprite;
	CP_Vector position;
	int grid_pos;
};

void food_init(struct Food* food);
void food_eaten(struct Food* food);