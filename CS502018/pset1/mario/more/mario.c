#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //counter and variables
    int height = 0;
    int counter = 1;

    //ask user for height
    do
    {
        height = get_int("Height: ");
    }
    while(height > 23);

    while(height != 0)
    {
        //adds whitespace before #
        for(int j = 0; j < (height - 1); j++)
        {
            printf(" ");
        }

        //prints first set of #
        for(int i = 0; i < counter; i++)
        {
            printf("#");
        }

        //prints whitespace that seperate the #
        printf("  ");

        //prints the second set of #
        for(int i = 0; i < counter; i++)
        {
            printf("#");
        }

        //next line
        printf("\n");

        //decrease/increase variables
        height--;
        counter++;
    }
    return 0;
}