#pragma once
#include "cprocessing.h"
#include "globals.h"
#include "sprite.h"
#include <stdbool.h>

CP_Vector Random_Pos();
int Random_Grid_Pos();
//Generates grid position inside of boundary.
int Random_Snake_Grid_Pos();
//Helper function for setting sprite size.
void Set_Sprite_Size(struct Sprite* sprite);
//Helper function for determining if mouse is over object (Rect).
//Object position must start at top left corner.
bool isMouseOver_Rect(CP_Vector position, float width, float height, float mouseX, float mouseY);