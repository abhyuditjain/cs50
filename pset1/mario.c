#include <stdio.h>
#include <cs50.h>

void build_pyramid(int height);

int main(void) {
    
    printf("Height: ");
    int height = get_int();
    
    while(height > 23 || height < 0) {
        printf("Height: ");
        height = get_int();
    }
    
    build_pyramid(height);
}

void build_pyramid(int n) {
    for(int i=0; i<n; i++) {
        for(int j=n-i-1; j>0; j--) {
            printf(" ");
        }
        for (int j=n-i-1; j<n; j++) {
            printf("#");
        }
        
        printf("  ");
        
        for (int j=n-i-1; j<n; j++) {
            printf("#");
        }
        
        printf("\n");
    }
}