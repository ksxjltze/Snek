#include "music.h"

void init_music(void)
{
	CP_Sound_PlayMusic(CP_Sound_LoadMusic("./Assets/snek.wav"));
}

void exit_music(void)
{
	CP_Sound_StopAll();
}
