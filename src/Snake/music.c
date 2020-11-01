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

/// <Play music>
/// 
/// </summary>
/// <param name= void""></nil>

void Play_Music(void)
{
	CP_Sound_PlayMusic(CP_Sound_LoadMusic("./Assets/snakelmao.wav"));
}

void Stop_Music(void)
{
	CP_Sound_StopAll();
}
