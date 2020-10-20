#include "MainMenu.h"
#include "snake.h"

static const int WINDOW_WIDTH = 1200, WINDOW_HEIGHT = 800;
struct Button Button_Play;
struct Button Button_Exit;

void Menu_init(void)
{
	CP_System_SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	CP_Settings_TextSize(100.0f);
	Button_init();
}
void Menu_update(void)
{	
	Button_update();
}

void Menu_exit(void)
{

}

void Init_Menu_Button(void)
{
	Menu_button.width = 300.0f;
	Menu_button.height = 100.0f;

	Menu_button.hover = CP_Color_Create(255, 0, 0, 255);
	Menu_button.idle = CP_Color_Create(0, 255, 0, 255);
	Menu_button.clicked = CP_Color_Create(0, 0, 255, 255);
	Menu_button.text = CP_Color_Create(0, 0, 0, 255);
}

void Button_init(void)
{
	Init_Menu_Button();

	CP_Vector pos = CP_Vector_Zero();
	pos.x = (float)(WINDOW_WIDTH / 2.0f) - (Menu_button.width / 2);
	pos.y = (float)(WINDOW_HEIGHT / 4.0f) - (Menu_button.height / 2);	
	
	CP_Vector pos2 = CP_Vector_Zero();
	pos2.x = (float)(WINDOW_WIDTH / 2.0f) - (Menu_button.width / 2);
	pos2.y = (float)(WINDOW_HEIGHT / 2.0f) + (Menu_button.height / 2);

	Button_Play = Create_TextButton(pos, Menu_button.width, Menu_button.height, "Play");
	Button_Exit = Create_TextButton(pos2, Menu_button.width, Menu_button.height, "Exit");

	Button_Set_Colors(&Button_Play, Menu_button.idle, Menu_button.hover, Menu_button.clicked, Menu_button.text);
	Button_Set_Colors(&Button_Exit, Menu_button.idle, Menu_button.hover, Menu_button.clicked, Menu_button.text);


	//start_button.Play = "Play";
	//start_button.x = (float)(WINDOW_WIDTH / 2.0f) - (Menu_button.width / 2);
	//start_button.y = (float)(WINDOW_HEIGHT / 4.0f) - (Menu_button.height / 2);

	//exit_button.Exit = "Exit";
	//exit_button.x = (float)(WINDOW_WIDTH / 2.0f) - (Menu_button.width / 2);
	//exit_button.y = (float)(WINDOW_HEIGHT / 2.0f) + (Menu_button.height / 2);
}

void Button_update(void)
{
	//Clear Buffer
	CP_Settings_Background(CP_Color_Create(160, 160, 160, 255));

	float mouseX = CP_Input_GetMouseX();
	float mouseY = CP_Input_GetMouseY();

	Update_Button(Button_Play, mouseX, mouseY);
	Update_Button(Button_Exit, mouseX, mouseY);

	//if (start_button.x <= mouseX && mouseX <= start_button.x + Menu_button.width
	//	&& start_button.y <= mousey && mousey <= start_button.y + Menu_button.height)
	//{
	//	CP_Settings_Fill(Menu_button.hover);
	//	if (CP_Input_MouseClicked())
	//	{	
	//		CP_Engine_SetNextGameState(Snake_Init, Snake_Update, Snake_Exit);
	//	}
	//}
	//else
	//{
	//	CP_Settings_Fill(Menu_button.idle);
	//}

	//CP_Graphics_DrawRect(start_button.x, start_button.y, Menu_button.width, Menu_button.height);
	//CP_Settings_Fill(Menu_button.text);
	//CP_Font_DrawText(start_button.Play, start_button.x + Menu_button.width / 4,
	//	start_button.y + Menu_button.height / 1.3f);

	// if (exit_button.x <= mouseX && mouseX <= exit_button.x + Menu_button.width
	//	&& exit_button.y <= mousey && mousey <= exit_button.y + Menu_button.height)
	//{
	//	CP_Settings_Fill(Menu_button.hover);
	//	if (CP_Input_MouseClicked())
	//	{
	//		CP_Engine_Terminate();
	//	}
	//}
	//else
	//{
	//	CP_Settings_Fill(Menu_button.idle);
	//}
	//CP_Graphics_DrawRect(exit_button.x, exit_button.y, Menu_button.width, Menu_button.height);
	//CP_Settings_Fill(Menu_button.text);
	//CP_Font_DrawText(exit_button.Exit, exit_button.x + Menu_button.width / 4,
	//	exit_button.y + Menu_button.height / 1.3f);
}