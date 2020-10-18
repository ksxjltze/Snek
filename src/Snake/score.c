#include "score.h"

void init_timerscore(void)
{
	Time_score.text = "Time:";
	
	Time_score.x = 850.0f;
	
}
void init_foodscore(void)
{
	Food_score.text = "Food:";

	Food_score.x = 1000.0f;
	
}
void init_score(void)
{
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
	sprintf_s(str_buffer, 16, "%.2fs", Time_score.count);

	CP_Font_DrawText(Time_score.text, Time_score.x, score.y);

	CP_Font_DrawText(str_buffer, Time_score.x + 50.0f, score.y);

	CP_Font_DrawText(Food_score.text, Food_score.x, score.y);
}

void exit_score(void)
{

}