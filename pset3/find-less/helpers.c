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
    // insertion sort
    
    for (int i=1; i<n; i++) {
        int key = values[i];
        int j = i-1;
        
        while(j>=0 && values[j] > key) {
            values[j+1] = values[j];
            j--;
        }
        
        values[j+1] = key;
    }
    return;
}
