#include "converter.h"
#include "service/buffer.h"
#include "service/file_print.h"
#include "service/line.h"
#include <stdio.h>

void converter (char* input)
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
			printf ("\n0 | Exit\n1 | Temperature\n2 | Length\n3 | Time\n\n:");
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
		if (menu_conv == CONV)
		{
			do
			{
				if (list_choice == 1)
				{
					printf ("\n0 | Exit\n1 | C° -> F°\n2 | F° -> C°\n\n:");
				}
				else if (list_choice == 2)
				{
					printf ("\n0 | Exit\n1 | Centimeters to inches\n2 | Inches to centimeters\n\n:");
				}
				else if (list_choice == 3)
				{
					printf ("\n0 | Exit\n1 | Hours to minutes\n2 | Minutes to seconds\n3 | Hours to seconds\n\n:");
				}
				clear_line (input, SIZE);
				empty_reading ();
				scanf ("%s", input);
				go = line_to_int (&choice, input);
				if (go && choice != EXIT)
				{
					choice = choice + list_choice * 100;
				}
				else if (go && choice == EXIT)
				{
					menu_conv = SIZE;
				}
			}
			while (!go);
		}
		if (menu_conv == CONV)
		{
			do
			{
				printf ("\nEnter digits to convert\n\n:");
				clear_line (input, SIZE);
				empty_reading ();
				scanf ("%s", input);
				go = line_to_double (1, &digits_entered, input);
			}
			while (!go);
			if (choice == 101)
			{
				choice = 0;
				digits_output = (digits_entered * 9 / 5) + 32;
			}
			else if (choice == 102)
			{
				choice = 1;
				digits_output = (digits_entered - 32) * 5 / 9;
			}
			else if (choice == 201)
			{
				choice = 2;
				digits_output = digits_entered / 2.54;
			}
			else if (choice == 202)
			{
				choice = 3;
				digits_output = digits_entered * 2.54;
			}
			else if (choice == 301)
			{
				choice = 4;
				digits_output = digits_entered * 60;
			}
			else if (choice == 302)
			{
				choice = 5;
				digits_output = digits_entered * 60;
			}
			else if (choice == 303)
			{
				choice = 6;
				digits_output = digits_entered * 60 * 60;
			}
			FILE* rooms = fopen ("./demo-lines/converter.txt", "r");
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
			}
			while (!go && !(feof (rooms)));
			fclose (rooms);
			go = 0;
			choice = 0;
			list_choice = 0;
			digits_entered = 0.0;
			digits_output = 0.0;
		}
	}
	clear_line (input, SIZE);
	empty_reading ();
}
