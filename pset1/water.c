#include <stdio.h>
#include <cs50.h>

int get_bottle_count(int);

int main(void) {
    printf("Minutes: ");
    int minutes = get_int();
    
    printf("Bottles: %i\n", get_bottle_count(minutes));
}

int get_bottle_count(int minutes) {
    //1.5 gallons/minute * minutes * 128 ounces/gallon / 16 ounces/bottle
    return (1.5 * minutes * 128)/16;
}