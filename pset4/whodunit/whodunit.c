/**
 * Converts full red to white and darkens other pixels for readability 
 */ 

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[]) {
    if (argc != 3)
    {
        fprintf(stderr, "Usage: ./whodunit infile outfile\n");
        return 1;
    }
    
    char *infile = argv[1];
    char *outfile = argv[2];
    
    // opening input file
    FILE *inptr = fopen(infile, "r");
    
    // check if input file opened
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }
    
    // opening output file
    FILE *outptr = fopen(outfile, "w");
    
    // checking if output file opened
    if (outptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", outfile);
        return 3;
    }
    
    
    // input file's bitmapfileheader
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    
    // input file's bitmapinfoheader
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    
    // checking if input file is a 24-bit bmp
    if (bf.bfOffBits != 54 || bi.biSize != 40 || bi.biBitCount != 24 || bi.biCompression != 0 || bf.bfType != 0x4d42) {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // rows of pixels
    for (int i=0, biHeight = abs(bi.biHeight); i < biHeight; i++) {
        // iterate over pixels
        for (int j=0; j< bi.biWidth; j++) {
            
            // buffer for reading rgb triple
            RGBTRIPLE rgb;

            // read rbg
            fread(&rgb, sizeof(RGBTRIPLE), 1, inptr);
            
            // check if rgb is full red
            if (rgb.rgbtRed == 255 && rgb.rgbtGreen == 0 && rgb.rgbtBlue == 0) {
                // if rgb is full red, make it white
                rgb.rgbtGreen = 255, rgb.rgbtBlue = 255;
            } 
            else {
                if (rgb.rgbtRed < 240 && rgb.rgbtRed > 225) {
                    rgb.rgbtRed = 240;
                    rgb.rgbtBlue = 240;
                    rgb.rgbtGreen = 240;
                } else if (rgb.rgbtRed < 225 && rgb.rgbtRed > 200) {
                    rgb.rgbtRed = 225;
                    rgb.rgbtBlue = 225;
                    rgb.rgbtGreen = 225;
                } else if (rgb.rgbtRed < 200 && rgb.rgbtRed > 175) {
                    rgb.rgbtRed = 125;
                    rgb.rgbtBlue = 125;
                    rgb.rgbtGreen = 125;
                } else if (rgb.rgbtRed <= 175 && rgb.rgbtRed > 150) {
                    rgb.rgbtRed = 60;
                    rgb.rgbtBlue = 60;
                    rgb.rgbtGreen = 60;
                } else if (rgb.rgbtRed <= 150 && rgb.rgbtRed > 100) {
                    rgb.rgbtRed = 50;
                    rgb.rgbtBlue = 50;
                    rgb.rgbtGreen = 50;
                } else if (rgb.rgbtRed <= 150 && rgb.rgbtRed > 100) {
                    rgb.rgbtRed = 25;
                    rgb.rgbtBlue = 25;
                    rgb.rgbtGreen = 25;
                } else if (rgb.rgbtRed <= 100 && rgb.rgbtRed > 50) {
                    rgb.rgbtRed = 15;
                    rgb.rgbtBlue = 15;
                    rgb.rgbtGreen = 15;
                } else if (rgb.rgbtRed <= 50 && rgb.rgbtRed > 0) {
                    rgb.rgbtRed = 0;
                    rgb.rgbtBlue = 0;
                    rgb.rgbtGreen = 0;
                }
            }
            
            fwrite(&rgb, sizeof(RGBTRIPLE), 1, outptr);
        }
        
        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }
    
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}