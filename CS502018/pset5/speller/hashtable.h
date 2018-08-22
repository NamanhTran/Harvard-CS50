#define TABLE_SIZE 10000
#include <ctype.h>


//hash function
/**
 * A case-insensitive implementation of the djb2 hash function.
 * Change NUM_BUCKETS to whatever your number of buckets is.
 *
 * Adapted by Neel Mehta from
 * http://stackoverflow.com/questions/2571683/djb2-hash-function.
 */
unsigned int hash_word(const char* word)
{
    unsigned long hash = 5381;

    for (const char* ptr = word; *ptr != '\0'; ptr++)
    {
        hash = ((hash << 5) + hash) + tolower(*ptr);
    }

    return hash % TABLE_SIZE;
}


// single linked list struct
typedef struct sllist
{
    char* value;
    struct sllist* next;
}sllnode;


// delcare hashtable to use
sllnode* global_hashtable[TABLE_SIZE];

