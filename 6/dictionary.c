#include "dictionary.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 70;

// Hash table
node *table[N];



// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int x = hash(word);
    node *q = table[x] -> next;
    while  (q != NULL){
        if (strcmp(q -> word, word) == true)
        {
            return true;
        }
        else {
            q = q-> next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{

    int sum = 0;
    int word_size = 0;
    for (int j = 0; word[j] != '\0'; j++)
    {
        sum += word[j];
        word_size++;
    }

    return sum % N;
}

int dict_size = -1;
bool yes = false;
// Loads dictionary into memory, returning true if successful else false
bool load(const char *dict) {

    FILE* dictionary = fopen(dict, "r");
    if (dictionary != NULL) { 
        char* temp = malloc(LENGTH * sizeof(char));


        node* temp1 = malloc(sizeof(node));
        while (fgets(temp, LENGTH + 1, dictionary) != NULL){

            node* n = malloc(sizeof(node)); 
            if (table[hash(temp)] -> next != NULL)
            {
                n = table[hash(temp)] -> next;
            }


            table[hash(temp)] -> next = temp1;
            //temp1 -> word = temp;
            if (table[hash(temp)] -> next != NULL) {
                temp1 -> next = n;
            }
                dict_size++;

        }
        //while(temp != NULL);
        yes = true;

        return true;
    }
    yes = false;

    return false;


}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    printf("size start");
    if (yes == true)
    {
        printf("size end");
        return dict_size;
    }
    else {
        printf("size end");
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{

    for (int n = 0; n <= N - 1; n++)
    {
        while (table[n] -> next != NULL)
        {
            node* j = table[n] -> next;
            while (j -> next -> next != NULL)
            {
                j = j -> next;
            }
            free(j -> next);
        }
    }
    for (int i = 0; i < N; i++)
    {
        if (table[i] -> next != NULL)
        {

            return false;
        }
    }

    return true;
}