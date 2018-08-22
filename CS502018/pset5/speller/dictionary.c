// Implements a dictionary's functionality
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

#include "hashtable.h"

// counter for the size function
int counter = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // declare temp char array to store the word
    char temp[LENGTH + 1];

    // declare size so the for loop function doesn't have to run strlen() n times;
    int size = strlen(word);

    //cast the word to lowercase so we can
    for(int i = 0; i < size; i++)
    {
        temp[i] = tolower(word[i]);
    }

    //add string ender to temp
    temp[size] = '\0';

    int hash = hash_word(temp);

    for (sllnode *ptr = global_hashtable[hash]; ptr != NULL; ptr = ptr->next)
    {
        if (strcmp(temp, ptr->value) == 0)
        {
            return true;
        }
    }

    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // open the dictionary file
    FILE* dictionary_file = fopen(dictionary, "r");
    if(dictionary_file == NULL)
    {
        printf("Could not open dictionary file\n");
        return false;
    }

    // malloc space for a word
    char word[LENGTH + 1];

    // reads the file until EOF and stores word in word variable
    while(fscanf(dictionary_file, "%s", word) != EOF)
    {
        // hash the word
        int hash = hash_word(word);

        // call size of here so the program doesn't call sizeof() n times in the while loop
        int size = sizeof(word);

        // create linked list if it's not created yet
        if(global_hashtable[hash] == NULL)
        {
            // allocate space for a list and checks if it was sucessful
            sllnode* list = malloc(sizeof(sllnode));
            if(list == NULL)
            {
                fclose(dictionary_file);
                unload();
                return false;
            }

            // allocate space for a word and checks if it was sucessful
            list->value = malloc(sizeof(char) * (size + 1));
            if(list->value == NULL)
            {
                fclose(dictionary_file);
                unload();
                return false;
            }

            // copies the word into the list
            strcpy(list->value, word);

            // since the start of a new linked list next is null
            list->next = NULL;

            // point the head to the new linked list
            global_hashtable[hash] = list;

            // counter for size() function
            counter++;
        }

        // if there is a linked list add to that list
        else if(global_hashtable[hash] != NULL)
        {
            // allocate space for a list and checks if it was sucessful
            sllnode* list = malloc(sizeof(sllnode));
            if(list == NULL)
            {
                fclose(dictionary_file);
                unload();
                return false;
            }

            // allocate space for a word and checks if it was sucessful
            list->value = malloc(sizeof(char) * (size + 1));
            if(list->value == NULL)
            {
                fclose(dictionary_file);
                unload();
                return false;
            }

            // copies the word into the list
            strcpy(list->value, word);

            // next value points the the latest element in the list
            list->next = global_hashtable[hash];

            // head now points to the new list
            global_hashtable[hash] = list;

            // counter for the size() function
            counter++;
        }
    }
    fclose(dictionary_file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return counter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // goes through each bucket freeing each element
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        // temp ptr so we free the lists slowly
        sllnode* ptr = global_hashtable[i];

        // free each list then moves onto the next one
        while(ptr != NULL)
        {
            sllnode* next = ptr->next;
            free(ptr->value);
            free(ptr);
            ptr = next;
        }
    }
    return true;
}
