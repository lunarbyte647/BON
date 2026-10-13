#include <stdio.h>
#include <ctype.h>
#include <string.h>
char p[20][20];
int n;
void first(char c)
{
    int i;
    if (!isupper(c))
    {
        printf("%c ", c);
        return;
    }
    for (i = 0; i < n; i++)
    {
        if (p[i][0] == c)
        {
            if (p[i][2] == '#')
                printf("# ");
            else
                first(p[i][2]);
        }
    }
}
void follow(char c)
{
    int i, j;
    if (c == p[0][0])
        printf("$ ");
    for (i = 0; i < n; i++)
    {
        for (j = 2; p[i][j] != '\0'; j++)
        {
            if (p[i][j] == c)
            {
                if (p[i][j + 1] != '\0')
                {
                    first(p[i][j + 1]);
                }
                else if (p[i][0] != c)
                {
                    follow(p[i][0]);}}}}}
int main()
{
    int i;
    char c;
    printf("Enter number of productions: ");
    scanf("%d", &n);
        printf("\nFIRST:\n");
    for (i = 0; i < n; i++)
    {
        c = p[i][0];
        printf("FIRST(%c) = { ", c);
        first(c);
        printf("}\n");
    }
    printf("\nFOLLOW:\n");
    for (i = 0; i < n; i++)
    {
        c = p[i][0];
        printf("FOLLOW(%c) = { ", c);
        follow(c);
        printf("}\n");
    }
    return 0;
}
printf("Enter productions (use # for epsilon):\n");
    for (i = 0; i < n; i++)
        scanf("%s", p[i]);}
