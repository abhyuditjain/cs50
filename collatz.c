#include <stdio.h>
#include <stdlib.h>

int collatz(int n);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./collatz n\n");
        return 1;
    }
    
    int n = atoi(argv[1]);
    
    if (n <= 0) {
        printf("n should be >= 0\n");
        return 1;
    }
    
    printf("Number of steps: %i\n", collatz(n));
}

int collatz(int n) {
    if (n == 1) {
        return 0;
    } else if (n%2 == 0) {
        return 1 + collatz(n/2);
    } else {
        return 1 + collatz(3*n + 1);
    }
    
}