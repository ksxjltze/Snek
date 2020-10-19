#pragma once
#include "cprocessing.h"

enum Button_Types { BUTTON, TEXT_BUTTON, IMAGE_BUTTON };

struct Button
{
	int type;

	CP_Image image;
	const char* text;

	CP_Vector position;
	float width;
	float height;
};

struct Button Create_Button(CP_Vector position, float width, float height);
struct Button Create_TextButton(CP_Vector position, float width, float height, char* text);
struct Button Create_ImageButton(CP_Vector position, float width, float height, CP_Image image);