/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // binary search
    int first = 0;
    int last = n-1;
    
    while (first <= last) {
        int mid = (first + last)/2;
        
        if (values[mid] == value) {
            return true;
        } else if (value > values[mid]) {
            first = mid+1;
        } else {
            last = mid-1;
        }
    }
    
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // counting the number of occurences and then filling the array
    
    int count[65537];
    
    for (int i=0; i<n; i++) {
        // printf("i=%i\n", i);
        // printf("values[i]=%i\n", values[i]);
        count[values[i]]++;
        
        // printf("count[values[i]]=%i\n", count[values[i]]);
    }
    
    for (int i=0, j=0; i<65537; i++) {
        while (count[i] > 0 && j<n) {
            // printf("j=%i\n", j);
            values[j] = i;
            // printf("values[j]=%i\n", values[j]);
            count[i]--;
            j++;
        }
    }
    
    return;
}
