// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
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

//initializes a global variable to count the words
int counterx = 0;

// Number of buckets in hash table
const unsigned int N = 20000;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //obtains the hash index of the word.
    int hashindex = hash(word);

    //creates a pointer to the active node
    node *activenode = table[hashindex];

    //loops the check process until it reaches the end of the chain
    while(activenode != NULL)
    {
        //compares the word against the node content.
        bool match = strcasecmp(activenode->word, word);

        //returns true if match found.
        if (match == 0)
        {
            return true;
        }

        //if not true, it sets activenode to point at the next node.
        else
        {
            activenode = activenode->next;
        }
    }

    //if not found, returns false.
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // djb2 hash function from http://www.cse.yorku.ca/~oz/hash.html
    unsigned long hash = 5381;
    int c;

    char lower[LENGTH + 1];
    char* target = &lower[0];
    
    for (int i = 0; i < LENGTH+1; i++)
    {
        lower[i] = tolower(word[i]);
    }
    
    while ((c = *target++))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //open the dictionary file.
    FILE* file = fopen(dictionary, "r");
    
    //error check if pointer NULL
    if (file == NULL)
    {
        return 1;
    }

    //initializes array called temp to store the word.
    char temp[LENGTH+1];

    //scans one string at a time into temp.
    while ((fscanf(file, "%s", temp) != EOF))
    {
        //mallocs memory the size of a node and returns a pointer to that node.
        node *n = malloc(sizeof(node));
        
        //malloc error check
        if (n == NULL)
        {
            return 1;
        }

        //copies the string from temp to the newly mallocd node -> word
        strcpy(n->word, temp);
        
        //sets newly mallocd node onward pointer to NULL
        n->next = NULL;
        
        //initiaizes a hash variable and assigns the hash code generated by the hash function to that variable.
        int hashindex = hash(n->word);
        n->next = table[hashindex];
        table[hashindex] = n;
        
        //increments the global variable which counts the words in the dictionary.
        counterx++;

    }

    return true;

}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    //returns the value of the global variable which is incremented in the load function.
    return counterx;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    
    for (int i = 0; i < N; i++)
    {
        
        node* temp = table[0];
        
        while (temp != NULL)
        {
            node* cursor = temp->next;
            free(temp);
            temp = cursor;
        }
        
    }
    
    return true;

    
}