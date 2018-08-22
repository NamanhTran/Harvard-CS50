/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
//(needle, haystack, size)
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    //checks if there are numbers
    if(n <= 0)
    {
        return false;
    }
    
    else if (n > 0)
    {
        int start;
        start = 0;
        
        int end;
        end = n - 1;
        
        //searchs until found or not found
        while(end >= start)
        {
            int middle;
            middle = ((end + start)/2);
            
            if(values[middle] == value)
            {
                return true;
            }
            
            else if (values[middle] < value)
            {
                start = middle + 1;
            }
            
            else if (values[middle] > value)
            {
                end = middle - 1;
            }
            
            else
            {
                return false;
            }
        }
    }
    else
    {
        return false;
    }
    return false;
}

  

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement a sorting algorithm
    int scount;
    scount = -1;
    //i is used to implement "sorted side"
    for(int i = 0; i < n - 1; i++)
    {
        //check if sorted
        if(scount == 0)
        {
            return;
        }
            
        //swapping
        else if(scount != 0)
        {    
            scount = 0;
            
            for(int j = 0; j < ((n - 1) - i); j++)
            {    
                if(values[j] > values[j+1])
                {
                    int ogint;
                    ogint = values[j];
                    
                    int ogint2;
                    ogint2 = values[j+1];
                    
                    values[j+1] = ogint;
                    
                    values[j] = ogint2;
                    
                    scount++;
                }
            }    
        }
        else
        {
            return;
        }
    }    
    
    return;
}
