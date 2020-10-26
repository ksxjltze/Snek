#include "pause.h"
CP_Color backgroundColor;

struct PauseMenu
{
	struct Button btn_Continue;
	struct Button btn_Restart;
	struct Button btn_Quit;
}menu;

void Snake_PauseMenu_Init()
{
	float width, height;
	float offsetX, offsetY;

	width = 800;
	height = 100;

	offsetX = width / 2;
	offsetY = height / 2;

	backgroundColor = CP_Color_Create(0, 0, 0, 255);
	CP_Vector pos_continue = CP_Vector_Set((float)WINDOW_WIDTH / 2 - offsetX, (float)WINDOW_HEIGHT / 2 - offsetY);
	menu.btn_Continue = Create_TextButton(pos_continue, width, height, "Continue");

	CP_Color idle = CP_Color_Create(100, 100, 100, 255);
	CP_Color hover = CP_Color_Create(100, 0, 100, 255);
	CP_Color clicked = CP_Color_Create(100, 100, 0, 255);
	CP_Color text = CP_Color_Create(255, 255, 255, 255);

	Button_Set_Colors(&menu.btn_Continue, idle, hover, clicked, text);
}

bool Snake_Pause(bool isPaused)
{
	return !isPaused;
}

void Snake_PauseMenu_Update()
{
	float mouseX, mouseY;
	mouseX = CP_Input_GetMouseX();
	mouseY = CP_Input_GetMouseY();

	CP_Settings_Background(backgroundColor);
	Update_Button(menu.btn_Continue, mouseX, mouseY);

}
