#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void) {
    printf("O hai! How much change is owed?\n");
    float change = get_float();
    
    while (change < 0) {
        printf("O hai! How much change is owed?\n");
        change = get_float();
    }
    
    int cents =  round(change*100);
    
    int coins = 0;
    while (cents > 0) {
        if (cents - 25 >= 0) {
            cents -= 25;
        } else if (cents - 10 >= 0) {
            cents -= 10;
        } else if (cents - 5 >= 0) {
            cents -= 5;
        } else if (cents - 1 >= 0) {
            cents -= 1;
        }
        
        coins++;
    }
    
    printf("%i\n", coins);
}