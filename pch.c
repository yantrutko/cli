#include "pch.h"
#include "service/buffer.h"
#include "service/time_step.h"
#include <stdio.h>

void pch (void)
{
	enum pch_constants
	{ EXIT, PLAY, SETTINGS, MENU };
	int pch_menu = MENU;
	int width = 10;
	int push_speed = 2;
	int index = 0;
	int position = 1;
	int direction = 1;
	long time_limit = 5;
	long time_one = 0;
	long time_two = 0;
	double time_ms_one = 0.0;
	double time_ms_two = 0.0;
	double waiting_time = 0.0;
	while (pch_menu)
	{
		if (pch_menu == SETTINGS)
		{
			do
			{
				printf ("\nEnter duration in seconds\n:");
				empty_reading ();
				scanf ("%li", &time_limit);
			}
			while (!time_limit);
			do
			{
				printf ("\nEnter speed of motion from 1 to 3\n:");
				empty_reading ();
				scanf ("%i", &push_speed);
			}
			while (push_speed < 1 || push_speed > 3);
			do
			{
				printf ("\nEnter width of moving\n:");
				empty_reading ();
				scanf ("%i", &width);
			}
			while (!width);
			pch_menu = PLAY;
		}
		if (pch_menu == PLAY)
		{
			position = 1;
			time_one = time_step_sec ();
			do
			{
				if (push_speed == 1)
				{
					waiting_time = 0.2;
				}
				else if (push_speed == 2)
				{
					waiting_time = 0.02;
				}
				else if (push_speed == 3)
				{
					waiting_time = 0.005;
				}
				time_ms_one = time_step_sec_ms ();
				do
				{
					time_ms_two = time_step_sec_ms ();
				}
				while (time_ms_two - time_ms_one < waiting_time);
				putc ('\n', stdout);
				index = position;
				while (index > 0)
				{
					putc (' ', stdout);
					index = index - 1;
				}
				putc ('O', stdout);
				if (direction == 1)
				{
					position = position + 1;
					if (position > width - 1)
					{
						direction = -1;
					}
				}
				else if (direction == -1)
				{
					position = position - 1;
					if (position < 2)
					{
						direction = 1;
					}
				}
				time_two = time_step_sec () - time_one;
			}
			while (time_two < time_limit);
			pch_menu = MENU;
		}
		if (pch_menu == MENU)
		{
			printf ("\nSetup for now:\nduration: %li seconds\nspeed: %i\nwidth: %i symbols size\n\n0 | Exit\n1 | Play\n2 | Settings\n\n:", time_limit, push_speed, width);
			empty_reading ();
			scanf ("%i", &pch_menu);
		}
	}
	empty_reading ();
}
