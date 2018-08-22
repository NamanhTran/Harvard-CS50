#include <stdio.h>
#include <cs50.h>
#include <ctype>

#define _XOPEN_SOURCE
#include <unistd.h>

int main(int argc, string argv[])
{
    //checks for proper arguemnts
    if (argc != 2)
    {
        printf("Useage: ./crack hash\n");
        return 1;
    }

    string hash = argv[1];

    return 0;
}

//resources
//http://www.gnu.org/software/libc/manual/html_node/crypt.html
//https://www.reddit.com/r/cs50/comments/5rkl6z/what_the_crack/