#include <stdio.h>

int main ()
{
  char word[20] = {0};
  char guess[20] = {0};
  char input = '\0';
  int char_pointer = 0;
  int index = 0;
  int count = 0;
  char go = 'y';
  FILE* words;
  words = fopen ("./words.txt", "r");
  do
  {
    char_pointer = fgetc (words);
    if (char_pointer == '\n')
    {
      go = 'n';
    }
    word[index] = char_pointer;
    if (go == 'y')
    {
      index = index + 1;
    }
  }
  while (go == 'y');
  count = index;
  index = 0;
  while (count)
  {
    guess[index] = '*';
    index = index + 1;
    count = count - 1;
  }
  while (go != 'w')
  {
    printf ("\n%s\n", guess);
    scanf ("%c", &input);
    do
    {
      char_pointer = getchar ();
    }
    while (char_pointer != '\n');
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
  }
  printf ("\n%s\n", guess);
  fclose (words);
  return 0;
}
