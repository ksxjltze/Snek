#include "MainMenu.h"
#include "snake.h"

extern const int WINDOW_WIDTH, WINDOW_HEIGHT;
struct Button Button_Play;
struct Button Button_Exit;

void Menu_init(void)
{
	CP_System_SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	Button_init();
}
void Menu_update(void)
{	
	CP_Image_Draw(CP_Image_Load("./Assets/Menu.png"), WINDOW_WIDTH / 2.0f, 
		WINDOW_HEIGHT / 2.0f, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT, 255);
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

void MainMenu_Load_Game()
{
	CP_Engine_SetNextGameState(Snake_Init, Snake_Update, Snake_Exit);
}

void MainMenu_Exit_Game()
{
	CP_Engine_Terminate();
}

void Button_init(void)
{
	Init_Menu_Button();
	void(*ptr_play)() = &MainMenu_Load_Game;
	void(*ptr_exit)() = &MainMenu_Exit_Game;

	CP_Vector pos = CP_Vector_Zero();
	pos.x = (float)(WINDOW_WIDTH * 0.5f) - (Menu_button.width / 2);
	pos.y = (float)(WINDOW_HEIGHT * 0.3f) - (Menu_button.height / 2);	
	
	CP_Vector pos2 = CP_Vector_Zero();
	pos2.x = (float)(WINDOW_WIDTH * 0.5f) - (Menu_button.width / 2);
	pos2.y = (float)(WINDOW_HEIGHT * 0.5f) - (Menu_button.height / 2);

	Button_Play = Create_TextButton(pos, Menu_button.width, Menu_button.height, "Play");
	Button_Exit = Create_TextButton(pos2, Menu_button.width, Menu_button.height, "Exit");

	Button_Set_Colors(&Button_Play, Menu_button.idle, Menu_button.hover, Menu_button.clicked, Menu_button.text);
	Button_Set_Colors(&Button_Exit, Menu_button.idle, Menu_button.hover, Menu_button.clicked, Menu_button.text);

	Button_Set_Text_Size(&Button_Play, 100);
	Button_Set_Text_Size(&Button_Exit, 100);

	Button_Set_Callback(&Button_Play, ptr_play);
	Button_Set_Callback(&Button_Exit, ptr_exit);

}

void Button_update(void)
{
	//Clear Buffer
	CP_Settings_Background(CP_Color_Create(160, 160, 160, 255));

	float mouseX = CP_Input_GetMouseX();
	float mouseY = CP_Input_GetMouseY();

	Update_Button(Button_Play, mouseX, mouseY);
	Update_Button(Button_Exit, mouseX, mouseY);
}