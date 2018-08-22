#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    //Checks if there are arguments
    if(argc!=2)
    {
        printf("Error\n");
        return 1;
    }
    else
    {
        string key;

        key = argv[1];

        int keylen;

        keylen = strlen(argv[1]);

        //Checks for numbers in arguments
        for(int i=0; i<keylen; i++)
        {

            if(isalpha(key[i]))
            {
                //nothing
            }
            else
            {
                printf("Error\n");
                return 1;
            }
        }

        //Ask for user input
        printf("plaintext: ");
        string plaintext;
        plaintext = get_string();

        printf("ciphertext: ");

        //Declaring variables that will be used later on
        int plainlen;
        plainlen = strlen(plaintext);

        int j;
        j = 0;

        for(int i=0; i<plainlen; i++)
        {
            j = j % keylen;

            //Checks if plaintext is alphabetical
            if(isalpha(plaintext[i]))
            {

                int intplain;
                intplain = (int)plaintext[i];


                //checks if the i'th of the plaintext is upper
                if(isupper(plaintext[i]))
                {
                    //checks if the j'th of the key is upper
                    if(isupper(key[j]))
                    {
                        //ciphering
                        int ctext;
                        ctext =(((intplain - 65) + ((int)key[j] - 65)) % 26) + 65;
                        printf("%c", (char)ctext);
                        j++;
                    }
                    //checks if the j'th of the key is lower
                    else if(islower(key[i]))
                    {
                        //ciphering
                        int ctext;
                        ctext =(((intplain - 65) + ((int)key[j] - 97)) % 26) + 65;
                        printf("%c", (char)ctext);
                        j++;
                    }
                }
                //else plaintext is lower
                else if(islower(plaintext[i]))
                {
                    //checks if the j'th of the key is upper
                    if(isupper(key[j]))
                    {
                        //ciphering
                        int ctext;
                        ctext =(((intplain - 97) + ((int)key[j] - 65)) % 26) + 97;
                        printf("%c", (char)ctext);
                        j++;
                    }
                    //checks if the j'th of the key is lower
                    else if(islower(key[j]))
                    {
                        //ciphering
                        int ctext;
                        ctext =(((intplain - 97) + ((int)key[j] - 97)) % 26) + 97;
                        printf("%c", (char)ctext);
                        j++;
                    }
                }

            }
            //keeps numbers in plaintext
            else
            {
                printf("%c",plaintext[i]);
            }
        }
    }
    printf("\n");
    return 0;
}