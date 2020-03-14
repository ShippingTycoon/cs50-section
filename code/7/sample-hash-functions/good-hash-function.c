// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <strings.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

unsigned int counter = 0;
bool loaded = false;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    char *wordlower = malloc(LENGTH);

    for (int i = 0; i < LENGTH; i++)
    {
        wordlower[i] = tolower(word[i]);
    }

    int index = hash(word);

    node *tmp = table[index];

    while (strcasecmp(wordlower, tmp->word) != 0)
    {
        if (tmp->next == NULL)
        {
            return false;
        }

        tmp = tmp->next;
    }
    return true;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    return (tolower(word[0]) - 97) % 25;

}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    char buffer[LENGTH + 1];

    while (fscanf(file, "%s", buffer) != EOF)
    {
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            return false;
        }

        strcpy(n->word, buffer);

        n->next = NULL;

        int index = hash(n->word);

        //check if first of that letter to enter hash table
        if (table[index] == NULL)
        {
            table[index] = n;
        }

        //otherwise place node at the start of the hash table
        else
        {
            n->next = table[index];
            table[index] = n;
        }
        counter++;
    }
    loaded = true;
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (loaded == true)
    {
        return counter;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int j = 0; j <= 25; j++)
    {
        node *cursor = table[j];
        while (cursor->next != NULL)
        {
            node *tmp = cursor->next;
            free(cursor);
            cursor = tmp;
        }
        free(cursor);
    }

    return true;
}
