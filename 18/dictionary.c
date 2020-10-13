// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>

#include "dictionary.h"

#define HASHTABLE_SIZE 65536

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = HASHTABLE_SIZE;

// Hash table
node *table[N];
unsigned int totalWords = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //Initialize lower case word
    char lcword[LENGTH + 1];

    for (int i = 0; i < LENGTH; i++)
        lcword[i] = tolower(word[i]);

    node *cursor = table[hash(lcword)];

    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }

        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //https://www.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/cf9nlkn/
    unsigned int hash_value;

    for (int i=0, n=strlen(word); i<n; i++)
        hash_value = (hash_value << 2) ^ word[i];

    return hash_value % HASHTABLE_SIZE;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{

    FILE *dicfile = fopen(dictionary, "r");
    char *word = malloc(LENGTH);

    //Check if word is null
    if (word == NULL)
        return false;

    //Check if the fopen function opened a not NULL file
    if (dicfile == NULL)
        return false;

    //Iterate over dictionary until fscanf return EOF (meaning it's the end of the file)
    while (fscanf(dicfile, "%s", word) != EOF)
    {
        //Create a node to store the current word
        node *new_node = malloc(sizeof(node));

        if (new_node == NULL)
            return false;

        //Copy the new_node's word into the current word
        strcpy(new_node->word, word);

        //Get the index (hash the current word and store it in n)
        int n = hash(new_node->word);

        //Insert the new_node into the linked list
        new_node->next = table[n];
        table[n] = new_node;

        //Add to the total number of words in the text file
        totalWords++;
    }

    fclose(dicfile);
    free(word);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return totalWords;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{

    for (int i = 0; i < HASHTABLE_SIZE; i++)
    {
        node* cursor = table[i];
        node* tmp;

        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
        free(cursor);
    }
    return true;
}