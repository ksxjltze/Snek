#pragma once
#include "cprocessing.h"

enum Button_Types { BUTTON, TEXT_BUTTON, IMAGE_BUTTON };

struct Button_Colors
{
	CP_Color idle;
	CP_Color hover;
	CP_Color clicked;
};

struct Button
{
	int type;
	struct Button_Colors color;
	CP_Color fill;

	CP_Image image;
	const char* text;

	CP_Vector position;
	float width;
	float height;
};

struct Button Create_Button(CP_Vector position, float width, float height);
struct Button Create_TextButton(CP_Vector position, float width, float height, char* text);
struct Button Create_ImageButton(CP_Vector position, float width, float height, CP_Image image);
void Button_Set_Colors(struct Button* button, CP_Color idle, CP_Color hover, CP_Color clicked);
void Draw_Button(struct Button button);