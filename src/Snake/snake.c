#include "snake.h"
#include "CProcessing.h"
//Define in Snake.c
static const int WINDOW_WIDTH = 1200, WINDOW_HEIGHT = 800;

static int GRID_SIZE = 100;
static int GRID_WIDTH = 10;
static float speed = 20.0f;
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

struct Snake
{
	struct Sprite sprite;
	CP_Vector position;
	int direction;
}the_snake;

void Snake_Init(void)
{
	CP_Image img_snake = CP_Image_Load("./Assets/snek.png");
	WINDOW_CENTRE = CP_Vector_Set((float)WINDOW_WIDTH / 2, (float)WINDOW_HEIGHT / 2);
	the_snake.sprite.image = img_snake;
	the_snake.position = WINDOW_CENTRE;
	the_snake.direction = RIGHT;

	the_snake.sprite.width = (float)CP_Image_GetWidth(img_snake);
	the_snake.sprite.height = (float)CP_Image_GetHeight(img_snake);
	init_score();
}

void Snake_Update(void)
{
	Snake_UpdateInput();
	Snake_UpdateMovement();
	Snake_Draw();
	update_score();
}

void Snake_Exit(void)
{

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
	CP_Vector movement_vector = CP_Vector_Set(0, 0);

	if (the_snake.direction % 2 == 0)
		movement_vector = CP_Vector_Scale(CP_Vector_Normalize(CP_Vector_Set((float)the_snake.direction, 0)), speed * CP_System_GetDt()); //Horizontal
	else
		movement_vector = CP_Vector_Scale(CP_Vector_Normalize(CP_Vector_Set(0, (float)the_snake.direction)), speed * CP_System_GetDt()); //Vertical

	the_snake.position = CP_Vector_Add(the_snake.position, movement_vector);
}

void Snake_Draw(void)
{
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	CP_Image_Draw(the_snake.sprite.image, the_snake.position.x, the_snake.position.y, the_snake.sprite.width, the_snake.sprite.height, 255);
}
