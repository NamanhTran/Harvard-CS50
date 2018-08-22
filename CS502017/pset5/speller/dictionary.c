/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "dictionary.h"
#define LENGTH 45
#define HASHTABLE_SIZE 10000
//global variables
int counter = 0;
sllnode *hashtable[HASHTABLE_SIZE];
sllnode *headp;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // TODO
    
    //change upper to lower
    char *lowerword = malloc((strlen(word) * sizeof(char)) + 1);
    
    for(int i = 0; i < (strlen(word) + 1); i++)
    {
        
        //check if it's alphabetical
        if(isalpha(word[i]))
        {
            
            //checks if it's not lower
            if(!islower(word[i]))
            {
                lowerword[i] = tolower(word[i]);
            }
            
            //if it's lower
            else
            {
                lowerword[i] = word[i];
            }
        }
        
        //prints same letter if not alphabetical
        else
        {
            lowerword[i] = word[i];
        }
    }
    
    //hash the new lowerword
    int key = hash_word(lowerword);

    //search dictionary for word
    bool result = find(hashtable[key], lowerword);
    
    //free malloc mem
    free(lowerword);
    
    //return result
    return result;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    // TODO
    
    //Opens file
    FILE *file = fopen(dictionary, "r");
    if(file == NULL)
    {
        printf("Failed to open file.\n");
        return false;
    }
    
    else
    {
        //declaring variables
        char word[LENGTH + 1];
        
        int key;
        
        //scans for words from file
        while(fscanf(file, "%s", word) != EOF)
        {
            //hash word
            key = hash_word(word);
            
            //if bucket is empty
            if(hashtable[key] == NULL)
            {
                hashtable[key] = create(word);
                counter++;
            }
            
            //if bucket isn't empty
            else 
            {
                //insert into the existing list
                hashtable[key] = insert(hashtable[key], word);
                counter++;
            }
        }
        
        fclose(file);
        
        return true;
    }
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    //returns dictionary word count
    return counter;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    //go over every bucket in hashtable
    for(int i = 0; i <= HASHTABLE_SIZE; i++)
    {
        destory(&hashtable[i]);
    }
    
    return true;
}

//start of my stuff

//creates list
sllnode* create(char word[])
{
    
    //creating space for new node
    sllnode *node = malloc((sizeof(sllnode)));
    if(node == NULL)
    {
        unload();
        printf("Memory error in creating list\n");
        return false;
    }
    
    //copies word to node's string
    strcpy(node->string, word);
    
    //next is NULL due to start of a list
    node->next = NULL;
    
    return node;
}

//search list
bool find(sllnode *list, char *word)
{
    //TODO
    
    //declaring a trav variable
    sllnode *trav = list;
    
    //search
    while(trav != NULL)
    {    
        
        //compares the two strings
        int found = strcasecmp(trav->string, word);
        
        //if found
        if(found == 0)
        {
            return true;
        }
        
        //next if not found
        trav = trav->next;
        
    }
    
    return false;
}

//insert node
sllnode* insert(sllnode *head, char word[])
{
    //creating space for node
    sllnode *node = malloc((sizeof(sllnode)));
    if(node == NULL)
    {
        unload();
        printf("Memory error in creating list\n");
        return false;
    }
    
    //puts word into node's string
    strcpy(node->string, word);
    
    node->next = NULL;
    
    //make node's next point to head
    node->next = head;
    
    //returning node will result head pointing to node
    return node;
}

//free list
void destory(sllnode* head[])
{
    //TODO
   
   sllnode* trav = *head;
   
   //repeat until end of list
   while(trav != NULL)
   {
       sllnode* tmp = trav;
    
       trav = trav->next;
    
       free(tmp);
   }
}

//hash function
unsigned int hash_word(const char* word)
 {
     unsigned long hash = 5381;

     for (const char* ptr = word; *ptr != '\0'; ptr++)
     {
         hash = ((hash << 5) + hash) + tolower(*ptr);
     }

     return hash % HASHTABLE_SIZE;
 }
 //hash function is taken from github.com/hathix/cs50-section/blob/master/code/7/sample-hash-functions/good-hash-function.c