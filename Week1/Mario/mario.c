#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int h;
    int j = 0;

    // do-while loop for accepting values of height which is at max 8
    do
    {

        // Asks the user the the height of the mario wall
        h = get_int("Height: ");

    } while (1 > h || h > 8);

    // for loop for printing height
    for (int i = 0; i < h; i++)
    {

        // while loop for printing the space before the hashes
        while (j < h - 1)
        {

            printf(" ");
            j++;
        }
        j = i + 1;

        // while loop for printing the tower again and the space between them
        for (int l = 0; l < 2; l++)
        {

            int k = h - i - 1;
            while (k < h)
            {
                printf("#");
                k++;
            }

            if (l == 0)
            {
                printf("  ");
            }
        }

        printf("\n");
    }
}
