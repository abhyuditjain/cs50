#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

void copy(char *to, char *from);

int main(void) {
    char *s = get_string();
    
    printf("Initial string: %s\n", s);
    
    // strlen(s) + 1 because we need the '\0' also.
    char *t = malloc((strlen(s) + 1) * sizeof(char));
    
    copy(t, s);
 
    t[0] = toupper(t[0]);
    
    printf("Initial string: %s\n", s);
    printf("Copied string: %s\n", t);
    
    // free the memory to avoid leaks
    free(t);
}

void copy(char *to, char *from) {
    for (int i=0, n= strlen(from) + 1; i<n; i++) {
        // to[i] = from[i]  <=== syntactic sugar
        *(to + (i * sizeof(char))) = *(from + (i * sizeof(char)));
    }
}