// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Decalre trie node struct
typedef struct trie
{
    bool isLeaf;
    struct trie* children[Alphabet_size];
}
trie;

//Declare root node globally
trie* root_node;

// Declare word globally
char string[LENGTH + 1];

// Keep track of number of words in dictionary
int dict_size = 0;

// Function that gets new trie node
struct trie* getNewTrieNode(void)
{
    // Malloc memory for new trie node and check pointer != NULL
    struct trie* node = malloc(sizeof(trie));
    if (node != NULL)
    {
        // Set isLeaf Boolean to false
        node->isLeaf = false;
        // Initialise all 26 child pointers to NULL
        for (int i = 0; i < Alphabet_size; i++)
        {
            node->children[i] = NULL;
        }
    }
    return node;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //Open dictionary.h file
    FILE *dict_ptr = fopen(dictionary, "r");
    // Check to see if dictionary.h file pointer is NULL
    if (dict_ptr == NULL)
    {
        fprintf(stderr, "Error: Could not open %s", dictionary);
        return false;
    }
    // Create array of chars into which we can temporarily store each word
    char buffer[LENGTH + 1];
    // Dynamically allocate memory for universal root node
    root_node = malloc(sizeof(trie));
    // Loop over whole file to copy each string until we reach EOF
    while (fscanf(dict_ptr, "%s", buffer) != EOF)
    {
        // Insert word into Trie data structure
        // Create pointer to root_node in order to traverse data structure
        struct trie* current_node = root_node;
        int j = strlen(buffer);
        for (int i = 0; i < j; i++)
        {
            // Create new node if child pointer does not point to path
            if (current_node->children[buffer[i] - 'a'] == NULL)
            {
                current_node->children[buffer[i] - 'a'] = getNewTrieNode();
            }
            //Go to next node if child pointer points to one
            current_node = current_node->children[buffer[i] - 'a'];
            // Move to next character in string
            buffer[i]++;
        }
        dict_size++;
    }
    fclose(dict_ptr);
    return true;
}

// Returns true if word is in dictionary else false
bool check(const char* word)
{
    // Make lowercase copy of word (so it will match path of corresponding word from dictionary)
    int n = strlen(word);
    char word_copy[n + 1];
    for (int i = 0; i < n; i++)
    {
        word_copy[i] = tolower(word[i]);
    }
    // Add NULL terminating character to lowercase copy of word
    word_copy[n] = '\0';
    // Search Trie data structure for lowercase copy of word
    // Return false if Trie is empty
    if (root_node == NULL)
    {
        return false;
    }
    // Declare pointer to root_node to traverse Trie data structure
    struct trie* current_node = root_node;
    // Declare integer the length of the lowercase copy of word
    int k = strlen(word_copy);
    for (int i = 0; i < k; i++)
    {
        // Go to next node
        current_node = current_node->children[word_copy[i] - 'a'];
        // If current_node pointer is NULL we have reached the end of the path and the string has not been found
        if (current_node == NULL)
        {
            return false;
        }
        // Move to next character in string
        word_copy[i]++;
    }
    // If we have gotten through whole string, current node must be Leaf Node corresponding to that string
    return (current_node->isLeaf);
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return dict_size;
}

// Prototype for destroy trie data structure function
void destroy(struct trie* root_node);

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    destroy(root_node);
    return true;
}

// Destroys entire trie data structure recursively and frees dynamically allocated memory
void destroy(struct trie* root)
{
    // Initialise current node to point to root node to traverse trie data structure
    struct trie* current_node = root_node;
    // Recursively delete entire trie data structure
    for (int i = 0; i < Alphabet_size; i++)
    {
        if (current_node->children[i] != NULL)
        {
            destroy(current_node->children[i]);
        }
    }
    free(current_node);
}