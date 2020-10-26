#include "score.h"

extern const int WINDOW_WIDTH, WINDOW_HEIGHT;
int high_score = 0;

void Init_Timerscore(void) // Variables for time elasped score
{
	Time_score.text = "Time:";
	
	Time_score.x = (float)(WINDOW_WIDTH / 1.41);
	
}
void Init_Foodscore(void) // Variables for food eaten score
{
	Food_score.text = "Food:";
	Food_score.count = 0;

	Food_score.x = (float)(WINDOW_WIDTH / 1.2);
	
}
void Init_Score(void) // global variables for the two typedef struct
{
	Time_score.offset = CP_System_GetSeconds(); // To offset time difference between start of engine and start of game
	
	score.y = 50.0f;

	score.text = CP_Color_Create(255, 255, 255, 255);

	CP_Settings_Fill(score.text);

	Init_Timerscore();
	Init_Foodscore();
}

void Update_Score(void)
{
	CP_Settings_TextSize(20.0f);
	Time_score.count = CP_System_GetSeconds();
	char timescore_buffer[16];
	char foodscore_buffer[16];

	sprintf_s(timescore_buffer, 16, "%.2fs", (double)Time_score.count - (double)Time_score.offset); // casted to double to prevent overflow
	sprintf_s(foodscore_buffer, 16, "%d", Food_score.count);

	CP_Font_DrawText(Time_score.text, Time_score.x, score.y);

	CP_Font_DrawText(timescore_buffer, Time_score.x + 50.0f, score.y);

	CP_Font_DrawText(Food_score.text, Food_score.x, score.y);
	CP_Font_DrawText(foodscore_buffer, Food_score.x + 50.0f, score.y);
	score.total = Food_score.count  + (int)Time_score.count - (int)Time_score.offset; // combined food and time score

	if (CP_Input_KeyTriggered(KEY_Q))
	{

		Highscore_Manager(score.total, &high_score);// check against registered highscore
		GameOver_Score(score.total, high_score); // call gameover_score to print total score at gameover screen
		CP_Engine_SetNextGameState(Init_GameOver, Update_GameOver, Exit_GameOver); // placeholder for death
	}
}

void Exit_Score(void)
{

}

void Highscore_Manager(int player_score, int* highscore_ptr)
{
	ReadFile(&high_score);
	*highscore_ptr = high_score;

	if (player_score > high_score)
	{
		WriteFile(player_score);
	}
}