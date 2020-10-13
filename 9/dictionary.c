#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
Node;

//number of words
int word_count = 0;

// Number of buckets in hash table
const unsigned int N = 25;

// Hash table
Node *table[N];


// Returns true if word is in dictionary else false
bool check(const char *word)
{
    bool isWord;
    //gets hash value of word
    int index = hash(word);

    //makes temp cursor node
    //Node *cursor = NULL;
    Node* cursor = malloc(sizeof(Node));
    if(cursor == NULL)
    {
        return 1;
    }

    //makes a copy from word
    /*char copy[LENGTH+1];
    for(int i = 0; i < strlen(word) ;i++)
    {
        copy[i] = tolower(word[i]);
    }
    copy[LENGTH] = '\0';
    */

    //points cursor to hashtable
    cursor->next = table[index];
    //checks that cursor points to corect word
    while(cursor->next != NULL)
    {
        if(strcasecmp(cursor->word,word) == 0)
        {
            isWord = true;
        }
        else
        {
            isWord = false;
        }
    }

    return isWord;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    char first_letter = word[0];
    first_letter = tolower(first_letter);
    int hash_num = (int)(first_letter) - 97;
    return hash_num;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //creates pointer to dictionary
    FILE *dict_ptr = fopen(dictionary,"r");
    if(dict_ptr == NULL)
    {
        return false;
    }

    for(int i = 0; i < 25; i++)
    {
        table[i] = malloc(sizeof(Node));
        table[i] = NULL;
    }

    char buffer[LENGTH];
    int n = LENGTH+1;

    //opens up dictionary and makes a singly linked list
    while(fgets(buffer,n,dict_ptr) != NULL)
    {
        buffer[strlen(buffer)-1] = '\0';
        //creates temp word to store words in
        Node* temp_word = NULL;
        temp_word = malloc(sizeof(Node));
        if(temp_word == NULL)
        {
            return 1;
        }

        //copies words in dictionary to node temp_word
        strcpy(temp_word->word,buffer);
        int index = hash(buffer);
        //sets temp word to point to table
        temp_word->next = table[index];
        table[index] = temp_word;
        word_count++;
    }

    fclose(dict_ptr);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for(int i = 0; i < 25; i++)
    {
        Node *temp = NULL;
        temp = malloc(sizeof(Node));

        table[i]->next = temp;
        free(table[i]);
        free(temp);
    }
    return true;
}