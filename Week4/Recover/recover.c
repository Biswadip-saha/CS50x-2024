#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const int fileChunk = 512;
typedef uint8_t Byte;

int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        printf("Usage: ./recover filename\n");
        return 1;
    }

    FILE *img = fopen(argv[1], "r");
    if (img == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    Byte b[fileChunk];
    int counter = 0;
    FILE *recoveredImg = NULL;

    while (fread(b, fileChunk, 1, img) != 0)
    {
        if (b[0] == 0xff && b[1] == 0xd8 && b[2] == 0xff && (b[3] & 0xf0) == 0xe0)
        {
            if (counter != 0)
            {
                fclose(recoveredImg);
            }

            char filename[50] = "recoveredImg.jpg";
            sprintf(filename, "%03i.jpg", counter);

            recoveredImg = fopen(filename, "w");
            if (recoveredImg == NULL)
            {
                printf("Could not open file.\n");
                return 1;
            }

            fwrite(b, fileChunk, 1, recoveredImg);

            counter += 1;
        }
        else
        {
            if (counter > 0)
            {
                fwrite(b, fileChunk, 1, recoveredImg);
            }
        }
    }
    fclose(recoveredImg);
    fclose(img);
}
