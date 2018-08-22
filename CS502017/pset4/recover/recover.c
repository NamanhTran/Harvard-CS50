#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//make struct with BYTE
typedef uint8_t  BYTE;

int main(int argc, char *argv[])
{
    //checks for proper useage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }
    
    //opens the file
    FILE *infile = fopen(argv[1], "r");
    if(infile == NULL)
    {
        fprintf(stderr, "Can't open\n");
        return 2;
    }
    
    //declarations
    int n;
    n = 0;
    
    int counter;
    counter = 0;
    
    int found;
    found = 0;
    
    FILE *newfile;
    
    BYTE block[512];
    
    while(fread(block, sizeof(BYTE), 512, infile) == 512)
    {
       //checks for start of jpeg
       if(block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] & 0xf0) == 0xe0)
       {
           
           //if previously found close the last file
           if(found == 1)
           {
               fclose(newfile);
               found = 0;
           }
           
           //creates new file
           char filename[8];
           
           sprintf(filename, "%03i.jpg", counter);
           
           newfile = fopen(filename, "w");
           if(newfile == NULL)
           {
               return 4;
           }
           
           //indicates that a jpeg is found
           found = 1;
           
           //use to name file
           counter++;
           
           //writes to outfile
           fwrite(&block, 512 * sizeof(BYTE), 1, newfile);
       }
       
       //if jpeg header isn't found and part of an image
       else if(found == 1)
       {
           fwrite(&block, 512, 1, newfile);
       }
    }
    //close file
    fclose(newfile);
    
    //success
    return 0;
}