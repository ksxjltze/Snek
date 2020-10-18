#pragma once
#include "cprocessing.h"
#include <stdbool.h>

void Snake_Grid_Init();
void Snake_SetGrid(CP_Vector grid[]);
void Snake_SetBoundary(CP_Vector grid[], CP_Vector boundary[]);
bool Snake_CheckBoundary(CP_Vector position, int direction, CP_Vector boundary[]);
void Snake_DrawBoundary(CP_Vector boundary[]);
void Snake_DrawGrid();
