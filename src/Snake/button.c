#include "button.h"
#include "snake.h"   //Game loop functions
#include <stdbool.h> //bool
#include "utils.h"   //isMouseOver_Rect()

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

void Button_Set_Colors(struct Button* button, CP_Color idle, CP_Color hover, CP_Color clicked, CP_Color text)
{
	struct Button_Colors colors;
	colors = button->color;

	colors.idle = idle;
	colors.hover = hover;
	colors.clicked = clicked;
	colors.text = text;

	button->color = colors;
}

void Update_Button(struct Button button, float mouseX, float mouseY)
{
	CP_Settings_Fill(button.color.idle);
	if (isMouseOver_Rect(button.position, button.width, button.height, mouseX, mouseY))
	{
		CP_Settings_Fill(button.color.hover);

		if (CP_Input_MouseDown(MOUSE_BUTTON_1))
			CP_Settings_Fill(button.color.clicked);

		else if(CP_Input_MouseReleased(MOUSE_BUTTON_1))
			CP_Engine_SetNextGameState(Snake_Init, Snake_Update, Snake_Exit);
	}
	Draw_Button(button);
}

void Draw_Button_Text(struct Button button)
{
	CP_Settings_Fill(button.color.text);
	CP_Font_DrawText(button.text, button.position.x + button.width / 4,
		button.position.y + button.height / 1.3f);
}

void Draw_Button_Image(struct Button button)
{
	CP_Vector position = button.position;
	CP_Image_Draw(button.image,
		position.x + button.width / 2,
		position.y + button.height / 2,
		button.width, button.height, 255);
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
		Draw_Button_Text(button);
		break;
	case IMAGE_BUTTON:
		Draw_Button_Image(button);
		break;
	default:
		break;
	}
}