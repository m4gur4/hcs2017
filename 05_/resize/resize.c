/**
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

int paddingCalc(int width);
void writeHeader(FILE* outFile,BITMAPFILEHEADER bf,BITMAPINFOHEADER bi);
void paddingWrite(FILE* outfile,int padding);
void writeBody(FILE* inptr, FILE* outptr, BITMAPINFOHEADER bi,BITMAPINFOHEADER newBI,float Ratio);
int resize(FILE *inptr,FILE *outptr,float Ratio);

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize N infile outfile\n");
        return 1;
    }

    // remember filenames
    float Ratio = atof(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    if ( Ratio<0 || Ratio>100) 
    {
        fprintf(stderr, " N must be between 0.00 and 100.00 %f.\n",Ratio);
        return 2;
    }
    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    return resize(inptr,outptr,Ratio);;
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

void writeBody(FILE* inptr, FILE* outptr, BITMAPINFOHEADER bi,BITMAPINFOHEADER newBI,float Ratio)
{
    RGBTRIPLE triple;
    
    RGBTRIPLE* buffer = malloc(newBI.biWidth*sizeof(RGBTRIPLE));
    
    int precision = Ratio*1000;
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++){
            
        int currentpixel = 0;  //in newline
        // read line to buffer
        for (int j = 0; j < bi.biWidth; j++){
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            // add pixel to buffer if need 
            if (j*precision%(int)(precision/Ratio) == 0){
                for(int z = 0; z<Ratio; z++){
                    *(buffer + currentpixel) = triple;
                    currentpixel++;
                } 
            }
        }
        // write line if need
        if (i*precision%(int)(precision/Ratio) == 0)
           for (int l = 0 ; l< Ratio; l++){
                fwrite(buffer, sizeof(RGBTRIPLE), newBI.biWidth, outptr);  
                paddingWrite(outptr,paddingCalc(newBI.biWidth));
            }
        fseek(inptr, paddingCalc(bi.biWidth), SEEK_CUR);
    }
    free(buffer);
}

int resize(FILE *inptr,FILE *outptr,float Ratio)
{    
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
    
    BITMAPFILEHEADER newBF;
    newBF = bf;
    BITMAPINFOHEADER newBI;
    newBI = bi;
    newBI.biWidth = lroundf(newBI.biWidth*Ratio);
    newBI.biHeight = lroundf(newBI.biHeight*Ratio);
    // outfile's header info
    newBI.biSizeImage = ((sizeof(RGBTRIPLE) * newBI.biWidth) + paddingCalc(newBI.biWidth)) * abs(newBI.biHeight);
    newBF.bfSize = newBI.biSizeImage + sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER);

    writeHeader(outptr,newBF,newBI);
    writeBody(inptr,outptr,bi,newBI,Ratio);

    fclose(inptr);
    fclose(outptr);
    return 0;
}