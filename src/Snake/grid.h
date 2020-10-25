#pragma once
#include "cprocessing.h"
#include <stdbool.h>

void Snake_Grid_Init();
void Snake_SetGrid(CP_Vector grid[]);
void Snake_DrawGrid();
void Snake_DrawGrid_Truncated();
void Colour_Boundary();
