#include "button.h"
#include "snake.h"   //Game loop functions
#include <stdbool.h> //bool
#include "utils.h"   //isMouseOver_Rect()

//Button Defaults
CP_Color color_idle;
CP_Color color_hover;
CP_Color color_clicked;
CP_Color color_text;

float text_size;

void Button_Init()
{
	color_hover = CP_Color_Create(255, 0, 0, 255);
	color_idle = CP_Color_Create(0, 255, 0, 255);
	color_clicked = CP_Color_Create(0, 0, 255, 255);
	color_text = CP_Color_Create(0, 0, 0, 255);

	text_size = 100;

}

struct Button Create_Button(CP_Vector position, float width, float height)
{
	struct Button button;
	button.type = BUTTON;

	button.position = position;
	button.width = width;
	button.height = height;

	//Set Default colors
	Button_Set_Colors(&button, color_idle, color_hover, color_clicked, color_text);
	button.function = NULL;

	return button;
}

struct Button Create_TextButton(CP_Vector position, float width, float height, char* text)
{
	struct Button button = Create_Button(position, width, height);
	button.type = TEXT_BUTTON;
	button.textSize = text_size; //Default text size
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

void Button_Set_Text_Size(struct Button* button, float size)
{
	button->textSize = size;

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

void Button_Set_Callback(struct Button* button, void (*ptr)())
{
	button->function = ptr;
}

void Update_Button(struct Button button, float mouseX, float mouseY)
{
	CP_Settings_Fill(button.color.idle);
	if (isMouseOver_Rect(button.position, button.width, button.height, mouseX, mouseY))
	{
		CP_Settings_Fill(button.color.hover);

		if (CP_Input_MouseDown(MOUSE_BUTTON_1))
			CP_Settings_Fill(button.color.clicked);

		else if (CP_Input_MouseReleased(MOUSE_BUTTON_1))
		{
			if (button.function != NULL)
				Button_Execute_Callback(button.function);
		}
	}
	Draw_Button(button);
}

void Button_Execute_Callback(void (*ptr)())
{
	(*ptr)();
}

void Draw_Button_Text(struct Button button)
{
	CP_Settings_Fill(button.color.text);
	CP_Settings_TextSize(button.textSize);
	CP_Font_DrawText(button.text, button.position.x + button.width / 2,
		button.position.y + button.height / 2.5f);
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