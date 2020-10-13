// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 50000;

// Number of words in dictionary
int k;


// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // hash the word we want to know is in the dictionary or not
    int index = hash(word) % 50000;
    //creates node to traverse the linked list

    if (table[index] == NULL)
    {
        return false;
    }
    else
    {
        for (node *tmp = table[index]; tmp != NULL; tmp = tmp->next)

        if (strcasecmp(tmp->word, word) == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
     }
     return false;
}



///* D. J. Bernstein hash function */
unsigned int hash(const char *word)
{
   size_t hash = 5381;
    while (*word)
        hash = 33 * hash ^ (unsigned char) *word++;
    return hash % 50000;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //declares a variable that will be what hash() returns
    int index;
    // creates a string to read dictionary entries into
    char dictionary_entry[LENGTH+1];
    FILE *pf;
    pf = fopen(dictionary, "r");
    if (pf == NULL)
    {
        return false;
    }
    // read one word at a time for as long a enf of file not reached
    while (fscanf(pf, "%s", dictionary_entry) != EOF)
    {
        printf ("%s\n", dictionary_entry);
        node *n = malloc(sizeof(node));
        if ( n == NULL)
        {
            return false;
        }
        //copy dictionary entry into new node
        strcpy(n->word, dictionary_entry);
        // set new node's pointer to null
        n->next = NULL;
        // call hash function and pass the new word
        index = hash(dictionary_entry);

        // if head points to nothing, then list is empty and I make the new word first element of list
        if (table[index] == NULL)
        {
            table[index] = n;
        }

        else
        {
            n->next = table[index]->next;
            table[index] = n;
        }
        k+= 1;

    }
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return k;
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *tmp;
    node *cursor;
    for (int i = 0; i < N; i++)
    {
        printf ("table[%d] = %p\n", i, table[i]);
        for (cursor = table[i]; 
             cursor; 
             cursor = cursor->next) {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    free(cursor);
    return false;
}