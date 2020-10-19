#pragma once
#include "cprocessing.h"
#include "snake.h"
#include "MainMenu.h"

struct GameOver_Button
{
	float x;
	float width;
	float height;
	CP_Color hover;
	CP_Color idle;
	CP_Color text;

}GameOver_button;

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

void GameOver_button_init(void);
void init_GameOver(void);
void update_GameOver(void);
void exit_GameOver(void);