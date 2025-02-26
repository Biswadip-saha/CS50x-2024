// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;
typedef uint8_t Byte;
typedef int16_t Byte2;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    Byte b1[HEADER_SIZE];
    fread(b1, HEADER_SIZE, 1, input);
    fwrite(b1, HEADER_SIZE, 1, output);

    // TODO: Read samples from input file and write updated data to output file
    Byte2 b2;
    while (fread(&b2, sizeof(b2), 1, input) != 0)
    {
        b2 = b2 * factor;
        fwrite(&b2, sizeof(b2), 1, output);
    }
    // Close files
    fclose(input);
    fclose(output);
}
