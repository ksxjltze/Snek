#pragma once
#include "cprocessing.h"
#include "button.h"

struct Menu_Button
{
	float width;
	float height;
	CP_Color hover;
	CP_Color idle;
	CP_Color clicked;
	CP_Color text;
}Menu_button;


void Init_Menu_Button(void);
void Button_init(void);
void Button_update(void);

void Menu_init(void);
void Menu_update(void);
void Menu_exit(void);

void MainMenu_Load_Game();
void MainMenu_Exit_Game();
void View_LeaderBoard(void);
