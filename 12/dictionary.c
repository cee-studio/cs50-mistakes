// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

// Represents a node in a hash table

typedef struct node

{

  char word[LENGTH + 1];

  struct node *next;

}

node;

// number of words in the dictionary

int count = 0;

// Number of buckets in hash table

const unsigned int N = 100;

// Hash table

node *table[N];

// Returns true if word is in dictionary else false

bool check(const char *word)

{

  int index = hash(word);

  node *cursor = table[index];

  // check if the word is in the dictionary

  while (cursor != NULL)

  {

    if (strcasecmp(cursor->word, word))

    {

      return true;

    }

    else

    {

      cursor = cursor->next;
    }
  }

  return false;
}

// djb2 hash function from http://www.cse.yorku.ca/~oz/hash.html

// Hashes word to a number

unsigned int hash(const char *str)

{

  unsigned int hash = 5381;

  int c;

  while ((c = *str++))

    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

  return hash % N;

  return 0;
}

// Loads dictionary into memory, returning true if successful else false

bool load(const char *dictionary) {

  // file variable
  FILE *file;

  char *str = NULL;

  // opens the file and returns its adress

  file = fopen(dictionary, "r");

  if (file == NULL) {
    return false;
  }

  // creates a node for each word
  while (fscanf(file, "%s", str) != EOF) {

    // allocation of memory for the node

    node *n = malloc(sizeof(node));

    if (n == NULL)

    {

      return false;
    }

    int index = hash(str);

    strcpy(str, n->word);

    if (table[index] == NULL)

    {

      n->next = NULL;

      table[index] = n;

      count++;

    } else {

      n->next = table[index];

      table[index] = n;

      count++;
    }
  }
  return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded

unsigned int size(void)
{
  return count;
}

// Unloads dictionary from memory, returning true if successful else false

bool unload(void)
{
  int i = 0;
  node *cursor;
  node *tmp;

  while (i < N)

  {

    if (cursor == NULL)

    {

      i++;

      tmp = table[i];

      cursor = table[i];

    }

    else

    {

      cursor = cursor->next;

      free(tmp);

      tmp = cursor;
    }
  }

  return false;
}