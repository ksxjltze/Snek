#include "filemanager.h"

void WriteFile(void)
{
	FILE* fptr;
	errno_t error;

	error = fopen_s(&fptr, "test.txt", "w");

	if (error != 0)
		return;

	if (fptr == NULL)
		return;

	//fprintf(fptr, "%s", "dadadawdawdadaa");
	fputc('\0', fptr);

	fclose(fptr);

}

void ReadFile(void)
{
	FILE* fptr;
	errno_t error;
	int hs;

	error = fopen_s(&fptr, "test.txt", "r");

	if (error != 0)
		return;

	if (fptr == NULL)
		return;

	fscanf_s(fptr, "%d", &hs);
}