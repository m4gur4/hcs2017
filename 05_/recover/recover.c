#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;
const int BLOCK = 512;
const int LETTERS = 7;

bool isJpeg(BYTE* buf);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover infile \n");
        return 1;
    }
    char *infile = argv[1];
    FILE *rawFile = fopen(infile, "r");
    if (rawFile == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    FILE* jpegFile = NULL;
    int jpegCouter = 0;
    char* jpegName = malloc(LETTERS * sizeof(char));
    
    BYTE* buf;
    buf = malloc(BLOCK * sizeof(BYTE));
    while ( !feof(rawFile) ) 
        {
            fread(buf, BLOCK, 1, rawFile);      
            if (isJpeg(buf))
            {
                if (jpegFile != NULL)
                   fclose(jpegFile);
                sprintf(jpegName, "%03d.jpg", jpegCouter);
                jpegFile = fopen(jpegName, "w");
                jpegCouter++;
               // printf("%s , ", jpegName);
            }
            
            if (feof(rawFile)) 
                break;    
            if (jpegFile != NULL) 
                fwrite(buf, BLOCK, 1, jpegFile);
        }
    free(buf);
    free(jpegName);
    
    fclose(rawFile);
    if (jpegFile != NULL)
        fclose(jpegFile);

    return 0;
}

bool isJpeg(BYTE* buf)
{
    if ( (buf[0]==0xff) && (buf[1]==0xd8) && (buf[2]==0xff) && (buf[3]>>4==0xe) ) return 1;
    else return 0;
}