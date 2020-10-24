#include "music.h"

void Init_Music(void)
{
	CP_Sound_PlayMusic(CP_Sound_LoadMusic("./Assets/snek.wav"));
}

void Exit_Music(void)
{
	CP_Sound_StopAll();
}
