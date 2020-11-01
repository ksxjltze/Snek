//---------------------------------------------------------
// file:	music.c
// author:	[Bryan Koh Yan Wei]
// email:	[yanweibryan.koh@digipen.edu]
//
// brief:	code for background music during gameplay
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------
#include "music.h"
int playing;

/// <Play music>
/// 
/// </summary>
/// <param name= void""></nil>

void Play_Music(void)
{
	playing = 1;
	CP_Sound_PlayMusic(CP_Sound_LoadMusic("./Assets/unhtz.wav"));
}

void Stop_Music(void)
{
	playing = 0;
	CP_Sound_StopAll();
}

void Toggle_Music(void)
{
	if (playing)
		Stop_Music();
	else
		Play_Music();
}
