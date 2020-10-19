#include "gameover.h"
#include "snake.h"
static const int WINDOW_WIDTH = 1200, WINDOW_HEIGHT = 800;

void GameOver_button_init(void)
{
	GameOver_button.width = 300.0f;
	GameOver_button.height = 100.0f;
	GameOver_button.x = (float)(WINDOW_WIDTH / 2.0f) - (GameOver_button.width / 2.0f); // 600 - 150 = 450

	GameOver_button.hover = CP_Color_Create(255, 0, 0, 255);
	GameOver_button.idle = CP_Color_Create(0, 255, 0, 255);
	GameOver_button.text = CP_Color_Create(0, 0, 0, 255);

	retry_button.text = "Retry";
	retry_button.y = (float)WINDOW_HEIGHT/ 4.0f - GameOver_button.height / 2.0f;

	quit_button.text = "Quit";
	quit_button.y = (float)WINDOW_HEIGHT / 2.0f + GameOver_button.height / 2.0f;

}
void init_GameOver(void)
{
	CP_Settings_TextSize(100.0f);
	GameOver_button_init();
}

void update_GameOver(void)
{
	float mouseX = CP_Input_GetMouseX();
	float mouseY = CP_Input_GetMouseY();

	CP_Settings_Background(CP_Color_Create(160, 160, 160, 255));

	if (GameOver_button.x <= mouseX && mouseX <= GameOver_button.x + GameOver_button.width
		&& retry_button.y <= mouseY && mouseY <= retry_button.y + GameOver_button.height)
	{
		CP_Settings_Fill(GameOver_button.hover);
		if (CP_Input_MouseClicked())
		{
			CP_Engine_SetNextGameState(Snake_Init, Snake_Update, Snake_Exit);
		}
	}
	else
	{
		CP_Settings_Fill(GameOver_button.idle);
	}
	
	CP_Graphics_DrawRect(GameOver_button.x, retry_button.y, GameOver_button.width, GameOver_button.height);
	CP_Settings_Fill(GameOver_button.text);
	CP_Font_DrawText("YOU DIED", (float)WINDOW_WIDTH / 2.8f, 75.0f);
	CP_Font_DrawText(retry_button.text, GameOver_button.x + GameOver_button.width * 0.15f,
		retry_button.y + GameOver_button.height * 0.7f);

	if (GameOver_button.x <= mouseX && mouseX <= GameOver_button.x + GameOver_button.width
		&& quit_button.y <= mouseY && mouseY <= quit_button.y + GameOver_button.height)
	{
		CP_Settings_Fill(GameOver_button.hover);
		if (CP_Input_MouseClicked())
		{
			CP_Engine_Terminate();
		}
	}
	else
	{
		CP_Settings_Fill(GameOver_button.idle);
	}

	CP_Graphics_DrawRect(GameOver_button.x, quit_button.y, GameOver_button.width, GameOver_button.height);
	CP_Settings_Fill(GameOver_button.text);
	CP_Font_DrawText(quit_button.text, GameOver_button.x + GameOver_button.width * 0.25f,
		quit_button.y + GameOver_button.height * 0.7f);
}

void exit_GameOver(void)
{
	
}