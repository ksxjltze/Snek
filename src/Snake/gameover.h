#pragma once
#include "cprocessing.h"
#include "snake.h"
#include "MainMenu.h"
#include "score.h"
#include "music.h"
#include "files.h"
#include "food.h"
#include "MainMenu.h"
#include "leaderboard.h"
#include <stdbool.h>

struct Highscore
{
	float x, y;
	const char* text;
}highscore;


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

void Draw_GameOver_Score(void);
void GameOver_Var_Init(void);
void GameOver_Update_Input(void);
void Init_GameOver(void);
void Update_GameOver(void);
void Exit_GameOver(void);

void Draw_Gameover_Score(void);
void Gameover_Init(void);
void Gameover_Update(void);
void Gameover_Exit(void);