// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
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
const unsigned int N = 26;

// Hash table
node *table[N];

// total number of words in the dictionary
unsigned int words_count = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    unsigned int hash_ret = hash(word);
    for (node *cursor = table[hash_ret]; cursor != NULL; cursor = cursor->next)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash_ret = 0;

    if (isalpha(word[0]))
    {
        hash_ret = tolower(word[0]) - 'a';
    }
    else
    {
        hash_ret = 'x' - 'a';
    }
    return hash_ret;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *file_p = fopen(dictionary, "r");
    if (file_p == NULL)
    {
        // printf("Error opening dictionary file!");
        return false;
    }

    // read one word at a time from file to memory
    char buffer[LENGTH + 1];
    while (fscanf(file_p, "%s", buffer) != EOF)
    {
        words_count ++;
        node *tmp = malloc(sizeof(node));
        if (tmp == NULL)
        {
            // printf("malloc failed!");
            fclose(file_p);
            return false;
        }
        strcpy(tmp->word, buffer);
        tmp->next = NULL;
        unsigned int hash_ret = hash(buffer);
        if (table[hash_ret] == NULL)
        {
            table[hash_ret] = tmp;
        }
        else
        {
            tmp->next = table[hash_ret];
            table[hash_ret] = tmp;
        }
    }
    fclose(file_p);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return words_count;
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
    }
    return true;
}
