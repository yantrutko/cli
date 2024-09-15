#include "words.h"
#include "library/randigit.h"
#include "library/time_step.h"
#include "library/line.h"
#include "library/buffer.h"
#include <stdio.h>

void words (char* input)
{
    enum constants
    {
        EXIT, PLAY, SCORE, SIZE = 999
    };
    char word[SIZE] = {0};
    double word_score = 0.0;
    double time_one, time_two;
    long step_word = 0;
    int go = 0;
    int play = SIZE;
    int char_pointer = 0;
    fpos_t position;
    FILE* file = fopen ("./lines/words.txt", "r+");
    while (play)
    {
        if (play == PLAY)
        {
            step_word = randigit (10);
            while (step_word)
            {
                char_pointer = fgetc (file);
                if (char_pointer == '\n')
                {
                    step_word -= 1;
                    fgetpos (file, &position);
                    char_pointer = fgetc (file);
                    if (char_pointer == EOF)
                    {
                        rewind (file);
                        fgetpos (file, &position);
                    }
                    else
                    {
                        fsetpos (file, &position);
                    }
                }
            }
            clear_line (word, SIZE);
            fscanf (file, "%s%lf", word, &word_score);
            printf ("\n %s\n:", word);
            clear_line (input, SIZE);
            empty_reading ();
            time_one = time_step_sec_ms ();
            scanf ("%s", input);
            time_two = time_step_sec_ms ();
            time_two -= time_one;
            line_to_int (&play, input);
            if (!play)
            {
                play = SIZE;
            }
            if (play == PLAY)
            {
                go = is_lines_equal (input, word, SIZE);
                if (go)
                {
                    if (time_two < word_score)
                    {
                        fsetpos (file, &position);
                        do
                        {
                            char_pointer = fgetc (file);
                        }
                        while (char_pointer != ' ');
                        fprintf (file, "%lf", time_two);
                        printf (" %lf sec.\n", time_two);
                        if ((char_pointer = fgetc (file)) == '\n')
                        {
                            fgetpos (file, &position);
                            if ((char_pointer = fgetc (file)) == EOF)
                            {
                                rewind (file);
                                fgetpos (file, &position);
                            }
                            else
                            {
                                fsetpos (file, &position);
                            }
                        }
                    }
                }
                else
                {
                    printf ("| dirty\n");
                }
            }
        }
        else if (play == SCORE)
        {
            rewind (file);
            printf ("\n");
            while ((char_pointer = fgetc (file)) != EOF)
            {
                putc (char_pointer, stdout);
            }
            rewind (file);
            play = SIZE;
        }
        else if (play > SCORE)
        {
            do
            {
                printf ("\n0 | Exit\n1 | Start\n2 | Score\n\n:");
                clear_line (input, SIZE);
                empty_reading ();
                scanf ("%s", input);
                go = line_to_int (&play, input);
            }
            while (!go || play > SCORE);
        }
    }
    fclose (file);
    clear_line (input, SIZE);
    empty_reading ();
}
