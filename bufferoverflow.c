#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }
    
    // allocating 5 bytes but can write more so, it's bad.
    // char *s = malloc(5);
    
    // allocate strlen() + 1 (including '\0')
    char *s = malloc(strlen(argv[1])+1);
    
    // copy entire string including '\0'
    memcpy(s, argv[1], strlen(argv[1]) + 1);
    
    printf("s: %s\n", s);
    
    free(s);
    
    int *p = malloc(sizeof(int));
    
    *p = 4;
    
    printf("int: %i\n", *p);
    printf("address: %p\n", &p);
    printf("pointer: %p\n", p);
    
    free(p);
}
