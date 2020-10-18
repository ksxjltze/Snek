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

enum direction
{
	LEFT = -2, 
	UP, 
	DOWN = 1, 
	RIGHT
};

struct Segment
{
	CP_Vector position;
	int grid_position;
	bool active;
};

struct Snake //Snake (Player)
{
	struct Sprite sprite;
	struct Segment segments[GRID_SIZE - 1]; //Snake Body

	CP_Vector position;
	int grid_position;
	int direction;
	
}the_snake;

void Snake_Init(void)
{
	CP_Image img_snake = CP_Image_Load("./Assets/snek.png");
	WINDOW_CENTRE = CP_Vector_Set((float)WINDOW_WIDTH / 2, (float)WINDOW_HEIGHT / 2);
	CP_Settings_Stroke(CP_Color_Create(255, 255, 255, 255)); //White lines
	BACKGROUND_COLOR = CP_Color_Create(0, 0, 0, 255); //Black

	Snake_Grid_Init();
	Snake_SetGrid(grid);
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

	the_snake.sprite.width = (float)CP_Image_GetWidth(img_snake) * 2;
	the_snake.sprite.height = (float)CP_Image_GetHeight(img_snake) * 2;

	the_snake.sprite.width = (float)CP_Image_GetWidth(img_snake);
	the_snake.sprite.height = (float)CP_Image_GetHeight(img_snake);
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
		CP_Engine_SetNextGameState(init_GameOver, update_GameOver, exit_GameOver);
	}
}

void Snake_Exit(void)
{

}

void Snake_Grow()
{
	int direction = the_snake.direction;
	if (direction % 2 == 0)
		direction /= 2;
	else
		direction *= GRID_WIDTH;

	for (int i = 0; i < GRID_SIZE - 1; i++)
	{
		struct Segment* segment = &the_snake.segments[i];
		if (!segment->active)
		{
			segment->active = true;
			if (i > 0)
				segment->grid_position = the_snake.segments[i - 1].grid_position - direction;
			else
				segment->grid_position = the_snake.grid_position - direction;

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
	if (move_timer <= 0)
	{
		move_timer = grid_seconds;
		int direction = the_snake.direction;
		int pos = the_snake.grid_position;

		if (direction % 2 == 0)
			pos += direction / 2;
		else
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
		}

		the_snake.grid_position = pos;
		the_snake.position = grid[pos];
	}
}

void Snake_Draw(void)
{
	CP_Settings_Background(BACKGROUND_COLOR);
	//CP_Image_Draw(the_snake.sprite.image, the_snake.position.x, the_snake.position.y, the_snake.sprite.width, the_snake.sprite.height, 255);
	CP_Image_Draw(the_snake.sprite.image, the_snake.position.x, the_snake.position.y, the_snake.sprite.width, the_snake.sprite.height, 255);
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

