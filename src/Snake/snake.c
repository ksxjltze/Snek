//---------------------------------------------------------
// file:	snake.c
// author:	Team Asteroids
//
// brief:	Snake game scene.
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "snake.h"
#include "utils.h"

//Define in Snake.c
extern const int WINDOW_WIDTH, WINDOW_HEIGHT;
static CP_Color BACKGROUND_COLOR;

static float start_speed = 0.5f;
float grid_seconds = 0.5f; //seconds per grid (movement)
float move_timer;

static CP_Vector WINDOW_CENTRE;
bool paused;
bool lock;

CP_Vector grid[GRID_SIZE]; //Grid Positions, Full grid.
CP_Vector grid_field[GRID_SIZE - BOUNDARY_SIZE]; //Truncated grid (without boundary)
//CP_Vector boundary[BOUNDARY_SIZE]; //Grid boundary

enum Directions			//Integer values used to determine snake direction. Modulo (%) is used to determine axis.
{
	LEFT = -2,			//-2
	UP,					//-1
	DOWN = 1,			//+1
	RIGHT				//+2
};

void Snake_Init(void)
{
	CP_Image img_snake = CP_Image_Load("./Assets/head.png");
	CP_Image img_body = CP_Image_Load("./Assets/body.png");
	WINDOW_CENTRE = CP_Vector_Set((float)WINDOW_WIDTH / 2, (float)WINDOW_HEIGHT / 2);
	BACKGROUND_COLOR = CP_Color_Create(0, 0, 0, 255);		 //Black background

	Snake_Grid_Init();									//Initialize Grid specific variables
	Snake_SetGrid(grid);								//Populates the grid array with CP_Vector positions.
	Snake_TruncateGrid(grid, grid_field);
	move_timer = 0.0f;

	the_snake.sprite.image = img_snake;
	the_snake.body_sprite.image = img_body;
	the_snake.grid_position = Random_Snake_Grid_Pos();		//Sets a random position
	the_snake.position = grid[the_snake.grid_position]; //Screen Position
	the_snake.direction = RIGHT;						//Snake faces right by default.

	//Initialize snake's segments
	Snake_Init_Segments();

	the_snake.sprite.width = GRID_WIDTH;
	the_snake.sprite.height = GRID_WIDTH;

	init_food(grid_field);
	Button_Init();
	Init_Scores_Var();
	Init_GameOver();
	Snake_PauseMenu_Init();
	CP_Sound_SetGroupPitch(CP_SOUND_GROUP_MUSIC, (start_speed / grid_seconds) / 2);
	Play_Music();
	paused = false;
	lock = false;

}

void Snake_Update(void)
{
	if (paused)
	{
		Snake_PauseMenu_Update();
	}
	else
	{
		Snake_Timer();
		Snake_UpdateInput();
		Snake_Collide();
		Snake_UpdateMovement();
		food_update(grid_field);
		Snake_Draw();
		Update_Score();
	}
	
	if (CP_Input_KeyTriggered(KEY_ESCAPE))
		paused = Snake_Pause(paused);


	if (CP_Input_KeyTriggered(KEY_Q)) // debug leaderboard
	{
		CP_Engine_SetNextGameState(Init_GameOver, Update_GameOver, Exit_GameOver);
	}

}

void Snake_Exit(void)
{
	Snake_Reset();
	_fcloseall();
}

void Snake_Death(void)
{
	//Check_If_Leader();
	CP_Engine_SetNextGameState(Init_GameOver, Update_GameOver, Exit_GameOver);
}

void Snake_Init_Segments()
{
	for (int i = 0; i < GRID_SIZE - 1; i++)		//Minus 1 to account for snake's head.
	{
		the_snake.segments[i].active = false;	//Not active, will not be drawn.
		the_snake.segments[i].position = CP_Vector_Set(0, 0);
		the_snake.segments[i].grid_position = 0;
		the_snake.segments[i].direction = RIGHT;
	}
}

void Snake_Collide()
{
	CP_Vector pos = the_snake.position;
	for (int i = 0; i < GRID_SIZE - 1; i++)
	{
		if (the_snake.segments[i].position.x == pos.x && the_snake.segments[i].position.y == pos.y)
		{
			Snake_Death();
			return;
		}
	}
}

int Snake_Normalize_Direction(int direction)
{
	if (direction % 2 == 0) //Horizontal
		direction /= 2;			//"Normalize" to become 1.
	else					//Vertical
		direction *= GRID_WIDTH;

	return direction;
}

//Makes the snake grow longer. (Lee Jia Keat)
void Snake_Grow()
{
	int direction = Snake_Normalize_Direction(the_snake.direction);
	Snake_Speed_Up();

	//Finds and sets the next segment's position, sets it to active then returns.
	for (int i = 0; i < GRID_SIZE - 1; i++)
	{
		struct Segment* segment = &the_snake.segments[i];
		if (!segment->active) //Find first inactive segment. i.e. Segment after the "Last Segment".
		{
			segment->active = true;

			if (i > 0)
			{
				struct Segment previous_segment = the_snake.segments[i - 1];
				direction = Snake_Normalize_Direction(previous_segment.direction);

				segment->grid_position = previous_segment.grid_position - direction;	//Segments after the first.
				
			}
			else
				segment->grid_position = the_snake.grid_position - direction;					//First segment after the head.

			segment->position = grid[segment->grid_position];
			segment->destination = segment->position;
			return;
		}
	}
}

void Snake_Speed_Up()
{
	grid_seconds *= 0.95f; //snake moves 5% faster.
	printf("%f", CP_Sound_GetGroupPitch(CP_SOUND_GROUP_MUSIC));
	if ((start_speed / grid_seconds) / 2 < 3)
		CP_Sound_SetGroupPitch(CP_SOUND_GROUP_MUSIC, (start_speed / grid_seconds) / 2); //Music plays 5% faster.
}

