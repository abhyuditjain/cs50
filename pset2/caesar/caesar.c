#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[]) {
    
    if (argc != 2) {
        printf("Error in arguments\n");
        return 1;
    }
    
    printf("plaintext: ");
    string plaintext = get_string();
    
    // Convert the string to int (base 10)
    int shift = strtol(argv[1], NULL, 10);
    
    printf("ciphertext: ");
    
    for(int i=0, n = strlen(plaintext); i< n; i++) {
        char c = plaintext[i];
        
        if (isupper(c)) {
            c = (c + shift - 65) % 26 + 65;
        } else if (islower(c)) {
            c = (c + shift - 97) % 26 + 97;
        }
        
        printf("%c", c);
    }
    
    printf("\n");
}