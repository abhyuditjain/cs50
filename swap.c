#include <stdio.h>

void swap(int *a, int *b);

int main(void) {
    int x = 1;
    int y = 2;
    
    printf("Before SWAP:\n\tx = %i\n\ty = %i\n\n", x, y);
    
    swap(&x, &y);
 
    printf("After SWAP:\n\tx = %i\n\ty = %i\n\n", x, y);
}

void swap(int *a, int *b) {
    
    // *a means dereferencing the pointer i.e. go to the address in a and get value stored there.
    int temp = *a;
    *a = *b;
    *b = temp;
}