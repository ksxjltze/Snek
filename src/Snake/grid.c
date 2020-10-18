#include "grid.h"
#include "cprocessing.h"
#include "globals.h"
#include <stdbool.h>
#include "snake.h"

static float CELL_WIDTH;
float offset; //Offset from top left corner of window.
float target; //Size to draw grid.

extern const int WINDOW_WIDTH, WINDOW_HEIGHT;

void Snake_Grid_Init()
{
	offset = 10; //10 pixels from top left corner
	target = (float)WINDOW_HEIGHT - 2 * offset; //Fit to Window (based on height)
}

void Snake_SetGrid(CP_Vector grid[])
{
	CELL_WIDTH = target / GRID_WIDTH;
	for (int i = 0; i < GRID_SIZE; i++)
	{
		grid[i] = CP_Vector_Set(
			offset + i % GRID_WIDTH * CELL_WIDTH + CELL_WIDTH / 2,
			offset + i / GRID_WIDTH * CELL_WIDTH + CELL_WIDTH / 2);
	}
}

void Snake_SetBoundary(CP_Vector grid[], CP_Vector boundary[])
{
	int boundary_index = BOUNDARY_SIZE - GRID_WIDTH; //last row
	int grid_index = GRID_SIZE - GRID_WIDTH;
	for (int i = 0; i < GRID_WIDTH; i++) //first and last row
	{
		boundary[i] = grid[i];
		boundary[boundary_index + i] = grid[grid_index + i];
	}

	for (int i = 0; i < GRID_WIDTH - 2; i++) //middle rows
	{
		int first_index = (i + 1) * GRID_WIDTH;
		int last_index = (i + 2) * GRID_WIDTH - 1;

		boundary[GRID_WIDTH + i] = grid[first_index];
		boundary[2 * GRID_WIDTH - 2 + i] = grid[last_index];

	}
}

bool Snake_CheckBoundary(CP_Vector position, int direction, CP_Vector boundary[])
{
	int right_index = BOUNDARY_SIZE - GRID_WIDTH;
	bool is_top = false, is_bottom = false, is_left = false, is_right = false;
	bool gameover = false;

	if (direction % 2 != 0)
	{
		for (int i = 0; i < GRID_WIDTH; i++) //top and bottom
		{
			CP_Vector pos_top = boundary[i];
			CP_Vector pos_bottom = boundary[right_index + i];

			is_top = position.x == pos_top.x && position.y == pos_top.y;
			is_bottom = position.x == pos_bottom.x && position.y == pos_bottom.y;

			if (is_top || is_bottom)
				break;

		}

		if (is_top && direction < 0)
			gameover = true;
		else if (is_bottom && direction > 0)
			gameover = true;

	}

	if (direction % 2 == 0)
	{
		int column_offset = GRID_WIDTH - 2;
		for (int i = GRID_WIDTH; i < BOUNDARY_SIZE - GRID_WIDTH - column_offset; i++)
		{
			CP_Vector pos_left = boundary[i];
			CP_Vector pos_right = boundary[i + column_offset];

			is_left = position.x == pos_left.x && position.y == pos_left.y;
			is_right = position.x == pos_right.x && position.y == pos_right.y;

			if (is_left || is_right)
				break;

		}

		if (is_left && direction < 0)
			gameover = true;
		else if (is_right && direction > 0)
			gameover = true;
	}

	if (gameover)
	{
		Snake_GameOver();
		return true;
	}

	return false;

}

void Snake_DrawBoundary(CP_Vector boundary[])
{
	for (int i = 0; i < BOUNDARY_SIZE; i++)
	{
		CP_Vector position = boundary[i];
		CP_Graphics_DrawCircle(position.x, position.y, 8);
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