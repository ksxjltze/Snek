
#include "leaderboard.h"

#define MAX_CHAR_PER_LINE 20
#define MAX_LEADERS 3

Leader LeaderBoard[MAX_LEADERS];
int x = 0;


void Read_Leaderboard_Score(void)
{
	FILE* leaderboard_scores;
	errno_t error;

	error = fopen_s(&leaderboard_scores, "leaderboard.txt", "r");

	if (leaderboard_scores == 0)
	{
		fopen_s(&leaderboard_scores, "leaderboard.txt", "w");		// write empty placement in?
		if (leaderboard_scores)
			fprintf(leaderboard_scores, "Leaderboards are empty!");	// write into the file leader boards are empty
		return;
	}


	else if (error == 0)						// 0 is successful.
	{
		char buffer[MAX_CHAR_PER_LINE];			// char array of max 30 characters.
		int leaders_count = 0;

		while (fgets(buffer, MAX_CHAR_PER_LINE, leaderboard_scores) != NULL)
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
		fclose(leaderboard_scores);
	}
}

void Write_Leaderboard_Score(void)
{
	FILE* leaderboard_scores;
	errno_t error;

	error = fopen_s(&leaderboard_scores, "leaderboard.txt", "w");

	if (leaderboard_scores == 0)
	{
		return;
	}

	else if (error != 0)
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
	//scanf("%20c", Player.name);
	//Player.name = "Player";

}

void LeaderBoard_ReadInput()
{
	if (x >= 20)
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

void Exit_LeaderBoard(void)
{

}