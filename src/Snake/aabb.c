#include "aabb.h"

bool Snake_Collision_AABB(float width1, float height1, CP_Vector pos1, float width2, float height2, CP_Vector pos2)
{
	//simple collision
	int is_overlap_x = (pos1.x + width1 / 2 >= pos2.x - width2 / 2 && pos2.x + width2 / 2 >= pos1.x - width1 / 2);
	int is_overlap_y = (pos1.y + height1 / 2 >= pos2.y - height2 / 2 && pos2.y + height2 / 2 >= pos1.y - height1 / 2);

	if (is_overlap_x && is_overlap_y)
	return 1;

	return 0;
}