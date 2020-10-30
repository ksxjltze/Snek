#include "food.h"
#include "sprite.h"
#include "cprocessing.h"
#include "globals.h"
#include "grid.h"
#include "snake.h"
#include "stdbool.h"
#include "sfx.h"


//CP_Vector grid[GRID_SIZE]; //Grid Positions, Full grid.
struct Food
{
	struct Sprite sprite;
	CP_Vector position;						//Screen position (pixels)
	int grid_position;						//Grid position (0 < position < GRID_SIZE)
	int direction;
}the_food;

void food_Draw(void)
{
	{
		CP_Image_Draw(the_food.sprite.image,
			the_food.position.x, the_food.position.y,
			the_food.sprite.width, the_food.sprite.height, 255);        //Draw food.
	}
}

void init_food(CP_Vector grid[])
{

	CP_Image img_food = CP_Image_Load("./Assets/food.png");
	the_food.sprite.image = img_food;
	the_food.sprite.width = GRID_WIDTH;
	the_food.sprite.height = GRID_WIDTH;
	CP_Settings_Stroke(CP_Color_Create(255, 255, 255, 255)); //White lines

	the_food.sprite.image = img_food;

	the_food.grid_position = CP_Random_RangeInt(0, 324);
	the_food.position = grid[the_food.grid_position]; //Screen Position
	the_food.sprite.width = GRID_WIDTH;
	the_food.sprite.height = GRID_WIDTH;

};

void food_update(CP_Vector grid[])
{
	food_Draw();
	collision(the_snake.position, grid);
}

void collision(CP_Vector position, CP_Vector grid[])
{
	if (position.x == the_food.position.x && position.y == the_food.position.y)
	{ 
		//play sfx
		Crunch_SFX();
		Snake_Grow();
		the_food.grid_position = CP_Random_RangeInt(0, 324);     // food position generated inside the barrier
		the_food.position = grid[the_food.grid_position];		 //Screen Position
		Food_score.count++;
	}	
}