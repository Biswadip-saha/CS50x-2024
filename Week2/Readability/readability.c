#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

string sent;

int calc(string);

int main(void)
{
    // gets the text from the user

    sent = get_string("Text: ");

    // prints the grade of the text inputted by the user

    int value = calc(sent);
    if (value < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (1 <= value && value < 16)
    {
        printf("Grade %i\n", value);
    }
    else if (value >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

// the calc function

int calc(string letter)
{
    int L = 0;
    int S = 0;
    int W = 1;
    for (int i = 0; i < strlen(letter); i++)
    {
        if (isalpha(letter[i]))
        {
            L += 1;
        }
        else if (isspace(letter[i]))
        {
            W += 1;
        }
        else if (letter[i] == '?' || letter[i] == '.' || letter[i] == '!')
        {
            S += 1;
        }
    }

    // calculating the grade using Coleman-Liau index (index = 0.0588 * L - 0.296 * S - 15.8) where L is the average number of letters per 100 words in the text, and S is the average number of sentences per 100 words in the text

    float index = 0.0588 * ((float)L / W) * 100 - 0.296 * ((float)S / W) * 100 - 15.8;
    return (int)round(index);
}
