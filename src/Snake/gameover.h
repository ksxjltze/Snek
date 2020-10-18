#pragma once
#include "Cprocessing.h"

struct Death
{
	CP_Image screen;
}gameover;

struct Button
{
	float width;
	float height;
	CP_Color color;

}button;

struct Retry
{
	const char* text;
	float x;
	float y;

}retry_button;

struct Quit_Button
{
	const char* text;
	float x;
	float y;
}quiit_button;

void gameover_button(void);
void gameover_init(void);
void gameover_update(void);
void gameover_exit(void);