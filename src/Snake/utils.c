//---------------------------------------------------------
// file:	utils.c
// author:	Lee Jia Keat
// email:	l.jiakeat@digipen.edu
//
// brief:	Useful functions
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------
#include "utils.h"

CP_Vector Random_Pos()
{
	return CP_Vector_Set(CP_Random_RangeFloat(0, (float)WINDOW_WIDTH), CP_Random_RangeFloat(0, (float)WINDOW_HEIGHT));
}

int Random_Grid_Pos()
{
	return CP_Random_RangeInt(0, GRID_SIZE);
}

//Generates grid position inside of boundary.
int Random_Snake_Grid_Pos()
{
	int pos = CP_Random_RangeInt(GRID_WIDTH, GRID_SIZE - GRID_WIDTH);	//Top and bottom boundary
	while (pos % GRID_WIDTH == 0 || pos % GRID_WIDTH == GRID_WIDTH - 1)	//Left and Right boundary
	{
		pos = CP_Random_RangeInt(GRID_WIDTH, GRID_SIZE - GRID_WIDTH);
	}
	return pos;
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