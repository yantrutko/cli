#include "buffer.h"
#include <stdio.h>

void empty_reading (void)
{
	int buffer = 0;
	do
	{
		buffer = getchar ();
	}
	while (buffer != '\n');
}
