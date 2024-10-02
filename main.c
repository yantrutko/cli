#include "service/file_print.h"
#include "service/line.h"
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
	int go = 0;
	int menu = SIZE;
	while (menu)
	{
		clear_line (input, SIZE);
		if (menu == CONV)
		{
			converter (input);
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
			pch ();
			menu = SIZE;
		}
		else if (menu == XO)
		{
			xo ();
			menu = SIZE;
		}
		else
		{
			do
			{
				file_print ("./lines/1.title.txt");
				printf ("\n\n:");
				clear_line (input, SIZE);
				scanf ("%s", input);
				go = line_to_int (&menu, input);
			}
			while (!go || menu > XO);
		}
	}
	return 0;
}
