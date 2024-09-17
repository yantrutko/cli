#include "converter.h"
#include "library/line.h"
#include "library/buffer.h"
#include "library/file_print.h"
#include <stdio.h>

void converter (char* input,
								int fitting_rooms (int),
								double x_rooms (int*, double))
{
	enum conv_enum
	{
		EXIT, CONV, SIZE = 999
	};
	int list_choice = 0;
	int choice = 0;
	double digits_entered = 0.0;
	double digits_output = 0.0;
	int go = 0;
	int menu_conv = CONV;
	while (menu_conv)
	{
		do
		{
			putc ('\n', stdout);
			file_print ("./lines/2.list.txt");
			printf ("\n:");
			clear_line (input, SIZE);
			empty_reading ();
			scanf ("%s", input);
			go = line_to_int (&list_choice, input);
			if (list_choice < 0 || list_choice > 3)
			{
				go = 0;
			}
			else if (go && list_choice == EXIT)
			{
				menu_conv = EXIT;
			}
		}
		while (!go);
		if (menu_conv)
		{
			do
			{
				putc ('\n', stdout);
				if (list_choice == 1)
				{
					file_print ("./lines/3.temperature.txt");
				}
				else if (list_choice == 2)
				{
					file_print ("./lines/4.length.txt");
				}
				else if (list_choice == 3)
				{
					file_print ("./lines/5.time.txt");
				}
				printf ("\n:");
				clear_line (input, SIZE);
				empty_reading ();
				scanf ("%s", input);
				go = line_to_int (&choice, input);
				if (go && choice != EXIT)
				{
					choice = choice + list_choice * 100;
					go = fitting_rooms (choice);
				}
				else if (go && choice == EXIT)
				{
					menu_conv = EXIT;
				}
			}
			while (!go);
		}
		if (menu_conv)
		{
			do
			{
				putc ('\n', stdout);
				file_print ("./lines/6.digits.txt");
				printf ("\n:");
				clear_line (input, SIZE);
				empty_reading ();
				scanf ("%s", input);
				go = line_to_double (1, &digits_entered, input);
			}
			while (!go);
			digits_output = x_rooms (&choice, digits_entered);
			FILE* rooms = fopen ("./lines/7.rooms.txt", "r");
			go = 0;
			do
			{
				clear_line (input, SIZE);
				fgets (input, SIZE - 1, rooms);
				if (input[0] - '0' == choice)
				{
					input[0] = '\n';
					printf (input, digits_entered, digits_output);
					go = 1;
				}
				else if (feof (rooms))
				{
					go = 1;
					printf ("\nno-room error\n");
				}
			}
			while (!go);
			fclose (rooms);
		}
	}
	clear_line (input, SIZE);
	empty_reading ();
}

int fitting_rooms (int room)
{
	if (room == 101 ||
			room == 102 ||
			room == 201 ||
			room == 202 ||
			room == 301 ||
			room == 302 ||
			room == 303)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

double x_rooms (int* choice, double digits_entered)
{
	double digits_output = digits_entered;
	switch (*choice)
	{
		case 101:
		{
			*choice = 0;
			digits_output = (digits_output * 9 / 5) + 32;
			break;
		}
		case 102:
		{
			*choice = 1;
			digits_output = (digits_output - 32) * 5 / 9;
			break;
		}
		case 201:
		{
			*choice = 2;
			digits_output = digits_output / 2.54;
			break;
		}
		case 202:
		{
			*choice = 3;
			digits_output = digits_output * 2.54;
			break;
		}
		case 301:
		{
			*choice = 4;
			digits_output = digits_output * 60;
			break;
		}
		case 302:
		{
			*choice = 5;
			digits_output = digits_output * 60;
			break;
		}
		case 303:
		{
			*choice = 6;
			digits_output = digits_output * 60 * 60;
			break;
		}
	}
	return digits_output;
}