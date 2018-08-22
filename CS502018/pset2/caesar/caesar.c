#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    //checks for proper arguements
    if (argc != 2 || atoi(argv[1]) < 0)
    {
        printf("Usage: ./caesar k\n");
        return 1;
    }

    //set key to argv[1] and wrap it around
    int key = atoi(argv[1]);
    while(key > 26)
    {
        key = (key % 26);
    }

    //ask user for plaintext
    string plainText = get_string("plaintext: ");

    //gets the plaintext's length
    int plainLen = strlen(plainText);

    //prints ciphertext
    printf("ciphertext: ");

    //goes through each element in the plaintext
    for(int i = 0; i < plainLen; i++)
    {
        //checks if if the plaintext is alphabetical
        if(isalpha(plainText[i]))
        {
            //checks if letter is uppercase
            if(isupper(plainText[i]))
            {
                //adds key to the letter
                int cWord = (((int)plainText[i]) + key);

                //wraps around if needed
                if(cWord > 90)
                {
                    cWord = (((int)cWord) % 91) + 65;
                }

                //printf the cipher letter
                printf("%c",cWord);
            }

            //checks if letter is lower case
            else if (islower(plainText[i]))
            {
                //adds key to letter
                int cWord = (((int)plainText[i]) + key);

                //wraps around if needed
                if(cWord > 122)
                {
                    cWord = (((int)cWord) % 123) + 97;
                }

                //prints cipher letter
                printf("%c",cWord);
            }
        }

        //if letter is not alphabetical print character
        else
            printf("%c", plainText[i]);
    }

//adds new line
printf("\n");

return 0;
}