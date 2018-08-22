#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    //check if user put in the proper arguments
    if (argc != 2)
    {
        printf("Useage: ./vigenere k\n");
        return 1;
    }

    //set arguemnt to key and length to length of key
    string key = argv[1];
    int length = strlen(key);

    //array to keep the key's alphabet number change
    int keyArray[length];

    //check for numbers in key
    for (int i = 0; i < length; i++)
    {
        //if confirmed a letter make it a uppercase then store the value of the letter into keyArray
        if (isalpha(key[i]))
        {
            key[i] = toupper(key[i]);
            keyArray[i] = (int)key[i] - 65;
        }

        //if number is found send error
        else
        {
            printf("Useage: ./vigenere k\n");
            return 1;
        }
    }

    //ask user for plainText
    string plainText = get_string("plaintext: ");
    printf("ciphertext: ");

    //plaintext's length
    int plainLength = strlen(plainText);

    //counter for keyArray
    int counter = 0;

    //goes through each letter of plaintext
    for (int j = 0; j < plainLength; j++)
    {
        //changes the letter if upper
        if (isupper(plainText[j]))
        {
            //formula to change plaintext letter to ciphertext letter
            int cText = ((int)plainText[j] + keyArray[(counter % length)]);

            //if needs to wraparound
            if (cText > 90)
            {
                cText = (cText % 91) + 65;
            }

            //prints ciphered letter
            printf("%c", cText);

            counter++;
        }

        //changes the letter if lower
        else if (islower(plainText[j]))
        {
            //formula to change plaintext letter to ciphertext letter
            int cText = ((int)plainText[j] + keyArray[(counter % length)]);

            //if needs to wraparound
            if (cText > 122)
            {
                cText = (cText % 123) + 97;
            }

            //prints ciphered letter
            printf("%c", cText);

            counter++;
        }

        //if the letter in question is not a letter
        else
        {
            printf("%c", plainText[j]);
        }
    }

//new line
printf("\n");

return 0;

}