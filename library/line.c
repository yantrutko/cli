#include "line.h"
#include "symbol.h"

void clear_line (char* line, int size)
{
    for (int index = 0; index < size; index += 1)
    {
        line[index] = 0;
    }
}

int is_lines_equal (char* line_one, char* line_two, int size)
{
    for (int index = 0; index < size; index += 1)
    {
        if ((line_one[index] || line_two[index]) &&
            line_one[index] != line_two[index])
       	{
            return 0;
       	}
    }
    return 1;
}

int line_to_int (int* number, char* line)
{
    int temporary_number = 0;
    int is_a_digit = 0;
    int index = 0;
    while (line[index])
    {
        is_a_digit = is_digit (line[index]);
        if (is_a_digit && index != 0)
       	{
            temporary_number *= 10 + line[index] - '0';
       	}
        else if (is_a_digit && index == 0)
       	{
            temporary_number = line[index] - '0';
       	}
        else
       	{
            return 0;
       	}
        index += 1;
    }
    *number = temporary_number;
    return 1;
}

int line_to_double (int mode, double* pointer_for_digits, char* line)
{
    int plus_or_minus = 0;
    int point = 0;
    int is_a_sign = 0;
    int is_a_digit = 0;
    double digits_growing = 0.0;
    double tenth = 0.1;
    int stop = 0;
    int index = 0;
    while ((mode == 1 || mode == 2) && !stop && line[index])
    {
        is_a_digit = is_digit (line[index]);
        is_a_sign = is_sign (line[index]);
        if (is_a_digit)
        {
            if (point == 0)
            {
                if (index == 0)
                {
                    digits_growing = line[index] - '0';
                }
                else if (index == 1 && plus_or_minus != 0)
                {
                    digits_growing = line[index] - '0';
                }
                else
                {
                    digits_growing = digits_growing * 10 + (line[index] - '0');
                }
            }
            else if (point == 1)
            {
                digits_growing = digits_growing + (line[index] - '0') * tenth;
                tenth = tenth * 0.1;
            }
        }
        else if (is_a_sign)
        {
            if (line[index] == '-' || line[index] == '+')
            {
                if (index != 0)
                {
                    stop = 1;
                }
                else if (line[index] == '-')
                {
                    plus_or_minus = -1;
                }
                else if (line[index] == '+')
                {
                    plus_or_minus = 1;
                }
            }
            else if (line[index] == '.' || line[index] == ',')
            {
                if (point != 0)
                {
                    stop = 1;
                }
                else
                {
                    point = 1;
                }
            }
            else
            {
                stop = 1;
            }
        }
        else
        {
            stop = 1;
        }
        index = index + 1;
    }
    if (!stop || (stop && mode == 2))
    {
        if (plus_or_minus == -1)
        {
            *pointer_for_digits = digits_growing * plus_or_minus;
        }
        else
        {
            *pointer_for_digits = digits_growing;
        }
        return 1;
    }
    return 0;
}