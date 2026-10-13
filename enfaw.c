#include <stdio.h>
#include <stdlib.h>


#define MAX 10


int n_states, n_symbols, n_final;
char symbols[MAX], nfa[MAX][MAX][MAX], nfa_no_e[MAX][MAX][MAX];


void epsilon_closure(int state, int closure[MAX], int *n_closure) {
   if (closure[state] == 1)
       return;   // Already in the closure


   closure[state] = 1;
   (*n_closure)++;


   for (int i = 0; i < n_states; i++) {
       if (nfa[state][n_symbols][i] == '1') {
           epsilon_closure(i, closure, n_closure);
       }
   }
}


void initialize_table() {
   printf("Enter the number of states: ");
   scanf("%d", &n_states);


   printf("Enter the number of input symbols (excluding epsilon): ");
   scanf("%d", &n_symbols);


   printf("Enter the symbols (for example: a b c):\n");
   for (int i = 0; i < n_symbols; i++) {
       scanf(" %c", &symbols[i]);
   }


   symbols[n_symbols] = 'e';   // Epsilon transition symbol


   for (int i = 0; i < n_states; i++) {
       for (int j = 0; j < n_symbols + 1; j++) {   // Include epsilon
           for (int k = 0; k < n_states; k++) {
               nfa[i][j][k] = '0';   // Initialize all to '0'
           }
       }
   }


   int trans;
   printf("Enter the number of transitions: ");
   scanf("%d", &trans);


   printf("Enter transitions in the form (start, symbol, end) (e for epsilon):\n");


   for (int i = 0; i < trans; i++) {
       int start, end;
       char symbol;


       scanf("%d %c %d", &start, &symbol, &end);


       int symbol_index;


       if (symbol == 'e')
           symbol_index = n_symbols;   // Epsilon index
       else {
           for (int j = 0; j < n_symbols; j++) {
               if (symbols[j] == symbol) {
                   symbol_index = j;
                   break;
               }
           }
       }


       nfa[start][symbol_index][end] = '1';   // Mark the transition
   }
}


void convert_to_nfa_without_epsilon() {
   for (int state = 0; state < n_states; state++) {


       int closure[MAX] = {0};
       int n_closure = 0;


       epsilon_closure(state, closure, &n_closure);


       for (int sym = 0; sym < n_symbols; sym++) {
           for (int i = 0; i < n_states; i++) {


               if (closure[i] == 1) {


                   for (int j = 0; j < n_states; j++) {


                       if (nfa[i][sym][j] == '1') {
                           nfa_no_e[state][sym][j] = '1';
                       }


                   }
               }
           }
       }
   }
}


void print_nfa_formatted(char table[MAX][MAX][MAX], int symbols_count) {


   for (int i = 0; i < n_states; i++) {
       for (int j = 0; j < symbols_count; j++) {
           for (int k = 0; k < n_states; k++) {


               if (table[i][j][k] == '1') {
                   printf("q%d %c q%d\n", i, symbols[j], k);
               }


           }
       }
   }
}


int main() {


   initialize_table();


   convert_to_nfa_without_epsilon();


   printf("\nEquivalent NFA without epsilon transitions (formatted):\n");


   print_nfa_formatted(nfa_no_e, n_symbols);


   return 0;
}
