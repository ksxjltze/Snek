#pragma once
#include "cprocessing.h"
#include <stdio.h>
#include "snake.h"

//Draw
void food_Draw(void);

void init_food(CP_Vector grid[]);

void food_update(void);

void collision(CP_Vector position);