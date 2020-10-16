#include "food.h"
#include "globals.h"
#include "utils.h"

void food_init(struct Food* food, CP_Vector grid[])
{
	food->grid_pos = Random_Grid_Pos();
	food->position = grid[food->grid_pos];
}

void food_eaten(struct Food* food)
{

}