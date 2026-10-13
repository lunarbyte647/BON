%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
%}


%%


int                     { printf("%s : Keyword\n", yytext); }
[0-9]+                  { printf("%s : Number\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]*  { printf("%s : Identifier\n", yytext); }
"="|"+"|"-"|"*"|"/"     { printf("%s : Operator\n", yytext); }
";"|","|"("|")"|"{"|"}" { printf("%s : Symbol\n", yytext); }


[ \t\n]+                ;


.                       { printf("%s : Unknown\n", yytext); }


%%


int main()
{
   char input[10000] = "";
   char line[256];


   printf("Enter code (type END on a new line to finish):\n");


   while (fgets(line, sizeof(line), stdin))
   {
       if (strcmp(line, "END\n") == 0 || strcmp(line, "END") == 0)
           break;


       strcat(input, line);
   }


   YY_BUFFER_STATE bp = yy_scan_string(input);


   yylex();


   yy_delete_buffer(bp);


   return 0;
}


int yywrap()
{
   return 1;
}
