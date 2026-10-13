#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

char input[100];
int pos = 0;

void E();
void Eprime();
void T();
void Tprime();
void F();

void error()
{
    printf("Invalid Expression\n");
    exit(0);
}

/* E → T E' */
void E()
{
    T();
    Eprime();
}

/* E' → + T E' | - T E' | ε */
void Eprime()
{
    if (input[pos] == '+' || input[pos] == '-')
    {
        pos++;
        T();
        Eprime();
    }
}

/* T → F T' */
void T()
{
    F();
    Tprime();
}

/* T' → * F T' | / F T' | ε */
void Tprime()
{
    if (input[pos] == '*' || input[pos] == '/')
    {
        pos++;
        F();
        Tprime();
    }
}

/* F → ( E ) | id */
void F()
{
    if (input[pos] == 'i' && input[pos + 1] == 'd')
    {
        pos += 2;
    }
    else if (input[pos] == '(')
    {
        pos++;
        E();

        if (input[pos] == ')')
            pos++;
        else
            error();
    }
    else
    {
        error();
    }
}

int main()
{
    printf("Enter the expression: ");
    scanf("%s", input);

    E();

    if (input[pos] == '\0')
        printf("Valid Expression\n");
    else
        printf("Invalid Expression\n");

    return 0;
}
