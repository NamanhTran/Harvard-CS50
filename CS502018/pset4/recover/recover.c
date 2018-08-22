#include <stdio.h>
#include <stdint.h>

typedef uint8_t  BYTE;

#define BLOCK_SIZE 512

int main(int argc, char* argv[])
{
    //checks if the user inputted proper arguments
    if(argc != 2)
    {
        printf("Usage: ./recover image\n");
    }

    //opens the inputFile and checks if it opens sucessfully
    FILE* inputFile = fopen(argv[1], "r");
    if(inputFile == NULL)
    {
        //print error
        fprintf(stderr, "Cannot open %s\n", argv[1]);
        return 1;
    }

    //declare the byte block array
    BYTE block[BLOCK_SIZE];

    //counter to use for the new file names
    int counter = 0;

    //char array containting the new images names
    char fileName[9];

    //reads in blocks from the file until EOF
    while(fread(block, BLOCK_SIZE, 1, inputFile) == 1)
    {
        //if found start of JPG
        if(block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] & 0xf0) == 0xe0)
        {
            //create file name
            sprintf(fileName, "%03i.jpg", counter);

            //increase number for next image name
            counter++;

            //create the image file
            FILE* outputFile = fopen(fileName, "w");

            //write to the outputFile
            fwrite(block, BLOCK_SIZE, 1, outputFile);

            //flag for while loop
            int flag = 0;

            while(flag == 0)
            {
                //variable used to use for EOF situation
                int check = fread(block, BLOCK_SIZE, 1, inputFile);

                //if did not reach end of file
                if(check == 1)
                {
                    //writes to the outfile containing the jpg's information
                    if(block[0] != 0xff || block[1] != 0xd8 || block[2] != 0xff || (block[3] & 0xf0) != 0xe0)
                    {
                        fwrite(block, BLOCK_SIZE, 1, outputFile);
                    }

                    //if we hit a new jpg
                    else
                    {
                        //stop while loop
                        flag = 1;

                        //go back one block
                        fseek(inputFile, -(BLOCK_SIZE), SEEK_CUR);
                    }
                }

                //if we hit EOF write last bit to the outfile
                else
                {
                    fwrite(block, check, 1, outputFile);
                    flag = 1;
                }
            }

            //closes the out file
            fclose(outputFile);
        }
    }

    //closes the inputfile
    fclose(inputFile);

    //sucess
    return 0;
}