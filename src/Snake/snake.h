#pragma once
#include <stdbool.h> //bool (true, false)
#include "MainMenu.h"
#include "score.h"
//Declare in Snake.h

void Snake_Init(void);
void Snake_Update(void);
void Snake_Exit(void);

//Movement
void Snake_UpdateInput(void);
void Snake_UpdateMovement(void);
void Snake_Timer(void);

//Draw
void Snake_Draw(void);

//Grow
void Snake_Grow(void);

//GG
void Snake_GameOver(void);