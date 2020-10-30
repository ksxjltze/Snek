#include "music.h"

void Play_Music(void)
{
	CP_Sound_PlayMusic(CP_Sound_LoadMusic("./Assets/snek.wav"));
}

void Stop_Music(void)
{
	CP_Sound_StopAll();
}
