#include "pch.h"
#include "library/time_step.h"
#include "library/buffer.h"
#include <stdio.h>

void pch (void put_line (int),
          void busy_waiting (int))
{
    int width = 50;
    int position = 0;
    int push_speed = 0.0;
    long time_limit = 0;
    long time_one = 0;
    long time_two = 0;
    /* 1.play; 2.settings */
    do
    {
        printf ("\nEnter duration in seconds\n:");
        empty_reading ();
        scanf ("%li", &time_limit);
    }
    while (!time_limit);
    do
    {
        printf ("Enter speed of motion from 1 to 3\n:");
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
    time_one = time_step_sec ();
    while (time_two < time_limit)
    {
        while (position < width && time_two < time_limit)
        {
            busy_waiting (push_speed);
            put_line (position);
            position += 1;
            time_two = time_step_sec () - time_one;
        }
        while (position > 0 && time_two < time_limit)
        {
            busy_waiting (push_speed);
            put_line (position);
            position -= 1;
            time_two = time_step_sec () - time_one;
        }
    }
    empty_reading ();
}

void busy_waiting (int push_speed)
{
    double time_ms_one = 0.0;
    double time_ms_two = 0.0;
    double waiting_time = 0.0;
    if (push_speed == 1)
    {
        waiting_time = 0.2;
    }
    else if (push_speed == 2)
    {
        waiting_time = 0.05;
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
}

void put_line (int position)
{
    putchar ('\n');
    for (int gap = position; gap > 0; gap -= 1)
    {
        putchar (' ');
    }
    putchar ('O');
}
