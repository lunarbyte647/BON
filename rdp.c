#include <stdio.h>
#include <string.h>

char s[100];
int i = 0;
int error = 0;

void E();
void Eprime();
void T();
void Tprime();
void F();

void skipSpaces()
{
    while (s[i] == ' ' || s[i] == '\t')
        i++;
}

// E -> T E'
void E()
{
    if (error) return;

    T();
    Eprime();
}

// E' -> + T E' | - T E' | epsilon
void Eprime()
{
    if (error) return;

    skipSpaces();

    if (s[i] == '+' || s[i] == '-')
    {
        i++;
        T();
        Eprime();
    }
}

// T -> F T'
void T()
{
    if (error) return;

    F();
    Tprime();
}

// T' -> * F T' | / F T' | epsilon
void Tprime()
{
    if (error) return;

    skipSpaces();

    if (s[i] == '*' || s[i] == '/')
    {
        i++;
        F();
        Tprime();
    }
}

// F -> id | (E)
void F()
{
    if (error) return;

    skipSpaces();

    if (s[i] == 'i' && s[i + 1] == 'd')
    {
        i = i + 2;
    }
    else if (s[i] == '(')
    {
        i++;
        E();

        skipSpaces();

        if (s[i] == ')')
            i++;
        else
            error = 1;
    }
    else
    {
        error = 1;
    }
}

int main()
{
    printf("Enter the expression: ");
    scanf("%99s", s);

    E();

    if (error == 0 && s[i] == '\0')
        printf("Accepted");
    else
        printf("Invalid String");

    return 0;
}
