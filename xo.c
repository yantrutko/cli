#include "xo.h"
#include "service/buffer.h"
#include "service/line.h"
#include "service/symbol.h"
#include <stdio.h>

void xo (char* input)
{
	enum xo_enum
	{
		EXIT, PLAY, SIZE = 999
	};
	char alphabet[11] = { '0', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i' };
	int grid_column = 0;
	int grid_row = 0;
	int column = 0;
	int row = 0;
	int field_size = 0;
	char field[82] = { 0 };
	int position_index = 0;
	char input_column[5] = { 0 };
	int index = 0;
	char turn = 'X';
	int go = 0;
	int menu_xo = SIZE;
	while (menu_xo)
	{
		if (menu_xo == PLAY)
		{
			go = 0;
			while (!go && menu_xo == PLAY)
			{
				printf ("\nEnter two number from 1 to 9 to set the grid.\nExample with maximum [9 9]\nOr enter 0 0 (zero zero) for exit\n:");
				empty_reading ();
				clear_line (input, SIZE);
				clear_line (input_column, 4);
				scanf ("%s%s", input, input_column);
				if (input[0] == '0'
						&&
						!input[1]
						&&
						input_column[0] == '0'
						&&
						!input_column[1])
				{
					menu_xo = SIZE;
				}
				else
				{
					go = line_to_int (&grid_row, input);
					if (go)
					{
						go = line_to_int (&grid_column, input_column);
						if ((grid_row < 1 || grid_row > 9)
								||
								(grid_column < 1 || grid_column > 9))
						{
							go = 0;
						}
					}
				}
			}
			if (menu_xo == PLAY)
			{
				field_size = grid_column * grid_row;
				index = 0;
				while (index < field_size)
				{
					field[index] = ' ';
					index ++;
				}
				printf ("\nX turn X:\n");
			}
			while (menu_xo == PLAY)
			{
				column = 1;
				index = 'A';
				putc ('\n', stdout);
				while (column <= grid_column)
				{
					printf ("   %c", index);
					column ++;
					index ++;
				}
				column = 2;
				printf ("\n ┌───");
				while (column <= grid_column)
				{
					printf ("┬───");
					column ++;
				}
				printf ("┐");
				row = 0;
				while (row <= grid_row - 1)
				{
					index = row * grid_column;
					column = 1;
					putc ('\n', stdout);
					while (column <= grid_column)
					{
						printf (" │ %c", field[index]);
						index ++;
						column ++;
					}
					printf (" │ %i", row + 1);
					if (row <= grid_row - 2)
					{
						column = 2;
						printf ("\n ├───");
						while (column <= grid_column)
						{
							printf ("┼───");
							column ++;
						}
						printf ("┤");
					}
					row ++;
				}
				column = 2;
				printf ("\n └───");
				while (column <= grid_column)
				{
					printf ("┴───");
					column ++;
				}
				printf ("┘\n");
				go = 0;
				while (!go)
				{
					go = 0;
					printf ("Enter position, example: 3k or s6.\nOr 0 (zero) for exit\n:");
					empty_reading ();
					clear_line (input, SIZE);
					scanf ("%s", input);
					if (input[0] == '0' && !input[1])
					{
						printf ("Confirm exit with 0 or enter position\n:");
						empty_reading ();
						clear_line (input, SIZE);
						scanf ("%s", input);
						if (input[0] == '0' && !input[1])
						{
							go = 1;
							menu_xo = SIZE;
						}
					}
					if (menu_xo == PLAY
							&&
							is_digit (input[0])
							&&
							is_alphabetic (input[1]))
					{
						row = input[0] - '0';
						index = 0;
						column = 0;
						while (alphabet[index])
						{
							if (input[1] == alphabet[index])
							{
								column = index;
							}
							index ++;
						}
						if ((row > 0 && row <= grid_row)
								&&
								column > 0)
						{
							go = 1;
						}
					}
					else if (menu_xo == PLAY
									&&
									is_alphabetic (input[0])
									&&
									is_digit (input[1]))
					{
						row = input[1] - '0';
            index = 0;
            column = 0;
            while (alphabet[index])
            {
              if (input[0] == alphabet[index])
              {
                column = index;
              }
              index ++;
            }
            if ((row > 0 && row <= grid_row)
                &&
                column > 0)
            {
              go = 1;
            }
					}
					if (go && menu_xo == PLAY)
					{
						position_index = ((row - 1) * grid_column) + column - 1;
						if (field[position_index] != ' ')
						{
							go = 0;
						}
					}
				}
				if (menu_xo == PLAY)
				{
					if (turn == 'X')
					{
						field[position_index] = 'X';
						turn = 'O';
						printf ("\nO turn O:\n");
					}
					else if (turn == 'O')
					{
						field[position_index] = 'O';
						turn = 'X';
						printf ("\nX turn X:\n");
					}
				}
			}
		}
		else if (menu_xo > PLAY)
		{
			do
			{
				empty_reading ();
				clear_line (input, SIZE);
				printf ("\n0 | Exit\n1 | Play\n\n:");
				scanf ("%s", input);
				go = line_to_int (&menu_xo, input);
			}
			while (!go || menu_xo > PLAY);
		}
	}
	empty_reading ();
}
