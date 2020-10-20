#pragma once
#include "cprocessing.h"
#include "globals.h"
#include "sprite.h"
#include <stdbool.h>

CP_Vector Random_Pos()
{
	return CP_Vector_Set(CP_Random_RangeFloat(0, (float)WINDOW_WIDTH), CP_Random_RangeFloat(0, (float)WINDOW_HEIGHT));
}

int Random_Grid_Pos()
{
	return CP_Random_RangeInt(0, GRID_SIZE);
}

//Helper function for setting sprite size.
void Set_Sprite_Size(struct Sprite* sprite)
{
	CP_Image image = sprite->image;
	sprite->width = (float)CP_Image_GetWidth(image);
	sprite->height = (float)CP_Image_GetHeight(image);
}

//Helper function for determining if mouse is over object (Rect).
//Object position must start at top left corner.
bool isMouseOver_Rect(CP_Vector position, float width, float height, float mouseX, float mouseY)
{
	bool left = position.x <= mouseX;
	bool right = position.x + width >= mouseX;
	bool top = position.y <= mouseY;
	bool bottom = position.y + height >= mouseY;

	return left && right && top && bottom;
}