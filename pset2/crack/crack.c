#define _XOPEN_SOURCE
#include <unistd.h>
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
    
    string encrypted = argv[1];
    char *salt = "50";
    
    char alpha [] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u',
                    'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    int alphalen = 52;
    
    char result[5];
    bool found = false;
    
    if (!found) {
        for(int i=0; i < alphalen; i++) {
            result[0] = alpha[i];
            result[1] = '\0';
            string enc_word = crypt(result, salt);
            
            // printf("%s -- %s\n", result, enc_word);
            
            if (strcmp(enc_word, encrypted) == 0) {
                    printf("%s\n", result);
    				found = true;
    				return 0;
    		}
        }
    }
    
    //2 letter
    if (!found) {
        for(int i=0; i<alphalen; i++){
            for(int j=0; j<alphalen; j++){
                result[0] = alpha[i];
                result[1] = alpha[j];
                result[2] = '\0';
                string enc_word = crypt(result, salt);
            
                //  printf("%s -- %s\n", result, enc_word);
            
                if (strcmp(enc_word, encrypted) == 0) {
                    printf("%s\n", result);
    				found = true;
    				return 0;
    		    }
            }
        }
    }
    
    // 3 letter
    if (!found) {
        for(int i=0; i<alphalen; i++){
            for(int j=0; j<alphalen; j++){
                for(int k=0; k<alphalen; k++){
                    result[0] = alpha[i];
                    result[1] = alpha[j];
                    result[2] = alpha[k];
                    result[3] = '\0';
                    string enc_word = crypt(result, salt);
                    
                    // printf("%s -- %s\n", result, enc_word);
                    
                    if (strcmp(enc_word, encrypted) == 0) {
                            printf("%s\n", result);
            				found = true;
            				return 0;
            		}
                }
            }
        }
    }
    
    // 4 letter
    if (!found) {
        for(int i=0; i<alphalen; i++){
            for(int j=0; j<alphalen; j++){
                for(int k=0; k<alphalen; k++){
                    for(int l=0; l<alphalen; l++){
                        result[0] = alpha[i];
                        result[1] = alpha[j];
                        result[2] = alpha[k];
                        result[3] = alpha[l];
                        result[4] = '\0';
                        string enc_word = crypt(result, salt);
                        
                        // printf("%s -- %s\n", result, enc_word);
                        
                        if (strcmp(enc_word, encrypted) == 0) {
                                printf("%s\n", result);
                				found = true;
                				return 0;
                		}
                    }
                }   
            }
        }
    }
    
    // if (found) {
    //     printf("%s\n", result);
    // }
    
    return 0;
}