//Update Movement Timer
void Snake_Timer(void)
{
	move_timer -= CP_System_GetDt();
	if (move_timer <= 0)
		lock = false;
}

//Check Input and Update Snake's direction.
void Snake_UpdateInput(void)
{

	if (lock == false)
	{
		if (CP_Input_KeyTriggered(KEY_W) || CP_Input_KeyTriggered(KEY_UP))
		{
			if (the_snake.direction != DOWN)
				the_snake.direction = UP;
			lock = true;

		}
		else if (CP_Input_KeyTriggered(KEY_A) || CP_Input_KeyTriggered(KEY_LEFT))
		{
			if (the_snake.direction != RIGHT)
				the_snake.direction = LEFT;
			lock = true;
		}
		else if (CP_Input_KeyTriggered(KEY_S) || CP_Input_KeyTriggered(KEY_DOWN))
		{
			if (the_snake.direction != UP)
				the_snake.direction = DOWN;
			lock = true;
		}
		else if (CP_Input_KeyTriggered(KEY_D) || CP_Input_KeyTriggered(KEY_RIGHT))
		{
			if (the_snake.direction != LEFT)
				the_snake.direction = RIGHT;
			lock = true;
		}

	}
}

//Update snake's position. (Lee Jia Keat)
void Snake_UpdateMovement(void)
{
	//Update snake's target cell/position (including body).
	if (move_timer <= 0)						//Snake updates destination once every x seconds.
	{
		move_timer = grid_seconds;				//Reset timer
		int direction = the_snake.direction;	//Movement Direction
		int pos = the_snake.grid_position;		//Grid Position

		if (direction % 2 == 0)					//Horizontal
			pos += direction / 2;
		else									//Vertical
			pos += direction * GRID_WIDTH;

		//Iterates from snake's tail to head, updates each segment's position.
		for (int i = GRID_SIZE - 2; i >= 0; i--)
		{
			struct Segment* segment = &the_snake.segments[i];
			if (segment->active)				//Finds active segments from the back of the array.
			{
				if (i > 0)						//Not first segment (before head)
				{
					segment->grid_position = the_snake.segments[i - 1].grid_position;	//Sets current segment's position to be the position of the segment before it.
					segment->direction = the_snake.segments[i - 1].direction;
				}
				else							//Segment before head.
				{
					segment->grid_position = the_snake.grid_position;					//Set first segment's position to be the position of the head.
					segment->direction = the_snake.direction;
				}

				segment->destination = grid[segment->grid_position];	//Update screen position. (Pixels)

			}
		}

		the_snake.grid_position = pos;			//Update head's grid position.
		the_snake.destination = grid[pos];
		//the_snake.position = grid[pos];			//Screen Position

		//Collision with boundary (Dania)
		if (the_snake.position.y == grid[GRID_SIZE - 1].y || the_snake.position.x == grid[GRID_SIZE - 1].x ||
			the_snake.position.y == grid[0].y || the_snake.position.x == grid[0].x)
		{
			Score_Manager();
			Snake_Death();
		}

	}
	else
	{
		//Move to next cell
		Snake_Move(&the_snake.position, the_snake.destination);
		for (int i = 0; i < GRID_SIZE - 1; i++)
		{
			struct Segment* segment = &the_snake.segments[i];
			if (segment->active) //Find first inactive segment. i.e. Segment after the "Last Segment".
			{
				Snake_Move(&segment->position, segment->destination);
			}
		}
	}

}

//Lerps snake movement from cell to cell for smooth movement.
void Snake_Move(CP_Vector* old_pos, CP_Vector new_pos)
{
	old_pos->x = CP_Math_LerpFloat(old_pos->x, new_pos.x, CP_System_GetDt() / move_timer);
	old_pos->y = CP_Math_LerpFloat(old_pos->y, new_pos.y, CP_System_GetDt() / move_timer);
}

void Snake_UnPause()
{
	paused = false;
}

void Snake_Quit()
{
	Stop_Music();
	CP_Engine_SetNextGameState(Menu_init, Menu_update, Menu_exit);
}

void Snake_Reset(void)
{
	//Reset snake position (random)
	the_snake.grid_position = Random_Snake_Grid_Pos();		//Sets a random position
	the_snake.position = grid[the_snake.grid_position];		//Screen Position
	the_snake.direction = RIGHT;
	move_timer = 0.0f;
	grid_seconds = start_speed;
	CP_Sound_SetGroupPitch(CP_SOUND_GROUP_MUSIC, (start_speed / grid_seconds) / 2);

	Snake_Init_Segments();		//Reset Snake body.
	Init_Scores_Var();				//Reset Score.

	paused = false;				//Unpause.
}

//Draw sprites
void Snake_Draw(void)
{
	//Clear Buffer
	CP_Settings_Background(BACKGROUND_COLOR);
	//Snake_DrawGrid_Truncated();

	//Draw Snake's head.
	CP_Image_Draw(the_snake.sprite.image, 
		the_snake.position.x, the_snake.position.y, 
		the_snake.sprite.width, the_snake.sprite.height, 255);
	
	//Draw Segments.
	for (int i = 0; i < GRID_SIZE - 1; i++)				//Minus one to account for head.
	{
		struct Segment segment = the_snake.segments[i];
		if (segment.active)
		{
			CP_Image_Draw(the_snake.body_sprite.image,
				segment.position.x, segment.position.y,
				the_snake.sprite.width, the_snake.sprite.height, 255);
		}
	}

	Colour_Boundary();

	//Snake_DrawGrid();
	//Snake_DrawGridPositions(grid_field, GRID_SIZE - BOUNDARY_SIZE);
}

