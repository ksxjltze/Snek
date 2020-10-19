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

void Draw_Button(struct Button button)
{
	CP_Vector position = button.position;
	CP_Graphics_DrawRect(position.x, position.y, button.width, button.height);

	switch (button.type)
	{
	case BUTTON:
		break;
	case TEXT_BUTTON:
		CP_Font_DrawText(button.text, 
			position.x + button.width / 4, 
			position.y + button.height / 1.3f);
		break;
	case IMAGE_BUTTON:
		CP_Image_Draw(button.image, 
			position.x + button.width / 2, 
			position.y + button.height / 2, 
			button.width, button.height, 255);
		break;
	default:
		break;
	}
}