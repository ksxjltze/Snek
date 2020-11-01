#pragma once
#include <stdbool.h> //bool (true, false)
#include "MainMenu.h"
#include "score.h"
#include "gameover.h"
#include "music.h"
#include "sprite.h"
#include "cprocessing.h"
#include "globals.h"
#include "grid.h"
#include "food.h"
#include "pause.h"
#include "leaderboard.h"

struct Segment					//Segment of Snake body.
{
	CP_Vector position;			//Screen position.
	CP_Vector destination;		//Next position
	int grid_position;			//Grid position. (Index of array)
	int direction;
	bool active;				//Used in array to determine if segment should be updated.
};

struct Snake								//Snake (Player)
{
	struct Sprite sprite;
	struct Sprite body_sprite;
	struct Segment segments[GRID_SIZE - 1]; //Snake Body

	CP_Vector position;						//Screen position (pixels)
	CP_Vector destination;					//Next position
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
void Snake_Move(CP_Vector* old_pos, CP_Vector new_pos);

//Init Segments
void Snake_Init_Segments();

//Draw
void Snake_Draw(void);

//Grow
void Snake_Grow(void);

//Death
void Snake_Death(void);

//Pause and Reset
void Snake_UnPause();
void Snake_Reset(void);

void Snake_Collide();
int Snake_Normalize_Direction(int direction);
