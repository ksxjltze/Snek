#pragma once
#include <stdbool.h> //bool (true, false)
#include "MainMenu.h"
#include "score.h"
#include "gameover.h"
#include "music.h"
#include "file_manager.h"
#include "sprite.h"
#include "cprocessing.h"
#include "globals.h"
#include "grid.h"
#include "food.h"

struct Segment			//Segment of Snake body.
{
	CP_Vector position; //Screen position.
	int grid_position;  //Grid position. (Index of array)
	bool active;		//Used in array to determine if segment should be updated.
};

struct Snake								//Snake (Player)
{
	struct Sprite sprite;
	struct Segment segments[GRID_SIZE - 1]; //Snake Body

	CP_Vector position;						//Screen position (pixels)
	int grid_position;						//Grid position (0 < position < GRID_SIZE)
	int direction;							//Snake direction (defined in enum Directions)

}the_snake;									//Single instance of Snake struct.

//Declare in Snake.h

void Snake_Init(void);
void Snake_Update(void);
void Snake_Exit(void);

//Movement
void Snake_UpdateInput(void);
void Snake_UpdateMovement(void);
void Snake_Timer(void);

//Draw
void Snake_Draw(void);

//Grow
void Snake_Grow(void);

//Death
void Snake_Death(void);
