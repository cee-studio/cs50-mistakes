// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// Represents number of children for each node in a trie
#define N 27

// Represents a node in a trie
typedef struct node
{
    bool is_word;
    struct node *children[N];
}
node;

void nodeCreator(struct node *c, int X);
void nullFree();
int wordCount;

// Represents a trie
node *root;
node *current;
node *ptr;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize trie
    root = malloc(sizeof(node));
    current = malloc(sizeof(node));
    if (root == NULL)
    {
        return false;
    }
    root->is_word = false;
    for (int i = 0; i < N; i++)
    {
        root->children[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into trie
    while (fscanf(file, "%s", word) != EOF)
    {
        //To reset to the top of the trie
        current = root;
        int x;
        //Loop over the characters of the word
        for(int i = 0; i <= strlen(word); i++)
        {
            //check if end of string, if yes, mark as word.
            if(word[i] == '\0')
            {
                current->is_word = true;
                wordCount++;
            }
            //if not, check if apostrophe or letter
            else
            {
                //if apostrophe, move to end of array
                if(isalpha(word[i]) == 0)
                {
                    x = 26;
                    if(current->children[x] == NULL)
                    {
                        nodeCreator(current, x);
                    }
                }
                //if it's a letter
                else
                {
                    //Convert letter to a lowercase int, and then get it into 0-25 range.
                    x = ((int)tolower(word[i])) - 97;
                    //Check if position already exists for letter
                    //if not, malloc a new node, set is_word flag to false,
                    //initialize all children array items to NULL
                    //point position to created node
                    if(current->children[x] == NULL)
                    {
                        nodeCreator(current, x);
                    }
                }
                //finally, move current position in trie forward for next cycle
                current = current->children[x];
            }
        }
    }
    // Close dictionary
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return wordCount;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    current = root;
    for(int i = 0; i <= strlen(word); i++)
    {
        int x;
        if(word[i] == '\0')
        {
            if(current->is_word == true)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
            if(isalpha(word[i]) == 0)
            {
                if(current->children[26] == NULL)
                {
                    return false;
                }
                else
                {
                    current = current->children[26];
                }
            }
            else
            {
                x = ((int)tolower(word[i])) - 97;
                if(current->children[x] == NULL)
                {
                    return false;
                }
                else
                {
                    current = current->children[x];
                }
            }
    }
    return false;
}

//Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    current = root;
    for(int i = 0; i < N; i++)
    {
        nullFree();
    }
    free(current);
    free(ptr);
    free(root);
    return true;
}

void nullFree()
{
    for(int i = 0; i < N; i++)
    {
        if(current->children[i] == NULL)
        {
            printf("NULL");
            return free(current);
        }
        else
        {
            current = current->children[i];
            nullFree();
        }
    }
}

void nodeCreator(struct node *c, int x)
{
    ptr = malloc(sizeof(node));
    ptr->is_word = false;
    for (int j = 0; j < N; j++)
    {
        ptr->children[j] = NULL;
    }
    c->children[x] = ptr;
}