#include "xo.h"
#include "library/buffer.h"
#include "library/line.h"
#include "library/symbol.h"
#include <stdio.h>

void xo ()
{
	enum xo_enum
	{
		EXIT, PLAY, MENU
	};
	int grid_column = 0;
	int grid_row = 0;
	char field[101] = { 0 };
	char input_column[5] = { 0 };
	int input_row = 0;
	int field_size = 0;
	int index = 0;
	int go = 0;
	int menu_xo = MENU;
	while (menu_xo)
	{
		if (menu_xo == PLAY)
		{
			do
			{
				printf ("\nEnter two number from 1 to 10 for grid. Example with maximum [10 10]\n:");
				empty_reading ();
/*
		clear both inputs,
		put them to line_to_int,
		if if
*/
				scanf ("%i %i", &grid_column, &grid_row);
				if (grid_column == 0 && grid_row == 0)
				{
					go = 1;
					menu_xo = EXIT;
				}
				else if (
									(
										grid_column < 1
										||
										grid_column > 10
									)
  								||
  								(
  									grid_row < 1
  									||
  									grid_row > 10
  								)
  							)
				{
					go = 0;
				}
				else
				{
					go = 1;
				}
			}
			while (!go);
			if (menu_xo == PLAY)
			{
				field_size = grid_column * grid_row;
				while (index <= field_size - 1)
				{
					field[index] = '*';
					index += 1;
				}
				int row = grid_row - 1;
				int column = grid_column;
				int index = 'A';
				putc ('\n', stdout);
				while (column)
				{
					printf ("   %c", index);
					column -= 1;
					index += 1;
				}
				printf ("\n ┌───");
				column = grid_column - 1;
				while (column)
				{
					printf ("┬───");
					column -= 1;
				}
				printf ("┐");
				int row_number = grid_row - row;
				while (row > - 1)
				{
					index = (row_number - 1) * grid_column;
					column = grid_column - 1;
					printf ("\n │ %c", field[0]);
					while (column)
					{
						index += 1;
						printf (" │ %c", field[index]);
						column -= 1;
					}
					printf (" │ %i", row_number);
					if (row)
					{
						printf ("\n ├───");
						column = grid_column - 1;
						while (column)
						{
							printf ("┼───");
							column -= 1;
						}
						printf ("┤");
					}
					row -= 1;
					row_number += 1;
				}
				printf ("\n └───");
				column = grid_column - 1;
				while (column)
				{
					printf ("┴───");
					column -= 1;
				}
				printf ("┘\n");
				do
				{
					go = input_position (input_column,
															&input_row);
				}
				while (!go);
				menu_xo = MENU;
			}
		}
		else if (menu_xo > PLAY)
		{
			go = 0;
			empty_reading ();
			clear_line (input_column, 5);
			printf ("\n0 | Exit\n1 | Play\n\n:");
			scanf ("%s", input_column);
			go = line_to_int (&menu_xo, input_column);
		}
	}
	empty_reading ();
}

int input_position (char* input_column,
										int* input_row)
{
	printf ("Enter position, example: 3k or s6.\n:");
	scanf ("%s", input_column);
	if (is_digit (input_column[0])
			&&
			is_alphabetic(input_column[1]))
	{
		*input_row = input_column[0];
		input_column[0] = input_column[1];
		input_column[1] = 0;
		return 1;
	}
	else if (is_alphabetic (input_column[0])
					&&
					is_digit (input_column[1]))
	{
		*input_row = input_column[1];
		input_column[1] = 0;
		return 1;
	}
	return 0;
}
