//---------------------------------------------------------
// file:	files.c
// author:	Lee Jia Keat
// email:	l.jiakeat@digipen.edu
//
// brief:	Basic File management for reading and writing scores.
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "files.h"

void Write_Score(int player_score) // function to write score into file
{
	FILE* fptr;
	errno_t error;

	error = fopen_s(&fptr, "highscore.txt", "w");

	if (error != 0)
	{
		_fcloseall();
		return;
	}

	if (fptr == NULL)
	{
		_fcloseall();
		return;
	}

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
		_fcloseall();
		return score;
	}

	if (fptr == NULL)
	{
		_fcloseall();
		return score;
	}

	fscanf_s(fptr, "%d", &score);
	fclose(fptr);

	return score;
}