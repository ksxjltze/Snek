#include "leaderboard.h"

#define MAX_LINE_INPUT 100
#define BUFFER_SIZE 20
#define MAX_LEADERS 3

bool is_leader;

Leader LeaderBoard[MAX_LEADERS] = {0};
int LeaderBoard_Scores[MAX_LEADERS];

const char leaderboard_file[] = "leaderboard.txt";
struct Button Button_Exit;


void Read_Leaderboard_Data(void)
{	
	FILE* leaderboard = leaderboard_file;
	errno_t error;
	char buffer[MAX_LINE_INPUT];

	error = fopen_s(&leaderboard, "leaderboard.txt", "r");

	//printf("\nwhore\n");//debug prints
 
	if (error != 0)						
	{

		//printf("Bitch\n");//debug prints
		fopen_s(&leaderboard, "leaderboard.txt", "w");

		if (leaderboard)
		{
			fprintf(leaderboard, "%s %d","Leaderboards are empty!", 0);	// write into the file leader boards are empty %s "Leaderboards are empty!"
			fclose(leaderboard);
		}

		return;
	}

	else if (error == 0)						// 0 is successful.
	{
		//printf("Hello World!\n");				//debug prints

		if (leaderboard)
		{
			while(fgets(buffer, MAX_LINE_INPUT, leaderboard) != NULL)
			{
				//printf("Hello World Again!\n"); //debug prints

				if (counter.leaders_count < MAX_LEADERS)
				{
					int index = counter.leaders_count;
					int a = sscanf_s(buffer, "%s %d", LeaderBoard[index].name, (unsigned)sizeof buffer, &LeaderBoard[index].score);

					for (int i = 0; i < MAX_LEADERS; i++)
					{
						LeaderBoard_Scores[i] = LeaderBoard[i].score;
					}

					if (a != 2)
					{
						// TODO complain about incorect format. But while reading from .txt file, should be no problems.
					}
					else
					{
						counter.leaders_count++;
					}

				}
				else
				{
					//printf("break on 3 leaders test\n");//debug prints
					break;
				}

			}

			fclose(leaderboard);
		}

	}
}

void Write_Leaderboard_Data(void)
{
	FILE* leaderboard = leaderboard_file;
	errno_t error;

	error = fopen_s(&leaderboard, "leaderboard.txt", "w+");

	if (leaderboard == 0) //file not found
	{
		return;
	}

	else if (error == 0)		// error = 0 successfully opened
	{
		for (int i = 0; i < MAX_LEADERS; i++)
		{
			fprintf(leaderboard, "%s %d\n", LeaderBoard[i].name, LeaderBoard[i].score);
		}
	}

	fclose(leaderboard);
}

void Check_If_Leader(void)
{
	for (int i = 0; i < MAX_LEADERS; i++)
	{
		if (Player.score > LeaderBoard[i].score)
			is_leader = true;
	}

	if (CP_Input_KeyTriggered(KEY_1))
		is_leader = true;
}

void Init_LeaderBoard(void)
{	
	is_leader = false;
	counter.leaders_count = 0;
	Leaderboard_Variables.text_color = CP_Color_Create(255, 255, 255, 255);
	Leaderboard_Variables.x = (float)(WINDOW_WIDTH / 2.0);
	Leaderboard_Variables.y = (float)(WINDOW_HEIGHT / 3.5);

	void(*ptr_exit)() = &Load_Main_Menu;

	CP_Vector pos = CP_Vector_Zero();
	pos.x = (float)(WINDOW_WIDTH * 0.5f) - (Menu_button.width / 2);
	pos.y = (float)(WINDOW_HEIGHT * 0.8f) - (Menu_button.height / 2);

	Button_Exit = Create_TextButton(pos, Menu_button.width, Menu_button.height, "Exit");
	Button_Set_Colors(&Button_Exit, Menu_button.idle, Menu_button.hover, Menu_button.clicked, Menu_button.text);
	Button_Set_Text_Size(&Button_Exit, 50);
	Button_Set_Callback(&Button_Exit, ptr_exit);

	if (Player.name)
	{
		counter.name_length = (int)strlen(Player.name);
	}
	else
		counter.name_length = 0;

	Read_Leaderboard_Data();

	int n = sizeof(LeaderBoard_Scores) / sizeof(LeaderBoard_Scores[0]);
	for (int i = 0; i < MAX_LEADERS; i++)
	{
		printf("\nOriginal LeaderBoard_Data is Name: %s Score: %d\n", LeaderBoard[i].name, LeaderBoard_Scores[i]); //debug prints
	}

	//printf("n is %d\n", n);
	
	Sort_Data(LeaderBoard_Scores, n);
	for (int i = 0; i < MAX_LEADERS; i++)
	{
		printf("\nSorted LeaderBoard_Data is Name: %s Score: %d\n", LeaderBoard[i].name, LeaderBoard_Scores[i]);//debug prints
	}
}

