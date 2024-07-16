#include <cs50.h>
#include <math.h>
#include <stdio.h>

// prototypes of the functions

int digits(long, int);
int countDigits(long);

int main(void)
{
    long num = get_long("Enter the number: ");
    int counter = countDigits(num);
    int sum;
    int digit;

    // multiply every other digit by 2, and then add those products’ digits together and also add the digits that weren’t multiplied by 2

    for (int i = 1; i < counter + 1; i++)
    {
        if (i % 2 == 0)
        {
            digit = digits(num, i);
            digit = digit * 2;
            if (digit >= 10)
            {
                sum = sum + (digit / 10) + (digit % 10);
            }
            else
            {
                sum = sum + digit;
            }
        }
        else
        {
            digit = digits(num, i);
            sum = sum + digit;
        }
    }

    // conditions for different kinds of cards

    if (sum % 10 == 0)
    {
        //  Visa numbers start with 4 and have 13 or 16 digits

        if (counter == 13)
        {
            if (digits(num, counter) == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }

        // Amex numbers start with 34 or 37 and have 15 digits

        else if (counter == 15)
        {
            if (digits(num, counter) == 3 &&
                (digits(num, counter - 1) == 7 || digits(num, counter - 1) == 4))
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }

        // MasterCard numbers start with 51, 52, 53, 54, or 55 and have 16 digits

        else if (counter == 16)
        {
            if (digits(num, counter) == 5 &&
                (digits(num, counter - 1) == 1 || digits(num, counter - 1) == 2 ||
                 digits(num, counter - 1) == 3 || digits(num, counter - 1) == 4 ||
                 digits(num, counter - 1) == 5))
            {
                printf("MASTERCARD\n");
            }
            else if (digits(num, counter) == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

// digits function with 2 arguments, 1 for the number and the other for the digit place for returning the digit at the specified place

int digits(long a, int b)
{
    long rem = a % (long)pow(10, b);
    int quotient = rem / (long)pow(10, b - 1);
    return quotient;
}

// countDigits function with 1 argument for counting the number of digits in the number

int countDigits(long num)
{
    int counter = 0;
    while (num != 0)
    {
        num = num / 10;
        counter++;
    }
    return counter;
}
