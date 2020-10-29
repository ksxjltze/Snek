#pragma once
#include "cprocessing.h"

enum Button_Types { BUTTON, TEXT_BUTTON, IMAGE_BUTTON };

struct Button_Colors
{
	CP_Color idle;
	CP_Color hover;
	CP_Color clicked;
	CP_Color text;
};

struct Button
{
	int type;
	struct Button_Colors color;
	void(*function)();

	CP_Image image;
	const char* text;
	float textSize;

	CP_Vector position;
	float width;
	float height;
};

struct Button Create_Button(CP_Vector position, float width, float height);
struct Button Create_TextButton(CP_Vector position, float width, float height, char* text);
struct Button Create_ImageButton(CP_Vector position, float width, float height, CP_Image image);

void Button_Set_Colors(struct Button* button, CP_Color idle, CP_Color hover, CP_Color clicked, CP_Color text);
void Button_Set_Text_Size(struct Button* button, float size);

void Update_Button(struct Button button, float mouseX, float mouseY);

void Draw_Button(struct Button button);
void Draw_Button_Text(struct Button button);
void Draw_Button_Image(struct Button button);

void Button_Set_Callback(struct Button* button, void(*ptr)());
void Button_Execute_Callback(void(*ptr)());

void Button_Init();