// Implements a dictionary's functionality
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>
#include <cs50.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
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
const unsigned int N = 17576;

// Hash table
node *table[N];


// int for storing number of words in hashtable
unsigned int numofwords = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    bool ans = false;
    int index = hash(word);

    node *cursor = table[index];

    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            ans = true;
            break;
        }
        else
        {
            cursor = cursor->next;
        }
    }
    return ans;
}


// Hashes word to a number
unsigned int hash(const char *word)
{
    int char1, char2, char3;
    char word2[LENGTH + 1];
    for (int i = 0; i < LENGTH; i++)
    {
        word2[i] = tolower(word[i]);
    }
    char1 = (int) word2[0] - 97;
    char2 = (int) word2[1] - 97;
    char3 = (int) word2[2] - 97;
    return ((676 * char1) + (26 * char2) + char3) % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    char word[LENGTH + 1];
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return 1;
    }
    while (fscanf(file, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return 1;
        }

        strcpy(n->word, word);

        int index = hash(n->word);
        if (table[index] != NULL)
        {
            n->next = table[index];
        }
        table[index] = n;
        numofwords += 1;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return numofwords;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
        free(cursor);
    }
    return true;
}
