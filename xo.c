#include "xo.h"
#include "library/symbol.h"
#include <stdio.h>

short grid_column = 0;
short grid_row = 0;
char input_column[3] = {0};
short input_row = 0;
short turn = 1;

void xo ()
{
    do
    {
        input_grid (&grid_column, &grid_row);
    }
    while (!grid_column || !grid_row);

    short field_size = grid_column * grid_row;
    char positions[field_size + 1];
    positions[field_size] = 0;
    while (field_size)
    {
        field_size -= 1;
        positions[field_size] = ' ';
    }

    print_grid (&alphabetic_line,
                &upper_line,
                &chars_line,
                &x_line,
                &lower_line,
                grid_column,
                grid_row,
                positions);

    short go = 0;
    do
    {
        go = input_position (input_column, &input_row);
    }
    while (!go);
}

void input_grid (short* grid_column, short* grid_row)
{
    printf ("\nEnter the number of vertical lines and the number of horizontal lines\n:");
    scanf ("%hu %hu", grid_column, grid_row);
}

short input_position (char* input_column, short* input_row)
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

void print_grid (void alphabetic_line (short),
                 void upper_line (short),
                 void chars_line (short, short, short, char*),
                 void x_line (short),
                 void lower_line (short),
                 short grid_column,
                 short grid_row,
                 char* positions)
{
    short row = grid_row;
    short i = 0;
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

void chars_line (short grid_column,
                 short grid_row,
                 short for_row,
                 char* positions)
{
    short row = grid_row - for_row;
    short column = grid_column - 1;
    short i = (row - 1) * grid_column;
    printf ("\n │ %c", positions[0]);
    while (column)
    {
        i += 1;
        printf (" │ %c", positions[i]);
        column -= 1;
    }
    printf (" │ %hu", row);
}

void alphabetic_line (short grid_column)
{
    short column = grid_column - 1;
    printf ("\n   A");
    int abc = 'B';
    while (column)
    {
        printf ("   %c", abc);
        column -= 1;
        abc += 1;
    }
    return;
}

void upper_line (short grid_column)
{
    short column = grid_column - 1;
    printf ("\n ┌───");
    while (column)
    {
        printf ("┬───");
        column -= 1;
    }
    printf ("┐");
}

void x_line (short grid_column)
{
    short column = grid_column - 1;
    printf ("\n ├───");
    while (column)
    {
        printf ("┼───");
        column -= 1;
    }
    printf ("┤");
}

void lower_line (short grid_column)
{
    short column = grid_column - 1;
    printf ("\n └───");
    while (column)
    {
        printf ("┴───");
        column -= 1;
    }
    printf ("┘\n");
}