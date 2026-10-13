
#include <stdio.h>
#define MAX 20

int n, trans[MAX][2][MAX], dfa[MAX][2];
int sets[MAX][MAX], count = 0;

int find(int s[]) {
    for (int i = 0; i < count; i++) {
        int j;
        for (j = 0; j < n && sets[i][j] == s[j]; j++);
        if (j == n) return i;
    }
    return -1;
}

int add(int s[]) {
    for (int i = 0; i < n; i++)
        sets[count][i] = s[i];
    return count++;
}

int main() {
    int start, c, to, s[MAX], i, j, k, x;

    printf("Enter number of NFA states: ");
    scanf("%d", &n);
    if (n < 1 || n > MAX) return 1;

    for (i = 0; i < n; i++)
        for (j = 0; j < 2; j++) {
            printf("From q%d on input %d, number of destinations: ", i, j);
            scanf("%d", &c);
            printf("Enter destination states: ");
            while (c--) {
                scanf("%d", &to);
                if (to >= 0 && to < n)
                    trans[i][j][to] = 1;
            }
        }

    printf("Enter start state: ");
    scanf("%d", &start);
    if (start < 0 || start >= n) return 1;

    for (i = 0; i < n; i++) s[i] = 0;
    s[start] = 1;
    add(s);

    for (i = 0; i < count; i++)
        for (j = 0; j < 2; j++) {
            for (k = 0; k < n; k++) s[k] = 0;

            for (k = 0; k < n; k++)
                if (sets[i][k])
                    for (x = 0; x < n; x++)
                        if (trans[k][j][x]) s[x] = 1;

            int d = find(s);
            if (d == -1) d = add(s);
            dfa[i][j] = d;
        }

    printf("\nDFA Transition Table\nState\t\t0\t1\n");
    for (i = 0; i < count; i++) {
        printf("D%d = {", i);
        for (j = 0; j < n; j++)
            if (sets[i][j]) printf("q%d ", j);
        printf("}\tD%d\tD%d\n", dfa[i][0], dfa[i][1]);
    }

    return 0;
}
