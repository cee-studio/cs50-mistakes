#include <stdbool.h>
#include "dictionary.h"
#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

unsigned int numWords = 0;
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 65536;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    unsigned int bucket = hash(word);
    node *tmp = table[bucket];
    while(tmp != NULL)
    {
        if (strcasecmp(word, tmp->word) == 0)
        {
            return true;
        }
        tmp = tmp->next;
    }

             return false;
}


// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash = 0;
   // char *lword = malloc(sizeof(*word) + 1);
   char lword[sizeof(*word)];
    for (int a = 0; a < strlen(word); a++)
    {
        lword[a] = (char) tolower(word[a]);
    }
    for (int i = 0; i < 3; i++)
    {
        if (i < strlen(word))
        {
        hash = hash + (int) lword[i];
        }
    }
 //   free(lword);
    return hash;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    node *n;
    FILE * file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    char indWord[LENGTH + 1];
    while (fscanf(file, "%s", indWord) != EOF)
    {
        n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        numWords++;
        strcpy(n->word, indWord);
        n->next = table[hash(n->word)];
        table[hash(n->word)] = n;
    }

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return numWords;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{

    node *cursor = NULL;
    node *tmp = NULL;
    for (int i = 0; i < N; i++)
    {
        cursor = table[i];
        while (tmp != NULL)
        {
        tmp = cursor->next;
        free(cursor);
        cursor = tmp;
        }
    }
    return true;

   

}