#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

#include "dictionary.h"

//Size counter
int counter = 0;

//Hash function declaration
unsigned int hash(const char *str);

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

//Function declaration
void freenode(node *trav);

// Number of buckets in hash table
const unsigned int N = 40000;

// Hash table
node *table[N] = { NULL };

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //Hash word
    int index = hash(word) % N;

    //Access linked list, traverse and compare
    node *trav = malloc(sizeof(node));
    trav = table[index];
    while (1)
    {
        if (strcasecmp(word, trav->word) == 0)
        {
            return true;
        }
        if (trav->next == NULL)
        {
            break;
        }
        else
        {
            trav = trav->next;
        }

    }
    free(trav);
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //Open file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Couldn't open dictionary\n");
        return false;
    }

    //Loop that iterates through each string of file
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        //Size counter
        counter++;

        //Create a new node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Not enough memory\n");
            return false;
        }
        strcpy(n->word, word);  //set word

        //Hash word
        int index = hash(word) % N;

        //Insert into table
        n->next = table[index];
        table[index] = n;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return counter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *trav = NULL;
        trav = table[i];
        freenode(trav);
        return true;
    }

    return false;
}

// hash function djb2 by Dan Bernstein, code taken from http://www.cse.yorku.ca/~oz/hash.html
unsigned int hash(const char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

//FREE NODE function definition
void freenode(node *trav)
{
    if (trav->next != NULL)
        {
            trav = trav->next;
            freenode(trav->next);
        }
    else
        {
            free(trav);
        }
}