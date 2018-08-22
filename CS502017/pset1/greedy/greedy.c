#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float m;
    int i;
    int c;
    i=0;
    printf("O hai! How much change is owed?\n");
    m = get_float();
    c = round(m*100);
    while (m<0)
    {
        printf("How much change is owed?\n");
        m = get_float();
    }
    while (c>=25)
            {
                c=c-25;
                i++;
            }
    while (c>=10)
            {
                c=c-10;
                i++;
            }
    while (c>=5)
            {
                c=c-5;
                i++;
            }
    while (c>=1)
            {
                c=c-1;
                i++;
            }
        printf("%i\n",i);

}