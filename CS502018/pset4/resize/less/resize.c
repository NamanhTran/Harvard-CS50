// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }

    int scale = atoi(argv[1]);

    //check if scale is positive and less than or equal to 100
    if (scale < 0 || scale > 100)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // outfile's new header and info header
    BITMAPFILEHEADER bfNew = bf;
    BITMAPINFOHEADER biNew = bi;

    //change the outfile's image width and height
    biNew.biWidth *= scale;
    biNew.biHeight *= scale;

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int newPadding = (4 - (biNew.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    //change the image size
    biNew.biSizeImage = ((sizeof(RGBTRIPLE) * biNew.biWidth) + newPadding) * abs(biNew.biHeight);
    bfNew.bfSize = biNew.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bfNew, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&biNew, sizeof(BITMAPINFOHEADER), 1, outptr);

    RGBTRIPLE RGBarray[biNew.biWidth];

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        int counter = 0;
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            for(int k = 0; k < scale; k++)
            {
                // write RGB triple to outfile
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                RGBarray[counter] = triple;
                counter++;
            }
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // puts padding for the new image
        for (int k = 0; k < newPadding; k++)
        {
            fputc(0x00, outptr);
        }

        // resizes the image vertically
        for (int j = 0; j < scale - 1; j++)
        {
            // use the RGBarray to print the pixel
            for(int l = 0; l < biNew.biWidth; l++)
            {
                fwrite(&RGBarray[l], sizeof(RGBTRIPLE), 1, outptr);
            }

            //padding for the line
            for (int k = 0; k < newPadding; k++)
            {
                fputc(0x00, outptr);
            }
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
