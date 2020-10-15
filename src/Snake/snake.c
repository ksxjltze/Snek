#include "snake.h"
#include "CProcessing.h"
//Define in Snake.c
static const int WINDOW_WIDTH = 1200, WINDOW_HEIGHT = 800;

static int GRID_SIZE = 50;
float CELL_WIDTH;
float CELL_HEIGHT;
static float speed = 5; //Grids per second
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
	float speed;
}the_snake;

void Snake_Init(void)
{	
	CP_Image img_snake = CP_Image_Load("./Assets/snek.png");
	WINDOW_CENTRE = CP_Vector_Set((float)WINDOW_WIDTH / 2, (float)WINDOW_HEIGHT / 2);
	CELL_WIDTH = (float)WINDOW_WIDTH / GRID_SIZE;
	CELL_HEIGHT = (float)WINDOW_HEIGHT / GRID_SIZE;

	the_snake.sprite.image = img_snake;
	the_snake.position = WINDOW_CENTRE;
	the_snake.direction = RIGHT;
	the_snake.speed = (speed * (CELL_WIDTH + CELL_HEIGHT) / 2);

	the_snake.sprite.width = (float)CP_Image_GetWidth(img_snake);
	the_snake.sprite.height = (float)CP_Image_GetHeight(img_snake);


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
		movement_vector = CP_Vector_Scale(
			CP_Vector_Normalize(
				CP_Vector_Set((float)the_snake.direction, 0)), the_snake.speed * CP_System_GetDt()); //Horizontal
	else
		movement_vector = CP_Vector_Scale(
			CP_Vector_Normalize(
				CP_Vector_Set(0, (float)the_snake.direction)), the_snake.speed * CP_System_GetDt()); //Vertical

	the_snake.position = CP_Vector_Add(the_snake.position, movement_vector);
}

void Snake_Draw(void)
{
	//for (int i = 0; i < GRID_SIZE; i++)
	//{
	//	/*CP_Graphics_DrawLine(0, i * CELL_HEIGHT, (float)WINDOW_WIDTH, i * CELL_HEIGHT);
	//	CP_Graphics_DrawLine(i * CELL_WIDTH, 0, i * CELL_WIDTH, (float)WINDOW_HEIGHT);*/
	//	for (int j = 0; j < GRID_SIZE; j++)
	//	{
	//		CP_Graphics_DrawCircle(i * CELL_WIDTH + CELL_WIDTH / 2, j * CELL_HEIGHT + CELL_HEIGHT / 2, 3);

	//	}
	//}

	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	CP_Image_Draw(the_snake.sprite.image, the_snake.position.x, the_snake.position.y, the_snake.sprite.width, the_snake.sprite.height, 255);
}
