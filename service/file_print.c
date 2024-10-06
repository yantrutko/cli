#include "file_print.h"
#include <stdio.h>

void file_print (const char* path)
{
	int char_pointer = 0;
	FILE* file = fopen (path, "r");
	while ((char_pointer = fgetc (file)) != EOF)
	{
		putc (char_pointer, stdout);
	}
	fclose (file);
}
