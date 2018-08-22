#include <stdio.h>
#include <cs50.h>

int main(void)
    {
        int h;
        do
        {
            printf("Height:");
            h = get_int();
        }
        while (h<0||h>23);
        for (int i = 0; i<h; i++)
        {
           for(int s = h-2; s>=i; s--)
           {
               printf(" ");
           }
           for(int d = -2; d<i; d++)
           {
               printf("#");
           }
           for(int p = h; p==h; p++)
           {
               printf("\n");
           }
        }
    
    }