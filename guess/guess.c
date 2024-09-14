#include <stdio.h>
#include <time.h>

int main ()
{
  char word[20] = {0};
  char guess[20] = {0};
  char input = '\0';
  int char_pointer = 0;
  int index = 0;
  int count = 0;
  clock_t random = 0;
  fpos_t file_start;
  fpos_t position;
  char go = 'n';
  char game = 'y';
  FILE* words;
  words = fopen ("./guess.txt", "r");
  fgetpos (words, &file_start);
  printf ("\nWord guessing game.\nEnter letter one by one.\nFor exit enter 0 (zero).\n");
  while (game == 'y')
  {
    random = clock ();
    while (random > 10)
    {
      random = random % 10;
    }
    while (random > -1)
    {
      index = 0;
      while (index <= 19)
      {
        word[index] = 0;
        index = index + 1;
      }
      index = 0;
      go = 'n';
      while (go == 'n')
      {
        char_pointer = fgetc (words);
        if (char_pointer == '\n')
        {
          go = 'y';
          count = count + 1;
        }
        if (go == 'n' && index <= 19)
        {
          word[index] = char_pointer;
          index = index + 1;
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
    index = 0;
    while (index <= 19)
    {
      guess[index] = 0;
      index = index + 1;
    }
    index = 0;
    while (count)
    {
      guess[index] = '*';
      index = index + 1;
      count = count - 1;
    }
    while (go != 'w' && game == 'y')
    {
      printf ("\n%s\n", guess);
      scanf ("%c", &input);
      do
      {
        char_pointer = getchar ();
      }
      while (char_pointer != '\n');
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
            guess[index] = input;
          }
          index = index + 1;
        }
        index = 0;
        count = 0;
        while (guess[index])
        {
          if (guess[index] == '*')
          {
            count = 1;
          }
          index = index + 1;
        }
        if (!count)
        {
          go = 'w';
        }
      } /*if (game == 'y')*/
    } /*while (go != 'w' && game == 'y')*/
  } /*while (game == 'y')*/
  putc ('\n', stdout);
  fclose (words);
  return 0;
}
