#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int checkletters(string);
int checkalpha(string);
string cipher(string, string);

int main(int argc, string argv[])
{
    if (argc == 1)
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }
    else if (argc == 2)
    {
        if (strlen(argv[1]) != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        if (checkalpha(argv[1]) && checkletters(argv[1]))
        {
            string plain = get_string("plaintext: ");
            printf("ciphertext: %s\n", cipher(plain, argv[1]));
        }
        else
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
    }
    else if (argc > 2)
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }
    else
    {
        printf("INVALID\n");
        return 1;
    }
}

int checkletters(string key)
{
    int count[26] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 26; i++)
    {
        int index = toupper(key[i]) - 65;
        if (count[index] == 0)
        {
            count[index] += 1;
        }
        else
        {
            return 0;
        }
    }
    return 1;
}

int checkalpha(string key)
{
    for (int i = 0; i < 26; i++)
    {
        if (isalpha(key[i]) == 0)
        {
            return 0;
        }
    }
    return 1;
}

string cipher(string plaintext, string key)
{
    for (int i = 0; i < strlen(plaintext); i++)
    {
        char character = plaintext[i];
        if (isalpha(character))
        {
            int keyIndex = toupper(character) - 65;

            if (isupper(character))
            {
                plaintext[i] = toupper(key[keyIndex]);
            }
            else
            {
                plaintext[i] = tolower(key[keyIndex]);
            }
        }
    }
    return plaintext;
}
