/**
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

const int COLOR_MAX = 0xFF;
const int COLOR_MIN = 0x00;

int paddingCalc(int width);
void writeHeader(FILE* outFile,BITMAPFILEHEADER bf,BITMAPINFOHEADER bi);
void paddingWrite(FILE* outfile,int padding);
RGBTRIPLE fixPixel(RGBTRIPLE triple);
void writeBody(FILE* inptr, FILE* outptr, BITMAPINFOHEADER bi);

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 3)
    {
        fprintf(stderr, "Usage: ./whodunit infile outfile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[1];
    char *outfile = argv[2];

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
    writeHeader(outptr,bf,bi);
    writeBody(inptr,outptr,bi);
    fclose(inptr);
    fclose(outptr);
    return 0;
}

int paddingCalc(int width)
{
  return (4 - (width * sizeof(RGBTRIPLE)) % 4) % 4;  
}

void writeHeader(FILE* outFile,BITMAPFILEHEADER bf,BITMAPINFOHEADER bi)
{
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outFile);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outFile);
}

void paddingWrite(FILE* outfile,int padding)
{
    for (int k = 0; k < padding; k++)
    {
        fputc(0x00, outfile);
    }
}

RGBTRIPLE fixPixel(RGBTRIPLE triple)
{
    if (triple.rgbtRed == COLOR_MAX) 
    {
        triple.rgbtRed = COLOR_MIN;
        triple.rgbtBlue = COLOR_MIN;
        triple.rgbtGreen = COLOR_MIN;
    }
    return triple;
}

void writeBody(FILE* inptr, FILE* outptr, BITMAPINFOHEADER bi)
{
    // determine padding for scanlines
    int padding =  paddingCalc(bi.biWidth);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            RGBTRIPLE triple;
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            triple = fixPixel(triple);
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }
        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
        // then add it back (to demonstrate how)
        paddingWrite(outptr,padding);
    }
}