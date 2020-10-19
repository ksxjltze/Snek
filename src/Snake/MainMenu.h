#pragma once
#include "cprocessing.h"
#include "button.h"

struct Menu_Button
{
	float width;
	float height;
	CP_Color hover;
	CP_Color idle;
	CP_Color text;
}Menu_button;

struct Button1
{	
	const char* Play;
	float x;
	float y;
}start_button;

struct Button2
{
	const char* Exit;
	float x;
	float y;
}exit_button;

void Button_init(void);
void Button_update(void);
void Menu_init(void);
void Menu_update(void);
void Menu_exit(void);

