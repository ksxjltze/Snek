#include "file_manager.h"

void Write_Score(int player_score) // function to write score into file
{
	FILE* fptr;
	errno_t error;

	error = fopen_s(&fptr, "highscore.txt", "w");

	if (error != 0)
		return;

	if (fptr == NULL)
		return;

	fprintf(fptr, "%d", player_score);

	fclose(fptr);

}

int Read_Score(void) // function to read score from file
{
	int score = 0;
	FILE* fptr;
	errno_t error;

	error = fopen_s(&fptr, "highscore.txt", "r");

	if (error != 0)
	{
		Write_Score(0);
		return 0;
	}

	if (fptr == NULL)
		return 0;

	fscanf_s(fptr, "%d", &score);
	fclose(fptr);

	return score;
}