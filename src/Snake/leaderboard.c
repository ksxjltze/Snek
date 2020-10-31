
#include "leaderboard.h"

#define MAX_LINE_INPUT 100
#define MAX_LEADERS 3

Leader LeaderBoard[MAX_LEADERS] = {0};
const char leaderboard_file[] = "leaderboard.txt";
int x = 0;
int leaders_count = 0;


void Read_Leaderboard_Data(void)
{	
	FILE* leaderboard = leaderboard_file;
	errno_t error;
	char buffer[MAX_LINE_INPUT];

	error = fopen_s(&leaderboard, "leaderboard.txt", "r");

	printf("\nwhore\n");//debug prints
 
//if (leaderboard == 0 || leaderboard == NULL)	
//{	
//	fclose(leaderboard);
//	return;
//}	
	if (error != 0)						
	{

		printf("Bitch\n");//debug prints
		fopen_s(&leaderboard, "leaderboard.txt", "w");

		fprintf(leaderboard, "%s %d","nil",  69);	// write into the file leader boards are empty %s "Leaderboards are empty!"

		fclose(leaderboard);
		return;
	}

	else if (error == 0)						// 0 is successful.
	{
		printf("Hello World!\n"); //debug prints

		while(fgets(buffer, MAX_LINE_INPUT, leaderboard) != NULL)
		{
			printf("Hello World Again!\n"); //debug prints
			if (leaders_count > MAX_LEADERS)
			{
				printf("break on 3 leaders test\n");//debug prints
				
				break;							// I only want 3 leaders
			}
			//int test = 0;
			//int a = sscanf_s(buffer, "%d", &test);

			int a = sscanf_s(buffer, "%s %d", LeaderBoard[leaders_count].name, (unsigned)sizeof buffer, &LeaderBoard[leaders_count].score);

			printf("A value is %d\n", a);
			printf("buffer is %s\n", buffer);
			printf("name is %s\n", LeaderBoard[0].name);
			printf("score is %d\n", LeaderBoard[0].score);

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
	fclose(leaderboard);
}

void Write_Leaderboard_Data(void)
{
	FILE* leaderboard = leaderboard_file;
	errno_t error;

	error = fopen_s(&leaderboard, "leaderboard.txt", "w");

	if (leaderboard == 0) //file not found
	{
		return;
	}

	else if (error == 0)		// error = 0 successfully opened
	{
		for (int i = 0; i < MAX_LEADERS; i++)
		{
			Leader leader = LeaderBoard[i];
			if (Player.score > LeaderBoard[i].score) // check if total score is higher than any registered leader score
			{
				leader.score = Player.score;		 // if higher, write score total as leader score
				leader.name = Player.name;
			}
		}
		fclose(leaderboard);
	}
}

void Check_If_Leader(void)
{
	for (int i = 0; i < MAX_LEADERS; i++)
	{
		if (Player.score > LeaderBoard[i].score)											// If true, draw different screen for leaderboard?????
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

	CP_Font_DrawTextBox("CONGRATULATIONS, YOU WON A SPOT ON THE LEADERBOARD! Please Enter Your Name! (Up to 20 characters)", (float)(WINDOW_WIDTH / WINDOW_WIDTH), (float)WINDOW_HEIGHT / 16, (float)WINDOW_WIDTH);

	LeaderBoard_ReadInput();
	
	// CP_Font_DrawText(Player.name, 100, 100); // this is null now

	Draw_LeaderBoard(); 

}

void LeaderBoard_ReadInput()
{
	if (x >= MAX_LINE_INPUT)
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

	char leaderscore_buffer[16];
	sprintf_s(leaderscore_buffer, 16, "%c", LeaderBoard[0].score);//debug prints


	for (int i = 0; i < leaders_count; i++)
	{	

		CP_Font_DrawText(leaderscore_buffer, Leaderboard_Variables.x + 100.0f, Leaderboard_Variables.y);
		CP_Font_DrawText(LeaderBoard[i].name, Leaderboard_Variables.x, Leaderboard_Variables.y);
	}
}

void Exit_LeaderBoard(void)
{
	_fcloseall();
}