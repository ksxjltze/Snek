#pragma once

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
void Snake_DrawGrid(void);
void Snake_DrawBoundary(void);

//Grid and Boundary
void Snake_SetGrid(void);
void Snake_SetBoundary(void);

//Grow
void Snake_Eat(void);
void Snake_Grow(void);