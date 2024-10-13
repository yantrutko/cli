#include "service/line.h"
#include "converter.h"
#include "expenses.h"
#include "words.h"
#include "guess.h"
#include "pch.h"
#include "xo.h"
#include <stdio.h>

int main (int argc, char* argv[])
{
	enum menu_enum
	{
		EXIT, CONV, EXP, WORDS, GUESS, PCH, XO, SIZE = 999
	};
	char input[SIZE + 1] = { 0 };
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
			xo (input);
			menu = SIZE;
		}
		else
		{
			do
			{
				printf ("\n┌──────────┐\n│   DEMO   │\n└──────────┘\n\n0 | Exit\n1 | Unit Converter\n2 | Expenses\n3 | Words\n4 | Guess\n5 | Pch\n6 | XO\n\n:");
				clear_line (input, SIZE);
				scanf ("%s", input);
				go = line_to_int (&menu, input);
			}
			while (!go || menu > XO);
		}
	}
	return 0;
}
