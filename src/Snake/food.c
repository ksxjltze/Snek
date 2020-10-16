#include "food.h"
#include "globals.h"
#include "utils.h"

void Food_Init(struct Food* food, CP_Image sprite, CP_Vector grid[])
{
	food->sprite.image = sprite;
	Set_Sprite_Size(&food->sprite);
	food->grid_pos = Random_Grid_Pos();
	food->position = grid[food->grid_pos];
}

void Food_Update(struct Food* food)
{
	Food_Draw(*food);
}

void Food_Draw(struct Food food)
{
	CP_Image_Draw(food.sprite.image, food.position.x, food.position.y, food.sprite.width, food.sprite.height, 255);
}

void Food_Respawn(struct Food* food, CP_Vector grid[])
{
	food->grid_pos = Random_Grid_Pos();
	food->position = grid[food->grid_pos];
}