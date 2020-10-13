// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

//number of words in dictionary
int dwordcount;

// Number of buckets in hash table
const unsigned int N = 100;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    char *test;

    int bucket = hash(word);
    node *trav = table[bucket];

    while (trav != NULL)
    {
        strcpy(trav->word, test);
        if (strcasecmp(word, test) != 0)
        {
            return true;
        }
        trav = table[bucket]->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //this uses the djb2 hash algorythm. source: http://www.cse.yorku.ca/~oz/hash.html
    unsigned long hash = 5381;
    int c;

    while ((c = *word++) != '\0')
    {
        hash = ((hash << 5) + hash) + tolower(c);
    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{

    char tmpwrd[LENGTH + 1];
    //open the file
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("fail");
        return false;
    }

    while ((fscanf(dict, "%s", tmpwrd)) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        strcpy(n->word, tmpwrd);
        int k = hash(tmpwrd);
        n->next = table[k];
        table[k] = n;
        dwordcount++;
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return dwordcount;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int j = 0; j < 100; j++)
    {
        while (table[j] != NULL)
        {
            node *del = table[j]->next;
            free(table[j]);
            table[j] = del;
        }
    }
    return true;
    return false;

}