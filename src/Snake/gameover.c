#include "gameover.h"
#include "snake.h"

extern const int WINDOW_WIDTH, WINDOW_HEIGHT;
int hs = 0;

void GameOver_Score(int total_score, int high_score)// function to print score
{
	char playerscore_buffer[16]; //buffer for current game score
	char highscore_buffer[16]; // buffer for highscore
	CP_Settings_TextSize(50.0f);
	hs = high_score;
	
	sprintf_s(playerscore_buffer, 16, "%d", total_score - (int)Time_score.offset); 
	sprintf_s(highscore_buffer, 16, "%d", hs);

	CP_Font_DrawText(gameover_score.text, (float)WINDOW_WIDTH / 2.5f, WINDOW_HEIGHT / 2.5f);
	CP_Font_DrawText(highscore.text, (float)WINDOW_WIDTH / 2.5f, WINDOW_HEIGHT / 2.0f);
	
	CP_Font_DrawText(playerscore_buffer, WINDOW_WIDTH / 1.6f, WINDOW_HEIGHT / 2.5f);
	CP_Font_DrawText(highscore_buffer, WINDOW_WIDTH / 1.6f, WINDOW_HEIGHT / 2.0f);
}

void GameOver_Button_Init(void) //initialize variables for the buttons on gameover screen
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
	Exit_Music();

	gameover_score.text = "Your score:";
	highscore.text = "High score:";
}

void Update_GameOver(void) // updates the rendering based on 
{
	float mouseX = CP_Input_GetMouseX();
	float mouseY = CP_Input_GetMouseY();

	CP_Settings_Background(CP_Color_Create(160, 160, 160, 255));

	if (gameover_button.x <= mouseX && mouseX <= gameover_button.x + gameover_button.width
		&& retry_button.y <= mouseY && mouseY <= retry_button.y + gameover_button.height) // applies colour to the button if mouse is hovering over
	{
		CP_Settings_Fill(gameover_button.hover);
		if (CP_Input_MouseClicked()) // check for retry button input
		{
			CP_Engine_SetNextGameState(Snake_Init, Snake_Update, Snake_Exit); //initialize game if retry clicked
		}
	}
	else
	{
		CP_Settings_Fill(gameover_button.idle); // fill button with default color
	}
	
	CP_Graphics_DrawRect(gameover_button.x, retry_button.y, gameover_button.width, gameover_button.height);//draw retry button
	CP_Settings_Fill(gameover_button.text);//set color for text

	CP_Font_DrawText("YOU DIED", (float)WINDOW_WIDTH / 2.8f, 75.0f);// draw "YOU DIED"

	CP_Font_DrawText(retry_button.text, gameover_button.x + gameover_button.width * 0.15f,
		retry_button.y + gameover_button.height * 0.7f); // draw "retry" text inside button

	if (gameover_button.x <= mouseX && mouseX <= gameover_button.x + gameover_button.width // check if mouse is hovering over quit button
		&& quit_button.y <= mouseY && mouseY <= quit_button.y + gameover_button.height)
	{
		CP_Settings_Fill(gameover_button.hover);
		if (CP_Input_MouseClicked())
		{
			CP_Engine_Terminate(); //termiante the engine if mouse input while over quit button
		}
	}
	else
	{
		CP_Settings_Fill(gameover_button.idle); // fill in default color if not hovering
	}

	CP_Graphics_DrawRect(gameover_button.x, quit_button.y, gameover_button.width, gameover_button.height);// draw rectangular button for quit option
	CP_Settings_Fill(gameover_button.text); // set color for text
	CP_Font_DrawText(quit_button.text, gameover_button.x + gameover_button.width * 0.25f,
		quit_button.y + gameover_button.height * 0.7f); // draw "quit" over the button

	GameOver_Score((int)Time_score.count, hs); // call gameover_score which prints the final player score
	CP_Settings_TextSize(100.0f); // reset text size back to 100.0f
}

void Exit_GameOver(void)
{
	
}