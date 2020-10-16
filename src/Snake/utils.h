#pragma once
#include "cprocessing.h"
#include "globals.h"
#include "sprite.h"

CP_Vector Random_Pos()
{
	return CP_Vector_Set(CP_Random_RangeFloat(0, (float)WINDOW_WIDTH), CP_Random_RangeFloat(0, (float)WINDOW_HEIGHT));
}

int Random_Grid_Pos()
{
	return CP_Random_RangeInt(0, GRID_SIZE);
}

void Set_Sprite_Size(struct Sprite* sprite)
{
	CP_Image image = sprite->image;
	sprite->width = (float)CP_Image_GetWidth(image);
	sprite->height = (float)CP_Image_GetHeight(image);
}