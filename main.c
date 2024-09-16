#include "library/line.h"
#include "converter.h"
#include "expenses.h"
#include "words.h"
#include "guess.h"
#include "pch.h"
#include "xo.h"
#include <stdio.h>

int main ()
{
	enum menu_enum
	{
		EXIT, CONV, EXP, WORDS, GUESS, PCH, XO, SIZE = 999
	};
	char input[SIZE] = {0};
	int character_pointer = 0;
	int go = 0;
	int menu = SIZE;
	while (menu)
	{
		clear_line (input, SIZE);
		if (menu == CONV)
		{
			converter (input, &fitting_rooms, &x_rooms);
			menu = SIZE;
		}
		else if (menu == EXP)
		{
			expenses (input);
			menu = SIZE;
		}
		else if (menu == WORDS)
		{
			words (input);
			menu = SIZE;
		}
		else if (menu == GUESS)
		{
			guess ();
			menu = SIZE;
		}
		else if (menu == PCH)
		{
			pch (&put_line, &busy_waiting);
			menu = SIZE;
		}
		else if (menu == XO)
		{
			xo ();
			menu = SIZE;
		}
		else
		{
			FILE* file = fopen ("./lines/1.title.txt", "r");
			while ((character_pointer = getc (file)) != EOF)
			{
				putc (character_pointer, stdout);
			}
			fclose (file);
			do
			{
				printf ("\n0 | Exit\n1 | Unit Converter\n2 | Expenses\n3 | Words\n4 | Guess\n5 | Pch\n6 | XO (in development)\n\n:");
				clear_line (input, SIZE);
				scanf ("%s", input);
				go = line_to_int (&menu, input);
			}
			while (!go || menu > PCH);
		}
	}
	return 0;
}
