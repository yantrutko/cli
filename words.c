#include "words.h"
#include "service/buffer.h"
#include "service/file_print.h"
#include "service/line.h"
#include "service/randigit.h"
#include "service/time_step.h"
#include <stdio.h>

void words (char* input)
{
	enum constants
	{
		EXIT, PLAY, SCORE, SIZE = 999
	};
	char word[SIZE + 1] = { 0 };
	double word_score = 0.0;
	double time_one = 0.0;
	double time_two = 0.0;
	long step_word = 0;
	int go = 0;
	int play = SIZE;
	int char_pointer = 0;
	fpos_t position_start = 0;
	fpos_t position = 0;
	FILE* file = fopen ("./demo-lines/words.txt", "r+");
	fgetpos (file, &position_start);
	while (play)
	{
		while (play == PLAY)
		{
			step_word = randigit (20);
			while (step_word)
			{
				do
				{
					char_pointer = fgetc (file);
					if (feof (file))
					{
						fsetpos (file, &position_start);
					}
				}
				while (char_pointer != '\n');
				step_word = step_word - 1;
			}
			fgetpos (file, &position);
			char_pointer = fgetc (file);
			if (feof (file))
			{
        fsetpos (file, &position_start);
				fgetpos (file, &position);
      }
      else
      {
      	fsetpos (file, &position);
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
			if (play < EXIT || play > SCORE)
			{
				play = PLAY;
			}
			if (play == EXIT)
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
						fpos_t pos;
						fgetpos (file, &pos);
						fsetpos (file, &pos);
						fprintf (file, "%lf", time_two);
						fsetpos (file, &position);
						printf (" %lf sec.\n", time_two);
					}
				}
				else
				{
					printf ("| dirty\n");
				}
			}
		}
		if (play == SCORE)
		{
			printf ("\n");
			file_print ("./demo-lines/words.txt");
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
