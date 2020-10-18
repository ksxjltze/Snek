#pragma once
#include "cprocessing.h"
//Declare in Snake.h
void Snake_Init(void);
void Snake_Update(void);
void Snake_Exit(void);
void Snake_UpdateInput(void);
void Snake_UpdateMovement(void);
void Snake_Draw(void);
CP_Vector Snake_CalculateMovement(int direction);
void Snake_Init_Snake(CP_Image snake_sprite);
void Snake_UpdateSegments(CP_Vector movement);

