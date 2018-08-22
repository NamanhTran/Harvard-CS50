#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    //Ask user for input.
    string name = get_string();
    
    //Prints the first letter.
    printf("%c", toupper(name[0]));
    
    //Scans for ' ' and takes the next element, capitalizes it, and prints it.
    for(int i=0;i<strlen(name);i++)
    {
        if(name[i]==' ')
        {
            printf("%c",toupper(name[i+1]));
        }
    }
    printf("\n");
    return 0;
}