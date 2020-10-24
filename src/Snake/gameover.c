#include "gameover.h"
#include "snake.h"
static const int WINDOW_WIDTH = 1200, WINDOW_HEIGHT = 800;

void GameOver_Score(int total_score)// function to print score
{
	CP_Settings_TextSize(50.0f);
	char score_buffer[16];
	sprintf_s(score_buffer, 16, "%d", total_score - (int)Time_score.offset);
	CP_Font_DrawText(gameover_score.text, (float)WINDOW_WIDTH / 2.8f, WINDOW_HEIGHT / 2.0f);
	CP_Font_DrawText(score_buffer, WINDOW_WIDTH / 1.4f, WINDOW_HEIGHT / 2.0f);
}

void GameOver_Button_Init(void) 
{
	gameover_button.width = 300.0f;
	gameover_button.height = 100.0f;
	gameover_button.x = (float)(WINDOW_WIDTH / 2.0f) - (gameover_button.width / 2.0f); 

	gameover_button.hover = CP_Color_Create(255, 0, 0, 255);
	gameover_button.idle = CP_Color_Create(0, 255, 0, 255);
	gameover_button.text = CP_Color_Create(0, 0, 0, 255);

	retry_button.text = "Retry";
	retry_button.y = (float)WINDOW_HEIGHT/ 4.0f - gameover_button.height / 2.0f;

	quit_button.text = "Quit";
	quit_button.y = (float)WINDOW_HEIGHT / 2.0f + gameover_button.height / 2.0f;
}


void Init_GameOver(void) // initializing variables for gameover screen
{
	GameOver_Button_Init();

	gameover_score.text = "Your score:";
}

void Update_GameOver(void) // updates the rendering based on 
{
	float mouseX = CP_Input_GetMouseX();
	float mouseY = CP_Input_GetMouseY();

	CP_Settings_Background(CP_Color_Create(160, 160, 160, 255));

	if (gameover_button.x <= mouseX && mouseX <= gameover_button.x + gameover_button.width
		&& retry_button.y <= mouseY && mouseY <= retry_button.y + gameover_button.height)
	{
		CP_Settings_Fill(gameover_button.hover);
		if (CP_Input_MouseClicked())
		{
			CP_Engine_SetNextGameState(Snake_Init, Snake_Update, Snake_Exit);
		}
	}
	else
	{
		CP_Settings_Fill(gameover_button.idle);
	}
	
	CP_Graphics_DrawRect(gameover_button.x, retry_button.y, gameover_button.width, gameover_button.height);
	CP_Settings_Fill(gameover_button.text);
	CP_Font_DrawText("YOU DIED", (float)WINDOW_WIDTH / 2.8f, 75.0f);
	CP_Font_DrawText(retry_button.text, gameover_button.x + gameover_button.width * 0.15f,
		retry_button.y + gameover_button.height * 0.7f);

	if (gameover_button.x <= mouseX && mouseX <= gameover_button.x + gameover_button.width
		&& quit_button.y <= mouseY && mouseY <= quit_button.y + gameover_button.height)
	{
		CP_Settings_Fill(gameover_button.hover);
		if (CP_Input_MouseClicked())
		{
			CP_Engine_Terminate();
		}
	}
	else
	{
		CP_Settings_Fill(gameover_button.idle);
	}

	CP_Graphics_DrawRect(gameover_button.x, quit_button.y, gameover_button.width, gameover_button.height);
	CP_Settings_Fill(gameover_button.text);
	CP_Font_DrawText(quit_button.text, gameover_button.x + gameover_button.width * 0.25f,
		quit_button.y + gameover_button.height * 0.7f);

	GameOver_Score((int)Time_score.count);
	CP_Settings_TextSize(100.0f);


}

void Exit_GameOver(void)
{
	
}