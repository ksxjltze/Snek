#include "score.h"
static const int WINDOW_WIDTH = 1200, WINDOW_HEIGHT = 800;
void init_timer(void)
{
	CP_Settings_TextSize(100.0f);

	timer.x = 400.0f;
	timer.y = 400.0f;
	timer.text = CP_Color_Create(255, 255, 255, 255);
}

void init_score(void)
{
	init_timer();
}

void update_score(void)
{
	timer.count = CP_System_GetSeconds();
	char str_buffer[16];
	sprintf_s(str_buffer, 16, "%.2f", 200.0f);

	CP_Font_DrawText("Hello World", 400.0f, 400.0f);
}

void exit_score(void)
{

}