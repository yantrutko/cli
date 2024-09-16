#include "expenses.h"
#include "library/line.h"
#include "library/buffer.h"
#include <stdio.h>
#include <stdlib.h>

void expenses (char* input)
{
	enum controls
	{
		EXIT, PRINT, ADD, PERCENT, REMOVE, SIZE = 999
	};
	char remove_input[SIZE] = {0};
	double expenses = 0.0;
	int go = 0;
	int percent = 0;
	int c_pointer = 0;
	int exp_menu = PRINT;
	while (exp_menu)
	{
		if (exp_menu == PRINT)
		{
			FILE* print = fopen ("./lines/expenses.txt", "r+");
			printf ("\n");
			while ((c_pointer = fgetc (print)) != EOF)
			{
				putc (c_pointer, stdout);
			}
			fclose (print);
			exp_menu = SIZE;
		}
		else if (exp_menu == ADD)
		{
			FILE* append = fopen ("./lines/expenses.txt", "a");
			printf ("\nformat: [digits/price] [description/name of]\n:");
			clear_line (input, SIZE);
			scanf ("%s", input);
			line_to_double (2, &expenses, input);
			fprintf (append, "%g", expenses);
			while ((c_pointer = getchar ()) != '\n')
			{
				fputc (c_pointer, append);
			}
			fputc ('\n', append);
			fclose (append);
			exp_menu = SIZE;
		}
		else if (exp_menu == PERCENT)
		{
			do
			{
				expenses = 0.0;
				percent = 0;
				printf ("\nTo get 10 percent use format: [digits] [10%%]\n:");
				scanf ("%lf %i", &expenses, &percent);
				empty_reading ();
			}
			while (expenses == 0.0 || percent == 0);
			expenses = expenses * percent / 100;
			printf ("\n%g\n", expenses);
			exp_menu = SIZE;
		}
		else if (exp_menu == REMOVE)
		{
			int coincedens = 0;
			int is_remove = 0;
			int new_line = 0;
			int exp_size = 0;
			int r_index = 0;
			int e_index = 0;
			fpos_t position;
			fpos_t next_position;
			FILE* for_remove = fopen ("./lines/expenses.txt", "r+");
			printf ("\nEnter part of text from the line to remove \n:");
			clear_line (input, SIZE);
			scanf ("%s", input);
			while (!coincedens && !(feof (for_remove)))
			{
				clear_line (remove_input, SIZE);
				fgetpos (for_remove, &position);
				fgets (remove_input, SIZE, for_remove);
				new_line += 1;
				fgetpos (for_remove, &next_position);
				exp_size = 0;
				while (input[exp_size])
				{
					exp_size += 1;
				}
				exp_size -= 1;
				r_index = 0;
				while (!coincedens &&
							remove_input[r_index])
				{
					e_index = 0;
					while (!coincedens &&
								(input[e_index] ==
								remove_input[r_index]))
					{
						if (e_index == exp_size)
						{
							coincedens = 1;
						}
						else
						{
							e_index += 1;
							r_index += 1;
						}
					}
					r_index += 1;
				}
				if (coincedens)
				{
					is_remove = 0;
					while (is_remove < 1 || is_remove > 2)
					{
						printf ("\n%s", remove_input);
						printf ("\n1 | Next one\n2 | Delete\n:");
						scanf ("%i", &is_remove);
					}
					if (is_remove == 2)
					{
						rewind (for_remove);
						FILE* new_file = fopen ("./lines/new_expenses.txt", "w");
						while (new_line > 1)
						{
							c_pointer = fgetc (for_remove);
							fputc (c_pointer, new_file);
							if (c_pointer == '\n')
							{
								new_line -= 1;
							}
						}
						fsetpos (for_remove, &next_position);
						while ((c_pointer = fgetc (for_remove)) != EOF)
						{
							fputc (c_pointer, new_file);
						}
						fclose (new_file);
					}
					else if (is_remove == 1)
					{
						coincedens = 0;
					}
				}
			}
			fclose (for_remove);
			if (is_remove == 2)
			{
				remove ("./lines/expenses.txt");
				rename ("./lines/new_expenses.txt", "./lines/expenses.txt");
			}
			exp_menu = SIZE;
		}
		else
		{
			do
			{
				printf ("\n0 | Exit\n1 | Print expenses\n2 | Throw in\n3 | Percentage\n4 | Remove one\n\n:");
				clear_line (input, SIZE);
				scanf ("%s", input);
				go = line_to_int (&exp_menu, input);
			}
			while (!go || exp_menu > REMOVE);
		}
	}
	clear_line (input, SIZE);
}
