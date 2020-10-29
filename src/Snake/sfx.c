#include "sfx.h"

void Init_SFX()
{
	CP_Sound_Play(CP_Sound_LoadMusic("./Assets/Crunch_1.wav"));
}

void Exit_SFX() 
{
	CP_Sound_StopAll();
}