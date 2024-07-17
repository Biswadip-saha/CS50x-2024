#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int values(string);

char alpha[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
int value[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int main(void)
{
    string player1 = get_string("Player 1: ");
    string player2 = get_string("Player 2: ");

    int value1 = values(player1);
    int value2 = values(player2);

    if (value1 > value2)
    {
        printf("Player 1 wins!\n");
    }
    else if (value1 < value2)
    {
        printf("Player 2 wins!\n");
    }
    else if (value1 == value2)
    {
        printf("Tie!\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

int values(string sentence)
{
    int sum = 0;
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if (toupper(sentence[i]) == alpha[j])
            {
                sum = sum + value[j];
            }
        }
    }
    return sum;
}
