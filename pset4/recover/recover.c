/**
 * Recovers JPGs from a file
 */
       
#include <stdio.h>

int writeImage(int imageNumber);
int isJpeg(void);

const int BLOCK_SIZE = 512;
unsigned char buffer[BLOCK_SIZE];
unsigned char jpeg[] = {0xff, 0xd8, 0xff, 0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6,  0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef};
int imageNumber = 0;

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }
    
    char *infile = argv[1];
    
    FILE *file = fopen(infile, "r");
    
    if (file == NULL) {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 1;
    }
    
    int foundFirstImage = 0;
    
    while(fread(buffer, BLOCK_SIZE, 1, file) == 1) {
        // if jpg is found after the 1st one, start writing to another file.
        if (foundFirstImage == 1)
        {
            if (isJpeg() == 1) {
                imageNumber++;
            }
            writeImage(imageNumber);
        }
        // start writing if 1st jpg is found
        else if (isJpeg() == 1)
        {
            foundFirstImage = 1;
            writeImage(imageNumber);
        }
    }
    
    fclose(file);
}

// If JPEG, return 1 else return 0
int isJpeg() {
    if (buffer[0] != jpeg[0]) {
        return 0;
    }
    
    if (buffer[1] != jpeg[1]) {
        return 0;
    }
    
    if (buffer[2] != jpeg[2]) {
        return 0;
    }
    
    int flag = 0;
    
    for (int i = 3; i < 19; i++) {
        if (buffer[3] == jpeg[i]) {
            flag++;
        }
    }
    
    if (flag == 0) {
        return 0;
    }
    
    
    return 1;
}


// writes the buffer to output file (imageNumber supplied as param)
// returns 0 if successful else 1
int writeImage(int number) {
    char name[7];
    sprintf(name, "%.3i.jpg", number);
    
    // Append mode as jpg may be across multiple blocks, so we need to append to existing file and not overwrite it
    FILE *jpg = fopen(name, "a");
    
    if (jpg == NULL) {
        return 1;
    }
    
    fwrite(buffer, BLOCK_SIZE, 1, jpg);
    
    fclose(jpg);
    
    return 0;
}