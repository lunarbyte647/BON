arith.y
%{
    #include <stdio.h>
    #include <stdlib.h>

    void yyerror(char *s);
    int yylex();
%}

%token NUM

%left '+' '-'
%left '*' '/'

%%

expr
    : expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | '(' expr ')'
    | NUM
    ;

%%

int main()
{
    printf("Enter an arithmetic expression:\n");

    if (yyparse() == 0)
        printf("Valid Expression\n");

    return 0;
}

void yyerror(char *s)
{
    printf("Invalid Expression\n");
}

