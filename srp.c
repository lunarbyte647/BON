#include<stdio.h>
#include<string.h>

char stack[100][3], input[100];
int top = -1;
int i = 0;

void show() {
    int j;

    for(j=0; j<=top; j++) {
        printf("%s", stack[j]);
    }
    printf("\n");
}

int reduce() {
    if(top >=0 && strcmp(stack[top], "id") == 0) {
        strcpy(stack[top], "E");
        return 1;
    }

    if(top >= 2 &&
        strcmp(stack[top - 2], "(") == 0 &&
        strcmp(stack[top - 1], "E") == 0 &&
        strcmp(stack[top], ")") == 0) {
            top -= 2;
            strcpy(stack[top], "E");
            return 1;
        }

    if(top >= 2 &&
        strcmp(stack[top - 2], "E") == 0 &&
        strchr("+-*/", stack[top - 1][0]) &&
        strcmp(stack[top], "E") == 0) {
            top -= 2;
            strcpy(stack[top], "E");
            return 1;
        }

    return 0;
}

int main() {
    printf("Enter the string: ");
    scanf("%s", input);

    while(input[i] != '\0') {
        if(input[i] == 'i' && input[i + 1] == 'd') {
            strcpy(stack[++top], "id");
            i += 2;
        } else {
            stack[++top][0] = input[i++];
            stack[top][1] = '\0';
        }

        printf("SHIFT: ");
        show();

        while(reduce()) {
            printf("REDUCE: ");
            show();
        }
    }

    if(top == 0 && strcmp(stack[0], "E") == 0) {
        printf("Accepted\n");
    } else{
        printf("Rejected");
    }

    return 0;
}
