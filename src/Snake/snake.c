#include "snake.h"
#include "sprite.h"
#include "cprocessing.h"
#include <stdbool.h>
#include "food.h"
#include "globals.h"

//Define in Snake.c
extern const int WINDOW_WIDTH = 1200, WINDOW_HEIGHT = 800;
static int GRID_WIDTH = 10;
static float CELL_WIDTH;

static float grid_seconds = 0.5f; //seconds per grid
float move_timer;

float offset;
float target;
static CP_Vector WINDOW_CENTRE;
CP_Vector grid[GRID_SIZE];

struct Food food;

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

struct Snake
{
	struct Sprite sprite;
	struct Segment segments[GRID_SIZE - 1];

	CP_Vector position;
	int grid_position;
	int direction;
	
}the_snake;

void Snake_Init(void)
{
	CP_Image img_snake = CP_Image_Load("./Assets/snake.png");
	CP_Image img_food = CP_Image_Load("./Assets/food.png");
	WINDOW_CENTRE = CP_Vector_Set((float)WINDOW_WIDTH / 2, (float)WINDOW_HEIGHT / 2);

	target = (float)(WINDOW_WIDTH + WINDOW_HEIGHT) / 4;
	offset = ((float)(WINDOW_WIDTH + WINDOW_HEIGHT) / 4) / 2;
	Snake_SetGrid();
	move_timer = grid_seconds;

	Food_Init(&food, img_food, grid);

	the_snake.sprite.image = img_snake;
	the_snake.grid_position = 3;
	the_snake.position = grid[3];
	the_snake.direction = RIGHT;

	for (int i = 0; i < GRID_SIZE - 1; i++)
	{
		the_snake.segments[i].active = 0;
		the_snake.segments[i].position = CP_Vector_Set(0, 0);
		the_snake.segments[i].grid_position = 0;
	}

	the_snake.sprite.width = (float)CP_Image_GetWidth(img_snake) * 2;
	the_snake.sprite.height = (float)CP_Image_GetHeight(img_snake) * 2;

}

void Snake_Update(void)
{
	Snake_UpdateInput();
	Snake_Timer();
	Snake_UpdateMovement();
	Food_Update(&food);
	Snake_Draw();

}

void Snake_Exit(void)
{

}

void Snake_SetGrid()
{
	CELL_WIDTH = target / GRID_WIDTH;
	for (int i = 0; i < GRID_SIZE; i++)
	{
		grid[i] = CP_Vector_Set(
			offset + i % GRID_WIDTH * CELL_WIDTH + CELL_WIDTH / 2,
			offset + i / GRID_WIDTH * CELL_WIDTH + CELL_WIDTH / 2);
	}
}



void Snake_DrawGrid()
{
	float start = (float)offset;
	float end = CELL_WIDTH * GRID_WIDTH + offset;

	for (int i = 0; i <= GRID_WIDTH; i++)
	{
		float row = i * CELL_WIDTH + offset;

		CP_Graphics_DrawLine(start, row, end, row);
		CP_Graphics_DrawLine(row, start, row, end);
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

		for (int i = GRID_SIZE - 1; i >= 0; i--)
		{
			struct Segment* segment = &the_snake.segments[i];
			if (segment->active)
			{
				if (i > 1)
					segment->grid_position = the_snake.segments[i - 1].grid_position;
				else
					segment->grid_position = pos;

				segment->position = grid[segment->grid_position];

			}
		}

		the_snake.grid_position = pos;
		the_snake.position = grid[pos];
	}
}

void Snake_Draw(void)
{
	CP_Settings_Background(CP_Color_Create(255, 255, 255, 255));
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
