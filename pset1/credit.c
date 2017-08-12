#include <stdio.h>
#include <cs50.h>

int is_valid_credit_card(long long);
long long power_of_ten(int);

int main(void) {
    printf("Number: ");
    long long number = get_long_long();
    
    switch(is_valid_credit_card(number)) {
        case 1:
            printf("AMEX\n");
            break;
        case 2:
            printf("MASTERCARD\n");
            break;
        case 3:
            printf("VISA\n");
            break;
        default:
            printf("INVALID\n");
            break;
    }
}

int is_valid_credit_card(long long number) {
    long long copy = number;
    long long sum1 = 0;
    long long sum2 = 0;
    int length = 0;
    
    while (number > 0) {
       // printf("length: %i\tdigit: %lld", length, number%10);
        if (length % 2 == 0) {
            sum1 += (number%10);
            // printf("\n");
        } else {
            long long prod = (number%10) * 2;
            while(prod > 0) {
                sum2 += prod%10;
                prod /= 10;
            }
            
            //printf("x2 = %lld\n",(((number%10) * 2)%10));
        }
        length++;
        number /= 10;
    }
    
    // printf("%lld\n", sum1+sum2);
    // printf("Length: %i\n", length);
    long long mod = (sum1 + sum2) % 10;
    
    if (mod == 0) {
        // printf("Copy mod power of 10: %lld\n", copy/power_of_ten(length-2));
        if (length == 15 && ((copy/power_of_ten(length-2)) == 34 || (copy/power_of_ten(length-2) == 37))) {
            return 1;
        }
        
        if (length == 16 && ((copy/power_of_ten(length-2) >= 51) && (copy/power_of_ten(length-2) <= 55))) {
            return 2;
        }
        
        if ((length == 13 || length == 16) && ((copy/power_of_ten(length-1) == 4))) {
            return 3;
        }
    }
    
    return 0;
}

long long power_of_ten(int n) {
    long long prod = 10;
    for (int i = 1; i< n; i++) {
        prod *= 10;
    }
    
    return prod;
}