/**
 * Copies a BMP piece by piece, just because.
 */
       
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
    
    int n = atoi(argv[1]);
    
    if(n >= 100 || n <= 0)
    {
        fprintf(stderr, "n must be positive and less than or equal to 100\n");
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
    
    //outfile's BITMAPFILEHEADER
    BITMAPFILEHEADER bfnew;
    bfnew = bf;
    
    //outfile's BITMAPINFOHEADER
    BITMAPINFOHEADER binew;
    binew = bi;
    
    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    //infile's padding
    int ogpadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    //outfile's new width
    binew.biWidth = bi.biWidth * n;
    
    //outfile's new height
    binew.biHeight = bi.biHeight * n;
    
    // determine padding for scanlines
    int padding = (4 - (binew.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    //outfile's image size
    binew.biSizeImage = ((sizeof(RGBTRIPLE) * binew.biWidth) + padding) * abs(binew.biHeight);
    
    //outfile's total file size
    bfnew.bfSize = binew.biSizeImage + sizeof(bfnew) + sizeof(binew);
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bfnew, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&binew, sizeof(BITMAPINFOHEADER), 1, outptr);

    RGBTRIPLE array[sizeof(RGBTRIPLE) * abs(binew.biWidth)];
    
    int counter;
    counter = -1;
    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        counter = 0;
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            RGBTRIPLE triple;
            
            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
            //repeat pixel n times
            for(int k = 0; k < n; k++)
            {
                array[counter] = triple;
                counter++;
            }
        }
        
        //prints array n time for each row
        for(int m = 0; m < n; m++)
        {
            //prints array's pixels
            for(int o = 0; o < binew.biWidth; o++)
            {
                fwrite(&array[o], sizeof(RGBTRIPLE), 1, outptr);
            }
            
            // then add it back (to demonstrate how)
            for (int l = 0; l < padding; l++)
            {
                fputc(0x00, outptr);
            }
        }    

        // skip over padding, if any
        fseek(inptr, ogpadding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
