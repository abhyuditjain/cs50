#include <stdio.h>
#include <cs50.h>

int main(void) {

    printf("Size of bool: %lu\n", sizeof(bool));
    printf("Size of char: %lu\n", sizeof(char));
    printf("Size of int: %lu\n", sizeof(int));
    printf("Size of float: %lu\n", sizeof(float));
    printf("Size of long: %lu\n", sizeof(long));
    printf("Size of double: %lu\n", sizeof(double));
    printf("Size of long long: %lu\n", sizeof(long long));
    printf("Size of string: %lu\n", sizeof(string));
    
    long long n = 1;
    
    for(int i=0; i<65; i++) {
        printf("n is %lld\n", n);
        
        n *= 2;
    }
}