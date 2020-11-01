//---------------------------------------------------------
// file:	pause.c
// author:	Lee Jia Keat
// email:	l.jiakeat@digipen.edu
//
// brief:	Pause menu.
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

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
	backgroundColor = CP_Color_Create(0, 0, 0, 255);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);

	float width, height;
	float offsetX;

	width = WINDOW_WIDTH * 0.6f;
	height = 100;
	offsetX = width / 2;

	CP_Vector pos_continue = CP_Vector_Set((float)WINDOW_WIDTH / 2 - offsetX, (float)WINDOW_HEIGHT * 0.25f);
	CP_Vector pos_restart = CP_Vector_Set((float)WINDOW_WIDTH / 2 - offsetX, (float)WINDOW_HEIGHT * 0.5f);
	CP_Vector pos_quit = CP_Vector_Set((float)WINDOW_WIDTH / 2 - offsetX, (float)WINDOW_HEIGHT * 0.75f);

	menu.btn_Continue = Create_TextButton(pos_continue, width, height, "Continue");
	menu.btn_Restart = Create_TextButton(pos_restart, width, height, "Restart");
	menu.btn_Quit = Create_TextButton(pos_quit, width, height, "Quit");

	CP_Color idle = CP_Color_Create(100, 100, 100, 255);
	CP_Color hover = CP_Color_Create(100, 0, 100, 255);
	CP_Color clicked = CP_Color_Create(100, 100, 0, 255);
	CP_Color text = CP_Color_Create(255, 255, 255, 255);

	Button_Set_Colors(&menu.btn_Continue, idle, hover, clicked, text);
	Button_Set_Colors(&menu.btn_Restart, idle, hover, clicked, text);
	Button_Set_Colors(&menu.btn_Quit, idle, hover, clicked, text);

	Button_Set_Callback(&menu.btn_Continue, &Snake_Pause_Continue);
	Button_Set_Callback(&menu.btn_Restart, &Snake_Pause_Restart);
	Button_Set_Callback(&menu.btn_Quit, &Snake_Pause_Quit);
}

void Snake_Pause_Quit()
{
	Snake_Quit();
}

void Snake_Pause_Restart()
{
	Snake_Reset();
}

void Snake_Pause_Continue()
{
	Snake_UnPause();
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
	Update_Button(menu.btn_Restart, mouseX, mouseY);
	Update_Button(menu.btn_Quit, mouseX, mouseY);

}
