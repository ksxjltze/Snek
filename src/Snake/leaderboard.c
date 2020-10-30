
#include "leaderboard.h"

#define MAX_NAME_CHAR 20
#define MAX_LEADERS 3

Leader LeaderBoard[MAX_LEADERS];
int x = 0;


void Read_Leaderboard_Data(void)
{
	FILE* leaderboard_scores;
	errno_t error;

	error = fopen_s(&leaderboard_scores, "leaderboard.txt", "r");

	if (leaderboard_scores == 0 || leaderboard_scores == NULL)
	{
		fopen_s(&leaderboard_scores, "leaderboard.txt", "w");		// write empty placement in?
		fprintf(leaderboard_scores, "%s %d", "Leaderboards are empty!", 0);	// write into the file leader boards are empty
		return;
	}
	else if (error == 0)						// 0 is successful.
	{
		char buffer[MAX_NAME_CHAR];			// char array of max 30 characters.
		int leaders_count = 0;

		while (fgets(buffer, MAX_NAME_CHAR, leaderboard_scores) != NULL)
		{
			if (leaders_count < MAX_LEADERS)
			{
				break;							// I only want 3 leaders
			}

			//int test = 0;
			//int a = sscanf_s(buffer, "%d", &test);
			int a = sscanf_s(buffer, "%s %d", LeaderBoard[leaders_count].name, (unsigned)sizeof buffer, &LeaderBoard[leaders_count].score);

			if (a != 2)
			{
				// TODO complain about incorect format. But while reading from .txt file, should be no problems.
			}
			else
			{
				leaders_count++;
			}
		}
	}
	fclose(leaderboard_scores);
}

void Write_Leaderboard_Data(void)
{
	FILE* leaderboard_scores;
	errno_t error;

	error = fopen_s(&leaderboard_scores, "leaderboard.txt", "w");

	if (leaderboard_scores == 0) //file not found
	{
		return;
	}

	else if (error == 0)		// error = 0 successfully opened
	{
		for (int i = 0; i < MAX_LEADERS; i++)
		{
			Leader leader = LeaderBoard[i];
			if (LeaderBoard[i].score < Player.score) // check if total score is higher than any registered leader score
			{
				leader.score = Player.score; // if higher, write score total as leader score
				leader.name = Player.name;
			}
		}
		fclose(leaderboard_scores);
	}
}

void Check_If_Leader(void)
{
	for (int i = 0; i < MAX_LEADERS; i++)
	{
		if (Player.score > LeaderBoard[i].score)		// If true, draw different screen for leaderboard?????
		{
			CP_Engine_SetNextGameState(Init_LeaderBoard, Update_LeaderBoard, Exit_LeaderBoard);
		}
		else
			CP_Engine_SetNextGameState(Init_GameOver, Update_GameOver, Exit_GameOver);		// Normal gameover screen
	}
}

void Init_LeaderBoard(void)
{	
	Leaderboard_Variables.text_color = CP_Color_Create(255, 255, 255, 255);
	Leaderboard_Variables.text = "Leaders:";
	Leaderboard_Variables.x = (float)(WINDOW_WIDTH / 2.0);
	Leaderboard_Variables.y = (float)(WINDOW_HEIGHT / 5.0);

	Read_Leaderboard_Data();

}

void Update_LeaderBoard(void)
{

	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_TextSize(50.0f);

	CP_Font_DrawTextBox("CONGRATULATIONS, YOU WON A SPOT ON THE LEADERBOARD\n"
		"Please Enter Your Name! (Up to 20 characters)", (float)WINDOW_WIDTH / 2, (float)WINDOW_HEIGHT / 2, 100.0f);

	LeaderBoard_ReadInput();
	CP_Font_DrawText(Player.name, 100, 100);

	Draw_LeaderBoard();

}

void LeaderBoard_ReadInput()
{
	if (x >= MAX_NAME_CHAR)
		return;

	for (int i = KEY_A; i < KEY_Z; i++)
	{
		if (CP_Input_KeyTriggered(i))
		{
			Player.name[x] = (char)i;
			x++;
		}
	}
}

void Draw_LeaderBoard(void)
{
	CP_Settings_TextSize(50.0f);
	CP_Settings_Fill(Leaderboard_Variables.text_color);
	CP_Font_DrawText(Leaderboard_Variables.text, Leaderboard_Variables.x, Leaderboard_Variables.y);

	for (int i = 0; i < MAX_LEADERS; i++)
	{
		CP_Font_DrawText(LeaderBoard[i].name, Leaderboard_Variables.x, Leaderboard_Variables.y + 50.0f + (i * 50.0f));
	}
}

void Exit_LeaderBoard(void)
{

}