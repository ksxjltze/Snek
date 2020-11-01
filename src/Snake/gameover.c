//---------------------------------------------------------
// file:	gameover.c
// author:	[Bryan Koh Yan Wei]
// email:	[yanweibryan.koh@digipen.edu]
//
// brief:	File which manages the gameover screen
			
//
// documentation link:
// https://inside.digipen.edu/main/GSDP:GAM100/CProcessing
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "gameover.h"

extern const int WINDOW_WIDTH, WINDOW_HEIGHT;

struct Button Button_Play;
struct Button Button_LeaderBoard;

void Draw_Gameover_Score(void)
{
	char playerscore_buffer[16];

	sprintf_s(playerscore_buffer, 16, "%d", Player.score);

	CP_Font_DrawText("Score: ", (float)WINDOW_WIDTH / 2.2f, 65.0f);
	CP_Font_DrawText(playerscore_buffer, WINDOW_WIDTH / 1.7f, 65.0f);

}


void Gameover_Init(void)
{
	Init_Menu_Button();
	void(*ptr_play)() = &MainMenu_Load_Game; // Same duty as MainMenu_Load_game even tho at gameover screen
	void(*ptr_leaderboard)() = &View_LeaderBoard;

	CP_Vector pos = CP_Vector_Zero();
	pos.x = (float)(WINDOW_WIDTH * 0.5f) - (Menu_button.width / 2);
	pos.y = (float)(WINDOW_HEIGHT * 0.5f) - (Menu_button.height / 2);

	CP_Vector pos2 = CP_Vector_Zero();
	pos2.x = (float)(WINDOW_WIDTH * 0.5f) - (Menu_button.width / 2);
	pos2.y = (float)(WINDOW_HEIGHT * 0.65f) - (Menu_button.height / 2);

	Button_Play = Create_TextButton(pos, Menu_button.width, Menu_button.height, "Retry");
	Button_LeaderBoard = Create_TextButton(pos2, Menu_button.width, Menu_button.height, "LeaderBoard");

	Button_Set_Colors(&Button_Play, Menu_button.idle, Menu_button.hover, Menu_button.clicked, Menu_button.text);
	Button_Set_Colors(&Button_LeaderBoard, Menu_button.idle, Menu_button.hover, Menu_button.clicked, Menu_button.text);

	Button_Set_Text_Size(&Button_Play, 50);
	Button_Set_Text_Size(&Button_LeaderBoard, 40);

	Button_Set_Callback(&Button_Play, ptr_play);
	Button_Set_Callback(&Button_LeaderBoard, ptr_leaderboard);

	CP_Engine_SetNextGameState(Gameover_Init, Gameover_Update, Gameover_Exit);
}

void Gameover_Update(void)
{
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));

	float mouseX = CP_Input_GetMouseX();
	float mouseY = CP_Input_GetMouseY();


	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_DrawText("GAME OVER", (float)WINDOW_WIDTH / 2.0f, 25.0f);
	Draw_Gameover_Score();
	Update_Button(Button_Play, mouseX, mouseY);
	Update_Button(Button_LeaderBoard, mouseX, mouseY);

	Check_If_Leader();
	Player_Is_Leader();
}

void Gameover_Exit(void)
{

}