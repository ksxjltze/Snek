#include "button.h"

struct Button Create_Button(CP_Vector position, float width, float height)
{
	struct Button button;
	button.type = BUTTON;

	button.position = position;
	button.width = width;
	button.height = height;

	return button;
}

struct Button Create_TextButton(CP_Vector position, float width, float height, char* text)
{
	struct Button button = Create_Button(position, width, height);
	button.type = TEXT_BUTTON;
	button.text = text;

	return button;
}

struct Button Create_ImageButton(CP_Vector position, float width, float height, CP_Image image)
{
	struct Button button = Create_Button(position, width, height);
	button.type = TEXT_BUTTON;
	button.image = image;

	return button;
}