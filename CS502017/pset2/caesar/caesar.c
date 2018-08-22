#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    //Checks for command-line arguments
    if (argc==1||argc>2)
    {
        printf("ERROR\n");
        return 1;
    }
    
    //Changing Key from string to int
    int key;
    key = atoi(argv[1]);
    
    //User inputs plaintext
    printf("plaintext:");
    string ptext;
    ptext = get_string();
    
    printf("ciphertext:");
    
    //Ciphering
    for(int i = 0; i<strlen(ptext); i++)
    {
            //Converting char to integer
            int intptext;
            intptext = (int)ptext[i];
            
            //If it's a number
            if(intptext>=48&&intptext<=57)
                {
                    printf("%c",ptext[i]);
                }
            else
            {
                if(isupper(ptext[i]))
                {
                    //Encoding the int
                    intptext = ((intptext-65) + key) % 26;
            
                    // Converting integer to char
                    char encodetext;
                    encodetext = (char)intptext + 65;
                    printf("%c",encodetext);
                }
                else if(islower(ptext[i]))
                {
                    //Encoding the int
                    intptext = ((intptext-97) + key) % 26;
            
                    // Converting integer to char
                    char encodetext;
                    encodetext = (char)intptext + 97;
                    printf("%c",encodetext);
                }
                else
                {
                    printf("%c",ptext[i]);
                }
                
            }
    }
    printf("\n");
    return 0;
}
