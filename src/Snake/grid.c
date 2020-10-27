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

//Populates CP_Vector array with positions.
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

//Truncates grid (Remove boundary)
void Snake_TruncateGrid(CP_Vector grid[], CP_Vector grid_truncated[])
{
	int x = 0;														//Truncated grid index.
	for (int i = GRID_WIDTH; i < GRID_SIZE - GRID_WIDTH; i++)		
	{
		if ((i - GRID_WIDTH + 1) % GRID_WIDTH == 0)
			continue;

		if (i % GRID_WIDTH != 0)
		{
			grid_truncated[x] = grid[i];
			x++;
		}
	
	}
}

//Draws the grid.
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

<<<<<<< Updated upstream
//Draws the grid without the boundary.
void Snake_DrawGrid_Truncated()
{
	float start = (float)offset + CELL_WIDTH;
	float end = CELL_WIDTH * (GRID_WIDTH - 1) + offset;

	for (int i = 1; i <= GRID_WIDTH - 1; i++)
	{
		float row = i * CELL_WIDTH + offset;

		CP_Graphics_DrawLine(start, row, end, row);
		CP_Graphics_DrawLine(row, start, row, end);
	}
}

//Draws circles on grid positions (Debug)
void Snake_DrawGridPositions(CP_Vector grid[], int size)
{
	for (int i = 0; i < size; i++)
	{
		CP_Vector pos = grid[i];
		CP_Graphics_DrawCircle(pos.x, pos.y, 5);
	}
}

void Colour_Boundary()
{
	//TODO color
	//color var
	//set draw color

	float end = (CELL_WIDTH * GRID_WIDTH - offset) - CELL_WIDTH / 2;
	CP_Settings_Fill(CP_Color_Create(153, 0, 0, 255));
	CP_Graphics_DrawRect(offset, offset - 2, GRID_WIDTH * CELL_WIDTH, CELL_WIDTH);  //Top boundary
	CP_Graphics_DrawRect(offset, end + 2, GRID_WIDTH * CELL_WIDTH, CELL_WIDTH);     //Bottom boundary
	CP_Graphics_DrawRect(offset, offset, CELL_WIDTH, GRID_WIDTH * CELL_WIDTH);					//Left boundary
	CP_Graphics_DrawRect(end + 2, offset, CELL_WIDTH, GRID_WIDTH * CELL_WIDTH);						//Right boundary

	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255)); // change color back to white;
}
=======
>>>>>>> Stashed changes
