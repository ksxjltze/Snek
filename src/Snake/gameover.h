#pragma once
#include "cprocessing.h"
#include "snake.h"
#include "MainMenu.h"
#include "score.h"


struct GameOver_score
{
	const char* text;
	int score;
	float x, y;
}gameover_score;


struct GameOver_Button
{
	float x;
	float width;
	float height;
	CP_Color hover;
	CP_Color idle;
	CP_Color text;

}gameover_button;

struct Retry_button
{
	const char* text;
	float y;

}retry_button;

struct Quit_button
{
	const char* text;
	float y;
}quit_button;

void GameOver_Score(int total_score);
void GameOver_Button_Init(void);
void Init_GameOver(void);
void Update_GameOver(void);
void Exit_GameOver(void);