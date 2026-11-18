#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

char stack[100];
int top = -1;
int temp = 1;

int precedence(char op) {
    if(op == '+' || op == '-') 
    {
        return 1;
    }

    if(op == '*' || op == '/') {
        return 2;
    }

    return 0;
}

int main() {

    char expr[100];
    char output[100];

    int i,j=0;
    printf("Enter the expression: ");
    scanf("%s", expr);

    for(int i=2; expr[i]!='\0'; i++) {
        char ch = expr[i];

        if(isalnum(ch)) {
            output[j++]  = ch;
        }

        else if(ch == '(') {
            stack[++top] = ch;
        }

        else if(ch == ')') {
            while(top >= 0 && stack[top] != '(') {
                output[j++] = stack[top--];
            }

            if(top >= 0 && stack[top] == '(') {
                top--;
            } 
        }

        else if(ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            while(top >= 0 && stack[top] != '(' && 
            precedence(stack[top]) >= precedence(ch)) {
                output[j++] = stack[top--];
            } 
            stack[++top] = ch;
        }
    }

    while(top >= 0) {
        output[j++] = stack[top--];
    }
    output[j] = '\0';

    printf("\n Three Address Code:\n"); 
    char operand[100][20];
    int operandTop = -1;

    for(int i=0; output[i] != '\0'; i++) {
        char ch = output[i];

        if(isalnum(ch)) {
            operand[++operandTop][0] = ch;
            operand[operandTop][1] = '\0';
        } else {
            char op1[20], op2[20];
            strcpy(op2, operand[operandTop--]);
            strcpy(op1, operand[operandTop--]);

            printf("t%d = %s %c %s\n", temp, op1, ch, op2);
            sprintf(operand[++operandTop], "t%d", temp);
            temp++;
        }
    }

    printf("%c = %s\n", expr[0], operand[operandTop]);
    return 0;
}
