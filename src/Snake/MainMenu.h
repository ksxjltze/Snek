#pragma once
#include "cprocessing.h"

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

struct Button
{
	int type;

	CP_Image image;
	const char* text;

	CP_Vector position;
	float width;
	float height;
};

enum Button_Types { BUTTON, TEXT_BUTTON, IMAGE_BUTTON };

void Button_init(void);
void Button_update(void);
void Menu_init(void);
void Menu_update(void);
void Menu_exit(void);

struct Button Create_Button(CP_Vector position, float width, float height);
struct Button Create_TextButton(CP_Vector position, float width, float height, char* text);
struct Button Create_ImageButton(CP_Vector position, float width, float height, CP_Image image);

