/**
 * Resizes a BMP
 */
       
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize f infile outfile\n");
        return 1;
    }

    // parse conversion factor from string
    float conversion = atof(argv[1]);
    
    if (conversion <= 0 || conversion > 100) {
        fprintf(stderr, "Conversion (f) should be > 0 and <= 100\n");
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
        return 1;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 1;
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
    
    // store old height and width data
    int oldWidth = bi.biWidth;
    
    int inputPadding = (4 - (oldWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    // int oldHeight = abs(bi.biHeight);

    // change height and width data in header
    bi.biWidth *= conversion;
    bi.biHeight *= conversion;
    
    // store new height and width
    int newWidth = bi.biWidth;
    int newHeight = abs(bi.biHeight);
    
    // padding for output file
    int padding = (4 - (newWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // change image size for output file
    bi.biSizeImage = newHeight * ((newWidth * sizeof(RGBTRIPLE)) + padding);
    
    // change file size for output file
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    // size of a scanline in input file
    int lengthScanline = oldWidth * sizeof(RGBTRIPLE);
    
    // buffer to store input file's scanline
    RGBTRIPLE *scanline = malloc(lengthScanline);
    
    // counter to track of last row
    int oldRow = 0;
    
    // Start iterating over each line of output file
    for (int i = 0; i < newHeight; i++) {
        // currRow is the row number that should be copied from the input file
        // for a particular conversion =>
        // for 0th row in output file, 0/conversion row of input is copied
        // for 1st row in output file, 1/conversion row of input is copied
        int currRow = (int)floor(i/conversion);
        
        printf("Row to be copied from input: #%i\t Last row copied: #%i\t i=%i\n", currRow, oldRow, i);
        
        // if starting at i=0 or only when the current row is greater than old row, read new line
        
        if (i==0) {
            printf("Reading new line...\n");
            fread(scanline, lengthScanline, 1, inptr);
            // skip over padding, if any
            fseek(inptr, inputPadding, SEEK_CUR);
        } else if (currRow > oldRow) {
            while((oldRow != currRow)) {
                printf("Reading new line...\n");
                fread(scanline, lengthScanline, 1, inptr);
                // skip over padding, if any
                fseek(inptr, inputPadding, SEEK_CUR);
                oldRow++;
            }
        }
        
        // start filling pixels
        for (int j = 0; j < newWidth; j++) {
            // the index of pixel to be copied is
            int index = (int)floor(j/conversion);
            
            printf("Copying pixel from index: %i\t to index: %i\n", index, j);
            
            RGBTRIPLE rgb;
            
            rgb = scanline[index];
            
            fwrite(&rgb, sizeof(RGBTRIPLE), 1, outptr);
        }
        
        
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
        
        oldRow = currRow;
    }
    
    // free malloc'd space
    free(scanline);

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
