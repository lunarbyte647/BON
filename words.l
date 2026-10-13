%{
    #include <stdio.h>
    #include <string.h>

    int lines = 0, words = 0, chars = 0;
%}
%%
END\n {
    printf("\nNumber of Lines : %d\n", lines);
    printf("Number of Words : %d\n", words);
    printf("Number of Characters : %d\n", chars);
    return 0;
}
\n {
    lines++;
    chars++;
}

[ \t]+ {
    chars += yyleng;
}

[^ \t\n]+ {
    words++;
    chars += yyleng;
}
%%
int yywrap()
{
    return 1;
}

int main()
{
    printf("Enter text (Type END on a new line to stop):\n");
    yylex();

    return 0;
}



