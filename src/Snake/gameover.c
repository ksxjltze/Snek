#include "gameover.h"
#include "globals.h"

void GameOver_Init()
{
	
}

void GameOver_Update()
{
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	CP_Font_DrawText("GAME OVER", (float)WINDOW_WIDTH / 2, (float)WINDOW_HEIGHT / 2);
}

void GameOver_Exit()
{

}