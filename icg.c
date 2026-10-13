#include <stdio.h>
#include <string.h>
#include <ctype.h>

char expr[50];
int temp = 1;

void generate(char op, char a[], char b[], char result[])
{
    printf("%s = %s %c %s\n", result, a, op, b);
}

int precedence(char op)
{
    if (op == '*' || op == '/')
        return 2;

    if (op == '+' || op == '-')
        return 1;

    return 0;
}

int main()
{
    char operands[50][10];
    char operators[50];

    int top = -1;
    int opTop = -1;
    int i;

    printf("Enter expression: ");
    scanf("%49s", expr);

    printf("\nIntermediate Code:\n");

    for (i = 0; expr[i] != '\0'; i++)
    {
        if (isalnum((unsigned char)expr[i]))
        {
            top++;
            operands[top][0] = expr[i];
            operands[top][1] = '\0';
        }
        else
        {
            while (opTop >= 0 &&
                   precedence(operators[opTop]) >= precedence(expr[i]))
            {
                char a[10], b[10], result[10];

                strcpy(b, operands[top--]);
                strcpy(a, operands[top--]);

                sprintf(result, "t%d", temp);

                generate(operators[opTop], a, b, result);

                strcpy(operands[++top], result);

                temp++;
                opTop--;
            }

            operators[++opTop] = expr[i];
        }
    }

    while (opTop >= 0)
    {
        char a[10], b[10], result[10];

        strcpy(b, operands[top--]);
        strcpy(a, operands[top--]);

        sprintf(result, "t%d", temp);

        generate(operators[opTop], a, b, result);

        strcpy(operands[++top], result);

        temp++;
        opTop--;
    }

    return 0;
}
