//---------------------------------------------------------
// file:	main.c
// author:	[NAME]
// email:	[DIGIPEN EMAIL ADDRESS]
//
// brief:	Main entry point for the sample project
//			of the CProcessing library
//
// documentation link:
// https://inside.digipen.edu/main/GSDP:GAM100/CProcessing
//
// Copyright � 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "cprocessing.h"
/*For console and printf*/
#include <stdio.h>
#include "Snake/snake.h"
#include "Snake/MainMenu.h"

static const float WINDOW_SCALE = 0.8f;
static const int WINDOW_WIDTH = 1200, WINDOW_HEIGHT = 800;

// main() the starting point for the program
// CP_Engine_SetNextGameState() tells CProcessing which functions to use for init, update and exit
// CP_Engine_Run() is the core function that starts the simulation
int main(void)
{
	//Setting the window title
	CP_System_SetWindowTitle("Snake");

	//Setting the window size and position
	CP_System_SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	CP_System_SetFrameRate(60.0f);

	/*The following stuff is for console output.
	The current console output function from CProcessing
	is being fixed*/
	CP_System_ShowConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);


	CP_Engine_SetNextGameState(Menu_init, Menu_update, Menu_exit);
	CP_Engine_Run();
	return 0;
}
