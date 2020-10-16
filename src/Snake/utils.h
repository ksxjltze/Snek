#pragma once
#include "cprocessing.h"
#include "globals.h"

CP_Vector Random_Pos()
{
	return CP_Vector_Set(CP_Random_RangeFloat(0, (float)WINDOW_WIDTH), CP_Random_RangeFloat(0, (float)WINDOW_HEIGHT));
}

int Random_Grid_Pos()
{
	return CP_Random_RangeInt(0, GRID_SIZE);
}