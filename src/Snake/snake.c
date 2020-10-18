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
static float speed = 5; //Grids per second
static CP_Vector WINDOW_CENTRE;
int old_direction;

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
	int direction;
	bool turning;
};

struct Snake
{
	struct Sprite sprite;
	struct Segment* head;
	float speed;
	//int direction;
	//CP_Vector position;
}the_snake;

void Snake_Init(void)
{
	CP_Image img_snake = CP_Image_Load("./Assets/snek.png");
	WINDOW_CENTRE = CP_Vector_Set((float)WINDOW_WIDTH / 2, (float)WINDOW_HEIGHT / 2);
	CELL_WIDTH = (float)WINDOW_WIDTH / GRID_SIZE;
	CELL_HEIGHT = (float)WINDOW_HEIGHT / GRID_SIZE;

	Snake_Init_Snake(img_snake);
}

void Snake_Init_Snake(CP_Image snake_sprite)
{
	struct Segment* head = malloc(sizeof * head);
	if (head == 0)
		return;

	struct Segment* current = malloc(sizeof * head);
	if (current == 0)
		return;

	head->direction = RIGHT;
	head->position = WINDOW_CENTRE;
	head->next = current;
	the_snake.head = head;

	the_snake.sprite.image = snake_sprite;
	the_snake.speed = (speed * (CELL_WIDTH + CELL_HEIGHT) / 2);

	the_snake.sprite.width = (float)CP_Image_GetWidth(snake_sprite);
	the_snake.sprite.height = (float)CP_Image_GetHeight(snake_sprite);

	for (int i = 1; i <= 10; i++)
	{
		struct Segment* next = malloc(sizeof * head);
		if (next == 0)
			break;
		next->next = NULL;

		current->direction = RIGHT;
		current->position = CP_Vector_Set(head->position.x - the_snake.sprite.width, head->position.y);
		head = current;
		current->next = next;
		current = next;
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

	while (the_snake.head != NULL)
	{
		tmp = the_snake.head;
		the_snake.head = the_snake.head->next;
		free(tmp);
	}

}

void Snake_UpdateInput(void)
{
	old_direction = the_snake.head->direction;
	if (CP_Input_KeyTriggered(KEY_W) || CP_Input_KeyTriggered(KEY_UP))
	{
		if (the_snake.head->direction != DOWN)
			the_snake.head->direction = UP;

	}
	else if (CP_Input_KeyTriggered(KEY_A) || CP_Input_KeyTriggered(KEY_LEFT))
	{
		if (the_snake.head->direction != RIGHT)
			the_snake.head->direction = LEFT;

	}
	else if (CP_Input_KeyTriggered(KEY_S) || CP_Input_KeyTriggered(KEY_DOWN))
	{
		if (the_snake.head->direction != UP)
			the_snake.head->direction = DOWN;

	}
	else if (CP_Input_KeyTriggered(KEY_D) || CP_Input_KeyTriggered(KEY_RIGHT))
	{
		if (the_snake.head->direction != LEFT)
			the_snake.head->direction = RIGHT;
	}

	if (old_direction != the_snake.head->direction)
		the_snake.head->turning = true;

}

CP_Vector Snake_CalculateMovement(int direction)
{
	CP_Vector movement_vector = CP_Vector_Set(0, 0);
	if (direction % 2 == 0)
		movement_vector = CP_Vector_Scale(
			CP_Vector_Normalize(
				CP_Vector_Set((float)direction, 0)), the_snake.speed * CP_System_GetDt()); //Horizontal
	else
		movement_vector = CP_Vector_Scale(
			CP_Vector_Normalize(
				CP_Vector_Set(0, (float)direction)), the_snake.speed * CP_System_GetDt()); //Vertical

	return movement_vector;
}

void Snake_UpdateMovement(void)
{
	the_snake.head->position = CP_Vector_Add(the_snake.head->position, Snake_CalculateMovement(the_snake.head->direction));

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
	CP_Image_Draw(the_snake.sprite.image, the_snake.head->position.x, the_snake.head->position.y, the_snake.sprite.width, the_snake.sprite.height, 255);
	struct Segment* current = the_snake.head->next;
	while (current->next != NULL)
	{
		CP_Image_Draw(the_snake.sprite.image, current->position.x, current->position.y, the_snake.sprite.width, the_snake.sprite.height, 255);
		current = current->next;

	}

}
