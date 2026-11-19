
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char s[100];
int i = 0;

void E();
void T();
void F();
void Eprime();
void Tprime();

void error()
{
    printf("Rejected");
    exit(0);
}

void E()
{
    T();
    Eprime();
}

void Eprime()
{
    if (s[i] == '+')
    {
        i++;
        T();
        Eprime();
    }
}

void T()
{
    F();
    Tprime();
}

void Tprime()
{
    if (s[i] == '*')
    {
        i++;
        F();
        Tprime();
    }
}

void F()
{
    if (s[i] == '(')
    {
        i++;
        E();

        if (s[i] == ')')
            i++;
        else
            error();
    }
    else if (s[i] == 'i' && s[i+1] == 'd')
    {
        i = i + 2;
    }
    else
    {
        error();
    }
}

int main()
{
    printf("Enter the string: ");
    scanf("%99s", s);

    E();

    if (s[i] == '\0')
        printf("Accepted");
    else
        printf("Rejected");

    return 0;
}
