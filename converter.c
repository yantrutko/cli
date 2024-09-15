#include "converter.h"
#include "library/line.h"
#include "library/buffer.h"
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
    double duty_for_booty = 0.0;
    double booty = 0.0;
    int go = 0;
    int c = 0;
    int conv = CONV;
    while (conv)
    {
        do
        {
            FILE* file = fopen ("./lines/2.list.txt", "r");
            do
            {
                c = fgetc (file);
                if (c != EOF)
                {
                    printf ("%c", c);
                }
            }
            while (c != EOF);
            fclose (file);
            printf (":");
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
                conv = EXIT;
            }
        }
        while (!go);
        if (conv)
        {
            do
            {
                FILE* file;
                if (list_choice == 1)
                {
                    file = fopen ("./lines/3.temperature.txt", "r");
                }
                if (list_choice == 2)
                {
                    file = fopen ("./lines/4.length.txt", "r");
                }
                if (list_choice == 3)
                {
                    file = fopen ("./lines/5.time.txt", "r");
                }
                do
                {
                    c = fgetc (file);
                    if (c != EOF)
                    {
                        printf ("%c", c);
                    }
                }
                while (c != EOF);
                fclose (file);
                printf (":");
                clear_line (input, SIZE);
                empty_reading ();
                scanf ("%s", input);
                go = line_to_int (&choice, input);
                if (go)
                {
                    choice += list_choice * 100;
                    go = fitting_rooms (choice);
                }
                else if (go && choice == EXIT)
                {
                    conv = EXIT;
                }
            }
            while (!go);
        }
        if (conv)
        {
            do
            {
                FILE* file = fopen ("./lines/6.digits.txt", "r");
                do
                {
                    c = fgetc (file);
                    if (c != EOF)
                    {
                        printf ("%c", c);
                    }
                }
                while (c != EOF);
                fclose (file);
                printf (":");
                clear_line (input, SIZE);
                empty_reading ();
                scanf ("%s", input);
                go = line_to_double (1, &duty_for_booty, input);
            }
            while (!go);
            go = 0;
            clear_line (input, SIZE);
            booty = x_rooms (&choice, duty_for_booty);
            FILE* rooms = fopen ("./lines/7.rooms.txt", "r");
            do
            {
                fgets (input, SIZE - 1, rooms);
                if (input[0] - '0' == choice)
                {
                    input[0] = '\n';
                    printf (input, duty_for_booty, booty);
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

double x_rooms (int* choice, double duty_for_booty)
{
    double booty = duty_for_booty;
    switch (*choice)
    {
       	case 101:
        {
            *choice = 0;
            booty = (booty * 9 / 5) + 32;
            break;
        }
       	case 102:
        {
            *choice = 1;
            booty = (booty - 32) * 5 / 9;
            break;
        }
       	case 201:
        {
            *choice = 2;
            booty /= 2.54;
            break;
        }
        case 202:
        {
            *choice = 3;
            booty *= 2.54;
            break;
        }
        case 301:
        {
            *choice = 4;
            booty *= 60;
            break;
        }
        case 302:
        {
            *choice = 5;
            booty *= 60;
            break;
        }
        case 303:
        {
            *choice = 6;
            booty *= 60 * 60;
            break;
        }
    }
    return booty;
}
