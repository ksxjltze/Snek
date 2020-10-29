#pragma once
#include "cprocessing.h"
#include <stdio.h>
#include "snake.h"
#include "score.h"

//Draw
void food_Draw(void);

void init_food(CP_Vector grid[]);

void food_update(CP_Vector grid[]);

void collision(CP_Vector position , CP_Vector grid[]);