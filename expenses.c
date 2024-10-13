#include "expenses.h"
#include "service/buffer.h"
#include "service/line.h"
#include "service/symbol.h"
#include <stdio.h>
#include <stdlib.h>

void expenses (char* input)
{
	enum controls
	{
		EXIT, PRINT, APPEND, PERCENT, REMOVE, SIZE = 999
	};
	char remove_input[SIZE + 1] = { 0 };
	double expenses_sum = 0.0;
	double expenses = 0.0;
	double percent = 0;
	int go = 0;
	int index = 0;
	int exp_size = 0;
	int c_pointer = 0;
	int exp_menu = PRINT;
	while (exp_menu)
	{
		if (exp_menu == PRINT)
		{
			exp_size = 0;
			expenses_sum = 0.0;
			FILE* fprint = fopen ("./dlines/expenses.txt", "r");
			while (!feof (fprint))
			{
				clear_line (input, SIZE);
				fgets (input, 998, fprint);
				index = 0;
				while (input[index] != ' ')
				{
					index = index + 1;
				}
				index = index + 1;
				if (exp_size < index
						&&
						index < 13)
				{
					exp_size = index;
				}
				line_to_double (2, &expenses, input);
				expenses_sum = expenses_sum + expenses;
			}
			fclose (fprint);
			go = 0;
			index = 0;
			putc ('\n', stdout);
			FILE* print = fopen ("./dlines/expenses.txt", "r");
			while ((c_pointer = fgetc (print)) != EOF)
			{
				if (!go)
				{
					if (c_pointer == ' ')
					{
						go = 1;
						while (index < exp_size)
						{
							putc (' ', stdout);
							index = index + 1;
						}
						if (index > exp_size)
						{
							putc (' ', stdout);
						}
						index = 0;
					}
					else
					{
						putc (c_pointer, stdout);
						index = index + 1;
					}
				}
				else if (go)
				{
					if (c_pointer == '\n')
					{
						go = 0;
					}
					putc (c_pointer, stdout);
				}
			}
			fclose (print);
			printf ("\n=\n%g\n", expenses_sum);
			exp_menu = SIZE;
		}
		else if (exp_menu == APPEND)
		{
			int sign = 0;
			int decimal = 0;
			FILE* append = fopen ("./dlines/expenses.txt", "a");
			printf ("\nentering format example: 13.50 lunch\n:");
			clear_line (input, SIZE);
			empty_reading ();
			c_pointer = 0;
			decimal = 0;
			index = 0;
			sign = 0;
			go = 0;
			while ((c_pointer = getc (stdin)) == ' ');
			ungetc (c_pointer, stdin);
			while (!feof (stdin) && !go && index < 998)
			{
				c_pointer = getc (stdin);
				if (c_pointer == '+' || c_pointer == '-')
				{
					if (!sign)
					{
						input[index] = c_pointer;
						index = index + 1;
						sign = 1;
					}
					else
					{
						go = 1;
					}
				}
				else if (c_pointer == '.' || c_pointer == ',')
				{
					if (!decimal)
					{
						input[index] = c_pointer;
						index = index + 1;
						decimal = 1;
					}
					else
					{
						go = 1;
					}
				}
				else if (is_digit (c_pointer))
				{
					input[index] = c_pointer;
					index = index + 1;
				}
				else
				{
					go = 1;
				}
			}
			line_to_double (2, &expenses, input);
			fprintf (append, "%g", expenses);
			if (c_pointer != ' ')
			{
				putc (' ', append);
			}
			while (c_pointer != '\n')
			{
				putc (c_pointer, append);
				c_pointer = getc (stdin);
			}
			putc (c_pointer, append);
			fclose (append);
			exp_menu = SIZE;
		}
		else if (exp_menu == PERCENT)
		{
			expenses = 0.0;
			percent = 0;
			printf ("\nTo get 10 percent use format: [digits] [10%%]\n:");
			empty_reading ();
			scanf ("%lf %lf", &expenses, &percent);
			expenses = expenses * percent / 100;
			printf ("\n%g\n", expenses);
			exp_menu = SIZE;
		}
		else if (exp_menu == REMOVE)
		{
			int coincedens = 0;
			int is_remove = 0;
			int new_line = 0;
			int r_index = 0;
			int e_index = 0;
			fpos_t position;
			fpos_t next_position;
			fpos_t start_position;
			exp_size = 0;
			FILE* for_remove = fopen ("./dlines/expenses.txt", "r+");
			fgetpos (for_remove, &start_position);
			printf ("\nEnter some text from the selected line\n\n:");
			clear_line (input, SIZE);
			empty_reading ();
			scanf ("%s", input);
			while (!coincedens && !(feof (for_remove)))
			{
				clear_line (remove_input, SIZE);
				fgetpos (for_remove, &position);
				fgets (remove_input, SIZE - 1, for_remove);
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
						printf ("\n1 | Next one\n2 | Delete\n\n:");
						empty_reading ();
						scanf ("%i", &is_remove);
					}
					if (is_remove == 2)
					{
						fsetpos (for_remove, &start_position);
						FILE* new_file = fopen ("./dlines/new_expenses.txt", "w");
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
				remove ("./dlines/expenses.txt");
				rename ("./dlines/new_expenses.txt", "./dlines/expenses.txt");
			}
			exp_menu = SIZE;
		}
		else
		{
			do
			{
				printf ("\n0 | Exit\n1 | Print expenses\n2 | Throw in\n3 | Percentage\n4 | Remove one\n\n:");
				clear_line (input, SIZE);
				empty_reading ();
				scanf ("%s", input);
				go = line_to_int (&exp_menu, input);
			}
			while (!go || exp_menu > REMOVE);
		}
	}
	clear_line (input, SIZE);
	empty_reading ();
}
