#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    string name = get_string();
    
    bool found = false;
    
    for (int i=0, n = strlen(name); i<n; i++) {
        if (name[i] == ' ') {
            found = false;
            continue;
        }
        
        if (name[i] != ' ' && !found) {
            printf("%c", toupper(name[i]));
            found = true;
        }
    }
    
    printf("\n");
}