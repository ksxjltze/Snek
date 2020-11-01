//---------------------------------------------------------
// file:	score.c
// author:	[Bryan Koh Yan Wei]
// email:	[yanweibryan.koh@digipen.edu]
//
// brief:	Function which track, calculates and draws the score to the screen
//
// documentation link:
// https://inside.digipen.edu/main/GSDP:GAM100/CProcessing
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "score.h"

extern const int WINDOW_WIDTH, WINDOW_HEIGHT;
int high_score = 0;

void Init_Scores_Var(void)
{
	score.y = 50.0f;									// Common Y-axis var to print location
	score.text = CP_Color_Create(255, 255, 255, 255);	// Create color for text score
	CP_Settings_Fill(score.text);						// Set text color to white

	Time_score.text = "Time:";							// Variables for time related score
	Time_score.x = (float)(WINDOW_WIDTH / 1.41);
	Time_score.offset = CP_System_GetSeconds();			// Offset to calculate difference between start of engine and start of game

	Food_score.text = "Food:";							// Variables for food related score
	Food_score.x = (float)(WINDOW_WIDTH / 1.2);
}

void Draw_Score(void)									// Function to draw score at gameover screen
{
	CP_Settings_TextSize(20.0f);						// Setting text size of scores
	Time_score.count = CP_System_GetSeconds();			// CP Library function used to calculate time score.
	char timescore_buffer[16];
	char foodscore_buffer[16];

	sprintf_s(timescore_buffer, 16, "%.2fs", (double)Time_score.count - (double)Time_score.offset); // Set time score to char buffer
	sprintf_s(foodscore_buffer, 16, "%d", Food_score.count);										// Set food score to char buffer

	CP_Font_DrawText(Time_score.text, Time_score.x, score.y);										// Draw Time text

	CP_Font_DrawText(timescore_buffer, Time_score.x + 50.0f, score.y);;								// Draw Time score (stop watch)

	CP_Font_DrawText(Food_score.text, Food_score.x, score.y);										// Draw Food text
	CP_Font_DrawText(foodscore_buffer, Food_score.x + 50.0f, score.y);								// Draw Food score
	
	Player.score = ((int)Time_score.count) - (int)Time_score.offset + 5* Food_score.count;			// combined food and time score.
}


void Update_Score(void)									//Draws scores to screen every frame	
{
	Draw_Score();
}

void Exit_Score(void)
{

}