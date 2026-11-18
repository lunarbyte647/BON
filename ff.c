#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 20
#define SIZE 30

char prod[MAX][SIZE];
char first[26][SIZE], follow[26][SIZE];

int n;
int fc[26] = {0}, flc[26] = {0};

void add(char set[], int *count, char c) {
    for(int i = 0; i < *count; i++) {
        if(set[i] == c)
            return;
    }

    set[(*count)++] = c;
}

int isEpsilon(char set[], int count) {
    for(int i = 0; i < count; i++) {
        if(set[i] == '#')
            return 1;
    }
    return 0;
}

void FIRST() {
    int changed;

    do {
        changed = 0;

        for(int i = 0; i < n; i++) {
            char lhs = prod[i][0];
            int index = lhs - 'A';

            int nullable = 1;

            for(int j = 2; prod[i][j] != '\0'; j++) {
                char c = prod[i][j];
                // if it is terminal add to first set
                if(!isupper(c)) {
                    int old = fc[index];
                    add(first[index], &fc[index], c);

                    if(old != fc[index])
                        changed = 1;

                    nullable = 0;
                    break;
                }

                int k = c - 'A';
                // if it is Non Terminal and first of non terminal
                for(int x = 0; x < fc[k]; x++) {
                    if(first[k][x] != '#') {
                        int old = fc[index];
                        add(first[index], &fc[index], first[k][x]);

                        if(old != fc[index])
                            changed = 1;
                    }
                }

                if(!isEpsilon(first[k], fc[k])) {
                    nullable = 0;
                    break;
                }
            }
            // add epsilon if whole production gives epsilon
            if(nullable) {
                int old = fc[index];
                add(first[index], &fc[index], '#');

                if(old != fc[index])
                    changed = 1;
            }
        }

    } while(changed);
}

void FOLLOW() {
    int changed;

    // Add $ to FOLLOW of start symbol
    add(follow[prod[0][0] - 'A'], &flc[prod[0][0] - 'A'], '$');

    do {
        changed = 0;

        for(int i = 0; i < n; i++) {
            char lhs = prod[i][0];
            int lhsIndex = lhs - 'A';

            for(int j = 2; prod[i][j] != '\0'; j++) {

                char c = prod[i][j];

                if(!isupper(c))
                    continue;

                int index = c - 'A';
                int nullable = 1;

                // Find FIRST of the remaining string
                for(int k = j + 1; prod[i][k] != '\0'; k++) {

                    char next = prod[i][k];
                    // if the next letter is a terminal add it to follow
                    if(!isupper(next)) {
                        int old = flc[index];
                        add(follow[index], &flc[index], next);

                        if(old != flc[index])
                            changed = 1;

                        nullable = 0;
                        break;
                    }

                    int nextIndex = next - 'A';
                    // if the next is a non terminal copy the first to the follow
                    for(int x = 0; x < fc[nextIndex]; x++) {
                        if(first[nextIndex][x] != '#') {
                            int old = flc[index];
                            add(follow[index], &flc[index],
                                first[nextIndex][x]);

                            if(old != flc[index])
                                changed = 1;
                        }
                    }

                    if(!isEpsilon(first[nextIndex], fc[nextIndex])) {
                        nullable = 0;
                        break;
                    }
                }

                // If remaining symbols can produce epsilon,
                // add FOLLOW of LHS
                if(nullable) {
                    for(int x = 0; x < flc[lhsIndex]; x++) {
                        int old = flc[index];

                        add(follow[index], &flc[index], follow[lhsIndex][x]);

                        if(old != flc[index])
                            changed = 1;
                    }
                }
            }
        }

    } while(changed);
}

int main() {
    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (Example: E=TR):\n");

    for(int i = 0; i < n; i++) {
        scanf("%s", prod[i]);
    }

    FIRST();
    FOLLOW();

    printf("\nFIRST sets:\n");

    for(int i = 0; i < 26; i++) {
        if(fc[i] > 0) {
            printf("FIRST(%c) = { ", i + 'A');

            for(int j = 0; j < fc[i]; j++)
                printf("%c ", first[i][j]);

            printf("}\n");
        }
    }

    printf("\nFOLLOW sets:\n");

    for(int i = 0; i < 26; i++) {
        if(flc[i] > 0) {
            printf("FOLLOW(%c) = { ", i + 'A');

            for(int j = 0; j < flc[i]; j++)
                printf("%c ", follow[i][j]);

            printf("}\n");
        }
    }

    return 0;
}
