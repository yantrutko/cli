#include "guess.h"
#include "service/buffer.h"
#include "service/line.h"
#include "service/randigit.h"
#include <stdio.h>
#include <time.h>

void guess (void)
{
	char word[21] = { 0 };
	char guess_word[21]= { 0 };
	char input = '\0';
	int char_pointer = 0;
	int index = 0;
	int count = 0;
	long random = 0;
	fpos_t file_start;
	fpos_t position;
	char go = 'n';
	char game = 'y';
	FILE* words = fopen ("./lines/words.txt", "r");
	fgetpos (words, &file_start);
	printf ("\nWord guessing game.\nEnter letter one by one.\nFor exit enter 0 (zero).\n");
	while (game == 'y')
	{
		random = randigit (20);
		while (random > -1)
		{
			clear_line (word, 20);
			index = 0;
			go = 'n';
			while (go == 'n')
			{
				char_pointer = fgetc (words);
				if (char_pointer == ' ')
				{
					go = 'y';
					count = count + 1;
				}
				if (go == 'n' && index <= 19)
				{
					word[index] = char_pointer;
					index = index + 1;
				}
				while (go == 'y' && char_pointer != '\n')
				{
					char_pointer = fgetc (words);
				}
			}
			fgetpos (words, &position);
			char_pointer = fgetc (words);
			if (feof (words))
			{
				fsetpos (words, &file_start);
			}
			else
			{
				fsetpos (words, &position);
			}
			random = random - 1;
		}
		count = index;
		clear_line (guess_word, 20);
		index = 0;
		while (count)
		{
			guess_word[index] = '*';
			index = index + 1;
			count = count - 1;
		}
		while (go != 'w' && game == 'y')
		{
			printf ("\n%s\n:", guess_word);
			empty_reading ();
			scanf ("%c", &input);
			if (input == '0')
			{
				game = 'n';
			}
			if (game == 'y')
			{
				index = 0;
				while (word[index])
				{
					if (word[index] == input)
					{
						guess_word[index] = input;
					}
					index = index + 1;
				}
				index = 0;
				count = 0;
				while (guess_word[index])
				{
					if (guess_word[index] == '*')
					{
						count = 1;
					}
					index = index + 1;
				}
				if (!count)
				{
					go = 'w';
				}
			}
		}
	}
	putc ('\n', stdout);
	fclose (words);
	empty_reading ();
}
