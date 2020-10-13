#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    int n = strlen(argv[1]);
    if (argc == 2 && n == 26)
    {
        for (int i = 0; i < n; i++)
        {
            if (!(isalpha(argv[1][i])))
            {
                printf("Please enter a valid substitution key in the command-line. Your key must contain each and every letter of the alphabet only once in no particular order, but nothing more.\n");
                return 1;
            }
            else
            {
                for (int j = 0; j < n; j++)
                {
                    if (i != j && argv[1][i] == argv[1][j])
                    {
                            printf("Please enter a valid substitution key in the command-line. Your key must contain each and every letter of the alphabet only once in no particular order, but nothing more.\n");
                            return 1;
                    }
                }
            }
        }
    }
    else
    {
        printf("Please enter a valid substitution key in the command-line. Your key must contain each and every letter of the alphabet only once in no particular order, but nothing more.\n");
        return 1;
    }
    string ptext = get_string("plaintext: ");
    printf("ciphertext: ");
    for (int k = 0, o = strlen(ptext); k < o; k++)
    {
        if (islower(ptext[k]))
        {
            printf("%c", tolower(argv[1][ptext[k] - 'a']));
        }
        else if (isupper(ptext[k]))
        {
            printf("%c", toupper(argv[1][ptext[k] - 'A']));
        }
        else
        {
            printf("%c", ptext[k]);
        }
    }
    printf("\n");
    return 0;
}