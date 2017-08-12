#include <stdio.h>
#include <cs50.h>

int main(int argc, string argv[]) {
    
    printf("Hello ");
    
    printf("%s\t", argv[0]);
    if (argc == 2) {
        printf("%s\t", argv[1]);
    }
    
    printf("\n");
}