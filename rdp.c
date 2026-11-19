
#include <stdio.h>
#include <stdlib.h>

char s[100];
int i = 0;

void S();

void error()
{
    printf("Invalid String\n");
    exit(0);
}

void S()
{
    if (s[i] == '(')
    {
        i++;
        S();

        if (s[i] == ')')
        {
            i++;
            S();
        }
        else
        {
            error();
        }
    }
}

int main()
{
    printf("Enter the string: ");
    scanf("%99s", s);

    S();

    if (s[i] == '\0')
        printf("Accepted");
    else
        printf("Rejected");

    return 0;
}
