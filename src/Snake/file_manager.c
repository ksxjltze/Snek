#include "file_manager.h"

extern int hs;

void WriteFile(int player_score)
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

void ReadFile(void)
{
	FILE* fptr;
	errno_t error;
	int score;

	error = fopen_s(&fptr, "highscore.txt", "r");

	if (error != 0)
		return;

	if (fptr == NULL)
		return;

	fscanf_s(fptr, "%d", &score);
	hs = score;
	fclose(fptr);
}