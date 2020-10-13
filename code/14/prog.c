#include <stdio.h>

#include <cs50.h>

#include <string.h>

#include <ctype.h>

int main(void)

{

  int i = -1;

  int j = -1;

  int LetterX = 0;

  int WordsY = 0;

  int SentencesZ = 0;

  string Text = get_string("Introduce text: ");

  /*Checks whether it's a letter or not.*/

  do
  {
    i++;
    while ((65 <= Text[i] && Text[i] <= 90) ||
           (97 <= Text[i] && Text[i] <= 122))
    {
      LetterX++;
      i++;
    }
  } while (i < strlen(Text));

  do {
    j++;
    while (Text[j] != '!' || Text[j] != '?' ||
           Text[j] != '.') /*This is were the error is (all 3 of them)*/ 
    {
      j++;
    }
    SentencesZ++;
  } while (j < strlen(Text));

  printf("%i\n", SentencesZ);
}