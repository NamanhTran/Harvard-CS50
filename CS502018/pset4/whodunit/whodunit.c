#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>
#include "bmp.h"

#define RED 49
#define GREEN 31
#define BLUE 126

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        fprintf(stdout, "Usage: ./whodunit infile outfile\n");
        return 1;
    }

    FILE* inputf = fopen(argv[1], "r");
    if(inputf == NULL)
    {
        fprintf(stdout, "Cannot open %s\n", argv[1]);
        return 2;
    }

    FILE* outputf = fopen(argv[2], "w");
    if(outputf == NULL)
    {
        fprintf(stdout, "Cannot open %s\n", argv[2]);
        return 3;
    }

    //create and read the input file's file header
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inputf);

    //create and read the input file's info header
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inputf);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outputf);
        fclose(inputf);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    //write the file header to the output file
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outputf);

    //write the info header to the output file
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outputf);

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inputf);

            if(triple.rgbtRed == 255)
            {
                triple.rgbtRed = RED;
                triple.rgbtGreen = GREEN;
                triple.rgbtBlue = BLUE;
            }

            // write RGB triple to outfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outputf);
        }

        // skip over padding, if any
        fseek(inputf, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outputf);
        }
    }

    //close both the input and output file
    fclose(inputf);
    fclose(outputf);

    return 0;
}