void Update_LeaderBoard(void)
{
	CP_Settings_Background(CP_Color_Create(0, 0, 0, 255));
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_TextSize(50.0f);

	float mousex = CP_Input_GetMouseX();
	float mousey = CP_Input_GetMouseY();

	CP_Font_DrawTextBox("CONGRATULATIONS, YOU WON A SPOT ON THE LEADERBOARD! Please Enter Your Name! (Up to 20 characters)", 
		(float)(WINDOW_WIDTH / WINDOW_WIDTH), (float)WINDOW_HEIGHT / 16, (float)WINDOW_WIDTH);

	LeaderBoard_ReadInput();
	LeaderBoard_Display_PlayerName();
	Draw_LeaderBoard(); 
	Update_Button(Button_Exit, mousex, mousey);

}

void Load_Main_Menu(void)
{
	CP_Engine_SetNextGameState(Menu_init, Menu_update, Menu_exit);
}

void LeaderBoard_Display_PlayerName()
{
	if (Player.name)
		CP_Font_DrawText(Player.name, Leaderboard_Variables.x, Leaderboard_Variables.y);
}

void LeaderBoard_ReadInput() // function to read input from file?
{
	if (CP_Input_KeyTriggered(KEY_ENTER))
	{
		Write_Leaderboard_Data();
		return;
	}

	if (CP_Input_KeyTriggered(KEY_BACKSPACE))
	{
		if (counter.name_length > 0)
		{
			counter.name_length--;
			Player.name[counter.name_length] = '\0';
		}
	}

	for (int i = KEY_A, j = KEY_0; i <= KEY_Z; i++, j++)
	{
		if (counter.name_length >= BUFFER_SIZE)
			return;

		if (CP_Input_KeyTriggered(i))
		{
			Player.name[counter.name_length] = (char)i;
			counter.name_length++;
		}
		else if (CP_Input_KeyTriggered(j))
		{
			if (j > KEY_9)
				return;

			Player.name[counter.name_length] = (char)j;
			counter.name_length++;
		}

	}

}

void Draw_LeaderBoard(void)
{
	CP_Settings_TextSize(50.0f);
	CP_Settings_Fill(Leaderboard_Variables.text_color);

	for (int i = 0; i < counter.leaders_count; i++)
	{	

		char leaderscore_buffer[16];
		sprintf_s(leaderscore_buffer, 16, "%d", LeaderBoard[i].score);//debug prints

		CP_Font_DrawText(leaderscore_buffer, Leaderboard_Variables.x + 300.0f, Leaderboard_Variables.y + 100.0f + (i * 100));
		CP_Font_DrawText(LeaderBoard[i].name, Leaderboard_Variables.x + 100.0f, Leaderboard_Variables.y + 100.0f + (i * 100));
	}
}

void Exit_LeaderBoard(void)
{
	_fcloseall();
}

void Sort_Data(int test[], int n)
{
	int i, j, temp;
	char Temp_name[BUFFER_SIZE];
	for (i = 0; i < n; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			if (test[i] < test[j])
			{
				temp = test[i];											// If score gets sorted
				strcpy_s(Temp_name, BUFFER_SIZE, LeaderBoard[i].name);  // Sort name also
				
				test[i] = test[j];
				strcpy_s(LeaderBoard[i].name, BUFFER_SIZE, LeaderBoard[j].name); // 

				test[j] = temp;
				strcpy_s(LeaderBoard[j].name, BUFFER_SIZE, Temp_name);
			}
		}
		LeaderBoard[i].score = LeaderBoard_Scores[i];					// Write Sorted scores into struct
	}
	Write_Leaderboard_Data();											// Write sorted data into file
}

void Player_Is_Leader(void)
{
	if (is_leader)
	{
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Font_DrawTextBox("CONGRATULATIONS, YOU WON A SPOT ON THE LEADERBOARD! Please Enter Your Name! (Up to 20 characters):",
			(float)(WINDOW_WIDTH / WINDOW_WIDTH), (float)WINDOW_HEIGHT / 6.0f, (float)WINDOW_WIDTH);

		LeaderBoard_Display_PlayerName();
		LeaderBoard_ReadInput();
	}
}