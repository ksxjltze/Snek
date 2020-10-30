void kill_me(void)
{

}


//#include "leaderboard.h"
//
//#define MAX_CHAR_PER_LINE 30
//#define MAX_LEADERS 3
//
//Leader Leaders[MAX_LEADERS];
//
//
//void Read_Leaderboard_Score(void)
//{
//	FILE* leaderboard_scores;
//	errno_t error;
//
//	error = fopen_s(&leaderboard_scores, "leaderboard.txt", "r");
//
//	if (leaderboard_scores == 0)
//	{
//		fopen_s(&leaderboard_scores, "leaderboard.txt", "w");// write empty placement in?
//		fprintf(&leaderboard_scores, "Leaderboards are empty!");// write into the file leader boards are empty
//		return;
//	}
//
//
//	else if (error == 0)						// 0 is successful.
//	{
//		char read_buffer[MAX_CHAR_PER_LINE];	// char array of max 30 characters.
//		int leaders_count = 0;
//
//		while (fgets(read_buffer, MAX_CHAR_PER_LINE, leaderboard_scores) != NULL)
//		{
//			if (leaders_count < MAX_LEADERS)
//			{
//				break;							// I only want 3 leaders
//			}
//
//			int a = sscanf(read_buffer, "%s %d", Leaders[leaders_count].name, Leaders[leaders_count].score);
//
//			if (a == 2)
//			{
//				sscanf(read_buffer, "%s %d", Leaders[leaders_count].name, Leaders[leaders_count].score);
//				leaders_count++;				//increment leaders by 1
//			}
//			else
//			{
//				// TODO complain about incorect format. But while reading from .txt file, should be no problems.
//			}
//		}
//		fclose(leaderboard_scores);
//	}
//}
//
//void Write_Leaderboard_Score(void)
//{
//	FILE* leaderboard_scores;
//	errno_t error;
//
//	error = fopen_s(&leaderboard_scores, "leaderboard.txt", "w");
//
//	if (leaderboard_scores == 0)
//	{
//		return;
//	}
//
//	else if (error != 0)
//	{
//		for (int i = 0; i < MAX_LEADERS; i++)
//		{
//			if (Leaders[i].score < Player.score) // check if total score is higher than any registered leader score
//			{
//				// Leaders[i].name = write in name from somewhere
//				Leaders[i].score = Player.score; // if higher, write score total as leader score
//			}
//		}
//		fclose(leaderboard_scores);
//	}
//}