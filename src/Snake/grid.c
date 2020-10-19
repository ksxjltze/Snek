#include "grid.h"
#include "cprocessing.h"
#include "globals.h"
#include <stdbool.h>
#include "snake.h"

static float CELL_WIDTH;
float offset; //Offset from top left corner of window.
float target; //Length of grid in pixels.

extern const int WINDOW_WIDTH, WINDOW_HEIGHT;

//Initalizes variables for the scope of grid.c
void Snake_Grid_Init()
{
	offset = 10;								//10 pixels from top left corner
	target = (float)WINDOW_HEIGHT - 2 * offset; //Fit to Window (based on height)
}

void Snake_SetGrid(CP_Vector grid[])		//Assumes that grid is a square grid.
{
	CELL_WIDTH = target / GRID_WIDTH;		//Width of one grid cell.
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