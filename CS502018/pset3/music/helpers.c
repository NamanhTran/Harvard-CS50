// Helper functions for music

#include <cs50.h>
#include <stdlib.h>
#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    //Declare flag, length, x, and y variable
    bool flag = false;
    int length = strlen(fraction);
    int x = 0;
    int y = 0;

    //goes through the string and assign x and y to their values
    for(int i = 0; i < length; i++)
    {
        if(fraction[i] == '\0')
        {
            break;
        }
        else if(fraction[i] == '/')
        {
            flag = true;
        }

        else if(!flag)
        {
            x = atoi(&fraction[i]);
        }

        else
        {
            y = atoi(&fraction[i]);
        }

    }

    //makes it over 8
    while(y != 8)
    {
        x *= 2;
        y *= 2;
    }

    //returns x
    return x;

}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    //declare noteLen which contains the length of the note
    int noteLen = strlen(note);
    //finds endChar value which is the offset semitones from 4
    int endChar = ((note[noteLen - 1] - '0') - 4);
    //declare offset variable
    int offset = 0;

    //finds the offset of the note
    switch(note[0])
    {
        case 'B':
        {
            offset = 2;
            break;
        }
        case 'C':
        {
            offset = -9;
            break;
        }
        case 'D':
        {
            offset = -7;
            break;
        }
        case 'E':
        {
            offset = -5;
            break;
        }
        case 'F':
        {
            offset = -4;
            break;
        }
        case 'G':
        {
            offset = -2;
            break;
        }
        default:
        {
            offset = 0;
        }
    }

    //finds the main offset
    int startChar = offset + (12 * endChar);

    //temp variable to hold the freq
    double tempFreq = 0;

    //if the note has a flat or sharp
    if(noteLen == 3)
    {
        if(note[1] == 'b')
        {
            startChar -= 1;
        }

        else
        {
            startChar += 1;
        }
    }

    //finds the freq of the note
    tempFreq = 440 * pow(2, (startChar / 12.0));

    //rounds the note of the freq
    int freq = round(tempFreq);
    return freq;

}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    //if space return true
    int compare = strcmp(s, "");
    if(compare == 0)
    {
        return true;
    }
    return false;
}
