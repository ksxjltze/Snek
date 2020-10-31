#pragma once
#include "cprocessing.h"
#include "score.h"
#include <stdio.h>
#include "button.h"
#include <string.h>

struct LeaderBoard
{
	CP_Color text_color;
	const char* text;
	float x, y;
}Leaderboard_Variables;


typedef struct Leaders
{
	char name[20];
	int score;
} Leader;

void Init_LeaderBoard(void);
void Update_LeaderBoard(void);
void Exit_LeaderBoard(void);

void Read_Leaderboard_Data(void);
void Write_Leaderboard_Data(void);
void Check_If_Leader(void);
void LeaderBoard_ReadInput();
void Draw_LeaderBoard(void);
void Load_Main_Menu(void);
void Draw_LeaderBoard(void);

void LeaderBoard_Display_PlayerName();