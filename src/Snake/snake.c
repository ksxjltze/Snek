#include "snake.h"
#include "utils.h"

//Define in Snake.c
extern const int WINDOW_WIDTH, WINDOW_HEIGHT;
static CP_Color BACKGROUND_COLOR;

static float grid_seconds = 0.5f; //seconds per grid (movement)
float move_timer;

static CP_Vector WINDOW_CENTRE;
bool paused;

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
	CP_Image img_snake = CP_Image_Load("./Assets/snek.png");
	WINDOW_CENTRE = CP_Vector_Set((float)WINDOW_WIDTH / 2, (float)WINDOW_HEIGHT / 2);
	CP_Settings_Stroke(CP_Color_Create(255, 255, 255, 255)); //White lines
	BACKGROUND_COLOR = CP_Color_Create(0, 0, 0, 255);		 //Black background

	Snake_Grid_Init();									//Initialize Grid specific variables
	Snake_SetGrid(grid);								//Populates the grid array with CP_Vector positions.
	Snake_TruncateGrid(grid, grid_field);
	move_timer = 0.0f;

	the_snake.sprite.image = img_snake;
	the_snake.grid_position = Random_Snake_Grid_Pos();		//Sets a random position
	the_snake.position = grid[the_snake.grid_position]; //Screen Position
	the_snake.direction = RIGHT;						//Snake faces right by default.

	//Initialize snake's segments
	Snake_Init_Segments();

	//Test
	//Snake_Grow();
	//Snake_Grow();
	//Snake_Grow();

	the_snake.sprite.width = GRID_WIDTH;
	the_snake.sprite.height = GRID_WIDTH;

	init_food(grid_field);
	Button_Init();
	Init_Score();
	Init_GameOver();
	Snake_PauseMenu_Init();
	//Init_Music();
	paused = false;

}

void Snake_Update(void)
{
	if (paused)
	{
		Snake_PauseMenu_Update();
	}
	else
	{
		Snake_UpdateInput();
		Snake_Timer();
		Snake_UpdateMovement();
		food_update(grid_field);
		Snake_Draw();
		Update_Score();
	}
	
	if (CP_Input_KeyTriggered(KEY_ESCAPE))
		paused = Snake_Pause(paused);

}

void Snake_Exit(void)
{

}

void Snake_Death(void)
{
	CP_Engine_SetNextGameState(Init_GameOver, Update_GameOver, Exit_GameOver);
}

void Snake_Init_Segments()
{
	for (int i = 0; i < GRID_SIZE - 1; i++)		//Minus 1 to account for snake's head.
	{
		the_snake.segments[i].active = false;	//Not active, will not be drawn.
		the_snake.segments[i].position = CP_Vector_Set(0, 0);
		the_snake.segments[i].grid_position = 0;
	}
}

//Makes the snake grow longer.
void Snake_Grow()
{
	int direction = the_snake.direction;
	if (direction % 2 == 0) //Horizontal
		direction /= 2;			//"Normalize" to become 1.
	else					//Vertical
		direction *= GRID_WIDTH;

	//Finds and sets the next segment's position, sets it to active then returns.
	for (int i = 0; i < GRID_SIZE - 1; i++)
	{
		struct Segment* segment = &the_snake.segments[i];
		if (!segment->active) //Find first inactive segment. i.e. Segment after the "Last Segment".
		{
			segment->active = true;
			if (i > 0)
				segment->grid_position = the_snake.segments[i - 1].grid_position - direction;	//Segments after the first.
			else
				segment->grid_position = the_snake.grid_position - direction;					//First segment after the head.

			segment->position = grid[segment->grid_position];
			return;
		}
	}
}

//Update Movement Timer
void Snake_Timer(void)
{
	move_timer -= CP_System_GetDt();
}

//Check Input and Update Snake's direction.
void Snake_UpdateInput(void)
{
	if (CP_Input_KeyTriggered(KEY_W) || CP_Input_KeyTriggered(KEY_UP))
	{
		if (the_snake.direction != DOWN)
			the_snake.direction = UP;

	}
	else if (CP_Input_KeyTriggered(KEY_A) || CP_Input_KeyTriggered(KEY_LEFT))
	{
		if (the_snake.direction != RIGHT)
			the_snake.direction = LEFT;

	}
	else if (CP_Input_KeyTriggered(KEY_S) || CP_Input_KeyTriggered(KEY_DOWN))
	{
		if (the_snake.direction != UP)
			the_snake.direction = DOWN;

	}
	else if (CP_Input_KeyTriggered(KEY_D) || CP_Input_KeyTriggered(KEY_RIGHT))
	{
		if (the_snake.direction != LEFT)
			the_snake.direction = RIGHT;
	}
}

//Update snake's position.
void Snake_UpdateMovement(void)
{
	if (move_timer <= 0)						//Snake moves once every x seconds.
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
					segment->grid_position =	//Sets current segment's position to be the position of the segment before it.
					the_snake.segments[i - 1].grid_position;
				else							//Segment before head
					segment->grid_position =	//Set first segment's position to be the position of the head.
					the_snake.grid_position;

				segment->destination = grid[segment->grid_position];	//Update screen position. (Pixels)

			}
		}

		the_snake.grid_position = pos;			//Update head's grid position.
		the_snake.destination = grid[pos];
		//the_snake.position = grid[pos];			//Screen Position

		//Collision with boundary (Dania)
		for (int i = GRID_SIZE - 2; i >= 0; i--)
		{
			if (the_snake.position.y == grid[GRID_SIZE - 1].y || the_snake.position.x == grid[GRID_SIZE - 1].x
				|| the_snake.position.y == grid[0].y || the_snake.position.x == grid[0].x ||
				the_snake.position.x == the_snake.segments[i].position.x || 
				the_snake.position.y == the_snake.segments[i].position.y)  //at the last cell
			{
				Snake_Death();
			}
		}

	}
	else
	{
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

void Snake_Move(CP_Vector* old_pos, CP_Vector new_pos)
{
	old_pos->x = CP_Math_LerpFloat(old_pos->x, new_pos.x, CP_System_GetDt() / move_timer);
	old_pos->y = CP_Math_LerpFloat(old_pos->y, new_pos.y, CP_System_GetDt() / move_timer);
}

void Snake_UnPause()
{
	paused = false;
}

//Draw sprites
void Snake_Draw(void)
{
	//Clear Buffer
	CP_Settings_Background(BACKGROUND_COLOR);
	Snake_DrawGrid_Truncated();

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
			CP_Image_Draw(the_snake.sprite.image, 
				segment.position.x, segment.position.y,
				the_snake.sprite.width, the_snake.sprite.height, 255);
		}
	}

	Colour_Boundary();

	//Snake_DrawGrid();
	//Snake_DrawGridPositions(grid_field, GRID_SIZE - BOUNDARY_SIZE);
}

