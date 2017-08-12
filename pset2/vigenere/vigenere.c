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
    
    string key = argv[1];
    int keyLength = strlen(key);
    
    for (int i = 0; i< keyLength; i++) {
        if (!isalpha(key[i])) {
            printf("Key not alphabetic\n");
            return 1;
        }
    }
    
    printf("plaintext: ");
    string plaintext = get_string();
    
    printf("ciphertext: ");
    
    for(int i=0, j=0, n = strlen(plaintext); i< n; i++) {
        char c = plaintext[i];
        
        if (isalpha(c)) {
            if (j >= keyLength) {
                j = 0;
            }
            
            if (isupper(c)) {
                if (islower(key[j])) {
                    c = (c - 65 + key[j] - 97) % 26 + 65;
                } else {
                    c = (c - 65 + key[j] - 65) % 26 + 65;
                }
            } else if (islower(c)) {
                if (islower(key[j])) {
                    c = (c - 97 + key[j] - 97) % 26 + 97;
                } else {
                    c = (c - 97 + key[j] - 65) % 26 + 97;
                }
            }
            
            j++;
        }
        printf("%c", c);
    }
    
    printf("\n");
       
}