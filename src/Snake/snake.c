#include "snake.h"
#include "CProcessing.h"
//Define in Snake.c
static const int WINDOW_WIDTH = 1200, WINDOW_HEIGHT = 800;

static int GRID_SIZE = 100;
static int GRID_WIDTH = 10;
static CP_Vector WINDOW_CENTRE;

enum direction
{
	LEFT = -2, 
	UP, 
	DOWN = 1, 
	RIGHT
};

struct Snake
{
	CP_Image sprite;
	CP_Vector position;
	int direction;
}the_snake;

void Snake_Init(void)
{
	CP_Image img_snake = CP_Image_Load("./Assets/snek.png");
	WINDOW_CENTRE = CP_Vector_Set((float)WINDOW_WIDTH / 2, (float)WINDOW_HEIGHT / 2);
	the_snake.sprite = img_snake;
	the_snake.position = WINDOW_CENTRE;
	the_snake.direction = RIGHT;

}

void Snake_Update(void)
{
	Snake_UpdateInput();
	Snake_UpdateMovement();
	Snake_Draw();

}

void Snake_Exit(void)
{

}

void Snake_UpdateInput(void)
{
	if (CP_Input_KeyTriggered(KEY_W) || CP_Input_KeyTriggered(KEY_UP))
		the_snake.direction = UP;
	else if (CP_Input_KeyTriggered(KEY_A) || CP_Input_KeyTriggered(KEY_LEFT))
		the_snake.direction = LEFT;
	else if (CP_Input_KeyTriggered(KEY_S) || CP_Input_KeyTriggered(KEY_DOWN))
		the_snake.direction = DOWN;
	else if (CP_Input_KeyTriggered(KEY_D) || CP_Input_KeyTriggered(KEY_RIGHT))
		the_snake.direction = RIGHT;

}

void Snake_UpdateMovement(void)
{
	CP_Vector movement_vector = CP_Vector_Set(0, 0);
	float velocity = the_snake.direction * 10 * CP_System_GetDt();

	if (the_snake.direction % 2 == 0)
		movement_vector = CP_Vector_Normalize(CP_Vector_Set(velocity, 0)); //Horizontal
	else
		movement_vector = CP_Vector_Normalize(CP_Vector_Set(0, velocity)); //Vertical

	the_snake.position = CP_Vector_Add(the_snake.position, movement_vector);
}

void Snake_Draw(void)
{
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	CP_Image_Draw(the_snake.sprite, the_snake.position.x, the_snake.position.y, 8, 8, 255);
}
