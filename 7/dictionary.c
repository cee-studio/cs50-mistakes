#include <stdbool.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
// It needs to be case insensitive
bool check(const char *word)
{
    int index = hash(word);
    node *tmp = NULL;
    if (table[index] != NULL)
    {
        tmp = table[index];
    }
    // Check if there is only one word in the dictionary
    if (tmp->next == NULL)
    {
        if(strcasecmp(tmp->word, word) == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    while(tmp->next != NULL)
    {
        // Check the first word
        if(strcasecmp(tmp->word, word) == 0)
        {
            return true;
        }
        // Iterate through the rest of the words
        tmp = tmp->next;
        if(strcasecmp(tmp->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int hash = 0;
    if(isalpha(word[0]))
    {
        if (isupper(word[0]))
        {
            hash = word[0] - 65;
        }
        else if (islower(word[0]))
        {
            hash = word[0] - 97;
        }
    }
    return hash;
}

bool load(const char *dictionary)
{
    // Open dictionary for reading
    FILE *file = fopen(dictionary, "r");
    if(!file)
    {
        return false;
    }

    int wordcount = 0;
    char *dictionaryword[LENGTH];
    while (fscanf(file, "%s", *dictionaryword) != EOF)
    {
        int index = hash(dictionaryword[0]);
        node *n = malloc(sizeof(node));
        if(n != NULL)
        {
            // Add scanned word to node element
            strcpy(n->word, *dictionaryword);
            wordcount++;

            // Add node (with word) to linked list at index
            if (table[index] != NULL)
            {
                // Case one: no node in hash table at index
                if (table[index]->next == NULL)
                {
                table[index] = n;
                }
                // Case two: at least one node in hash table at index
                else
                {
                    node *tmp = malloc(sizeof(node));
                    tmp = table[index];
                    table[index] = n;
                    n->next = tmp;
                }
            }
        }
    }
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    int wordcount = 0;
    for (int i = 0; i < N; i++)
    {
        // At each index, run down the linked list and count words
        node *tmp = malloc(sizeof(node));
        if (tmp != NULL)
        {
            tmp->next = NULL;
        }
        if (table[i] != NULL)
        {
            tmp = table[i];
            if (tmp->next == NULL)
            {
                wordcount++;
                continue;
            }
            while (tmp->next != NULL)
            {
                tmp = tmp->next;
                wordcount++;
            }
        }
    }
    return wordcount;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    while(true)
    {
        int counter = 0;
        node *cursor = malloc(sizeof(node));
        if (cursor != NULL)
        {
            cursor->next = NULL;
        }
        // Iterate over hash table
        for (int i = 0; i < LENGTH; i++)
        {
            if (table[i] != NULL)
            {
                cursor = table[i];
                // First case: there is only one node
                if (cursor->next == NULL)
                {
                    free(cursor);
                }
                // Second case: there is a linked list of nodes
                while(cursor->next != NULL)
                {
                    if (counter != 0)
                    {
                        node *tmp = malloc(sizeof(node));
                        tmp = cursor;
                        cursor = cursor->next;
                        free(tmp);
                    }
                    if (counter == 0)
                    {
                        node *tmp = malloc(sizeof(node));
                        tmp = table[i];
                        cursor = cursor->next;
                        free(tmp);
                        counter++;
                    }
                }
            }
        }
        return true;
    }
    return false;
}

