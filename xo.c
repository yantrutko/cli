#include "xo.h"
#include "library/symbol.h"
#include <stdio.h>

void xo ()
{
	int grid_column = 0;
	int grid_row = 0;
	char input_column[3] = {0};
	int input_row = 0;
	do
	{
		input_grid (&grid_column, &grid_row);
	}
	while (!grid_column || !grid_row);

	int field_size = grid_column * grid_row;
	char positions[field_size + 1];
	positions[field_size] = 0;
	while (field_size)
	{
		field_size -= 1;
		positions[field_size] = ' ';
	}

	print_grid (alphabetic_line,
							upper_line,
							chars_line,
							x_line,
							lower_line,
							grid_column,
							grid_row,
							positions);

	int go = 0;
	do
	{
		go = input_position (input_column, &input_row);
	}
	while (!go);
}

void input_grid (int* grid_column, int* grid_row)
{
	printf ("\nEnter the number of vertical lines and the number of horizontal lines\n:");
	scanf ("%i %i", grid_column, grid_row);
}

int input_position (char* input_column, int* input_row)
{
	printf ("Enter position. Example: 3k or s6.\n :");
	scanf ("%s", input_column);
	if (is_digit (input_column[0]) && is_alphabetic(input_column[1]))
	{
		*input_row = input_column[0];
		input_column[0] = input_column[1];
		input_column[1] = 0;
		return 1;
	}
	else if (is_alphabetic (input_column[0]) && is_digit (input_column[1]))
	{
		*input_row = input_column[1];
		input_column[1] = 0;
		return 1;
	}
	return 0;
}

void print_grid (void (*alphabetic_line) (int),
								void (*upper_line) (int),
								void (*chars_line) (int, int, int, char*),
								void (*x_line) (int),
								void (*lower_line) (int),
								int grid_column,
								int grid_row,
								char* positions)
{
	int row = grid_row;
	int i = 0;
	row -= 1;

	alphabetic_line (grid_column);
	upper_line (grid_column);
	chars_line (grid_column, grid_row, row, positions);
	while (row)
	{
		row -= 1;
		i += grid_column;
		x_line (grid_column);
		chars_line (grid_column, grid_row, row, positions);
	}
	lower_line (grid_column);
}

void chars_line (int grid_column,
								int grid_row,
								int for_row,
								char* positions)
{
	int row = grid_row - for_row;
	int column = grid_column - 1;
	int i = (row - 1) * grid_column;
	printf ("\n │ %c", positions[0]);
	while (column)
	{
		i += 1;
		printf (" │ %c", positions[i]);
		column -= 1;
	}
	printf (" │ %i", row);
}

void alphabetic_line (int grid_column)
{
	int column = grid_column - 1;
	printf ("\n   A");
	int abc = 'B';
	while (column)
	{
		printf ("   %c", abc);
		column -= 1;
		abc += 1;
	}
}

void upper_line (int grid_column)
{
	int column = grid_column - 1;
	printf ("\n ┌───");
	while (column)
	{
		printf ("┬───");
		column -= 1;
	}
	printf ("┐");
}

void x_line (int grid_column)
{
	int column = grid_column - 1;
	printf ("\n ├───");
	while (column)
	{
		printf ("┼───");
		column -= 1;
	}
	printf ("┤");
}

void lower_line (int grid_column)
{
	int column = grid_column - 1;
	printf ("\n └───");
	while (column)
	{
		printf ("┴───");
		column -= 1;
	}
	printf ("┘\n");
}
