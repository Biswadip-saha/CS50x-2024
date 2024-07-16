#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // gets the name of the user
    string name = get_string("What's your name? ");

    // prints hello (user)
    printf("hello, %s\n", name);
}
