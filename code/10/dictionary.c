// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Size value
int sizez = 0;

// Number of buckets in hash table
const unsigned int N = LENGTH + 1;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int X = (hash (word));
    if (table[X] == NULL)
    {
        return false;
    }
    node *cursor1 = table[X];
    int result = 0;

    do
    {
        result = strcasecmp(word, cursor1->word);
        if (result == 0)
        {
            cursor1 = NULL;
            return true;
        }
        cursor1 = cursor1->next;
    }
    while (cursor1 !=NULL);

    cursor1 = NULL;
    return false;
}

// Hashes word to a number based on the stringlength
unsigned int hash(const char *word)
{
    int size_t = strlen (word);

//JUST IN CASE the word is somehow longer than N
    if (size_t >= N)
    {
        size_t = size_t % N;
    }

// do -1 in order to use the [0] array of the hash table, if the number is only 1 letter, because one letter + "\0" equals already 2, and I want 0.
    int hash = size_t -2;
    return hash;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (!file)
    {
        return false;
    }

    char word[LENGTH + 1];

    while (fscanf(file, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            unload();
            return false;
        }
        strcpy (n->word, word);
//get hash value
        int X = hash(n->word);

//insert the node into the table
        if (table[X] == NULL)
        {
            table[X] = n;
            n->next = NULL;
        }
        else
        {
            n->next = table[X]->next;
            table[X]->next = n;
        }

//Move file pointer forward
        int position = strlen(word)+1;
        fseek(file, position, SEEK_CUR);
        position = 0;
        sizez = sizez + 1;
    }
    fclose(file);
return true;
}
// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return sizez;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int X = 0; X <= N; X++)
    {
        node *cursor = table[X];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
