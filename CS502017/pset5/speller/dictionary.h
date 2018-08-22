/**
 * Declares a dictionary's functionality.
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word);

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);

//start of my stuff
//struct for list
typedef struct sllist
{
    char string[LENGTH + 1];
    struct sllist *next;
}
sllnode;

//creates list
sllnode* create(char c[]);

//search list
bool find(sllnode* head, char *word);

//insert node
sllnode* insert(sllnode* head, char word[]);

//free list
void destory(sllnode* head[]);

//hash function
unsigned int hash_word(const char* word);

//HASH FUNCTION FROM HERE github.com/hathix/cs50-section/blob/master/code/7/sample-hash-functions/good-hash-function.c

#endif // DICTIONARY_H
