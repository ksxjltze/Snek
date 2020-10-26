#pragma once
#include "cprocessing.h"
#include <stdbool.h>

void Snake_Grid_Init();
void Snake_SetGrid(CP_Vector grid[]);
void Snake_DrawGrid();
void Snake_DrawGrid_Truncated();
void Colour_Boundary();
void Snake_TruncateGrid(CP_Vector grid[], CP_Vector grid_truncated[]);
void Snake_DrawGridPositions(CP_Vector grid[], int size);
