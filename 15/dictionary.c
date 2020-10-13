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

// Number of buckets in hash table
const unsigned int N = 2600;

// Hash table
node *table[N];

// Counter for size
int counter;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Making a pointer to the file which contains the dictionary
    FILE *file = fopen(dictionary, "r");
    // Declaring a temporary word to store the copied word from the dictionary
    char w[LENGTH + 1];
    // Check if memory is available
    if (file == NULL)
        return false;

    // Clearing the table to NULL
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // It will run until the file is finished
    while(fscanf(file, "%s", w) != EOF)
    {
        node *n = malloc(sizeof(node));
        // Check if memory is available
        if (n == NULL)
            return false;

        // Copy the word from the dictionary to w
        strcpy(n -> word, w);
        // Store the index at which the word should be stored
        int pos = hash(n -> word);

        // Set the 'next' value of 'n' to point at the head of the list
        n -> next = table[pos];
        table[pos] = n;

        // Increase the counter per word copied from the dictionary
        counter++;
        // Free the allocated memory
        free(n);
    }
    size();
    // close the file
    fclose(file);
    return true;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Idea inspired from "https://www.youtube.com/watch?v=2Ti5yvumFTU&t=782s"
    int sum = 0;
    for (int i = 0, len = strlen(word); i < len; i++)
    {
        sum +=  (int) word[i];
    }
    return (sum % N);
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return counter;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Make a temporary string to store the word to be checked
    char *temp = malloc(sizeof(char) * (LENGTH + 1));
    for (int i = 0; i < LENGTH; i++)
    {
        temp[i] = tolower(word[i]);
    }
    // Getting the hash value of the word to be searched
    int h = hash(temp);
    node *ptr = malloc(sizeof(node));
    temp[LENGTH] = '\0';

    // ptr searches table where the word would be if it exists
    ptr = table[h];
    while (ptr != NULL)
    {
        if (strcasecmp(temp, ptr -> word) == 0)
        {
            return true;
        }
        ptr = ptr -> next;
    }
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *ptr = table[i];
        // Free each linked list
        while (ptr != NULL)
        {
            node *tmp = ptr;;
            ptr = ptr->next;
            free(tmp);
        }
    }
    return true;
}