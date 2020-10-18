#include "snake.h"
#include "CProcessing.h"
#include <stdio.h>
#include <stdlib.h> //malloc
#include <stdbool.h> //bool

//Define in Snake.c
static const int WINDOW_WIDTH = 1200, WINDOW_HEIGHT = 800;

static int GRID_SIZE = 50;
float CELL_WIDTH;
float CELL_HEIGHT;
static float speed = 80.0f; //pixels per second
float movement_timer;
float seconds_per_movement;
static CP_Vector WINDOW_CENTRE;

enum direction
{
	LEFT = -2, 
	UP, 
	DOWN = 1, 
	RIGHT
};

struct Sprite
{
	CP_Image image;
	float width;
	float height;
};

struct Segment
{
	struct Segment* next;
	CP_Vector position;
};

struct Snake
{
	struct Sprite sprite;
	struct Segment* tail;
	float speed;
	int direction;
	CP_Vector position;
}the_snake;

void Snake_Init(void)
{
	CP_Image img_snake = CP_Image_Load("./Assets/snek.png");
	WINDOW_CENTRE = CP_Vector_Set((float)WINDOW_WIDTH / 2, (float)WINDOW_HEIGHT / 2);
	CELL_WIDTH = (float)WINDOW_WIDTH / GRID_SIZE;
	CELL_HEIGHT = (float)WINDOW_HEIGHT / GRID_SIZE;

	Snake_Init_Snake(img_snake);
	seconds_per_movement = 1.0f / 60 * (the_snake.sprite.width * 60 / speed);
	movement_timer = seconds_per_movement;
}

void Snake_Init_Snake(CP_Image snake_sprite)
{
	struct Segment* current = malloc(sizeof * current);
	if (current == 0)
		return;

	the_snake.direction = RIGHT;
	the_snake.position = WINDOW_CENTRE;

	the_snake.sprite.image = snake_sprite;
	the_snake.speed = (speed * (CELL_WIDTH + CELL_HEIGHT) / 2);

	the_snake.sprite.width = (float)CP_Image_GetWidth(snake_sprite);
	the_snake.sprite.height = (float)CP_Image_GetHeight(snake_sprite);

	current->position = CP_Vector_Set(the_snake.position.x - the_snake.sprite.width, the_snake.position.y);
	the_snake.tail = current;
	the_snake.tail->next = NULL;

	for (int i = 0; i < 10; i++)
	{
		current = malloc(sizeof * current);
		if (current == 0)
			return;
		current->position = CP_Vector_Set(the_snake.tail->position.x - the_snake.sprite.width, the_snake.tail->position.y);
		current->next = the_snake.tail;
		the_snake.tail = current;
	}

}

void Snake_Update(void)
{
	Snake_UpdateInput();
	Snake_UpdateMovement();
	Snake_Draw();

}

void Snake_Exit(void)
{
	struct Segment* tmp;

	while (the_snake.tail != NULL)
	{
		tmp = the_snake.tail;
		the_snake.tail = the_snake.tail->next;
		free(tmp);
	}

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

CP_Vector Snake_CalculateMovement(int direction)
{
	CP_Vector movement_vector = CP_Vector_Set(0, 0);
	if (direction % 2 == 0)
		movement_vector = CP_Vector_Scale(
			CP_Vector_Normalize(
				CP_Vector_Set((float)direction, 0)), the_snake.sprite.width); //Horizontal
	else
		movement_vector = CP_Vector_Scale(
			CP_Vector_Normalize(
				CP_Vector_Set(0, (float)direction)), the_snake.sprite.height); //Vertical

	return movement_vector;
}

void Snake_UpdateMovement(void)
{
	if (movement_timer <= 0)
	{
		movement_timer = seconds_per_movement;
		CP_Vector movement = Snake_CalculateMovement(the_snake.direction);
		the_snake.position = CP_Vector_Add(the_snake.position, movement);
		Snake_UpdateSegments(movement);
	}
	movement_timer -= CP_System_GetDt();
}

void Snake_UpdateSegments(CP_Vector movement)
{
	struct Segment* current = the_snake.tail;
	while (current->next != NULL)
	{
		struct Segment* next = current->next;
		current->position = next->position;
		current = next;
	}
	current->position = CP_Vector_Subtract(the_snake.position, movement);
}

void Snake_Draw(void)
{
#if 0
	for (int i = 0; i < GRID_SIZE; i++)
	{
		/*CP_Graphics_DrawLine(0, i * CELL_HEIGHT, (float)WINDOW_WIDTH, i * CELL_HEIGHT);
		CP_Graphics_DrawLine(i * CELL_WIDTH, 0, i * CELL_WIDTH, (float)WINDOW_HEIGHT);*/
		for (int j = 0; j < GRID_SIZE; j++)
		{
			CP_Graphics_DrawCircle(i * CELL_WIDTH + CELL_WIDTH / 2, j * CELL_HEIGHT + CELL_HEIGHT / 2, 3);

		}
	}
#endif

	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	CP_Image_Draw(the_snake.sprite.image, the_snake.position.x, the_snake.position.y, the_snake.sprite.width, the_snake.sprite.height, 255);
	struct Segment* current = the_snake.tail;

	while (current != NULL)
	{
		CP_Image_Draw(the_snake.sprite.image, current->position.x, current->position.y, the_snake.sprite.width, the_snake.sprite.height, 255);
		current = current->next;

	}

}
