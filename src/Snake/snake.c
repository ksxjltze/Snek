#include "snake.h"
#include "sprite.h"
#include "cprocessing.h"
#include "globals.h"
#include "grid.h"

//Define in Snake.c
#define DEBUG 1;
extern const int WINDOW_WIDTH = 1200, WINDOW_HEIGHT = 800;
static CP_Color BACKGROUND_COLOR;

static float grid_seconds = 0.5f; //seconds per grid (movement)
float move_timer;

static CP_Vector WINDOW_CENTRE;
CP_Vector grid[GRID_SIZE]; //Grid Positions
CP_Vector boundary[BOUNDARY_SIZE]; //Grid boundary

enum Directions			//Integer values used to determine snake direction. Modulo (%) is used to determine axis.
{
	LEFT = -2,			//-2
	UP,					//-1
	DOWN = 1,			//+1
	RIGHT				//+2
};

struct Segment			//Segment of Snake body.
{
	CP_Vector position;
	int grid_position;
	bool active;		//Used in array to determine if segment should be updated.
};

struct Snake								//Snake (Player)
{
	struct Sprite sprite;
	struct Segment segments[GRID_SIZE - 1]; //Snake Body

	CP_Vector position;						//Screen position (pixels)
	int grid_position;						//Grid position (0 < position < GRID_SIZE)
	int direction;							//Snake direction (defined in enum Directions)
	
}the_snake;									//Single instance of Snake struct

void Snake_Init(void)
{
	CP_Image img_snake = CP_Image_Load("./Assets/snek.png");
	WINDOW_CENTRE = CP_Vector_Set((float)WINDOW_WIDTH / 2, (float)WINDOW_HEIGHT / 2);
	CP_Settings_Stroke(CP_Color_Create(255, 255, 255, 255)); //White lines
	BACKGROUND_COLOR = CP_Color_Create(0, 0, 0, 255); //Black

	Snake_Grid_Init();									//Initialize Grid specific variables
	Snake_SetGrid(grid);								//Populates the grid array with CP_Vector positions.
	move_timer = grid_seconds;

	the_snake.sprite.image = img_snake;
	the_snake.grid_position = 15;
	the_snake.position = grid[the_snake.grid_position];
	the_snake.direction = RIGHT;

	for (int i = 0; i < GRID_SIZE - 1; i++)
	{
		the_snake.segments[i].active = false;
		the_snake.segments[i].position = CP_Vector_Set(0, 0);
		the_snake.segments[i].grid_position = 0;
	}

	the_snake.sprite.width = GRID_WIDTH;
	the_snake.sprite.height = GRID_WIDTH;

	init_score();
	init_GameOver();
}

void Snake_Update(void)
{
	Snake_UpdateInput();
	Snake_Timer();
	Snake_UpdateMovement();
	Snake_Draw();
	update_score();
	if (CP_Input_KeyTriggered(KEY_Q))
	{
		
	}
}

void Snake_Exit(void)
{

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

void Snake_Timer(void)
{
	move_timer -= CP_System_GetDt();
}


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

void Snake_UpdateMovement(void)
{
	if (move_timer <= 0) //Snake moves once every x seconds.
	{
		move_timer = grid_seconds;
		int direction = the_snake.direction;
		int pos = the_snake.grid_position;

		if (direction % 2 == 0) //Horizontal
			pos += direction / 2;
		else //Vertical
			pos += direction * GRID_WIDTH;

		for (int i = GRID_SIZE - 2; i >= 0; i--)
		{
			struct Segment* segment = &the_snake.segments[i];
			if (segment->active)
			{
				if (i > 0)
					segment->grid_position = the_snake.segments[i - 1].grid_position;
				else
					segment->grid_position = the_snake.grid_position;

				segment->position = grid[segment->grid_position];
			}
			
			
			if (pos == grid[GRID_WIDTH - 1].x) //at the last cell
			{
				Snake_Death();
			}
		}


		the_snake.grid_position = pos;
		the_snake.position = grid[pos];
	}
}

void Snake_Death(void)
{
	CP_Engine_SetNextGameState(init_GameOver, update_GameOver, exit_GameOver);
}

void Snake_Draw(void)
{
	//Clear Buffer
	CP_Settings_Background(BACKGROUND_COLOR);

	//Draw Snake's head.
	CP_Image_Draw(the_snake.sprite.image, 
		the_snake.position.x, the_snake.position.y, 
		the_snake.sprite.width, the_snake.sprite.height, 255);
	
	//Draw Segments.
	for (int i = 0; i < GRID_SIZE - 1; i++)
	{
		struct Segment segment = the_snake.segments[i];
		if (segment.active)
		{
			CP_Image_Draw(the_snake.sprite.image, 
				segment.position.x, segment.position.y,
				the_snake.sprite.width, the_snake.sprite.height, 255);
		}
	}

	Snake_DrawGrid();
}

