#include "score.h"

static const int WINDOW_WIDTH = 1200, WINDOW_HEIGHT = 800;

void init_timerscore(void) // Variables for time elasped score
{
	Time_score.text = "Time:";
	
	Time_score.x = (float)(WINDOW_WIDTH / 1.41);
	
}
void init_foodscore(void) // Variables for food eaten score
{
	Food_score.text = "Food:";

	Food_score.x = (float)(WINDOW_WIDTH / 1.2);
	
}
void init_score(void) // global variables for the two typedef struct
{
	Time_score.offset = CP_System_GetSeconds(); // To offset time difference between start of engine and start of game
	
	score.y = 50.0f;

	score.text = CP_Color_Create(255, 255, 255, 255);

	CP_Settings_Fill(score.text);

	init_timerscore();
	init_foodscore();
}

void update_score(void)
{
	CP_Settings_TextSize(20.0f);
	Time_score.count = CP_System_GetSeconds();
	char str_buffer[16];
	sprintf_s(str_buffer, 16, "%.2fs", (double)Time_score.count - (double)Time_score.offset); // casted to double to prevent overflow

	CP_Font_DrawText(Time_score.text, Time_score.x, score.y);

	CP_Font_DrawText(str_buffer, Time_score.x + 50.0f, score.y);

	CP_Font_DrawText(Food_score.text, Food_score.x, score.y);

	score.total = Food_score.count + (int)Time_score.count; // combined food and time score

	if (CP_Input_KeyTriggered(KEY_Q))
	{
		GameOver_score(score.total); // call gameover_score to print total score at gameover screen
		exit_music();

		int error;
		int ab = 0;

		FILE* highscore;

		fopen_s(&highscore, "./Snek/src/Snake/Score.txt", "w"); // create score.txt 
	
		fprintf(highscore, "0");

		error = fopen_s(&highscore, "./Snek/src/Snake/Score.txt", "r");
		if (error != 0)
		{
			return;
		}
		else
		{
			if (highscore != NULL)
			{
				while (!feof(highscore))
				{
					fscanf_s(highscore, "%d", &ab);
				}
				if (score.total > ab)
				{
					fopen_s(&highscore, "./Snek/src/Snake/Score.txt", "a");
					fprintf(highscore, "%d,", score.total);
				}
			}
				
		fclose(highscore); // 150, 1, 5, 0. 


		}
		CP_Engine_SetNextGameState(init_GameOver, update_GameOver, exit_GameOver); // placeholder for death
	}
}

void exit_score(void)
{

}